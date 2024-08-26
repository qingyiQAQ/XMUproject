import java.net.*;
import java.io.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
public class Server extends JFrame implements Runnable
{
  private DatagramPacket sDgPacket, rDgPacket;
  private DatagramSocket socket;
	private JTextArea taRec;
	private JScrollPane sp;
	private JButton btn;
	private JTextField tfPort;
	private Container container;
	private Thread th;
	public Server()
	{
		super("ʵ��� --- �������˳���");
		container=getContentPane();
    container.setLayout(new FlowLayout());
		taRec=new JTextArea(15,40);
		sp=new JScrollPane(taRec);
		btn=new JButton(" �򿪶˿� ");
		tfPort=new JTextField(20);
		container.add(new JLabel("�������˿ں�:"));
		container.add(tfPort);
		container.add(btn);
		container.add(new JLabel("UDP ������������־"));
		container.add(sp);
		btn.addActionListener( new ActionListener(){
				public void actionPerformed(ActionEvent ae)
				{
					btn.setEnabled(false);
					try
					{
					 		String str=tfPort.getText();
					 		int p;
					 		if(str.equals("")) p=5678;
					 		else p=Integer.parseInt(str);
					 		socket=new DatagramSocket(p);
					}
					catch( NumberFormatException nfe)
					{
    			 	taRec.append("�˿ں����ָ�ʽ����\n");
    			 	return;
    			 }
					catch(SocketException se)
					{
						taRec.append("Socket����ʧ�ܣ�\n");
						btn.setEnabled(true);
						return;
			 		}
			 		Thread th=new Thread(Server.this);
			 		th.start();
				}
			});
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
				String res="";
				String rData=new String(rDgPacket.getData(),0,rDgPacket.getLength());
				Date da=new Date();
				if ((rData.toUpperCase()).equals("TIME"))
				{
					int h, m, s;
					h=da.getHours();
					m=da.getMinutes();
					s=da.getSeconds();
					res=(h<10?"0":"")+h+":"+(m<10?"0":"")+m+":"+(s<10?"0":"")+s;
				}
				else if ((rData.toUpperCase()).equals("DATE"))
				{
					res=(da.getYear()+1900)+"��"+da.getMonth()+"��"+da.getDate()+"��";
				}
				else
				{
					res="���������";
				}
   			data=res.getBytes();
   			sDgPacket=new DatagramPacket(data,data.length,rDgPacket.getAddress(),rDgPacket.getPort());
   			socket.send(sDgPacket);
				taRec.append("�յ���IP:"+rDgPacket.getAddress()+"(Port:"+rDgPacket.getPort()+") ��\""+rData+"\"�����ѷ���\""+res+"\"\n");
			}
			catch(IOException e){}
		}
	}
	public static void main(String []args)
	{
		 Server server=new Server();
		 server.setSize(480, 400);
		 server.setVisible(true);
		 server.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}
