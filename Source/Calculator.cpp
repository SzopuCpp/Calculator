#include "Calculator.hpp"

#include <MathParser/MathParser.hpp>
#include <string>


template<>
void Calculator::AppendToken<Calculator::TokenType::Number>(const QString &value) {
    if (!tokens.isEmpty() && tokens.last().type == TokenType::Number) {
        tokens.last().value += value;
        return;
    }
    tokens.emplaceBack(TokenType::Number, value);
}

template<>
void Calculator::AppendToken<Calculator::TokenType::Operator>(const QString &value) {
    if (tokens.isEmpty()) return;

    if (tokens.last().type == TokenType::Operator) {
        tokens.last().value = value;
        return;
    }
    else if(tokens.last().type == TokenType::Number)
        tokens.emplaceBack(TokenType::Operator, value);
}

template<>
void Calculator::AppendToken<Calculator::TokenType::Parenthesis>(const QString &value) {
    tokens.emplaceBack(TokenType::Parenthesis, value);
}

template<>
void Calculator::AppendToken<Calculator::TokenType::Dot>(const QString &value) {
    if(tokens.isEmpty()) return;

    if (tokens.last().type == TokenType::Number || tokens.last().value == ")") {
        if (tokens.last().value.contains(".")) return;
        tokens.last().value.append(".");
    }
}

QString Calculator::GetText() const noexcept {
    return text;
}

void Calculator::Append(const QString &value, TokenType type) noexcept {
    switch (type) {
        case TokenType::Number:
            AppendToken<TokenType::Number>(value);
            break;
        case TokenType::Operator:
            AppendToken<TokenType::Operator>(value);
            break;
        case TokenType::Parenthesis:
            AppendToken<TokenType::Parenthesis>(value);
            break;
        case TokenType::Dot:
            AppendToken<TokenType::Dot>(value);
            break;
        default: break;
    }

    UpdateText();
}

void Calculator::Delete() noexcept {
    if(tokens.isEmpty()) return;

    if (tokens.last().type == TokenType::Number) {
        if (tokens.last().value.size() <= 1) {
            tokens.removeLast();
        } else {
            tokens.last().value.removeLast();
        }
    } else tokens.removeLast();
    UpdateText();
}

void Calculator::Negate() noexcept {
    if (!tokens.isEmpty() && tokens.last().type == TokenType::Number) {
        if (tokens.last().value.startsWith("-"))  tokens.last().value.removeFirst();
        else tokens.last().value.push_front("-");
    }
    UpdateText();
}

void Calculator::Calculate() noexcept {
    if(tokens.isEmpty()) return;

    mp::MathParser::Tokens expression;
    for (const auto& token : tokens) {
        if (token.type == TokenType::Number)
            expression.emplace_back(token.value.toDouble());
        else {
            mp::TokenType type;
            switch (token.value.toStdString()[0]) {
                case '+':
                    type = mp::TokenType::Add;
                    break;
                case '-':
                    type = mp::TokenType::Subtract;
                    break;
                case '*':
                    type = mp::TokenType::Multiply;
                    break;
                case '/':
                    type = mp::TokenType::Divide;
                    break;
                case '(':
                    type = mp::TokenType::LeftParenthesis;
                    break;
                case ')':
                    type = mp::TokenType::RightParenthesis;
                    break;
            }
            expression.emplace_back(type);
        }
    }

    try {
        tokens.clear();
        const auto result = QString::number(mp::MathParser::Calculate(expression));
        if (result == "nan" || result == "inf") {
            text = result;
            emit TextChanged(text);
            return;
        }
        tokens.emplaceBack(TokenType::Number, result);
    }
    catch (const std::exception& err) {
        text = "error";
        error = true;
        emit TextChanged(text);
        return;
    }
    UpdateText();
}

void Calculator::UpdateText() {
    QString newText;
    for (const auto& token : tokens) {
        newText += token.value;
    }
    text = newText;
    emit TextChanged(text);
}

template<Calculator::TokenType type>
void Calculator::AppendToken(const QString &value) {}