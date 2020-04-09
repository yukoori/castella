#ifndef __SCNODEITEM_H
#define __SCNODEITEM_H

#include "SCNodeComponent.h"

/// \class		SCNodeItem
/// \brief		leaf class of tree
class	SCNodeItem : public SCNodeComponent
{
public:
	SCNodeItem()
	{

	};

	virtual	~SCNodeItem()
	{

	};

	SCNodeItem(const SCNodeItem& o)
	{ 
		assign(o); 
	}

	SCNodeItem& operator=(const SCNodeItem& o)
	{
		assign(o);
		return *this;
	}

	virtual	int add(const SCNodeComponent*)
	{
		// do nothing
		return 0;
	};
	
	virtual int remove(const SCNodeComponent*)
	{ 
		// do nothing
		return 0;
	};
	
	virtual const SCNodeComponent* getChild(int) const
	{ 
		// do nothing 
		return NULL;
	};

	virtual	int size() const
	{
		return 0;
	}
};

#endif	// __SCNODEITEM_H

