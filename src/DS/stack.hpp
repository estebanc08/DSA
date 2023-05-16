#ifndef STACK
#define STACK

#include <iostream>
#include "singlyLinkedList.hpp"

/// @brief First in Last out container implementation
template <typename T>
class Stack{
    public:

        /// @brief Default Constructor
        Stack();

        /// @brief Clears the Stack and sets size to 0
        ~Stack();

        /// @brief Gets the size of the Stack
        /// @return Returns the size
        unsigned int size();

        /// @brief Removes the first element
        void pop();

        /// @brief Insert element at the end
        void push(T data);
        
        /// @brief Access the top of the stack
        /// @return References to top
        T& top();


        /// @brief Checks whether Stack is empty
        /// @return Returns true if size = 0
        bool empty();
        
    private:
        SinglyLinkedList<T>* list;
};

template <typename T>
Stack<T>::Stack(){
    list = new SinglyLinkedList<T>();
}

template <typename T>
Stack<T>::~Stack(){
    delete list;
}

template <typename T>
unsigned int Stack<T>::size(){
    return list->size();
}

template <typename T>
void Stack<T>::pop(){
    if(list->size() > 0)
        list->removeAt(list->size() - 1);
    else
        throw std::out_of_range("Stack is empty");
}

template <typename T>
void Stack<T>::push(T data){
    list->push_back(data);
}

template <typename T>
T& Stack<T>::top(){
    return (*list)[list->size() - 1];
}

template <typename T>
bool Stack<T>::empty(){
    return list->size() == 0;
}

#endif