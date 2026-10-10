#include "PmergeMe.hpp"
#include <iostream>
#include <climits>
#include <cstdlib>

template <typename Container>
bool ParseArgument(int argc, char* argv[], Container& container) {
	if (argc < 2)
		return false;

	for (int i = 1; i < argc; i++) {
		std::string arg = argv[i];

		if (arg.empty())
			return false;

		char* endptr;
		long val = std::strtol(arg.c_str(), &endptr, 10);

		if (*endptr != '\0' || val <= 0 || val > INT_MAX)
			return false;

		container.push_back(static_cast<int>(val));
	}
	return true;
}

template <typename Container>
void printContainer(Container& container) {
	for (size_t i = 0; i < container.size(); i++) {
		if (i > 0)
			std::cout << " ";
		std::cout << container[i];
	}
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	std::vector<int> vec;
	std::deque<int> deq;

	if (!ParseArgument(argc, argv, vec) || !ParseArgument(argc, argv, deq)) {
		std::cerr << "Error" << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "Before: ";
	printContainer(vec);

	// vector process time
	clock_t vec_start = clock();

	std::vector<int> sorted_vec = FordJohnsonSort(vec);

	clock_t vec_end = clock();
	double vec_time = static_cast<double>(vec_end - vec_start) / CLOCKS_PER_SEC * 1000000.0;

	// deque process time
	// clock_t deq_start = clock();

	// std::deque<int> sorted_deq = FordJohnsonSort(deq);

	// clock_t deq_end = clock();
	// double deq_time = static_cast<double>(deq_end - deq_start) / CLOCKS_PER_SEC * 1000000.0;

	std::cout << "After: ";
	printContainer(sorted_vec);

	std::cout << "Time to process a range of " << vec.size()
						<< " elements with std::vector : " << vec_time << " us"<< std::endl;
	// std::cout << "Time to process a range of " << deq.size()
	// 					<< " elements with std::deque : " << deq_time << " us"<< std::endl;
	return EXIT_SUCCESS;
}

// $> ./PmergeMe 3 5 9 7 4
// Before: 3 5 9 7 4
// After: 3 4 5 7 9
// Time to process a range of 5 elements with std::[..] : 0.00031 us
// Time to process a range of 5 elements with std::[..] : 0.00014 us
// $> ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
// Before: 141 79 526 321 [...]
// After: 79 141 321 526 [...]
// Time to process a range of 3000 elements with std::[..] : 62.14389 us
// Time to process a range of 3000 elements with std::[..] : 69.27212 us
// $> ./PmergeMe "-1" "2"
// Error
// $> # For OSX USER:
// $> ./PmergeMe `jot -r 3000 1 100000 | tr '\n' ' '`
// [...]
// $>
// この例では、時間の表記が意図的に不自然になっています。ソート処理とデータ管理処理の両方を含め、
// すべての操作にかかった時間を表示する必要があります。
