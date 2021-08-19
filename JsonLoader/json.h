#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <variant>

namespace json {

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
        return std::get<int>(value_);
    }

    bool IsPureDouble() const {
        return std::holds_alternative<double>(value_);
    }

    bool IsDouble() const {
        return IsInt() || IsPureDouble();
    }

    double AsDouble() const {
        return IsPureDouble() ? std::get<double>(value_) : AsInt();
    }

    bool IsString() const {
        return std::holds_alternative<std::string>(value_);
    }

    std::string AsString() const {
        return std::get<std::string>(value_);
    }

    bool IsBool() const {
        return std::holds_alternative<bool>(value_);
    }

    bool AsBool() const {
        return std::get<bool>(value_);
    }

    bool IsArray() const {
        return std::holds_alternative<Array>(value_);
    }

    Array& AsArray() {
        return std::get<Array>(value_);
    }

    const Array& AsArray() const {
        return std::get<Array>(value_);
    }

    bool IsMap() const {
        return std::holds_alternative<Dict>(value_);
    }

    Dict& AsMap() {
        return std::get<Dict>(value_);
    }
    
    const Dict& AsMap() const {
        return std::get<Dict>(value_);
    }

    NodeValue GetValue() const;

private:
    NodeValue value_;
};

bool operator==(Node left, Node right);

class Document {
public:
    explicit Document(Node root);

    const Node& GetRoot() const;

private:
    Node root_;
};

Document Load(std::istream& input);

void Print(const Document& doc, std::ostream& output);

}  // namespace json
