package com.example.lab11_1;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import javafx.stage.Window;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Comparator;
import java.util.stream.Collectors;

public class HelloController {
    private static class Student{
        private String no;
        private String name;
        private String phone;
        private Image image;
        private String email;
        public Student(String no, String name, String phone ,String image,String email) throws FileNotFoundException {
            this.name = name;
            this.phone = phone;
            this.no = no;
            this.email = email;
            if(image!=null){
                File file = new File(image);
                InputStream inputStream = new FileInputStream(file);
                this.image = new Image(inputStream);
            }
        }
        @Override
        public String toString() {
            return this.no+" "+this.name;
        }
        public int getNo(){
            return Integer.parseInt(this.no);
        }
    }
    @FXML private ListView listview;
    @FXML private ImageView imageview;
    @FXML private Button newButton;
    @FXML private Button checkButton;
    @FXML private Button nextButton;
    @FXML private Button previousButton;
    @FXML private ListView infoList;
    private ObservableList<Student> students = FXCollections.observableArrayList();
    private ObservableList<String> info = FXCollections.observableArrayList();
    public void initialize() throws FileNotFoundException {
        students.add(new Student("001","张三","186","C:/Users/CC507/ideaProjects/Lab11_1/src/main/resources/com/example/lab11_1/1.jpg","001@qq.com"));
        students.add(new Student("002","李四","187","C:/Users/CC507/IdeaProjects/Lab11_1/src/main/resources/com/example/lab11_1/2.jpg","002@qq.com"));
        students.add(new Student("003","王五","188","C:/Users/CC507/IdeaProjects/Lab11_1/src/main/resources/com/example/lab11_1/3.jpg","003@qq.com"));
        listview.setItems(students);
        info.add("学号：");
        info.add("姓名：");
        info.add("联系电话：");
        info.add("邮箱：");
        infoList.setItems(info);
    }
    @FXML
    public void onMouseClicked(MouseEvent event){
        Student selectedStudent = (Student) listview.getSelectionModel().getSelectedItem();
        if (selectedStudent != null) {
            listChanged();
        }
    }
    @FXML
    private void newButtonPressed(ActionEvent e) throws FileNotFoundException {
        String no,name,phone,email,image;
        TextInputDialog dialog = new TextInputDialog("请输入学号");
        dialog.setTitle("学号");
        dialog.showAndWait();
        no = dialog.getResult();
        dialog = new TextInputDialog("请输入姓名");
        dialog.setTitle("姓名");
        dialog.showAndWait();
        name = dialog.getResult();
        dialog = new TextInputDialog("请输入联系电话");
        dialog.setTitle("联系电话");
        dialog.showAndWait();
        phone = dialog.getResult();
        dialog = new TextInputDialog("请输入邮箱");
        dialog.setTitle("邮箱");
        dialog.showAndWait();
        email = dialog.getResult();
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("请打开学生照片");
        File selectedFile = fileChooser.showOpenDialog(new Stage());
        if(no!=null&&name!=null&phone!=null&&email!=null&&selectedFile!=null) {
            image = selectedFile.toString().replaceAll("\\\\","/");
            students.add(new Student(no, name, phone, image, email));
            listChanged();
        }
    }
    @FXML
    private void checkButtonPressed(ActionEvent e){
        TextInputDialog dialog = new TextInputDialog("请输入要查询的学生姓名");
        dialog.setTitle("查询");
        dialog.showAndWait();
        String name = dialog.getResult();
        int index=0;
        for(Student a:students){
            if(!a.name.equals(name))index++;
            else break;
        }
        if(index==students.size()){
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setContentText("未找到该学生!");
            alert.showAndWait();
        }
        else {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setContentText("学号：" + students.get(index).no + "\n姓名：" + students.get(index).name + "\n联系电话：" + students.get(index).phone + "\n邮箱：" + students.get(index).email);
            alert.showAndWait();
        }
    }
    @FXML
    private void previousButtonPressed(ActionEvent e){
        int selected = listview.getSelectionModel().getSelectedIndex();
        Student selectedStudent = (Student) listview.getSelectionModel().getSelectedItem();
        if (selectedStudent != null) {
            listview.getSelectionModel().select((selected+students.size()-1)%students.size());
            listChanged();
        }
        else {
            listview.getSelectionModel().select(0);
            listChanged();
        }
    }
    @FXML
    private void nextButtonPressed(ActionEvent e){
        int selected = listview.getSelectionModel().getSelectedIndex();
        Student selectedStudent = (Student) listview.getSelectionModel().getSelectedItem();
        if (selectedStudent != null) {
            listview.getSelectionModel().select((selected+1)%students.size());
            listChanged();
        }
        else {
            listview.getSelectionModel().select(0);
            listChanged();
        }
    }
    private void listChanged(){
        students = FXCollections.observableList(students.stream().sorted(Comparator.comparing(Student::getNo)).collect(Collectors.toList()));
        listview.setItems(students);
        Student selectedStudent = (Student) listview.getSelectionModel().getSelectedItem();
        if(selectedStudent!=null) {
            imageview.setImage(selectedStudent.image);
            info.set(0, "学号：" + selectedStudent.no);
            info.set(1, "姓名：" + selectedStudent.name);
            info.set(2, "联系电话：" + selectedStudent.phone);
            info.set(3, "邮箱：" + selectedStudent.email);
            infoList.setItems(info);
        }
    }
}