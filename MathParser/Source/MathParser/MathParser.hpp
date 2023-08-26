#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "Parser/Token.hpp"


namespace mp {
    class MathParser {
    public:
        using Tokens = std::vector<mp::Token>; //bad using, plus vector is fine type but you should mange this size at the start (prealocate)

        static auto Calculate(const MathParser::Tokens &expression) -> double;
        //Apart from the fact that I personally like this provision (it's ok when we omit explicitly specifying the output parameter),
        //the style of the code is inconsistent

    private:
        //It doesn't have to be a static class method, it can be in a cpp file as an internal method
        static auto ToReversePolishNotation(const Tokens& tokens) -> Tokens;
        //this too
        static auto CalculateTokens(const double &v1, const double &v2, const mp::Token &op) -> double;
    };
}
