#include "common.h"

void copy_string(char* &dest, size_t len, const char * source) {
	if (dest != nullptr) {
		delete[] dest;
		dest = nullptr;
	}

	if (len != 0) {
		dest = new char[len + 1];
		memcpy_s(dest, len, source, len);
		dest[len] = '\0';
	}
}
