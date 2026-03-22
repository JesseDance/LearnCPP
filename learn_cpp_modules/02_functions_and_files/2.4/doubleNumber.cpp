#include <iostream>

int doubleNumber(int x) {
	return 2 * x;
}


int main() {
	std::cout << "Enter a number: ";

	int input{};
	
	std::cin >> input;

	std::cout << "You entered the number: " << input << '\n';
	std::cout << input << " doubled is " << doubleNumber(input) << '\n';
	
	return 0;
}