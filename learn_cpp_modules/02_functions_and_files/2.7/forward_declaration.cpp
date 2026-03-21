#include <iostream>

int add(int x, int y);

int main() {
	std::cout << add(6, 7) << '\n';

	return 0;
}

int add(int x, int y) {
	return x + y;
}