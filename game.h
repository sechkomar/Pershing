#pragma once

#include <map>
#include <string>
#include <vector>
#include "objects.h"
#include "socket.h"

struct Home
{
	uint32_t idx;
	uint32_t post_id;
};

namespace game
{
	static Home home;
	static std::map<uint32_t, Train> trains;
	static std::string idx;
	static std::map<uint32_t, std::vector<Endpoint>> map;

	static Socket socket;


	void getMap();
	bool init();
	int end();

	void move(uint32_t line_idx, int speed, uint32_t train_idx);

	void turn();
};

