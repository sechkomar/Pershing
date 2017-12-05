#include "objects.h"


void to_json(json& j, const Train& t) {
	j = json{ 
		{ "idx", t.idx },
		{ "line_idx", t.line_idx },
	//	{ "player_id", t.player_id },
		{ "position", t.position },
		{ "speed", t.speed },
		{"capacity", t.capacity}, 
		{"product", t.product} 
	};
}

void to_json(json & j, const Line & line) {
	j = json{ 
		{ "idx", line.idx },
		{ "length", line.length },
		{ "point", line.points } 
	};
}


void to_json(json & j, const Market& post) {
	j = json{
		{ "idx", post.idx },
		{ "name", post.name },
		{ "product", post.product },
		{ "product_capacity", post.product_capacity },
		{ "replenishment", post.replenishment }, 
		{"point_id", post.point_id}  //not in original json
	};
}

void to_json(json & j, const Town& town) {
	j = json{
		{ "idx", town.idx },
		{ "name", town.name },
		{ "population", town.population },
		{ "product", town.product } 
	};
}

void from_json(const json& j, Train& t) {
	t.idx = j.at("idx").get<uint32_t>();
	t.line_idx = j.at("line_idx").get<uint32_t>();
	t.player_id = j.at("player_id").get<std::string>();
	t.position = j.at("position").get<uint32_t>();
	t.speed = j.at("speed").get<uint32_t>();
	t.capacity = j.at("capacity").get<uint32_t>();
	t.product = j.at("product").get<uint32_t>();
}

void from_json(const json & j, Line & line) {
	line.idx = j.at("idx").get<uint32_t>();
	line.length = j.at("length").get<uint32_t>();
	line.points = j.at("point").get<std::pair<uint32_t, uint32_t>>();
}

void from_json(const json & j, Market & post) {
	post.idx = j.at("idx").get<uint32_t>();
	post.name = j.at("name").get<std::string>();
	post.product = j.at("product").get<uint32_t>();
	post.product_capacity = j.at("product_capacity").get<uint32_t>();
	post.replenishment = j.at("replenishment").get<uint32_t>();
}

void from_json(const json & j, Town & town) {
	// town.armor = j.at("armor").get<uint32_t>();
	town.idx = j.at("idx").get<uint32_t>();
	town.name = j.at("name").get<std::string>();
	town.product = j.at("product").get<uint32_t>();
	town.population = j.at("population").get<uint32_t>();
}
