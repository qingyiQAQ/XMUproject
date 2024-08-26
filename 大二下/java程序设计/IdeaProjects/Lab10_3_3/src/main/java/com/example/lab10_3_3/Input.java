package com.example.lab10_3_3;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.StackPane;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import java.io.IOException;

public class Input extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        Text title = new Text("注册账号");
        TextField name = new TextField("请输入用户名");
        TextField password = new TextField("请输入密码");
        TextField password_confirm = new TextField("请确认密码");
        Button button = new Button("确定");
        button.setOnAction(event -> {
            if(name.getText().length()<4)
                new Alert(Alert.AlertType.ERROR, "用户名长度不得小于4!").showAndWait();
            if(!password.getText().equals(password_confirm.getText()))
                new Alert(Alert.AlertType.ERROR, "两次输入的密码必须相同!").showAndWait();
        });
        StackPane.setMargin(name, new Insets(-100, 0, 0, 0));
        StackPane.setMargin(password, new Insets(-50, 0, 0, 0));
        StackPane.setMargin(title, new Insets(-180, 0, 0, 0));
        StackPane.setMargin(button, new Insets(100, 0, 0, 0));
        StackPane pane = new StackPane(name,password,password_confirm,title,button);
        Scene scene = new Scene(pane, 300, 200);
        stage.setTitle("Hello!");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}