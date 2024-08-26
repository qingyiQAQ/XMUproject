
import java.util.HashSet;
import java.util.Set;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Set<String> name = new HashSet<>();
        System.out.println("请输入姓名序列(输入q退出):");
        Scanner scanner = new Scanner(System.in);
        while (true){
            String a = scanner.next();
            if(!a.equals("q")) name.add(a);
            else break;
        }
        System.out.println("删除重复姓名后的序列:");
        for(String a:name){
            System.out.println(a);
        }
    }
}