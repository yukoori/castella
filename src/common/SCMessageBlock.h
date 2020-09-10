#ifndef __SCMESSAGEBLOCK_H
#define __SCMESSAGEBLOCK_H

#include <string>

class SCMessageBlock
{
public:
	SCMessageBlock();
	explicit SCMessageBlock(const char* data);
	~SCMessageBlock();

	friend bool operator==(const SCMessageBlock& o1, const SCMessageBlock& o2);

	void set(const char* data);
	void set(const unsigned char* data, const size_t length);

	const size_t length() const;
	const char* get() const;

	const char* rd_ptr() const;
	const char* wr_ptr() const;

	void rd_ptr(const size_t pos);
	void wr_ptr(const size_t pos);

protected:
private:
	// member fucntions
	bool resize(size_t need);

	// member values
	unsigned char*	_data;
	size_t			_size;

	size_t			_rd_ptr;
	size_t			_wr_ptr;
};

#endif //! __SCMESSAGEBLOCK_H

