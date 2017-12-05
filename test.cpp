#include "game.h"

#include <string>
#include <iostream>
#include <fstream>
#include "path.h"


#pragma execution_character_set("utf-8")

int main(int argc, char* argv[]) {
	
	std::ofstream log("log.txt");
	Game game;
	if (!game.init()) {
		return EXIT_FAILURE;
	}

	game.Dijkstra(game.home.idx);
	for (auto market : game.markets) { 
		game.Dijkstra(market.second.point_id);
	}

	auto repls = game.get_replenishments();
	auto capas = game.get_capacities();
	auto markets_point_id = game.get_market_point_id();

	auto min_markets_pathes = game.get_min_markets_pathes();

	CalculatePath path(min_markets_pathes, game.trains[0].capacity, repls, capas, 
		game.towns[1].population, game.home.idx, game.get_market_point_id());

	while (true) {

		path.set_init_products(game.get_markets_product());
		path.set_product_in_town(game.towns[1].product);

		auto best_path = path.find_pathways();								   
		auto next_points = game.get_full_path(best_path);

		game.shopping(next_points, game.trains[0].idx);
		game.update();
	}

	int result = game.end();

	system("pause");
	
	return 0;
}
