#pragma once

#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#include <string>
#include <iostream>

#include "result.h"
#include "action.h"

class Socket 
{
	SOCKET sock;
public:
	Socket() {
		WSADATA wsaData;
    	WSAStartup(MAKEWORD(2, 2), &wsaData);
    	sock = socket(AF_INET, SOCK_STREAM, 0);
	};

	int Connect(const char* host_name, const char* port) const {
		struct addrinfo *dest_addr;
		int get_addr_result = getaddrinfo(host_name, port, NULL, &dest_addr);

		if (get_addr_result) {
			std::cout << "Error: Connection failed with error " << get_addr_result << std::endl;
			return -1;
		}

		return connect(sock, dest_addr->ai_addr, dest_addr->ai_addrlen);
	};

	void Send(const ActionMessage& act) const {
		
		send(sock, act.getStringActionCode(), sizeof(uint32_t), 0);
		if (act.dataLength != NULL) { 
			send(sock, act.getStringDataLength(), sizeof(uint32_t), 0);
			send(sock, act.data, act.dataLength, 0);
		}
	};

	void Receive(ResponseMessage& res) const {
		uint32_t resCode;
		uint32_t datLen;
		
		int received = recv(sock, reinterpret_cast<char*>(&resCode), sizeof(uint32_t), 0);
		if (received < 4) {
			res = ResponseMessage(Result::NO_RESULT, 0, "");
			return;
		}
			
		received = recv(sock, reinterpret_cast<char*>(&datLen), sizeof(uint32_t), 0);
		if (received < 4) {
			res = ResponseMessage(Result::NO_RESULT, 0, "");
			return;
		}
			
		size_t bytesLeft = datLen, size;
		char* datBuf = new char[datLen];
		while (bytesLeft > 0) {
			size = recv(sock, datBuf + (datLen - bytesLeft), bytesLeft, 0);
			bytesLeft -= size;
		}
		res = ResponseMessage(static_cast<Result>(resCode), datLen, datBuf);
	};

	void MakeMove(const ActionMessage& act, ResponseMessage &msg) const {
		Send(act);
		Receive(msg);
	}
	void Disconnect() {
		closesocket(sock);
    	WSACleanup();
	};

	~Socket() {
		Disconnect();
	}
};	