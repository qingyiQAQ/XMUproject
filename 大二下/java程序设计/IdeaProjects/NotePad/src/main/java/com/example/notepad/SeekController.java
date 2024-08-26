package com.example.notepad;

import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TextField;
import javafx.scene.control.TitledPane;

public class SeekController {
    @FXML
    public TitledPane replacePane;
    @FXML
    public TextField seekText;
    @FXML
    public TextField replaceText;
    public int currentIndex = 0;
    public int index = -1;
    public NotepadController notepadController = NotepadApplication.notepadLoader.getController();
    public void initialize() {
    }
    @FXML
    public void seekPressed(){
        int indexAll = 0,findSuccess = -1;
        String text = notepadController.textArea.getText();
        String target = seekText.getText();
        while(-1!=text.indexOf(target,indexAll)){
            findSuccess ++;
            indexAll +=seekText.getText().length();
        }
        if(findSuccess==-1) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setContentText("未找到\""+seekText.getText()+"\"");
            alert.showAndWait();
            return;
        }
        currentIndex = notepadController.textArea.getCaretPosition();
        index = text.indexOf(target,currentIndex);
        if (index >= 0) {
            notepadController.textArea.selectRange(index, index + target.length());
        }
        else{
            currentIndex = 0;
            index = text.indexOf(target,currentIndex);
            notepadController.textArea.selectRange(index, index + target.length());
        }
        currentIndex = notepadController.textArea.getCaretPosition();
    }
    @FXML
    public void seekPrevPressed(){
        int indexAll = 0,findSuccess = -1;
        String text = notepadController.textArea.getText();
        String target = seekText.getText();
        while(-1!=text.indexOf(target,indexAll)){
            findSuccess ++;
            indexAll +=seekText.getText().length();
        }
        if(findSuccess==-1) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setContentText("未找到\""+seekText.getText()+"\"");
            alert.showAndWait();
            return;
        }
        currentIndex = notepadController.textArea.getCaretPosition() - 2*target.length();
        index = text.lastIndexOf(target,currentIndex);
        if (index >= 0) {
            notepadController.textArea.selectRange(index, index + target.length());
        }
        else{
            currentIndex = notepadController.textArea.getLength() - 1;
            index = text.lastIndexOf(target,currentIndex);
            notepadController.textArea.selectRange(index, index + target.length());
        }
        currentIndex = notepadController.textArea.getCaretPosition() - 2*target.length();
    }
    @FXML
    public void seekNextPressed(){
        seekPressed();
    }
    @FXML
    public void replacePressed(){
        if(!replaceText.getText().equals("")){
            if(notepadController.textArea.getSelectedText().equals(""))seekPressed();
            else {
                notepadController.textArea.replaceSelection(replaceText.getText());
                seekPressed();
            }
        }
    }
    @FXML
    public void replaceAllPressed(){
        if(!replaceText.getText().equals("")) {
            int indexAll = 0, findSuccess = -1;
            int replaceIndex = 0;
            String text = notepadController.textArea.getText();
            String target = seekText.getText();
            while (-1 != text.indexOf(target, indexAll)) {
                findSuccess++;
                indexAll += seekText.getText().length();
            }
            if (findSuccess == -1) {
                Alert alert = new Alert(Alert.AlertType.WARNING);
                alert.setContentText("未找到\"" + seekText.getText() + "\"");
                alert.showAndWait();
                return;
            }
            while (-1 != text.indexOf(target, replaceIndex)) {
                int index = text.indexOf(target, replaceIndex);
                notepadController.textArea.replaceText(index, index + target.length(), replaceText.getText());
                replaceIndex += replaceText.getText().length();
            }
        }
    }
}
