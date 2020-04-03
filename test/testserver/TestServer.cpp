#include <stdio.h>

#include "SCAcceptor.h"
#include "ServerHandler.h"

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
