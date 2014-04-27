package com.ledpong.LEDPongController;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;

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

    public AnimatorCanvas(Context context) {
        super(context);
        ledMatrix = new boolean[24][24];
        linePaint = new Paint();
        linePaint.setColor(Color.CYAN);
        this.clearFrame(null);
    }

    public AnimatorCanvas(Context context, AttributeSet attributeSet) {
        super(context, attributeSet);
        ledMatrix = new boolean[24][24];
        linePaint = new Paint();
        linePaint.setColor(Color.CYAN);
        this.clearFrame(null);
    }

    public AnimatorCanvas(Context context, AttributeSet attributeSet, int defStyle) {
        super(context, attributeSet, defStyle);
        ledMatrix = new boolean[24][24];
        linePaint = new Paint();
        linePaint.setColor(Color.CYAN);
        this.clearFrame(null);
    }


    @Override
    protected void onSizeChanged(int w, int h, int oldh, int oldw){
        cellWidth = ((w - (getPaddingLeft()+getPaddingRight())) / 24);
        cellHeight = ((h - (getPaddingBottom()+getPaddingTop())) / 24);
    }

    @Override
    protected void onDraw(Canvas canvas){
        float startX = 0;
        float startY = 0;
        for(int i = 0; i < 24; i++){
            startX = 0;
            for(int j = 0; j < 24; j++){
                canvas.drawLine(startX + cellWidth, startY, startX+cellWidth, startY+cellHeight, linePaint);
                canvas.drawLine(startX, startY+cellHeight, startX+cellWidth, startY+cellHeight, linePaint);
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

    public void clearFrame(View view){
        for(boolean[] boolList : ledMatrix){
            for(boolean bool : boolList){
                bool = false;
            }
        }
    }
}
