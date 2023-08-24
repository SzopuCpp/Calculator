#include "MathParser.hpp"

#include <format>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>

#include "Parser/Token.hpp"

namespace mp {
    auto MathParser::Calculate(const MathParser::Tokens &expression) -> double {
        using namespace mp;

        Tokens tokens = ToReversePolishNotation(expression);

        for (;;) {
            auto operatorPos = std::ranges::find_if(
                    tokens,
                    [](const auto &t) { return t.IsOperator(); }
            );
            if (operatorPos == tokens.end())
                break;

            const auto distance_from_begin = operatorPos - tokens.begin();

            if (operatorPos->IsOperator() && distance_from_begin >= 2) {
                const auto first = operatorPos - 2;
                const auto second = operatorPos - 1;

                if (*first == TokenType::Number && *second == TokenType::Number) {
                    *operatorPos = Token{CalculateTokens(first->value, second->value, *operatorPos)};
                    tokens.erase(first, second + 1);
                }
            } else throw std::runtime_error("Invalid operator");
        }

        if (tokens.size() != 1)
            throw std::runtime_error("Invalid expression");
        return tokens[0].value;
    }

    auto MathParser::ToReversePolishNotation(const Tokens &tokens) -> Tokens {
        using
        enum mp::TokenType;

        Tokens outputQueue;
        std::stack<mp::TokenType> operatorStack;

        for (const auto &token: tokens) {
            if (token.tokenType == Number) {
                outputQueue.push_back(token);
//		} else if(token.IsFunction()) {
//            operatorStack.push(token);
            } else if (token.IsOperator()) {
                while (!operatorStack.empty() && operatorStack.top() != LeftParenthesis
                       && (PrecedenceOf(operatorStack.top()) > PrecedenceOf(token)
                           || (PrecedenceOf(operatorStack.top()) == PrecedenceOf(token) && IsLeftAssociative(token)))) {
                    outputQueue.emplace_back(operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.push(token);
            } else if (token.tokenType == LeftParenthesis) {
                operatorStack.push(LeftParenthesis);
            } else if (token.tokenType == RightParenthesis) {
                while (!operatorStack.empty() && operatorStack.top() != LeftParenthesis) {
                    outputQueue.emplace_back(operatorStack.top());
                    operatorStack.pop();
                }
                if (operatorStack.empty() || operatorStack.top() != LeftParenthesis)
                    throw std::logic_error{"Parentheses are mismatched"};
                operatorStack.pop();
            }
        }
        while (!operatorStack.empty()) {
            auto topOperator = operatorStack.top();
            if (topOperator == LeftParenthesis)
                throw std::logic_error{"Parentheses are mismatched"};
            outputQueue.emplace_back(topOperator);
            operatorStack.pop();
        }

        return outputQueue;
    }

    auto MathParser::CalculateTokens(const double &v1, const double &v2, const mp::Token &op) -> double {
        double result;
        switch (op.tokenType) {
            case mp::TokenType::Add:
                result = v1 + v2;
                break;
            case mp::TokenType::Subtract:
                result = v1 - v2;
                break;
            case mp::TokenType::Multiply:
                result = v1 * v2;
                break;
            case mp::TokenType::Divide:
                result = v1 / v2;
                break;
            default:
                throw std::logic_error("");
        }
        return result;
    }

//    auto MathParser::Parse(const std::string &expression) -> Tokens {
//        using namespace mp;
//
//        std::istringstream ss{expression};
//
//        Tokens tokens;
//        char c;
//
//        while (ss >> c) {
//            if (std::isdigit(c)) {
//                ss.putback(c);
//                double value;
//                ss >> value;
//                tokens.emplace_back(value);
//            } else {
//                TokenType type;
//
//                switch (c) {
//                    case '+':
//                        type = TokenType::Add;
//                        break;
//                    case '-':
//                        type = TokenType::Subtract;
//                        break;
//                    case '*':
//                        type = TokenType::Multiply;
//                        break;
//                    case '/':
//                        type = TokenType::Divide;
//                        break;
//                    case '(':
//                        type = TokenType::LeftParenthesis;
//                        break;
//                    case ')':
//                        type = TokenType::RightParenthesis;
//                        break;
//                    default:
//                        throw std::logic_error(std::format("Invalid character: {}", c));
//                }
//
//                tokens.emplace_back(type);
//            }
//            if (ss.eof()) break;
//        }
//
//        return tokens;
//    }
}

