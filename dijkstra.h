#pragma once
 
#include <cstdint>
#include <map>
#include <vector>
#include <functional>

class dijkstra {
	std::map<uint32_t, std::map<uint32_t, uint32_t>> edges_lens;
	uint32_t vertices_count;

	std::map<uint32_t, std::pair<uint32_t, std::vector<uint32_t>>> get_full_min_pathes(
		uint32_t from,
		const std::vector<uint32_t> &vector,
		const std::vector<int32_t> &parents);
public:
	dijkstra(std::map<uint32_t, std::map<uint32_t, uint32_t>> &edges_lens, uint32_t vert_count);

	std::map<uint32_t, std::pair<uint32_t, std::vector<uint32_t>>> get_min_pathes(uint32_t from);

	std::vector<uint32_t> get_best_way(
		uint32_t home_point,
		uint32_t train_cap,
		uint32_t from,
		std::vector<std::pair<uint32_t, uint32_t>> pass_edges,
		std::map<uint32_t, uint32_t> possible_points, 
		std::function<float(uint32_t train_cap, uint32_t idx, uint32_t len)>,
		bool home = false);
};
