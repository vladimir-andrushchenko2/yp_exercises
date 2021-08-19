#include "json.h"

#include <cassert>
#include <iterator>

using namespace std;

namespace json {

namespace {

Node LoadNode(istream& input);

Node LoadArray(istream& input) {
    Array result;

    for (char c; input >> c && c != ']';) {
        if (c != ',') {
            input.putback(c);
        }
        result.push_back(LoadNode(input));
    }

    return Node(move(result));
}

Node LoadNumber(std::istream& input) {
    using namespace std::literals;

    std::string parsed_num;

    // Считывает в parsed_num очередной символ из input
    auto read_char = [&parsed_num, &input] {
        parsed_num += static_cast<char>(input.get());
        if (!input) {
            throw ParsingError("Failed to read number from stream"s);
        }
    };

    // Считывает одну или более цифр в parsed_num из input
    auto read_digits = [&input, read_char] {
        if (!std::isdigit(input.peek())) {
            throw ParsingError("A digit is expected"s);
        }
        while (std::isdigit(input.peek())) {
            read_char();
        }
    };

    if (input.peek() == '-') {
        read_char();
    }
    // Парсим целую часть числа
    if (input.peek() == '0') {
        read_char();
        // После 0 в JSON не могут идти другие цифры
    } else {
        read_digits();
    }

    bool is_int = true;
    // Парсим дробную часть числа
    if (input.peek() == '.') {
        read_char();
        read_digits();
        is_int = false;
    }

    // Парсим экспоненциальную часть числа
    if (int ch = input.peek(); ch == 'e' || ch == 'E') {
        read_char();
        if (ch = input.peek(); ch == '+' || ch == '-') {
            read_char();
        }
        read_digits();
        is_int = false;
    }

    try {
        if (is_int) {
            // Сначала пробуем преобразовать строку в int
            try {
                return Node(std::stoi(parsed_num));
            } catch (...) {
                // В случае неудачи, например, при переполнении
                // код ниже попробует преобразовать строку в double
            }
        }
        return Node(std::stod(parsed_num));
    } catch (...) {
        throw ParsingError("Failed to convert "s + parsed_num + " to number"s);
    }
}

// Node LoadInt(istream& input) {
//    int result = 0;
//    while (isdigit(input.peek())) {
//        result *= 10;
//        result += input.get() - '0';
//    }
//    return Node(result);
//}

// this only mb works correctly
Node LoadString(istream& input) {
    std::string output;
    char symbol;
    while (input.get(symbol)) {
        if (symbol == '"') {
            return Node(output);
        }

        if (symbol != '\\') {
            output += symbol;
        } else {
            char escaped_symbol;
            input.get(escaped_symbol);
            if (escaped_symbol == 'n') {
                output += '\n';
            } else if (escaped_symbol == 'r') {
                output += '\r';
            } else if (escaped_symbol == '"') {
                output += '"';
            } else if (escaped_symbol == 't') {
                output += 't';
            } else if (escaped_symbol == '\\') {
                output += '\\';
            // mb next condition will prove buggy
            } else if (symbol == '\n' || symbol == '\r') {
                throw ParsingError("Unexpected end of line"s);
            }
        }
    }

    assert(false && "reached end of input without reading string successfully");
}

Node LoadDict(istream& input) {
    Dict dict;

    for (char c; input >> c && c != '}';) {
        if (c == '"') {
            std::string key = LoadString(input).AsString();
            if (input >> c && c == ':') {
                if (dict.find(key) != dict.end()) {
                    throw ParsingError("Duplicate key '"s + key + "' have been found");
                }
                dict.emplace(move(key), LoadNode(input));
            }
            else {
                throw ParsingError(": is expected but '"s + c + "' has been found"s);
            }
        } else if (c != ',') {
            throw ParsingError(R"(',' is expected but ')"s + c + "' has been found"s);
        }
    }
    if (!input) {
        throw ParsingError("Dictionary parsing error"s);
    }
    return Node(move(dict));
}

std::string ReadAlphabetic(istream& input) {
    std::string s;
    while (std::isalpha(input.peek())) {
        s.push_back(static_cast<char>(input.get()));
    }
    return s;
}

Node LoadBool(istream& input) {
    const std::string s = ReadAlphabetic(input);
    if (s == "true"sv) {
        return Node{true};
    } else if (s == "false"sv) {
        return Node{false};
    } else {
        throw ParsingError("Failed to parse '"s + s + "' as bool"s);
    }
}

Node LoadNull(istream& input) {
    const std::string word = ReadAlphabetic(input);
    if (word == "null"s) {
        return Node();
    }
    throw ParsingError("Tried to parse " + word + " as null");
}

Node LoadNode(istream& input) {
    char c;
    input >> c;

    if (c == '[') {
        return LoadArray(input);
    } else if (c == '{') {
        return LoadDict(input);
    } else if (c == '"') {
        return LoadString(input);
    } else if (c == 'f' || c == 't') {
        input.putback(c);
        return LoadBool(input);
    } else if (c == 'n') {
        input.putback(c);
        return LoadNull(input);
    } else {
        input.putback(c);
        return LoadNumber(input);
    }
}

}  // namespace

Node::Node() : value_(nullptr) {}

Node::Node(const nullptr_t&) : value_(nullptr) {}

Node::Node(Array array) : value_(move(array)) {}

Node::Node(Dict map) : value_(move(map)) {}

Node::Node(bool value) : value_(value) {}

Node::Node(int value) : value_(value) {}

Node::Node(double value) : value_(value) {}

Node::Node(string value) : value_(move(value)) {}

NodeValue Node::GetValue() const { return value_; }

bool operator==(Node left, Node right) { return left.GetValue() == right.GetValue(); }

Document::Document(Node root) : root_(move(root)) {}

const Node& Document::GetRoot() const { return root_; }

Document Load(istream& input) { return Document{LoadNode(input)}; }

struct OstreamNodeValuePrinter {
    ostream& out;

    void operator()(const std::nullptr_t&) const { out << "null"s; }

    void operator()(Dict dict) const {
        out << '{';
        for (auto it = dict.begin(); it != dict.end(); ++it) {
            const auto& [key, value] = *it;
            out << '"' << key << '"' << ':';
            std::visit(OstreamNodeValuePrinter{out}, value.GetValue());
            if (std::next(it) != dict.end()) {
                out << ',';
            }
        }
        out << '}';
    }

    void operator()(Array array) const {
        out << '[';
        for (auto it = array.begin(); it != array.end(); ++it) {
            Node node = *it;
            std::visit(OstreamNodeValuePrinter{out}, node.GetValue());
            if (std::next(it) != array.end()) {
                out << ',';
            }
        }
        out << ']';
    }

    void operator()(bool value) const {
        std::string output = value ? "true"s : "false"s;
        out << output;
    }

    void operator()(int number) const { out << number; }

    void operator()(double number) const { out << number; }

    void operator()(std::string str) const {
        out << '"';
        for (const char c : str) {
            switch (c) {
                case '\r':
                    out << "\\r"sv;
                    break;
                case '\n':
                    out << "\\n"sv;
                    break;
                case '"':
                    [[fallthrough]];
                case '\\':
                    out.put('\\');
                    [[fallthrough]];
                default:
                    out.put(c);
                    break;
            }
        }
        out << '"';
    }
};

void Print(const Document& doc, std::ostream& output) {
    auto value = doc.GetRoot().GetValue();
    std::visit(OstreamNodeValuePrinter{output}, value);
}

}  // namespace json
