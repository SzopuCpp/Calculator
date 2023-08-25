#pragma once

#include <cstdint>


namespace mp {
    enum class TokenType {
        Number,
        Add,
        Subtract,
        Multiply,
        Divide,
        LeftParenthesis,
        RightParenthesis,
    };

    constexpr auto IsOperator(const TokenType token) noexcept -> bool {
        using enum TokenType;
        return token == Add || token == Subtract || token == Multiply || token == Divide;
    }

    constexpr auto IsLeftAssociative(const TokenType token) noexcept -> bool {
        using enum TokenType;
        return token == Add || token == Subtract || token == Multiply || token == Divide;
    }

    constexpr auto PrecedenceOf(const TokenType op) -> int16_t {
        using enum TokenType;
	    switch (op) {
	        case Add:
	        case Subtract:
                return 1;
	        case Multiply:
	        case Divide:
                return 2;

	        default:
                return -1;
	    }
    }

    struct Token {
        explicit Token(const TokenType& type);
        explicit Token(double numberValue);

        auto IsOperator() const noexcept -> bool;

        TokenType tokenType;
        double value {};

        operator TokenType() const noexcept;
    };
}

