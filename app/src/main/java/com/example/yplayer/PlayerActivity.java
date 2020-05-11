package com.example.yplayer;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import com.example.yplayer.R;

public class PlayerActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_player);

        Intent intent = getIntent();
        String path =  intent.getStringExtra("path");
        Ylayer yplayer = findViewById(R.id.yplayer);
        yplayer.setPath(path);

    }
}
