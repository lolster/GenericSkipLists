#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include "Skip_list.h"

//==================================================
int main () {

    // 1.Initialize an empty Skip_list object
    Skip_list s;

    // 2. insert()
    for (int i = 0; i < 50; ++i){

        std::stringstream ss;
        ss << i;

        s.insert(i, ss.str());
    }

    // 2a. print()
    s.print();

    // 3. find()
    Skip_Node* f = nullptr;
    f = s.find(10);
    if (f) std::cout <<"Node found!\nvalue: "<< f->value <<'\n';
    else std::cout <<"Node NOT found!\n";

    // 4. insert() - reassign
    s.insert(40, "TEST");

    // 4a. print()
    s.print();

    // 5. erase()
    s.erase(40);

    // 5a. print();
    s.print();

    std::cout << "\nDone!\n";
    getchar();   
}
