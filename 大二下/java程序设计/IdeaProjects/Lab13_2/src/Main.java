public class Main {
    public static void main(String[] args) {
        Thread thread1 = new Thread(new Num(1));
        Thread thread2 = new Thread(new Num(2));
        thread1.start();
        thread2.start();
    }
}
class Num implements Runnable{
    int num;
    Num(int num){
        this.num = num;
    }
    @Override
    public void run() {
        for(int i=1;i<=10;i++)
        System.out.println("Thread"+this.num+"-"+i);
    }
}