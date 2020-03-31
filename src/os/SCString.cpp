#include "SCTypes.h"

#include <windows.h>

const SCChar* TOSCChar(const char* data)
{
	if (sizeof(SCChar) == sizeof(char))
	{
		return (SCChar*)data;
	}

	SCString returnString;
#if defined(_WIN32) || defined(_WIN64)
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
#else
	int nLen = 0;
	int error = mbstowcs_s(&nLen, NULL, 0, data, strlen(data));
	if (error != 0)
	{
		return returnString.c_str();
	}

	SCChar* toData = (SCChar*)calloc(nLen + sizeof(SCChar), sizeof(SCChar));
	if (toData == NULL)
	{
		return returnString.c_str();
	}

	mbstowcs_s(NULL, toData, nLen, data, strlen(data));
	if (STRLEN(toData) <= 0)
	{
		return returnString.c_str();
	}

	returnString = toData;

	free(toData);
#endif	// defined(_WIN32) || defined(_WIN64)
	return returnString.c_str();
}

const char* TOChar(const SCChar* data)
{
	if (sizeof(SCChar) == sizeof(char))
	{
		return (char*)data;
	}

	std::string returnString;
#if defined(_WIN32) || defined(_WIN64)
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
#else
	int nLen = 0;
	int error = wcstombs_s(&nLen, NULL, 0, data, STRLEN(data));
	if (nLen <= 0)
	{
		return returnString.c_str();
	}

	char* toData = (char*)calloc(nLen + sizeof(char), sizeof(char));
	if (toData == NULL)
	{
		return returnString.c_str();
	}

	wcstombs_s(NULL, toData, nLen, data, STRLEN(data));
	if (strlen(toData) <= 0)
	{
		return returnString.c_str();
	}

	returnString = toData;

	free(toData);
#endif	// defined(_WIN32) || defined(_WIN64)
	return returnString.c_str();
}