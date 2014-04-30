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
 * Created by Miles on 4/25/2014.
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

    @Override
    protected void onSizeChanged(int w, int h, int oldh, int oldw){
        cellWidth = ((w - (getPaddingLeft()+getPaddingRight())) / 24);
        cellHeight = ((h - (getPaddingBottom()+getPaddingTop())) / 24);
    }

    @Override
    protected void onDraw(Canvas canvas){
        float startX;
        float startY = 0;
        canvas.drawColor(Color.BLACK);
        for(int i = 0; i < 24; i++){
            startX = 0;
            for(int j = 0; j < 24; j++){
                canvas.drawLine(startX + cellWidth, startY, startX+cellWidth, startY+cellHeight, linePaint);
                canvas.drawLine(startX, startY+cellHeight, startX+cellWidth, startY+cellHeight, linePaint);
                if(ledMatrix[i][j]){
                    canvas.drawRect(startX,startY,
                            (startX+cellWidth),(startY+cellHeight),squarePaint);
                }
                startX += cellWidth;
            }
            startY += cellHeight;
        }
        canvas.drawLine(0,0,selfWidth,0,linePaint);
        canvas.drawLine(0,0,0,selfHeight,linePaint);
        canvas.drawLine(0,selfHeight,selfWidth,selfHeight,linePaint);
        canvas.drawLine(selfWidth,0,selfWidth,selfHeight,linePaint);
    }

    public void saveFrame(View view){
        frames.add(ledMatrix);
    }

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

    public boolean getLed(int x, int y){
        return ledMatrix[x][y];
    }

    public Vector<boolean[][]> getFrames(){
        return frames;
    }

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
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        float touchX = event.getX();
        float touchY = event.getY();
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
            case MotionEvent.ACTION_MOVE:
            //case MotionEvent.ACTION_UP:
                toggleLed((int)touchX/23, (int)touchY/23);
                break;
            default:
                return false;
        }
        invalidate();
        try {
           if(arduinoThread != null) arduinoThread.sendLed((int) touchX / 23, (int) touchY / 23,
                   getLed((int) touchX / 23, (int) touchY / 23));
        } catch (IOException e) {
            e.printStackTrace();
        }
        return true;
    }

    public void setThread(PongServer thread){
        arduinoThread = thread;
    }
}
