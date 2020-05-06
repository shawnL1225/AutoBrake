package com.example.autobrake_android

import android.annotation.SuppressLint
import android.app.ProgressDialog
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothSocket
import android.content.Context
import android.content.Intent
import android.os.*
import android.speech.tts.TextToSpeech
import android.util.Log
import android.view.MotionEvent
import android.view.View
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*
import java.io.IOException
import java.text.SimpleDateFormat
import java.util.*

class MainActivity: AppCompatActivity() {

    companion object {
        var m_myUUID: UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB")
        private val BLUETOOTH_SEND_STRING = 1
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

        //onTouch
        var x1 =0F
        var x2 =0F
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        supportActionBar!!.setDisplayShowHomeEnabled(true);
        supportActionBar!!.setIcon(R.mipmap.ic_launcher_foreground);
        setContentView(R.layout.activity_main)

        myLayout.alpha = 0.3F

        //speech init
        mTTS = TextToSpeech(applicationContext, TextToSpeech.OnInitListener { status ->
            if(status != TextToSpeech.ERROR)
                mTTS.language = Locale.ENGLISH
        })


        //set BT address then connect to BT
        m_address = "98:D3:31:FC:20:72"
        ConnectToDevice(this).execute()


        //connect stuff
        reconnect_btn.setOnClickListener { ConnectToDevice(this).execute() }
        disconnect_btn.setOnClickListener { disconnect(this) }

        //show BT receiveThread value
        start_receive_btn.setOnClickListener {
            val vibrator = getSystemService(Context.VIBRATOR_SERVICE) as Vibrator
            myLayout.alpha = 1F
            var isSpeaking = false


            
            val handler = @SuppressLint("HandlerLeak") object: Handler() {
                override fun handleMessage(msg: Message) {
                    if(msg.what==BLUETOOTH_SEND_STRING)
                    {
                        var b: ByteArray = mmBuffer.copyOf(numBytes)
                        val bufToString =  b.toString(Charsets.UTF_8)
                        Log.d(BT_TAG, bufToString)

                        val part = bufToString.split('|')
                        var speed = part[0].toInt()
                        var battery = part[1]
                        var warning_main = part[2].toInt()
                        var warnning_left = part[3].toInt()
                        var warning_right = part[4].toInt()


                        //set speed and progress bar
                        if (speed > 30) speed = 30
                        speed_txt.text =  speed.toString()
                        progress_circular.max = 40
                        progress_circular.setProgress(speed, true)


                        if(warning_main>0 || warnning_left>0 || warning_right>0)
                        {
                            warning_img.visibility = View.VISIBLE
                            progress_circular.setProgress(0,true)

                            if (vibrator.hasVibrator()) {
                                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                                    vibrator.vibrate(VibrationEffect.createOneShot(200, VibrationEffect.DEFAULT_AMPLITUDE))
                                } else {
                                    vibrator.vibrate(200)
                                }
                            }

                            if(!isSpeaking)
                            {
                                if(warning_main>0)
                                    mTTS.speak("watch out!start braking system", TextToSpeech.QUEUE_FLUSH, null)
                                else if(warnning_left>0)
                                    mTTS.speak("Be careful of left side", TextToSpeech.QUEUE_FLUSH, null)
                                else
                                    mTTS.speak("Be careful of right side", TextToSpeech.QUEUE_FLUSH, null)

                                isSpeaking = true

                            }
                        }
                        else
                        {
                            warning_img.visibility = View.INVISIBLE
                            isSpeaking = false
                        }
                        //set battery
                        battery_txt.text = battery+'%'
                    }
                }
            }
            val thread = ReceiveThread(handler)
            thread.start()
        }

        //current time
        object: CountDownTimer(86400000, 1000) {
            @SuppressLint("SetTextI18n")
            override fun onFinish() {
                time_txt.text = "ride over 24H ?"
            }
            @SuppressLint("SimpleDateFormat")
            override fun onTick(millisUntilFinished: Long) {
                val cal = Calendar.getInstance()
                time_txt.text = SimpleDateFormat("HH:mm:ss").format(cal.time)
            }

        }.start()
    }

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
            //super.run()

            Log.d(BT_TAG, "START RUN")
            var available = 0
            while (true) {
                try {
                    available = m_bluetoothSocket!!.inputStream.available()
                    if(available>0) {
                        //wait for read
                        Thread.sleep(150)
                        numBytes = m_bluetoothSocket!!.inputStream.read(mmBuffer, 0, 500)

                        //debug show the num and value of BT
                        Log.d(BT_TAG, "numBytes :  " +numBytes)
                        for(x in 0..numBytes-1)
                        {
                            Log.d(BT_TAG, "buffer :  " + mmBuffer[x])
                        }

                        //return msg to UI
                        val message = Message.obtain()
                        message.what = BLUETOOTH_SEND_STRING
                        handler.sendMessage(message)
                        Log.d(BT_TAG, "--------------------------")
                    }
                } catch (e: IOException) {
                    Log.d(BT_TAG, "BT Input stream was disconnected", e)
                }
            }

        }
    }

    // BT send data
    private fun sendData(input: String) {
        if (m_bluetoothSocket != null) {
            try{
                Toast.makeText(this,"write successfully", Toast.LENGTH_SHORT).show()
                m_bluetoothSocket!!.outputStream.write(input.toByteArray())
            } catch(e: IOException) {
                e.printStackTrace()
                Toast.makeText(this,"write got wrong: "+e.message, Toast.LENGTH_SHORT).show()
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
            } catch (e: IOException) {
                e.printStackTrace()
            }
        }
    }

    //BT connect
    private class ConnectToDevice(var context: Context) : AsyncTask<Void, Void, String>() {
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

        override fun onPostExecute(result: String?) {
            super.onPostExecute(result)
            if (!connectSuccess) {
                Toast.makeText(context,"couldn't connect", Toast.LENGTH_SHORT).show()
            } else {
                m_isConnected = true
                Toast.makeText(context,"connected", Toast.LENGTH_SHORT).show()
            }
            m_progress.dismiss()

        }
    }

}