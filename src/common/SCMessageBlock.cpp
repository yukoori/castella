#include "SCMessageBlock.h"

#define	BLOCK_SIZE	2048

SCMessageBlock::SCMessageBlock()
	: _data(NULL)
	, _size(0)
	, _rd_ptr(0)
	, _wr_ptr(0)
{

}

SCMessageBlock::SCMessageBlock(const char* data)
	: _rd_ptr(0)
	, _wr_ptr(0)
{
	set(data);
}

SCMessageBlock::~SCMessageBlock()
{

}

void SCMessageBlock::set(const char* data)
{
	const size_t data_length = strlen(data);
	resize(data_length);
	
	memcpy(&_data[_wr_ptr], data, data_length);
	wr_ptr(data_length);

	return;
}

void SCMessageBlock::set(const unsigned char* data, const size_t length)
{
	resize(length);

	memcpy(_data, data, length);
	wr_ptr(length);

	return;
}

const size_t SCMessageBlock::length() const
{
	return _wr_ptr - _rd_ptr;
}

const char* SCMessageBlock::get() const
{
	return (char*)_data;
}

const char* SCMessageBlock::rd_ptr() const
{
	return (char*)(_data + _rd_ptr);
}

const char* SCMessageBlock::wr_ptr() const
{
	return (char*)(_data + _wr_ptr);
}

void SCMessageBlock::rd_ptr(const size_t pos)
{
	_rd_ptr += pos;
}

void SCMessageBlock::wr_ptr(const size_t pos)
{
	_wr_ptr += pos;
}

bool SCMessageBlock::resize(size_t need)
{
	if (_data == NULL)
	{
		_size = BLOCK_SIZE;
		if (need > _size)
		{
			_size = need;
		}

		_data = (unsigned char*)calloc(_size, sizeof(char));
		if (_data == NULL)
		{
			return false;
		}
	}
	else
	{
		unsigned char* temp = _data;

		size_t remain = _size - _wr_ptr;
		if (need > remain)
		{
			if ((need > (remain + BLOCK_SIZE)))
			{
				_size += need;
			}
			else
			{
				_size += BLOCK_SIZE;
			}

			_data = (unsigned char*)calloc(_size, sizeof(char));
			if (_data == NULL)
			{
				return false;
			}

			memcpy(_data, temp, _wr_ptr);

			free(temp);
			temp = NULL;
		}
	}

	return true;
}

inline bool operator==(const SCMessageBlock& o1, const SCMessageBlock& o2)
{
	if (o1.length() != o2.length())
	{
		return false;
	}

	if (memcmp(o1._data, o2._data, o1.length()) != 0)
	{
		return false;
	}

	return true;
}
