#include <iostream>
#include <string>

int main() {
	int x;

	std::cout << x << '\n';

	//prints the number of bytes that an int takes
	std::cout << "Size of int: " << sizeof(int) << '\n';
	std::cout << "Size of float: " << sizeof(float) << '\n';
	std::cout << "Size of char: " << sizeof(char) << '\n';
	std::cout << "Size of long: " << sizeof(long) << '\n';

	std::string word = "bejimbus";

	std::cout << "Size of string with 8 characters: " 
			  << sizeof(std::string) 
			  << '\n';

	return 0;
}