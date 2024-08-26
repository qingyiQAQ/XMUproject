import java.io.File;
import java.io.FileNotFoundException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner scanner = new Scanner(System.in);
        String a = scanner.next();
        File file = new File(a);
        if(!file.exists())System.err.println("该文件路径不存在!");
        else {
            if (file.isDirectory()) {
                int count_all = 0, count_directory = 0;
                for (File f : file.listFiles()) {
                    if (f.isDirectory()) count_directory++;
                    count_all++;
                }
                System.out.println("该文件是文件夹!");
                System.out.println("该文件夹的文件个数" + count_all);
                System.out.println("该文件夹的文件夹个数" + count_directory);
            } else {
                System.out.println("该文件不是文件夹!");
                System.out.println("该文件大小:" + file.length()+"B");
                DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
                System.out.println("该文件最后修改时间:" + dateFormat.format(file.lastModified()));
            }
        }
    }
}