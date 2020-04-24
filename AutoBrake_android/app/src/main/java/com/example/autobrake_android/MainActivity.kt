package com.example.autobrake_android

import android.annotation.SuppressLint
import android.app.ProgressDialog
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothSocket
import android.content.Context
import android.os.*
import android.util.Log
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
        var m_bluetoothSocket: BluetoothSocket? = null
        lateinit var m_progress: ProgressDialog
        lateinit var m_bluetoothAdapter: BluetoothAdapter
        var m_isConnected: Boolean = false
        lateinit var m_address: String

        const val TAG = "BLUETOOTH DEBUG"


        val mmBuffer: ByteArray = ByteArray(1024)
        var numBytes: Int = 0


    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        //set BT address
        m_address = "98:D3:31:FC:20:72"
        ConnectToDevice(this).execute()

        //connect stuff
        reconnect_btn.setOnClickListener { ConnectToDevice(this).execute() }
        disconnect_btn.setOnClickListener { disconnect() }

        //show BT receiveThread value
        start_recieve_btn.setOnClickListener {
            val handler = @SuppressLint("HandlerLeak") object: Handler() {
                override fun handleMessage(msg: Message) {
                    if(msg.what==1)
                    {
                        var b: ByteArray = mmBuffer.copyOf(numBytes)
                        val bufToString =  b.toString(Charsets.UTF_8)
                        Log.d(TAG, bufToString)
                        val part = bufToString.split('|')
                        speed_txt.text =  part[0]
                        bettery_txt.text = part[1]+'%'

                        if(part[2].toInt()>0) {
                            //Log.d(TAG, "part 2 = true")
                            warning_img.visibility = View.VISIBLE
                        }
                        else
                        {
                            //Log.d(TAG, "part 2 = false")
                            warning_img.visibility = View.INVISIBLE
                        }




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

    //BT Receive Data
    class ReceiveThread(val handler: Handler) : Thread() {
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
                        message.what = 1
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

    private fun disconnect() {
        if (m_bluetoothSocket != null) {
            try {
                m_bluetoothSocket!!.close()
                m_bluetoothSocket = null
                m_isConnected = false
            } catch (e: IOException) {
                e.printStackTrace()
            }
        }
    }

    private class ConnectToDevice(c: Context) : AsyncTask<Void, Void, String>() {
        private var connectSuccess: Boolean = true
        private val context: Context = c

        override fun onPreExecute() {
            super.onPreExecute()
            m_progress = ProgressDialog.show(context, "Connecting...", "please wait")
        }

        override fun doInBackground(vararg p0: Void?): String? {
            try {
                if (m_bluetoothSocket == null || !m_isConnected) {
                    m_bluetoothAdapter = BluetoothAdapter.getDefaultAdapter()
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
                Toast.makeText(context,"was connected", Toast.LENGTH_SHORT).show()


            }
            m_progress.dismiss()

        }
    }

}