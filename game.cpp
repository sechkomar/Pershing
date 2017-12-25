 
#include "game.h"
#include "dijkstra.h"

//--	ETC

bool Game::upgrade(std::list<uint32_t> posts_, std::list<uint32_t> trains_) {
	json jUpg;
	/*std::vector<uint32_t> postsIdx;
	for (auto post : posts_) {
		postsIdx.push_back(post.idx);
	}
	jUpg["post"] = postsIdx;

	std::vector<uint32_t> trainsIdx;
	for (auto train : trains_) {
		trainsIdx.push_back(train.idx);
	}
	jUpg["train"] = trainsIdx;*/

	jUpg["post"] = posts_;
	jUpg["train"] = trains_;

	std::string strUpg = jUpg.dump();

	ResponseMessage resp;
	ActionMessage act(Action::UPGRADE, strUpg);
	socket.make_move(act, resp);

	if (resp.resp_code != Response::OKEY) {
		return false;
	}

	load_dynamic_map();

	//std::cout << ">> upgrade" << std::endl;
	return true;
}

void Game::update_train_point(Train & train) {
	if (train.cooldown != 0) {
		train.last_point_id = towns.at(home.post_id).point_id;
		return;
	}
	if (train.player_id == idx && train.speed == 0) {
		for (auto line : map.at(train.last_point_id)) {
			if (train.line_idx == line.line_idx) {
				if (line.direction == 1) {
					if (train.position == line.length) train.last_point_id = line.end;
				}
				else if (train.position == 0) train.last_point_id = line.end;
			}
		}
	}
}
 
void Game::set_train_point(Train & train) {
	for (auto lines : map) {
		for (auto line : lines.second) {
			if (line.line_idx == train.line_idx) {				
				if (line.direction == 1) {
					if (train.position == 0)
						train.last_point_id = lines.first;
					else if (train.position == line.length)
						train.last_point_id = line.end;
					else train.last_point_id = 0;
				}
				else {
					if (train.position == 0)
						train.last_point_id = line.end;
					else if (train.position == line.length)
						train.last_point_id = lines.first;
					else train.last_point_id = 0;
				}
			}
		}
	}
}

void Game::go(Train &tr, post_type market_type) {

	if (tr.speed == 0) {

		if (tr.current_path.size() != 0 && tr.current_path.front() == tr.last_point_id) {
			tr.current_path.erase(tr.current_path.begin());
		}

		dijkstra d(edges_lens, 100);

		std::map<uint32_t, uint32_t> possible_posts;
		std::vector<std::pair<uint32_t, uint32_t>> passed;
		std::pair<uint32_t, uint32_t> point;

		if (market_type == post_type::MARKET) {
			for (auto m : markets) {
				possible_posts[m.second.point_id] = m.first;
			}
			get_profit = [this](uint32_t train_cap, uint32_t post_idx, uint32_t len) {
				Market m = markets[post_idx];
				return min(train_cap, min(m.product + len * m.replenishment, m.product_capacity)) / float(2 * len);
			};
		}
		else if (market_type == post_type::STORAGE) {
			for (auto s : storages) {
				possible_posts[s.second.point_id] = s.first;
			}
			get_profit = [this](uint32_t train_cap, uint32_t post_idx, uint32_t len) {
				Storage s = storages[post_idx];
				return min(train_cap, min(s.armor + len * s.replenishment, s.armor_capacity)) / float(2 * len);
			};
		}

		for (auto train : trains) {
			if (train.second.player_id == idx && train.second.current_path.size() != 0 && train.second.idx != tr.idx) {
				possible_posts.erase(train.second.current_path.front());
			}
			else if (train.second.player_id == idx && train.second.current_path.size() == 0 && train.second.idx != tr.idx) {
				possible_posts.erase(train.second.last_point_id);
			}

			if (train.second.player_id == idx  && train.second.idx != tr.idx) {
				if (train.second.current_path.size() != 0) {
					point.first = train.second.last_point_id;
					point.second = train.second.current_path.front();
					passed.push_back(point);
				}
				else {
					point.first = train.second.last_point_id;
					point.second = train.second.last_point_id;
					passed.push_back(point);
				}
			}
		}

		if (market_type == post_type::MARKET) {
			for (auto s : storages) {
				point.first = s.second.point_id;
				point.second = s.second.point_id;
				passed.push_back(point);
			}
		}
		else if (market_type == post_type::STORAGE) {
			for (auto m : markets) {
				point.first = m.second.point_id;
				point.second = m.second.point_id;
				passed.push_back(point);
			}
		}

		if (tr.goods_capacity <= tr.goods * 1.5) {
			auto best = d.get_best_way(towns.at(home.post_id).point_id, tr.goods_capacity, tr.last_point_id, passed, possible_posts, get_profit, true);
			tr.current_path = best;
			return;
		}

		auto best = d.get_best_way(towns.at(home.post_id).point_id, tr.goods_capacity, tr.last_point_id, passed, possible_posts, get_profit);
		tr.current_path = best;
	}
}