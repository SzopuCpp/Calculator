#include "Calculator.hpp"

#include <MathParser/MathParser.hpp>
#include <string>


//About messy idea. Look, you do not use template parameters in arguments, your function arent templates based on template class so..
//there is absolutely NO difference between making these functions as templates and as usual functions with separate names
//You are introducing unreasonable complexity


//looks this function and second, both of them may begeneric, logic is very similar
template<>
void Calculator::AppendToken<Calculator::TokenType::Number>(const QString &value) {
    if (!tokens.isEmpty()) {
        if (tokens.last().type == TokenType::Number) {
            tokens.last().value += value;
            return;
        } else if (tokens.last().type == TokenType::Parenthesis && tokens.last().value == ")") return;
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
    else if(tokens.last().type == TokenType::Number || tokens.last().value == ")")
        tokens.emplaceBack(TokenType::Operator, value);
}

template<>
void Calculator::AppendToken<Calculator::TokenType::Parenthesis>(const QString &value) {
    if(value == "(") {
        if (tokens.isEmpty() || tokens.last().type != TokenType::Number)
            tokens.emplaceBack(TokenType::Parenthesis, value);
    } else if (value == ")") {
        if (!tokens.isEmpty() && tokens.last().type != TokenType::Operator)
            tokens.emplaceBack(TokenType::Parenthesis, value);
    }
}

template<>
void Calculator::AppendToken<Calculator::TokenType::Dot>(const QString &value) {
    if (!tokens.isEmpty() && tokens.last().type == TokenType::Number) {
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

//If you didn't parse tokens on a regular basis here is an example of removing complexity, you wouldn't be interested in deleting a token at all
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

//negatoin shuld be process like operator token (overload)
void Calculator::Negate() noexcept {
    if (!tokens.isEmpty() && tokens.last().type == TokenType::Number) {
        if (tokens.last().value.startsWith("-"))  tokens.last().value.removeFirst();
        else tokens.last().value.push_front("-");
    }
    UpdateText();
}

void Calculator::Calculate() noexcept {
    if(tokens.isEmpty()) return;

    mp::MathParser::Tokens expression; //MathParser shoud create expression based on string
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
        //moving math parser to thread will be nice (and using signals and slots)
        //bot is not nessesary, you still need to block 90% UI to wait result
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
