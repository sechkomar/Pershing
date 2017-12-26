 
#include "game.h"

void Game::get_layer_response(layer type, ResponseMessage& resp) {
	json jLayer;
	jLayer["layer"] = type;

	std::string strLayer = jLayer.dump();
	ActionMessage act(Action::MAP, strLayer);
	socket.make_move(act, resp);
}

// good
bool Game::load_static_map() {
	ResponseMessage resp;
	get_layer_response(layer::STATIC, resp);

	//std::cout << "static map:\n" << resp.data << std::endl;

	if (resp.resp_code != Response::OKEY) {
		return false;
	}

	map.clear();

	json jMapResp = json::parse(resp.data);

	std::list<Line> lines = jMapResp.at("line").get<std::list<Line>>();
	for (auto line : lines) {
		Endpoint in(line.points.second, line.idx, line.length, 1);
		map[line.points.first].push_back(in);

		Endpoint out(line.points.first, line.idx, line.length, -1);
		map[line.points.second].push_back(out);

		edges_lens[line.points.first][line.points.second] = line.length;
		edges_lens[line.points.second][line.points.first] = line.length;
	}

	return true;
} 

// ok
bool Game::load_dynamic_map() {
	ResponseMessage resp;
	get_layer_response(layer::DYNAMIC, resp);

	if (resp.resp_code != Response::OKEY) {
		return false;
	}

	//std::cout << "dynamic map:\n" << resp.data << std::endl;

	json jMapResp = json::parse(resp.data);

	for (auto post : jMapResp.at("post")) {
		if (post["type"] == post_type::TOWN) {
			Town t(post);
			towns[t.idx] = t;
			home = towns[home.idx];

			if (home.events.size() != 0) {
				print_log("Home events:\n");
				for (auto e : home.events) {
					print_log(e + "\n");
				}
			}
		}
		else if (post["type"] == post_type::MARKET) {
			Market m(post);
			markets[m.idx] = m;
		}
		else if (post["type"] == post_type::STORAGE) {
			Storage s(post);
			storages[s.idx] = s;
		}
	}

	rating = jMapResp["rating"][username];

	std::list<Train> trainsList = jMapResp.at("train").get<std::list<Train>>();
	for (auto train : trainsList) {
		if (train.player_id == idx) {
			std::vector<uint32_t> cur_p = trains[train.idx].current_path;
			uint32_t train_last_point = trains[train.idx].last_point_id;

			trains[train.idx] = train;
			trains[train.idx].last_point_id = train_last_point;
			trains[train.idx].current_path = cur_p;

			update_train_point(trains[train.idx]);
		}
	}

	return true;
}