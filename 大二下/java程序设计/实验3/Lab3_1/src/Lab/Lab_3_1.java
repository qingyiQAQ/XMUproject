package Lab;
import java.util.Scanner;
public class Lab_3_1 {

	public static void main(String[] args) {
		int n=0;
		while(n<1000) {
			if(is_prime(n)==true)
				System.out.print(n+" ");
			n++;
		}
	}//主函数
	public static  boolean is_prime(int n) {
		if(n<=1)return false;
		for(int i=2;i<=Math.sqrt(n);i++) {
			if(n%i==0)return false;
		}
		return true;
	}//判断是否为素数的方法
}
