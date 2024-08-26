
import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner scanner=new Scanner(System.in);
        int n=Integer.parseInt(scanner.nextLine());//读取图形个数
        int area[] = new int[n];//面积数组，用于储存结果
        for(int i=0;i<n;i++){
            String line = scanner.nextLine();//读取一行数据
            String[] numsStr = line.split("\\s+");//去除数据中的空格和回车字符，并转化为字符串数组
            int count = numsStr.length;//获得该字符串数组的长度
            int[] array = new int[count];
            for (int j = 0; j < count; j++) {
                array[j] = Integer.parseInt(numsStr[j]);
            }//将字符串数组转化为整数数组
            if(count==2){
                Rectangle rectangle = new Rectangle(array[0],array[1]);
                area[i]=rectangle.area();
            }//若数组长度为2则按照矩形处理
            if(count==3){
                Triangle triangle = new Triangle(array[0],array[1],array[2]);
                area[i]=triangle.area();
            }//若数组长度为3则按照三角形处理
        }
        for(int i=0;i<n;i++){
            System.out.println(area[i]);
        }//输出结果
    }
}
class Graph{
    int area(){
        return 0;
    }
}//图形类
class Triangle extends Graph{
    int a;
    int b;
    int c;
    Triangle(int a,int b,int c){
        this.a=a;
        this.b=b;
        this.c=c;
    }
    @Override
    int area(){
        double p=(a+b+c)/2;
        return (int)Math.sqrt(p*(p-a)*(p-b)*(p-c));
    }//利用海伦公式计算面积
}//继承于图形类的三角形类
class Rectangle extends Graph{
    int width;
    int height;
    Rectangle(int width,int height){
        this.width=width;
        this.height=height;
    }
    @Override
    int area(){
        return width*height;
    }//重写面积计算函数
}//继承于图形类的矩形类