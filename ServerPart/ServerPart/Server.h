#ifndef _SERVER_H_
#define _SERVER_H_
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib")

#include <WinSock2.h>
#include <iostream>

using namespace std;

class Server
{
public: 
	Server();

	bool Initialize(int);
	void ListenForNewConnection();

private:
	SOCKET _Connection;
	SOCKADDR_IN _addr;
	int _addrlen;
	SOCKET _Listen;
};

#endif // !_SERVER_H_