package com.example.notepad;

import javafx.fxml.FXML;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import java.io.IOException;

public class SaveController {
    @FXML
    public Text saveText;
    public NotepadController notepadController;
    public void initialize() throws IOException {
        notepadController = NotepadApplication.notepadLoader.getController();
        if(notepadController.filePath!=null)saveText.setText("是否将文件保存到:"+ notepadController.filePath+"?");
        else saveText.setText("是否保存文件?");
    }
    @FXML
    public void saveSavePressed(){
        notepadController.savePressed();
        Stage stage = (Stage) saveText.getScene().getWindow();
        while(notepadController.filePath!=null&&stage.isShowing()){
            saveNotSavePressed();
        }
    }
    @FXML
    public void saveNotSavePressed(){
        notepadController.quit();
    }
    @FXML
    public void saveCancelPressed(){
        Stage stage = (Stage) saveText.getScene().getWindow();
        stage.close();
    }
}
