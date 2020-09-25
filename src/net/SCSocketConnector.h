#ifndef __SCSOCKETCONNECTOR_H
#define __SCSOCKETCONNECTOR_H

#include "SCSocket.h"
#include "SCTypes.h"

class SCSocketConnector
{
public:
	SCSocketConnector();
	~SCSocketConnector();

	int open(const SCChar* ip, int port);
	void close();

	int send_data(const unsigned char* send_buffer, int buffer_len);
	int recv_data(const unsigned char* recv_buffer, int buffer_len);

	// ACE 인터페이스 참고!!
	// void set_option();
	void set_timeout(int conn_timeout, int recv_timeout, int send_timeout);

protected:
private:
	// member functions
	int set_recv_timeout();
	int set_send_timeout();

	void set_nonblock();
	void set_block();

	// member values
	SC_SOCKET_HANDLE _socket;

	int		_conn_timeout;
	int		_recv_timeout;
	int		_send_timeout;
};

#endif // !__SCSOCKETCONNECTOR_H
