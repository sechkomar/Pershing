 
#include "game.h"

bool Game::init(std::string player_name, uint32_t num_player, 
				std::string game_name, std::string security_key) {

	const char* HOST_NAME = "wgforge-srv.wargaming.net";
	const char* PORT = "443";
	username = player_name;

	log.open("log.txt");

	if (socket.Connect(HOST_NAME, PORT)) {
		print_log("Error while connecting.\n");
		return false;
	}

	json jLogin;
	jLogin["name"] = player_name;
	jLogin["num_players"] = num_player;
	jLogin["game"] = game_name;

	if (!security_key.empty()) {
		jLogin["security_key"] = security_key;
	}

	if (!login(jLogin)) {
		print_log("Error while login\n");
		return false;
	}

	load_dynamic_map();

	return true;
}

bool Game::login(json jLogin) {
	std::string strLogin = jLogin.dump();
	ActionMessage act(Action::LOGIN, strLogin);

	ResponseMessage resp;
	socket.make_move(act, resp);

	if (resp.resp_code != Response::OKEY) {
		return false;
	}


	std::cout << "login response:\n" << resp.data << std::endl << std::endl;

	json jLoginResp = json::parse(resp.data);

	/*home.idx = jLoginResp["home"]["idx"].get<uint32_t>();
	home.post_id = jLoginResp["home"]["post_id"].get<uint32_t>();*/

	home = jLoginResp.at("town").get<Town>();
	idx = jLoginResp["idx"].get<std::string>();

	std::list<Train> trainsList = jLoginResp.at("train").get<std::list<Train>>();
	for (auto train : trainsList) {
		train.last_point_id = home.point_id;
		trains[train.idx] = train;
	}

	load_static_map();

	print_log(">> logged as " + username);
	return true;
}

int Game::end() {
	ActionMessage act = ActionMessage(Action::LOGOUT, std::string());
	ResponseMessage resp;
	socket.make_move(act, resp);

	print_log(">> logout\n bye, " + username);
	socket.Disconnect();
	log.close();
	return EXIT_SUCCESS;
}
