#include "SCNode.h"

SCNode::SCNode()
{
	_child.reserve(0);
}

SCNode::~SCNode()
{
	clear();
}

int 
SCNode::add(const SCNodeComponent* component)
{
	_child.push_back(const_cast<SCNodeComponent*>(component));
	return (int)_child.size();
}

int 
SCNode::remove(const SCNodeComponent* component)
{
	std::vector<SCNodeComponent*>::iterator iter_s = _child.begin();
	std::vector<SCNodeComponent*>::iterator iter_e = _child.end();

	while(iter_s != iter_e)
	{
		SCNodeComponent* temp = *iter_s;
		if(temp == component)
		{
			iter_s = _child.erase(iter_s);
			delete temp;
			temp = NULL;
		}
		else 
		{
			++iter_s;
		}
	}

	return (int)_child.size();
}

const SCNodeComponent*
SCNode::getChild( int nIdex ) const
{
	return _child.at( nIdex );
}

void
SCNode::clear()
{
	std::vector<SCNodeComponent*>::iterator iter_s = _child.begin();
	std::vector<SCNodeComponent*>::iterator iter_e = _child.end();
	for( ; iter_s != iter_e; ++iter_s)
	{
		SCNodeComponent* temp = *iter_s;
		if (temp != NULL)
		{
			delete temp;
		}	
		temp = NULL;
	}
	_child.clear();
	std::vector<SCNodeComponent*>().swap(_child);
}
