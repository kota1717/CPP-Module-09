#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char**argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return EXIT_FAILURE;
	}

	BitcoinExchange btc;
	if (!btc.loadDatabase("data.csv"))
	{
		std::cerr << "Error: could not open database file." << std::endl;
		return EXIT_FAILURE;
	}

	if (!btc.processInput(argv[1]))
		return EXIT_FAILURE;
	
	return EXIT_SUCCESS;
}
