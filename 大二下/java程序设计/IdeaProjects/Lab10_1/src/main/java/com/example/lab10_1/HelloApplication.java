package com.example.lab10_1;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextField;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.scene.control.*;
import javafx.stage.*;
import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        RadioButton button1 = new RadioButton("High");
        RadioButton button2 = new RadioButton("Medium");
        RadioButton button3 = new RadioButton("Low");
        ToggleGroup group = new ToggleGroup();
        button1.setToggleGroup(group);
        button2.setToggleGroup(group);
        button3.setToggleGroup(group);
        TextField name = new TextField("Your name");
        name.setPrefSize(100,0);
        TextField password = new TextField("Your password");
        password.setPrefSize(100,0);
        ComboBox<String> comboBox = new ComboBox<>();
        comboBox.getItems().addAll("English", "Chinese");
        Button accept = new Button("Accept");
        Button decline = new Button("Decline");
        Text text1 = new Text("Not Available");
        CheckBox checked = new CheckBox("Checked");
        CheckBox normal = new CheckBox("Normal");
        CheckBox undefined = new CheckBox("Undefined");
        undefined.setAllowIndeterminate(true);
        Slider slider = new Slider();
        Text text2 = new Text("Progress:");
        RadioButton button = new RadioButton();
        slider.setMin(0);
        slider.setMax(100);
        slider.setValue(50);
        Text text3 = new Text();
        slider.valueProperty().addListener((observable, oldValue, newValue) -> {
            text3.setText((int)(newValue.doubleValue())+"%");
        });
        // 创建一个布局管理器，并将按钮添加到其中
        GridPane grid = new GridPane();
        grid.add(button1,0,0);
        grid.add(button2,0,1);
        grid.add(button3,0,2);
        grid.add(name,1,1);
        grid.add(password,1,2);
        grid.add(comboBox,2,2);
        grid.add(accept,0,3);
        grid.add(decline,1,3);
        grid.add(text1,2,3);
        grid.add(checked,0,4);
        grid.add(normal,1,4);
        grid.add(undefined,2,4);
        grid.add(slider,1,5);
        grid.add(text2,0,5);
        grid.add(button,2,5);
        grid.add(text3,2,6);
        // 创建一个场景，并将布局管理器添加到其中
        Scene scene = new Scene(grid, 300, 250);
        // 将场景设置到主舞台中，并显示舞台
        stage.setTitle("demo");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}