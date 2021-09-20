#pragma once
#include "date.h"

struct DayInfo {
    double earnings = 0.0;
    double spendings = 0.0;
};

class BudgetManager {
public:
    inline static const Date START_DATE{2000, 1, 1};
    inline static const Date END_DATE{2100, 1, 1};

public:
    BudgetManager() { days_.resize(Date::ComputeDistance(START_DATE, END_DATE)); }

    void Earn(Date begin, Date end, double total_earnings) {
        double earnings_per_day = total_earnings / DaysFromFirstToLast(begin, end);

        ForEachDay(begin, end,
                   [earnings_per_day](DayInfo& day) { day.earnings += earnings_per_day; });
    }

    double ComputeIncome(Date begin, Date end) {
        double output{};

        ForEachDay(begin, end, [&output](const DayInfo day) { output += day.earnings - day.spendings; });

        return output;
    }

    void PayTax(Date begin, Date end, int tax_rate) {
        assert(tax_rate <= 100 && tax_rate >= 0);

        double tax_multiplier = 1.0 - (static_cast<double>(tax_rate) / 100.0);

        ForEachDay(begin, end, [tax_multiplier](DayInfo& day) {
            day.earnings *= tax_multiplier;
        });
    }

    void Spend(Date begin, Date end, double spendings) {
        double spendings_per_day = spendings / DaysFromFirstToLast(begin, end);

        ForEachDay(begin, end, [spendings_per_day](DayInfo& day){
            day.spendings += spendings_per_day;
        });
    }

private:
    template <typename Predicate>
    void ForEachDay(Date begin, Date end, Predicate predicate) {
        const int first_day_index = Date::ComputeDistance(START_DATE, begin);
        const int last_day_index = Date::ComputeDistance(START_DATE, end);

        for (int i = first_day_index; i <= last_day_index; ++i) {
            predicate(days_[i]);
        }
    }

    int DaysFromFirstToLast(Date begin, Date end) {
        // +1 to accomodate for the first day
        return Date::ComputeDistance(begin, end) + 1;
    }

private:
    std::vector<DayInfo> days_;
};

