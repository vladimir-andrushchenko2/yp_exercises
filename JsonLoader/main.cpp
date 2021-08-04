// не меняйте файлы json.h и json.cpp
#include "json.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string_view>
#include <vector>

using namespace std;

struct Spending {
    string category;
    int amount;
};

int CalculateTotalSpendings(const vector<Spending>& spendings) {
    int result = 0;
    for (const Spending& s : spendings) {
        result += s.amount;
    }
    return result;
}

string FindMostExpensiveCategory(const vector<Spending>& spendings) {
    auto compare_by_amount = [](const Spending& lhs, const Spending& rhs) {
        return lhs.amount < rhs.amount;
    };
    return max_element(begin(spendings), end(spendings), compare_by_amount)->category;
}

vector<Spending> LoadFromJson(istream& input) {
    const auto document = Load(input);
    const auto root = document.GetRoot();
    const auto map_of_spending = root.AsArray();

    vector<Spending> output;
    for (const auto& spending_info_node : map_of_spending) {
        const auto spending_info = spending_info_node.AsMap();
        output.push_back({spending_info.at("category").AsString(), spending_info.at("amount"s).AsInt()});
    }

    return output;
}

int main() {
    // не меняйте main
    const vector<Spending> spendings = LoadFromJson(cin);
    cout << "Total "sv << CalculateTotalSpendings(spendings) << '\n';
    cout << "Most expensive is "sv << FindMostExpensiveCategory(spendings) << '\n';
}
