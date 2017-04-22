/* 
	Authors
	* Anush S. Kumar (01FB14ECS037)
	* Sushrith Arkal (01FB14ECS262)
	* Tejas S Ksetty (01FB14ECS267)
*/

#include <iostream>
#include <string>
#include <algorithm>
#include "skip_list.hpp"

int main() {
	skip_list<std::string> s(10);
	s.insert("c");
	s.insert("a");
	s.insert("d");
	s.insert("b");
	s.insert("f");
	s.insert("e");
	//s.pretty_print();
	//skip_list<std::string>::Iterator i1 = s.begin();
	//skip_list<int>::Iterator i2 = s.end();
	//while(i1 != i2) {
	//	int a = *i1;
	//	std::cout << a << std::endl;
	//	++i1;
	//}
	//std::cout << "Done" << std::endl;
	
	//std::for_each(s.begin(), s.end(), [](auto e) {
	//	std::cout << e << std::endl;
	//});
	//std::cout << skip_list<int>::comp(3,4) << std::endl;
	
	//std::cout << *s.find(1) << "\n";
	//s.remove(1);
	//std::for_each(s.begin(), s.end(), [](auto e) {
//		std::cout << e << std::endl;
	//s});
	
	s.pretty_print();
	return 0;
}
