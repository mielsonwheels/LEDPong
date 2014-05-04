package com.ledpong.LEDPongController;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import java.util.Set;

/**
 * Created by Miles on 4/25/2014. This is the main drawing
 * activity. You can use this activity to connect to the
 * LED Matrix, and draw on it, live.
 */
public class Animator extends Activity {
    private BluetoothAdapter myBluetoothAdapter;
    private Set<BluetoothDevice> pairedDevices;
    private BluetoothDevice mmDevice;
    private PongServer arduinoThread;
    private AnimatorCanvas c;
    private int REQUEST_ENABLE_BT = 1;
    protected boolean arduinoFound = false;

   /**
    *  Within the constructor we initialize the bluetooth adapter,
    *  create a thread that handles the connection, and pass the
    *  connection handling thread to the canvas.
    */
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // take an instance of BluetoothAdapter - Bluetooth radio
        myBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if(myBluetoothAdapter == null) {

            Toast.makeText(getApplicationContext(), "Your device does not support Bluetooth",
                    Toast.LENGTH_LONG).show();
            this.finish();
        }
        if (!myBluetoothAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }
        // get paired devices
        pairedDevices = myBluetoothAdapter.getBondedDevices();

        // put it's one to the adapter
        for(BluetoothDevice device : pairedDevices) {
            if (device.getName().contains("HC-06")) {
                mmDevice = device;
                arduinoFound = true;
                break;
            }
        }
        setContentView(R.layout.animate);
        AnimatorCanvas canvas = (AnimatorCanvas)findViewById(R.id.canvas);
        c = canvas;
        arduinoThread = new PongServer(mmDevice);
        arduinoThread.start();
        c.setThread(arduinoThread);
    }

    public void clear(View view){
        c.clearFrame();
    }

    public void eraseMode(View view){
        c.toggleErase();
    }

    @Override
    public void onDestroy(){
        if(arduinoThread != null) arduinoThread.cancel();
        super.onDestroy();
    }
}