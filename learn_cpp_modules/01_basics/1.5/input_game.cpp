#include <iostream>

int main() {
	std::cout << "Enter a number: ";
	int x{}; //value initialization
	std::cin >> x; 
	std::cout << "Value stored: " << x << '\n';

	return 0;
}