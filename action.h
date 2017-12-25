#pragma once
 
#include <inttypes.h>

enum class Action : uint32_t {
	LOGIN = 1,
	LOGOUT = 2,
	MOVE = 3,
	UPGRADE = 4,
	TURN = 5,
	MAP = 10
};

struct ActionMessage {
	Action action_code;
	size_t data_length;
	char* data;

	ActionMessage(const Action &code, const std::string &msg) : action_code(code) {
		data_length = msg.length();
		data = new char[data_length + 1];
		memcpy(data, msg.c_str(), data_length + 1);
	}

	const char* get_string_action_code() const {
		return reinterpret_cast<const char*>(&action_code);
	}

	const char* get_string_data_length() const {
		return reinterpret_cast<const char*>(&data_length);
	}

	~ActionMessage() {
		delete[] data;
		data = nullptr;
	}
};
