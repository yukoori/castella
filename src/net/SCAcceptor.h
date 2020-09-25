#ifndef	__SCACCEPTOR_H
#define __SCACCEPTOR_H

#include <string>

#include "SCTypes.h"
#include "SCSocket.h"
#include "SCSelectReactor.h"

template<class T>
class SCAcceptor
{
public:
	SCAcceptor();
	virtual ~SCAcceptor();

	int		Open();
	void	Close();

	// setter & getter
	void	ip( const SCChar* ip )
	{
		STRNCPY( _ip, ip, STRLEN(ip) );
	}
	const SCChar* ip()
	{ 
		return _ip;
	}

	void port( int port )
	{
		_port = port;
	}
	int port()
	{ 
		return _port;
	}

protected:
	// member functions
	int		accept_loop();
	virtual T* make_handler();

	// member values
	SCChar		_ip[MAX_IP_LEN];
	int			_port;

	SC_SOCKET_HANDLE	_socket;

	SCSelectReactor		_reactor;
};

//////////////////////////////////////////////////////////////////////////
template<class T>
SCAcceptor<T>::SCAcceptor()
	: _port(0)
	, _socket(SC_SOCKET_INVALID)
{
	memset(_ip, 0x00, MAX_IP_LEN);
}

template<class T>
SCAcceptor<T>::~SCAcceptor()
{
	Close();
}

template<class T>
int SCAcceptor<T>::Open()
{
	SC_SOCKET_DATA	wsaData;

	if( SC_STARTUP( MAKEWORD(2,2), &wsaData) != 0 )
	{
		return SC_SOCKET_LASTERR; // 소켓 초기화 실패
	}

	// socket을 생성한다.
	_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(_socket == SC_SOCKET_INVALID )
	{
		return SC_SOCKET_LASTERR;
	}

	SC_SOCKET_OPT_VALUE optval = SC_SOCKET_OPT_INIT;
	if ( setsockopt(_socket,  SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == SC_SOCKET_INVALID)
	{
		return SC_SOCKET_LASTERR;
	}

	//fill in sockaddr_in struct 
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons( _port );
	sin.sin_addr.s_addr = htonl(INADDR_ANY);

	//bind to the socket
	int nRet = bind(_socket, (struct sockaddr*)&sin, sizeof(sin));
	if( nRet == SC_SOCKET_INVALID)
	{
		return SC_SOCKET_LASTERR;
	}

	//Listen to the desire port on which client suppose to connect
	nRet = listen( _socket, MAX_SOCKET_COUNT );	
	if( nRet == SC_SOCKET_INVALID)
	{
		return SC_SOCKET_LASTERR;
	}

	this->accept_loop();

	return 0;
}

template<class T>
void SCAcceptor<T>::Close()
{
	SC_SOCKET_CLOSE(_socket);
	SC_CLEANUP();
}

template<class T>
int SCAcceptor<T>::accept_loop()
{
	while( true )
	{
		struct sockaddr_in client_addr;
		SC_SOCKET_ADDR_LEN client_addr_len = sizeof(client_addr);
#ifdef	WIN32
		SC_SOCKET_HANDLE client = accept(_socket, reinterpret_cast<struct sockaddr *>(&client_addr), reinterpret_cast<int*>(&client_addr_len));
#elif	__HP__
		SC_SOCKET_HANDLE client = accept(_socket, (struct sockaddr *)&client_addr, (int*)&client_addr_len);
#else
		SC_SOCKET_HANDLE client = accept(_socket, (struct sockaddr *)&client_addr, &client_addr_len);
#endif	// WIN32
		if(client == SC_SOCKET_INVALID)
		{
			SC_SOCKET_CLOSE(client);
			continue;
		}

		struct	sockaddr_in peer_addr;
		SC_SOCKET_ADDR_LEN peer_addr_len = sizeof(peer_addr);
#ifdef	WIN32
		::getpeername(client, reinterpret_cast<struct sockaddr *>(&peer_addr), &peer_addr_len);
#elif	__HP__
		getpeername(client, (struct sockaddr *)&peer_addr, &peer_addr_len);
#else
		getpeername(client, (struct sockaddr *)&peer_addr, (socklen_t *)&peer_addr_len);
#endif	// WIN32
		
		T* handler = make_handler();
		handler->socket(client);
		handler->peer(TOSCChar(inet_ntoa(client_addr.sin_addr)).c_str(), client_addr.sin_port);

		int nRet = _reactor.set_handler(client, handler);
		if( nRet != 0 )
		{
			SC_SOCKET_CLOSE(client);
			continue;
		}
	}
}

template<class T>
T* SCAcceptor<T>::make_handler()
{
	// SCAcceptor 클래스의 accept_loop()에서 설정하는 정보(socket과 peer)외의
	// 값을 설정해야 한다면 make_handler 함수를 overriding 한다.
	return (new T);
}

#endif	// __ACCEPTOR_H

