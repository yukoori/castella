#ifndef __SCFILESTREAM_H
#define	__SCFILESTREAM_H

#include "SCLogStream.h"

#include <fstream>

class SCFileStream : public SCLogStream
{
public:
	SCFileStream();
	~SCFileStream();

	virtual int open();
	virtual int close();

	virtual void print(const SCChar* record, ELogLevel level);

	// setter & getter
	void path(const SCChar* path);
	const SCChar* path() const;

	void componet(const SCChar* component);
	const SCChar* componet() const;

	const SCString getFileName() const;

protected:
private:
	//
	void create_directory(const SCChar* path);
	bool exist(const SCChar* path);

	// 
	SCString	_path;
	SCString	_component;

	SCOFStream*	_output;
};

#endif // !__SCFILESTREAM_H
