#include"Server.h"
#include<memory>

int main()
{
	auto_ptr<Server>MyServer(new Server);

	if (MyServer->Initialize(4444))
	{
		MyServer->ListenForNewConnection();
	}

	system("pause");
	return 0;
}