package com.example.notepad;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class NotepadApplication extends Application {
    public static FXMLLoader notepadLoader,saveLoader,seekLoader;
    public static Scene scene;
    @Override
    public void start(Stage stage) throws IOException {
        notepadLoader = new FXMLLoader(NotepadApplication.class.getResource("notepad.fxml"));
        saveLoader = new FXMLLoader(NotepadApplication.class.getResource("save.fxml"));
        seekLoader = new FXMLLoader(NotepadApplication.class.getResource("seek.fxml"));
        scene = new Scene(notepadLoader.load(), 750, 500);
        stage.setTitle("记事本");
        stage.setScene(scene);
        stage.show();
    }
    public static void main(String[] args) {
        launch();
    }
}