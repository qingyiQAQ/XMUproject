package com.example.lab10_3_3;

import javafx.fxml.FXML;
import javafx.scene.control.Label;

public class InputController {
    @FXML
    private Label welcomeText;

    @FXML
    protected void onHelloButtonClick() {
        welcomeText.setText("Welcome to JavaFX Application!");
    }
}