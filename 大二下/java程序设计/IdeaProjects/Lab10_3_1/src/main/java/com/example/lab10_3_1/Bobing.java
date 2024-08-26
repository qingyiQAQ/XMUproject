package com.example.lab10_3_1;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.StackPane;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.geometry.Insets;
import java.io.IOException;
import java.util.Random;

public class Bobing extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        Button start = new Button("开始博饼");
        Text text1 = new Text();
        Text text2 = new Text();
        start.setOnAction(event -> {
            String result="结果为:";
            Random random = new Random();
            int a[]=new int[6];
            int count=0;
            for(int n:a){
                n=random.nextInt(6)+1;
                result+=n+" ";
                if(n==4)count++;
            }
            text1.setText(result);
            switch(count){
                case 0:text2.setText("无奖项");break;
                case 1:text2.setText("一秀");break;
                case 2:text2.setText("二举");break;
                case 3:text2.setText("三红");break;
                case 4:text2.setText("状元");break;
            }
        });
        StackPane pane = new StackPane();
        pane.getChildren().add(start);
        pane.getChildren().add(text1);
        pane.getChildren().add(text2);
        StackPane.setMargin(start, new Insets(-50, 0, 0, 0));
        StackPane.setMargin(text2, new Insets(50, 0, 0, 0));
        Scene scene = new Scene(pane, 200,200 );
        stage.setTitle("博饼");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}