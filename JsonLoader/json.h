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
    explicit Node();
    explicit Node(const nullptr_t&);
    explicit Node(Array array);
    explicit Node(Dict map);
    explicit Node(bool value);
    explicit Node(int value);
    explicit Node(double value);
    explicit Node(std::string value);

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
