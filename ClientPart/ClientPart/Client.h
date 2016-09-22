#ifndef _CLIENT_H_
#define _Client_H_

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <string> 
#include <iostream>

using namespace std;

class Client
{
public:
	Client();

	bool Initialize();
	void Connect();

private:
	SOCKET _Connection;//This client's connection to the server
	SOCKADDR_IN _addr; //Address to be binded to our Connection socket
	int _sizeofaddr; //Need sizeofaddr for the connect function
};

#endif // !_CLIENT_H_