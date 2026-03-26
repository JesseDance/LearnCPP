#include <climits> // for CHAR_BIT
#include <iomanip> // for std::setw (which sets the width of the subsequent output)
#include <iostream>

int main() {
  std::cout << "A byte is " << CHAR_BIT << " bits\n\n";

  std::cout << std::left; // left justify output

  std::cout << std::setw(16) << "bool:" << sizeof(bool) << " bytes\n";
  std::cout << std::setw(16) << "char:" << sizeof(char) << " bytes\n";
  std::cout << std::setw(16) << "short:" << sizeof(short) << " bytes\n";
  std::cout << std::setw(16) << "int:" << sizeof(int) << " bytes\n";
  std::cout << std::setw(16) << "long:" << sizeof(long) << " bytes\n";
  std::cout << std::setw(16) << "long long:" << sizeof(long long) << " bytes\n";
  std::cout << std::setw(16) << "float:" << sizeof(float) << " bytes\n";
  std::cout << std::setw(16) << "double:" << sizeof(double) << " bytes\n";
  std::cout << std::setw(16) << "long double:" << sizeof(long double)
            << " bytes\n";

  std::cout << "Enter an int to see how many bytes it takes lol: ";
  int x{};
  std::cout << "x is " << sizeof(x) << " bytes\n";

  return 0;
}