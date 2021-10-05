#include <cstdint>
#include <limits>
#include <iostream>

bool CheckSumOverflow(int64_t first, int64_t second) {
  bool fir_neg = first > 0;
  bool sec_neg = second > 0;
  bool all_positive = fir_neg && sec_neg;
  bool all_negative = !fir_neg && !sec_neg;
  if (all_positive || all_negative) {
    if (all_positive) {
//      std::cerr << "all positive" << std::endl;
      uint64_t int_max = std::numeric_limits<int64_t>::max();
      uint64_t sum = static_cast<uint64_t>(first) + static_cast<uint64_t>(second);
      return sum <= int_max;
    }
    if (all_negative) {
//      std::cerr << "all negative" << std::endl;
      uint64_t int_min = std::abs(std::numeric_limits<int64_t>::min());
      uint64_t sum = static_cast<uint64_t>(std::abs(first)) + static_cast<uint64_t>(std::abs(second));
      return sum <= int_min;
    }

      return false;
  }
  else {
//    std::cerr << "different sign" << std::endl;
    return true;
  }
}

int main() {
  int64_t first, second;
  std::cin >> first >> second;
  if (!CheckSumOverflow(first, second)) {
    std::cout << "Overflow!" << std::endl;
  }
  else {
    std::cout << first + second << std::endl;
  }
}
