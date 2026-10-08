#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
	*this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this == &other)
		return *this;
	this->db_ = other.db_;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase(const std::ifstream& database) {
	BitcoinExchange Bitcoin;
	std::string line;
	while (std::getline(database, line)) {
		
	}
}
