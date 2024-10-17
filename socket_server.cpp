#include <winsock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
using namespace std;


DWORD WINAPI ThreadFun(LPVOID lpThreadParameter);

int main()
{
	WSADATA wd;
	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)
	{
		cout << "WSAStartup Error:" << WSAGetLastError() << endl;
		return 0;
	}


	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET)
	{
		cout << "socket error:" << WSAGetLastError() << endl;
		return 0;
	}


	sockaddr_in addr;
	memset(&addr, 0, sizeof(sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int len = sizeof(sockaddr_in);
	if (bind(s, (SOCKADDR*)&addr, len) == SOCKET_ERROR)
	{
		cout << "bind Error:" << WSAGetLastError() << endl;
		return 0;
	}


	listen(s, 5);
	cout << "Server is listening!" << endl;

	while (true)
	{
		sockaddr_in addrClient;
		len = sizeof(sockaddr_in);

		SOCKET c = accept(s, (SOCKADDR*)&addrClient, &len);
		if (c != INVALID_SOCKET)
		{

			HANDLE hThread = CreateThread(NULL, 0, ThreadFun, (LPVOID)c, 0, NULL);
			CloseHandle(hThread);
		}

	}

	closesocket(s);
	WSACleanup();
	return 0;
}

DWORD WINAPI ThreadFun(LPVOID lpThreadParameter)
{

	SOCKET c = (SOCKET)lpThreadParameter;

	cout  << c << "is conneted!" << endl;

	char buf[100] = { 0 };
	sprintf(buf, "Welcome %d to the chat room!", c);
	send(c, buf, 100, 0);

	int ret;
	do
	{
		char buf2[100] = { 0 };
		ret = recv(c, buf2, 100, 0);
		cout << c << " say:" << buf2 << endl;

	} while (ret != SOCKET_ERROR && ret != 0);

	cout << c << "left the chat room!";

	return 0;
}
