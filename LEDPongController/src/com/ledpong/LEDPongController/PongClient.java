package com.ledpong.LEDPongController;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

/**
 * Created by Miles on 4/24/2014. This is the thread that handles the connection
 * from a client phone to the server. This is executed client side, and therefore
 * is far more simple than pongServer needs to be.
 */
public class PongClient extends Thread {
    private final BluetoothSocket mmSocket;
    private final BluetoothDevice mmDevice;
    private InputStream mmInStream;
    private OutputStream mmOutStream;
    private boolean quit;
    private int player = 0;

    public PongClient(BluetoothDevice server){
        BluetoothSocket tmp = null;
        mmDevice = server;
        UUID uuid = UUID.fromString("84837563-fd99-455f-9719-65019b492ce9");//hardcode this bitch
        try{
            tmp = mmDevice.createRfcommSocketToServiceRecord(uuid);

        } catch (IOException e){
            e.printStackTrace();
        }
        mmSocket = tmp;
        quit = false;
    }

    public void run(){
        try {
            mmSocket.connect();
            while(!mmSocket.isConnected()){
                System.out.println("Waiting to connect...");
            }
            mmInStream = mmSocket.getInputStream();
            mmOutStream = mmSocket.getOutputStream();
            player = mmInStream.read();
            System.out.printf("Client is player %d\n", player);
        } catch (IOException e) {
            e.printStackTrace();
        }

        while(!quit){
            //keep thread alive until we don't need it anymore
            //This is where where we listen for connections on master socket
            //once we get the right number of players, we close master socket
            //and start handling the game
        }
    }

    public void sendLeft() throws IOException {
        try {
            byte[] command = new byte[2];
            command[0] = (byte) player;
            command[1] = (byte) 'l';
            mmOutStream.write(command);
        } catch (IOException e) {
            throw e;
        }
    }

    public void sendRight() throws IOException {
        try {
            byte[] command = new byte[2];
            command[0] = (byte) player;
            command[1] = (byte) 'r';
            mmOutStream.write(command);
        } catch (IOException e) {
            throw e;
        }
    }

    public void cancel() {
        quit = true;
        try {
            if(mmSocket != null) mmSocket.close();
            if(mmInStream != null) mmInStream.close();
            if(mmOutStream != null) mmOutStream.close();
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}