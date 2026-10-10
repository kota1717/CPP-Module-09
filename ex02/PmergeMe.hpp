#ifndef PMERGEME_HPP_
#define PMERGEME_HPP_

#include <vector>
#include <deque>

std::vector<int> FordJohnsonSort(std::vector<int>& nums);
std::deque<int> FordJohnsonSort(std::deque<int>& nums);

#endif

// • プログラムは、マージインサートソートアルゴリズムを使用して、正の整数
// 列をソートする必要があります。
// • プログラムの実行中にエラーが発生した場合は、標準エラー出力にエラーメッセージを表示する必要があります。
// この演習を検証するには、コード内で少なくとも2つの異なるコンテナを
// 使用する必要があります。プログラムは、重複する値を含めて、
// 少なくとも3000個の整数を処理できなければなりません。
// 各コンテナごとにアルゴリズムを実装し、汎用関数を使用することは避けることを強くお勧めします。
