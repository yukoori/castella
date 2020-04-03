#ifndef __SERVERHANDLER_H
#define	__SERVERHANDLER_H

#include "SCSocketHandler.h"

class ServerHandler : public SCSocketHandler
{
public:
	ServerHandler();
	virtual ~ServerHandler();

	virtual int handle_close();
	virtual int handle_input();
};

#endif // !__SERVERHANDLER_H

