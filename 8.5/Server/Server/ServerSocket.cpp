#include <iostream>   
#include <string>   
#include <winsock2.h>   
#pragma comment(lib,"ws2_32.lib")   
using std::cout;
using std::cin;
using std::string;
using std::endl;
typedef struct Date {
	float m1;
	float m2;
	float m3;
	float m_roll;
	float m_pitch;
	float m_rotate;
}Datablock;

int main()
{

	cout << "������������....." << endl;
	//��ʼ��winsock   
	WSADATA wsaD;
	WSAStartup(MAKEWORD(1, 1), &wsaD);
	//���������׽���   
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// ��������ַ�ͼ����׽���   
	struct sockaddr_in my_addr;   //������ַ   
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(3030); //ָ���˿�   
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(slisten, (struct sockaddr *)&my_addr, sizeof(my_addr));
	//��������   
	listen(slisten, 5);    //5�����������
						   //��ʼ��������   
	struct sockaddr_in c_addr;  //�ͻ���ַ   
	int addr_len = sizeof(c_addr);


	SOCKET sconnect = accept(slisten, (struct sockaddr*)&c_addr, &addr_len); //ͨ�������׽��ִ��������׽���   

	cout << "�����ѽ���......" << endl;

	char buf[500];
	while (true) {
		Datablock client_send;

		cout << "����(start)��ʼ���ģ�����(end)��������" << endl;

		cout << "���뷢�����ݣ�";
		while (cin.getline(buf, 500))
		{


			string rcover = buf;
			if (rcover == "end")break;
			if (rcover == "start") {
				cout << "����m1-m2-m3-m_roll-m_pitch-m_rotate��ʽ�������ݣ�" << endl;
				char transmit[100];
				cin.getline(transmit, 99);
				send(sconnect, transmit, strlen(transmit) + 1, 0);  //�ַ������и�������־
				memset(transmit, 0, sizeof(transmit));
			}

		}
		return 0;
	}
}