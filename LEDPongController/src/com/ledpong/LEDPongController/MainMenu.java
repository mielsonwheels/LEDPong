package com.ledpong.LEDPongController;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

/**
 * Created by Miles on 4/23/2014.
 */
public class MainMenu extends Activity {
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.menu);
    }

    public void startServer(View view){
        Intent intent = new Intent(this, BTConnectorServer.class);
        startActivity(intent);
    }

    public void startClient(View view){
        Intent intent = new Intent(this, BTConnectorClient.class);
        startActivity(intent);
    }
    @Override
    public void onDestroy() {
        super.onDestroy();
    }
}