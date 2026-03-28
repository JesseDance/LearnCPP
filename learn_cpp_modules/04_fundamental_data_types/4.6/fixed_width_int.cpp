#include <iostream>
#include <cstdint>

int main() {
	std::int32_t x { 32767 };
	x = x + 1;
	std::cout << x << '\n';

	return 0;
}