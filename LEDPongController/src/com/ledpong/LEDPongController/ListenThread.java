package com.ledpong.LEDPongController;

import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.os.Handler;

import java.io.IOException;
import java.util.Vector;


/**
 * Created by Miles on 5/3/2014. We needed another thread to handle listening for incoming
 * connections. The reason why is explained in the MainMenu class.
 */
public class ListenThread extends Thread {
    private BluetoothServerSocket listenSocket;
    private int players = 1;
    private boolean quit;
    private Handler myHandler;
    private Vector<ClientHandlerThread> threads;

    public ListenThread(BluetoothServerSocket sock, Handler h){
        listenSocket = sock;
        quit = false;
        myHandler = h;
        threads = new Vector<ClientHandlerThread>(4);
    }

    public void run() {
        while (!quit) {
            //keep thread alive until we don't need it anymore
            //This is where where we listen for connections on master socket
            //once we get the right number of players, we close master socket
            //and start handling the game

            BluetoothSocket socket = null;
            if (players < 4) {
                try {
                    socket = listenSocket.accept();
                    System.out.println("socket accepted");
                } catch (IOException e) {
                    e.printStackTrace();
                }
                if (socket != null) {
                    ClientHandlerThread t = new ClientHandlerThread(socket, ++players, myHandler);
                    System.out.printf("# players = %d\n", players);
                    t.start();
                    threads.add(t);
                }
            }
        }
    }

    public void cancel(){
        try {
            listenSocket.close();
            quit = true;
            if(threads != null) {
                for (ClientHandlerThread t : threads) {
                    t.cancel();
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
