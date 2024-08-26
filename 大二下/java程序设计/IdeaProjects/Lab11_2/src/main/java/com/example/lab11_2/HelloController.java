package com.example.lab11_2;

import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class HelloController {
    @FXML private ImageView imageview;
    @FXML private AnchorPane anchorPane;
    private boolean isBlack = true;
    private int[][] put;
    public void initialize() {
        Image image = new Image(getClass().getResourceAsStream("棋盘.jpg"));
        imageview.setImage(image);
        put = new int[15][15];
    }
    @FXML
    private void onMouseClicked(MouseEvent e){
        if(isBlack) {
            if(getIndex(e.getX())>=0&&getIndex(e.getX())<=14&&getIndex(e.getY())>=0&&getIndex(e.getY())<=14&&put[getIndex(e.getX())][getIndex(e.getY())]==0) {
                Circle newCircle = new Circle(position(e.getX()), position(e.getY()), 16, Color.BLACK);
                anchorPane.getChildren().add(newCircle);
                isBlack = false;
                put[getIndex(e.getX())][getIndex(e.getY())] = 1;
            }
        }
        else {
            if(getIndex(e.getX())>=0&&getIndex(e.getX())<=14&&getIndex(e.getY())>=0&&getIndex(e.getY())<=14&&put[getIndex(e.getX())][getIndex(e.getY())]==0) {
                Circle newCircle = new Circle(position(e.getX()), position(e.getY()), 16, Color.WHITE);
                anchorPane.getChildren().add(newCircle);
                isBlack = true;
                put[getIndex(e.getX())][getIndex(e.getY())] = 1;
            }
        }
    }
    private double position(double a){
        int b = 32 , c=25;
        a-=c;
        if(a%b>b/2)return (int)a/b*b+b+c;
        else return (int)a/b*b+c;
    }
    private int getIndex(double a){
        int b = 32 , c=25;
        a-=c;
        if(a%b>b/2)return (int)a/b+1;
        else return (int)a/b;
    }
}