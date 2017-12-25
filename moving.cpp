 
#include "game.h"

//--	MOVING
bool Game::move(uint32_t line_idx, int speed, uint32_t train_idx) {
	json jMove({
		{ "line_idx", line_idx },
		{ "speed", speed },
		{ "train_idx", train_idx }
	});

	ActionMessage act = ActionMessage(Action::MOVE, jMove.dump());
	ResponseMessage resp;
	socket.make_move(act, resp);

	if (resp.resp_code != Response::OKEY) {
		return false;
	}
	//std::cout << ">> move" << std::endl;
	return true;
}

bool Game::move(uint32_t point_idx, uint32_t train_idx) {
	uint32_t line_idx;
	int speed;

	for (auto line : map.at(point_idx)) {
		if (line.end == trains[train_idx].last_point_id) {
			line_idx = line.line_idx;
			speed = -line.direction;
			break;
		}
	}

	json jMove({
		{ "line_idx", line_idx },
		{ "speed", speed },
		{ "train_idx", train_idx }
	});

	ActionMessage act = ActionMessage(Action::MOVE, jMove.dump());
	ResponseMessage resp;
	socket.make_move(act, resp);

	if (resp.resp_code != Response::OKEY) {
		return false;
	}

	//print_log(">> move\n");
	return true;
}


//--	TURN
bool Game::turn() {
	ActionMessage act = ActionMessage(Action::TURN, std::string("{}"));
	ResponseMessage resp;
	socket.make_move(act, resp);

	if (resp.resp_code != Response::OKEY) {
		return false;
	}

	turn_number++;
	load_dynamic_map();

	//print_log(">> turn " + std::to_string(turn_number) + "\n");
	return true;
}

bool Game::turn(uint32_t num_of_turns_to_pass) {
	ActionMessage act = ActionMessage(Action::TURN, std::string("{}"));
	for (uint32_t i = 0; i < num_of_turns_to_pass; i++) {
		ResponseMessage resp;
		socket.make_move(act, resp);

		if (resp.resp_code != Response::OKEY) {
			return false;
		}
	}

	turn_number += num_of_turns_to_pass;
	load_dynamic_map();

	print_log(">> turn " + std::to_string(turn_number) + "\n");
	return true;
}