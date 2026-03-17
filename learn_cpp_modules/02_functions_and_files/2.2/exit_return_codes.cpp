#include <iostream>
#include <cstdlib> //for EXIT_SUCCESS and EXIT_FAILURE

int main() {
	std::cout << "Type 1 now and then press enter: ";
	int input {};

	std::cin >> input;

	if (input == 1) {
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}