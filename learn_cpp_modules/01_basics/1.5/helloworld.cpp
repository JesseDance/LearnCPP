#include <iostream> //for std::cout

int main() {
	std::cout << "Hello world!\n";

	std::cout << 4 << std::endl;

	int width{5}; //direct list initialization
	std::cout << width << std::endl;

	// std::endl moves to next line and also flushes buffer
	// \n is only a newline, does not flush buffer (better perf when flush is not necessary)

	std::cout << "Enter two numbers: ";

	int x{}; //value initialization
	std::cin >> x;

	int y{}; //value initialization
	std::cin >> y;

	std::cout << "You entered " << x << " and " << y << '\n';
	return 0;
}