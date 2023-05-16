#include "sortingAlgorithms.hpp"
#include <random>

int main(){
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution dist(0.f, 1000.f);
    std::vector<float> vec;
    for(unsigned int i = 0; i < 10; i++){
        float curr = dist(rng);
        vec.push_back(curr);
        std::cout << curr << " ";

    }
    std::cout << "\n\n-----------------------------------------------\n\n";

    SortingAlgorithms<float>::quickSort(vec);

    for(float i : vec){
        std::cout << i << " ";
    }

    std::cout << "\n";

}