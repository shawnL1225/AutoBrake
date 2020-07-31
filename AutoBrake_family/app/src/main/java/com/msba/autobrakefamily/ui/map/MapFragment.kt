package com.msba.autobrakefamily.ui.map

import android.content.ContentValues
import android.graphics.Color
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.fragment.app.Fragment
import com.google.android.gms.maps.CameraUpdateFactory
import com.google.android.gms.maps.GoogleMap
import com.google.android.gms.maps.OnMapReadyCallback
import com.google.android.gms.maps.SupportMapFragment
import com.google.android.gms.maps.model.CircleOptions
import com.google.android.gms.maps.model.LatLng
import com.google.android.gms.maps.model.MarkerOptions
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.database.ValueEventListener
import com.msba.autobrakefamily.R

class MapFragment : Fragment() , OnMapReadyCallback{
    private lateinit var gotLocation:String
    private lateinit var mMap: GoogleMap
    var database = FirebaseDatabase.getInstance().reference
    lateinit var lat : String
    lateinit var lon : String

    override fun onCreateView(
            inflater: LayoutInflater,
            container: ViewGroup?,
            savedInstanceState: Bundle?
    ): View? {
        val root = inflater.inflate(R.layout.fragment_map, container, false)
        val latlon : TextView = root.findViewById(R.id.lat_lon)
        val date : TextView = root.findViewById(R.id.date)
        val mapFragment = childFragmentManager
            .findFragmentById(R.id.map) as SupportMapFragment
        mapFragment.getMapAsync(this)
        //Firebase GetData
        var getData = object : ValueEventListener{
            override fun onCancelled(p0: DatabaseError) {
            }
            override fun onDataChange(p0: DataSnapshot) {
                val dateVal :String = p0.child("autobrake/date").getValue() as String

                lat = p0.child("autobrake/lat").getValue() as String
                lon = p0.child("autobrake/lon").getValue() as String
                lat = lat.substring(0, lat.indexOf(".")+7)
                lon = lon.substring(0, lon.indexOf(".")+7)

//                val loc1 = Location("")
//                loc1.setLatitude(lat.toDouble())
//                loc1.setLongitude(lon.toDouble())
//
//                val loc2 = Location("")
//                loc2.setLatitude(lat2)
//                loc2.setLongitude(lon2)
//
//                val distanceInMeters: Float = loc1.distanceTo(loc2)

                latlon.text = "經緯度:$lon , $lat"
                date.text = "(上次取得時間 : $dateVal)"

            }
        }



        database.addValueEventListener(getData)

        return root
    }

    override fun onMapReady(googleMap: GoogleMap) {
        mMap = googleMap
        mMap.uiSettings.isZoomControlsEnabled = true
        var databaseList = FirebaseDatabase.getInstance().getReference("autobrake/setLocation")
        // Add a marker in Sydney and move the camera
        val locationNow = LatLng(lat.toDouble(), lon.toDouble())
        mMap.addMarker(MarkerOptions().position(locationNow).title("長者即時位置"))
        mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(locationNow, 16.0f))
        // Add a circle to map
        var getPlaceList = object : ValueEventListener{
            override fun onDataChange(dataSnapshot: DataSnapshot) {
                if(dataSnapshot!!.exists()){
                    for (e in dataSnapshot.children){
                        val place = e.getValue() as String
                        mMap!!.addCircle(
                                CircleOptions()
                                    .center(LatLng(place.substring(place.indexOf(":")+1, place.indexOf(",")).toDouble(), place.substring(place.indexOf(",")+1, place.length).toDouble()))
                                    .radius(50.0)
                                    .strokeWidth(3f)
                                    .strokeColor(Color.BLUE)
                                    .fillColor(Color.argb(70, 136, 170, 205))
                            )
                    }
                }
            }
            override fun onCancelled(databaseError: DatabaseError) {
                // Getting Post failed, log a message
                Log.w(ContentValues.TAG, "loadPost:onCancelled", databaseError.toException())
            }
        }
        databaseList.addValueEventListener(getPlaceList)
    }

}