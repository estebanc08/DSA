#ifndef HEAP
#define HEAP

#include <vector>

/// @brief Max heap implementation with fixed time to access max value
template <typename T>
class Heap{
    public:

        /// @brief Gets size of heap
        /// @return Returns size
        unsigned int size();
        
        /// @brief Insert new value in heap        
        void insert(T data);

        /// @brief Get the max value in the heap
        /// @return Reference to max value
        T& getMax();

        /// @brief Remove the max value update heap
        void removeMax();

        /// @brief Checks if the heap is empty
        /// @return Return true if heap is empty
        bool empty();

        /// @brief Clears the heap and resets to size 0
        void clear();

    private:
        std::vector<T> heap;

        /// @brief Update the heap when element removed
        /// @param index 
        void heapifyDown(unsigned int index);

        /// @brief Update the heap when new element inserted
        /// @param index 
        void heapifyUp(unsigned int index);
};

template <typename T>
void Heap<T>::clear(){
    heap.clear();
}

template <typename T>
bool Heap<T>::empty(){
    return heap.size() == 0;
}

template <typename T>
unsigned int Heap<T>::size(){
    return heap.size();
}

template <typename T>
void Heap<T>::removeMax(){
    if(heap.size() == 0)
        throw  std::out_of_range("Heap is empty");
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
}

template <typename T>
T& Heap<T>::getMax(){
    return heap[0];
}

template <typename T>
void Heap<T>::insert(T data){
    heap.push_back(data);
    heapifyUp(heap.size() -1);
}

template <typename T>
void Heap<T>::heapifyDown(unsigned int index){
    unsigned int leftChild = index*2+1;
    unsigned int rightChild = index*2+2;
    unsigned int largest = index;

    if(leftChild < heap.size() && heap[leftChild] > heap[index]){
        largest = leftChild;
    }
    if(rightChild < heap.size() && heap[rightChild] > heap[largest]){
        largest = rightChild;
    }

    if(largest != index){
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}

template <typename T>
void Heap<T>::heapifyUp(unsigned int index){
    unsigned int parent = index / 2;
    if(heap[parent] < heap[index]){
        std::swap(heap[parent], heap[index]);
        heapifyUp(parent);
    }
}

#endif