#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <variant>

namespace json {

using namespace std::literals;

class Node;
using Dict = std::map<std::string, Node>;
using Array = std::vector<Node>;

using NodeValue = std::variant<std::nullptr_t, Array, Dict, bool, int, double, std::string>;

// Эта ошибка должна выбрасываться при ошибках парсинга JSON
class ParsingError : public std::runtime_error {
public:
    using runtime_error::runtime_error;
};

class Node {
public:
    Node();
    Node(const nullptr_t&);
    Node(Array array);
    Node(Dict map);
    Node(bool value);
    Node(int value);
    Node(double value);
    Node(std::string value);

    bool IsNull() const {
        return std::holds_alternative<nullptr_t>(value_);
    }

    bool IsInt() const {
        return std::holds_alternative<int>(value_);
    }

    int AsInt() const {
        if (!IsInt()) {
            throw std::logic_error("Not an int"s);
        }
        return std::get<int>(value_);
    }

    bool IsPureDouble() const {
        return std::holds_alternative<double>(value_);
    }

    bool IsDouble() const {
        return IsInt() || IsPureDouble();
    }

    double AsDouble() const {
        if (!IsDouble()) {
            throw std::logic_error("Not a double"s);
        }
        return IsPureDouble() ? std::get<double>(value_) : AsInt();
    }

    bool IsString() const {
        return std::holds_alternative<std::string>(value_);
    }

    std::string AsString() const {
        if (!IsString()) {
            throw std::logic_error("Not a string"s);
        }
        return std::get<std::string>(value_);
    }

    bool IsBool() const {
        return std::holds_alternative<bool>(value_);
    }

    bool AsBool() const {
        if (!IsBool()) {
            throw std::logic_error("Not a bool"s);
        }
        return std::get<bool>(value_);
    }

    bool IsArray() const {
        return std::holds_alternative<Array>(value_);
    }

    Array& AsArray() {
        if (!IsArray()) {
            throw std::logic_error("Not a map"s);
        }
        return std::get<Array>(value_);
    }

    const Array& AsArray() const {
        if (!IsArray()) {
            throw std::logic_error("Not a map"s);
        }
        return std::get<Array>(value_);
    }

    bool IsMap() const {
        return std::holds_alternative<Dict>(value_);
    }

    Dict& AsMap() {
        if (!IsMap()) {
            throw std::logic_error("Not a map"s);
        }
        return std::get<Dict>(value_);
    }
    
    const Dict& AsMap() const {
        if (!IsMap()) {
            throw std::logic_error("Not a map"s);
        }
        return std::get<Dict>(value_);
    }

    NodeValue GetValue() const;

private:
    NodeValue value_;
};

bool operator==(Node left, Node right);

bool operator!=(Node left, Node right);

class Document {
public:
    explicit Document(Node root);

    const Node& GetRoot() const;

private:
    Node root_;
};

bool operator==(const Document& lhs, const Document& rhs);
bool operator!=(const Document& lhs, const Document& rhs);

Document Load(std::istream& input);

void Print(const Document& doc, std::ostream& output);

}  // namespace json
