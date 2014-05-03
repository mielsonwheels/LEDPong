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

public class BTConnectorClient extends Activity {

    private BluetoothAdapter myBluetoothAdapter;
    private Set<BluetoothDevice> pairedDevices;
    private BluetoothDevice mmDevice;
    private PongClient connectionThread;
    private int REQUEST_ENABLE_BT = 0;
    protected boolean serverFound = false;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.client);

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
            if (device.getName().equals("Pong Server")) {
                mmDevice = device;
                serverFound = true;
                break;
            }
        }
        if(!serverFound){
            Toast.makeText(getApplicationContext(),"Arduino not found!",
                    Toast.LENGTH_LONG).show();
            finish();
        }
        //wait for adapter to turn on
        while(myBluetoothAdapter.getState() != BluetoothAdapter.STATE_ON);

        //start main server thread
        connectionThread = new PongClient(mmDevice);
        connectionThread.start();
    }

    public void sendLeft(View v){
        try {
            connectionThread.sendLeft();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sendRight(View view){
        try {
            connectionThread.sendRight();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void onDestroy() {
        // TODO Auto-generated method stub
        if(connectionThread != null) connectionThread.cancel();
        super.onDestroy();
    }
}