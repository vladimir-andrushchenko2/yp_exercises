#include "json_builder.h"
#include <iostream>


using namespace std;

int main() {
    try {
        json::Print(
            json::Document{
                json::Builder{}.Build()
            },
            cout
        );
        cout << endl;
    } catch (std::logic_error& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        json::Print(
            json::Document{
                json::Builder{}.StartArray().Value("lol"s).Build()
            },
            cout
        );
        cout << endl;
    } catch (std::logic_error& e) {
        std::cout << e.what() << std::endl;
    }



    json::Print(
        json::Document{
            json::Builder{}
            .StartDict()
                .Key("key1"s).Value(123)
                .Key("key2"s).Value("value2"s)
                .Key("key3"s).StartArray()
                    .Value(456)
                    .StartDict().EndDict()
                    .StartDict()
                        .Key(""s)
                        .Value(nullptr)
                    .EndDict()
                    .Value(""s)
                .EndArray()
            .EndDict()
            .Build()
        },
        cout
    );
    cout << endl;

    json::Print(
        json::Document{
            json::Builder{}
                .StartArray()
                .Value("Hello"s)
                    .StartArray()
                    .Value("World"s)
                    .EndArray()
                .EndArray()
            .Build()
        },
        std::cout
    );
    std::cout << std::endl;

    json::Print(
        json::Document{
            json::Builder{}
            .StartDict().Key("hello world"s).Value("rise and shine"s).EndDict()
            .Build()
        },
        std::cout
    );
    std::cout << endl;
}
