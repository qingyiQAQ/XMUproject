#define WIN32
#include<iostream>
#include<sstream>
#include<string>
#include<map>
#include<fstream>
#include <pcap.h>
#pragma warning(disable:4996)
using namespace std;
map<string, string[3]> ftp;
bool flag;
ofstream out("mark.txt");
typedef struct mac_header
{
	u_char dest_addr[6];
	u_char src_addr[6];
	u_char type[2];
} mac_header;

/* IPv4 首部 ,20字节*/
typedef struct ip_header {
	u_char  ver_ihl;        // 版本 (4 bits) + 首部长度 (4 bits)  
	u_char  tos;            // 服务类型(Type of service)  
	u_short tlen;           // 总长(Total length)  
	u_short identification; // 标识(Identification)  
	u_short flags_fo;       // 标志位(Flags) (3 bits) + 段偏移量(Fragment offset) (13 bits)  
	u_char  ttl;            // 存活时间(Time to live)  
	u_char  proto;          // 协议(Protocol)  
	u_short crc;            // 首部校验和(Header checksum)  
	u_char  saddr[4];      // 源地址(Source address)  
	u_char  daddr[4];      // 目的地址(Destination address)  
	u_int   op_pad;         // 选项与填充(Option + Padding)  
}ip_header;
//TCP头部，总长度20字节  
typedef struct tcp_header
{
	u_short sport;            //源端口号  
	u_short dport;             //目的端口号  
	u_int th_seq;                //序列号  
	u_int th_ack;               //确认号  
	u_int th1 : 4;              //tcp头部长度  
	u_int th_res : 4;             //6位中的4位首部长度  
	u_int th_res2 : 2;            //6位中的2位首部长度  
	u_char th_flags;            //6位标志位  
	u_short th_win;             //16位窗口大小  
	u_short th_sum;             //16位tcp检验和  
	u_short th_urp;             //16位紧急指针  
}tcp_header;

/* 回调函数原型 */
void packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data);
string get_request_m_ip_message(const u_char* pkt_data);
string get_response_m_ip_message(const u_char* pkt_data);
void print(const struct pcap_pkthdr* header, string m_ip_message, const u_char* pkt_data);

int main()
{
	flag = false;
	pcap_if_t* alldevs;
	pcap_if_t* d;
	int inum;
	int i = 0;
	pcap_t* adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	u_int netmask;
	char packet_filter[] = "tcp";
	struct bpf_program fcode;

	/* 获得设备列表 */
	if (pcap_findalldevs_ex((char*)PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}

	/* 打印列表 */
	for (d = alldevs; d; d = d->next)
	{
		printf("%d. %s", ++i, d->name);
		if (d->description)
			printf(" (%s)\n", d->description);
		else
			printf(" (No description available)\n");
	}

	if (i == 0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		return -1;
	}

	printf("Enter the interface number (1-%d):", i);
	cin >> inum;

	if (inum < 1 || inum > i)
	{
		printf("\nInterface number out of range.\n");
		/* 释放设备列表 */
		pcap_freealldevs(alldevs);
		return -1;
	}

	/* 跳转到已选设备 */
	for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++);

	/* 打开适配器 */
	if ((adhandle = pcap_open(d->name,  // 设备名  
		65536,     // 要捕捉的数据包的部分  
		// 65535保证能捕获到不同数据链路层上的每个数据包的全部内容  
		PCAP_OPENFLAG_PROMISCUOUS,         // 混杂模式  
		1000,      // 读取超时时间  
		NULL,      // 远程机器验证  
		errbuf     // 错误缓冲池  
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
		/* 释放设备列表 */
		pcap_freealldevs(alldevs);
		return -1;
	}

	/* 检查数据链路层，为了简单，我们只考虑以太网 */
	if (pcap_datalink(adhandle) != DLT_EN10MB)
	{
		fprintf(stderr, "\nThis program works only on Ethernet networks.\n");
		/* 释放设备列表 */
		pcap_freealldevs(alldevs);
		return -1;
	}

	if (d->addresses != NULL)
		/* 获得接口第一个地址的掩码 */
		netmask = ((struct sockaddr_in*)(d->addresses->netmask))->sin_addr.S_un.S_addr;
	else
		/* 如果接口没有地址，那么我们假设一个C类的掩码 */
		netmask = 0xffffff;


	//编译过滤器  
	if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) < 0)
	{
		fprintf(stderr, "\nUnable to compile the packet filter. Check the syntax.\n");
		/* 释放设备列表 */
		pcap_freealldevs(alldevs);
		return -1;
	}

	//设置过滤器  
	if (pcap_setfilter(adhandle, &fcode) < 0)
	{
		fprintf(stderr, "\nError setting the filter.\n");
		/* 释放设备列表 */
		pcap_freealldevs(alldevs);
		return -1;
	}

	printf("\nlistening on %s...\n", d->description);

	/* 释放设备列表 */
	pcap_freealldevs(alldevs);

	/* 开始捕捉 */
	pcap_loop(adhandle, 0, packet_handler, NULL);
	out.close();
	return 0;
}


static int cnt = 0;

/* 回调函数，当收到每一个数据包时会被libpcap所调用 */
void packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data)
{

	int head = 54;//14位以太网头，20位ip头，20位tcp头  
	//选择出command为USER和PASS的包，当然这里就简单的以首字母来代表了，反正其他的  
	//command 没有以U和P开头的  
	string com;
	string m_ip_message;
	//对数据包的处理，先提前前四个字符，查看是什么命令
	for (int i = 0; i < 4; i++)
		com += (char)pkt_data[head + i];
	if (com == "USER")
	{
		m_ip_message = get_request_m_ip_message(pkt_data);
		string user;
		ostringstream sout;
		for (int i = head + 5; pkt_data[i] != 13; i++)
		{
			sout << pkt_data[i];
		}
		user = sout.str();
		ftp[m_ip_message][0] = user;
		print(header, m_ip_message, pkt_data);
	}
	else if (com == "PASS")
	{
		m_ip_message = get_request_m_ip_message(pkt_data);
		string pass;
		ostringstream sout;
		for (int i = head + 5; pkt_data[i] != 13; i++)
		{
			sout << pkt_data[i];
		}
		pass = sout.str();
		ftp[m_ip_message][1] = pass;
		print(header, m_ip_message, pkt_data);
	}
	else if (com == "230 ")
	{
		m_ip_message = get_response_m_ip_message(pkt_data);
		ftp[m_ip_message][2] = "SUCCEED";
		print(header, m_ip_message, pkt_data);
	}
	else if (com == "530 ")
	{
		m_ip_message = get_response_m_ip_message(pkt_data);
		ftp[m_ip_message][2] = "FAILD";
		print(header, m_ip_message, pkt_data);
	}

}
string get_request_m_ip_message(const u_char* pkt_data)
{
	mac_header* mh;
	ip_header* ih;
	string m_ip_message;
	string str;//empty string
	ostringstream sout;
	int length = sizeof(mac_header) + sizeof(ip_header);
	mh = (mac_header*)pkt_data;
	ih = (ip_header*)(pkt_data + sizeof(mac_header));
	//sout << "SRC MAC:";

	//sout << "DESC MAC:";
	for (int i = 0; i < 3; i++)
		sout << dec << (int)(ih->saddr[i]) << ".";
	sout << (int)(ih->saddr[3]) << ",";
	for (int i = 0; i < 5; i++)
		sout << hex << (int)(mh->dest_addr[i]) << "-";
	sout << (int)(mh->dest_addr[5]) << ",";
	for (int i = 0; i < 3; i++)
		sout << dec << (int)(ih->daddr[i]) << ".";
	sout << (int)(ih->daddr[3]);
	m_ip_message = sout.str();
	return m_ip_message;
}
string get_response_m_ip_message(const u_char* pkt_data)
{
	mac_header* mh;
	ip_header* ih;
	string m_ip_message;
	string str;//empty string
	ostringstream sout;
	int length = sizeof(mac_header) + sizeof(ip_header);
	mh = (mac_header*)pkt_data;
	ih = (ip_header*)(pkt_data + sizeof(mac_header));
	for (int i = 0; i < 5; i++)
		sout << hex << (int)(mh->dest_addr[i]) << "-";
	sout << (int)(mh->dest_addr[5]) << ",";
	for (int i = 0; i < 3; i++)
		sout << dec << (int)(ih->daddr[i]) << ".";
	sout << (int)(ih->daddr[3]) << ",";
	for (int i = 0; i < 5; i++)
		sout << hex << (int)(mh->src_addr[i]) << "-";
	sout << (int)(mh->src_addr[5]) << ",";
	for (int i = 0; i < 3; i++)
		sout << dec << (int)(ih->saddr[i]) << ".";
	sout << (int)(ih->saddr[3]);
	m_ip_message = sout.str();
	return m_ip_message;
}

void print(const struct pcap_pkthdr* header, string m_ip_message, const u_char* pkt_data)
{
	mac_header* mh;
	ip_header* ih;
	mh = (mac_header*)pkt_data;
	ih = (ip_header*)(pkt_data + sizeof(mac_header));
	tcp_header* th;
	th = (tcp_header*)(pkt_data + 34);
	cnt++;
	cout << "No." << cnt << endl << endl;
	time_t tt = time(NULL);
	tm* t = localtime(&tt);

	cout << "Time:";
	printf("%d:%d:%d(%d)", t->tm_hour, t->tm_min, t->tm_sec, header->ts.tv_usec);
	cout << endl;
	//计算tcp报文数据长度还有点子错
	/*u_int len = ih->tlen-ih->ver_ihl-th->th1;
	cout << "TCP_Data_Length:" << len << endl;*/
	cout << "get an ip packet" << endl;
	cout << "get a tcp packet" << endl;
	u_short server = 21;//这里需要自己写服务器的端口，才能在后面判断到底是客户端到服务器端还是服务器端到客户端
	cout << "源端口：" << ntohs(th->sport) << endl;
	cout << "目的端口：" << ntohs(th->dport) << endl;
	if (ntohs(th->dport) == server)
		cout << "ftp:client->server" << endl;
	else
		cout << "ftp:server->client" << endl;
	cout << "SRC MAC ";
	for (int i = 0; i < 5; i++) {//源MAC地址
		printf("%02X-", mh->src_addr[i]);
	}
	printf("%02X,", mh->src_addr[5]);
	cout << endl;

	cout << "SOURCE IP ";
	for (int i = 0; i < 3; i++) {//源IP地址
		printf("%d.", ih->saddr[i]);
	}
	//fprintf_s(file, "%d,", ih->saddr[3]);
	printf("%d,", ih->saddr[3]);
	cout << endl;

	cout << "DEST MAC ";
	for (int i = 0; i < 5; i++) {//目的MAC地址
		printf("%02X-", mh->dest_addr[i]);
	}
	printf("%02X,", mh->dest_addr[5]);
	cout << endl;

	cout << "DEST IP ";
	for (int i = 0; i < 3; i++) {//目的IP地址
		printf("%d.", ih->daddr[i]);
	}
	printf("%d,", ih->daddr[3]);
	cout << endl;
	u_short dport;
	u_char flags = '\0';
	dport = ntohs(th->dport);
	flags = th->th_flags;

	printf("6比特标志位：\n");
	bool URG = flags & 0x20;
	bool ACK = flags & 0x10;
	bool PSH = flags & 0x08;
	bool RST = flags & 0x04;
	bool SYN = flags & 0x02;
	bool FIN = flags & 0x01;
	printf("URG=%d\tACK=%d\tPSH=%d\tRST=%d\tSYN=%d\tFIN=%d\n", URG, ACK, PSH, RST, SYN, FIN);

	if (SYN) { if (ACK)printf("第二个握手包");else printf("第一个握手包"); }

	else if (FIN)printf("挥手包");
	cout << endl;
	cout << "USER:" << ftp[m_ip_message][0] << " ";
	cout << "PASSWORD:" << ftp[m_ip_message][1] << " ";
	cout << ftp[m_ip_message][2] << endl;
	ftp.erase(m_ip_message);
	cout << endl << endl;
}
