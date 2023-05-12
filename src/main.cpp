#include "main.hpp"
#include <random>
#include <set>

int main(){
    std::mt19937 rng(std::random_device{}());
    // Generate a random integer between 1 and 100
    std::uniform_int_distribution<int> dist(0,1000);
    RedBlackTree<int, std::vector<int>> tree;

    for(unsigned int i = 0; i < 100; i++){
        std::vector<int> temp;
        for(unsigned int j = 0; j < 15; j++){
            temp.push_back(dist(rng));
        }
        std::cout << i << " " << temp.size() << "\n";
        tree.insert(i, temp);
    }

    for(auto it : tree){
        std::cout << it.first << ": ";
        for(unsigned int i = 0; i < it.second.size(); i++){
            std::cout << it.second[i] << " ";
        }
        std::cout << "\n";
    }
    return 0;
}