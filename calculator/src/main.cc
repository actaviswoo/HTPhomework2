#include "tokenizer.h"


int main() {
    std::string input = "(max(123, abs(456)) - sqr(7)) * 8 & 9";

    Tokenizer tokenizer;
    std::vector<Token> tokens = tokenizer.Tokenize(input);
    std::cout << "Tokens:" << std::endl;
    for (const auto& token : tokens)
        std::cout << token << std::endl;
    return 0;
}