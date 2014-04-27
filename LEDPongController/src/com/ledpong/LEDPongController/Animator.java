package com.ledpong.LEDPongController;

import android.app.ActionBar;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.view.View;
import android.widget.GridLayout;
import android.widget.TableLayout;
import android.widget.Toast;
import android.widget.ToggleButton;

import java.util.Set;

/**
 * Created by Miles on 4/25/2014.
 */
public class Animator extends Activity {
    private BluetoothAdapter myBluetoothAdapter;
    private Set<BluetoothDevice> pairedDevices;
    private BluetoothDevice mmDevice;
    private PongServer arduinoThread;
    private int REQUEST_ENABLE_BT = 1;
    protected boolean arduinoFound = false;

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
        //arduinoThread = new PongServer(mmDevice);
        //arduinoThread.start();
    }

    @Override
    public void onDestroy(){
        if(arduinoThread != null) arduinoThread.cancel();
        super.onDestroy();
    }
}