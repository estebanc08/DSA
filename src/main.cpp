#include "main.hpp"

int main(){
    BST<int> tree;
    std::string input = "";
    tree.insert(5);
    tree.insert(3);
    tree.insert(1);
    tree.insert(4);
    tree.insert(9);
    tree.insert(8);
    tree.insert(10);
    tree.insert(13);
    tree.insert(11);
    tree.insert(12);
    tree.insert(14);

    tree.printLevelOrder();
    std::cout << tree.size() << "\n";

    tree.remove(5);
    tree.remove(4);

    std::cout << tree.size() << "\n";

    tree.clear();
    if(tree.empty())
        std::cout << "empty\n";
    else
        std::cout << "failed\n";
    
    tree.insert(100);

    if(tree.empty())
        std::cout << "failed\n";
    else
        std::cout << "not empty\n";
    
    return 0;
}