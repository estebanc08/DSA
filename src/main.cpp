#include "main.hpp"
#include <random>
#include <set>

int main(){
    std::mt19937 rng(std::random_device{}());
    // Generate a random integer between 1 and 100
    std::uniform_int_distribution<int> dist(0,100000);
    std::vector<int> v;
    RedBlackTree<int> tree;
    for(unsigned int i = 0; i < 100000; i++){
        tree.insert(dist(rng));
    }
    
    for(unsigned int i = 0; i < 1000; i++){
            std::uniform_int_distribution<int> offset(0,tree.size() -1);
            auto it = tree.begin();
            unsigned int toDel = offset(rng);
            for(unsigned int i = 0; i < toDel; i++){
                it++;
            }
            unsigned int val = (*it);
            tree.remove(val);
    }
    return 0;
}