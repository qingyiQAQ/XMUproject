
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {
    private final int capacity = 4;
    private final int[] buffer = new int[capacity];
    private int occupiedCells=0;
    private int writeIndex=0;
    private int readIndex=0;
    private final Random rand = new Random();
    public synchronized void produce() throws InterruptedException {
        int num = rand.nextInt(10) + 1;
        if(occupiedCells == capacity){
            wait();
        }
        buffer[writeIndex]=num;
        System.out.println("Produced: " + num);
        writeIndex=(writeIndex+1)%capacity;
        occupiedCells++;
        notifyAll();
    }
    public synchronized void consume() throws InterruptedException {
        while (occupiedCells==0) {
            wait();
        }
        int num = buffer[readIndex];
        System.out.println("Consume: " + num);
        readIndex=(readIndex+1)%capacity;
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