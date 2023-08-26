#pragma once

#include <QtCore>

#include <MathParser/MathParser.hpp>


class Calculator : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString text READ GetText NOTIFY TextChanged)

public:
    //Tokens should be needed only at the stage of parsing the entire input,
    //there is no need to add them to the GUI (Q enum), they also partially duplicate the functionality of the parser
    enum class TokenType {
        Number,
        Operator,
        Parenthesis,
        Dot
    };
    Q_ENUM(TokenType)

private:
    QString text;
    bool error {false}; //make it simpler, just write = The compiler optimizes it anyway
    //plus error may be type with string of informations

    struct TokenData { //Can make all fields immutable, and as i say, its parsing, it should do not touch GUI
        TokenType type;
        QString value;

        bool isNegative {false};
    };

    QList<TokenData> tokens { TokenData{} }; //list is bad idea for this, vector may be fine, or QStack

    template<TokenType type> //what a messy idea... I will exaplain later
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
