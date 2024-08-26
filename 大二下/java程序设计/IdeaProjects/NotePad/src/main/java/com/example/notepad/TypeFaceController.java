package com.example.notepad;

import javafx.fxml.FXML;
import javafx.scene.control.MenuButton;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TextArea;
import javafx.scene.text.Font;
import javafx.scene.text.FontPosture;
import javafx.scene.text.FontWeight;
import javafx.stage.Stage;

import java.text.NumberFormat;

public class TypeFaceController {
    @FXML
    public TextArea textArea;
    @FXML
    public MenuButton typeFaceButton,patternButton,scaleButton;
    public int scale = 12;
    public String fontType = "SansSerif";
    public FontWeight fontWeight = FontWeight.NORMAL;
    public FontPosture fontPosture = FontPosture.REGULAR;
    public NotepadController notepadController = NotepadApplication.notepadLoader.getController();
    public void initialize() {
        for(int i=0;i<Font.getFamilies().size();i++){
            MenuItem newItem = new MenuItem(Font.getFamilies().get(i));
            typeFaceButton.getItems().add(newItem);
            newItem.setOnAction(e->{
                fontType = newItem.getText();
                textArea.setFont(Font.font(fontType,fontWeight,fontPosture,scale));
                typeFaceButton.setText(fontType);
            });
        }
        for(int i=1;i<=36;i++){
            MenuItem newItem = new MenuItem(i+"");
            scaleButton.getItems().add(newItem);
            int finalI = i;
            newItem.setOnAction(e->{
                textArea.setFont(Font.font(fontType,fontWeight,fontPosture,finalI));
                scaleButton.setText(finalI+"");
                scale=finalI;
            });
        }
        MenuItem style0 = new MenuItem("常规");
        style0.setOnAction(e->{
            fontWeight = FontWeight.NORMAL;
            fontPosture = FontPosture.REGULAR;
            textArea.setFont(Font.font(fontType,fontWeight,fontPosture,scale));
            patternButton.setText("常规");
        });
        MenuItem style1 = new MenuItem("斜体");
        style1.setOnAction(e->{
            fontWeight = FontWeight.NORMAL;
            fontPosture = FontPosture.ITALIC;
            textArea.setFont(Font.font(fontType,fontWeight,fontPosture,scale));
            patternButton.setText("斜体");
        });
        MenuItem style2 = new MenuItem("粗体");
        style2.setOnAction(e->{
            fontWeight = FontWeight.BOLD;
            fontPosture = FontPosture.REGULAR;
            textArea.setFont(Font.font(fontType,fontWeight,fontPosture,scale));
            patternButton.setText("粗体");
        });
        MenuItem style3 = new MenuItem("细体");
        style3.setOnAction(e->{
            fontWeight = FontWeight.LIGHT;
            fontPosture = FontPosture.REGULAR;
            textArea.setFont(Font.font(fontType,fontWeight,fontPosture,scale));
            patternButton.setText("细体");
        });
        MenuItem style4 = new MenuItem("极粗体");
        style4.setOnAction(e->{
            fontWeight = FontWeight.EXTRA_BOLD;
            fontPosture = FontPosture.REGULAR;
            textArea.setFont(Font.font(fontType,fontWeight,fontPosture,scale));
            patternButton.setText("极粗体");
        });
        MenuItem style5 = new MenuItem("粗斜体");
        style5.setOnAction(e->{
            fontWeight = FontWeight.BOLD;
            fontPosture = FontPosture.ITALIC;
            textArea.setFont(Font.font(fontType,fontWeight,fontPosture,scale));
            patternButton.setText("粗斜体");
        });
        MenuItem style6 = new MenuItem("细斜体");
        style6.setOnAction(e->{
            fontWeight = FontWeight.LIGHT;
            fontPosture = FontPosture.ITALIC;
            textArea.setFont(Font.font(fontType,fontWeight,fontPosture,scale));
            patternButton.setText("细斜体");
        });
        MenuItem style7 = new MenuItem("极粗斜体");
        style7.setOnAction(e->{
            fontWeight = FontWeight.EXTRA_BOLD;
            fontPosture = FontPosture.ITALIC;
            textArea.setFont(Font.font(fontType,fontWeight,fontPosture,scale));
            patternButton.setText("极粗斜体");
        });
        patternButton.getItems().addAll(style0,style1,style2,style3,style4,style5,style6,style7);
    }
    @FXML
    public void ensureButtonPressed(){
        notepadController.textArea.setFont(Font.font(fontType,fontWeight,fontPosture,scale));
        notepadController.scaleText.setText((int)(textArea.getFont().getSize()/12*100)+"%");
        Stage stage = (Stage)textArea.getScene().getWindow();
        stage.close();
    }
}
