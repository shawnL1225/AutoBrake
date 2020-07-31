package com.msba.autobrakefamily

import android.app.*
import android.content.Context
import android.content.Intent
import android.media.RingtoneManager
import android.net.Uri
import android.os.IBinder
import android.util.Log
import androidx.core.app.NotificationCompat
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.database.ValueEventListener
import java.text.SimpleDateFormat
import java.util.*


class NotificationService : Service(){
    val TAG = "Notification"

    var database = FirebaseDatabase.getInstance().reference

    var valBattery : Int = -7626

    override fun onBind(intent: Intent): IBinder? {
        return null
    }

    override fun onCreate() {
        ShowLog("OnCreate")
        super.onCreate()
        val BatteryLow = NotificationCompat.Builder(this,"channel id test")
            .setSmallIcon(R.drawable.ic_baseline_report_problem_24)
            .setContentTitle("警告，發生危險")
            .setContentText("電量過低，請盡速充電")
            .build()

        val TiltWarning = NotificationCompat.Builder(this,"channel id test")
            .setSmallIcon(R.drawable.ic_baseline_report_problem_24)
            .setContentTitle("警告，發生危險")
            .setContentText("車體傾斜，發生地點")
            .setDefaults(Notification.DEFAULT_ALL)
            .setAutoCancel(true)
            .build()

        val notificationManager = getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager
        var getdata = object :ValueEventListener{
            override fun onDataChange(p0: DataSnapshot) {
                var error = p0.child("autobrake/error").getValue() as String
                var cal = Calendar.getInstance()
                val timeSetListener = TimePickerDialog.OnTimeSetListener{ view, hour, minute ->

                    cal.set(Calendar.HOUR, hour)
                    cal.set(Calendar.MINUTE, minute)

                    val time = SimpleDateFormat("yyyy-M-DD HH:mm", Locale.TAIWAN)
                }
                fun createID():Int{
                    var now :Date = Date()
                    var id : Int = Integer.parseInt(SimpleDateFormat("ddHHmmss",  Locale.TAIWAN).format(now))
                    return id
                }

                when(error){
                    "1" -> {
                        notificationManager.notify(createID(), TiltWarning)
                        try {
                            val notification: Uri =
                                RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION)
                            val r =
                                RingtoneManager.getRingtone(applicationContext, notification)
                            r.play()
                        } catch (e: Exception) {
                            e.printStackTrace()
                        }
                    }
                }
            }
            override fun onCancelled(p0: DatabaseError) {
            }
        }
        database.addValueEventListener(getdata)
    }

    override fun onStartCommand(intent: Intent?, flags: Int, startId: Int): Int {
        ShowLog("onStartCommand")
        return super.onStartCommand(intent, flags, startId)
    }

    fun ShowLog(message: String){
        Log.d(TAG,message)
    }
}
