#pragma once
#include <inttypes.h>

#include "common.h"


enum class Response : uint32_t {
	OKEY = 0,
	BAD_COMMAND = 1,
	RESOURCE_NOT_FOUND = 2,
	PATH_NOT_FOUND = 3,
	ACCESS_DENIED = 5,
	NO_RESULT
};

struct ResponseMessage {
	Response resp_code;
	size_t data_length;
	char* data;

	ResponseMessage() : data(nullptr) {};

	ResponseMessage(const Response &res, const size_t &len, const char* const msg) : 
									resp_code(res), data_length(len) {

		data = new char[1];		//for initialization	
		copy_string(this->data, len, msg);
	}

	ResponseMessage(const ResponseMessage &msg) {
		data = new char[1];		//for initialization
		set(msg.resp_code, msg.data_length, msg.data);
	}

	ResponseMessage & operator=(const ResponseMessage &msg) {
		set(msg.resp_code, msg.data_length, msg.data);
		return *this;
	}

	void set(Response new_result, size_t new_data_len, const char* new_data) {
		this->resp_code = new_result;
		this->data_length = new_data_len;

		copy_string(this->data, new_data_len, new_data);
	}

	~ResponseMessage() {
		if (data != nullptr) {
			delete[] data;
			data = nullptr;
		}
	}
};