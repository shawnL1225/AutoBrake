package com.msba.autobrakefamily

import android.app.Notification
import android.app.NotificationManager
import android.app.Service
import android.content.Context
import android.content.Intent
import android.location.Location
import android.os.IBinder
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
        var error:String = ""




        val BatteryLow = NotificationCompat.Builder(applicationContext,"channel id test")
            .setSmallIcon(R.drawable.ic_baseline_report_problem_24)
            .setContentTitle("警告，發生危險")
            .setContentText("電量過低，請盡速充電")
            .build()

        val TiltWarning = NotificationCompat.Builder(applicationContext,"channel id test")
            .setSmallIcon(R.drawable.ic_baseline_report_problem_24)
            .setContentTitle("警告，發生危險")
            .setContentText("車體傾斜，發生地點")
            .setDefaults(Notification.DEFAULT_ALL)
            .setAutoCancel(true)
            .build()

        val notificationManager = getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager

        fun getTime():String{
            var now :Date = Date()
            return SimpleDateFormat("M/dd HH:mm",  Locale.getDefault()).format(now)
        }

        fun createID():Int{
            var now :Date = Date()
            var id : Int = Integer.parseInt(SimpleDateFormat("ddHHmmss",  Locale.TAIWAN).format(now))
            return id
        }



        var Approach : Notification = NotificationCompat.Builder(applicationContext,"approach").build()
        fun getPlace(placename:String ,time:String){
            Approach = NotificationCompat.Builder(applicationContext,"approach")
                .setSmallIcon(R.drawable.ic_baseline_location_24)
                .setContentTitle("靠近設定點「${placename}」")
                .setContentText("長輩於${time}時間出現於\"${placename}\"附近")
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
                error = p0.child("error").getValue() as String

                if(p0.child("lat").exists()){
                    lat = p0.child("lat").getValue() as String
                    lon = p0.child("lon").getValue() as String
                }
                if(p0.exists()){for(e in p0.child("setLocation").children){
                    val placeString = e.value.toString()
                    list.add(placeString)
                }}
                val len = list.count()

                for (i in 0..len-1){
                    val loc1 = Location("here")
                    loc1.latitude = lat.toDouble()
                    loc1.longitude = lon.toDouble()

                    var listString : String = list[i]
                    val placeName = listString.substring(0,listString.indexOf(':'))

                    val loc2 = Location("set")
                    loc2.latitude = listString.substring(listString.indexOf(":")+1,listString.indexOf(",")).toDouble()
                    loc2.longitude = listString.substring(listString.indexOf(",")+1,listString.length).toDouble()

                    distanceInMeters = loc1.distanceTo(loc2)
                    if (distanceInMeters < 50f) {
                        getPlace(placeName, getTime())
                        if (notifyBuffer[i] == false){
                            notificationManager.notify(i, Approach)
                            notifyBuffer[i] = true
                            Log.d("test: ", placeName)
                        }
                    }
                    else{
                        notifyBuffer[i] = false
                    }
                }
            }
        })

        val runnable = Runnable {
            while (true) {
                when (error) {
                    "1" -> {
                        notificationManager.notify(createID(), TiltWarning)
                        Thread.sleep(30000)
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
