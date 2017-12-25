#pragma once
 
#include <inttypes.h>

enum class Response : uint32_t {
	OKEY = 0,
	BAD_COMMAND = 1,
	RESOURCE_NOT_FOUND = 2,
	PATH_NOT_FOUND = 3,
	ACCESS_DENIED = 5,
	NO_RESULT = 6
};

struct ResponseMessage {
	Response resp_code;
	size_t data_length;
	char* data;

	ResponseMessage() : data(nullptr) {};

	ResponseMessage(const Response &res, const size_t &len, const char* const msg) :
		resp_code(res), data_length(len) {
		data = new char[len + 1];
		memcpy(data, msg, len + 1);
	}

	ResponseMessage & operator=(const ResponseMessage &msg) {
		resp_code = msg.resp_code;
		data_length = msg.data_length;
		delete data;
		data = new char[msg.data_length + 1];
		memcpy(data, msg.data, msg.data_length + 1);
		return *this;
	}

	~ResponseMessage() {
		if (data != nullptr) {
			delete[] data;
			data = nullptr;
		}
	}
};