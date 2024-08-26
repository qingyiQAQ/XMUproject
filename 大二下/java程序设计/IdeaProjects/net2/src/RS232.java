import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.charset.Charset;
import java.util.Arrays;
import java.util.Scanner;
import com.fazecast.jSerialComm.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
public class RS232 {

    public static void main(String[] args) throws IOException {
        //获得串口列表并初始化为数组
        SerialPort[] ports = SerialPort.getCommPorts();
        System.out.println("可用的串口列表：");
        for (int i = 0; i < ports.length; i++) {
            System.out.println( (i+1) + ". " + ports[i].getSystemPortName() );
        }
        //选择要使用的串口并打开串口
        System.out.println("选择已连接的串口（输入）：");
        Scanner in = new Scanner(System.in);
        int choice = in.nextInt();
        SerialPort chosenPort1 = ports[choice-1];
        chosenPort1.openPort();
        System.out.println("选择已连接的串口（输出）：");
        choice = in.nextInt();
        SerialPort chosenPort2 = ports[choice-1];
        chosenPort2.openPort();
        //初始化输入输出流
        InputStream inputStream = chosenPort1.getInputStream();
        OutputStream outputStream = chosenPort2.getOutputStream();
        while(true){
            System.out.println("等待数据输入...（输入switch交换输入输出端）");
            Scanner scanner = new Scanner(System.in, Charset.defaultCharset());
            String input = scanner.nextLine();
            if(input.equals("switch")){
                SerialPort t=chosenPort1;
                chosenPort2=chosenPort1;
                chosenPort1=t;
                System.out.println("已交换，等待数据输入...");
                input = scanner.nextLine();
            }
            //发送数据
            byte[] buffer = input.getBytes();
            outputStream.write(buffer);
            outputStream.flush();
            int bytes1 =buffer.length;
            System.out.println("[SEND " + getTime() + "] " + new String(Arrays.copyOf(buffer, bytes1)));
            //接收数据
            byte[] readBuffer = new byte[1024];
            int bytes2 = inputStream.read(readBuffer);
            System.out.println("[RECV " + getTime() + "] " + new String(Arrays.copyOf(readBuffer, bytes2)));
        }
    }
    static String getTime(){
        LocalDateTime currentTime = LocalDateTime.now();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        return currentTime.format(formatter);
    }//获取当前时间
}