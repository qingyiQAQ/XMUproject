public class Test {
    public static void main(String[] args) {
        Vehicle[] a = new Vehicle[6];
        a[0] = new Vehicle();
        a[1] = new Motor();
        a[2] = new Ship();
        a[3] = new Aeroplane();
        a[4] = new Bus();
        a[5] = new Car();
        for(int i=0;i<6;i++){
            a[i].run();
        }
    }
}
class Vehicle{
    void run(){
        System.out.println("这是交通工具run方法");
    }
}
class Motor extends Vehicle{
    void run(){
        System.out.println("这是汽车run方法");
    }
}
class Ship extends  Vehicle{
    void run(){
        System.out.println("这是船run方法");
    }
}
class Aeroplane extends Vehicle{
    void run(){
        System.out.println("这是飞机run方法");
    }
}
class Bus extends Motor{
    void run(){
        System.out.println("这是公共汽车run方法");
    }
}
class Car extends  Motor{
    void run(){
        System.out.println("这是轿车run方法");
    }
}