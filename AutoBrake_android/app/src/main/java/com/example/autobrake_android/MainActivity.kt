package com.example.autobrake_android

import android.Manifest
import android.annotation.SuppressLint
import android.app.Activity
import android.app.ProgressDialog
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothSocket
import android.content.Context
import android.content.Intent
import android.content.pm.PackageManager
import android.location.Location
import android.location.LocationListener
import android.location.LocationManager
import android.net.Uri
import android.os.*
import android.speech.tts.TextToSpeech
import android.util.Log
import android.view.MotionEvent
import android.view.View
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.app.ActivityCompat.startActivityForResult
import androidx.fragment.app.FragmentActivity
import com.google.firebase.database.*
import kotlinx.android.synthetic.main.activity_main.*
import java.io.IOException
import java.text.SimpleDateFormat
import java.util.*


class MainActivity: AppCompatActivity() {

    companion object {
        var m_myUUID: UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB")
        lateinit var m_address: String
        var m_bluetoothSocket: BluetoothSocket? = null
        var m_bluetoothAdapter: BluetoothAdapter? = BluetoothAdapter.getDefaultAdapter()
        var m_isConnected: Boolean = false
        lateinit var m_progress: ProgressDialog


        lateinit var mTTS:TextToSpeech

        const val BT_TAG = "BLUETOOTH_DEBUG"
        const val TOUCH_TAG = "TOUCH_DEBUG"
        const val GPS_TAG = "GPS_DEBUG"

        const val REQUEST_GPS = 1
        const val REQUEST_CALL = 2
        const val REQUEST_BT = 3

        val mmBuffer: ByteArray = ByteArray(1024)
        var numBytes: Int = 0
        var isRun = false


        lateinit var initHandler: Handler

        var callNumber = ""

    }


    @SuppressLint("SetTextI18n", "SimpleDateFormat")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        supportActionBar!!.setDisplayShowHomeEnabled(true);
        supportActionBar!!.setIcon(R.mipmap.ic_launcher_foreground);
        setContentView(R.layout.activity_main)





        //connect to BT
        m_address = "AB:F5:E7:56:34:02"
//        m_address = "00:21:13:00:1C:F0"

        if (m_bluetoothAdapter?.isEnabled == false) {
            val enableBtIntent = Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE)
            startActivityForResult(enableBtIntent, REQUEST_BT)
        }else {
            ConnectToDevice(this,this).execute()
        }


        //GPS
        getLocation(this)


        firebase()


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
                        start_btn.isEnabled = true
                        start_btn.alpha = 1F
                    }
                    3 ->  ready_txt.text = "System Error"

                }

            }
        }




        exit_btn.setOnClickListener { disconnect(this)
                                        finish()}
        call_btn.setOnClickListener {
            val callIntent = Intent(Intent.ACTION_CALL)
            val string = "tel:$callNumber"
            callIntent.data = Uri.parse(string)

            if (ActivityCompat.checkSelfPermission(this@MainActivity, Manifest.permission.CALL_PHONE) != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(this,
                    arrayOf(Manifest.permission.CALL_PHONE),
                    REQUEST_CALL)
            }else
                startActivity(callIntent)
        }


        start_btn.alpha = 0.4F
        start_btn.isEnabled = false

        //start BT and show BT receiveThread value
        val vibrator = getSystemService(Context.VIBRATOR_SERVICE) as Vibrator

        var warningLight = 0
        var warningLine = 0
        var warningRecognition = 0
        var speed = 0

        start_btn.setOnClickListener {


            val startingHandler = @SuppressLint("HandlerLeak") object: Handler() {
                override fun handleMessage(msg: Message) {

                    //GET BT data
                    if(msg.what==1) {
                        // copy and split
                        var b: ByteArray = mmBuffer.copyOf(numBytes)
                        var bufToString = b.toString(Charsets.UTF_8)
                        // in case n==0 get null
                        if(bufToString[0] == '|')   bufToString = bufToString.drop(1)
                        val part = bufToString.split('|').toMutableList()
                        Log.d(BT_TAG, "BTget:$bufToString")
                        Log.d(BT_TAG, part.size.toString())

                        var warningDirection = ' '


                        for (i in 0..part.size - 2) {
                            var differentiate = part[i].first()
                            part[i] = part[i].drop(1)
                            when (differentiate) {

                                //set speed and progress bar
                                'S' -> {
                                    speed = part[i].toInt()
                                    if (speed > 30) speed = 30
                                    speed_txt.text = speed.toString()
                                    progress_circular.max = 40
                                    progress_circular.setProgress(speed, true)
                                }

                                //set battery
                                'B' -> {
                                    battery_txt.text = part[i] + '%'
                                    var battery = part[i].toInt()
                                    when(battery) {
                                        in 81..100 -> battery_img.setImageResource(R.drawable.battery_5)
                                        in 61..80 -> battery_img.setImageResource(R.drawable.battery_4)
                                        in 41..60 -> battery_img.setImageResource(R.drawable.battery_3)
                                        in 21..40 -> battery_img.setImageResource(R.drawable.battery_2)
                                        in 0..20 -> battery_img.setImageResource(R.drawable.battery_1)
                                    }
                                }


                                'X' -> warningLight = part[i].toInt()
                                'Y' -> warningLine = part[i].toInt()
                                'Z' -> {warningRecognition = Character.getNumericValue( part[i][0])
                                        if(part[i].length>1) warningDirection = part[i][1]}

                                //set motor
//                                'M' -> motor_txt.text = part[i] + '%'
//
//                                'T' -> engineT_txt.text = part[i] + "℃"

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
                                warning_img.setImageResource(R.drawable.close_warning)
                                warning_img.visibility = View.VISIBLE
                                if(warningDirection == 'l') {
                                    mTTS.speak(
                                        "Beware of left side", TextToSpeech.QUEUE_FLUSH, null
                                    )
                                }
                                else if (warningDirection == 'r'){
                                    mTTS.speak(
                                        "Beware of right side", TextToSpeech.QUEUE_FLUSH, null
                                    )
                                }else if(warningDirection == 'f'){
                                    mTTS.speak(
                                        "watch out!start braking system", TextToSpeech.QUEUE_FLUSH, null
                                    )
                                }else {
                                    mTTS.speak(
                                        "Beware of the rear", TextToSpeech.QUEUE_FLUSH, null
                                    )
                                }
                            }

                            // traffic light warning
                            else if(warningLight == 1) {
                                warning_img.setImageResource(R.drawable.light_warning)
                                warning_img.visibility = View.VISIBLE

                                mTTS.speak(
                                    "Red light detected", TextToSpeech.QUEUE_FLUSH, null
                                )
                            }


                            // deviation warning
                            else if(warningLine == 1) {
                                warning_img.setImageResource(R.drawable.line_warning)
                                warning_img.visibility = View.VISIBLE

                                mTTS.speak(
                                    "Please keep on the right side", TextToSpeech.QUEUE_FLUSH, null
                                )
                            }
                        }

                    }
                }
            }
            val thread = MovingMode(startingHandler)


            if(!isRun)
            {
                isRun = true
                start_btn.setBackgroundResource(R.drawable.custom_button_pause)
                start_btn.text = "暫停"
                thread.start()
                sendData("@")
                ready_txt.visibility = View.INVISIBLE
            }
            else
            {
                isRun = false
                start_btn.setBackgroundResource(R.drawable.custom_button)
                start_btn.text = "開始"
                sendData("#")
            }
            

        }


        // current time
        object: CountDownTimer(86400000, 1000) {
            override fun onFinish() {
                hour_txt.text = "run over 24H"
            }
            @SuppressLint("SimpleDateFormat")
            override fun onTick(millisUntilFinished: Long) {
                val cal = Calendar.getInstance()
                hour_txt.text = SimpleDateFormat("HH:").format(cal.time)
                minute_txt.text = SimpleDateFormat("mm").format(cal.time)
            }

        }.start()
    }

    // open google map
    var x1 =0F
    var x2 =0F
    override fun onTouchEvent(e: MotionEvent): Boolean {


        var isTouched = false
        when (e.action) {
            MotionEvent.ACTION_DOWN -> {
                x1 = e.x
                Log.d(TOUCH_TAG, "DOWN!!!$x1")
            }
            MotionEvent.ACTION_UP -> {
                x2 = e.x
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
    class MovingMode(private val handler: Handler) : Thread() {
        override fun run() {

            Log.d(BT_TAG, "START THREAD")
            var available: Int
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
                            Log.d(BT_TAG, "numBytes :  $numBytes")
//                            for(x in 0..numBytes-1)
//                            {
//                                Log.d(BT_TAG, "buffer :  " + mmBuffer[x])
//                            }

                            //return msg to UI
                            val message = Message.obtain()
                            message.what = 1
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
                Log.d(BT_TAG, "BT write :　$input")
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
//                Toast.makeText(context,"disconnected", Toast.LENGTH_SHORT).show()
            } catch (e: IOException) {
                e.printStackTrace()
            }
        }
    }

    //BT connect and receive bike state
    class ConnectToDevice(private var context: Context, private var activity: MainActivity) : AsyncTask<Void, Void, String>() {


        override fun onPreExecute() {
            super.onPreExecute()
            m_progress = ProgressDialog.show(context, "connecting...", "please wait")

        }

        override fun doInBackground(vararg p0: Void?): String? {
            if (m_bluetoothSocket == null || !m_isConnected) {
                val device: BluetoothDevice = m_bluetoothAdapter!!.getRemoteDevice(m_address)
                m_bluetoothSocket = device.createInsecureRfcommSocketToServiceRecord(m_myUUID)
                m_bluetoothAdapter!!.cancelDiscovery()

                //keep connecting BT
                while(true){
                    try{
                        Log.d(BT_TAG,"reconnect ! ")
                        m_bluetoothSocket!!.connect()

                        if(m_bluetoothSocket!!.isConnected){
                            m_isConnected = true
                            break
                        }
                    }catch (e: IOException) {
                        Log.d(BT_TAG,"catch IOE ! ")
                    }

                }

            }
            return null
        }

        //connect successfully
        override fun onPostExecute(result: String?) {
            super.onPostExecute(result)

            Log.d(BT_TAG,"onPostExecute ! ")
            m_progress.dismiss()
            Toast.makeText(context,"connected", Toast.LENGTH_SHORT).show()
            val cal = Calendar.getInstance()
            val dateReturn = '?'+SimpleDateFormat("yyyy:MM:dd:HH:mm:ss").format(cal.time)
            activity.sendData(dateReturn)

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
                            Log.d(BT_TAG, "init_BTget:$bufToString")


                            val message = Message.obtain()
                            if (bufToString == "=") {
                                message.what = 2
                                initHandler.sendMessage(message)
                                break
                            }
                            else if (bufToString == "E") {
                                message.what = 3
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

    private fun getLocation(context: Context) {


        //request permission
        if (ActivityCompat.checkSelfPermission(this@MainActivity, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(
                this,
                arrayOf(Manifest.permission.ACCESS_FINE_LOCATION),
                REQUEST_GPS)

        }
        else{
            val locationManager = getSystemService(Context.LOCATION_SERVICE) as LocationManager
            val hasGps = locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER)

            val database: FirebaseDatabase = FirebaseDatabase.getInstance()
            val myRef: DatabaseReference = database.getReference("autobrake")


            if (hasGps) {
                Log.d(GPS_TAG, "hasGps")
                locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 5000, 0F, object : LocationListener {

                    @SuppressLint("SimpleDateFormat")
                    override fun onLocationChanged(location: Location?) {
                        Log.d(GPS_TAG, "changed")
                        if (location != null) {
                            val latitude = location.latitude
                            val longitude = location.longitude

                            Log.d(GPS_TAG, "GPS Latitude : $latitude")
                            Log.d(GPS_TAG, "GPS Longitude : $longitude")

                            val cal = Calendar.getInstance()
                            val date = SimpleDateFormat("yyyy/MM/dd HH:mm:ss").format(cal.time)


                            //to firebase
                            myRef.child("lat").setValue(latitude.toString())
                            myRef.child("lon").setValue(longitude.toString())
                            myRef.child("date").setValue(date)



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
                if (localGpsLocation != null) {
                    Log.d(GPS_TAG, " End GPS Latitude : " + localGpsLocation.latitude)
                    Log.d(GPS_TAG, " End GPS Longitude : " + localGpsLocation.longitude)

                    val cal = Calendar.getInstance()
                    val date = SimpleDateFormat("yyyy/MM/dd HH:mm:ss").format(cal.time)

                    myRef.child("lat").setValue(localGpsLocation.latitude.toString())
                    myRef.child("lon").setValue(localGpsLocation.longitude.toString())
                    myRef.child("date").setValue(date)

                }

            }
        }

    }

    private fun firebase() {
        val database: FirebaseDatabase = FirebaseDatabase.getInstance()
        val myRef: DatabaseReference = database.getReference("autobrake")


        myRef.addValueEventListener(object : ValueEventListener {
            override fun onDataChange(dataSnapshot: DataSnapshot) {

                var note = dataSnapshot.child("note").value
                note_txt.text = note.toString()

                var number = dataSnapshot.child("callNumber").value
                callNumber = number.toString()
            }

            override fun onCancelled(error: DatabaseError) {}
        })
    }

    //request permission
    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<String>, grantResults: IntArray) {
        when (requestCode) {
            REQUEST_CALL -> {
                // If request is cancelled, the result arrays are empty.
                if ((grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED)) {

                }
            }

            REQUEST_GPS -> {
                if ((grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED)) {
                    getLocation(this)
                }
            }
        }
    }


    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (requestCode == REQUEST_BT) {
            if (resultCode == Activity.RESULT_OK) {
                if (m_bluetoothAdapter!!.isEnabled) {
                    ConnectToDevice(this,this).execute()
                } else {
                    Toast.makeText(this,"Bluetooth has been disabled", Toast.LENGTH_SHORT).show()
                }
            } else if (resultCode == Activity.RESULT_CANCELED) {
                Toast.makeText(this,"Bluetooth enabling has been canceled", Toast.LENGTH_SHORT).show()
            }
        }
    }

    //second check when exit
    private var lastTime: Long = 0
    override fun finish() {
        Log.d("flow", "finish")
        val currentTime = System.currentTimeMillis()

        if(currentTime - lastTime > 3 * 1000) {
            lastTime = currentTime
            Toast.makeText(this, "\t\t再次按下離開\n請確認車體電源已關閉", Toast.LENGTH_SHORT).show()
        } else {
            super.finish()
        }
    }


}