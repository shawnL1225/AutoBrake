package com.example.autobrake_android

import android.annotation.SuppressLint
import android.app.ProgressDialog
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothSocket
import android.content.Context
import android.os.*
import android.util.Log
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*
import java.io.IOException
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
        const val TAG2 = "TAG2"
        const val MESSAGE_READ: Int = 0


    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        m_address = "98:D3:31:FC:20:72"
        ConnectToDevice(this).execute()

        reconnect_btn.setOnClickListener {
            ConnectToDevice(this).execute()
        }
        disconnect_btn.setOnClickListener { disconnect() }
        start_recieve_btn.setOnClickListener {
            val handler = @SuppressLint("HandlerLeak") object: Handler() {
                override fun handleMessage(msg: Message) {
                    speed_txt.text = msg.what.toString()
                }
            }
            val Rthread = ReceiveThread(handler)
            Rthread.start()
        }




    }

    //BT Receive Data
    class ReceiveThread(handler: Handler) : Thread() {
        val handler: Handler = handler
        override fun run() {
            //super.run()
            val mmBuffer: ByteArray = ByteArray(1024)
            var numBytes: Int = 0
            var total: Int = 0
            var available = m_bluetoothSocket!!.inputStream.available()
            Log.d(TAG, "START RUN")

            while (true) {

                try {
                    available =  m_bluetoothSocket!!.inputStream.available()
                    if(available==0) {
                        Thread.sleep(15)
                        available =  m_bluetoothSocket!!.inputStream.available()
                        if(available==0) {
                            val message = Message.obtain()
                            message.what = total
                            handler.sendMessage(message)
                            Log.d(TAG, "Return :  " + total)
                            total = 0
                        }
                    }
                    numBytes = m_bluetoothSocket!!.inputStream.read(mmBuffer, 0, 500)

                } catch (e: IOException) {
                    Log.d(TAG, "Input stream was disconnected", e)
                }
                total+=numBytes
                Log.d(TAG2, "Return :  " + total)
            }

        }
    }

    private fun sendCommand(input: String) {


        if (m_bluetoothSocket != null) {
            try{

                Toast.makeText(this,"writen", Toast.LENGTH_SHORT).show()
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
        private val context: Context

        init {
            this.context = c
        }

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