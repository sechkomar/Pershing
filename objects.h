#pragma once
 
#include <string>
#include <list>
#include "nlohmann-json\json.hpp"
using json = nlohmann::json;

struct Home {
	uint32_t idx;
	uint32_t post_id;
	uint32_t point_id;
};

struct Event {
	uint32_t type;
	uint32_t tick;
	uint32_t event_power;
	std::string event_power_name;
};

struct Train {
	uint32_t cooldown;
	std::list<Event> events;
	uint32_t goods;
	uint32_t goods_capacity;
	uint32_t last_point_id; //not in json
	uint32_t idx;
	uint32_t level;
	uint32_t line_idx;
	uint32_t next_level_price;
	std::string player_id;
	uint32_t position;
	uint32_t post_type;
	uint32_t speed;
	std::vector<uint32_t> current_path;
};

struct Line {
	uint32_t idx;
	uint32_t length;
	std::pair<uint32_t, uint32_t> points;
};

struct Endpoint {
	uint32_t end;
	uint32_t line_idx;
	uint32_t length;
	int direction;
	Endpoint(uint32_t _end, uint32_t _line_idx, uint32_t _length, int _direction) :
		end(_end), line_idx(_line_idx), length(_length), direction(_direction) {};
};

struct Market {		//post_type == 2
	std::list<Event> events;
	uint32_t idx;
	std::string name;
	uint32_t point_id;
	uint32_t product;
	uint32_t product_capacity;
	uint32_t replenishment;
};

struct Storage {		//post.type == 3
	std::list<Event> events;
	uint32_t idx;
	std::string name;
	uint32_t point_id;
	uint32_t armor;
	uint32_t armor_capacity;
	uint32_t replenishment;
};

struct Town {		//post.type == 1
	uint32_t armor;
	uint32_t armor_capacity;
	std::list<std::string> events;
	uint32_t idx;
	uint32_t level;
	std::string name; 
	uint32_t next_level_price;
	std::string player_id;
	uint32_t point_id;
	uint32_t population;
	uint32_t population_capacity;
	uint32_t product;
	uint32_t product_capacity;
	uint32_t train_cooldown_on_collision;
};

void to_json(json& j, const Train& t);
void to_json(json& j, const Line& t);
void to_json(json& j, const Market& t);
void to_json(json& j, const Storage& t);
void to_json(json& j, const Town& t);

void from_json(const json& j, Train& t);
void from_json(const json& j, Line& t);
void from_json(const json& j, Market& t);
void from_json(const json& j, Storage& t);
void from_json(const json& j, Town& t);

enum layer : uint32_t {
	STATIC = 0,
	DYNAMIC = 1
};

enum post_type : uint32_t {
	TOWN = 1,
	MARKET = 2,
	STORAGE = 3
};

enum event_type : uint32_t {
	TRAIN_COLLISION = 1,
	HIJACKERS_ASSAULT = 2,
	PARASITES_ASSAULT = 3,
	REFUGEES_ARRIVAL = 4,
	RESOURCE_OVERFLOW = 5,
	RESOURCE_LACK = 6,
	GAME_OVER = 100
};