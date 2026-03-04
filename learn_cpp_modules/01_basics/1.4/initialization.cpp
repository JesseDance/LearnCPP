#include <iostream>

int main() {
	
	int width { 5 }; //define and initialize with value 5
	std::cout << width; 

	int a; 			//default-initialization (no initializer)
					//produces garbage value (random/whatever is already there)

	//traditional forms
	int b = 5; 		//copy-initialization
	//Copy-initialization is also used whenever values are implicitly copied, 
	//such as when passing arguments to a function by value, 
	//returning from a function by value, or catching exceptions by value.
	int c ( 6 ); 	//direct-initialization
	//Direct-initialization is also used when values are explicitly cast to another type 
	//(e.g. via static_cast).

	//modern initialization 
	int d { 7 }; 	//direct-list-initialization

	int w1 { 4.5 }; // compile error: list-init does not allow narrowing conversion

	int w2 = 4.5;   // compiles: w2 copy-initialized to value 4
	int w3 (4.5);   // compiles: w3 direct-initialized to value 4


	int e {}; 		//value-initialization / zero-initialization when possible
	// For class types, value-initialization (and default-initialization) 
	// may instead initialize the object to predefined default values, which may be non-zero.

	int x { 0 };    // direct-list-initialization with initial value 0
	std::cout << x; // we're using that 0 value here

	int x {};      // value initialization
	std::cin >> x; // we're immediately replacing that value so an explicit 0 would be meaningless

	int a = 5, b = 6;          // copy-initialization
	int c ( 7 ), d ( 8 );      // direct-initialization
	int e { 9 }, f { 10 };     // direct-list-initialization
	int i {}, j {};            // value-initialization

	return 0;
}