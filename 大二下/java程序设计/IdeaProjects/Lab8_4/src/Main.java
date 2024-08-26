import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入一个整数:");
        int n = scanner.nextInt();
        double sqrt_n=Math.sqrt(n);
        Set<Integer> set = new HashSet<>();
        for(int i=2;i<=sqrt_n;i++){
            while(n%i==0){
                set.add(i);
                n=n/i;
            }
        }
        if(set.size()==0)System.out.println("该数是质数!");
        else{
            System.out.println("该数不是质数，质因子:");
            for(int i:set)System.out.print(" "+i);
        }
    }
}