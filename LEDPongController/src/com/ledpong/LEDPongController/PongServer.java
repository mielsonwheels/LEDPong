package com.ledpong.LEDPongController;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.SystemClock;

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
            //This is where where we listen for connections on master socket
            //once we get the right number of players, we close master socket
            //and start handling the game
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

    public void clearLED() throws IOException {
        try{
            byte[] message;
            String command = Integer.toString(101234);
            command += "a";
            message = command.getBytes();
            mmOutStream.write(message);
        } catch(IOException e) {
            throw e;
        }
    }

    public void sendLed(int x, int y, boolean on) throws IOException {
        try{
            byte[] message;
            int c = 1;
            if(on){
                c = 9;
            }
            String xs = Integer.toString(x), ys = Integer.toString(y);
            if(x < 10)
                xs = "0" + xs;
            if(y < 10)
                ys = "0" + ys;
            String command = Integer.toString(c) + xs + ys;
            command += "a";
            message = command.getBytes();
            System.out.println(command);
            if (mmOutStream != null) mmOutStream.write(message);
        } catch(IOException e) {
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
