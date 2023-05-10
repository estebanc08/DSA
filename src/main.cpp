#include "main.hpp"
#include <random>
int main(){
    Set<int> set;
    std::mt19937 rng(std::random_device{}());

    // Generate a random integer between 1 and 100
    std::uniform_int_distribution<int> dist(1,100);
    set.insert(1);
    set.remove(1);
    if(set.find(1) != set.end())
        std::cout << "found\n";
    else
        std::cout << "Not found\n";
    set.insert(2);
    if(set.find(2) != set.end())
        std::cout << "found\n";
    else
        std::cout << "Not found\n";
    return 0;
}