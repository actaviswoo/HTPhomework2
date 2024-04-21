#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <vector>
#include <variant>
#include <unordered_map>

// отличие от java объекты в c++ не наследуют класс object, и соотвественно метода toString() нет у классов
// в связи с этим репликации как таковой нет, это означает, что для каждой структуры пришлость опрядлять оператор <<
// данный функционал имеет полезность лишь для отладки токенайзера и впоследующем, убедившись в том, 
// что токенайзер работает правильно, его можно будет убрать, поскольку калькулятор в данном функционале не нуждается

struct OpeningBracketToken { 
    friend std::ostream& operator<<(std::ostream& os, const OpeningBracketToken&) { return os << "OpeningBracketToken"; }
};
struct ClosingBracketToken { 
    friend std::ostream& operator<<(std::ostream& os, const ClosingBracketToken&) { return os << "ClosingBracketToken"; }
};
struct CommaToken {
    friend std::ostream& operator<<(std::ostream& os, const CommaToken&) { return os << "CommaToken"; }
};
struct MinToken {
    friend std::ostream& operator<<(std::ostream& os, const MinToken&) { return os << "MinToken"; }
};
struct MaxToken {
    friend std::ostream& operator<<(std::ostream& os, const MaxToken&) { return os << "MaxToken"; }
};   
struct AbsToken {
    friend std::ostream& operator<<(std::ostream& os, const AbsToken&) { return os << "AbsToken"; }
};   
struct SqrToken {
    friend std::ostream& operator<<(std::ostream& os, const SqrToken&) { return os << "SqrToken"; }
};   
struct PlusToken {
    friend std::ostream& operator<<(std::ostream& os, const PlusToken&) { return os << "PlusToken"; }
};
struct MinusToken {
    friend std::ostream& operator<<(std::ostream& os, const MinusToken&) { return os << "MinusToken"; }
};
struct MultiplyToken {
    friend std::ostream& operator<<(std::ostream& os, const MultiplyToken&) { return os << "MultiplyToken"; }
};
struct ModuloToken {
    friend std::ostream& operator<<(std::ostream& os, const ModuloToken&) { return os << "ModuloToken"; }
};
struct DivideToken {
    friend std::ostream& operator<<(std::ostream& os, const DivideToken&) { return os << "DivideToken"; }
};
struct NumberToken {
    int value;
    friend std::ostream& operator<<(std::ostream& os, const NumberToken& token) { return os << "NumberToken " << token.value; }
};
struct UnknownToken {
    std::string value;
    friend std::ostream& operator<<(std::ostream& os, const UnknownToken& token) { return os << "UnknownToken "<< token.value; }
};

using Token = std::variant<OpeningBracketToken, ClosingBracketToken, CommaToken, MinToken, MaxToken, AbsToken, SqrToken,
    PlusToken, MinusToken, MultiplyToken, ModuloToken, DivideToken, NumberToken, UnknownToken>;

std::ostream& operator<<(std::ostream& os, const Token& token) {
    std::visit([&os](const auto& t) { os << t; }, token);
    return os;
}

// так как в задании явно не сказано, что токенайзер должен обрабатывать неправильный ввод, 
// то обязанность обработки ошибочного ввода, будет передана парсеру

// поскольку калькулятор будет работать в цикле то, лучшим решением будет объявить 
// symbol2Token и func2Token статичными приватными полями класса Tokenizer, чтобы не было накладных расходов

// единственным доступным методом Tokenizer является Tokenize, поскольку от него больше ничего не требуется
// методы ToDigit, ParseNumber, ParseName объявлены приватными, поскольку к достпуному функционалу не имеют причастия

class Tokenizer {
public:
    Tokenizer() {};

    std::vector<Token> Tokenize(const std::string& input);

private:
    static const std::unordered_map<char, Token> symbol2Token;
    static const std::unordered_map<std::string, Token> func2Token;
    int ToDigit(unsigned char symbol);
    NumberToken ParseNumber(const std::string& input, size_t& pos);
    Token ParseName(const std::string& input, size_t& pos);
};

const std::unordered_map<char, Token> Tokenizer::symbol2Token {
    {'+', PlusToken{}},
    {'-', MinusToken{}},
    {'*', MultiplyToken{}},
    {'/', DivideToken{}},
    {'%', ModuloToken{}},
    {'(', OpeningBracketToken{}},
    {')', ClosingBracketToken{}},
    {',', CommaToken{}}
};

const std::unordered_map<std::string, Token> Tokenizer::func2Token {
    {"abs", AbsToken{}},
    {"min", MinToken{}},
    {"max", MaxToken{}},
    {"sqr", SqrToken{}}
};


// принимает символ в качестве аргумента и возвращает соответствующее числовое значение
int Tokenizer::ToDigit(unsigned char symbol) {
    return symbol - '0';
}

// принимает в качестве аргумента исходную строку и позицию в ней
// возвращает NumberToken, содержащий число
// число определяется циклом в котором происходит перемещение по символам
NumberToken Tokenizer::ParseNumber(const std::string& input, size_t& pos) {
    int value = 0;
    auto symbol = static_cast<unsigned char>(input[pos]);
    
    while (std::isdigit(symbol)) {
        value = value * 10 + ToDigit(symbol);
        if (pos == input.size() - 1) {
            ++pos;
            break;
        }
        symbol = static_cast<unsigned char>(input[++pos]);
    }

    return NumberToken{value};
}

// принимает в качестве аргумента исходную строку и позицию в ней
// возвращает Token, представляющий имя функции или неизвестный токен
// пока текущая позиция является символом, он добавляет его к строке str
// токен опредляется циклом в котором str, является либо элементом func2Token, либо не является
Token Tokenizer::ParseName(const std::string& input, size_t& pos) {
    auto symbol = input[pos];
    std::string str;

    while (std::isalpha(symbol)) {
        str.push_back(symbol);
        if (pos == input.size() - 1) {
            ++pos;
            break;
        }
        symbol = input[++pos];
    }

    if (auto it = func2Token.find(str); it != func2Token.end()) {
        return it->second;
    }

    if (str.empty()) {
        ++pos;
        str.push_back(symbol);
    }

    return UnknownToken{str};
}

// принимает в качестве аргумента исходную строку
// возвращает вектор токенов, полученных из строки
// вектор заполняется перемещением по каждому символу строки, анализируя соотвестующими методами
std::vector<Token> Tokenizer::Tokenize(const std::string& input) {
    std::vector<Token> tokens;
    const size_t size = input.size();
    size_t pos = 0;

    while (pos < size) {
        const auto symbol = static_cast<unsigned char>(input[pos]);
        if (std::isspace(symbol)) {
            ++pos;
        } else if (std::isdigit(symbol)) {
            tokens.emplace_back(ParseNumber(input, pos));
        } else if (auto it = symbol2Token.find(symbol); it != symbol2Token.end()) {
            tokens.emplace_back(it->second);
            ++pos;
        } else {
            tokens.emplace_back(ParseName(input, pos));
        }
    }

    return tokens;
}

#endif  // TOKENIZER_H
