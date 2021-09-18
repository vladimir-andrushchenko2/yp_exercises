#include "budget_manager.h"

#include <cassert>
#include <iostream>

void TestBudgetManager() {
    using namespace std::string_literals;

    BudgetManager budget_manager_;

    budget_manager_.Earn(Date{2000, 1, 2}, Date{2000, 1, 6}, 20);
    assert(budget_manager_.ComputeIncome(Date{2000, 1, 1}, Date{2001, 1, 1}) == 20);

    budget_manager_.Earn(Date{2099, 12, 31}, Date{2099, 12, 31}, 100);
    assert(budget_manager_.ComputeIncome(Date{2099, 12, 31}, Date{2099, 12, 31}) == 100);

    // PayTax 2000-01-02 2000-01-03
    budget_manager_.PayTax(Date{2000, 1, 2}, Date{2000, 1, 3});
    assert(budget_manager_.ComputeIncome(Date{2000, 1, 1}, Date{2001, 1, 1}) == 18.96);

    std::cout << "Test ok"s << std::endl;
}
