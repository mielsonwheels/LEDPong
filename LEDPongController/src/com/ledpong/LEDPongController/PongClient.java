package com.ledpong.LEDPongController;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

/**
 * Created by Miles on 4/25/2014.
 */
public class PongClient extends Thread {
    private final BluetoothSocket mmSocket;
    private final BluetoothDevice mmDevice;
    private InputStream mmInStream;
    private OutputStream mmOutStream;
    private boolean quit;

    public PongClient(BluetoothDevice device) {
        BluetoothSocket tmp = null;
        mmDevice = device;
        UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb"); //Standard SerialPortService ID
                                                                             //snagged from a website
        try{
            tmp = device.createRfcommSocketToServiceRecord(uuid);
        } catch (IOException e){

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

    public void sendLeft(int player) {
        try {
            mmOutStream.write(00000 + player);  //TODO: remember move codes
            mmOutStream.write('a');
        } catch (IOException e) {

        }
    }

    public void sendRight(int player) {
        try {
            mmOutStream.write(00000 + player);  //TODO: remember move codes
            mmOutStream.write('a');
        } catch (IOException e) {

        }
    }

    public void cancel(){
        quit = true;
        try {
            mmSocket.close();
            mmInStream.close();
            mmOutStream.close();
        } catch (IOException e){

        }
    }
}
