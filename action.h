#pragma once
#include <inttypes.h>

enum class Action: uint32_t
{
    LOGIN = 1,
    LOGOUT = 2,
    MOVE = 3,
    TURN = 5,
    MAP = 10
};

struct ActionMessage	
{
	ActionMessage(const Action &code, std::string &msg) : actionCode(code)
	{
		dataLength = msg.length();
		if (dataLength != 0)
		{
			data = new char[dataLength];
			memcpy_s(data, dataLength, msg.c_str(), msg.length());
		}
		else
			data = nullptr;
	}

	const char* getStringActionCode() const
	{
		return reinterpret_cast<const char*>(&actionCode);
	}
	const char* getStringDataLength() const
	{
		return reinterpret_cast<const char*>(&dataLength);
	}
    Action actionCode;
    size_t dataLength;
    char* data;
	~ActionMessage()
	{
		delete[] data;
		data = nullptr;
	}
};