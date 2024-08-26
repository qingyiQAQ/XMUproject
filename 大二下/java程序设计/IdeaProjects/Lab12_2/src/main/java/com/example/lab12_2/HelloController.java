package com.example.lab12_2;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.stage.FileChooser;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.Window;
import java.io.*;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Comparator;
import java.util.stream.Collectors;

public class HelloController {
    private static String projectPath = (System.getProperty("user.dir")+"\\src\\main\\resources\\com\\example\\lab12_2\\").replaceAll("\\\\","/");
    private static File data = new File((projectPath + "data.txt"));
    public static FileWriter fileWriter;
    public static boolean is_check = false;
    public static int check_index = 0;
    public static int[] check = new int[100];
    public static int check_result = 0;
    public static String check_name = null;
    public static Alert check_alert;
    private static class Student{
        private String no;
        private String name;
        private String phone;
        private Image image;
        private String email;
        private String image_path;
        public Student(String no, String name, String phone ,String email,String image) throws IOException {
            if(no!=null&&name!=null&&phone!=null&&email!=null&&image!=null){
                this.name = name;
                this.phone = phone;
                this.no = no;
                this.email = email;
                image = image.replaceAll("\\\\","/");
                this.image_path = image;
                File file = new File(image);
                if(file.getName().endsWith(".jpg")) {
                    InputStream inputStream = new FileInputStream(file);
                    this.image = new Image(inputStream);
                    inputStream.close();
                }
                else{
                    Alert alert = new Alert(Alert.AlertType.WARNING);
                    alert.setContentText("文件格式不正确!");
                    alert.showAndWait();
                }
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
    @FXML private Button changeButton;
    @FXML private Button deleteButton;
    @FXML private Button nextButton;
    @FXML private Button previousButton;
    @FXML private ListView infoList;
    private ObservableList<Student> students = FXCollections.observableArrayList();
    private ObservableList<String> info = FXCollections.observableArrayList();
    public void initialize() throws IOException {
        FileReader fileReader = new FileReader(data);
        BufferedReader br = new BufferedReader(fileReader);
        String no = br.readLine();
        String name = br.readLine();
        String phone = br.readLine();
        String email = br.readLine();
        while(no!=null&&name!=null&&phone!=null&&email!=null){
            students.add(new Student(no,name,phone,email,projectPath+"images/" + no + ".jpg"));
            no = br.readLine();
            name = br.readLine();
            phone = br.readLine();
            email = br.readLine();
        }
        listview.setItems(students);
        info.add("学号：");
        info.add("姓名：");
        info.add("联系电话：");
        info.add("邮箱：");
        infoList.setItems(info);
        for(int i=0;i<students.size();i++)check[i]=-1;
    }
    @FXML
    public void onMouseClicked(MouseEvent event) throws IOException {
        Student selectedStudent = (Student) listview.getSelectionModel().getSelectedItem();
        if (selectedStudent != null) {
            listChanged();
        }
    }
    @FXML
    private void newButtonPressed(ActionEvent e) throws IOException {
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
            File newfile = new File(projectPath+"images/" + no + ".jpg");
            FileInputStream fis = new FileInputStream(selectedFile);
            FileOutputStream fos = new FileOutputStream(newfile);
            byte[] buffer = new byte[1024];
            int length;
            while ((length = fis.read(buffer)) > 0) {
                fos.write(buffer, 0, length);
            }
            fis.close();
            fos.close();
            image = newfile.toString().replaceAll("\\\\","/");
            students.add(new Student(no, name, phone, email, image));
            listChanged();
        }
    }
    private void check(){
        is_check=true;
        while(check_index<students.size()){
            if(students.get(check_index).name.equals(check_name)) {
                check[check_result]=check_index;
                check_result++;
            }
            check_index++;
        }
        check_result = 0;
        check_index = 0;
        if(check[0]==-1){
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setContentText("未找到该学生!");
            alert.showAndWait();
            is_check=false;
        }
    }
    @FXML
    private void checkButtonPressed(ActionEvent e){
        TextInputDialog dialog = new TextInputDialog("请输入要查询的学生姓名");
        dialog.setTitle("查询");
        dialog.showAndWait();
        check_name = dialog.getResult();
        check();
        check_alert = new Alert(Alert.AlertType.INFORMATION);
        if(check[0]!=-1) {
            check_alert.setContentText("学号：" + students.get(check[0]).no + "\n姓名：" + students.get(check[0]).name + "\n联系电话：" + students.get(check[0]).phone + "\n邮箱：" + students.get(check[0]).email);
            check_alert.initModality(Modality.NONE);
            check_alert.show();
        }
    }
    @FXML
    private void changeButtonClicked(ActionEvent e) throws IOException {
        int selected = listview.getSelectionModel().getSelectedIndex();
        Dialog dialog = new ChoiceDialog("学号","姓名","电话","邮箱","照片");
        dialog.setTitle("修改");
        dialog.showAndWait();
        if(dialog.getResult().equals("学号")){
            File oldfile = new File(projectPath + "images/" + students.get(selected).no + ".jpg");
            TextInputDialog input = new TextInputDialog("请输入学号");
            input.setTitle("学号");
            input.showAndWait();
            if(input.getResult()!=null) {
                students.get(selected).no = input.getResult();
                File newfile = new File(projectPath + "images/" + students.get(selected).no + ".jpg");
                oldfile.renameTo(newfile);
                listChanged();
            }
        }
        else if(dialog.getResult().equals("姓名")){
            TextInputDialog input = new TextInputDialog("请输入姓名");
            input.setTitle("姓名");
            input.showAndWait();
            if(input.getResult()!=null) {
                students.get(selected).name = input.getResult();
                listChanged();
            }
        }
        else if(dialog.getResult().equals("电话")){
            TextInputDialog input = new TextInputDialog("请输入联系电话");
            input.setTitle("联系电话");
            input.showAndWait();
            if(input.getResult()!=null) {
                students.get(selected).phone = input.getResult();
                listChanged();
            }
        }
        else if(dialog.getResult().equals("邮箱")){
            TextInputDialog input = new TextInputDialog("请输入邮箱");
            input.setTitle("邮箱号");
            input.showAndWait();
            if(input.getResult()!=null) {
                students.get(selected).email = input.getResult();
                listChanged();
            }
        }
        else if(dialog.getResult().equals("照片")){
            FileChooser fileChooser = new FileChooser();
            fileChooser.setTitle("请打开学生照片");
            File selectedFile = fileChooser.showOpenDialog(new Stage());
            if(selectedFile!=null) {
                students.get(selected).image_path = selectedFile.toString().replaceAll("\\\\","/");
                students.get(selected).image = new Image(students.get(selected).image_path);
                listChanged();
            }
        }
        else{
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setContentText("输入不正确!");
            alert.showAndWait();
        }
    }
    @FXML void deleteButtonClicked(ActionEvent e)throws IOException{
        Student selectedStudent = (Student) listview.getSelectionModel().getSelectedItem();
        for(Student s:students){
            if(s.equals(selectedStudent)) {
                students.remove(s);
                listChanged();
                File images = new File(projectPath + "images");
                for(File f:images.listFiles()){
                    if(f.getName().equals(s.no+".jpg")){
                        f.delete();
                        break;
                    }
                }
                break;
            }
        }
    }
    @FXML
    private void previousButtonPressed(ActionEvent e) throws IOException {
        if(!is_check) {
            int selected = listview.getSelectionModel().getSelectedIndex();
            Student selectedStudent = (Student) listview.getSelectionModel().getSelectedItem();
            if (selectedStudent != null) {
                listview.getSelectionModel().select((selected + students.size() - 1) % students.size());
                listChanged();
            } else {
                listview.getSelectionModel().select(0);
                listChanged();
            }
        }
        else{
            if(check_result>=1) {
                check_result--;
                check_alert.setContentText("学号：" + students.get(check[check_result]).no + "\n姓名：" + students.get(check[check_result]).name + "\n联系电话：" + students.get(check[check_result]).phone + "\n邮箱：" + students.get(check[check_result]).email);
                check_alert.show();
            }
            else {
                is_check = false;
                check_result =0;
                for(int i=0;i<students.size();i++)check[i]=-1;
                Alert alert = new Alert(Alert.AlertType.WARNING);
                alert.setContentText("查询结束!");
                alert.showAndWait();
            }
        }
    }
    @FXML
    private void nextButtonPressed(ActionEvent e) throws IOException {
        if(!is_check) {
            int selected = listview.getSelectionModel().getSelectedIndex();
            Student selectedStudent = (Student) listview.getSelectionModel().getSelectedItem();
            if (selectedStudent != null) {
                listview.getSelectionModel().select((selected + 1) % students.size());
                listChanged();
            } else {
                listview.getSelectionModel().select(0);
                listChanged();
            }
        }
        else{
            if(check[check_result+1]!=-1) {
                check_result++;
                check_alert.setContentText("学号：" + students.get(check[check_result]).no + "\n姓名：" + students.get(check[check_result]).name + "\n联系电话：" + students.get(check[check_result]).phone + "\n邮箱：" + students.get(check[check_result]).email);
                check_alert.show();
            }
            else {
                is_check = false;
                check_result = 0;
                for(int i=0;i<students.size();i++)check[i]=-1;
                Alert alert = new Alert(Alert.AlertType.WARNING);
                alert.setContentText("查询结束!");
                alert.showAndWait();
            }
        }
    }
    private void listChanged() throws IOException {
        students = FXCollections.observableList(students.stream().sorted(Comparator.comparing(Student::getNo)).collect(Collectors.toList()));
        listview.setItems(students);
        Student selectedStudent = (Student) listview.getSelectionModel().getSelectedItem();
        fileWriter = new FileWriter(data);
        for(Student student:students){
            fileWriter.write(student.no);
            fileWriter.write("\n");
            fileWriter.write(student.name);
            fileWriter.write("\n");
            fileWriter.write(student.phone);
            fileWriter.write("\n");
            fileWriter.write(student.email);
            fileWriter.write("\n");
        }
        fileWriter.close();
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