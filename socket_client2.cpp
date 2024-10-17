#include <winsock2.h>
#include <iostream>
#include <Ws2tcpip.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

int main()
{
    // Generate winsock2 environment
    WSADATA wd;
    if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)
    {
        cout << "WSAStartup error: " << GetLastError() << endl;
        return 0;
    }

    // Create socket
    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
    {
        cout << "socket error: " << GetLastError() << endl;
        return 0;
    }

    // Connect to server
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int len = sizeof(sockaddr_in);
    if (connect(s, (SOCKADDR*)&addr, len) == SOCKET_ERROR)
    {
        cout << "connect error: " << GetLastError() << endl;
        return 0;
    }

    while (true) {
        char buf[1024] = { 0 };
        cout << "Please enter text: ";
        cin.getline(buf, sizeof(buf));

        int ret = send(s, buf, strlen(buf) + 1, 0);

        if (ret == SOCKET_ERROR) {
            cout << "send error: " << GetLastError() << endl;
            break;
        }

        char buf2[1024] = { 0 };
        int receive = recv(s, buf2, sizeof(buf2), 0);
        if (receive > 0) {
            cout << "Server says: " << buf2 << endl;
        }
        else {
            cout << "recv error: " << GetLastError() << endl;
            break;
        }
    }

    // Close socket
    closesocket(s);

    // Clear winsock2 environment
    WSACleanup();

    return 0;
}
