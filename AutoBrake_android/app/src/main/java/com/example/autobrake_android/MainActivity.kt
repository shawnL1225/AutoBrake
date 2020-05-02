package com.example.autobrake_android

import android.annotation.SuppressLint
import android.app.ProgressDialog
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothSocket
import android.content.Context
import android.content.Intent
import android.graphics.Color
import android.graphics.PorterDuff
import android.graphics.drawable.Drawable
import android.os.*
import android.util.Log
import android.view.MotionEvent
import android.view.View
import android.view.WindowManager
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.app.ActivityCompat.startActivityForResult
import androidx.core.content.ContextCompat
import kotlinx.android.synthetic.main.activity_main.*
import java.io.IOException
import java.text.SimpleDateFormat
import java.util.*
import com.example.autobrake_android.MapsActivity.Companion

class MainActivity: AppCompatActivity() {

    companion object {
        var m_myUUID: UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB")
        private val BLUETOOTH_SEND_STRING = 1
        var m_bluetoothSocket: BluetoothSocket? = null
        lateinit var m_progress: ProgressDialog
        var m_bluetoothAdapter = BluetoothAdapter.getDefaultAdapter()
        var m_isConnected: Boolean = false
        lateinit var m_address: String

        const val TAG = "BLUETOOTH DEBUG"

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

//        Handler().postDelayed({
//            //start main activity
//            startActivity(Intent(this, MapsActivity::class.java))
//            //finish this activity
//            finish()
//        },10000)


        //set BT address
        m_address = "98:D3:31:FC:20:72"
        ConnectToDevice(this).execute()


        //connect stuff
        reconnect_btn.setOnClickListener { ConnectToDevice(this).execute() }
        disconnect_btn.setOnClickListener { disconnect(this) }

        //show BT receiveThread value
        start_receive_btn.setOnClickListener {
            val handler = @SuppressLint("HandlerLeak") object: Handler() {
                override fun handleMessage(msg: Message) {
                    if(msg.what==BLUETOOTH_SEND_STRING)
                    {
                        var b: ByteArray = mmBuffer.copyOf(numBytes)
                        val bufToString =  b.toString(Charsets.UTF_8)
                        Log.d(TAG, bufToString)
                        //[0]:speed, [1]:battery, [2]warning
                        val part = bufToString.split('|')
                        speed_txt.text =  part[0]
                        progress_circular.max = 25
                        progress_circular.setProgress(part[0].toInt(),true)

                        if(part[1].toInt()>0)
                        {
                            //Log.d(TAG, "part 2 = true")
                            warning_img.visibility = View.VISIBLE
                            progress_circular.setProgress(0,true)
                        }
                        else
                        {
                            //Log.d(TAG, "part 2 = false")
                            warning_img.visibility = View.INVISIBLE
                        }
                        battery_txt.text = part[2]+'%'
                    }
                }
            }
            val thread = ReceiveThread(handler)
            thread.start()
        }

        //current time
        object: CountDownTimer(86400000, 1000) {
            override fun onFinish() {
                time_txt.text = "ride over 24H ?"
            }
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
                Log.d("MY-touch", "DOWN!!!$x1")
            }
            MotionEvent.ACTION_UP -> {
                x2 = e.getX()
                Log.d("MY-touch", "UP!!!$x2")
                isTouched = true
            }
        }
        if(x1 > x2 && isTouched)
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

            Log.d(TAG, "START RUN")
            var available = 0
            while (true) {
                try {
                    available = m_bluetoothSocket!!.inputStream.available()
                    if(available>0) {
                        //wait then read
                        Thread.sleep(80)
                        numBytes = m_bluetoothSocket!!.inputStream.read(mmBuffer, 0, 500)

                        //debug show what BT got
                        Log.d(TAG, "numBytes :  " +numBytes)
                        for(x in 0..numBytes-1)
                        {
                            Log.d(TAG, "buffer :  " + mmBuffer[x])
                        }

                        //return msg to UI
                        val message = Message.obtain()
                        message.what = BLUETOOTH_SEND_STRING
                        handler.sendMessage(message)
                        Log.d(TAG, "--------------------------")
                    }
                } catch (e: IOException) {
                    Log.d(TAG, "Input stream was disconnected", e)
                }
            }

        }
    }

    private fun sendCommand(input: String) {


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