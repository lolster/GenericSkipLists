#include <iostream>
#include <string>
#include "skip_list.hpp"

int main() {
	skip_list<std::string> s(2);
	s.insert("b");
	s.insert("d");
	s.insert("c");
	s.insert("a");
	s.insert("r");
	s.insert("s");
	s.insert("p");
	s.insert("x");
	s.insert("z");
	
	//std::cout << skip_list<int>::comp(3,4) << std::endl;
	return 0;
}
