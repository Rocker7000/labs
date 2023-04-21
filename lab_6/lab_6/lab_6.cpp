#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

enum TokenType {
    IDENTIFIER,
    HEX_NUMBER,
    ASSIGNMENT,
    OR_OPERATOR,
    XOR_OPERATOR,
    AND_OPERATOR,
    NOT_OPERATOR,
    LEFT_PAREN,
    RIGHT_PAREN,
    SEMICOLON,
    INVALID
};

struct Token {
    TokenType type;
    string value;
};

bool is_hex_digit(char c) {
    return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

bool is_valid_identifier_char(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

Token get_next_token(string& input, size_t& pos) {
    while (pos < input.size() && input[pos] == ' ') {
        pos++;
    }

    if (pos == input.size()) {
        return { SEMICOLON, "" };
    }

    if (is_valid_identifier_char(input[pos])) {
        string identifier = "";
        while (pos < input.size() && is_valid_identifier_char(input[pos])) {
            identifier += input[pos];
            pos++;
        }
        return { IDENTIFIER, identifier };
    }

    if (input[pos] == '0' && pos + 1 < input.size() && input[pos + 1] == 'x') {
        pos += 2;
        string hex_num = "";
        while (pos < input.size() && is_hex_digit(input[pos])) {
            hex_num += input[pos];
            pos++;
        }
        return { HEX_NUMBER, hex_num };
    }

    if (input[pos] == ':' && pos + 1 < input.size() && input[pos + 1] == '=') {
        pos += 2;
        return { ASSIGNMENT, ":=" };
    }

    if (input[pos] == '|') {
        pos++;
        if (pos < input.size() && input[pos] == '|') {
            pos++;
            return { OR_OPERATOR, "||" };
        }
        return { INVALID, "" };
    }

    if (input[pos] == '^') {
        pos++;
        return { XOR_OPERATOR, "^" };
    }

    if (input[pos] == '&') {
        pos++;
        if (pos < input.size() && input[pos] == '&') {
            pos++;
            return { AND_OPERATOR, "&&" };
        }
        return { INVALID, "" };
    }

    if (input[pos] == '!') {
        pos++;
        return { NOT_OPERATOR, "!" };
    }

    if (input[pos] == '(') {
        pos++;
        return { LEFT_PAREN, "(" };
    }

    if (input[pos] == ')') {
        pos++;
        return { RIGHT_PAREN, ")" };
    }

    if (input[pos] == ';') {
        pos++;
        return { SEMICOLON, ";" };
    }

    return { INVALID, "" };
}

void print_token(Token token) {
    unordered_map<TokenType, string> type_to_str = {
        { IDENTIFIER, "Identifier" },
        { HEX_NUMBER, "Hex Number" },
        { ASSIGNMENT, "Assignment" },
        { OR_OPERATOR, "Or Operator"},
        { XOR_OPERATOR, "Xor Operator" },
        { AND_OPERATOR, "And Operator" },
        { NOT_OPERATOR, "Not Operator" },
        { LEFT_PAREN, "Left Parenthesis" },
        { RIGHT_PAREN, "Right Parenthesis" },
        { SEMICOLON, "Semicolon" },
        { INVALID, "Invalid" }
    };

    cout << type_to_str[token.type] << " - " << token.value << endl;
}

int main() {
    ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        cerr << "Error opening file: " << endl;
        return 1;
    }

    string input((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());
    input_file.close();

    vector<Token> tokens;
    size_t pos = 0;
    while (pos < input.size()) {
        Token token = get_next_token(input, pos);
        if (token.type != INVALID) {
            tokens.push_back(token);
        }
        else {
            cerr << "Invalid token found at position " << pos << endl;
            return 1;
        }
    }

    for (Token token : tokens) {
        print_token(token);
    }

    return 0;
}