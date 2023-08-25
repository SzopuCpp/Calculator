#pragma once

#include <QtCore>

#include <MathParser/MathParser.hpp>


class Calculator : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString text READ GetText NOTIFY TextChanged)

public:
    enum class TokenType {
        Number,
        Operator,
        Parenthesis,
        Dot
    };
    Q_ENUM(TokenType)

private:
    QString text;
    bool error {false};

    struct TokenData {
        TokenType type;
        QString value;

        bool isNegative {false};
    };

    QList<TokenData> tokens { TokenData{} };

    template<TokenType type>
    void AppendToken(const QString& value);
    void UpdateText();

public:
    QString GetText() const noexcept;

    Q_INVOKABLE void Append(const QString &value, TokenType type = TokenType::Number) noexcept;
    Q_INVOKABLE void Delete() noexcept;
    Q_INVOKABLE void Negate() noexcept;
    Q_INVOKABLE void Calculate() noexcept;

signals:
    void TextChanged(QString);
};