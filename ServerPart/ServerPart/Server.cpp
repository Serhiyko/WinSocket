#include "Server.h"

Server::Server()
{
	_Connection = _Listen = INVALID_SOCKET;
	_addrlen = sizeof(_addr);
}

bool Server::Initialize(int Port)
{
	//Winsock Startup
	WSADATA wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		cerr << "Winsock startup failed" << endl;
		return false;
	}

	// setup the host_addr structure for use in bind call
	_addr.sin_family = AF_INET;
	_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	_addr.sin_port = htons(Port);

	return true;
}

void Server::ListenForNewConnection()
{
	//Create socket to listen for new connections
	_Listen = socket(AF_INET, SOCK_STREAM, NULL);

	//bind the address to the socket
	bind(_Listen, (SOCKADDR*)&_addr, _addrlen);
	listen(_Listen, SOMAXCONN);

	//Accept a new connection
	_Connection = accept(_Listen, (SOCKADDR*)&_addr, &_addrlen);
	if (_Connection == 0)
	{
		cerr << "Failed to accept the client's connection." << endl;
	}
	else
	{
		cout << "Client Connected" << endl;

		//send the message
		char SendMsg[256]="Welcome! Connection is Accepted.";
		send(_Connection, SendMsg, sizeof(SendMsg), NULL);

		char Msg[256];

		while (true)
		{
			int BytesRecv = recv(_Connection, Msg, sizeof(Msg), 0);
			if (BytesRecv == 0)
			{
				cout << "The client closed the connection. " << endl;
			}
			else if (BytesRecv == SOCKET_ERROR)
			{
				cout << "The client seems to be offline." << endl;
				closesocket(_Connection);
				closesocket(_Listen);
				WSACleanup();
			}
			else
			{
				Msg[BytesRecv] = 0;
				cout << "Client: " << Msg << endl;
			}

			//send the chat message to this client
			cout << "Server: ";
			cin.getline(Msg, sizeof(Msg));
			send(_Connection, Msg, sizeof(Msg), NULL);
		}
	}
}

