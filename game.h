#pragma once

#include <map>
#include <string>
#include <vector>
#include "objects.h"
#include "socket.h"


class Game
{
public:
	Home home;
	std::map<uint32_t, Train> trains;
	std::string idx;
	std::map<uint32_t, std::vector<Endpoint>> map;

	std::map<uint32_t, Market> markets;
	std::map<uint32_t, Town> towns;

	std::map<uint32_t, uint32_t> markets_location; //market_id -> post_id

	Socket socket;

	std::map<uint32_t, std::map<uint32_t, std::map<uint32_t, std::vector<uint32_t>>>> min_pathes;

	void init_static_map();
	bool init_dynamic_map();

	void get_layer_response(layer layer_type, ResponseMessage& resp);

	bool init();

	bool login(std::string name);

	int end();

	bool move(uint32_t line_idx, int speed, uint32_t train_idx);

	bool turn();

	bool update();

	void print_trains();

	void print_markets();

	void get_login_response(json jLoginResp);

	void Dijkstra(const size_t &);

	void shopping(const std::vector<uint32_t> &, const uint32_t &);

	std::map<uint32_t, std::map<uint32_t, uint32_t>> get_min_markets_pathes();
	std::map<uint32_t, uint32_t> get_replenishments();
	std::map<uint32_t, uint32_t> get_capacities();
	std::map<uint32_t, uint32_t> get_markets_product();
	std::vector<uint32_t> get_market_point_id();
	std::vector<uint32_t> get_full_path(std::vector<uint32_t>);
};

