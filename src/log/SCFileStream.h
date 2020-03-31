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

	virtual void print(const SCChar* record);

	// setter & getter
	void path(const SCChar* pPath);
	const SCChar* path() const;

	void componet(const SCChar* pComponent);
	const SCChar* componet() const;

	const SCString getFileName() const;

protected:
private:
	SCString	_path;
	SCString	_component;

	SCOFStream*	_output;
};

#endif // !__SCFILESTREAM_H
