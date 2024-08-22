#include <map>
#include "logging_allocator.h"
#include "MyContainer.h"
#include <iostream>

constexpr size_t factorial(size_t n){
    return (n < 2) ? 1 : (n * factorial(n-1));
}

int main(int, char **) {
    // map with default allocator
    std::map<int, int> map_std_alloc{};
    for (int i=0; i < 10; i++){
        map_std_alloc[i] = factorial(i);
    }

    // print key-value pairs stored in the map with custom allocator
    for (int i=0; i < 10; i++){
        std::cout << i << " " << map_std_alloc[i] << std::endl;
    }

    // map with custom allocator
    std::map<int, int, std::less<int>, logging_allocator< std::pair<int, int>>> my_map_custom_alloc{};
    for (int i=0; i < 10; i++){
        my_map_custom_alloc[i] = factorial(i);
    }

    // print key-value pairs stored in the map with custom allocator
    for (int i=0; i < 10; i++){
        std::cout << i << " " << my_map_custom_alloc[i] << std::endl;
    }

    // MyContainer with default allocator
    MyContainer<int> my_container_std_alloc{};
    for (int i=0; i < 10; i++){
        my_container_std_alloc.push_back(factorial(i));
    }

    // print value stored in the MyContainer with std allocator
    for (int i=0; i < 10; i++){
        std::cout << i << " " << my_container_std_alloc.at(i) << std::endl;
    }

    // MyContainer with custom allocator
    MyContainer<int, logging_allocator<int> > my_container_custom_alloc{};
    for (int i=0; i < 10; i++){
        my_container_custom_alloc.push_back(factorial(i));
    }

    // print value stored in the MyContainer with custom allocator
    for (int i=0; i < 10; i++){
        std::cout << i << " " << my_container_custom_alloc.at(i) << std::endl;
    }

    return 0;
}
