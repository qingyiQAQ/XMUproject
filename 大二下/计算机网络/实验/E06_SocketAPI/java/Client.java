import java.net.*;
import java.io.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.text.*;
public class Client extends JFrame implements Runnable
{
  private DatagramPacket sDgPacket, rDgPacket;
  private DatagramSocket socket;
  private JTextField tfIP, tfPort, tfRequest, tfResponse;
	private Container container;
	private JButton btn;
	Client()
	{
		super("实验八 --- 客户端程序");
		container=getContentPane();
    container.setLayout(new FlowLayout());
		tfIP=new JTextField(15);
		tfPort=new JTextField(15);
		tfRequest=new JTextField(15);
		tfResponse=new JTextField(15);
		btn=new JButton("  发 送  ");
		container.add(new JLabel("服务器IP地址："));
    container.add(tfIP);
		container.add(new JLabel("　 服务器端口："));
		container.add(tfPort);
		container.add(new JLabel("　　请求命令： "));
		container.add(tfRequest);
		container.add(new JLabel("　服务器响应："));
		container.add(tfResponse);
    container.add(btn);
		try
		{
			socket=new DatagramSocket();
		}
		catch(SocketException se)
		{
			tfResponse.setText("Socketc创建失败！");
 		}	
    btn.addActionListener(new ActionListener()
    	{
    		public void actionPerformed(ActionEvent ae)
    		{
    			if (ae.getSource()==btn)
    			{
    				byte data[]=tfRequest.getText().getBytes();
    				try
    				{
    					sDgPacket=new DatagramPacket(data,data.length,
    							InetAddress.getByName(tfIP.getText()),
    							Integer.parseInt(tfPort.getText()));
    				}
					  catch( NumberFormatException nfe)
					  {
    			  	tfResponse.setText("端口号数字格式错误！");
    			  	return;
    			  } 
    			  catch( UnknownHostException une)
    			  {
    			  	tfResponse.setText("主机无法到达！");
    			  	return;
    			  }
    			  try
    			  {
    			  	socket.send(sDgPacket);
    			  }
   				  catch( NullPointerException npe){
    				  	tfResponse.setText("Socket创建失败！");
   				  }
   					catch(IOException IOe){
   							tfResponse.setText("IO错误！");
   						}
    			}
    		}
    	}
    );
	}
	public void run()
	{
   	while(true)
		{
			try
			{
				byte data[]=new byte[200];
				rDgPacket=new DatagramPacket(data,data.length);
				socket.receive(rDgPacket);
				tfResponse.setText(new String(rDgPacket.getData(), 0, rDgPacket.getLength()));
			}
			catch(IOException e){}
		}
	}
	public static void main(String[] args)
	{
		Client client=new Client();
		client.setSize(300, 200);
		client.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		client.setVisible(true);
		Thread th=new Thread(client);
		th.start();
	}
}