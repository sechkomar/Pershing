#pragma once

#include <string>

#include "nlohmann-json\json.hpp"
using json = nlohmann::json;

struct Home {
	uint32_t idx;
	uint32_t post_id;
};

struct Train {
	uint32_t idx;
	uint32_t line_idx;
	std::string player_id;
	uint32_t position;
	uint32_t speed;

	uint32_t capacity;
	uint32_t product;

	void set(uint32_t line_idx_, uint32_t position_, uint32_t speed_, uint32_t product_) {
		line_idx = line_idx_;
		position = position_;
		speed = speed_;
		product = product_;
	}
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
	uint32_t direction;
};

struct Market {		//post.type == 2
	uint32_t idx;	//maybe not necessary (there is in map)
	std::string name; //maybe not necessary

	uint32_t product;
	uint32_t product_capacity;
	uint32_t replenishment;

	uint32_t point_id; //not in json

	void set(uint32_t product_){
		product = product_;
	}
};

struct Town { //post.type == 1
	uint32_t idx;
	std::string name; //maybe not necessary

	uint32_t population;
	uint32_t product;

	void set(uint32_t population_, uint32_t product_) {
		population = population_;
		product = product_;
	}
		
};

void to_json(json& j, const Train& t);
void to_json(json& j, const Line& t);
void to_json(json& j, const Market& t);
void to_json(json& j, const Town& t);

void from_json(const json& j, Train& t);
void from_json(const json& j, Line& t);
void from_json(const json& j, Market& t);
void from_json(const json& j, Town& t);

enum layer : uint32_t {
	STATIC = 0,
	DYNAMIC = 1
};

enum post_type : uint32_t {
	TOWN = 1,
	MARKET = 2
};