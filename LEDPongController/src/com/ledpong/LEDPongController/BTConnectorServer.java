package com.ledpong.LEDPongController;

import android.os.Bundle;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;

import java.io.IOException;
import java.util.Set;
import android.content.Intent;
import android.view.View;
import android.widget.*;

public class BTConnectorServer extends Activity {

    private BluetoothAdapter myBluetoothAdapter;
    private Set<BluetoothDevice> pairedDevices;
    private BluetoothDevice mmDevice;
    private PongServer arduinoThread;
    private int REQUEST_ENABLE_BT = 0;
    protected boolean arduinoFound = false;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.bt_test);

        // take an instance of BluetoothAdapter - Bluetooth radio
        myBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if(myBluetoothAdapter == null){
            Toast.makeText(getApplicationContext(),"Your device does not support Bluetooth",
                    Toast.LENGTH_LONG).show();
            finish();
        }
        if (!myBluetoothAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
            while(REQUEST_ENABLE_BT != RESULT_OK);
        }

        // get paired devices
        pairedDevices = myBluetoothAdapter.getBondedDevices();

        // put it's one to the adapter
        for(BluetoothDevice device : pairedDevices) {
            if (device.getName().equals("HC-06")) {
                mmDevice = device;
                arduinoFound = true;
                break;
            }
        }
        if(!arduinoFound){
            Toast.makeText(getApplicationContext(),"Arduino not found!",
                    Toast.LENGTH_LONG).show();
            finish();
        }
        myBluetoothAdapter.setName("Pong Server");

        //wait for adapter to turn on
        while(myBluetoothAdapter.getState() != BluetoothAdapter.STATE_ON);

        //make ourselves discoverable
        Intent discoverableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
        discoverableIntent.putExtra(BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION, 60);
        startActivity(discoverableIntent);

        //start main server thread
        arduinoThread = new PongServer(mmDevice);
        arduinoThread.start();
    }

    public void sendLeft(View v){
        try {
            arduinoThread.sendLeft(1);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sendRight(View view){
        try {
            arduinoThread.sendRight(1);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void onDestroy() {
        // TODO Auto-generated method stub
        if(arduinoThread != null) arduinoThread.cancel();
        super.onDestroy();
    }
}