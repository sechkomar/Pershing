
#include "game.h"
#pragma execution_character_set("utf-8")

int main(int argc, char* argv[]) {
	Game game;

	if (!game.init("persing111", 2, "TEST_GAME")) {
		return EXIT_FAILURE;
	}


	for (int i = 0;; i++) {
		game.game_step();

		if (i % 20 == 0) {
			game.print_info();
		}

		std::cout << "turn " << game.turn_number << std::endl;
	}

	game.end();

	return 0;
}
