package com.example.exam2;

import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
class Health{
    String no;
    String weight;
    String muscle;
    String body_fat_rate;
    String save_path;
    Health(String no,String weight,String muscle,String body_fat_rate,String save_path){
        this.no = no;
        this.weight = weight;
        this.muscle = muscle;
        this.body_fat_rate = body_fat_rate;
        this.save_path = save_path;
    }
}

public class HelloController {
    public List<Health> user_health = new ArrayList<>();
    @FXML
    public TextField TextInput1;
    @FXML
    public TextField TextInput2;
    @FXML
    public TextField TextInput3;
    @FXML
    public TextField TextInput4;
    @FXML
    public TextField User_no;
    @FXML
    public TextArea TextArea;
    public void initialize(){

    }
    @FXML
    private void OnSaveButtonPressed()  {
        int count=0;
        for(Health h:user_health){
            if(h.no.equals(TextInput1.getText())){
                try {
                    File file = new File(h.save_path);
                    FileWriter fw = new FileWriter(file);
                    BufferedWriter bw = new BufferedWriter(fw);
                    h.weight=TextInput2.getText();
                    h.muscle=TextInput3.getText();
                    h.body_fat_rate=TextInput4.getText();
                    bw.write("会员编号:" + "NO."+TextInput1.getText());
                    bw.write("体重:" + TextInput2.getText()+"kg");
                    bw.write("肌肉:" + TextInput3.getText()+"kg");
                    bw.write("体脂百分比:" + TextInput4.getText()+"%");
                    bw.close();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            else count++;
        }
        if(count==user_health.size()) {
            FileChooser fileChooser = new FileChooser();
            List<FileChooser.ExtensionFilter> extensionFilters = fileChooser.getExtensionFilters();
            FileChooser.ExtensionFilter textFilter = new FileChooser.ExtensionFilter("Text files (*.txt)", "*.txt");
            extensionFilters.add(textFilter);
            File file = fileChooser.showSaveDialog(new Stage());
            if (file != null) {
                try {
                    FileWriter fw = new FileWriter(file);
                    BufferedWriter bw = new BufferedWriter(fw);
                    Health h = new Health(TextInput1.getText(),TextInput2.getText(),TextInput3.getText(),TextInput4.getText(),file.getPath().replaceAll("\\\\","/"));
                    user_health.add(h);
                    bw.write("会员编号:" + "NO."+TextInput1.getText()+"\n");
                    bw.write("体重:" + TextInput2.getText()+"kg\n");
                    bw.write("肌肉:" + TextInput3.getText()+"kg\n");
                    bw.write("体脂百分比:" + TextInput4.getText()+"%\n");
                    bw.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
    @FXML
    public void Analysis(){
        int reach_num = 0;
        boolean weight_reach ,muscle_reach,fat_reach;
        if(User_no.getText()!=null){
            for(Health h:user_health){
                if(h.no.equals(User_no.getText())){
                    if(Double.parseDouble(h.weight)>=65.5&&Double.parseDouble(h.weight)<=80.1){reach_num++;weight_reach=true;}
                    else weight_reach = false;
                    if(Double.parseDouble(h.muscle)>=52.5&&Double.parseDouble(h.muscle)<=63.6){reach_num++;muscle_reach=true;}
                    else muscle_reach = false;
                    if(Double.parseDouble(h.body_fat_rate)>=10&&Double.parseDouble(h.body_fat_rate)<=20){reach_num++;fat_reach=true;}
                    else fat_reach = false;
                    String s;
                    s="所有项达标的次数"+reach_num+"\n"+"存在不达标项的次数"+(3-reach_num)+"\n"+"所有存在不达标的数据记录:";
                    if(!weight_reach)s+="体重/";
                    if(!muscle_reach)s+="肌肉/";
                    if(!fat_reach)s+="体脂百分比";
                    TextArea.setText(s);
                }
            }
        }
    }
}