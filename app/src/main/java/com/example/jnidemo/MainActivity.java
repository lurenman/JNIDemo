package com.example.jnidemo;

import android.app.IntentService;
import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import java.lang.reflect.Proxy;

import androidx.annotation.NonNull;

public class MainActivity extends BaseActivity {
    private Button btn_click;
    private Button btn_add;
    private Button btn_str_parse;
    private Button btn_parse_intarr;
    private Button btn_callbackvoidmethod;
    private Button btn_callbackintmethod;
    private Button btn_callbackstringmethod;

    @NonNull
    @Override
    protected String getActionBarTitle() {
        return "JNIDemo";
    }

    @Override
    protected int getLayoutResId() {
        return R.layout.activity_main;
    }

    @Override
    protected void initView() {
        btn_click = (Button) findViewById(R.id.btn_click);
        btn_add = (Button) findViewById(R.id.btn_add);
        btn_str_parse = (Button) findViewById(R.id.btn_str_parse);
        btn_parse_intarr = (Button) findViewById(R.id.btn_parse_intarr);
        btn_callbackvoidmethod = (Button) findViewById(R.id.btn_callbackvoidmethod);
        btn_callbackintmethod = (Button) findViewById(R.id.btn_callbackintmethod);
        btn_callbackstringmethod = (Button) findViewById(R.id.btn_callbackstringmethod);
    }

    @Override
    protected void initVariables() {

    }

    @Override
    protected void initListenter() {
        btn_click.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String strFromJNI = JNITest.getStrFromJNI();
                Toast.makeText(mContext, strFromJNI, Toast.LENGTH_SHORT).show();
            }
        });
        btn_add.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int add = JNITest.add(1, 2);
                Toast.makeText(mContext, add + "", Toast.LENGTH_SHORT).show();
            }
        });
        btn_str_parse.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String strParse = JNITest.getStrParse("abc");
                Toast.makeText(mContext, strParse, Toast.LENGTH_SHORT).show();
            }
        });
        btn_parse_intarr.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int[] ints = JNITest.parseIntArray(new int[]{1, 2, 3});
                StringBuilder stringBuilder = new StringBuilder();
                for (int i = 0; i < ints.length; i++) {
                    int anInt = ints[i];
                    stringBuilder.append(anInt);
                }
                Toast.makeText(mContext, stringBuilder.toString(), Toast.LENGTH_SHORT).show();
            }
        });
        btn_callbackvoidmethod.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                JNITest.callbackvoidmethod();
            }
        });
        btn_callbackintmethod.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                JNITest.callbackintmethod();
            }
        });
        btn_callbackstringmethod.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                JNITest.callbackstringmethod();
            }
        });
    }
}