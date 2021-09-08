#pragma once

#include "json.h"

#include <memory>
#include <cassert>

using namespace std::string_literals;

namespace json {

class ExpectsValueOrStartDictOfStartArray{

};

class ExpectsKeyOrEndDict {

};

class Builder {
public:
    Builder& Value(Node::Value value) {
        // value == string
        if (const std::string* val = std::get_if<std::string>(&value)) {
            if (nodes_stack_.empty()) {
                root_ = {*val};
                return *this;
            }

            if (nodes_stack_.back()->IsArray()) {
                nodes_stack_.back()->AsArray().emplace_back(*val);
                return *this;
            }

            throw std::logic_error("couldn't put string into an Array"s);

        // // value == Dict
        // } else if (const json::Dict* val = std::get_if<json::Dict>(&value)) {
        //     if (nodes_stack_.empty()) {
        //         root_ = {*val};
        //     } else {
        //         auto ptr = std::make_unique<Node>();
        //         *ptr = *val;
        //         nodes_stack_.push_back(std::move(ptr));
        //     }

        // // value == Array
        // } else if (const json::Array* val = std::get_if<json::Array>(&value)) {
        //     if (nodes_stack_.empty()) {
        //         root_ = {*val};
        //     } else {
        //         auto ptr = std::make_unique<Node>();
        //         *ptr = *val;
        //         nodes_stack_.push_back(std::move(ptr));
        //     
            
        } else {
            throw std::logic_error("Value method didn't accept string, dict, or array ar argument"s);
        }

        return *this;
    }

    Builder& StartArray() {
        auto ptr = std::make_unique<Node>();
        *ptr = json::Array{};
        nodes_stack_.push_back(std::move(ptr));

        return *this;
    }

    Builder& EndArray() {
        if (nodes_stack_.back()->IsArray()) {
            auto array_being_closed = std::move(nodes_stack_.back());
            nodes_stack_.pop_back();

            // if array is root element
            if (nodes_stack_.empty()) {
                root_ = *array_being_closed.release();

                return *this;
            }

            // if array is inside another array
            if (nodes_stack_.back()->IsArray()) {
                nodes_stack_.back()->AsArray().emplace_back(*array_being_closed.release());

                return *this;
            }
        }

        throw std::logic_error("couldn't close array because previous element on stack isn't array"s);
    }

    Node Build() {
        return root_;
    }

private:
    Node root_;
    std::vector<std::unique_ptr<Node>> nodes_stack_;
};

}
