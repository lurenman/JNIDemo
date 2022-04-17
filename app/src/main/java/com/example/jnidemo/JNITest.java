package com.example.jnidemo;


import android.util.Log;

public class JNITest {
    private static final String TAG = "JNITest";

    static {
        System.loadLibrary("jnidemo");
    }

    public native static String getStrFromJNI();

    public native static int add(int x, int y);

    public native static String getStrParse(String str);

    public native static int[] parseIntArray(int[] intArr);

    public native static void callbackvoidmethod();

    public native static void callbackintmethod();

    public native static void callbackstringmethod();

    public static void helloFromJava() {
        Log.d(TAG, "helloFromJava---");
    }

    public static int addback(int a, int b) {
        int result = a + b;
        Log.d(TAG, "add:" + result);
        return result;
    }
    public static void stringback(String str) {
        Log.d(TAG, "stringback:" + str);
    }
}
