#ifndef __SCEVENTHANDLER_H
#define __SCEVENTHANDLER_H

#include "config.h"

class SCEventHandler
{
public:
	SCEventHandler();
	virtual ~SCEventHandler();

	virtual int handle_close();
	virtual int handle_input();
	virtual int handle_output();
	virtual int handle_event();
	virtual int handle_timeout();
};

#endif	// __SCEVENTHANDLER_H