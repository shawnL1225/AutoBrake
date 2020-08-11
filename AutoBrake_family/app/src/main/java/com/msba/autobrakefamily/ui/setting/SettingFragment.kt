package com.msba.autobrakefamily.ui.setting

import android.app.AlertDialog
import android.content.Context
import android.os.Bundle
import android.util.TypedValue
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.view.inputmethod.InputMethodManager
import android.widget.*
import androidx.fragment.app.Fragment
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.database.ValueEventListener
import com.msba.autobrakefamily.R
import com.msba.autobrakefamily.SetPlaceFragment

class SettingFragment : Fragment(){
    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {

        val root = inflater.inflate(R.layout.fragment_setting, container, false)
        val sendBtn : Button = root.findViewById(R.id.send_btn)
        val phoneNum : EditText = root.findViewById(R.id.editTextPhone)
        val lastphoneNum : TextView = root.findViewById(R.id.last_phoneNum)

        val btnSendMessage : Button = root.findViewById(R.id.send_message_btn)
        val sendMessage: EditText = root.findViewById(R.id.send_message_box)
        val lastMessage : TextView = root.findViewById(R.id.last_message)

        val btnSetPlace : Button = root.findViewById(R.id.btn_toMap)
        val placeList : ListView = root.findViewById(R.id.place_list)

        var database = FirebaseDatabase.getInstance().reference

        var getData = object : ValueEventListener {
            override fun onCancelled(p0: DatabaseError) {
            }

            override fun onDataChange(p0: DataSnapshot) {

            }
        }
        database.addValueEventListener(getData)

        btnSendMessage.setOnClickListener(){
            val ime = activity?.getSystemService(Context.INPUT_METHOD_SERVICE) as InputMethodManager
            ime.hideSoftInputFromWindow(view?.windowToken, 0)

            var message :String = "${sendMessage.text}"
            Toast.makeText(activity, "傳送成功!", Toast.LENGTH_SHORT).show()
            database.child("autobrake/note").setValue(message)
        }

        sendBtn.setOnClickListener(){
            val ime = activity?.getSystemService(Context.INPUT_METHOD_SERVICE) as InputMethodManager
            ime.hideSoftInputFromWindow(view?.windowToken, 0)

            var message :String = "${phoneNum.text}"
            if (phoneNum.length()<9 || phoneNum.length()>10){
                Toast.makeText(activity, "格式錯誤 請重新輸入", Toast.LENGTH_SHORT).show()
            }else{
                database.child("autobrake/callNumber").setValue(message)
                Toast.makeText(activity, "設定成功!", Toast.LENGTH_SHORT).show()
            }
        }
        btnSetPlace.setOnClickListener(){
            SetPlaceFragment().show(parentFragmentManager , null)
        }

        val list = ArrayList<String>()
        val adapter = activity?.let { ArrayAdapter(it, R.layout.listview, list) }
        placeList.adapter = adapter


        val listRef = FirebaseDatabase.getInstance().getReference("autobrake")
        listRef.addValueEventListener(object : ValueEventListener {
            override fun onCancelled(p0: DatabaseError) {
            }

            override fun onDataChange(p0: DataSnapshot) {
                list.clear()
                lastMessage.text = "上次傳送 : ${p0.child("note").getValue() as String}"
                lastphoneNum.text = "目前為 : ${p0.child("callNumber").getValue()}"
                if(p0.exists()){
                    for(e in p0.child("setLocation").children){
                        val placeString = e.value as String
                        val placeName = placeString.substring(0,placeString.indexOf(':'))
                        list.add(placeName)

                        adapter!!.notifyDataSetChanged()
                    }
                }
                adapter!!.notifyDataSetChanged()
            }
        })

        placeList.onItemClickListener = AdapterView.OnItemClickListener { _, _, position, _ ->

            //alert dialog with layout Programmatically
            val mBuilder = AlertDialog.Builder(activity)
            val mLayout  = LinearLayout(activity)
            val mTvName  = TextView(activity)

            mTvName.text  = "確定要刪除嗎 ?"
            mTvName.setTextSize(TypedValue.COMPLEX_UNIT_SP, 20f)
            mLayout.orientation = LinearLayout.VERTICAL
            mLayout.addView(mTvName)
            mLayout.setPadding(80, 40, 80, 10)

            mBuilder.setView(mLayout)

            mBuilder.setPositiveButton("確定"){dialogInterface, i ->
                listRef.child("setLocation").child(list[position]).removeValue()
            }

            mBuilder.setNeutralButton("取消"){dialogInterface, i ->
                dialogInterface.dismiss()
            }
            mBuilder.show()
        }




        return root
    }
}