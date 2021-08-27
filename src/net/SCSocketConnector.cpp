#include "SCSocketConnector.h"

#ifndef WIN32
#	include <fcntl.h>
#endif

SCSocketConnector::SCSocketConnector()
	: _socket(SC_SOCKET_INVALID)
	, _conn_timeout(0)
	, _recv_timeout(0)
	, _send_timeout(0)
{

}

SCSocketConnector::~SCSocketConnector()
{
	close();
}

int SCSocketConnector::open(const SCChar* ip, int port)
{
	SC_SOCKET_DATA	wsaData;

	if (SC_STARTUP(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return SC_SOCKET_LASTERR; // 소켓 초기화 실패
	}

	// socket을 생성한다.
	_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket == SC_SOCKET_INVALID)
	{
		return SC_SOCKET_LASTERR;
	}

	struct linger ling;
	ling.l_onoff = 1;
	ling.l_linger = 0; //대기없이 바로 종료, blocking 대기시간

	if (setsockopt(_socket, SOL_SOCKET, SO_LINGER, (char*)&ling, sizeof(ling)) == -1)
	{
		return SC_SOCKET_LASTERR;
	}

	if (_recv_timeout != 0)
	{
		if (set_recv_timeout() != 0)
		{
			return SC_SOCKET_LASTERR;
		}
	}

	if (_send_timeout != 0)
	{
		if (set_send_timeout() != 0)
		{
			return SC_SOCKET_LASTERR;
		}
	}

	if (_conn_timeout != 0)
	{
		set_nonblock();
	}

	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(TOChar(ip).c_str());

	if (connect(_socket, (sockaddr*)&sin, sizeof(sockaddr_in)) != 0)
	{
		int lasterr = SC_SOCKET_LASTERR;
		if (_conn_timeout == 0)
		{
			return lasterr;
		}

		if ((lasterr != SC_SOCKET_ERR_INPROGRESS) && (lasterr != SC_SOCKET_ERR_WOULDBLOCK))
		{
			return lasterr;
		}

		fd_set rset, wset;
		struct timeval tm;

		// 연결 타임아웃은 일단 5초로 하드코딩한다.
		tm.tv_sec = _conn_timeout;
		tm.tv_usec = 0;

		FD_ZERO(&rset);
		FD_SET(_socket, &rset);
		FD_ZERO(&wset);
		FD_SET(_socket, &wset);

		int ret = select(_socket + 1, &rset, &wset, NULL, &tm);
		if (ret == 0)
		{
			// timeout
			set_block();
			return SC_SOCKET_ERR_TIMEOUT;
		}

		if (!FD_ISSET(_socket, &rset) && !FD_ISSET(_socket, &wset))
		{
			set_block();
			return -1;
		}

		int err = 0;
#if defined(_WIN32) || defined(_WIN64)
		int len = sizeof(err);
		ret = getsockopt(_socket, SOL_SOCKET, SO_ERROR, (char*)&err, &len);
#elif defined(_HPUX_)
		int len = sizeof(err);
		ret = getsockopt(_socket, SOL_SOCKET, SO_ERROR, &err, &len);
#else
		socklen_t len = sizeof(err);
		ret = getsockopt(_socket, SOL_SOCKET, SO_ERROR, &err, &len);
#endif	// defined(_WIN32) || defined(_WIN64)	
		if (ret < 0)
		{
			set_block();
			return -1;
		}

		if (err != 0)
		{
			set_block();
			return err;
		}
	}

	if (_conn_timeout != 0)
	{
		set_block();
	}

	return 0;
}

void SCSocketConnector::close()
{
	if (_socket != SC_SOCKET_INVALID)
	{
#if !defined(_WIN32) && !defined(_WIN64)
		shutdown(_socket, SHUT_RDWR);
#endif  // defined(_WIN32) || defined(_WIN64)
		SC_SOCKET_CLOSE(_socket);
	}
	_socket = SC_SOCKET_INVALID;
	SC_CLEANUP();
}

int SCSocketConnector::send_data(const unsigned char* send_buffer, int buffer_len)
{
	SC_SOCKET_SET_LASTERR(0);

	int	nTotal = 0;
	char* pBuf = reinterpret_cast<char*>(const_cast<unsigned char*>(send_buffer));
	int	nBuf = buffer_len;

	while (nTotal < buffer_len)
	{
		int nSend = SC_SOCKET_SEND(_socket, pBuf, nBuf, 0);
		if (nSend <= 0)
		{
			int lasterr = SC_SOCKET_LASTERR;
			if ((lasterr == SC_SOCKET_ERR_TIMEOUT) ||
				(lasterr == SC_SOCKET_ERR_NETRESET) ||
				(lasterr == SC_SOCKET_ERR_CONNRESET) ||
				(lasterr == SC_SOCKET_ERR_NOTCONN) ||
				(lasterr == SC_SOCKET_ERR_CONNABORTED))
			{
				return lasterr;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			nTotal += nSend;
			pBuf += nSend;
			nBuf -= nSend;
		}
	}
	return nTotal;
}

int SCSocketConnector::recv_data(const unsigned char* recv_buffer, int buffer_len)
{
	SC_SOCKET_SET_LASTERR(0);

	if (buffer_len <= 0 || recv_buffer == NULL)
	{
		return -1;
	}

	int nTotal = 0;
	int nBuf = buffer_len;
	char* pBuf = reinterpret_cast<char*>(const_cast<unsigned char*>(recv_buffer));

	while (nTotal < buffer_len)
	{
		int nRecv = SC_SOCKET_READ(_socket, (char*)pBuf, nBuf, 0);
		if (nRecv <= 0)
		{
			int lasterr = SC_SOCKET_LASTERR;
			if ((lasterr == SC_SOCKET_ERR_TIMEOUT) ||
				(lasterr == SC_SOCKET_ERR_NETRESET) ||
				(lasterr == SC_SOCKET_ERR_CONNRESET) ||
				(lasterr == SC_SOCKET_ERR_NOTCONN) ||
				(lasterr == SC_SOCKET_ERR_CONNABORTED))
			{
				return lasterr;
			}
			else
			{
				return -1;
			}
		}

		nTotal += nRecv;
		pBuf += nRecv;
		nBuf -= nRecv;
	}

	return nTotal;
}

void SCSocketConnector::set_timeout(int conn_timeout, int recv_timeout, int send_timeout)
{
	_conn_timeout = conn_timeout;
	_recv_timeout = recv_timeout;
	_send_timeout = send_timeout;
}

int SCSocketConnector::set_recv_timeout()
{
	// 소켓 옵션 설정
	struct timeval tv;
	tv.tv_usec = 0;

#ifndef WIN32
	tv.tv_sec = _recv_timeout;
#else   // WIN32  
	tv.tv_sec = _recv_timeout * 1000;
#endif  // WIN32

	if (setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv)) == -1)
	{
		return -1;
	}

	return 0;
}

int SCSocketConnector::set_send_timeout()
{
	// 소켓 옵션 설정
	struct timeval tv;
	tv.tv_usec = 0;

#ifndef WIN32
	tv.tv_sec = _send_timeout;
#else   // WIN32  
	tv.tv_sec = _send_timeout * 1000;
#endif  // WIN32

	if (setsockopt(_socket, SOL_SOCKET, SO_SNDTIMEO, (char*)&tv, sizeof(tv)) == -1)
	{
		return -1;
	}

	return 0;
}

void SCSocketConnector::set_nonblock()
{
	int             flags = 0;
	unsigned long   lflags = 1;
#ifdef WIN32
	flags = ioctlsocket(_socket, FIONBIO, &lflags);
#else
	flags = fcntl(_socket, F_GETFL, 0);
	fcntl(_socket, F_SETFL, flags | O_NONBLOCK);
#endif

	return;
}

void SCSocketConnector::set_block()
{
	int             flags = 0;
	unsigned long   lflags = 0;
#ifdef WIN32
	flags = ioctlsocket(_socket, FIONBIO, &lflags);
#else
	flags = fcntl(_socket, F_GETFL, 0);
	fcntl(_socket, F_SETFL, flags & 0x7f);
#endif

	return;
}