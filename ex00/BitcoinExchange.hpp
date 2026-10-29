#ifndef BITCOIN_EXCHANGE_HPP_
#define BITCOIN_EXCHANGE_HPP_

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <locale>
#include <cmath>

class BitcoinExchange {
	std::map<std::string, float> db_;
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	float getExchangeRate(const std::string& date);

	bool loadDatabase(const std::string& dbPath);
	bool processInput(const char* inputPath);
};

#endif
