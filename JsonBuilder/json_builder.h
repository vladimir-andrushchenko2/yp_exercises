#pragma once

#include <cassert>
#include <memory>

#include "json.h"

using namespace std::string_literals;

namespace json {

class ExpectsValueOrStartDictOfStartArray {};

class ExpectsKeyOrEndDict {};

class Builder {
   public:
    Builder& Value(Node::Value value) {
        // Get node using value
        std::unique_ptr<Node> ptr;
        visit([&ptr](auto&& val) { ptr = std::make_unique<Node>(val); }, value);

        // For empty
        if (nodes_stack_.empty()) {
            root_ = *ptr.release();
            return *this;
        }

        // For Array
        if (nodes_stack_.back()->IsArray()) {
            nodes_stack_.back()->AsArray().emplace_back(*ptr.release());
            return *this;
        }

        // For Key
        if (nodes_stack_.back()->IsString()) {
            std::string key = nodes_stack_.back().release()->AsString();
            nodes_stack_.pop_back();
            nodes_stack_.back()->AsDict().emplace(key, *ptr.release());

            return *this;
        }

        throw std::logic_error("value couldn't be inserted"s);
    }

    // Array
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
                nodes_stack_.back()->AsArray().push_back(*array_being_closed.release());

                return *this;
            }

            // if array is value in another array
            if (nodes_stack_.back()->IsString()) {
                std::string key = nodes_stack_.back().release()->AsString();
                nodes_stack_.pop_back();
                nodes_stack_.back()->AsDict().emplace(key, *array_being_closed.release());

                return *this;
            }
        }

        throw std::logic_error("couldn't close array"s);
    }

    // Dict
    Builder& StartDict() {
        auto ptr = std::make_unique<Node>();
        *ptr = json::Dict{};
        nodes_stack_.push_back(std::move(ptr));

        return *this;
    }

    Builder& EndDict() {
        if (nodes_stack_.back()->IsDict()) {
            auto dict_being_closed = std::move(nodes_stack_.back());
            nodes_stack_.pop_back();

            if (nodes_stack_.empty()) {
                root_ = *dict_being_closed.release();

                return *this;
            }

            // dict element of array
            if (nodes_stack_.back()->IsArray()) {
                nodes_stack_.back()->AsArray().push_back(
                    *dict_being_closed.release());  // mb emplace_back

                return *this;
            }

            // dict is value in another dict
            if (nodes_stack_.back()->IsString()) {
                std::string key = nodes_stack_.back().release()->AsString();
                nodes_stack_.pop_back();
                nodes_stack_.back()->AsDict().emplace(key, *dict_being_closed.release());

                return *this;
            }
        }

        throw std::logic_error("couldn't close dict"s);
    }

    Builder& Key(std::string key) {
        if (nodes_stack_.back()->IsDict()) {
            auto ptr = std::make_unique<Node>();
            *ptr = std::move(key);
            nodes_stack_.push_back(std::move(ptr));

            return *this;
        }

        throw std::logic_error("couldn't insert key"s);
    }

    Node Build() { return root_; }

   private:
    Node root_;
    std::vector<std::unique_ptr<Node>> nodes_stack_;
};

}  // namespace json
