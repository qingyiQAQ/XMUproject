import java.util.InputMismatchException;
import java.util.Scanner;
public class Main {
    static int vehicle_num=0;
    static vehicle v[] = new vehicle[100];
    public static void main(String[] args) {
        menu();
    }
    static void menu(){
        int n;
        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入对应输入进行相应菜单操作：");
        System.out.println("1.      新增车辆");
        System.out.println("2.      查询车辆");
        System.out.println("3.      列出所有车辆");
        System.out.println("4.      结束程序");
        try{
            n = scanner.nextInt();
        }
        catch (InputMismatchException e){
            System.out.println("请输入1-4的整数\n");
            menu();
            throw e;
        }
        if(n<1||n>4){System.out.println("请输入1-4的整数\n");menu();}
        //检测输入是否合法
        switch (n){
            case 1:new_vehicle(v);break;
            case 2:search_vehicle(v);break;
            case 3:print_all(v);break;
            case 4:return;
        }
        //调用相关功能
        menu();
        //递归
    }
    //菜单
    static void new_vehicle(vehicle v[]) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入车辆信息，实例：");
        System.out.println("    小汽车 丰田 红色 4 2007 2厢");
        System.out.println("    卡车 雷诺 红色 3.5 2008");
        System.out.println("结束新增，请输入end");
        String s =scanner.next();
        if(s.equals("end"))return;
        if(s.equals("小汽车")){
            car a = new car();
            a.brand=scanner.next();
            a.color=scanner.next();
            a.busload=scanner.nextInt();
            a.year=scanner.nextInt();
            a.carriages_num=scanner.next();
            v[vehicle_num]=a;
            vehicle_num++;
            new_vehicle(v);
        }
        else if(s.equals("卡车")){
            truck a = new truck();
            a.brand=scanner.next();
            a.color=scanner.next();
            a.loadage=scanner.nextDouble();
            a.year=scanner.nextInt();
            v[vehicle_num]=a;
            vehicle_num++;
            new_vehicle(v);
        }
        else{
            System.out.println("第一个应为小汽车或卡车\n");
            System.out.println("创建不成功");
            new_vehicle(v);
        }
    }
    //功能1：新增车辆
    static void search_vehicle(vehicle v[]){
        int find[] = new int[100];
        int count=0;
        Scanner scanner = new Scanner(System.in);
        String type;
        String brand;
        String color;
        String year;
        while(true){
            count=0;
            System.out.println("请按照“类型 商标 颜色 出厂年”的顺序输入条件，若条件为空用\"null\"代替，2个示例：");
            System.out.println("    小汽车 丰田 红色 2007");
            System.out.println("    null 丰田 null null");
            System.out.println("输入end返回上级菜单\n");
            type = scanner.next();
            if(type.equals("end"))break;
            brand = scanner.next();
            color = scanner.next();
            year = scanner.next();
            for(int i=0;i<vehicle_num;i++){
                if(v[i] instanceof car&&type.equals("小汽车")||type.equals("null")||v[i] instanceof truck&&type.equals("卡车")){
                    if(v[i].brand.equals(brand) || brand.equals("null")){
                        if(v[i].color.equals(color) || color.equals("null")){
                            if(year.equals("null")||v[i].year == Integer.parseInt(year)){
                                find[count]=i;
                                count++;
                            }
                        }
                    }
                }
            }
            if(count!=0){
                System.out.println("搜索到"+count+"辆车，信息如下");
                for(int i=0;i<count;i++){
                    v[find[i]].print();
                }
            }
            else System.out.println("没有搜索到相应的交通工具");
        }
    }
    //功能2：查询车辆
    static void print_all(vehicle v[]){
        System.out.println("目前有"+vehicle_num+"辆车信息如下");
        for(int i=0;i<vehicle_num;i++){
            System.out.print((i+1)+".");
            v[i].print();
        }
    }
    //功能3：列出所有车辆
}

class vehicle{
    String brand;//品牌
    String color;//颜色
    int year;//出厂年份
    void print(){
    }
}
//车辆类
class car extends vehicle{//小汽车
    int busload;//载客量
    String carriages_num;//车厢数
    void print(){
        System.out.println("小汽车，品牌："+brand+" 颜色："+color+" 出厂年份："+year+" 载客量："+busload+"人 厢数"+carriages_num);
    }
}
//小轿车类，包含了print方法的多态
class truck extends vehicle{//卡车
    double loadage;//载货量
    void print(){
        System.out.println("卡车，品牌："+brand+" 颜色："+color+" 出厂年份："+year+" 载重量："+loadage+"吨");
    }
}
//卡车类，包含print方法的多态