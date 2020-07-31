package com.msba.autobrakefamily

import android.app.AlertDialog
import android.app.Dialog
import android.content.ContentValues.TAG
import android.content.Context
import android.os.Bundle
import android.util.Log
import android.util.TypedValue
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.view.inputmethod.InputMethodManager
import android.widget.*
import androidx.fragment.app.DialogFragment
import com.google.android.gms.maps.CameraUpdateFactory
import com.google.android.gms.maps.GoogleMap
import com.google.android.gms.maps.OnMapReadyCallback
import com.google.android.gms.maps.SupportMapFragment
import com.google.android.gms.maps.model.*
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.database.ValueEventListener
import kotlinx.android.synthetic.main.fragment_setplace.*


class SetPlaceFragment : DialogFragment(), OnMapReadyCallback {
    var mMap: GoogleMap? = null
    override fun onStart() {
        super.onStart()
        val dialog: Dialog? = dialog
        if (dialog != null) {
            val width = ViewGroup.LayoutParams.MATCH_PARENT
            val height = ViewGroup.LayoutParams.MATCH_PARENT
            dialog.window!!.setLayout(width, height)
        }
    }
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        // Inflate the layout for this fragment
        val rootView: View = inflater.inflate(R.layout.fragment_setplace, container, false)
        val BtnDone : Button = rootView.findViewById(R.id.btn_setplace_done)
        val BtnConfirm : Button = rootView.findViewById(R.id.btn_setplace_confirm)
        val mapFragment =
            childFragmentManager.findFragmentById(R.id.setplace_map) as SupportMapFragment
        mapFragment.getMapAsync(this)


        BtnConfirm.visibility = View.GONE
        BtnDone.setOnClickListener{
            dialog?.dismiss()
        }

        return rootView
    }

    override fun onMapReady(googleMap: GoogleMap) {
        mMap = googleMap
        var database = FirebaseDatabase.getInstance().reference
        val latLng = LatLng(23.583234, 120.582597)
        mMap!!.moveCamera(CameraUpdateFactory.newLatLngZoom(latLng, 7f))

        var databaseList = FirebaseDatabase.getInstance().getReference("autobrake/setLocation")
        val list = ArrayList<String>()
        val postListener = object : ValueEventListener {
            override fun onDataChange(dataSnapshot: DataSnapshot) {
                if(dataSnapshot!!.exists()){
                    list.clear()
                    for (e in dataSnapshot.children){
                        val place = e.getValue() as String
                        mMap!!.addMarker(
                            MarkerOptions()
                                .position(LatLng(place.substring(place.indexOf(":")+1, place.indexOf(",")).toDouble(), place.substring(place.indexOf(",")+1, place.length).toDouble()))
                                .title("已設定")
                                .snippet(place.substring(0,place.indexOf(":")))
                                .icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_BLUE))
                        )
                        list.add(place)
                    }
                }
            }
            override fun onCancelled(databaseError: DatabaseError) {
                // Getting Post failed, log a message
                Log.w(TAG, "loadPost:onCancelled", databaseError.toException())
            }
        }
        databaseList.addValueEventListener(postListener)

        mMap!!.setOnMapClickListener(){
            mMap!!.clear()
            val setPoint : LatLng = it
            mMap!!.addMarker(MarkerOptions().position(it))

            for (i in list){
                mMap!!.addMarker(
                    MarkerOptions()
                        .position(LatLng(i.substring(i.indexOf(":")+1, i.indexOf(",")).toDouble(), i.substring(i.indexOf(",")+1, i.length).toDouble()))
                        .title("已設定")
                        .snippet(i.substring(0,i.indexOf(":")))
                        .icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_BLUE))
                )
            }

            btn_setplace_confirm.visibility = View.VISIBLE
            btn_setplace_confirm.setOnClickListener{
                //alert dialog with layout Programmatically
                val mBuilder = AlertDialog.Builder(activity)
                val mLayout  = LinearLayout(activity)
                val mTvName  = TextView(activity)
                val mEtName  = EditText(activity)

                mTvName.text  = "請輸入地點名稱 :"
                mTvName.setTextSize(TypedValue.COMPLEX_UNIT_SP, 16f)
                mEtName.setSingleLine()
                mLayout.orientation = LinearLayout.VERTICAL
                mLayout.addView(mTvName)
                mLayout.addView(mEtName)
                mLayout.setPadding(50, 40, 50, 10)

                mBuilder.setView(mLayout)

                mBuilder.setPositiveButton("完成"){dialogInterface, i ->

                    val name = mEtName.text.toString()
                    if (name != ""){
                        database.child("autobrake/setLocation/${name}").setValue("$name:${setPoint.latitude},${setPoint.longitude}")
                        Toast.makeText(activity, "設定成功!", Toast.LENGTH_SHORT).show()
                        val ime = activity?.getSystemService(Context.INPUT_METHOD_SERVICE) as InputMethodManager
                        ime.hideSoftInputFromWindow(view?.windowToken, 0)
                        dialog?.dismiss()
                    }else{Toast.makeText(activity, "請輸入名稱", Toast.LENGTH_SHORT).show()}
                }

                mBuilder.setNeutralButton("取消"){dialogInterface, i ->
                    val ime = activity?.getSystemService(Context.INPUT_METHOD_SERVICE) as InputMethodManager
                    ime.hideSoftInputFromWindow(view?.windowToken, 0)
                    dialogInterface.dismiss()
                }
                mBuilder.show()
            }
        }
    }
}