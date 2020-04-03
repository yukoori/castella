#include "SCTypes.h"

#if defined(_WIN32) || defined(_WIN64)
#	include <windows.h>
#else
#	include <stdlib.h>
#endif	// defined(_WIN32) || defined(_WIN64)

const SCChar* TOSCChar(const char* data)
{
#ifdef UNICODE
	SCString returnString;
#	if defined(_WIN32) || defined(_WIN64)
	int nLen = MultiByteToWideChar(CP_ACP, 0, data, strlen(data), NULL, NULL);
	if (nLen <= 0)
	{
		return returnString.c_str();
	}

	SCChar* toData = (SCChar*)calloc(nLen + sizeof(SCChar), sizeof(SCChar));
	if (toData == NULL)
	{
		return returnString.c_str();
	}

	MultiByteToWideChar(CP_ACP, 0, data, strlen(data), toData, nLen);
	if (STRLEN(toData) <= 0)
	{
		return returnString.c_str();
	}

	returnString = toData;

	free(toData);
#	else	// defined(_WIN32) || defined(_WIN64)
	int nLen = mbstowcs(NULL, data, strlen(data));
	if (nLen == 0)
	{
		return returnString.c_str();
	}

	SCChar* toData = (SCChar*)calloc(nLen + sizeof(SCChar), sizeof(SCChar));
	if (toData == NULL)
	{
		return returnString.c_str();
	}

	mbstowcs(toData, data, strlen(data));
	if (STRLEN(toData) <= 0)
	{
		return returnString.c_str();
	}

	returnString = toData;

	free(toData);
#	endif	// defined(_WIN32) || defined(_WIN64)
	return returnString.c_str();
#else	// UNICODE
	return (SCChar*)data;
#endif	// UNICODE
}

const char* TOChar(const SCChar* data)
{
#ifdef UNICODE
	std::string returnString;
#	if defined(_WIN32) || defined(_WIN64)
	int nLen = WideCharToMultiByte(CP_ACP, 0, data, -1, NULL, 0, NULL, NULL);
	if (nLen <= 0)
	{
		return returnString.c_str();
	}

	char* toData = (char*)calloc(nLen + sizeof(char), sizeof(char));
	if (toData == NULL)
	{
		return returnString.c_str();
	}

	WideCharToMultiByte(CP_ACP, 0, data, -1, toData, nLen, NULL, NULL);
	if (strlen(toData) <= 0)
	{
		return returnString.c_str();
	}

	returnString = toData;

	free(toData);
#	else	// defined(_WIN32) || defined(_WIN64)
	int nLen = wcstombs(NULL, data, STRLEN(data));
	if (nLen <= 0)
	{
		return returnString.c_str();
	}

	char* toData = (char*)calloc(nLen + sizeof(char), sizeof(char));
	if (toData == NULL)
	{
		return returnString.c_str();
	}

	wcstombs(toData, data, STRLEN(data));
	if (strlen(toData) <= 0)
	{
		return returnString.c_str();
	}

	returnString = toData;

	free(toData);
#	endif	// defined(_WIN32) || defined(_WIN64)
	return returnString.c_str();
#else	// UNICODE
	return (char*)data;
#endif	// UNICODE
}