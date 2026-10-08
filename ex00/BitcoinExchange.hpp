#ifndef BITCOIN_EXCHANGE_HPP_
#define BITCOIN_EXCHANGE_HPP_

#include <map>
#include <string>
#include <iostream>
#include <fstream>

class BitcoinExchange {
	std::map<std::string, float> db_;
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	void loadDatabase(const std::ifstream& database);
}

#endif

// 特定の日付における、一定量のビットコインの値を出力する
// プログラムを作成してください。
// このプログラムでは、ビットコインの価格推移を
// 表すCSV形式のデータベースを使用する必要があります。
// このデータベースは本課題と共に提供されます。
// プログラムは、評価対象となる異なる価格と日付を格納した
// 2つ目のデータベースを入力として受け取ります。
// プログラムは以下のルールに従う必要があります：
// • プログラム名は btc としてください。
// • プログラムは引数としてファイルを受け取る必要があります。
// • このファイルの各行は、以下の形式である必要があります："date | value"。
// • 有効な日付は、常に Year-Month-Day の形式である必要があります。
// • 有効な値は、float型、または0から1000までの正の整数である必要があります。

// プログラムは入力ファイル内の値を使用します。プログラムは、データベースに指定された
// 日付に基づいて、入力値に為替レートを乗じた結果を標準出力に表示する必要があります。

// 入力された日付がデータベースに存在しない場合は、データベース内で最も近い日付を使用する
// 必要があります。その際、日付の小さい方を使用し、大きい方の日付を使用しないように注意してください。
