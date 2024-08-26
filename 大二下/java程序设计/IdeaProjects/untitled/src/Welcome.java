import java.util.Scanner;//声明Scanner类变量
public class Welcome {//Welcome类
    public static void main(String[] args) {//main方法
        Scanner input = new Scanner(System.in);
        System.out.print("Hello");//第一种输出方式
        System.out.println(" world!");//第二种输出方式
        int a = input.nextInt();//第一种输入方式
        a=a*a;
        System.out.printf("%d%n", a);//第三种输出方式
        String b = input.next();//第二种输入方式
        System.out.println(b);
    }
}