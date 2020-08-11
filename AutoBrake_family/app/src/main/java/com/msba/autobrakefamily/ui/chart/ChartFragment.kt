package com.msba.autobrakefamily.ui.chart

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.webkit.WebView
import androidx.fragment.app.Fragment
import com.msba.autobrakefamily.R

class ChartFragment : Fragment() {


    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {

        val root = inflater.inflate(R.layout.fragment_chart, container, false)

        val batteryChart : WebView = root.findViewById(R.id.battery_web)
        batteryChart.settings.javaScriptEnabled = true
        val tempChart : WebView = root.findViewById(R.id.temp_web)
        tempChart.settings.javaScriptEnabled = true
        val speedChart : WebView = root.findViewById(R.id.speed_web)
        speedChart.settings.javaScriptEnabled = true
        val rpmChart : WebView = root.findViewById(R.id.rpm_web)
        rpmChart.settings.javaScriptEnabled = true


        batteryChart.loadUrl("https://thingspeak.com/channels/1087756/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=%E9%9B%BB%E6%B1%A0%E9%9B%BB%E9%87%8F%E7%B5%B1%E8%A8%88&type=line")
        tempChart.loadUrl("https://thingspeak.com/channels/1087756/charts/3?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=%E9%A6%AC%E9%81%94%E6%BA%AB%E5%BA%A6%E7%B5%B1%E8%A8%88&type=line")
        speedChart.loadUrl("https://thingspeak.com/channels/1087756/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=%E8%BB%8A%E9%80%9F%E7%B5%B1%E8%A8%88&type=line")
        rpmChart.loadUrl("https://thingspeak.com/channels/1087756/charts/4?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=%E9%A6%AC%E9%81%94%E8%B2%A0%E8%BC%89%E7%B5%B1%E8%A8%88&type=line")


        return root
    }
}