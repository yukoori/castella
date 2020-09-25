#ifndef __SCSOCKET_H
#define __SCSOCKET_H

#if	defined(_WIN32) || defined(_WIN64)
#	include		<windows.h>
#	define		SC_STARTUP(a, b)				WSAStartup(a, b)
#	define		SC_SOCKET_DATA					WSADATA
#	define		SC_SOCKET_HANDLE				SOCKET
#	define		SC_SOCKET_ADDR_LEN				int
#	define		SC_SOCKET_INVALID				INVALID_SOCKET
#	define		SC_SOCKET_ERR_EINTR				WSAEINTR
#	define		SC_SOCKET_ERR_TIMEOUT			WSAETIMEDOUT
#	define		SC_SOCKET_ERR_NETRESET			WSAENETRESET
#	define		SC_SOCKET_ERR_CONNRESET			WSAECONNRESET
#	define		SC_SOCKET_ERR_NOTCONN			WSAENOTCONN
#	define		SC_SOCKET_ERR_CONNABORTED		WSAECONNABORTED
#	define		SC_SOCKET_ERR_WOULDBLOCK		WSAEWOULDBLOCK
#	define		SC_SOCKET_ERR_INPROGRESS		WSAEINPROGRESS
#	define		SC_SOCKET_OPT_VALUE				char
#	define		SC_SOCKET_OPT_INIT				0x01
#	define		SC_SOCKET_SEND(a, b, c, d)		send(a, b, c, d)
#	define		SC_SOCKET_READ(a, b, c, d)		recv(a, b, c, d)
#	define		SC_SOCKET_LASTERR				WSAGetLastError()
#	define		SC_SOCKET_SET_LASTERR(err)		WSASetLastError(err)
#	define		SC_SOCKET_CLOSE					closesocket
#	define		SC_CLEANUP()					WSACleanup()
#	define		MAX_SOCKET_COUNT				SOMAXCONN
#else
#	include		<errno.h>
#	include		<unistd.h>
#	include		<arpa/inet.h>
#	include		<sys/types.h>
#	include		<sys/socket.h>
#	define		SC_STARTUP(a, b)				0
#	define		SC_MAKEWORD(a, b)
#	define		SC_SOCKET_DATA					int
#	define		SC_SOCKET_HANDLE				int
#	define		SC_SOCKET_ADDR_LEN				socklen_t
#	define		SC_SOCKET_INVALID				-1
#	define		SC_SOCKET_ERROR					-1
#	define		SC_SOCKET_ERR_EINTR				EINTR
#	define		SC_SOCKET_ERR_TIMEOUT			ETIMEDOUT
#	define		SC_SOCKET_ERR_NETRESET			ENETRESET
#	define		SC_SOCKET_ERR_CONNRESET			ECONNRESET
#	define		SC_SOCKET_ERR_NOTCONN			ENOTCONN
#	define		SC_SOCKET_ERR_CONNABORTED		ECONNABORTED
#	define		SC_SOCKET_ERR_WOULDBLOCK		EWOULDBLOCK
#	define		SC_SOCKET_ERR_INPROGRESS		EINPROGRESS
#	define		SC_SOCKET_OPT_VALUE				int
#	define		SC_SOCKET_OPT_INIT				0x01
#	define		SC_SOCKET_SEND(a, b, c, d)		send(a, b, c, d)
#	define		SC_SOCKET_READ(a, b, c, d)		read(a, b, c)
#	define		SC_SOCKET_LASTERR				errno
#	define		SC_SOCKET_SET_LASTERR(err)		errno = err
#	define		SC_SOCKET_CLOSE					close
#	define		SC_CLEANUP()
extern	int		errno;
#	define		MAX_SOCKET_COUNT				5
#endif	// defined(_WIN32) || defined(_WIN64)

#define		MAX_IP_LEN		256

#endif // !__SCSOCKET_H
