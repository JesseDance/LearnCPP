#include <iostream>

//Definition of user-defined function doPrint()
//doPrint() is the callled function in this example
void doPrint() {
	std::cout << "In doPrint()\n";
}

//Definition of user-defined function main()
int main() {
	std::cout << "Starting main()\n";
	doPrint(); //interupt main() by making a function call
				//to doPrint

	std::cout << "Main exiting...\n";
	return 0;
}