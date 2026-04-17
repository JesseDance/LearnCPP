#include <format> // C++20
#include <iostream>
#include <print> // C++23

int main() {
  std::cout << std::format(
      "{:b}\n", 0b1010); // C++20, {:b} formats the argument as binary digits
  std::cout << std::format(
      "{:#b}\n",
      0b1010); // C++20, {:#b} formats the argument as 0b-prefixed binary digits

  std::println("{:b} {:#b}", 0b1010,
               0b1010); // C++23, format/print two arguments (same as above) and
                        // a newline

  return 0;
}