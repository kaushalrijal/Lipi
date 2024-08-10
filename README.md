# Lipi : A Programming Language

This project is an implementation of a Nepali programming language. The language includes various features such as keywords, data types, identifiers, literals, operators, and delimiters. This README provides an overview of the language and details on how a compiler can be implemented.

## Language Features

### Keywords
The language includes the following keywords:
- `bhana`
- `suna`
- `yadi`
- `anyatha`
- `jabasamma`
- `kaam`
- `firta`
- `lagi`
- `purna`
- `dasa`
- `akshar`
- `paath`
- `sahi`
- `galat`

### Data Types
The language supports the following data types:
- `purna` (float)
- `dasa` (integer)
- `akshar` (character)
- `paath` (string)
- `sahi`/`galat` (boolean)

### Identifiers
Identifiers in the language follow the pattern of starting with a letter or underscore, followed by any number of letters, digits, or underscores.

### Literals
The language supports the following literals:
- Numbers (both integers and floats)
- Strings (enclosed in double quotes)
- Characters (enclosed in single quotes)

### Operators
The language includes the following operators:
- Arithmetic: `+`, `-`, `*`, `/`, `%`
- Comparison: `=`, `<`, `>`, `!`
- Logical: `&`, `|`

### Delimiters
The language uses the following delimiters:
- Parentheses: `(`, `)`
- Braces: `{`, `}`
- Semicolon: `;`

## Lexer Implementation

The lexer is responsible for converting the input source code into a series of tokens. Each token represents a meaningful element of the language, such as a keyword, identifier, or operator.

### Lexer Class

The `Lexer` class is defined in [`include/lexer.hpp`](include/lexer.hpp) and implemented in [`src/lexer.cpp`](src/lexer.cpp). It includes the following members:
- `std::string input`: The input source code to be tokenized.
- `Lexer(const std::string&)`: Constructor that initializes the lexer with the input source code.
- `std::vector<Token> tokenize()`: Method that performs the tokenization of the input source code.

### Token Structure

The `Token` structure is defined in [`include/lexer.hpp`](include/lexer.hpp). It includes the following members:
- `enum Type`: Enumeration of the different types of tokens (e.g., `KEYWORD`, `IDENTIFIER`, `NUMBER`, `STRING`, `OPERATOR`, `LEFT_PAREN`, `RIGHT_PAREN`, `LEFT_BRACE`, `RIGHT_BRACE`, `SEMICOLON`).
- `std::string value`: The value of the token.

### Tokenization Process

The `tokenize` method in the `Lexer` class uses regular expressions to identify and create tokens from the input source code. The process includes the following steps:
1. **Initialization**: The input source code is stored in `remainingInput`, and an empty vector `tokens` is created to store the tokens.
2. **Regular Expressions**: Various regular expressions are defined to match different types of tokens (e.g., keywords, strings, identifiers, numbers, operators, delimiters, whitespace, comments).
3. **Token Matching**: The method iterates through the `remainingInput`, using the regular expressions to match and create tokens. Matched tokens are added to the `tokens` vector, and the matched portion is removed from `remainingInput`.
4. **Handling Comments and Whitespace**: Comments and whitespace are identified and removed from `remainingInput` without creating tokens.
5. **Error Handling**: If an unexpected input is encountered, an error message is printed, and the tokenization process is terminated.

### Example Usage

An example usage of the lexer is provided in [`test/lexer_test.cpp`](test/lexer_test.cpp). The example reads input source code from the user, tokenizes it using the `Lexer` class, and prints the resulting tokens.

```cpp
#include <iostream>
#include "lexer.hpp"

int main() {
    std::string code;
    std::cout << "Enter code: ";

    std::getline(std::cin, code);

    Lexer lexer(code);
    
    std::vector<Token> tokens = lexer.tokenize();
    
    for (const Token& token : tokens) {
        std::cout << token.type << ": " << token.value << std::endl;
    }

    return 0;
}