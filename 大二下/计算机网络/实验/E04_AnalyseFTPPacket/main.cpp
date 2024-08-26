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

/* IPv4 �ײ� ,20�ֽ�*/
typedef struct ip_header {
	u_char  ver_ihl;        // �汾 (4 bits) + �ײ����� (4 bits)  
	u_char  tos;            // ��������(Type of service)  
	u_short tlen;           // �ܳ�(Total length)  
	u_short identification; // ��ʶ(Identification)  
	u_short flags_fo;       // ��־λ(Flags) (3 bits) + ��ƫ����(Fragment offset) (13 bits)  
	u_char  ttl;            // ���ʱ��(Time to live)  
	u_char  proto;          // Э��(Protocol)  
	u_short crc;            // �ײ�У���(Header checksum)  
	u_char  saddr[4];      // Դ��ַ(Source address)  
	u_char  daddr[4];      // Ŀ�ĵ�ַ(Destination address)  
	u_int   op_pad;         // ѡ�������(Option + Padding)  
}ip_header;
//TCPͷ�����ܳ���20�ֽ�  
typedef struct tcp_header
{
	u_short sport;            //Դ�˿ں�  
	u_short dport;             //Ŀ�Ķ˿ں�  
	u_int th_seq;                //���к�  
	u_int th_ack;               //ȷ�Ϻ�  
	u_int th1 : 4;              //tcpͷ������  
	u_int th_res : 4;             //6λ�е�4λ�ײ�����  
	u_int th_res2 : 2;            //6λ�е�2λ�ײ�����  
	u_char th_flags;            //6λ��־λ  
	u_short th_win;             //16λ���ڴ�С  
	u_short th_sum;             //16λtcp�����  
	u_short th_urp;             //16λ����ָ��  
}tcp_header;

/* �ص�����ԭ�� */
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

	/* ����豸�б� */
	if (pcap_findalldevs_ex((char*)PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}

	/* ��ӡ�б� */
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
		/* �ͷ��豸�б� */
		pcap_freealldevs(alldevs);
		return -1;
	}

	/* ��ת����ѡ�豸 */
	for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++);

	/* �������� */
	if ((adhandle = pcap_open(d->name,  // �豸��  
		65536,     // Ҫ��׽�����ݰ��Ĳ���  
		// 65535��֤�ܲ��񵽲�ͬ������·���ϵ�ÿ�����ݰ���ȫ������  
		PCAP_OPENFLAG_PROMISCUOUS,         // ����ģʽ  
		1000,      // ��ȡ��ʱʱ��  
		NULL,      // Զ�̻�����֤  
		errbuf     // ���󻺳��  
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
		/* �ͷ��豸�б� */
		pcap_freealldevs(alldevs);
		return -1;
	}

	/* ���������·�㣬Ϊ�˼򵥣�����ֻ������̫�� */
	if (pcap_datalink(adhandle) != DLT_EN10MB)
	{
		fprintf(stderr, "\nThis program works only on Ethernet networks.\n");
		/* �ͷ��豸�б� */
		pcap_freealldevs(alldevs);
		return -1;
	}

	if (d->addresses != NULL)
		/* ��ýӿڵ�һ����ַ������ */
		netmask = ((struct sockaddr_in*)(d->addresses->netmask))->sin_addr.S_un.S_addr;
	else
		/* ����ӿ�û�е�ַ����ô���Ǽ���һ��C������� */
		netmask = 0xffffff;


	//���������  
	if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) < 0)
	{
		fprintf(stderr, "\nUnable to compile the packet filter. Check the syntax.\n");
		/* �ͷ��豸�б� */
		pcap_freealldevs(alldevs);
		return -1;
	}

	//���ù�����  
	if (pcap_setfilter(adhandle, &fcode) < 0)
	{
		fprintf(stderr, "\nError setting the filter.\n");
		/* �ͷ��豸�б� */
		pcap_freealldevs(alldevs);
		return -1;
	}

	printf("\nlistening on %s...\n", d->description);

	/* �ͷ��豸�б� */
	pcap_freealldevs(alldevs);

	/* ��ʼ��׽ */
	pcap_loop(adhandle, 0, packet_handler, NULL);
	out.close();
	return 0;
}


static int cnt = 0;

/* �ص����������յ�ÿһ�����ݰ�ʱ�ᱻlibpcap������ */
void packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data)
{

	int head = 54;//14λ��̫��ͷ��20λipͷ��20λtcpͷ  
	//ѡ���commandΪUSER��PASS�İ�����Ȼ����ͼ򵥵�������ĸ�������ˣ�����������  
	//command û����U��P��ͷ��  
	string com;
	string m_ip_message;
	//�����ݰ��Ĵ�������ǰǰ�ĸ��ַ����鿴��ʲô����
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
	//����tcp�������ݳ��Ȼ��е��Ӵ�
	/*u_int len = ih->tlen-ih->ver_ihl-th->th1;
	cout << "TCP_Data_Length:" << len << endl;*/
	cout << "get an ip packet" << endl;
	cout << "get a tcp packet" << endl;
	u_short server = 21;//������Ҫ�Լ�д�������Ķ˿ڣ������ں����жϵ����ǿͻ��˵��������˻��Ƿ������˵��ͻ���
	cout << "Դ�˿ڣ�" << ntohs(th->sport) << endl;
	cout << "Ŀ�Ķ˿ڣ�" << ntohs(th->dport) << endl;
	if (ntohs(th->dport) == server)
		cout << "ftp:client->server" << endl;
	else
		cout << "ftp:server->client" << endl;
	cout << "SRC MAC ";
	for (int i = 0; i < 5; i++) {//ԴMAC��ַ
		printf("%02X-", mh->src_addr[i]);
	}
	printf("%02X,", mh->src_addr[5]);
	cout << endl;

	cout << "SOURCE IP ";
	for (int i = 0; i < 3; i++) {//ԴIP��ַ
		printf("%d.", ih->saddr[i]);
	}
	//fprintf_s(file, "%d,", ih->saddr[3]);
	printf("%d,", ih->saddr[3]);
	cout << endl;

	cout << "DEST MAC ";
	for (int i = 0; i < 5; i++) {//Ŀ��MAC��ַ
		printf("%02X-", mh->dest_addr[i]);
	}
	printf("%02X,", mh->dest_addr[5]);
	cout << endl;

	cout << "DEST IP ";
	for (int i = 0; i < 3; i++) {//Ŀ��IP��ַ
		printf("%d.", ih->daddr[i]);
	}
	printf("%d,", ih->daddr[3]);
	cout << endl;
	u_short dport;
	u_char flags = '\0';
	dport = ntohs(th->dport);
	flags = th->th_flags;

	printf("6���ر�־λ��\n");
	bool URG = flags & 0x20;
	bool ACK = flags & 0x10;
	bool PSH = flags & 0x08;
	bool RST = flags & 0x04;
	bool SYN = flags & 0x02;
	bool FIN = flags & 0x01;
	printf("URG=%d\tACK=%d\tPSH=%d\tRST=%d\tSYN=%d\tFIN=%d\n", URG, ACK, PSH, RST, SYN, FIN);

	if (SYN) { if (ACK)printf("�ڶ������ְ�");else printf("��һ�����ְ�"); }

	else if (FIN)printf("���ְ�");
	cout << endl;
	cout << "USER:" << ftp[m_ip_message][0] << " ";
	cout << "PASSWORD:" << ftp[m_ip_message][1] << " ";
	cout << ftp[m_ip_message][2] << endl;
	ftp.erase(m_ip_message);
	cout << endl << endl;
}
