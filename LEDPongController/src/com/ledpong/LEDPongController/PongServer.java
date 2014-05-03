package com.ledpong.LEDPongController;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;
import java.util.Vector;

/*
 * This is the thread that handles client connections.
 * This includes connection from server to arduino, and
 * between pong clients and the pong server.
 */
public class PongServer extends Thread {
    private final BluetoothSocket arduinoSocket;
    private BluetoothServerSocket listenSocket;
    private ListenThread listenThread;
    private final BluetoothDevice mmDevice;
    private InputStream mmInStream;
    private OutputStream mmOutStream;
    private Vector<ClientHandlerThread> threads;
    public Handler myHandler;

    public PongServer(BluetoothDevice arduino) {
        BluetoothSocket tmp = null;
        BluetoothServerSocket tmp2 = null;
        mmDevice = arduino;
        UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");//hardcode this bitch
        try{
            tmp = mmDevice.createRfcommSocketToServiceRecord(uuid);
            tmp2 = BluetoothAdapter.getDefaultAdapter().listenUsingInsecureRfcommWithServiceRecord("Pong Server",
                    UUID.fromString("84837563-fd99-455f-9719-65019b492ce9"));
        } catch (IOException e){
            e.printStackTrace();
        }
        arduinoSocket = tmp;
        listenSocket = tmp2;
    }

    public void run(){
        Looper.prepare();
        myHandler = new Handler(){
            @Override
            public void handleMessage(Message msg) {
                byte[] message = (byte[]) msg.obj;
                try {
                    char direction = (char) message[1];
                    int player = (int) message[0];
                    System.out.printf("Message received. Dir: %c, Player: %d", direction, player);
                    if (direction == 'l') sendLeft(player);
                    if (direction == 'r') sendRight(player);
                }
                catch(IOException e){
                    e.printStackTrace();
                }
                catch (NullPointerException e){
                    System.out.println("substring fucked up");
                    e.printStackTrace();
                }
            }
        };
        try {
            arduinoSocket.connect();
            while(!arduinoSocket.isConnected()){
                System.out.println("Waiting to connect arduino...");
            }
            mmInStream = arduinoSocket.getInputStream();
            mmOutStream = arduinoSocket.getOutputStream();
        } catch (IOException e) {
            e.printStackTrace();
        }
        ListenThread t = new ListenThread(listenSocket, myHandler);
        listenThread = t;
        listenThread.start();
        Looper.loop();
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

    public void sendReset(){
        try{
            if(mmOutStream != null) mmOutStream.write("88888a".getBytes());
        } catch (IOException e){
            e.printStackTrace();
        }
    }

    public void cancel() {
        try {
            if(arduinoSocket != null) arduinoSocket.close();
            if(mmInStream != null) mmInStream.close();
            if(mmOutStream != null) mmOutStream.close();
            listenThread.cancel();
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}
