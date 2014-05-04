package com.ledpong.LEDPongController;

import android.bluetooth.BluetoothSocket;
import android.os.Handler;
import android.os.Message;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * Created by Miles on 5/2/2014. This thread handles an individual connection
 * between a client and the server, on the server side. It keeps track of
 * the player who this thread is receiving from.
 */
public class ClientHandlerThread extends Thread {
    private int player;
    private InputStream inStream;
    private OutputStream outStream;
    private boolean quit;
    BluetoothSocket serverSocket;
    Handler parentHandler;

    public ClientHandlerThread(BluetoothSocket sock, int _player, Handler h) {
        serverSocket = sock;
        player = _player;
        parentHandler = h;
        quit = false;
    }

    /**
     * This run function just sits here and receives from the client. It
     * also sends the player number before receiving and data.
     */
    @Override
    public void run() {
        try {
            inStream = serverSocket.getInputStream();
            outStream = serverSocket.getOutputStream();
            outStream.write((byte) player);
            byte[] buf = new byte[1024];
            while(!quit){
                inStream.read(buf, 0, 2);
                System.out.println("Message received");
                Message m = Message.obtain();
                m.obj = buf;
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
        quit = true;
    }
}
