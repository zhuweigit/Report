 
#include<vector>
#include <thread>
#include <string>   
#include <iostream> 
#include <winsock2.h>   
#pragma comment(lib,"ws2_32.lib")   
using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::thread;

 

void SendMessage1(SOCKET sconnect, char* transmit, int len, int);
 

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
 	cout << "���뷢�����ݣ�"<<endl;
	char buf1[500];
	char buf2[500];
	while (true) 
	{
	  //����
	  char transmit[100];
	  thread t1(SendMessage1, sconnect, transmit, strlen(transmit) + 1, 0);
	  t1.detach();

	  //����
	  memset(buf2, '\0', sizeof(buf2));
	  int len = recv(sconnect, buf2, sizeof(buf2), 0);  //ͨ�������׽��ֽ�������
	  if (len > 0)
	  {
		  cout << "�ͻ���˵��" << buf2 << endl;
	  }
	  


		  
	}
		 
}

void SendMessage1(SOCKET sconnect, char* transmit, int len, int)
{
	while (true)
	{
		memset(transmit, '\0', sizeof(transmit));
		cin.getline(transmit, 99);
		send(sconnect, transmit, strlen(transmit) + 1, 0);
		memset(transmit, '\0', sizeof(transmit));
	}
	
}