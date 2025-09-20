package com.example.helloworld; // 包名，需与 AndroidManifest.xml 中一致

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // 加载 activity_main.xml 布局
        setContentView(R.layout.activity_main);
    }
}