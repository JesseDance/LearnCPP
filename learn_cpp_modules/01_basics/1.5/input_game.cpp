#include <iostream>

int main() {
	std::cout << "Enter a number: ";
	int x{}; //value initialization
	std::cin >> x; 
	std::cout << "Value stored: " << x << '\n';


	std::cout << "Now enter three numbers: ";
	int i{};
	int j{};
	int k{};
	std::cin >> i >> j >> k;
	std::cout << "You entered " << i << ", " << j << ", and "<< k << ".\n";

	return 0;
}