#include "main.hpp"
#include <random>

int main(){
    std::mt19937 rng(std::random_device{}());
    // Generate a random integer between 1 and 100
    std::uniform_int_distribution<int> dist(0,1000);
    std::uniform_real_distribution<float> fl(0.0,1.0);
    Trie trie;
    trie.insert("word");
    trie.insert("worm");
    trie.insert("worms");
    trie.insert("wormSSSS");

    // if(trie.search("word"))
    //     std::cout << "found\n";
    // else
    //     std::cout << "not Found\n";
    
    // if(trie.search("worm"))
    //     std::cout << "found\n";
    // else
    //     std::cout << "not Found\n";
    
    // if(trie.search("worms"))
    //     std::cout << "found\n";
    // else
    //     std::cout << "not Found\n";
    
    // if(trie.search("wor"))
    //     std::cout << "found\n";
    // else
    //     std::cout << "not Found\n";
    
    // std::cout << trie.size() << "\n";

    std::vector<std::string> temp = trie.startsWith("wo");
    for(std::string curr : temp)
        std::cout << curr << " ";
    std::cout << "\n";
    return 0;
}