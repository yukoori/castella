#ifndef __SCNODE_H
#define __SCNODE_H

#include "SCNodeComponent.h"

#include <vector>

/// \class		SCNode
/// \brief		component of containing child object
class	SCNode : public SCNodeComponent
{
public:
	SCNode();
	virtual	~SCNode();
	SCNode(const SCNode& o)
	{ 
		assign(o);
	}

	SCNode& operator=(const SCNode& o)
	{
		assign(o);
		return *this;
	}

	// virtual function
	virtual	int add(const SCNodeComponent*);	// must allocated outside!!
	virtual int remove(const SCNodeComponent*);
	virtual const SCNodeComponent* getChild(int) const;
	virtual	int size() const 
	{ 
		return (int)_child.size(); 
	}

protected:
	virtual void assign(const SCNode& o)
	{
		for( int i=0; i < o.size(); ++i )
		{
			this->add( o.getChild(i) );
		}
	}

private:
	void	clear();

	std::vector<SCNodeComponent*>	_child;
};

#endif	// __SCNODE_H

