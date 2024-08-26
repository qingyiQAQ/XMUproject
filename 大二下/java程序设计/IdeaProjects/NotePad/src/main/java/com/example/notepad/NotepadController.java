package com.example.notepad;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.scene.transform.Scale;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.Optional;

import static java.lang.System.exit;

public class NotepadController {
    public static String filePath;
    public static String fileContent;
    public static String copyText;
    @FXML
    public TextArea textArea;
    @FXML
    public MenuItem revokeButton,shearButton,copyButton,pasteButton,deleteButton;
    @FXML
    public Text positionText,scaleText;
    @FXML
    public GridPane statusBar;
    @FXML
    public CheckMenuItem statusBarButton,autoWrapButton;

    public void initialize() {
        fileContent = "";
        copyText = "";
        revokeButton.setDisable(true);
        shearButton.setDisable(true);
        copyButton.setDisable(true);
        deleteButton.setDisable(true);
        copyButton.setDisable(true);
        pasteButton.setDisable(true);
        statusBarButton.setSelected(true);
        textArea.setWrapText(true);
        autoWrapButton.setSelected(true);
    }
    public void quit(){
        exit(0);
    }

    /***********************************/
    /*文件菜单：*/
    /***********************************/
    //新建标签页
    @FXML
    public void newTabPressed(){

    }
    //新建窗口
    @FXML
    public void newWindowPressed(){
        FXMLLoader fxmlLoader = new FXMLLoader(NotepadController.class.getResource("notepad.fxml"));
        try {
            Scene scene = new Scene(fxmlLoader.load(), 750, 500);
            Stage stage = new Stage();
            stage.setTitle("记事本");
            stage.setScene(scene);
            stage.show();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
    //打开
    @FXML
    public void openPressed(){
        FileChooser fileChooser = new FileChooser();
        File file = fileChooser.showOpenDialog(new Stage());
        filePath = file.getPath().replaceAll("\\\\","/");
        if(file!=null){
            try {
                FileReader fileReader = new FileReader(file);
                BufferedReader br = new BufferedReader(fileReader);
                String line,s="";
                while ((line = br.readLine()) != null) {
                    s+=line+"\n";
                }
                br.close();
                fileReader.close();
                fileContent = s;
                textArea.setText(s);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }
    //保存
    @FXML
    public void savePressed(){
        if(filePath!=null){
            File file = new File(filePath);
            try {
                FileWriter fileWriter = new FileWriter(file);
                BufferedWriter bw = new BufferedWriter(fileWriter);
                bw.write(textArea.getText());
                bw.close();
                fileWriter.close();
                fileContent = textArea.getText();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        else{
            saveAsPressed();
        }
    }
    //另存为
    @FXML
    public void saveAsPressed(){
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("另存为:");
        List<FileChooser.ExtensionFilter> extensionFilters = fileChooser.getExtensionFilters();
        FileChooser.ExtensionFilter textFilter = new FileChooser.ExtensionFilter("Text files (*.txt)", "*.txt");
        extensionFilters.add(textFilter);
        File file = fileChooser.showSaveDialog(new Stage());
        if(file!=null) {
            try {
                filePath = file.getPath().replaceAll("\\\\", "/");
                FileWriter fileWriter = new FileWriter(file);
                BufferedWriter bw = new BufferedWriter(fileWriter);
                bw.write(textArea.getText());
                bw.close();
                fileWriter.close();
                fileContent = textArea.getText();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }
    //全部保存
    @FXML
    public void saveAllPressed(){
        savePressed();
    }
    //关闭选项卡
    @FXML
    public void closeTabPressed(){
        if(fileContent.equals(textArea.getText())){
            exit(0);
        }
        else{
            Stage stage = new Stage();
            Scene scene = null;
            try {
                FXMLLoader savefxmlLoader = new FXMLLoader(NotepadApplication.class.getResource("save.fxml"));
                scene = new Scene(savefxmlLoader.load(), 300, 200);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            stage.setTitle("记事本");
            stage.setScene(scene);
            stage.show();
        }
    }
    //关闭窗口
    @FXML
    public void closeWindowPressed(){
        closeTabPressed();
    }
    //退出
    @FXML
    public void exitPressed(){
        closeTabPressed();
    }
    /***********************************/
    /*编辑菜单：*/
    /***********************************/
    //撤销
    @FXML
    public void revokePressed(){
        if(textArea.isUndoable()) textArea.undo();
        else revokeButton.setDisable(true);
    }
    //剪切
    @FXML
    public void shearPressed(){
        copyText = textArea.getSelectedText();
        textArea.replaceSelection("");
    }
    //复制
    @FXML
    public void copyPressed(){
        copyText = textArea.getSelectedText();
    }
    //粘贴
    @FXML
    public void pastePressed(){
        textArea.replaceSelection(copyText);
    }
    //删除
    @FXML
    public void deletePressed(){
        textArea.replaceSelection("");
    }
    public SeekController seekController;
    //查找
    @FXML
    public void seekPressed(){
        if(seekController==null||!seekController.replacePane.getScene().getWindow().isShowing()) {
            Stage stage = new Stage();
            Scene scene = null;
            FXMLLoader seekfxmlLoader;
            try {
                seekfxmlLoader = new FXMLLoader(NotepadApplication.class.getResource("seek.fxml"));
                scene = new Scene(seekfxmlLoader.load(), 500, 100);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            stage.setTitle("查找与替换");
            stage.setScene(scene);
            stage.show();
            seekController = seekfxmlLoader.getController();
            seekController.replacePane.setExpanded(false);
        }
        else {
            seekController.seekPressed();
        }
    }
    //查找下一个
    @FXML
    public void seekNextPressed(){
        if(seekController!=null&&seekController.replacePane.getScene().getWindow().isShowing()){
            seekController.seekNextPressed();
        }
        else{
            seekPressed();
        }

    }
    //查找上一个
    @FXML
    public void seekPrevPressed(){
        if(seekController!=null&&seekController.replacePane.getScene().getWindow().isShowing()){
            seekController.seekPrevPressed();
        }
        else{
            seekPressed();
        }
    }
    //替换
    @FXML
    public void replacePressed(){
        if(seekController!=null&&seekController.replacePane.getScene().getWindow().isShowing()){
            seekController.replacePressed();
            seekController.replacePane.setExpanded(true);
        }
        else{
            seekPressed();
            seekController.replacePane.setExpanded(true);
        }
    }
    //转到
    @FXML
    public void gotoPressed(){
        Dialog dialog = new TextInputDialog();
        dialog.setTitle("转到行");
        dialog.setContentText("行号:");
        Optional<String> input = dialog.showAndWait();
        String result = input.get();
        int height = 1,a=0;
        while(a<textArea.getLength()){
            if(textArea.getText().charAt(a)=='\n'){
                height++;
            }
            a++;
        }
        System.out.println(height);
        try{
            int n = Integer.parseInt(result)-1;
            if(n<0||n>height-1){
                Alert alert = new Alert(Alert.AlertType.WARNING);
                alert.setTitle("记事本-GoTo行");
                alert.setContentText("行号超出总行数范围!");
                alert.showAndWait();
                return;
            }
            int index = 0;
            while(n>0){
                if(textArea.getText().charAt(index)=='\n'){
                    n--;
                }
                index++;
            }
            textArea.selectRange(index,index);
        }
        catch (NumberFormatException e){
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("记事本-GoTo行");
            alert.setContentText("输入格式不正确!");
            alert.showAndWait();
        }
    }
    //全选
    @FXML
    public void selectAllPressed(){
        textArea.selectRange(0,textArea.getLength());
    }
    //时间/日期
    @FXML
    public void timeDatePressed(){
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("HH:mm yyyy/MM/dd");
        textArea.replaceSelection(LocalDateTime.now().format(formatter).toString());
    }
    public TypeFaceController typeFaceController;
    //字体
    @FXML
    public void typefacePressed(){
        if(typeFaceController==null||!typeFaceController.textArea.getScene().getWindow().isShowing()) {
            Stage stage = new Stage();
            Scene scene = null;
            FXMLLoader typeFacefxmlLoader;
            try {
                typeFacefxmlLoader = new FXMLLoader(NotepadApplication.class.getResource("typeFace.fxml"));;
                scene = new Scene(typeFacefxmlLoader.load(), 300, 300);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            stage.setTitle("字体与样式");
            stage.setScene(scene);
            stage.show();
            typeFaceController = typeFacefxmlLoader.getController();
        }
    }
    /***********************************/
    /*查看菜单：*/
    /***********************************/
    //放大
    @FXML
    public void enlargePressed(){
        if(typeFaceController!=null){
            if(typeFaceController.scale<36)typeFaceController.scale+=1;
            textArea.setFont(Font.font(typeFaceController.fontType,typeFaceController.fontWeight,typeFaceController.fontPosture,typeFaceController.scale));
        }
        else{
            if(textArea.getFont().getSize()<36)textArea.setFont(Font.font(textArea.getFont().getSize()+1));
        }
        scaleText.setText((int)(textArea.getFont().getSize()/12*100)+"%");
    }
    //缩小
    @FXML
    public void shrinkPressed(){
        if(typeFaceController!=null){
            if(typeFaceController.scale>1)typeFaceController.scale-=1;
            textArea.setFont(Font.font(typeFaceController.fontType,typeFaceController.fontWeight,typeFaceController.fontPosture,typeFaceController.scale));
        }
        else{
            if(textArea.getFont().getSize()>1)textArea.setFont(Font.font(textArea.getFont().getSize()-1));
        }
        scaleText.setText((int)(textArea.getFont().getSize()/12*100)+"%");
    }
    //还原默认缩放
    @FXML
    public void restorePressed(){
        if(typeFaceController!=null){
            typeFaceController.scale=12;
            textArea.setFont(Font.font(typeFaceController.fontType,typeFaceController.fontWeight,typeFaceController.fontPosture,typeFaceController.scale));
        }
        else{
            textArea.setFont(Font.font(12));
        }
        scaleText.setText((int)(textArea.getFont().getSize()/12*100)+"%");
    }
    //状态栏
    @FXML
    public void statusBarPressed(){
        if(statusBar.isVisible()){
            statusBar.setVisible(false);
        }
        else {
            statusBar.setVisible(true);
        }
    }
    //自动换行
    @FXML
    public void autoWrapPressed(){
        if(textArea.isWrapText()){
            textArea.setWrapText(false);
        }
        else{
            textArea.setWrapText(true);
        }
    }
    @FXML
    public void onMenuShowing(){
        if(!textArea.isUndoable())revokeButton.setDisable(true);
        else revokeButton.setDisable(false);
        if(textArea.getSelectedText().equals("")||textArea.getSelectedText()==null){
            shearButton.setDisable(true);
            copyButton.setDisable(true);
            deleteButton.setDisable(true);
        }
        else {
            shearButton.setDisable(false);
            copyButton.setDisable(false);
            deleteButton.setDisable(false);
        }
        if(copyText.equals("")||copyText==null){
            pasteButton.setDisable(true);
        }
        else pasteButton.setDisable(false);
    }
    @FXML
    public void textAreaMouseClicked(){
        int caretPosition_x = textArea.getCaretPosition()+1;
        int caretPosition_y = 1,x_count = 1;
        for(int i=0;i<textArea.getCaretPosition();i++){
            x_count++;
            if(textArea.getText().charAt(i)=='\n'){
                caretPosition_y++;
                caretPosition_x-=(x_count-1);
                x_count = 1;
            }
        }
        positionText.setText("行"+caretPosition_y+"，列"+caretPosition_x);
        scaleText.setText((int)(textArea.getFont().getSize()/12*100)+"%");
    }
    @FXML
    public void textAreaKeyTyped(){
        textAreaMouseClicked();
    }
}