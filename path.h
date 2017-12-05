#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

class CalculatePath {
	//--- const ---
	std::vector<uint32_t> market_indices;

	std::map<uint32_t, std::map<uint32_t, uint32_t>> distances;
	uint32_t train_capacity;
	std::map<uint32_t, uint32_t> replenishments; //<market idx, value>
	std::map<uint32_t, uint32_t> capacities;

	uint32_t population;
	uint32_t home_point_idx;

	//--- need to update ---
	uint32_t product_in_town;

	std::map<uint32_t, uint32_t> initial_products;
	std::map<uint32_t, uint32_t> expected_products;

	std::vector<uint32_t> curr_path; // !! the first idx - idx of our town 

	std::vector<uint32_t> curr_lens;
	int32_t profit; // может быть отрицательным


	void update_curr_lens() {
		curr_lens.clear();
		for (size_t i = 0; i < curr_path.size() - 1; i++) {
			curr_lens.push_back(distances[curr_path[i]][curr_path[i + 1]]);
		}
		curr_lens.push_back(distances[curr_path[0]][curr_path[curr_path.size() - 1]]);
	}

	uint32_t calculate_path_len() {
		update_curr_lens();
		return std::accumulate(curr_lens.begin(), curr_lens.end(), 0);
	}

	bool check_path_len(uint32_t path_len) {
		return path_len <= product_in_town / population;
	}

	// auxiliary function
	uint32_t get_expected_product(uint32_t serial_idx) { //serial_idx == serial number in path
		uint32_t market_idx = curr_path[serial_idx];
		return min(capacities[market_idx],
			initial_products[market_idx] +
			replenishments[market_idx] *
			std::accumulate(curr_lens.begin(), curr_lens.begin() + serial_idx, 0)
		);
	}

	void init_expected_products() {
		for (size_t i = 1; i < curr_path.size(); i++) {
			expected_products[curr_path[i]] = get_expected_product(i);
		}
	}

	// Поезд должен вместить в себя всё то, что он хочет забрать.
	// Но на последнем маркете в пути он не обязан пихать всё, что там есть,
	// а может забить себя под завязку и поехать домой

	uint32_t calculate_before_last() {
		uint32_t before_last = 0;
		for (size_t i = 1; i < curr_path.size() - 1; i++) {
			before_last += expected_products[curr_path[i]];
		}
		return before_last;
	}

	// auxiliary function
	uint32_t received_product(uint32_t before_last) {
		uint32_t left_on_train = train_capacity - before_last;
		uint32_t received = before_last + min(left_on_train,
			expected_products[curr_path[curr_path.size() - 1]]);
		return received;
	}

	bool check_train_capacity(uint32_t before_last) {
		return train_capacity > before_last;
		//если false, будет другая перестановка, в которой будет такой же путь, но без последнего узла
	}

	void calculate_profit(uint32_t path_len, uint32_t before_last) {
		profit = received_product(before_last) - population * path_len;
	}

	std::vector<std::vector<uint32_t>> get_subsets(std::vector<uint32_t> arr) {
		//TODO replaced by next_subset
		int subsets_count = 1 << arr.size();
		std::vector<std::vector<uint32_t>> res(subsets_count);

		for (int i = 0; i < subsets_count; i++) {
			for (int k = 0; k < arr.size(); k++) {
				//if the k-th bit is set
				if ((1 << k) & i) {
					res[i].push_back(arr[k]);
				}
			}
		}
		res.erase(res.begin());
		return res;
	}

	bool check() {
		uint32_t path_len = calculate_path_len();
		if (!check_path_len(path_len)) {
			return false;
		}

		init_expected_products();
		uint32_t before_last = calculate_before_last();

		if (!check_train_capacity(before_last)) {
			return false;
		}

		calculate_profit(path_len, before_last);
		//return profit >= 0;
		return true;
	}

	void set_curr_path(const std::vector<uint32_t> &path) {
		this->curr_path.clear();
		this->curr_path.assign(path.begin(), path.end());
		this->curr_path.insert(this->curr_path.begin(), home_point_idx);
	}



public:
	CalculatePath(const std::map<uint32_t, std::map<uint32_t, uint32_t>> &distances, uint32_t train_capacity,
		const std::map<uint32_t, uint32_t> &replenishments, const std::map<uint32_t, uint32_t> &capacities,
		uint32_t population, uint32_t home_idx, std::vector<uint32_t> market_indices) {

		this->distances = distances;
		this->train_capacity = train_capacity;
		this->replenishments = replenishments;
		this->capacities = capacities;
		this->population = population;
		this->home_point_idx = home_idx;
		this->market_indices = market_indices;
	}


	void set_product_in_town(uint32_t product) {
		this->product_in_town = product;
	}

	void set_init_products(std::map<uint32_t, uint32_t> init_products) {
		initial_products = init_products;
	}

	int32_t get_profit() {
		return profit;
	}

	std::vector<uint32_t> find_pathways() {
		auto subsets = get_subsets(market_indices);

		int32_t max_profit = 0;
		int32_t profit;
		std::vector<uint32_t> best;

		for (auto set : subsets) {
			do {
				set_curr_path(set);
				if (check() && (profit = get_profit()) > max_profit) {
					max_profit = profit;
					best = set;
				}
			} while (std::next_permutation(set.begin(), set.end()));
		}
		//for (auto n : best) {
		//	std::cout << n << " ";
		//}
		//std::cout << std::endl << max_profit << std::endl;
		return best;
	}
};




