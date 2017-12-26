 
#include <limits.h>
#include <iostream>
#include "dijkstra.h"

dijkstra::dijkstra(std::map<uint32_t, std::map<uint32_t, uint32_t>> &edges_lens, uint32_t vert_count) :
	edges_lens(edges_lens),
	vertices_count(vert_count) {}

uint32_t min_distance(std::vector<uint32_t> dists, std::vector<bool> used) {
	uint32_t min = INT_MAX;
	uint32_t idx_of_min = INT_MAX;

	for (uint32_t v = 0; v < dists.size(); v++) {
		if (used[v] == false && dists[v] <= min) {
			min = dists[v];
			idx_of_min = v;
		}
	}

	return idx_of_min;
}

std::map<uint32_t, std::pair<uint32_t, std::vector<uint32_t>>> dijkstra::get_min_pathes(uint32_t from) {
	std::vector<uint32_t> dists(vertices_count + 1, INT_MAX);
	std::vector<bool> used(vertices_count + 1, false);
	std::vector<int32_t> parents(vertices_count + 1, -1);

	dists[from] = 0;

	for (uint32_t count = 0; count < vertices_count - 1; count++) {
		auto u = min_distance(dists, used);
		used[u] = true;

		for (auto ver_info : edges_lens[u]) {
			auto v = ver_info.first;
			auto curr_len = ver_info.second;

			if (!used[v] && dists[u] + curr_len < dists[v]) {
				parents[v] = u;
				dists[v] = dists[u] + curr_len;
			}
		}
	}

	return  get_full_min_pathes(from, dists, parents);
}

std::vector<uint32_t> dijkstra::get_best_way(uint32_t home_point, uint32_t train_cap, uint32_t from, std::vector<std::pair<uint32_t, uint32_t>> pass_edges,
	std::map<uint32_t, uint32_t> possible_points,
	std::function<float(uint32_t train_cap, uint32_t post_idx, uint32_t len)> fun, bool home) {

	for (size_t i = 0; i < pass_edges.size(); i++) {	
		if (pass_edges[i].first != pass_edges[i].second) {
			edges_lens.at(pass_edges[i].first).erase(pass_edges[i].second);
			edges_lens.at(pass_edges[i].second).erase(pass_edges[i].first);
		}
	}

	for (size_t i = 0; i < pass_edges.size(); i++) {
		/*for (auto edge : edges_lens) {
			edges_lens.at(edge.first).erase(pass_edges[i].second);
		}*/
		if (pass_edges[i].second != home_point) {
			edges_lens.erase(pass_edges[i].second);
		}
	}

	auto min_pathes = get_min_pathes(from);

	if (home == true)
		return min_pathes[home_point].second;

	float max_profit = -1;
	uint32_t best = (*possible_points.begin()).first;

	for (auto point : possible_points) {
		float curr_profit = fun(train_cap, point.second, min_pathes[point.first].first + min_pathes[home_point].first);

		if (curr_profit > max_profit) {
			max_profit = curr_profit;
			best = point.first;
		}
	}
	return min_pathes[best].second;
}

std::map<uint32_t, std::pair<uint32_t, std::vector<uint32_t>>> dijkstra::get_full_min_pathes(
	uint32_t from,
	const std::vector<uint32_t> &dists,
	const std::vector<int32_t> &parents) {

	std::map<uint32_t, std::pair<uint32_t, std::vector<uint32_t>>> res;

	for (uint32_t i = 0; i < vertices_count; ++i) {
		if (i != from) {
			std::vector<uint32_t> curr_path;
			uint32_t son = i;
			while (parents[son] != -1) {
				curr_path.insert(curr_path.begin(), son);
				son = parents[son];
			}
			res.insert(std::make_pair(i, std::make_pair(dists[i], curr_path)));
		}
	}

	return res;
}
