#include <iostream>
#include <string>

int main() {
  std::cout << "Enter your full name: ";
  std::string name{};
  std::cin >>
      name; // this won't work as expected since std::cin breaks on whitespace

  std::cout << "Enter your favorite color: ";
  std::string color{};
  std::cin >> color;

  std::cout << "Your name is " << name << " and your favorite color is "
            << color << '\n';

  return 0;
}