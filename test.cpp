#include <iostream>
#include <chrono>
#define BENCHMARK_N 50000
#include "myList.hpp"

int main(){

    gamingList::list<int> a;
    
    for(int i = 0; i< 100;i++){
        a.append(i);

    }

    /*
    for(int i = 0; i<a.len(); i++){
        std::cout << a.get(i) << std::endl;
    }

    std::cout << a.get(60) << std::endl;
    */

    a.insert(99999,50);
    a.insert(99999,0);
    //a.insert(99999,a.len());
    for(int i = 0; i<a.len(); i++){
        std::cout << a.get(i) << std::endl;
    }

}