#include "budget_manager.h"
//#include "test_budget_manager.h"

#include <iostream>
#include <string_view>
#include <iomanip>
#include <charconv>

using namespace std;

std::vector<std::string_view> Split(std::string_view text, char delim) {
    std::vector<std::string_view> result;

    while (true) {
        size_t space = text.find(delim);

        result.push_back(text.substr(0, space));

        if (space == text.npos) {
            break;
        } else {
            text.remove_prefix(space + 1);
        }
    }

    return result;
}

int StringViewToInt(std::string_view text) {
    int result{};

    auto [ptr, ec] { std::from_chars(text.data(), text.data() + text.size(), result) };

    if (ec == std::errc())
    {
        //        std::cout << "Result: " << result << ", ptr -> " << std::quoted(ptr) << '\n';
        //        throw std::logic_error("couldn't parse int"s);
    }
    else if (ec == std::errc::invalid_argument)
    {
        std::cout << text << " <- "s;
        std::cout << "That isn't a number.\n";
        throw std::logic_error("couldn't parse int"s);
    }
    else if (ec == std::errc::result_out_of_range)
    {
        std::cout << text << " <- "s;
        std::cout << "This number is larger than an int.\n";
        throw std::logic_error("couldn't parse int"s);
    }

    return result;
}

double StringViewToDouble(std::string_view text) {
    return stod(static_cast<std::string>(text));
}

Date ParseDateFromString(std::string_view text) {
    auto date_month_day = Split(text, '-');

    int date = StringViewToInt(date_month_day.at(0));
    int month = StringViewToInt(date_month_day.at(1));
    int day = StringViewToInt(date_month_day.at(2));

    return Date{date, month, day};
}

void ParseAndProcessQuery(BudgetManager& manager, string_view line) {
    auto command = Split(line, ' ');

    Date begin = ParseDateFromString(command.at(1));
    Date end = ParseDateFromString(command.at(2));

    if (command.at(0) == "Earn"sv) {
        int earnings = StringViewToDouble(command.at(3));

        manager.Earn(begin, end, earnings);

    } else if (command.at(0) == "ComputeIncome"sv) {
        std::cout << manager.ComputeIncome(begin, end) << std::endl;

    } else if (command.at(0) == "PayTax"sv) {
        int tax_rate = StringViewToInt(command.at(3));

        manager.PayTax(begin, end, tax_rate);

    } else if (command.at(0) == "Spend"sv) {
        double spendings = StringViewToDouble(command.at(3));

        manager.Spend(begin, end, spendings);
    } else {
        assert(false);
    }
}

int ReadNumberOnLine(istream& input) {
    std::string line;
    std::getline(input, line);
    return std::stoi(line);
}

int main() {
    //    TestBudgetManager();

    BudgetManager manager;

    const int query_count = ReadNumberOnLine(cin);

    for (int i = 0; i < query_count; ++i) {
        std::string line;
        std::getline(cin, line);
        ParseAndProcessQuery(manager, line);
    }
}
