#pragma once
 
#include "objects.h"
#include "socket.h"
#include <map>
#include <fstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>


struct Game
{
	//--	SYSTEM OBJECTS
	Socket socket;
	std::ofstream log;

	//--	GAME DATA
	std::string idx;
	uint32_t turn_number = 1;
	uint32_t rating;
	std::string username;

	//--	GAME OBJECTS
	Town home;
	std::map<uint32_t, std::vector<Endpoint>> map;
	std::map<uint32_t, std::map<uint32_t, uint32_t>> edges_lens;
	std::map<uint32_t, Train> trains;
	std::map<uint32_t, Town> towns;
	std::map<uint32_t, Market> markets;
	std::map<uint32_t, Storage> storages;

	//--	MAP.CPP
	void get_layer_response(layer layer_type, ResponseMessage& resp);
	bool load_static_map();
	bool load_dynamic_map();

	//--	CONNECTIONS.CPP
	bool init(std::string username, uint32_t num_players, std::string game_name, std::string security_key = "");
	bool login(json jLogin);
	int end();

	//--	MOVING.CPP
	bool move(uint32_t line_idx, int speed, uint32_t train_idx);
	bool move(uint32_t point_idx, uint32_t train_idx);
	bool turn();
	bool turn(uint32_t num_of_turns_to_pass);	

	//--	GAME.CPP
	bool upgrade(std::list<uint32_t> posts_, std::list<uint32_t> trains_);
	void set_train_point(Train & train);
	void update_train_point(Train & train);
	void go(Train &tr, post_type market_type);
	void upgrade_all();
	void game_step();

	std::function<float(uint32_t train_cap, uint32_t idx, uint32_t len)> get_profit;

	//--	PRINTS.CPP
	std::string print_trains();
	std::string print_marketplaces();
	std::string print_towns();
	void print_lines();
	void print_info();
	void print_log(std::string);

	~Game() {
		log.close();
	}
};

