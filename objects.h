#pragma once

#include <string>

#include "nlohmann-json\json.hpp"
using json = nlohmann::json;


struct Train
{	
	uint32_t idx;
	uint32_t line_idx;
	std::string player_id;
	uint32_t position;
	uint32_t speed;
};

struct Line
{
	uint32_t idx;
	uint32_t length;
	std::pair<uint32_t, uint32_t> point;
};

struct Endpoint
{
	uint32_t end;
	uint32_t line_idx;
	uint32_t length;
	uint32_t direction;
};

void to_json(json& j, const Train& t);
void to_json(json& j, const Line& t);

void from_json(const json& j, Train& t);
void from_json(const json& j, Line& t);
