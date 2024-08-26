import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {
    public static void main(String[] args) {
        int arr[] = new int[10000];
        ExecutorService executor = Executors.newFixedThreadPool(4);
        executor.submit(() -> {
            for (int i = 1; i <= 10; i++) {
                arr[i-1]=i;
            }
        });
        executor.submit(() -> {
            for (int i = 100; i <= 1000; i++) {
                arr[i-1]=i;
            }
        });
        executor.submit(() -> {
            for (int i = 2000; i <= 3000; i++) {
                arr[i-1]=i;
            }
        });
        executor.submit(() -> {
            for (int i = 4000; i <= 5000; i++) {
                arr[i-1]=i;
            }
        });
        executor.shutdown();
    }
}