#include <iostream>
#include "linked_list.h"
#include <algorithm>

int main() {
    LinkedList<int> list {21, 42, 63};
    std::cout << "===init 21, 42, 63" << std::endl;
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "===push front 84, 105, 126" << std::endl;
    list.push_front(84);
    list.push_front(105);
    list.push_front(126);
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "===pop front" << std::endl;
    list.pop_front();
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "===find value 63" << std::endl;
    std::cout << *(list.find(63)) << std::endl; 
    std::cout << "===find value 1000" << std::endl;
    if (list.find(1000) != list.end()) {
        std::cout << *(list.find(1000)) << std::endl; 
    } else {
        std::cout << "null" << std::endl;
    }
    return 0;
}