#include "ServerHandler.h"

ServerHandler::ServerHandler()
{

}

ServerHandler::~ServerHandler()
{

}

int ServerHandler::handle_close()
{
	this->Close();
	return 0;
}

int ServerHandler::handle_input()
{
	const int BUFFER_SIZE = 2048;
	char buffer[BUFFER_SIZE] = { '\0', };
	int nRecv = SC_SOCKET_READ(_socket, buffer, BUFFER_SIZE, 0);
	if (nRecv <= 0)
	{
		SCPRINTF(SCTEXT("Fail to recv %d\n"), nRecv);
		this->handle_close();
		return -1;
	}

	SCPRINTF(SCTEXT("Recv Data = %hs\n"), buffer);

	SC_SOCKET_SEND(_socket, "ok", (int)strlen("ok"), 0);

	return 0;
}
