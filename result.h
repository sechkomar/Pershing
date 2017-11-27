#pragma once;
#include <inttypes.h>


enum class Result : uint32_t
{
	OKEY = 0,
	BAD_COMMAND = 1,
	RESOURCE_NOT_FOUND = 2,
	PATH_NOT_FOUND = 3,
	ACCESS_DENIED = 5,
	NO_RESULT
};

struct ResponseMessage
{
	Result result;
	size_t dataLength;
	char* data;

	ResponseMessage() : data(nullptr) {};
	ResponseMessage(const Result &res, const size_t &len, const char* const msg) :
		result(res), dataLength(len)
	{
		if (dataLength)
		{
			data = new char[dataLength];
			memcpy_s(data, dataLength, msg, len);
		}
		else
			data = nullptr;
			
	}

	ResponseMessage(const ResponseMessage &msg)
	{
		result = msg.result;
		dataLength = msg.dataLength;
		if (dataLength)
		{
			data = new char[dataLength];
			memcpy_s(data, dataLength, msg.data, msg.dataLength);
		}
		else
			data = nullptr;
	}

	ResponseMessage & operator=(const ResponseMessage &msg)
	{
		result = msg.result;
		dataLength = msg.dataLength;
		if (dataLength)
		{
			if (data)
				delete[] data;
			data = new char[dataLength];
			memcpy_s(data, dataLength, msg.data, msg.dataLength);
		}
		else
			data = nullptr;
		return *this;
	}

	~ResponseMessage()
	{
		if (data)
		{
			delete[] data;
			data = nullptr;
		}
		
	}
};