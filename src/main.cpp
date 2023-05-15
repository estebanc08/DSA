#include "main.hpp"
#include <random>
#include <set>
#include <map>
int main(){
    std::mt19937 rng(std::random_device{}());
    // Generate a random integer between 1 and 100
    std::uniform_int_distribution<int> dist(0,1000);
    std::uniform_real_distribution<float> fl(0.0,1.0);
    Map<int, float> myMap;
    for(unsigned int i = 0; i < 100; i++){
        myMap[i] = fl(rng) * 1000;
    }
    for(auto it : myMap)
        std::cout << it.first << " " << it.second << "\n";
    myMap[99] = 100001.5f;
    std::cout << myMap[100] << "\n";
    std::cout << myMap.size() << "\n";
    if(myMap.erase(100) != myMap.end())
        std::cout << myMap.size() << "\n";
    std::map<int,int> trial;
    return 0;
}