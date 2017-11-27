#include "objects.h"


void to_json(json& j, const Train& t) {
	j = json{ { "idx", t.idx },{ "line_idx", t.line_idx },{ "player_id", t.player_id },
	{ "position", t.position },{ "speed", t.speed } };
}

void to_json(json & j, const Line & line)
{
	j = json{ { "idx", line.idx },{ "length", line.length },{ "point", line.point } };
}

void from_json(const json& j, Train& t) {
	t.idx = j.at("idx").get<uint32_t>();
	t.line_idx = j.at("line_idx").get<uint32_t>();
	t.player_id = j.at("player_id").get<std::string>();
	t.position = j.at("position").get<uint32_t>();
	t.speed = j.at("speed").get<uint32_t>();
}

void from_json(const json & j, Line & line)
{
	line.idx = j.at("idx").get<uint32_t>();
	line.length = j.at("length").get<uint32_t>();
	line.point = j.at("point").get<std::pair<uint32_t, uint32_t>>();
}
