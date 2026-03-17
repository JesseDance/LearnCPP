#include <iostream>

int getValueFromUserUB() {
	std::cout << "Enter an integer: ";
	int input {};
	std::cin >> input;

	//no return
}

int main() {
	int num { getValueFromUserUB() };

	std::cout << num << "doubled is: " << num * 2 << '\n';

	// Enter an integer: 4
	// Illegal instruction        (core dumped) ./bejimbus

	return 0;
}