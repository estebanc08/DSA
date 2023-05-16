#include "main.hpp"
#include <random>
#include <map>
int main(){
    std::mt19937 rng(std::random_device{}());
    // Generate a random integer between 1 and 100
    std::uniform_real_distribution<float> fl(0.0,1.0);

    std::uniform_int_distribution<int> dist(0,1000);
    mystl::Map<int, std::vector<int>> map;

    for(unsigned int i = 0; i < 10; i++){
        std::vector<int> temp;
        for(unsigned int j = 0; j < 20; j++){
            temp.push_back(dist(rng));
        }
        map[i] = temp;
    }

    for(auto it : map){
        for(int it : it.second)
            std::cout << it << " ";
        std::cout << "\n";
    }
    return 0;
}