import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {
    public static void main(String[] args) {
        ExecutorService executor = Executors.newFixedThreadPool(2);
        executor.submit(() -> {
            Thread.currentThread().setName("Thread1");
            for (int i = 1; i <= 10; i++) {
                System.out.println(Thread.currentThread().getName() + "-" + i);
            }
        });
        executor.submit(() -> {
            Thread.currentThread().setName("Thread2");
            for (int i = 1; i <= 10; i++) {
                System.out.println(Thread.currentThread().getName() + "-" + i);
            }
        });
        executor.shutdown(); // 关闭线程池
    }
}