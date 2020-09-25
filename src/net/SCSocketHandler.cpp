#include "SCSocketHandler.h"

SCSocketHandler::SCSocketHandler()
	: _time_out(30)
	, _peer_port(0)
	, _terminate(false)
	, _socket(SC_SOCKET_INVALID)
{
	memset(_peer_addr, 0x00, MAX_IP_LEN);
};

SCSocketHandler::~SCSocketHandler()
{
	Close();
}

int SCSocketHandler::Open()
{
	return 0;
}

void SCSocketHandler::Close()
{
	// 맺었던 소켓을 종료한다.
	if (_terminate == true)
	{
		return;
	}

	if (_socket != SC_SOCKET_INVALID)
	{
		SC_SOCKET_CLOSE(_socket);
	}

	_socket = SC_SOCKET_INVALID;
	_terminate = true;
	return;
}

bool SCSocketHandler::IsTerminate()
{ 
	return _terminate;
}

void SCSocketHandler::peer(const SCChar* ip, int port)
{
	STRNCPY(_peer_addr, ip, STRLEN(ip));
	_peer_port = port;
}

const SCChar* SCSocketHandler::peer_addr() const
{
	return _peer_addr;
}

int SCSocketHandler::peer_port() const
{
	return _peer_port;
}

void SCSocketHandler::time_out(long time_out)
{
	_time_out = time_out;
}

long SCSocketHandler::time_out()
{
	return _time_out;
}

void SCSocketHandler::socket(SC_SOCKET_HANDLE& socket)
{
	_socket = socket;
}

SC_SOCKET_HANDLE SCSocketHandler::socket()
{
	return _socket;
}
