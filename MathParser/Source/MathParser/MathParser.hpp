#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "Parser/Token.hpp"


namespace mp {
    class MathParser {
    public:
        using Tokens = std::vector<mp::Token>;

        static auto Calculate(const MathParser::Tokens &expression) -> double;

    private:
        static auto ToReversePolishNotation(const Tokens& tokens) -> Tokens;
        static auto CalculateTokens(const double &v1, const double &v2, const mp::Token &op) -> double;
    };
}
