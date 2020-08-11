package com.msba.autobrakefamily

import android.app.Notification
import android.app.NotificationChannel
import android.app.NotificationManager
import android.app.Service
import android.content.Context
import android.content.Intent
import android.location.Location
import android.os.Build
import android.os.IBinder
import android.os.VibrationEffect
import android.os.Vibrator
import android.provider.Settings
import android.util.Log
import androidx.core.app.NotificationCompat
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.database.ValueEventListener
import java.text.SimpleDateFormat
import java.util.*
import kotlin.collections.ArrayList


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



    }

    override fun onStartCommand(intent: Intent?, flags: Int, startId: Int): Int {
        ShowLog("onStartCommand")
        var error = ""


        val vibrator = getSystemService(Context.VIBRATOR_SERVICE) as Vibrator

        val batteryLow = NotificationCompat.Builder(applicationContext,"AutoBrake")
            .setSmallIcon(R.drawable.ic_baseline_report_problem_24)
            .setContentTitle("警告，發生危險")
            .setContentText("電量過低，請盡速充電")
            .setAutoCancel(true)
            .setSound(Settings.System.DEFAULT_NOTIFICATION_URI)
            .build()

        val tiltWarning = NotificationCompat.Builder(applicationContext,"AutoBrake")
            .setSmallIcon(R.drawable.ic_baseline_report_problem_24)
            .setContentTitle("警告，發生危險")
            .setContentText("車體傾斜，發生地點")
            .setAutoCancel(true)
            .build()

        var locationApproach : Notification = NotificationCompat.Builder(applicationContext,"AutoBrake").build()



        val notificationManager = getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager
         if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            val channel = NotificationChannel("AutoBrake", "AutoBrake", NotificationManager.IMPORTANCE_DEFAULT)
             channel.enableVibration(true)
             channel.setSound(null,null)


            notificationManager.createNotificationChannel(channel)
        }


        fun getTime():String{
            var now = Date()
            return SimpleDateFormat("M/dd HH:mm",  Locale.getDefault()).format(now)
        }



        fun setNotificationPlace(placeName:String, time:String){
            locationApproach = NotificationCompat.Builder(applicationContext,"AutoBrake")
                .setSmallIcon(R.drawable.ic_baseline_location_24)
                .setContentTitle("靠近設定點「${placeName}」")
                .setContentText("長輩於${time}時間出現於\"${placeName}\"附近")
                .build()
        }
        val list = ArrayList<String>()
        var distanceInMeters = 5000f
        var notifyBuffer = BooleanArray(30){false}

        val listRef = FirebaseDatabase.getInstance().reference.child("autobrake")
        listRef.addValueEventListener(object : ValueEventListener {
            var lat: String = ""
            var lon: String = ""
            override fun onCancelled(p0: DatabaseError) {
            }

            override fun onDataChange(p0: DataSnapshot) {
                list.clear()
                error = p0.child("error").value as String

                if(p0.child("lat").exists()){
                    lat = p0.child("lat").value as String
                    lon = p0.child("lon").value as String
                }
                if(p0.exists()){for(e in p0.child("setLocation").children){
                    val placeString = e.value.toString()
                    list.add(placeString)
                }}
                val len = list.count()

                for (i in 0 until len){
                    val loc1 = Location("here")
                    loc1.latitude = lat.toDouble()
                    loc1.longitude = lon.toDouble()

                    var listString : String = list[i]
                    val placeName = listString.substring(0,listString.indexOf(':'))

                    val loc2 = Location("set")
                    loc2.latitude = listString.substring(listString.indexOf(":")+1,listString.indexOf(",")).toDouble()
                    loc2.longitude = listString.substring(listString.indexOf(",")+1,listString.length).toDouble()

                    // approach notification
                    distanceInMeters = loc1.distanceTo(loc2)
                    if (distanceInMeters < 50f) {
                        setNotificationPlace(placeName, getTime())

                        if (!notifyBuffer[i]){
                            notificationManager.notify(i, locationApproach)
                            notifyBuffer[i] = true
                            if (vibrator.hasVibrator()) {
                                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                                    vibrator.vibrate(
                                        VibrationEffect.createOneShot(500, VibrationEffect.DEFAULT_AMPLITUDE)
                                    )
                                } else {
                                    vibrator.vibrate(1000)
                                }
                            }

                        }
                    }
                    else{
                        notifyBuffer[i] = false
                    }
                }
            }
        })

        var timeList = LongArray(2).toMutableList()
        val runnable = Runnable {
            while (true) {
                for(e in error){
                    when (e) {
                        '1' -> {
                            val now = System.currentTimeMillis()

                            if(now - timeList[0] > 30000){
                                notificationManager.notify(now.toInt() , tiltWarning)
                                if (vibrator.hasVibrator()) {
                                    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                                        vibrator.vibrate(
                                            VibrationEffect.createOneShot(500, VibrationEffect.DEFAULT_AMPLITUDE)
                                        )
                                    } else {
                                        vibrator.vibrate(500)
                                    }
                                }
                                timeList[0] = now
                                Thread.sleep(1000)
                            }
                            

                        }
                        '2' -> {
                            val now = System.currentTimeMillis()
                            if(now - timeList[1] > 30000) {
                                notificationManager.notify(now.toInt(), batteryLow)
                                if (vibrator.hasVibrator()) {
                                    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                                        vibrator.vibrate(
                                            VibrationEffect.createOneShot(
                                                500,
                                                VibrationEffect.DEFAULT_AMPLITUDE
                                            )
                                        )
                                    } else {
                                        vibrator.vibrate(500)
                                    }
                                }
                                timeList[1] = now
                                Thread.sleep(1000)
                            }

                        }
                    }
                }


            }
        }
        val thread = Thread(runnable)
        thread.start()

        return super.onStartCommand(intent, flags, startId)
    }

    override fun onDestroy() {
        ShowLog("OnDestroy")
        super.onDestroy()
    }

    fun ShowLog(message: String){
        Log.d(TAG,message)
    }
}
