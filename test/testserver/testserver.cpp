#include <stdio.h>

#include "SCAcceptor.h"
#include "SCSocketHandler.h"

class ServerHandler : public SCSocketHandler
{
public:
	ServerHandler()
	{

	}

	virtual ~ServerHandler()
	{

	}

	virtual int handle_close()
	{
		this->Close();
		return 0;
	}

	virtual int handle_input()
	{
		const int BUFFER_SIZE = 2048;
		char buffer[BUFFER_SIZE] = { '\0', };
		int nRecv = SC_SOCKET_READ(_socket, buffer, BUFFER_SIZE, 0);
		if (nRecv <= 0)
		{
			this->handle_close();
			return -1;
		}

		SCPRINTF(SCTEXT("Recv Data = %hs"), buffer);

		SC_SOCKET_SEND(_socket, "ok", (int)strlen("ok"), 0);

		return 0;
	}
};

int main(int argc, char* argv[])
{
	SCAcceptor<ServerHandler> acceptor;
	acceptor.ip(SCTEXT("127.0.0.1"));
	acceptor.port(18081);
	
	int nRet = acceptor.Open();
	if (nRet != 0)
	{
		SCPRINTF(SCTEXT("Fail to open acceptor. %s::%d"), acceptor.ip(), acceptor.port());
		return -1;
	}

	acceptor.Close();
	return 0;
}
