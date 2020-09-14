#ifndef __SCMESSAGEBLOCK_H
#define __SCMESSAGEBLOCK_H

#include <string>

class SCMessageBlock
{
public:
	enum {
		MB_DATA = 0x00,
		MB_SEND,
		MB_RECV,
		MB_START,
		MB_STOP,
		MB_USER
	};

	SCMessageBlock();
	explicit SCMessageBlock(const char* data);
	SCMessageBlock(const SCMessageBlock& o);
	~SCMessageBlock();
	SCMessageBlock& operator=(const SCMessageBlock& o);

	friend bool operator==(const SCMessageBlock& o1, const SCMessageBlock& o2);

	// support single
	void copy(const char* data);
	void copy(const unsigned char* data, const size_t length);

	void msg_type(int type);
	int msg_type() const;

	const size_t length() const;
	const size_t size() const;
	const char* base() const;

	char* rd_ptr() const;
	char* wr_ptr() const;
	
	void rd_ptr(const size_t pos);
	void wr_ptr(const size_t pos);

	void release();

	// support continuation
	SCMessageBlock* cont() const;
	void cont(SCMessageBlock* mb);

protected:
	void assign(const SCMessageBlock& o);

private:
	// member fucntions
	bool resize(size_t need);

	// member values
	// support single
	int				_msg_type;

	unsigned char*	_data;
	size_t			_size;

	size_t			_rd_ptr;
	size_t			_wr_ptr;

	// support continuation
	SCMessageBlock*	_cont;
};

#endif //! __SCMESSAGEBLOCK_H

