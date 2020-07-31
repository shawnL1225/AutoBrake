package com.msba.autobrakefamily

import android.content.Context
import android.content.Intent
import android.os.Bundle
import android.text.Html
import com.google.android.material.bottomnavigation.BottomNavigationView
import androidx.appcompat.app.AppCompatActivity
import androidx.navigation.findNavController
import androidx.navigation.ui.AppBarConfiguration
import androidx.navigation.ui.setupActionBarWithNavController
import androidx.navigation.ui.setupWithNavController

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
//        supportActionBar!!.title = Html.fromHtml("<font color = \"black\">AutoBrake_Family</font>")

        supportActionBar!!.setDisplayShowHomeEnabled(true);
        supportActionBar!!.setIcon(R.mipmap.ic_launcher_foreground_black);
        setContentView(R.layout.activity_main)

        val navView: BottomNavigationView = findViewById(R.id.nav_view)

        val navController = findNavController(R.id.nav_host_fragment)
        // Passing each menu ID as a set of Ids because each
        // menu should be considered as top level destinations.
        val appBarConfiguration = AppBarConfiguration(setOf(
                R.id.navigation_home, R.id.navigation_map, R.id.navigation_chart, R.id.navigation_setting))
        setupActionBarWithNavController(navController, appBarConfiguration)
        navView.setupWithNavController(navController)

        val intent = Intent(this, NotificationService::class.java)
        startService(intent)
    }
}