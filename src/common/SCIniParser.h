#ifndef __SCINIPARSER_H
#define __SCINIPARSER_H

#include "SCNodeComponent.h"
#include "SCTypes.h"

/// \class		SCIniParser
/// \brief		ini file parse and make root - section - type - value tree
class SCIniParser
{
public:
	/// \brief		creator
	SCIniParser();
	/// \brief		destructor
	~SCIniParser();

	/// \brief		load file and parse data
	/// \param		file			[IN]		ini data file path
	/// \return		return 0 if it success, other is fail
	int			load( const SCChar* file );

	/// \brief		save file and save data
	/// \param		file			[IN]		ini data file path
	/// \return		return 0 if it success, other is fail
	int			save(const SCChar* file);

	/// \brief		print data information in command prompt
	void		print();

	/// \brief		return integer value
	/// \param		section			[IN]		section name
	/// \param		key				[IN]		key name
	///	\param		defaultdata		[IN]		if there is no such value, return this
	/// \return		selected value, data type is integer
	int			getInteger( const SCChar* section, const SCChar* key, int defaultdata );

	/// \brief		return boolean value
	/// \param		section			[IN]		section name
	/// \param		key				[IN]		key name
	///	\param		defaultdata		[IN]		if there is no such value, return this
	/// \return		selected value, data type is boolean
	bool		getBoolean( const SCChar* section, const SCChar* key, bool defaultdata);

	/// \brief		return string value
	/// \param		section			[IN]		section name
	/// \param		key				[IN]		key name
	///	\param		defaultdata		[IN]		if there is no such value, return this
	/// \return		selected value, data type is string
	SCString	getString( const SCChar* section, const SCChar* key, SCString& defaultdata);

	/// \brief		set integer value
	/// \param		section			[IN]		section name
	/// \param		key				[IN]		key name
	///	\param		data			[IN]		if there is no such value, return this
	void		setInteger(const SCChar* section, const SCChar* key, int data);

	/// \brief		set boolean value
	/// \param		section			[IN]		section name
	/// \param		key				[IN]		key name
	///	\param		data			[IN]		if there is no such value, return this
	void		setBoolean(const SCChar* section, const SCChar* key, bool data);

	/// \brief		set string value
	/// \param		section			[IN]		section name
	/// \param		key				[IN]		key name
	///	\param		data			[IN]		if there is no such value, return this
	void		setString(const SCChar* section, const SCChar* key, SCString& data);

protected:
private:
	// member function
	void		save_child(FILE* fp, const SCNodeComponent* node);

	bool		read_line(FILE* fp, SCChar* data, bool& bEnd );

	const SCNodeComponent*	set_session(const SCChar* value);
	const SCNodeComponent*	set_key(const SCNodeComponent* session, const SCChar* value);
	void  set_value(const SCNodeComponent* key, const SCChar* value);

	// member value
	SCNodeComponent*	_root;
};

#endif	// __SCINIPARSER_H

