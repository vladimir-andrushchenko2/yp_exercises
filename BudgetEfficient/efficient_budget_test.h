#include <iostream>
#include <sstream>

#include "parser.h"

using namespace std;

void ParseAndProcessQuery(BudgetManager& manager, string_view line) {
    auto query = ParseQuery(line);

    if (!query) {
        return;
    }

    query->ProcessAndPrint(manager, cout);
}

int ReadNumberOnLine(istream& input) {
    std::string line;
    std::getline(input, line);
    return std::stoi(line);
}

const string test = R"d(5
Earn 2000-01-02 2000-01-06 100
ComputeIncome 2000-01-01 2001-01-01
PayTax 2000-01-02 2000-01-06 25
Spend 2000-01-02 2000-01-06 25
ComputeIncome 2000-01-01 2001-01-01
)d";

istringstream test_input{test};

void RunBudgetTests() {
    BudgetManager manager;

    const int query_count = ReadNumberOnLine(test_input);

    for (int i = 0; i < query_count; ++i) {
        std::string line;
        std::getline(test_input, line);
        ParseAndProcessQuery(manager, line);
    }


    std::cout << "Test ok" << std::endl;
}
