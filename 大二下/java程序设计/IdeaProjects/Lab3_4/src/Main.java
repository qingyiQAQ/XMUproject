import java.util.Random;
import java.util.Scanner;

public class Main {
    static int n=0;//储存回答次数
    static int t=0;//储存回答正确次数
    public static void main(String[] args) {
        make_question();
    }
    public static void make_question(){
        Scanner scanner=new Scanner(System.in);
        Random random=new Random();
        t=0;
        int c=0;//创建c用于获取学生输入
        int a=0;
        int b=0;//创建a,b用于作为乘数和被乘数
        for(n=0;n<10;n++){
            if(c!=a*b){
                random_bad();//若回答错误则随机产生错误评语
                System.out.println("How much is "+a+"times "+b+"?");//重新提问
                c=scanner.nextInt();//重新获得输入
            }
            else{
                if(n!=0)random_good();//若回答正确则产生正确评语
                a=random.nextInt(9)+1;
                b=random.nextInt(9)+1;//随机生成a,b
                System.out.println("How much is "+a+"times "+b+"?");//提出新问题
                c=scanner.nextInt();//获得输入
            }
        }
        if(c!=a*b)random_bad();else random_good();
        double accuracy=(double)t/(double)n*100;
        System.out.println("Your accuracy is "+accuracy+"%!");//计算并输出正确率
        if(accuracy>=75)System.out.println("Congratulations, you are ready to go to the next level!");
        else System.out.println("Please ask your teacher for extra help.");//根据正确率给出输出
        System.out.println("next student!");
        make_question();//重置程序，下一个学生答题
    }
    public static void random_good(){
        Random random=new Random();
        int a=random.nextInt(4)+1;
        switch(a){
            case 1:System.out.println("Very good!");break;
            case 2:System.out.println("Excellent!");break;
            case 3:System.out.println("Nice work!");break;
            case 4:System.out.println("Keep up the good work!");break;
        }
        t++;
    }//随机产生回答正确评语
    public static void random_bad(){
        Random random=new Random();
        int a=random.nextInt(4)+1;
        switch(a){
            case 1:System.out.println("No.Please try again.");break;
            case 2:System.out.println("Wrong. Try once more.");break;
            case 3:System.out.println("Don't give up!");break;
            case 4:System.out.println("No. Keep trying.");break;
        }
    }//随机产生回答错误评语
}