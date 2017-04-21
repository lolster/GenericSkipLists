#include <iostream>
#include <string>
#include "skip_list.hpp"

int main() {
	skip_list<int> s(3);
	s.insert(1);
	s.insert(4);
	s.insert(8);
	s.insert(9);
	s.insert(7);
	s.insert(6);
	s.pretty_print();
	
	//std::cout << skip_list<int>::comp(3,4) << std::endl;
	return 0;
}
