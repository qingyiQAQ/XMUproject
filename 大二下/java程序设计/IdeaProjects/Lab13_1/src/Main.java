public class Main {
    public static void main(String[] args) {
        Thread thread1 = new NumOutputTread(1);
        Thread thread2 = new NumOutputTread(2);
        thread1.start();
        thread2.start();
    }
}
class NumOutputTread extends Thread{
    NumOutputTread(int i){
        setName("Thread"+i);
    }
    public void run(){
        for(int i=1;i<=10;i++) {
            System.out.println(this.getName() + "-" + i);
        }
    }
}