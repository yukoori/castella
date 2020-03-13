#ifndef __LOGTESTTASK_H
#define	__LOGTESTTASK_H

#include "SCTask.h"
#include "SCLogger.h"

class LogTestTask : public SCWindowsTask
{
public:
	LogTestTask();
	~LogTestTask();

	void setLogger(SCLogger& logger);
	void setSid(int sid);

protected:
private:
	virtual	int svc();

	int			_sid;
	SCLogger*	_logger;
};

#endif // !__LOGTESTTASK_H
