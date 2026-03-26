#include <iostream>

// assume int is 4 bytes
int main() {
  unsigned int u{2};
  signed int s{3};

  std::cout << u - s << '\n'; // 2 - 3 = 4294967295

  signed int s2{-1};
  unsigned int u2{1};

  if (s2 < u2) // -1 is implicitly converted to 4294967295, and 4294967295 < 1
               // is false
    std::cout << "-1 is less than 1\n";
  else
    std::cout << "1 is less than -1\n"; // this statement executes

  return 0;
}