//作者:陈澄
//32420212202930
import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {
    static int property_num=0;//资产数目
    static Property properties[] = new Property[1000];//用于储存总资产
    public static void main(String[] args) {
        menu();
    }
    static void menu(){
        String n = null;
        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入命令编号：");
        System.out.println("A.录入资产信息");
        System.out.println("B.列出所有资产");
        System.out.println("C.根据某人领用资产");
        System.out.println("D.退出");
        try{
            n = scanner.next();
        }
        catch (InputMismatchException e){
            System.out.println("输入错误，请输入A-D的字母。");
            menu();
        }
        if(!(n.equals("A"))&&!(n.equals("B"))&&!(n.equals("C"))&&!(n.equals("D"))){
            System.err.println("输入错误，请输入A-D的字母。");
            menu();
        }
        //检测输入是否合法
        switch (n){
            case "A":input(properties);break;
            case "B":print_all(properties);break;
            case "C":use(properties);break;
            case "D":return;
        }
        //调用相关功能
        menu();
        //递归
    }
    //菜单
    static void input(Property[] p){//新增资产
        String number = null;//编号
        String name = null;//名称
        String model = null;//型号
        double price = 0;//单价
        int quantity = 0;//数量
        int receiver_id = 0;//领用人id
        Scanner scanner = new Scanner(System.in);
        System.out.println("请按照以下格式输入：");
        System.out.println("    仪器设备 编号 名称 型号 单价 数量 出厂号 供应商 领用人ID");
        System.out.println("    低值设备 编号 名称 型号 单价 数量 领用人ID");
        System.out.println("如：");
        System.out.println("    仪器设备 111 笔记本 联想-1 5000.00 20 101010 联想 11");
        System.out.println("    低值设备 222 刻录机 联想-2 500.00 30 111");
        System.out.println("其中“编号”为1-6位数字串，“单价”为最多两位小数的double型数据，");
        System.out.println("“数量”为整数，“领用人ID”为100以内的整数。");
        String s =scanner.next();
        if(s.equals("仪器设备")){
            String factory_number = null;
            String supplier = null;
            try {
                number = scanner.next();
                if (number.length() < 1 || number.length() > 6) input_fail(p);
                name = scanner.next();
                model = scanner.next();
                price = scanner.nextDouble();
                quantity = scanner.nextInt();
                factory_number = scanner.next();
                supplier = scanner.next();
                receiver_id = scanner.nextInt();
                if(receiver_id<0||receiver_id>100) input_fail(p);
            }
            catch (InputMismatchException e){
                input_fail(p);
            }
            Instruments_equipment a = new Instruments_equipment(number,name,model,price,quantity,receiver_id,factory_number,supplier);
            p[property_num]=a;
            property_num++;
            System.out.println("创建成功!");
            System.out.println("是否结束输入？（是则输入Y）");
            String t = scanner.next();
            if(!(t.equals("Y")))input(p);
        }
        else if(s.equals("低值设备")){
            try {
                number = scanner.next();
                if (number.length() < 1 || number.length() > 6) input_fail(p);
                name = scanner.next();
                model = scanner.next();
                price = scanner.nextDouble();
                quantity = scanner.nextInt();
                receiver_id = scanner.nextInt();
                if(receiver_id<0||receiver_id>1000) input_fail(p);
            }
            catch (InputMismatchException e){
                input_fail(p);
            }
            Low_value_equipment a = new Low_value_equipment(number,name,model,price,quantity,receiver_id);
            p[property_num]=a;
            property_num++;
            System.out.println("创建成功!");
            System.out.println("是否结束输入？（是则输入Y）");
            String t = scanner.next();
            if(!(t.equals("Y")))input(p);
            else menu();
        }
        else{
            input_fail(p);
        }
    }
    static void input_fail(Property[] p){
        Scanner scanner = new Scanner(System.in);
        System.err.println("创建失败!");
        System.out.println("是否结束输入？(是则输入Y)");
        String t = scanner.next();
        if(!(t.equals("Y")))input(p);
        else menu();
    }
    static void print_all(Property[] p){
        System.out.println("资产列表如下:");
        for (int i=0;i<property_num;i++) {
            System.out.print((i+1)+". ");
            p[i].print();
        }
    }
    static void use(Property[] p){
        int receiver_id = 0;
        int i,count = 0;
        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入领用人id:");
        try{
            receiver_id=scanner.nextInt();
        }
        catch (InputMismatchException e){
            System.err.println("输入格式错误!请输入整数!");
            return;
        }
        for (i=0;i<property_num;i++) {
            if(p[i].receiver_id==receiver_id){
                count++;
            }
        }
        if(count==0)System.err.println("未找到资产!");
        else {
            System.out.println("资产列表如下:");
            for (i=0;i<property_num;i++) {
                if(p[i].receiver_id==receiver_id){
                    System.out.print((i+1)+". ");
                    p[i].print();
                }
            }
        }
    }
}
class Property{
    String number;//编号
    String name;//名称
    String model;//型号
    double price;//单价
    int quantity;//数量
    int receiver_id;//领用人id
    Property(String number,String name,String model,double price,int quantity,int receiver_id){
        this.number=number;
        this.name=name;
        this.model=model;
        this.price=price;
        this.quantity=quantity;
        this.receiver_id=receiver_id;
    }
    void print(){
        System.out.println(number+" "+name+" "+model+" "+price+" "+quantity+" "+receiver_id);
    }
}
class Instruments_equipment extends Property{
    String factory_number;//出厂号
    String supplier;//供应商
    Instruments_equipment(String number,String name,String model,double price,int quantity,int receiver_id,String factory_number,String supplier){
        super(number,name,model,price,quantity,receiver_id);
        this.factory_number=factory_number;
        this.supplier=supplier;
    }
    void print(){
        System.out.println("仪器设备 "+number+" "+name+" "+model+" "+price+" "+quantity+" "+factory_number+" "+supplier+" "+receiver_id);
    }
}
class Low_value_equipment extends Property{
    Low_value_equipment(String number, String name, String model, double price, int quantity, int receiver_id) {
        super(number, name, model, price, quantity, receiver_id);
    }
    void print(){
        System.out.println("低值设备 "+number+" "+name+" "+model+" "+price+" "+quantity+" "+receiver_id);
    }
}