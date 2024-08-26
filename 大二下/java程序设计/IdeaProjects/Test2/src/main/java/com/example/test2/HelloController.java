package com.example.test2;

import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.stage.DirectoryChooser;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class HelloController {
    private static final String projectPath = (System.getProperty("user.dir")+"\\src\\main\\resources\\com\\example\\test2\\")
            .replaceAll("\\\\","/");//结果.txt的保存路径
    private static final File resultFile = new File((projectPath + "结果.txt"));//结果.txt的文件本体
    public List<Integer> count = new ArrayList<>(26);//用于计数字母出现次数
    public List<String> file_Path = new ArrayList<>();//用于记录所打开的文件路径+文件名
    public void initialize(){
        for(int i=0;i<=25;i++)count.add(0);//将计数初始化为0
    }
    @FXML
    public TextArea resultText;//显示文字区域
    @FXML
    public void openFile(){
        DirectoryChooser directoryChooser = new DirectoryChooser();
        File file = directoryChooser.showDialog(new Stage());//打开文件夹
        if (file != null) {
            for(File f:file.listFiles()){//对文件夹内所有文件操作
                if(f.getName().endsWith(".txt")){//判断文件是否是txt文件
                    file_Path.add(f.getPath());//添加到读取记录
                    try {
                        FileReader fileReader = new FileReader(f);
                        BufferedReader br = new BufferedReader(fileReader);
                        int a = br.read();//按字节读取文件
                        for(int i=65;i<=90;i++){
                            if(a==i)
                                count.set(i-65,count.get(i-65)+1);
                        }
                        for(int i=97;i<=122;i++){
                            if(a==i)
                                count.set(i-97,count.get(i-97)+1);
                        }//不区分大小写判断读取字母，储存至count的0-25号单元
                        while(a!=-1){
                            a = br.read();
                            for(int i=65;i<=90;i++){
                                if(a==i)
                                count.set(i-65,count.get(i-65)+1);
                            }
                            for(int i=97;i<=122;i++){
                                if(a==i)
                                count.set(i-97,count.get(i-97)+1);
                            }
                        }//循环读取
                        br.close();
                        fileReader.close();//关闭输入流
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        }
        String result = "";
        result+="所统计的文件有:";
        for(String s:file_Path){
            result+=s+"  ";
        }
        result+="\n";//输出读取的文件
        result+="统计结果:\n";
        for(int i=0;i<=25;i++){
            if(count.get(i)!=0) {
                result += (char) (i + 97) + ":";
                result += count.get(i);
                result += "\n";
            }
        }//输出所有字母出现次数
        resultText.setText(result);//显示在文本显示区域中
        try {
            FileWriter fileWriter = new FileWriter(resultFile);
            fileWriter.write(result);
            fileWriter.close();//写入结果.txt
        } catch (IOException e) {
            e.printStackTrace();
        }
        for(int i=0;i<=25;i++)count.set(i,0);//计数器清0便于下一次统计
    }
}