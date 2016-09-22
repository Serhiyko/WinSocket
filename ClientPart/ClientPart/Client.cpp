#include "Client.h"

Client::Client()
{
	_Connection = INVALID_SOCKET;
	_sizeofaddr = sizeof(_addr);
}

bool Client::Initialize()
{
	//Winsock Startup
	WSADATA wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		cerr << "Winsock startup failed" << endl;
		return false;
	}

	_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //Address = localhost (this pc)
	_addr.sin_port = htons(4444); //Port = 4444
	_addr.sin_family = AF_INET; //IPv4 Socket

	return true;
}

void Client::Connect()
{
	_Connection = socket(AF_INET, SOCK_STREAM, NULL); //Set Connection socket
	if (connect(_Connection, (SOCKADDR*)&_addr, _sizeofaddr) != 0)
	{
		cerr << "Failed to Connect" << endl;
	}

	cout << "Connected" << endl;
	while (true)
	{
		//Receive Message
		char Msg[256];
		recv(_Connection, Msg, sizeof(Msg), NULL);
		std::cout << "Server:" << Msg << std::endl;

		//Send Message
		char *SendText = new char[256];

		cout << "Client: ";
		cin.getline(SendText, 256, '\n');

		if (strcmp(SendText, "exit") == 0) 
		{
			closesocket(_Connection);
			WSACleanup();
			exit(1);
		}

		if (send(_Connection, SendText, strlen(SendText), 0) == SOCKET_ERROR)
		{
			cout << "Server probably down. " << endl;
			closesocket(_Connection);
			WSACleanup();
		}

		delete[] SendText;
	}
}
