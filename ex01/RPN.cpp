#include "RPN.hpp"
#include <stack>
#include <cctype>
#include <limits>

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int applyOperator(int num1, int num2, char operator_char) {
    if (operator_char == '+') {
        if (num2 > 0 && num1 > (std::numeric_limits<int>::max() - num2))
            throw std::overflow_error("Error: overflow");
        if (num2 < 0 && num1 < std::numeric_limits<int>::min() - num2)
            throw std::underflow_error("Error: underflow");
        return num1 + num2;
    }

    if (operator_char == '-') {
        if (num2 > 0 && num1 < (std::numeric_limits<int>::min() + num2))
            throw std::underflow_error("Error: underflow");
        if (num2 < 0 && num1 > (std::numeric_limits<int>::max() + num2))
            throw std::overflow_error("Error: overflow");
        return num1 - num2;
    }

    if (operator_char == '*') {
        if (num1 > 0) {
            if (num2 > 0 && num1 > (std::numeric_limits<int>::max() / num2))
                throw std::overflow_error("Error: overflow");
            if (num2 < 0 && num2 < (std::numeric_limits<int>::min() / num1))
                throw std::underflow_error("Error: underflow");
        } else if (num1 < 0) {
            if (num2 > 0 && num1 < (std::numeric_limits<int>::min() / num2))
                throw std::underflow_error("Error: underflow");
            if (num2 < 0 && num2 < (std::numeric_limits<int>::max() / num1))
                throw std::overflow_error("Error: overflow");
        }
        return num1 * num2;
    }

    if (operator_char == '/') {
        if (num2 == 0)
            throw std::runtime_error("Error: division by zero");
        if (num1 == std::numeric_limits<int>::min() && num2 == -1)
            throw std::overflow_error("Error: overflow");
        return num1 / num2;
    }
    return 0;
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
        if (std::isdigit(static_cast<unsigned char>(expression[i]))) {
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
            try {
                int result = applyOperator(num1, num2, expression[i]);
                nums.push(result);
            }   catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
                return;
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
