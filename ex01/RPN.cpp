#include "RPN.hpp"
#include <stack>
#include <cctype>

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int applyOperator(int num1, int num2, char operator_char) {
    if (operator_char == '+')
        return num1 + num2;

    if (operator_char == '-') 
        return num1 - num2;

    if (operator_char == '*')
        return num1 * num2;

    if (operator_char == '/') {
        if (num2 == 0)
            throw std::runtime_error("Zero division");
        return num1 / num2;
    }
    throw std::invalid_argument("Invalid operator");
}

void calculateRPN(const std::string& expression) {
    if (expression.empty()) {
        std::cerr << "Error" << std::endl;
        return;
    }
    std::stack<int> nums;
    for (size_t i = 0; i < expression.length(); i++) {
        if (std::isspace(static_cast<unsigned char>(expression[i]))) {
            continue;
        }
        if (std::isdigit(expression[i])) {
            nums.push(expression[i] - '0');
            continue;
        }
        if (isOperator(expression[i])) {
            if (nums.size() < 2) {
                std::cerr << "Error" << std::endl;
                return;
            }
            int num2 = nums.top();
            nums.pop();
            int num1 = nums.top();
            nums.pop();
            // operatorに応じて計算してpushする。
            try {
                int result = applyOperator(num1, num2, expression[i]);
                nums.push(result);
            }   catch (std::exception& e) {
                std::cerr << "Error" << std::endl;
            }
        }
        else {
            std::cerr << "Error" << std::endl;
            return;
        }
    }
    if (nums.size() != 1) {
        std::cerr << "Error" << std::endl;
        return;
    }
    std::cout << nums.top() << std::endl;
}

// 引数チェック　数値が0 ~ 9 演算子　+ - * /　かどうか 　スペースごとにスキップしてスタックに積むか　演算するか
// 数値が来たらpushする 演算子が来た場合は最後に積んだ２つをpopして計算してその結果をpushする 