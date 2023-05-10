#ifndef QUEUE
#define QUEUE

#include <iostream>
#include "singlyLinkedList.hpp"


template <typename T>
class Queue{
    public:

        /// @brief Default Constructor
        Queue();

        /// @brief Clears the queue and sets size to 0
        ~Queue();

        /// @brief Gets the size of the queue
        /// @return Returns the size
        unsigned int size();

        /// @brief Removes the first element
        void pop();

        /// @brief Insert element at the end
        void push(T data);
        
        /// @brief Access the first element
        /// @return References to last element
        T& front();

        /// @brief Access the last element
        /// @return Reference to last element
        T& back();

        /// @brief Checks whether queue is empty
        /// @return Returns true if size = 0
        bool empty();
        
    private:
        struct Node{
            T data;
            Node(T _data) : data(_data) {};
        };
        SinglyLinkedList<T>* list;
};

template <typename T>
Queue<T>::Queue(){
    list = new SinglyLinkedList<T>();
}

template <typename T>
Queue<T>::~Queue(){
    list->clear();
}

template <typename T>
unsigned int Queue<T>::size(){
    return list->size();
}

template <typename T>
void Queue<T>::pop(){
    list->removeAt(0);
}

template <typename T>
void Queue<T>::push(T data){
    list->push_back(data);
}

template <typename T>
T& Queue<T>::front(){
    return (*list)[0];
}

template <typename T>
T& Queue<T>::back(){
    return (*list)[list->size()-1];
}

template <typename T>
bool Queue<T>::empty(){
    return list->size() == 0;
}

#endif