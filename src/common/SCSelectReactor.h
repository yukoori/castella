#ifndef __SCSELECTREACTOR_H
#define	__SCSELECTREACTOR_H

#include "SCSocket.h"
#include "SCTask.h"
#include "SCEventHandler.h"
#include "SCMutex.h"

#include <map>

class SCSelectReactor : public SCTask
{
public:
	typedef SCTask super;

	SCSelectReactor();
	~SCSelectReactor();

	int set_handler(SC_SOCKET_HANDLE handle, SCEventHandler* handler);
	void remove_handler(SC_SOCKET_HANDLE handle);

private:
	virtual	int svc();

	void set_sockethandle(fd_set& fdset, int& maxfd);
	SCEventHandler* find_handler(fd_set& fdset, SC_SOCKET_HANDLE& handle);

	// member values
	SCMutex	_mutex;

	std::map<SC_SOCKET_HANDLE, SCEventHandler*> _map_handler;
};

#endif // !__SCSELECTREACTOR_H
