package com.example.autobrake_android

import android.annotation.SuppressLint
import android.app.ProgressDialog
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothSocket
import android.content.Context
import android.content.Intent
import android.location.Location
import android.location.LocationListener
import android.location.LocationManager
import android.os.*
import android.speech.tts.TextToSpeech
import android.util.Log
import android.view.MotionEvent
import android.view.View
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.google.firebase.database.*
import kotlinx.android.synthetic.main.activity_main.*
import java.io.IOException
import java.text.SimpleDateFormat
import java.util.*


@Suppress("RECEIVER_NULLABILITY_MISMATCH_BASED_ON_JAVA_ANNOTATIONS")
class MainActivity: AppCompatActivity() {

    companion object {
        var m_myUUID: UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB")
        private const val BLUETOOTH_SEND_STRING = 1
        var m_bluetoothSocket: BluetoothSocket? = null
        lateinit var m_progress: ProgressDialog
        var m_bluetoothAdapter = BluetoothAdapter.getDefaultAdapter()
        var m_isConnected: Boolean = false
        lateinit var m_address: String

        lateinit var mTTS:TextToSpeech

        const val BT_TAG = "BLUETOOTH DEBUG"
        const val TOUCH_TAG = "TOUCH DEBUG"

        val mmBuffer: ByteArray = ByteArray(1024)
        var numBytes: Int = 0
        var isRun = false

        //onTouch
        var x1 =0F
        var x2 =0F

        lateinit var initHandler: Handler

    }


    @SuppressLint("SetTextI18n")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        supportActionBar!!.setDisplayShowHomeEnabled(true);
        supportActionBar!!.setIcon(R.mipmap.ic_launcher_foreground);
        setContentView(R.layout.activity_main)




        //connect to BT
        m_address = "00:21:13:00:17:D1"
        ConnectToDevice(this,this).execute()

        //connect btn
        reconnect_btn.setOnClickListener { disconnect(this)
            ConnectToDevice(this, this).execute() }
        exit_btn.setOnClickListener { disconnect(this)
            finish()    }

        //GPS
        getLocation(this)


        //speech init
        mTTS = TextToSpeech(applicationContext, TextToSpeech.OnInitListener { status ->
            if(status != TextToSpeech.ERROR)
                mTTS.language = Locale.ENGLISH
        })

        // bike init status handler
        initHandler = @SuppressLint("HandlerLeak") object: Handler() {
            override fun handleMessage(msg: Message) {

                when(msg.what) {
                    2 -> {
                        ready_txt.text = "System All Set"
                        btn_layout.alpha = 1F
                    }
                    3 ->  ready_txt.text = "SD Card Checking"
                    4 ->  ready_txt.text = "SD Card OK"
                    5 ->  ready_txt.text = "SD Card Error (Please Insert SD Card)"
                    6 ->  ready_txt.text = "Controller Checking"
                    7 ->  ready_txt.text = "Controller OK"
                    8 ->  ready_txt.text = "Controller Error (Please Restart)"
                }

            }
        }



        btn_layout.alpha = 0.5F

        //start BT and show BT receiveThread value
        start_receive_btn.setOnClickListener {
            val vibrator = getSystemService(Context.VIBRATOR_SERVICE) as Vibrator

            var warningLight = 0
            var warningLine = 0
            var warningRecognition = 0

            val startingHandler = @SuppressLint("HandlerLeak") object: Handler() {
                override fun handleMessage(msg: Message) {

                    //GET BT data
                    if(msg.what==BLUETOOTH_SEND_STRING) {
                        // copy and split
                        var b: ByteArray = mmBuffer.copyOf(numBytes)
                        var bufToString = b.toString(Charsets.UTF_8)
                        // in case n==0 get null
                        if(bufToString[0] == '|')   bufToString = bufToString.drop(1)
                        val part = bufToString.split('|').toMutableList()
                        Log.d(BT_TAG, "BTget: $bufToString")
                        Log.d(BT_TAG, part.size.toString())

                        var warningDirection = ' '


                        for (i in 0..part.size - 2) {
                            var differentiate = part[i].first()
                            part[i] = part[i].drop(1)
                            when (differentiate) {

                                //set speed and progress bar
                                'S' -> {
                                    var speed = part[i].toInt()
                                    if (speed > 30) speed = 30
                                    speed_txt.text = speed.toString()
                                    progress_circular.max = 40
                                    progress_circular.setProgress(speed, true)
                                }

                                //set battery
                                'B' -> battery_txt.text = part[i] + '%'


                                'X' -> warningLight = part[i].toInt()
                                'Y' -> warningLine = part[i].toInt()
                                'Z' -> {warningRecognition = part[i][0].toInt()
                                        if(part[i].length>1) warningDirection = part[i][1]}

                                //set motor
                                'M' -> motor_txt.text = part[i] + '%'

                                'T' -> engineT_txt.text = part[i] + "℃"

                            }
                        }

                        if(warningLight == 0 && warningLine == 0 && warningRecognition == 0){
                            warning_img.visibility = View.INVISIBLE
                        }

                        // if warning
                        if (warningLight == 1 || warningLine == 1 || warningRecognition == 1) {
                            progress_circular.setProgress(0, true)

                            if (vibrator.hasVibrator()) {
                                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                                    vibrator.vibrate(
                                        VibrationEffect.createOneShot(
                                            1000,
                                            VibrationEffect.DEFAULT_AMPLITUDE
                                        )
                                    )
                                } else {
                                    vibrator.vibrate(1000)
                                }
                            }

                            // object warning
                            if(warningRecognition == 1) {
                                warning_img.setImageResource(R.mipmap.close_warning)
                                warning_img.visibility = View.VISIBLE
                                if(warningDirection == 'l') {
                                    mTTS.speak(
                                        "Be careful of light side", TextToSpeech.QUEUE_FLUSH, null
                                    )
                                }
                                else if (warningDirection == 'r'){
                                    mTTS.speak(
                                        "Be careful of left side", TextToSpeech.QUEUE_FLUSH, null
                                    )
                                }else {
                                    mTTS.speak(
                                        "watch out!start braking system", TextToSpeech.QUEUE_FLUSH, null
                                    )
                                }
                            }
                            // traffic light warning
                            else if(warningLight == 1) {
                                warning_img.setImageResource(R.mipmap.light_warning)
                                warning_img.visibility = View.VISIBLE

                                mTTS.speak(
                                    "Red light detected", TextToSpeech.QUEUE_FLUSH, null
                                )
                            }
                            // deviation warning
                            else if(warningLine == 1) {
                                warning_img.setImageResource(R.mipmap.line_warning)
                                warning_img.visibility = View.VISIBLE

                                mTTS.speak(
                                    "Please keep on the right side", TextToSpeech.QUEUE_FLUSH, null
                                )
                            }
                        }

                    }
                }
            }
            val thread = ReceiveThread(startingHandler)


            if(!isRun)
            {
                isRun = true
                start_receive_btn.setBackgroundResource(R.drawable.custom_button_pause)
                start_receive_btn.text = "PAUSE"
                thread.start()
                val cal = Calendar.getInstance()
                val dateReturn = '@'+SimpleDateFormat("yy:MM:dd:HH:mm:ss:SS").format(cal.time)
                sendData(dateReturn)
                ready_txt.visibility = View.INVISIBLE
            }
            else
            {
                isRun = false
                start_receive_btn.setBackgroundResource(R.drawable.custom_button)
                start_receive_btn.text = "START"
                sendData("#")
            }
            

        }


        // current time
        object: CountDownTimer(86400000, 1000) {
            @SuppressLint("SetTextI18n")
            override fun onFinish() {
                time_txt.text = "run over 24H"
            }
            @SuppressLint("SimpleDateFormat")
            override fun onTick(millisUntilFinished: Long) {
                val cal = Calendar.getInstance()
                time_txt.text = SimpleDateFormat("HH:mm:ss").format(cal.time)
            }

        }.start()
    }

    // open google map
    override fun onTouchEvent(e: MotionEvent): Boolean {


        var isTouched = false
        when (e.action) {
            MotionEvent.ACTION_DOWN -> {
                x1 = e.getX()
                Log.d(TOUCH_TAG, "DOWN!!!$x1")
            }
            MotionEvent.ACTION_UP -> {
                x2 = e.getX()
                Log.d(TOUCH_TAG, "UP!!!$x2")
                isTouched = true
            }
        }
        if(x1-x2 > 600 && isTouched)
        {

            var intent = Intent(this, MapsActivity::class.java)
            startActivity(intent)
        }
        return false
    }

    //BT Receive Data
    class ReceiveThread(private val handler: Handler) : Thread() {
        override fun run() {

            Log.d(BT_TAG, "START THREAD")
            var available = 0
            while (true) {
                if(!isRun) return
                if(m_bluetoothSocket != null)
                {
                    try {
                        available = m_bluetoothSocket!!.inputStream.available()
                        if(available>0) {
                            //wait for read
                            Thread.sleep(40 )
                            numBytes = m_bluetoothSocket!!.inputStream.read(mmBuffer, 0, 500)

                            //debug show the num and value of BT
                            Log.d(BT_TAG, "--------------------------")
                            Log.d(BT_TAG, "numBytes :  " +numBytes)
//                            for(x in 0..numBytes-1)
//                            {
//                                Log.d(BT_TAG, "buffer :  " + mmBuffer[x])
//                            }

                            //return msg to UI
                            val message = Message.obtain()
                            message.what = BLUETOOTH_SEND_STRING
                            handler.sendMessage(message)

                        }
                    } catch (e: IOException) {
                        Log.d(BT_TAG, "BT Input stream was disconnected", e)
                    }
                }




            }

        }
    }

    // BT send data
    fun sendData(input: String) {
        if(m_bluetoothSocket != null)
        {
            try{
                Log.d(BT_TAG, "BT write :　"+ input)
                m_bluetoothSocket!!.outputStream.write(input.toByteArray())
            } catch(e: IOException) {
                e.printStackTrace()
                Log.d(BT_TAG, "BT write got wrong ", e)
            }
        }


    }

    //BT disconnect
    private fun disconnect(context: Context) {
        if (m_bluetoothSocket != null) {
            try {
                m_bluetoothSocket!!.close()
                m_bluetoothSocket = null
                m_isConnected = false
                Toast.makeText(context,"disconnected", Toast.LENGTH_SHORT).show()
            } catch (e: IOException) {0
                e.printStackTrace()
            }
        }
//        finish()
    }

    //BT connect
    class ConnectToDevice(private var context: Context, private var activity: MainActivity) : AsyncTask<Void, Void, String>() {


        private var connectSuccess: Boolean = true

        override fun onPreExecute() {
            super.onPreExecute()
            m_progress = ProgressDialog.show(context, "Connecting...", "please wait")
        }

        override fun doInBackground(vararg p0: Void?): String? {
            try {
                if (m_bluetoothSocket == null || !m_isConnected) {
                    val device: BluetoothDevice = m_bluetoothAdapter.getRemoteDevice(m_address)
                    m_bluetoothSocket = device.createInsecureRfcommSocketToServiceRecord(m_myUUID)
                    BluetoothAdapter.getDefaultAdapter().cancelDiscovery()
                    m_bluetoothSocket!!.connect()
                }
            } catch (e: IOException) {
                connectSuccess = false
                e.printStackTrace()
            }
            return null
        }

        @SuppressLint("SetTextI18n")
        override fun onPostExecute(result: String?) {
            super.onPostExecute(result)


            if (connectSuccess) {
                m_isConnected = true
                val cal = Calendar.getInstance()
                val dateReturn = '@'+SimpleDateFormat("yy:MM:dd:HH:mm:ss:SS").format(cal.time)
                activity.sendData(dateReturn)

                Toast.makeText(context,"connected", Toast.LENGTH_SHORT).show()

            } else {
                Toast.makeText(context,"couldn't connect", Toast.LENGTH_SHORT).show()
            }

            m_progress.dismiss()


            if(connectSuccess) {
                try {
                    Log.d(BT_TAG, "start listen bike init status")

                    Thread {
                        while (true) {

                            Thread.sleep(50)
                            if(!m_isConnected) break

                            if (m_bluetoothSocket!!.inputStream.available() > 0) {
                                // wait for read
                                Thread.sleep(30)
                                numBytes = m_bluetoothSocket!!.inputStream.read(mmBuffer, 0, 500)

                                var b: ByteArray = mmBuffer.copyOf(numBytes)
                                var bufToString = b.toString(Charsets.UTF_8)
                                Log.d(BT_TAG, "BTget: $bufToString")


                                val message = Message.obtain()
                                if (bufToString == "=") {
                                    message.what = 2
                                    initHandler.sendMessage(message)
                                    break
                                }
                                else if (bufToString == "SC") {
                                    message.what = 3
                                }
                                else if (bufToString == "SO") {
                                    message.what = 4
                                }
                                else if (bufToString == "SE") {
                                    message.what = 5
                                }
                                else if (bufToString == "CC") {
                                    message.what = 6
                                }
                                else if (bufToString == "CO") {
                                    message.what = 7
                                }
                                else if (bufToString == "CE") {
                                    message.what = 8
                                }
                                initHandler.sendMessage(message)
                            }
                        }
                    }.start()

                } catch (e: IOException) {
                    Log.d(BT_TAG, "BT Input stream was disconnected", e)
                }
            }
        }

    }

    @SuppressLint("MissingPermission")
    private fun getLocation(context: Context) {
        val locationManager = getSystemService(Context.LOCATION_SERVICE) as LocationManager
        val hasGps = locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER)


        val database: FirebaseDatabase = FirebaseDatabase.getInstance()
        val myRef: DatabaseReference = database.getReference("autobrake")


        if (hasGps) {
            Log.d("GPS", "hasGps")
            locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 5000, 0F, object : LocationListener {

                override fun onLocationChanged(location: Location?) {
                    Log.d("GPS", "changed")
                    if (location != null) {
                        val latitude = location.latitude
                        val longitude = location.longitude

                        Log.d("GPS", " GPS Latitude : $latitude")
                        Log.d("GPS", " GPS Longitude : $longitude")

                        //to firebase
                        myRef.child("lat").setValue(latitude)
                        myRef.child("lon").setValue(longitude)


//                        /*------- To get city name from coordinates -------- */
//                        var cityName: String? = null
//                        val gcd = Geocoder(context, Locale.getDefault())
//                        val addresses: List<Address>
//                        try {
//                            addresses = gcd.getFromLocation(latitude, longitude, 1)
//                            if (addresses.isNotEmpty()) {
//                                cityName = addresses[0].locality
//                                Log.d("GPS", " GPS City name: $cityName")
//                            }
//                        } catch (e: IOException) {
//                            e.printStackTrace()
//                        }



                    }
                }

                override fun onStatusChanged(provider: String?, status: Int, extras: Bundle?) {}
                override fun onProviderEnabled(provider: String?) {}
                override fun onProviderDisabled(provider: String?) {}

            })

            val localGpsLocation = locationManager.getLastKnownLocation(LocationManager.GPS_PROVIDER)
            if (localGpsLocation != null)
                Log.d("GPS", " End GPS Latitude : " + localGpsLocation.latitude)
                Log.d("GPS", " End GPS Longitude : " + localGpsLocation.longitude)
                myRef.child("lat").setValue(localGpsLocation.latitude)
                myRef.child("lon").setValue(localGpsLocation.longitude)
        }
        
    }

}