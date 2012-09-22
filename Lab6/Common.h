#ifndef H_COMMON
#define H_COMMON

#include <stdlib.h>

struct ErrorMessages
{
	static const char* MEMORY_ERROR;
	static const char* FILE_OPEN_ERROR;
	static const char* WRONG_INPUT_ERROR;
};

class AppException 
{
public:
	AppException(const char* message)
	{
		_message = message;
	}

	const char* GetMessage() 
	{ 
		return _message;
	};
private:
	const char* _message;
};

#endif


