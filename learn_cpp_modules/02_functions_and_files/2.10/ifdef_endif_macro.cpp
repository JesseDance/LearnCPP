#include <iostream>

#define PRINT_BEJIMBUS

int main() {

#ifdef PRINT_BEJIMBUS
  std::cout << "BEJIMBUS\n";
#endif

#ifdef PRINT_BEJIMMY
  std::cout << "BEJIMMY";
#endif

  return 0;
}