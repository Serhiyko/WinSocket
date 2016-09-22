#include"Client.h"
#include<memory>

int main()
{
	auto_ptr<Client>MyClient(new Client);

	if (MyClient->Initialize())
	{
		MyClient->Connect();
	}

	system("pause");
	return 0;
}