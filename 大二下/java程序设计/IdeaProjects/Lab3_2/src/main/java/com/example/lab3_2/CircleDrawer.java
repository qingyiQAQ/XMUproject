package com.example.lab3_2;
import java.awt.Color;
import java.awt.Graphics;
import java.util.Random;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class CircleDrawer {

    public static void main(String[] args) {
        JFrame frame = new JFrame("Circle Drawer");//标题设置为”Circle Drawer”
        frame.setSize(500, 500);//大小设置为500*500
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//关闭时退出
        CirclePanel panel = new CirclePanel();
        frame.add(panel);
        frame.setVisible(true);
    }

    static class CirclePanel extends JPanel {

        @Override
        protected void paintComponent(Graphics g) {//新建一个JPanel面板类CirclePanel，并在其中重写paintComponent方法，传入Graphics对象，用于绘制圆
            super.paintComponent(g);
            // 设置颜色和大小的随机数生成器
            Random rand = new Random();
            for (int i = 0; i < 10; i++) {
                int x = rand.nextInt(getWidth() - 50); // 圆心横坐标
                int y = rand.nextInt(getHeight() - 50); // 圆心纵坐标
                int size = rand.nextInt(100) + 10; // 圆的直径
                Color color = generateColor(rand); // 生成颜色
                g.setColor(color);//边缘颜色
                g.fillOval(x, y, size, size);//填充颜色
            }
        }

        public Color generateColor(Random rand) {
            // 生成不同颜色
            int r = rand.nextInt(255);
            int g = rand.nextInt(255);
            int b = rand.nextInt(255);
            Color color = new Color(r, g, b);
            return color;
        }
    }
}