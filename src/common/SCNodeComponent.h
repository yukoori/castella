#ifndef __SCNODECOMPONENT_H
#define __SCNODECOMPONENT_H

#include "SCTypes.h"

/// \class		SCNodeComponent
/// \brief		abstract class of nodes, this class define virtual function to implement
class	SCNodeComponent
{
public:
	typedef enum {
		T_SESSION = 0,
		T_KEY,
		T_VALUE
	} ComponentType;

	SCNodeComponent()
		: _value(SCTEXT(""))
		, _type(T_VALUE)
	{

	};

	virtual	~SCNodeComponent()
	{

	};
	
	SCNodeComponent(const SCNodeComponent& o)
	{ 
		assign(o); 
	}

	SCNodeComponent& operator=(const SCNodeComponent& o)
	{
		assign(o);
		return *this;
	}

	// virtual function
	virtual	int add(const SCNodeComponent*) = 0;
	virtual int remove(const SCNodeComponent*) = 0;
	virtual const SCNodeComponent* getChild(int) const = 0;
	virtual	int size() const = 0;

	// setter & getter
	void	set_value( const SCString& value )
	{
		_value = value;
	}

	const SCString&	get_value() const
	{ 
		return _value; 
	}

	void	set_type(const ComponentType type)
	{
		_type = type;
	}

	const ComponentType get_type() const
	{
		return _type;
	}

protected:
	virtual void assign(const SCNodeComponent& o)
	{
		this->set_value( o.get_value() );
	}

private:
	SCString		_value;
	ComponentType	_type;
};

#endif	// __SCNODECOMPONENT_H

