package com.ledpong.LEDPongController;

import android.bluetooth.BluetoothSocket;
import android.os.Handler;
import android.os.Message;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * Created by Miles on 5/2/2014.
 */
public class ClientHandlerThread extends Thread {
    private int player;
    private InputStream inStream;
    private OutputStream outStream;
    BluetoothSocket serverSocket;
    Handler parentHandler;

    public ClientHandlerThread(BluetoothSocket sock, int _player, Handler h) {
        serverSocket = sock;
        player = _player;
        parentHandler = h;
    }

    @Override
    public void run() {
        try {
            serverSocket.connect();
            while (!serverSocket.isConnected()) ;
            inStream = serverSocket.getInputStream();
            outStream = serverSocket.getOutputStream();
            outStream.write((byte) player);
            byte[] buf = new byte[1024];
            while(true){
                inStream.read(buf, 0, 2);
                System.out.println("Message received");
                Message m = Message.obtain();
                String s = new String(buf, "UTF-8");
                m.obj = s;
                parentHandler.sendMessage(m);
            }
        } catch(IOException e){
            e.printStackTrace();
        }
    }

    public void cancel(){
        try {
            if (serverSocket != null) serverSocket.close();
            if (inStream != null) inStream.close();
            if (outStream != null) outStream.close();
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}
