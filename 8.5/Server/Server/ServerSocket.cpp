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

	char buf[500];
	while (true) {
		Datablock client_send;

		cout << "输入(start)开始更改，输入(end)结束服务：" << endl;

		cout << "输入发送内容：";
		while (cin.getline(buf, 500))
		{


			string rcover = buf;
			if (rcover == "end")break;
			if (rcover == "start") {
				cout << "请以m1-m2-m3-m_roll-m_pitch-m_rotate格式输入数据：" << endl;
				char transmit[100];
				cin.getline(transmit, 99);
				send(sconnect, transmit, strlen(transmit) + 1, 0);  //字符串还有个结束标志
				memset(transmit, 0, sizeof(transmit));
			}

		}
		return 0;
	}
}