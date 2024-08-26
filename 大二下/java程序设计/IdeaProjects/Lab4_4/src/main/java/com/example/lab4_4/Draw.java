package com.example.lab4_4;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;
import javax.swing.*;

public class Draw extends JPanel implements ActionListener{
    int a,b,c,d,ran;//四个图形基本参数，和一个生成图形的随机数
    static int count=0;//已生成图形计数
    public static void main(String[] args) {
        JFrame frame = new JFrame("Drawer");//标题设置为”Circle Drawer”
        frame.setSize(500, 500);//大小设置为500*500
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//关闭时退出
        Draw a =new Draw();
        frame.getContentPane().add(a);
        frame.setVisible(true);
    }
    public Draw(){
        JButton drawButton = new JButton("绘制");
        drawButton.addActionListener(this);
        add(drawButton);
    }//增加一个绘图按钮
    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        switch(ran){
            case 0:
                g.drawLine(a,b,c,d);
                break;
            case 1:
                g.drawRect(a,b,c,d);
                break;
            case 2:
                g.drawOval(a,b,c,d);
                break;
            default:
                break;
        }
    }//根据随机数绘制三种不同图形
    private int getInput(String prompt, int min, int max){
        String resultString = JOptionPane.showInputDialog(this,prompt);
        int result = Integer.parseInt(resultString);
        while(result < min || result > max){
            resultString = JOptionPane.showInputDialog(this,"Invalid input. " + prompt);
            result = Integer.parseInt(resultString);
        }
        return result;
    }//获取用户输入
    @Override
    public void actionPerformed(ActionEvent e) {
        Random random = new Random();
        ran = random.nextInt(3);
        switch(ran){
            case 0:{
                a=getInput("直线：请输入x1:",0,500);
                b=getInput("直线：请输入y1:",0,500);
                c=getInput("直线：请输入x2:",0,500);
                d=getInput("直线：请输入y2:",0,500);
                count++;
                if(count<=20)repaint();
                else return;
            }break;
            case 1:{
                a=getInput("矩形：请输入x:",0,500);
                b=getInput("矩形：请输入y:",0,500);
                c=getInput("矩形：请输入长度:",0,500);
                d=getInput("矩形：请输入宽度:",0,500);
                count++;
                if(count<=20)repaint();
                else return;
            }break;
            case 2:{
                a=getInput("椭圆：请输入x:",0,500);
                b=getInput("椭圆：请输入y:",0,500);
                c=getInput("椭圆：请输入长轴:",0,500);
                d=getInput("椭圆：请输入短轴:",0,500);
                count++;
                if(count<=20)repaint();
                else return;
            }break;
        }
    }//将用户的输入赋值给a,b,c,d四个参数并调用绘制函数
}