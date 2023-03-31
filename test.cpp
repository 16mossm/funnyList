#include <iostream>
#include <chrono>
#define BENCHMARK_N 500
#include "myList.hpp"

int main(){

    gamingList::list<int> a;
    
    //insert item in order and insure they are in order.
    for(int i =0; i < BENCHMARK_N; i++){
        a.append(i);
    }
    bool pass = true;
    for(int i =0; i< a.len();i++){
        if(i != a.get(i)){
            pass = false;
        }
    }
    std::cout << "appending in order: " << pass << std::endl;


    pass = true;
    //remove item 0, last item, and item size/2.
    int removed[] = {-1,-1,-1};
    removed[0] = a.get(0);
    a.remove(0);
    removed[1] = a.get(a.len()-1);
    a.remove(a.len()-1);
    removed[2] = a.get(a.len()/2);
    a.remove(a.len()/2);

    for(int i =0; i< a.len();i++){
        for(int j = 0; j< 3;j++){
            if(a.get(i) == removed[j]){
                pass = false;
            }
        }
    }
    

    
    std::cout << "removing: " << pass << std::endl;

    pass = true;
    a.insert(10,50);
    if(a.get(50) != 10){
        pass = false;
    }
    
    std::cout << "insert: " << pass << std::endl;

}