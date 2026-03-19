#include <iostream>

void doSomething() {
	std::cout << "Hello!\n";
}

int main() {
	int x{0}; //begin lifetime

	doSomething(); //lifetime continues

	return 0;
} //lifetime ends here