#include "Token.hpp"


namespace mp {
	Token::Token(const TokenType& type) : tokenType{type} {}
    Token::Token(const double numberValue) : tokenType{ TokenType::Number }, value{ numberValue } {}

    auto Token::IsOperator() const noexcept -> bool {
        return mp::IsOperator(tokenType);
    }

    Token::operator TokenType() const noexcept {
        return  tokenType;
    }
}
