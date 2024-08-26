
import java.util.Random;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {
    private final int capacity = 4;
    private int occupiedCells = 0;
    private final ArrayBlockingQueue<Integer> buffer = new ArrayBlockingQueue<>(capacity);
    private final Random rand = new Random();
    public synchronized void produce() throws InterruptedException {
        int num = rand.nextInt(10) + 1;
        if(buffer.size()==capacity){
            wait();
        }
        buffer.add(num);
        System.out.println("Produced: " + num);
        occupiedCells++;
        notifyAll();
    }
    public synchronized void consume() throws InterruptedException {
        while (occupiedCells==0) {
            wait();
        }
        int num = buffer.take();
        System.out.println("Consume: " + num);
        occupiedCells--;
        notifyAll();
    }
    public static void main(String[] args) {
        Main main = new Main();
        ExecutorService executor = Executors.newFixedThreadPool(2);
        executor.submit(() -> {
            try {
                while(true) {
                    main.produce();
                }
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        });
        executor.submit(() -> {
            try {
                while(true) {
                    main.consume();
                }
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        });
        executor.shutdown();
    }
}