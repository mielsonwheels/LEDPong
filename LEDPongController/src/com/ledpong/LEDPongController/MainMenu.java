package com.ledpong.LEDPongController;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

/**
 * Created by Miles on 4/23/2014. This handles the main menu; pressing a button starts
 * the related activity.
 */
public class MainMenu extends Activity {
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.menu);
    }

    /**
     * Starts the server. The server will start a PongServer thread, which handles
     * the message Queue for all the client threads. It also starts a listen thread,
     * which accepts incoming connections. For each connection, we create a ClientHandler
     * Thread, which receives messages from the clients. In total, we will have 7 threads.
     */
    public void startServer(View view){
        Intent intent = new Intent(this, BTConnectorServer.class);
        startActivity(intent);
    }

    /**
     * Starts the client. It will connect to the pong server, and only spawn a thread
     * to manage the connection.
     */
    public void startClient(View view){
        Intent intent = new Intent(this, BTConnectorClient.class);
        startActivity(intent);
    }
    /**
     * Starts the animator, which functions similarly to the pong server, minus
     * the listen thread/client threads.
     */
    public void startAnimate(View view){
        Intent intent = new Intent(this, Animator.class);
        startActivity(intent);
    }
    @Override
    public void onDestroy() {
        super.onDestroy();
    }
}