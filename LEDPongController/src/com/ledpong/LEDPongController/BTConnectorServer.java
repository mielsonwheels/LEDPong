package com.ledpong.LEDPongController;

import android.os.Bundle;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;

import java.io.IOException;
import java.util.Set;
import android.content.Intent;
import android.content.IntentFilter;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.*;

public class BTConnectorServer extends Activity {

    private BluetoothAdapter myBluetoothAdapter;
    private Set<BluetoothDevice> pairedDevices;
    private BluetoothDevice mmDevice;
    private PongClient arduinoThread;
    protected boolean arduinoFound = false;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.bt_test);

        // take an instance of BluetoothAdapter - Bluetooth radio
        myBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if(myBluetoothAdapter == null) {

            Toast.makeText(getApplicationContext(),"Your device does not support Bluetooth",
                    Toast.LENGTH_LONG).show();
            this.finish();
        }
        // get paired devices
        pairedDevices = myBluetoothAdapter.getBondedDevices();

        // put it's one to the adapter
        for(BluetoothDevice device : pairedDevices)
            if(device.getName() == "HC-06"){
                mmDevice = device;
                arduinoFound = true;
                break;
            }
        if(!arduinoFound) { //arduino isn't already paired; start searching for it.
            find();
        }
        arduinoThread = new PongClient(mmDevice);
        arduinoThread.run();
    }
    final BroadcastReceiver bReceiver = new BroadcastReceiver() {
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            // When discovery finds a device
            if (BluetoothDevice.ACTION_FOUND.equals(action)) {
                // Get the BluetoothDevice object from the Intent
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                // check if device is arduino BT module
                if (device.getName() == "HC-06") {
                    mmDevice = device;
                    myBluetoothAdapter.cancelDiscovery();
                    arduinoFound = true;
                    arduinoThread = new PongClient(mmDevice);
                    arduinoThread.run();
                }
            }
        }
    };
    private void find() {
        IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
        registerReceiver(bReceiver, filter);
        myBluetoothAdapter.startDiscovery();
    }

    public void sendLeft(View v){
        arduinoThread.sendLeft(1);
    }

    public void sendRight(View view){
        arduinoThread.sendRight(1);
    }

    @Override
    protected void onDestroy() {
        // TODO Auto-generated method stub
        super.onDestroy();
        unregisterReceiver(bReceiver);
    }
}