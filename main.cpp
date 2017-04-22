#include <iostream>
#include <string>
#include <algorithm>
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
	skip_list<int>::Iterator i1 = s.begin();
	skip_list<int>::Iterator i2 = s.end();
	while(i1 != i2) {
		int a = *i1;
		std::cout << a << std::endl;
		++i1;
	}
	std::cout << "Done" << std::endl;
	
	std::for_each(s.begin(), s.end(), [](auto e) {
	//	std::cout << e << std::endl;
	});
	//std::cout << skip_list<int>::comp(3,4) << std::endl;
	
	//std::cout << *s.find(1) << "\n";
	s.remove(1);
	std::for_each(s.begin(), s.end(), [](auto e) {
//		std::cout << e << std::endl;
	});
	
	s.pretty_print();
	return 0;
}
