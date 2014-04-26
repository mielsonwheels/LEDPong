package com.ledpong.LEDPongController;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

/*
 * This is the thread that handles client connections.
 * This includes connection from server to arduino, and
 * between pong clients and the pong server.
 */
public class PongServer extends Thread {
    private final BluetoothSocket mmSocket;
    private final BluetoothDevice mmDevice;
    private InputStream mmInStream;
    private OutputStream mmOutStream;
    private boolean quit;

    public PongServer(BluetoothDevice arduino) {
        BluetoothSocket tmp = null;
        mmDevice = arduino;
        UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");//hardcode this bitch
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
            mmInStream = mmSocket.getInputStream();
            mmOutStream = mmSocket.getOutputStream();
        } catch (IOException e) {
            e.printStackTrace();
        }
        while(!quit){
            //keep thread alive until we don't need it anymore
        }
    }

    public void sendLeft(int player) throws IOException {
        try {
            byte[] message;
            String command = Integer.toString(player+20100);
            command += "a";
            message = command.getBytes();
            mmOutStream.write(message);
        } catch (IOException e) {
            throw e;
        }
    }

    public void sendRight(int player) throws IOException {
        try {
            byte[] message;
            String command = Integer.toString(player+20110);
            command += "a";
            message = command.getBytes();
            mmOutStream.write(message);
        } catch (IOException e) {
            throw e;
        }
    }

    public void cancel() throws IOException {
        quit = true;
        try {
            mmSocket.close();
            mmInStream.close();
            mmOutStream.close();
        } catch (IOException e){
            throw e;
        }
    }
}
