#include "json_builder.h"
#include <iostream>


using namespace std;

int main() {
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
            .StartDict()
                .Key("Hello world"s).Value("You are beautifull"s)
                .Key("Array")
                    .StartArray()
                        .Value("Oh").Value("My")
                    .EndArray()
            .EndDict()
            .Build()
        },
        std::cout
    );
    std::cout << endl;
}
