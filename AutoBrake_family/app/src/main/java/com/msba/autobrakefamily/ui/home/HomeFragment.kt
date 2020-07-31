package com.msba.autobrakefamily.ui.home

import android.graphics.Color
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.*
import androidx.fragment.app.Fragment
import com.google.firebase.database.*
import com.msba.autobrakefamily.R

class HomeFragment : Fragment() {

    override fun onCreateView(
            inflater: LayoutInflater,
            container: ViewGroup?,
            savedInstanceState: Bundle?
    ): View? {

        var database = FirebaseDatabase.getInstance().reference
        val root = inflater.inflate(R.layout.fragment_home, container, false)
        var battery: TextView = root.findViewById(R.id.val_battery)
        var temp: TextView = root.findViewById(R.id.val_temp)
        var speed: TextView = root.findViewById(R.id.val_speed)

        val imgBattery : ImageView = root.findViewById(R.id.img_battery)

        val bBar: ProgressBar  = root.findViewById(R.id.battery_Bar)
        val tBar: ProgressBar = root.findViewById(R.id.temp_Bar)
        val sBar: ProgressBar = root.findViewById(R.id.speed_Bar)

        val bUnit: TextView  = root.findViewById(R.id.unit_battery)
        val tUnit: TextView = root.findViewById(R.id.unit_temp)
        val sUnit: TextView = root.findViewById(R.id.unit_speed)



        bUnit.visibility=View.INVISIBLE
        tUnit.visibility=View.INVISIBLE
        sUnit.visibility=View.INVISIBLE

        //getdata
        var getData = object : ValueEventListener{
            override fun onCancelled(p0: DatabaseError) {
            }

            override fun onDataChange(p0: DataSnapshot) {
                val valBattery :Int = p0.child("autobrake/battery").getValue(Int::class.java) as Int
                val valTemp :Int = p0.child("autobrake/temp").getValue(Int::class.java) as Int
                val valSpeed :Int = p0.child("autobrake/speed").getValue(Int::class.java) as Int
                //battery

                when (valBattery){
                    -7626 -> {
                        battery.textSize = 30f
                        battery.text = "裝置\n未連線"
                        imgBattery.setImageResource(R.drawable.battery_disconnected)
                        bBar.visibility=View.VISIBLE
                        bUnit.visibility=View.INVISIBLE
                    }
                    in 0..20 -> {
                        battery.textSize = 75f
                        battery.text = "${valBattery}"
                        battery.setTextColor(Color.parseColor("#F44336"))
                        imgBattery.setImageResource(R.drawable.battery_1)
                        bBar.visibility=View.GONE
                        bUnit.visibility=View.VISIBLE
                    }
                    in 21..40 -> {
                        battery.textSize = 75f
                        battery.text = "${valBattery}"
                        battery.setTextColor(Color.parseColor("#FF9800"))
                        imgBattery.setImageResource(R.drawable.battery_2)
                        bBar.visibility=View.GONE
                        bUnit.visibility=View.VISIBLE
                    }
                    in 41..60 -> {
                        battery.textSize = 75f
                        battery.text = "${valBattery}"
                        battery.setTextColor(Color.parseColor("#4CAF50"))
                        imgBattery.setImageResource(R.drawable.battery_3)
                        bBar.visibility=View.GONE
                        bUnit.visibility=View.VISIBLE
                    }
                    in 61..80 -> {
                        battery.textSize = 75f
                        battery.text = "${valBattery}"
                        battery.setTextColor(Color.parseColor("#4CAF50"))
                        imgBattery.setImageResource(R.drawable.battery_4)
                        bBar.visibility=View.GONE
                        bUnit.visibility=View.VISIBLE
                    }
                    in 81..100 -> {
                        battery.textSize = 75f
                        battery.text = "${valBattery}"
                        battery.setTextColor(Color.parseColor("#4CAF50"))
                        imgBattery.setImageResource(R.drawable.battery_5)
                        bBar.visibility=View.GONE
                        bUnit.visibility=View.VISIBLE
                    }
                }
                //Temp
                when(valTemp){
                    -7626 -> {
                        temp.textSize = 30f
                        temp.text = "裝置未連線"
                        tBar.visibility=View.VISIBLE
                        tUnit.visibility=View.INVISIBLE
                    }
                    else ->{
                        temp.textSize = 90f
                        temp.text = "${valTemp}"
                        tBar.visibility=View.GONE
                        tUnit.visibility=View.VISIBLE
                    }
                }

                //speed

                when(valSpeed){
                    -7626 -> {
                        speed.textSize = 30f
                        speed.text = "裝置未連線"
                        sBar.visibility=View.VISIBLE
                        sUnit.visibility=View.INVISIBLE
                    }
                    else ->{
                        speed.textSize = 90f
                        speed.text = "${valSpeed}"
                        sBar.visibility=View.GONE
                        sUnit.visibility=View.VISIBLE
                    }
                }


            }
        }
        database.addValueEventListener(getData)



        return root


    }
}