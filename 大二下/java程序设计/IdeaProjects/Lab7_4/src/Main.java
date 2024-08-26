import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IllegaNameException, IllegalAddressException {
        Student student = new Student();
        input_name(student);
        System.out.println("学生姓名为："+student.name);
        input_address(student);
        System.out.println("学生地址为："+student.address);
    }
    static void input_name(Student student) throws IllegaNameException {
        Scanner scanner = new Scanner(System.in);
        try {
            System.out.println("请输入学生姓名：");
            student.setName(scanner.next());
        } catch (IllegaNameException e) {
            System.err.println("请重新输入姓名!");
            input_name(student);
        }
    }
    static void input_address(Student student) throws IllegalAddressException {
        Scanner scanner = new Scanner(System.in);
        try {
            System.out.println("请输入学生地址：");
            student.setAddress(scanner.next());
        } catch (IllegalAddressException e) {
            System.err.println("请重新输入地址!");
            input_address(student);
        }
    }
}
class Student{
    String name;
    String address;
    void setName(String name) throws IllegaNameException {
        if(name.length()<1||name.length()>5)throw new IllegaNameException();
        else this.name=name;
    }
    void setAddress(String address) throws IllegalAddressException {
        if(!address.contains("省")||!address.contains("市"))throw new IllegalAddressException();
        else this.address=address;
    }
}
class IllegaNameException extends Exception{
    public String getMessage(){
        return "姓名长度必须在1~5之间";
    }
}
class IllegalAddressException extends Exception{
    public String getMessage(){
        return "地址必须包含省或市";
    }
}