#ifndef SORTING_ALGORITHMS
#define SORTING_ALGORITHMS

#include <vector>
#include <iostream>
#include "../DS/heap.hpp"

/// @brief Class with several sorting algorithms
/// @tparam T Type of vector to sort
template <typename T>
class SortingAlgorithms{
    public:

        /// @brief Performs bubble sort with O(N^2) time
        static inline void bubbleSort(std::vector<T>& vec);

        /// @brief Performs insertion sort with O(N^2) time
        static inline void insertionSort(std::vector<T>& vec);

        /// @brief Performs Selection Sort with O(N^2) time
        static inline void selectionSort(std::vector<T>& vec);

        /// @brief Performs merge sort with O(N*Log(N)) time
        static inline void mergeSort(std::vector<T>& vec);

        /// @brief 
        /// @param vec 
        static inline void quickSort(std::vector<T>& vec);

        /// @brief Uses Max heap with O(N*Log(N)) time
        static inline void heapSort(std::vector<T>& vec);

    private:

        /// @brief Helper function for merge sort
        /// @param vec Reference to original vector 
        /// @param begin Begin index
        /// @param end End index
        static void mergeHelper(std::vector<T>& vec, int begin, int end);

        static void quickSortHelper(std::vector<T>&, int low, int high);

        static int partition(std::vector<T>& vec, int low, int high);
};  

template <typename T>
void SortingAlgorithms<T>::bubbleSort(std::vector<T>& vec){
    bool flag;
    for(unsigned int i = 0; i < vec.size()-1; i++){
        flag = false;
        for(unsigned int j = 0; j < vec.size()-i-1; j++){
            if (vec[j] > vec[j + 1]) {
                flag = true;
                std::swap(vec[j], vec[j + 1]);
            }
        }
        if(!flag) //optimize if no swaps, break
            break;
    }
}

template <typename T>
void SortingAlgorithms<T>::insertionSort(std::vector<T>& vec){
    for(unsigned int i = 1; i < vec.size(); i++){
        unsigned int j = i;
        while(j > 0 && vec[j-1] > vec[j]){
            std::swap(vec[j], vec[j-1]);
            j--;
        }
    }
}

template <typename T>
void SortingAlgorithms<T>::selectionSort(std::vector<T>& vec){
    for(unsigned int i = 0; i < vec.size(); i++){
        T currMin = vec[i];
        int toSwap = i;
        for(unsigned int j = i; j < vec.size(); j++){
            if(vec[j] < currMin){
                toSwap = j;
                currMin = vec[j];
            }
        }
        std::swap(vec[i], vec[toSwap]);
    }
}

template <typename T>
void SortingAlgorithms<T>::mergeSort(std::vector<T>& vec){
    mergeHelper(vec, 0, vec.size() - 1);
}

template <typename T>
void SortingAlgorithms<T>::quickSort(std::vector<T>& vec){
    int low = 0;
    int high = vec.size() -1;
    quickSortHelper(vec, low, high);
}

template <typename T>
void SortingAlgorithms<T>::heapSort(std::vector<T>& vec){
    Heap<T> heap;

    for(unsigned int i = 0; i < vec.size(); i++){
        heap.insert(vec[i]);
    }

    unsigned int back = vec.size() -1; //using max heap so insert in back

    while(!heap.empty()){
        vec[back] = heap.getMax();
        heap.removeMax();
        back--;
    }
}

template <typename T>
void SortingAlgorithms<T>::mergeHelper(std::vector<T>& vec, int begin, int end) {
    if (begin >= end)
        return;

    //recursively call mergeHelper until vectors of size 1 and then merge
    int mid = begin + (end - begin) / 2;
    mergeHelper(vec, begin, mid);
    mergeHelper(vec, mid + 1, end);

    //create temp new vector to merge subvectors
    std::vector<T> temp;
    int left = begin;
    int right = mid + 1;

    //while left and right subvectors both still have values
    while (left <= mid && right <= end) {
        if (vec[left] <= vec[right]) {
            temp.push_back(vec[left]);
            left++;
        } 
        else {
            temp.push_back(vec[right]);
            right++;
        }
    }

    //if left vector was bigger than right
    while (left <= mid) {
        temp.push_back(vec[left]);
        left++;
    }

    //if right vector was bigger than left
    while (right <= end) {
        temp.push_back(vec[right]);
        right++;
    }

    //update the vector with new values
    for (int i = begin, j = 0; i <= end; i++, j++) { 
        vec[i] = temp[j];
    }
}

template <typename T>
int SortingAlgorithms<T>::partition(std::vector<T>& vec, int low, int high){
    T pivot = vec[high];
    int i = low - 1;

    for(unsigned int j = low; j < high; j++){
        if(vec[j] < pivot){
            i++;
            std::swap(vec[i], vec[j]);
        }
    }

    std::swap(vec[i+1], vec[high]);
    return i+1;
}

template <typename T>
void SortingAlgorithms<T>::quickSortHelper(std::vector<T>& vec, int low, int high){
    if(low < high){
        int pivot = partition(vec, low, high);
        quickSortHelper(vec, low, pivot-1);
        quickSortHelper(vec, pivot+1, high);
    }
}
#endif