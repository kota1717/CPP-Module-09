#include "RPN.hpp"
#include <cstdlib>

int main(int argc, char* argv[])
{
	if (argc != 2) {
        std::cerr << "Error" << std::endl;
        return EXIT_FAILURE;
    }
    calculateRPN(argv[1]);
    return EXIT_SUCCESS;
}

// $> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
// 42
// $> ./RPN "7 7 * 7 -"
// 42
// $> ./RPN "1 2 * 2 / 2 * 2 4 - +"
// 0
// $> ./RPN "(1 + 1)"
// Error
// $>
