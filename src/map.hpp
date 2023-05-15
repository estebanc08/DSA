#ifndef MAP
#define MAP

#include "redBlackTree.hpp"

/// @brief A standard container with (key,value) objects that inserts and retrieves in logarithmic time
/// @tparam Key Type of Key object 
/// @tparam Value Type of Mapped object
template <typename Key, typename Value>
class Map{
    public:

        /// @brief Creates new Map
        Map();
        
        /// @brief default destructor, deletes RB tree
        ~Map();

        /// @brief Insert new value into map
        /// @param key Key value to insert
        /// @return Reference to Value to insert
        Value& operator[](Key key);

        /// @brief Returns the size of the Map
        unsigned int size();
        
        /// @brief Returns true if map is empty
        bool empty();

        /// @brief Get the Rb Tree Iterator implementation
        using Iterator = typename RedBlackTree<Key, Value>::Iterator;

        /// @brief Get the start of the Map
        /// @return Iterator to start of Map
        Iterator begin() {
            return tree->begin();
        }

        /// @brief Get the end of the Tree
        /// @return Iterator to end of map
        Iterator end() {
            return tree->end();
        }

        /// @brief Searches for value in the Map
        /// @param data Value to find
        /// @return Iterator to the value 
        Iterator find(Key key);
        
        /// @brief Erases Object with given Key Value
        /// @param key Key object to erase
        /// @return Iterator to element before it was removed, end() if not found
        Iterator erase(Key key);

    private:
        RedBlackTree<Key, Value>* tree;
};

template <typename Key, typename Value>
Map<Key, Value>::Map(){
    this->tree = new RedBlackTree<Key, Value>();
}

template <typename Key, typename Value>
Map<Key, Value>::~Map(){
    delete tree;
}

template <typename Key, typename Value>
unsigned int Map<Key, Value>::size(){
    return tree->size();
}

template <typename Key, typename Value>
bool Map<Key, Value>::empty(){
    return tree->empty();
}

template <typename Key, typename Value>
Value& Map<Key, Value>::operator[](Key key){
    Iterator iterator = tree->find(key);
    if(iterator == tree->end()) {
        iterator = tree->insert(std::make_pair(key, Value()));
    }
    return iterator->second;
}

template <typename Key, typename Value>
Map<Key, Value>::Iterator Map<Key, Value>::erase(Key key){
    return tree->remove(key);
}

template <typename Key, typename Value>
Map<Key, Value>::Iterator Map<Key, Value>::find(Key key){
    return tree->find(key);
}

#endif