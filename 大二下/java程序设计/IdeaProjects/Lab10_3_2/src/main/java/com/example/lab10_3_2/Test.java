package com.example.lab10_3_2;

import javafx.application.Application;
import javafx.scene.*;
import javafx.stage.Stage;
import javafx.scene.control.*;
import java.io.IOException;
import javafx.scene.layout.StackPane;

public class Test extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        Button button = new Button("显示对话框");
        StackPane pane = new StackPane(button);
        Scene scene = new Scene(pane, 300, 200);
        stage.setTitle("Hello!");
        stage.setScene(scene);
        stage.show();
        button.setOnAction(event -> {
            // 创建多个对话框，并显示出来
            Alert alert1 = new Alert(Alert.AlertType.CONFIRMATION, "确认对话框");
            alert1.showAndWait();
            Alert alert2 = new Alert(Alert.AlertType.INFORMATION, "信息对话框");
            alert2.showAndWait();
            Alert alert3 = new Alert(Alert.AlertType.ERROR, "错误对话框");
            alert3.showAndWait();
            Alert alert4 = new Alert(Alert.AlertType.WARNING, "警告对话框");
            alert4.showAndWait();
            Alert alert5 = new Alert(Alert.AlertType.NONE, "空对话框");
            alert5.showAndWait();
        });
    }

    public static void main(String[] args) {
        launch();
    }
}