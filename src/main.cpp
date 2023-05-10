#include "main.hpp"
#include <random>
int main(){
    Queue<int> q;
    for(unsigned int i = 10; i > 0; i--)
        q.push(i);
    std::cout << q.size() << "\n";
    std::cout << q.front() << "\n";
    std::cout << q.back() << "\n";

    BST<int> tree;
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 100);

    for(unsigned int i = 0; i < 150; i++){
        tree.insert(dist(rng));
    }
    tree.printLevelOrder(); 
    
    return 0;
}