#include <iostream>
#include <tuple>
#include <string_view>
#include <vector>

//function returning a tuple (returning multiple variables)
std::tuple<std::string_view, int> getStatus() {
	return {"System Ready", 100};
}

int main() {
	//structured binding C++ 17
	//upack the tuple into var message and code
	auto [message, code] = getStatus();

	//range based for loop with auto C++11/14
	std::vector<int> data = {1,2,3,4,5};

	std::cout << "[" << code "]" << message << "\n";
	std::cout << "Data stream: ";

	for (const auto& val : data) {
		std::cout << val << " ";
	}
	std::cout << "\n";

	return 0;
}