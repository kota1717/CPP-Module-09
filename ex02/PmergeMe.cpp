#include "PmergeMe.hpp"
#include <cstddef>
#include <algorithm>

// -- vector container version --

size_t getJacobSthal(size_t n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	size_t j_prev = 1;
	size_t j_curr = 1;
	for (size_t i = 3; i <= n; i++) {
		size_t next = j_curr + 2 * j_prev;
		j_prev = j_curr;
		j_curr = next;
	}
	return j_curr;
}

void insertLoser(std::vector<int>& mainChain, const std::vector<int>& pending,
								const std::vector<int>& winners) {

	mainChain.insert(mainChain.begin(), pending[0]);

	size_t num_pairs = pending.size();
	size_t last_jacob = 1;
	size_t jacob_index = 3;

	while (last_jacob < num_pairs) {
		size_t curr_jacob = getJacobSthal(jacob_index);
		size_t target_bound = std::min(curr_jacob, num_pairs);

		for (size_t i = target_bound; i > last_jacob; i--) {
			int A_i = winners[i - 1];
			int B_i = pending[i - 1];

			std::vector<int>::iterator bound = std::find(mainChain.begin(), mainChain.end(), A_i);
			std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), bound, B_i);
			mainChain.insert(pos, B_i);
		}
		last_jacob = target_bound;
		jacob_index++;
	}
}

std::vector<int> FordJohnsonSort(std::vector<int>& nums) {
	if (nums.size() <= 1)
		return nums;

	std::vector<int> winner;
	std::vector<std::pair<int, int> > pairs;

	bool has_odd = (nums.size() % 2 != 0);
	int odd_element = 0;
	if (has_odd) {
		odd_element = nums.back();
		nums.pop_back();
	}

	for (size_t i = 0; i < nums.size(); i += 2) {
		int win = nums[i];
		int lose = nums[i + 1];
		if (win < lose) {
			std::swap(win, lose);
		}
		pairs.push_back(std::make_pair(win, lose));
		winner.push_back(win);
	}

	std::vector<int> mainChain = FordJohnsonSort(winner);

	std::vector<int> pending(pairs.size());
	std::vector<bool> used(pairs.size(), false);

	for (size_t i = 0; i < mainChain.size(); ++i) {
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (!used[j] && pairs[j].first == mainChain[i]) {
				pending[i] = pairs[j].second;
				used[j] = true;
				break;
			}
		}
	}

	std::vector<int> winners = mainChain;

	insertLoser(mainChain, pending, winners);

	if (has_odd) {
		std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), odd_element);
		mainChain.insert(pos , odd_element);
	}

	return mainChain;
}

// -- deque container version --

void insertLoser(std::deque<int>& mainChain, const std::deque<int>& pending,
								const std::deque<int>& winners) {

	mainChain.insert(mainChain.begin(), pending[0]);

	size_t num_pairs = pending.size();
	size_t last_jacob = 1;
	size_t jacob_index = 3;

	while (last_jacob < num_pairs) {
		size_t curr_jacob = getJacobSthal(jacob_index);
		size_t target_bound = std::min(curr_jacob, num_pairs);

		for (size_t i = target_bound; i > last_jacob; i--) {
			int A_i = winners[i - 1];
			int B_i = pending[i - 1];

			std::deque<int>::iterator bound = std::find(mainChain.begin(), mainChain.end(), A_i);
			std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), bound, B_i);
			mainChain.insert(pos, B_i);
		}
		last_jacob = target_bound;
		jacob_index++;
	}
}

std::deque<int> FordJohnsonSort(std::deque<int>& nums) {
	if (nums.size() <= 1)
		return nums;

	std::deque<int> winner;
	std::deque<std::pair<int, int> > pairs;

	bool has_odd = (nums.size() % 2 != 0);
	int odd_element = 0;

	if (has_odd) {
		odd_element = nums.back();
		nums.pop_back();
	}

	for (size_t i = 0; i < nums.size(); i += 2) {
		int win = nums[i];
		int lose = nums[i + 1];
		if (win < lose) {
			std::swap(win, lose);
		}
		pairs.push_back(std::make_pair(win, lose));
		winner.push_back(win);
	}

	std::deque<int> mainChain = FordJohnsonSort(winner);

	std::deque<int> pending(pairs.size());
	std::deque<bool> used(pairs.size(), false);

	for (size_t i = 0; i < mainChain.size(); ++i) {
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (!used[j] && pairs[j].first == mainChain[i]) {
				pending[i] = pairs[j].second;
				used[j] = true;
				break;
			}
		}
	}

	std::deque<int> winners = mainChain;

	insertLoser(mainChain, pending, winners);

	if (has_odd) {
		std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), odd_element);
		mainChain.insert(pos , odd_element);
	}

	return mainChain;
}
