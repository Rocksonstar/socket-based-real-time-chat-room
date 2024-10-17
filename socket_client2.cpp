#include<winsock2.h>
#include<iostream>
#include<Ws2tcpip.h>
using  namespace std;


#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
int  main()
{

	//generate winsock2 eviroment
	WSADATA  wd;
	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)
	{
		cout << "WSAStartup  error：" << GetLastError() << endl;
		return 0;
	}

	//create socket
	SOCKET  s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET)
	{
		cout << "socket  error：" << GetLastError() << endl;
		return 0;
	}

	//connect server
	sockaddr_in   addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int len = sizeof(sockaddr_in);
	if (connect(s, (SOCKADDR*)&addr, len) == SOCKET_ERROR)
	{
		cout << "connect  error：" << GetLastError() << endl;
		return 0;
	}

	while (1) {
		char buf[100] = { 0 };
		cout << "Please enter text:";
		cin >> buf;
		int ret = send(s, buf, strlen(buf), 0);

		char buf2[100] = { 0 };
		int receive = recv(s, buf2, sizeof(buf2), 0);
		cout << buf2 << endl;
	}

	//close socket
	closesocket(s);

	//clear winsock2 eviroment
	WSACleanup();



	return 0;
}
