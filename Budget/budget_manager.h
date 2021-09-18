#pragma once
#include "date.h"

struct DayInfo {
    double earnings = 0.0;
};

class BudgetManager {
   public:
    inline static const Date START_DATE{2000, 1, 1};
    inline static const Date END_DATE{2100, 1, 1};

   public:
    BudgetManager() { days_.resize(Date::ComputeDistance(START_DATE, END_DATE)); }

    void Earn(Date begin, Date end, double total_earnings) {
        double earnings_per_day = total_earnings / (Date::ComputeDistance(begin, end) + 1);

        ForEachDay(begin, end,
                   [earnings_per_day](DayInfo& day) { day.earnings += earnings_per_day; });
    }

    double ComputeIncome(Date begin, Date end) {
        double output{};

        ForEachDay(begin, end, [&output](const DayInfo day) { output += day.earnings; });

        return output;
    }

    void PayTax(Date begin, Date end) {
        ForEachDay(begin, end, [](DayInfo& day) {
            constexpr double kTaxMultiplier = 0.87;

            day.earnings *= kTaxMultiplier;
        });
    }

    template <typename Predicate>
    void ForEachDay(Date begin, Date end, Predicate predicate) {
        const int first_day_index = Date::ComputeDistance(START_DATE, begin);
        const int last_day_index = Date::ComputeDistance(START_DATE, end);

        for (int i = first_day_index; i <= last_day_index; ++i) {
            predicate(days_[i]);
        }
    }

   private:
    std::vector<DayInfo> days_;
};

