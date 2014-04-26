package com.ledpong.LEDPongController;

import android.app.Activity;
import android.os.Bundle;

/**
 * Created by Miles on 4/25/2014. Will be used by the clients to connect  to
 * pong server running on another android device. Also contains information for
 * sending left/rigth commands to server.
 */
public class BTConnectorClient extends Activity {
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.client);
    }
}