package com.ledpong.LEDPongController;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;

import java.io.IOException;
import java.util.Vector;

/**
 * Created by Miles on 4/25/2014. This class is a custom
 * view that handles the grid that you see in the animate
 * function. It's dynamic, and handles the correct cell size
 * based on the size of view.
 */
public class AnimatorCanvas extends View{
    private boolean[][] ledMatrix;
    private Vector<boolean[][]> frames;
    private float cellWidth;
    private float cellHeight;
    private float selfWidth;
    private float selfHeight;
    private Paint linePaint;
    private Paint squarePaint;
    private boolean eraseMode = false;
    PongServer arduinoThread;

    public AnimatorCanvas(Context context) {
        super(context);
        ledMatrix = new boolean[24][24];
        linePaint = new Paint();
        linePaint.setColor(Color.CYAN);
        squarePaint = new Paint();
        squarePaint.setColor(Color.GREEN);
        this.clearFrame();
    }

    public AnimatorCanvas(Context context, AttributeSet attributeSet) {
        super(context, attributeSet);
        ledMatrix = new boolean[24][24];
        linePaint = new Paint();
        linePaint.setColor(Color.CYAN);
        squarePaint = new Paint();
        squarePaint.setColor(Color.GREEN);
        this.clearFrame();
    }

    public AnimatorCanvas(Context context, AttributeSet attributeSet, int defStyle) {
        super(context, attributeSet, defStyle);
        ledMatrix = new boolean[24][24];
        linePaint = new Paint();
        linePaint.setColor(Color.CYAN);
        squarePaint = new Paint();
        squarePaint.setColor(Color.GREEN);
        this.clearFrame();
    }

    public void toggleErase(){
        eraseMode = !eraseMode;
    }

    /**
     * calculate the size of the cells whenever we're redrawn
     */
    @Override
    protected void onSizeChanged(int w, int h, int oldh, int oldw){
        cellWidth = ((w - (getPaddingLeft()+getPaddingRight())) / 24);
        cellHeight = ((h - (getPaddingBottom()+getPaddingTop())) / 24);
    }

    /**
     * This function handles drawing the canvas & what LEDs are lit up.
     */
    @Override
    protected void onDraw(Canvas canvas){
        float startX;
        float startY = 0;
        canvas.drawColor(Color.BLACK);  //clear the screen

        //This horrific for loop draws the grid
        for(int i = 0; i < 24; i++){
            startX = 0;
            for(int j = 0; j < 24; j++){
                canvas.drawLine(startX + cellWidth, startY, startX+cellWidth, startY+cellHeight, linePaint);
                canvas.drawLine(startX, startY+cellHeight, startX+cellWidth, startY+cellHeight, linePaint);

                //if the LED is set, we draw a green square to show that it is lit.
                if(ledMatrix[i][j]){
                    canvas.drawRect(startX,startY,
                            (startX+cellWidth),(startY+cellHeight),squarePaint);
                }
                startX += cellWidth;
            }
            startY += cellHeight;
        }

        //draw the the edge of the grid
        canvas.drawLine(0,0,selfWidth,0,linePaint);
        canvas.drawLine(0,0,0,selfHeight,linePaint);
        canvas.drawLine(0,selfHeight,selfWidth,selfHeight,linePaint);
        canvas.drawLine(selfWidth,0,selfWidth,selfHeight,linePaint);
    }

    //this function never actually used
    public void saveFrame(View view){
        frames.add(ledMatrix);
    }

    //toggle the LED on or off, depending on if we're erasing or not
    public void toggleLed(int x, int y){
        if(x < 0) x = 0;
        if(y < 0) y = 0;
        if(x > 23) x = 23;
        if(y > 23) y = 23;
        if(eraseMode) {
            ledMatrix[y][x] = false;
        }
        else {
            ledMatrix[y][x] = true;
        }
        invalidate();
    }

    //not actually used.
    public boolean getLed(int x, int y){
        if(x < 0) x = 0;
        if(x > 23) x = 23;
        if(y < 0) y = 0;
        if(y > 23) y = 23;
        return ledMatrix[x][y];
    }

    //not actually used
    public Vector<boolean[][]> getFrames(){
        return frames;
    }

    //go through and set every LED to false; we also send a clearLED command to the arduino
    public void clearFrame(){
        for(int i = 0; i < 24; i++){
            for(int j = 0; j < 24; j++){
                ledMatrix[i][j] = false;
            }
        }
        invalidate();
        try {
            if (arduinoThread != null) arduinoThread.clearLED(); //Might not want this here when saving animations?
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    //Rows are (where you touched) / width of the cell
    //Columns are the same, but just with Y and height
    private int calcRow(float touchX) {
        return (int)(touchX / cellWidth);
    }

    private int calcColumn(float touchY){
        return (int)(touchY / cellHeight);
    }

    /**The touch handler. Here we get the X and Y where you touch,
     * and update our internal representation of the matrix and
     * send the LED that got touched.
     */
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        float touchX = event.getX();
        float touchY = event.getY();
        int x = calcRow(touchX);
        int y = calcColumn(touchY);
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
            case MotionEvent.ACTION_MOVE:
                toggleLed(x,y);
                break;
            default:
                return false;
        }
        invalidate();
        try {
           if(arduinoThread != null) arduinoThread.sendLed(x, y, eraseMode);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return true;
    }

    /**
     * Simply used to pass the thread handling the connection to the arduino
     * into this class.
     */
    public void setThread(PongServer thread){
        arduinoThread = thread;
    }
}
