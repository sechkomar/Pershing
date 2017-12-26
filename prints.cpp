 
#include "game.h"

std::string Game::print_trains() {
	std::ostringstream string_trains;

	string_trains << "Trains:" << std::endl;
	for (auto train : trains) {
		string_trains << "    idx: " << train.first << 
			", line_idx: " << train.second.line_idx <<
			", point_idx: " << train.second.last_point_id << 
			", level(nl_price): " << train.second.level <<
			"(" << train.second.next_level_price << 
			"), goods: " << train.second.goods << "/" << train.second.goods_capacity << 
			" type: " << train.second.post_type;

		if (train.second.current_path.size() > 0) 
			string_trains << ", heading_to: " << train.second.current_path.front() << 
			"(" << train.second.current_path.back() << ")";
		string_trains << std::endl;
	}
	return string_trains.str();
}

std::string Game::print_marketplaces() {
	std::ostringstream string_marketplaces;

	string_marketplaces << "Marketplaces:" << std::endl;
	for (auto market : markets) {
		string_marketplaces << "    idx: " << market.first << 
			", point_id: " << market.second.point_id << 
			", name: " << market.second.name <<
			", product: " << market.second.product << "/" << market.second.product_capacity << 
			", repl: " << market.second.replenishment << std::endl;
	}

	for (auto storage : storages) {
		string_marketplaces << "    idx: " << storage.first << 
			", point_id: " << storage.second.point_id << 
			", name: " << storage.second.name <<
			", armor: " << storage.second.armor << "/" << storage.second.armor_capacity << 
			", repl: " << storage.second.replenishment << std::endl;
	}
	return string_marketplaces.str();
}

std::string Game::print_towns() {
	std::ostringstream string_towns;
	string_towns << "My towns:" << std::endl;
	for (auto town : towns) {
		if (town.second.player_id == idx) {
			string_towns << "    idx: " << town.first << 
				", point_id: " << town.second.point_id << 
				", level(nl_price): " << town.second.level << "(" << town.second.next_level_price << 
				"), armor: " << town.second.armor << "/" << town.second.armor_capacity << 
				", product: " << town.second.product << "/" << town.second.product_capacity <<
				", population: " << town.second.population << std::endl;
		}
	}
	return string_towns.str();
}

void Game::print_info() {
	std::ostringstream string_info;
	string_info << "Rating: " << rating << " Turn: " << turn_number << std::endl <<
		print_trains() << std::endl <<
		print_towns() << std::endl <<
		print_marketplaces() << std::endl;

	print_log(string_info.str());

}

void Game::print_log(std::string some_info) {
	std::cout << some_info << std::endl;
	log << some_info << std::endl;
}

void Game::print_lines() {
	std::cout << "lines:" << std::endl;
	for (auto point : map) {
		std::cout << point.first << " - ";
		for (auto line : point.second) {
			if (line.direction == -1) std::cout << "-";
			std::cout << line.end << "(" << line.line_idx << ") ";
		}
		std::cout << std::endl;
	}
}