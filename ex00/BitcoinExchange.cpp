#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
	*this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this == &other)
		return *this;
	this->db_ = other.db_;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::loadDatabase(const std::string& dbPath) {
	std::ifstream database(dbPath.c_str());
	if (!database.is_open())
		return false;
	
	std::string line;
	// skip header line
	std::getline(database, line);

	while (std::getline(database, line)) {
		std::stringstream ss(line);
		std::string date;
		std::string rateStr;
		if (std::getline(ss, date, ',') && std::getline(ss, rateStr)) {
			float exchange_rate = static_cast<float>(std::atof(rateStr.c_str()));
			db_[date] = exchange_rate;
		}
	}
	return true;
}

std::string trim(std::string str) {
	// spaceを飛ばして格納する
	size_t first = 0;
	while (first < str.length() && isspace(static_cast<unsigned char>(str[first])))
		first++;
	if (first == str.length())
		return "";
	size_t last = str.length() - 1;
	while (last > first && isspace(static_cast<unsigned char>(str[last])))
		last--;
	return str.substr(first, last - first + 1);
}

bool isLeapYear(int year) {
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

// 有効な日付は、常に Year-Month-Day の形式である必要があります。
// year の範囲？ Month 1 ~ 12 Day 1-31 1-30 2月は、うるう年も対応しなくてはいけない？ 
bool isValidDate(const std::string& date) {
	if (date.length() != 10)
		return false;
	if ((date[4] != '-') || (date[7] != '-'))
		return false;
	
	for (size_t i = 0; i < date.length(); i++) {
		if ((i == 4) || (i == 7))
			continue;
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return false;
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12)
		return false;
	
	int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (month == 2 && isLeapYear(year))
		daysInMonth[2] = 29;
	
	if (day < 1 || day > daysInMonth[month])
		return false;

	return true;
}

// 有効な値は、float型、または0から1000までの正の整数である必要があります。
// Error: not a positive number.  負の値でないか
// Error: too large a number.　　　範囲に収まっているか
bool parseValue(float& value ,std::string valStr) {
	if (valStr.empty()) {
		std::cerr << "Error: bad input => " << valStr << std::endl;
		return false;
	}

	char* endPtr;
	double val = std::strtod(valStr.c_str(), &endPtr);
	
	if (*endPtr != '\0') {
		std::cerr << "Error: bad input => " << valStr << std::endl;
		return false;
	}

	if (val < 0) {
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}

	if (val > 1000) {
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}

	value = static_cast<float>(val);
	return true;
}

// dateから、同じか、近い日付を探してそこのrateをデータベースから取得する
float BitcoinExchange::getExchangeRate(const std::string& date) {
	std::map<std::string, float>::const_iterator it = db_.upper_bound(date);
	if (it == db_.begin()) {
		// データベースよりも前の日付が渡されたとき
		throw std::runtime_error("Error: bad input  => " + date);
	}
	--it;
	return it->second;
}

// 受け取った入力ファイルを開けるか確認、中身を解析して、db_と照らし合わせて適切な出力を出す。
bool BitcoinExchange::processInput(char* inputPath) {
	std::ifstream inputfile(inputPath);
	if (!inputfile.is_open())
		return false;
	
	std::string line;
	std::getline(inputfile, line);

	while (std::getline(inputfile, line)) {
		if (line.empty())
			continue;
		size_t pipePos = line.find('|');
		if (pipePos == std::string::npos) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date = trim(line.substr(0, pipePos));
		std::string valStr = trim(line.substr(pipePos + 1));

		if (!isValidDate(date)) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		float value;
		if (!parseValue(value, valStr))
			continue;
		
		try {
			float rate = getExchangeRate(date);
			std::cout << date << " => " << value  << " = " << (rate * value) << std::endl;
		} catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}	
	}
	return true;
}

// • 入力ファイルの各行は、以下の形式である必要があります："date | value"。
// • 有効な日付は、常に Year-Month-Day の形式である必要があります。