#include "SCSelectReactor.h"

#include "SCOS.h"
#include "SCTypes.h"

SCSelectReactor::SCSelectReactor()
{
	super::Open();
}

SCSelectReactor::~SCSelectReactor()
{
	SCMutexMgr mutex(_mutex);

	std::map<SC_SOCKET_HANDLE, SCEventHandler*>::iterator iter_s = _map_handler.begin();
	std::map<SC_SOCKET_HANDLE, SCEventHandler*>::iterator iter_e = _map_handler.end();
	for (; iter_s != iter_e; ++iter_s )
	{
		if (iter_s->second != NULL)
		{
			iter_s->second->handle_close();
			delete iter_s->second;
			iter_s->second = NULL;
		}
	}
	_map_handler.clear();

	super::Close();
}

int SCSelectReactor::set_handler(SC_SOCKET_HANDLE handle, SCEventHandler* handler)
{
	SCMutexMgr mutex(_mutex);

	std::map<SC_SOCKET_HANDLE, SCEventHandler*>::iterator iter = _map_handler.find(handle);
	if (iter != _map_handler.end())
	{
		// 이미 등록되어 있는 경우
		return -1;
	}

	_map_handler.insert(std::pair<SC_SOCKET_HANDLE, SCEventHandler*>(handle, handler));
	return 0;
}

void SCSelectReactor::remove_handler(SC_SOCKET_HANDLE handle)
{
	std::map<SC_SOCKET_HANDLE, SCEventHandler*>::iterator iter = _map_handler.find(handle);
	if (iter == _map_handler.end())
	{
		// 찾을 수 없다!
		return ;
	}

	iter->second->handle_close();

	_map_handler.erase(iter);
	return;
}

int SCSelectReactor::svc()
{
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	while (true)
	{
		if (_map_handler.size() <= 0)
		{
			SCOS::sleep(100);
			continue;
		}

		fd_set	fdset;
		FD_ZERO(&fdset);

		int maxfd = 0;
		this->set_sockethandle(fdset, maxfd);

#ifdef _HPUX_
		int nRet = select(maxfd + 1, (int*)&_fd_set, NULL, NULL, &tv);
#else
		int nRet = select(maxfd + 1, &fdset, NULL, NULL, &tv);
#endif
		if (nRet < 0)
		{
			if (SC_SOCKET_LASTERR == SC_SOCKET_ERR_EINTR)
			{
				continue;
			}

			break;
		}
		else if (nRet == 0)
		{
			// 
			continue;
		}

		SC_SOCKET_HANDLE handle = SC_SOCKET_INVALID;
		SCEventHandler* handler = this->find_handler(fdset, handle);
		if ((handle != SC_SOCKET_INVALID) && (handler != NULL))
		{
			int nRet = handler->handle_input();
			if (nRet != 0)
			{
				this->remove_handler(handle);
			}
		}
	}

	return 0;
}

SCEventHandler* SCSelectReactor::find_handler(fd_set& fdset, SC_SOCKET_HANDLE& handle)
{
	SCMutexMgr mutex(_mutex);

	std::map<SC_SOCKET_HANDLE, SCEventHandler*>::iterator iter_s = _map_handler.begin();
	std::map<SC_SOCKET_HANDLE, SCEventHandler*>::iterator iter_e = _map_handler.end();

	for (; iter_s != iter_e; ++iter_s)
	{
		SC_SOCKET_HANDLE temp_handle = (iter_s->first);
		if (FD_ISSET(temp_handle, &fdset))
		{
			handle = temp_handle;
			return iter_s->second;
		}
	}

	handle = SC_SOCKET_INVALID;
	return NULL;
}

void SCSelectReactor::set_sockethandle(fd_set& fdset, int& maxfd)
{
	SCMutexMgr mutex(_mutex);
	
	std::map<SC_SOCKET_HANDLE, SCEventHandler*>::iterator iter_s = _map_handler.begin();
	std::map<SC_SOCKET_HANDLE, SCEventHandler*>::iterator iter_e = _map_handler.end();
	for (; iter_s != iter_e; ++iter_s)
	{
		if (iter_s->first != SC_SOCKET_INVALID)
		{
			if (maxfd < iter_s->first)
			{
				maxfd = (int)iter_s->first;
			}
			
			FD_SET(iter_s->first, &fdset);
		}
	}

	return;
}