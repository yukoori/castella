#include "SCIniParser.h"

#include "SCNode.h"
#include "SCNodeItem.h"

#include <memory.h>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>

#define	MAX_BUFFER	2048

// include comment
#define CHECK_BLANK_LINE(x) ((*x == '\n') || (*x == '\r') || (*x == '#')) ? true : false
#define CHECK_BLANK(x) ((*x == ' ') || (*x == '\t')) ? true : false

bool	bEnd = false;

SCIniParser::SCIniParser()
	: _root(NULL)
{

}

SCIniParser::~SCIniParser()
{
	if (_root != NULL)
	{
		delete _root;
	}	
	_root = NULL;
}

int
SCIniParser::load(const SCChar* file)
{
	FILE* fp = NULL;
#if defined(_WIN32) || defined(_WIN64)
	int error = fopen_s(&fp, TOChar(file).c_str(), "r+b");
	if (!fp)
	{
		return -1;
	}
#else
	fp = fopen(TOChar(file).c_str(), "r+b");
	if (!fp)
	{
		return -1;
	}
#endif // defined(_WIN32) || defined(_WIN64)
		
	bEnd = false;

	SCNodeComponent* session_component = NULL;
	SCNodeComponent* key_component	   = NULL;

	SCChar	buffer[MAX_BUFFER] = {'\0',};
	while( read_line(fp, buffer) )
	{
		if (STRLEN(buffer) == 0)		// no more data
		{
			break;
		}

		SCChar* current = buffer;
		if (CHECK_BLANK_LINE(current))	// skip blank line
		{
			continue;
		}	
		else if( *current == '[' )		// set session info
		{
			++current;

			SCChar	session[MAX_BUFFER] = {'\0',};
			SCChar* session_current = session;
			while( *current != ']' )
			{
				*session_current = *current;
				++session_current; ++current;
			}
			++current;

			session_component = const_cast<SCNodeComponent*>(set_session(session));
			continue;
		}
		else
		{						
			// set key and value
			SCChar	key[MAX_BUFFER] = {'\0',};
			SCChar* key_current = key;
			while( *current != '=' )
			{
				if( !CHECK_BLANK(current) )
				{
					*key_current = *current;
					++key_current;
				}
				++current;
			}
			++current;

			key_component = const_cast<SCNodeComponent*>(set_key(session_component, key));

			SCChar	value[MAX_BUFFER] = { '\0', };
			SCChar* value_current = value;
			while( !CHECK_BLANK_LINE(current) )
			{
// 				if( *pBuf == ',' )
//				{
// 					set_value( pKey, szTemp );
// 					memset( szTemp, 0x00, MAX_BUFFER );
// 					pTemp = szTemp;
// 					++pBuf;
// 				}

				if( !CHECK_BLANK(current) )
				{
					*value_current = *current;
					++value_current;
				}
				++current;
			}

			set_value(key_component, value);
			continue;
		}
	}

	if (fp)
	{
		fclose(fp);
	}
	fp = NULL;

	return 0;
}

int	
SCIniParser::save(const SCChar* file)
{
	FILE* fp = NULL;
#if defined(_WIN32) || defined(_WIN64)
	int error = fopen_s(&fp, TOChar(file).c_str(), "w+b");
	if (!fp)
	{
		return -1;
	}
#else
	fp = fopen(TOChar(file).c_str(), "w+b");
	if (!fp)
	{
		return -1;
	}
#endif // defined(_WIN32) || defined(_WIN64)

	save_child(fp, _root);

	if (fp)
	{
		fclose(fp);
	}
	fp = NULL;

	return 0;
}

const SCNodeComponent*
SCIniParser::set_session( const SCChar* value )
{
	SCString string_value = value;

	SCNode* node = new SCNode;
	node->set_value(string_value);
	node->set_type(SCNodeComponent::T_SESSION);

	if( !_root ) 
	{
		_root = new SCNode;

		SCString	strRoot = SCTEXT("root");
		_root->set_value( strRoot );
	}

	int idx = _root->add( node );

	return _root->getChild( idx-1 );
}

const SCNodeComponent*
SCIniParser::set_key(const SCNodeComponent* session, const SCChar* value)
{
	SCString string_value = value;

	SCNode*	node = new SCNode;
	node->set_value(string_value);
	node->set_type(SCNodeComponent::T_KEY);

	int idx = const_cast<SCNodeComponent*>(session)->add(node);

	return session->getChild( idx-1 );
}

void
SCIniParser::set_value(const SCNodeComponent* key, const SCChar* value)
{
	SCString string_value = value;

	SCNodeItem*	item = new SCNodeItem;
	item->set_value(string_value);

	const_cast<SCNodeComponent*>(key)->add(item);
}

void
SCIniParser::print()
{
	print_child( _root );
}

void
SCIniParser::print_child(const SCNodeComponent* pNode)
{
	if (pNode->get_type() == SCNodeComponent::T_SESSION)
	{
		SCPRINTF(SCTEXT("\n[%s]\n"), pNode->get_value().c_str());
	}
	else if (pNode->get_type() == SCNodeComponent::T_KEY)
	{
		SCPRINTF(SCTEXT("%s = "), pNode->get_value().c_str());
	}
	
	for( int i=0; i<pNode->size(); ++i ) 
	{
		const SCNodeComponent* const pChild = pNode->getChild(i);
		if (pChild->size() != 0)
		{
			print_child(pChild);
		}	
		else
		{
			SCPRINTF(SCTEXT("%s\n"), pChild->get_value().c_str());
		}	
	}
}

void
SCIniParser::save_child(FILE* fp, const SCNodeComponent* pNode)
{
	if (pNode->get_type() == SCNodeComponent::T_SESSION)
	{
		SCFPRINTF(fp, SCTEXT("\n[%s]\n"), pNode->get_value().c_str());
	}
	else if (pNode->get_type() == SCNodeComponent::T_KEY)
	{
		SCFPRINTF(fp, SCTEXT("%s = "), pNode->get_value().c_str());
	}

	for (int i = 0; i < pNode->size(); ++i)
	{
		const SCNodeComponent* const pChild = pNode->getChild(i);
		if (pChild->size() != 0)
		{
			save_child(fp, pChild);
		}
		else
		{
			SCFPRINTF(fp, SCTEXT("%s\n"), pChild->get_value().c_str());
		}
	}
}

bool
SCIniParser::read_line(FILE* fp, SCChar* data)
{
	if (bEnd == true)
	{
		return false;
	}	

	while(true) 
	{
		char c = '\0';
		if (!feof(fp))
		{
			c = fgetc(fp);
		}	
		else
		{
			*data = c;
			bEnd = true;
			break;
		}
		
		if (c == '\n')
		{
			*data = c;
			++data;
			*data = '\0';
			break;
		}
		else if (c == EOF) 
		{
			continue;
		}
		else 
		{
			*data = c;
			++data;
		}
	}

	return true;
}

int	
SCIniParser::getInteger(const SCChar* section, const SCChar* key, int defaultdata)
{
	SCString string_data = SCTEXT("");
	string_data = getString( section, key, string_data);

	if (string_data == SCTEXT(""))
	{
		return defaultdata;
	}	
	else
	{
		return atoi(TOChar(string_data.c_str()).c_str());
	}	
}

bool
SCIniParser::getBoolean(const SCChar* section, const SCChar* key, bool defaultdata)
{
	SCString string_data = SCTEXT("");
	string_data = getString( section, key, string_data);

	if (string_data.compare(SCTEXT("true")) == 0 || string_data.compare(SCTEXT("TRUE")) == 0 || string_data.compare(SCTEXT("1")) == 0)
	{
		return true;
	}	
	else if (string_data.compare(SCTEXT("false")) == 0 || string_data.compare(SCTEXT("FALSE")) == 0 || string_data.compare(SCTEXT("0")) == 0)
	{
		return false;
	}	

	return defaultdata;
}

SCString
SCIniParser::getString(const SCChar* section, const SCChar* key, SCString& defaultdata)
{
	for( int i=0; i<_root->size(); ++i ) 
	{
		const SCNodeComponent* const session_component = _root->getChild(i);
		if (session_component->get_value().compare(section) != 0)
		{
			continue;
		}	

		for( int j=0; j< session_component->size(); ++j )
		{
			const SCNodeComponent* const key_component = session_component->getChild(j);
			if (key_component->get_value().compare(key) != 0)
			{
				continue;
			}	

			if (key_component->size() == 1)
			{
				return key_component->getChild(0)->get_value();
			}	
			else 
			{
				// do not support yet!!
				return defaultdata;
			}
		}
	}

	return defaultdata;
}

void
SCIniParser::setInteger(const SCChar* section, const SCChar* key, int data)
{
	SCChar buffer[32] = { '\0', };
	SCSPRINTF(buffer, sizeof(buffer), SCTEXT("%d"), data);

	SCString string_data = buffer;
	setString(section, key, string_data);
}

void
SCIniParser::setBoolean(const SCChar* section, const SCChar* key, bool data)
{
	SCChar buffer[32] = { '\0', };
	SCSPRINTF(buffer, sizeof(buffer), SCTEXT("%s"), data ? SCTEXT("TRUE") : SCTEXT("FALSE"));
	
	SCString string_data = buffer;
	setString(section, key, string_data);
}

void
SCIniParser::setString(const SCChar* section, const SCChar* key, SCString& data)
{
	SCNodeComponent* session_component = NULL;
	for (int i = 0; i < _root->size(); ++i)
	{
		const SCNodeComponent* const node = _root->getChild(i);
		if (node->get_value().compare(section) == 0)
		{
			session_component = const_cast<SCNodeComponent*>(node);
		}
	}

	if (session_component == NULL)
	{
		session_component = const_cast<SCNodeComponent*>(set_session(section));
	}

	SCNodeComponent* key_component = NULL;
	for (int i = 0; i < session_component->size(); ++i)
	{
		const SCNodeComponent* const node = const_cast<SCNodeComponent*>(session_component->getChild(i));
		if (node->get_value().compare(key) == 0)
		{
			key_component = const_cast<SCNodeComponent*>(node);
		}
	}

	if (key_component == NULL)
	{
		key_component = const_cast<SCNodeComponent*>(set_key(session_component, key));
	}

	set_value(key_component, data.c_str());
}