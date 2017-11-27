#include "game.h"

#include <string>
#include <iostream>
#include <fstream>


#pragma execution_character_set("utf-8")

int main(int argc, char* argv[]) {
	
	std::ofstream log("log.txt");
	if (!game::init())
		return EXIT_FAILURE;

	
	
	return game::end();
}
