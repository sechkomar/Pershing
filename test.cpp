
#include "game.h"
#pragma execution_character_set("utf-8")

int main(int argc, char* argv[]) {
	Game game;

	if (!game.init("persing1", 1, "TEST_GAME")) {
		return EXIT_FAILURE;
	}


	std::list<uint32_t> trains_to_upgrade;
	std::list<uint32_t> towns_to_upgrade;


	for (int i = 0;; i++) {

		if (game.towns.at(game.home.post_id).armor * 1.5 >= game.towns.at(game.home.post_id).armor_capacity &&
			game.towns.at(game.home.post_id).product * 1.5 >= game.towns.at(game.home.post_id).product_capacity) {

			towns_to_upgrade.push_back(game.home.post_id);
			game.upgrade(towns_to_upgrade, trains_to_upgrade);
			towns_to_upgrade.clear();
		}

		for (auto train : game.trains) {

			if (train.second.player_id == game.idx) {

				if (train.second.last_point_id == game.towns.at(game.home.post_id).point_id &&
					train.second.next_level_price * 2 <= game.towns.at(game.home.post_id).armor) {

					trains_to_upgrade.push_back(train.second.idx);
					game.upgrade(towns_to_upgrade, trains_to_upgrade);
					trains_to_upgrade.clear();
				}

				if (train.first <= 8) {
					if (train.first <= 5) game.go(game.trains.at(train.second.idx), post_type::MARKET);
					else game.go(game.trains.at(train.second.idx), post_type::STORAGE);
					if (game.trains.at(train.second.idx).current_path.size() != 0) game.move(game.trains.at(train.second.idx).current_path.front(), train.second.idx);
				}

			}
		}

		game.turn();
		if (i % 20 == 0) {
			game.print_info();
		}
	}

	game.end();

	return 0;
}
