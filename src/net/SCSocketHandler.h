#ifndef __SCSOCKETHANDLER_H
#define __SCSOCKETHANDLER_H

#include "SCTypes.h"
#include "SCSocket.h"
#include "SCEventHandler.h"

class SCSocketHandler : public SCEventHandler
{
public:
	SCSocketHandler();
	virtual ~SCSocketHandler();

	virtual int Open();
	virtual void Close();

	// 
	bool IsTerminate();
	//
	void peer(const SCChar* ip, int port);
	const SCChar* peer_addr() const;
	int peer_port() const;

	// 
	void time_out(long time_out);
	long time_out();

	// 
	void socket(SC_SOCKET_HANDLE& socket);
	SC_SOCKET_HANDLE socket();

protected:
	// member functions

	// member values
	long				_time_out;

	SCChar				_peer_addr[MAX_IP_LEN];
	int					_peer_port;

	bool				_terminate;
	SC_SOCKET_HANDLE	_socket;
};

#endif	// __SCSOCKETHANDLER_H

