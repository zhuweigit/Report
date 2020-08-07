 
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

	cout << "服务器启动！....." << endl;
	//初始化winsock   
	WSADATA wsaD;
	WSAStartup(MAKEWORD(1, 1), &wsaD);
	//创建监听套接字   
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// 绑定主机地址和监听套接字   
	struct sockaddr_in my_addr;   //主机地址   
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(3030); //指定端口   
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(slisten, (struct sockaddr *)&my_addr, sizeof(my_addr));
	//启动监听   
	listen(slisten, 5);    //5是最大连接数
						   //开始接收数据   
	struct sockaddr_in c_addr;  //客户地址   
	int addr_len = sizeof(c_addr);
	SOCKET sconnect = accept(slisten, (struct sockaddr*)&c_addr, &addr_len); //通过监听套接字创建连接套接字   
	
	cout << "连接已建立......" << endl;
 	cout << "输入发送内容："<<endl;
	char buf1[500];
	char buf2[500];
	while (true) 
	{
	  //发信
	  char transmit[100];
	  thread t1(SendMessage1, sconnect, transmit, strlen(transmit) + 1, 0);
	  t1.detach();

	  //收信
	  memset(buf2, '\0', sizeof(buf2));
	  int len = recv(sconnect, buf2, sizeof(buf2), 0);  //通过连接套接字接收数据
	  if (len > 0)
	  {
		  cout << "客户端说：" << buf2 << endl;
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