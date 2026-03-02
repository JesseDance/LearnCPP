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
	int e {}; 		//value-initialization

	return 0;
}