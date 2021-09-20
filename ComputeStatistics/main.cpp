#include <algorithm>
#include <cassert>
#include <optional>
#include <string_view>
#include <utility>
#include <vector>
#include <numeric>

using namespace std;

template <typename InputIt, typename OutSum, typename OutSqSum, typename OutMax>
void ComputeStatistics(InputIt first, InputIt last, OutSum& out_sum, OutSqSum& out_sq_sum,
                       OutMax& out_max) {
    using Elem = std::decay_t<decltype(*first)>;

    constexpr bool need_sum = !is_same_v<OutSum, const nullopt_t>;
    constexpr bool need_sq_sum = !is_same_v<OutSqSum, const nullopt_t>;
    constexpr bool need_max = !is_same_v<OutMax, const nullopt_t>;

    if (first == last) {
        return;
    }

    Elem output_sum = *first;
    Elem output_sq_sum;

    if constexpr (need_sq_sum) {
        output_sq_sum = *first * (*first);
    }

    Elem output_max = *first;

    for (auto it = first + 1; it != last; ++it) {
        if constexpr (need_sum) {
            output_sum += *it;
        }

        if constexpr (need_max) {
            output_max = std::max(*it, output_max);
        }

        if constexpr (need_sq_sum) {
            output_sq_sum += *it * (*it);
        }
    }

    if constexpr (need_sum) {
        out_sum = output_sum;
    }

    if constexpr (need_max) {
        out_max = output_max;
    }

    if constexpr (need_sq_sum) {
        out_sq_sum = output_sq_sum;
    }
}


struct OnlySum {
    int value;
};

OnlySum operator+(OnlySum l, OnlySum r) {
    return {l.value + r.value};
}
OnlySum& operator+=(OnlySum& l, OnlySum r) {
    return l = l + r;
}

int main() {
    vector input = {1, 2, 3, 4, 5, 6};
    int sq_sum;
    std::optional<int> max;

    // Переданы выходные параметры разных типов - std::nullopt_t, int и std::optional<int>
    ComputeStatistics(input.begin(), input.end(), nullopt, sq_sum, max);

    assert(sq_sum == 91 && max && *max == 6);

    vector<OnlySum> only_sum_vector = {{100}, {-100}, {20}};
    OnlySum sum;

    // Поданы значения поддерживающие только суммирование, но запрошена только сумма
    ComputeStatistics(only_sum_vector.begin(), only_sum_vector.end(), sum, nullopt, nullopt);

    assert(sum.value == 20);
}
