#ifndef SET
#define SET

#include <iostream>
#include "bst.hpp"
#include <iterator>

namespace mystl{
    /// @brief Container with unique keys and logarithmic lookup
    template <typename T>
    class Set{
        private:
                BST<T>* tree;
        
        public:

            /// @brief Default Constructor
            Set();

            /// @brief Clears the Set and sets size to 0
            ~Set();

            /// @brief Gets the size of the Set
            /// @return Returns the size
            unsigned int size();

            /// @brief Insert element at the end
            void insert(T data);

            /// @brief Checks whether Set is empty
            /// @return Returns true if size = 0
            bool empty();

            /// @brief clears the contents
            void clear();
            
            /// @brief Remove value from the set
            /// @param data Value to remove
            /// @return True if data was in tree and was removed
            bool remove(T data){
                return tree->remove(data);
            }

            /// @brief Get the BST Iterator implementation
            using Iterator = typename BST<T>::Iterator;

            /// @brief Get the start of the Set
            /// @return 
            Iterator begin() {
                return tree->begin();
            }

            /// @brief Get the end of the set
            /// @return 
            Iterator end() {
                return tree->end();
            }

            /// @brief Searches for value in the set
            /// @param data Value to find
            /// @return Iterator to the value 
            Iterator find(T data){
                return tree->find(data);
            }
    };
}

template <typename T>
mystl::Set<T>::Set(){
    tree = new BST<T>();
}

template <typename T>
mystl::Set<T>::~Set(){
    delete tree;
}

template <typename T>
unsigned int mystl::Set<T>::size(){
    return tree->size();
}

template <typename T>
void mystl::Set<T>::insert(T data){
    if(tree->size() == 0){
        tree->insert(data);
        return;
    }
    if(tree->find(data) == tree->end()){
        tree->insert(data);
    }
}


template <typename T>
bool mystl::Set<T>::empty(){
    return tree->size() == 0;
}

#endif