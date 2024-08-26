import java.util.*;
import java.util.regex.Pattern;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入用户名:");
        String name = scanner.next();
        Pattern PATTERN = Pattern.compile("^[a-zA-Z_][a-zA-Z0-9_]+$");
        while(!PATTERN.matcher(name).matches()){
            if(name.charAt(0)>='0'&&name.charAt(0)<='9')System.err.println("姓名首字母不能以数字开头!");
            if(!name.matches("^[a-zA-Z0-9_]+$"))System.err.println("姓名不能包含除字母数字下划线以外的字符!");
            if(name.length()==0)System.err.println("姓名不能为空!");
            System.err.println("请重新输入:");
            name = scanner.next();
        }
        System.out.println("请输入密码:");
        String password = scanner.next();
        PATTERN = Pattern.compile("^[a-zA-Z0-9_]+$");
        while(!PATTERN.matcher(password).matches()||password.length()<8){
            if(password.length()<8)System.err.println("密码至少为8位!");
            if(!PATTERN.matcher(password).matches())System.err.println("密码只能由字母数字下划线组成!");
            if(password.length()==0)System.err.println("密码不能为空!");
            System.err.println("请重新输入:");
            password = scanner.next();
        }
        System.out.println("请输入邮箱:");
        String email = scanner.next();
        PATTERN = Pattern.compile("^.+@[a-zA-Z0-9_]+(\\.[a-zA-Z0-9_]+)*$");
        while(!PATTERN.matcher(email).matches()){
            if(!email.contains("@"))System.err.println("邮箱必须包含\"@\"符号!");
            else if(!email.contains("."))System.err.println("邮箱必须包含\".\"符号!");
            else System.err.println("邮箱中\"@\"前非空，\"@\"后只能由字母数字和\".\"组成且\".\"的前后都非空!");
            if(email.length()==0)System.err.println("姓名不能为空!");
            System.err.println("请重新输入:");
            email = scanner.next();
        }
    }
}