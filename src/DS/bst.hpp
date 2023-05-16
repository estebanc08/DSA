#ifndef BINARY_find_TREE
#define BINARY_find_TREE

#include <iostream>
#include "queue.hpp"
#include <iterator>

namespace mystl{
    /// @brief Binary Search Tree implementation
    template <typename T>
    class BST{
        private:
            struct Node{
                    unsigned int count;
                    T data;
                    Node* left;
                    Node* right;
                    Node* parent;
                    Node(T data);
            };
            Node* root;
        
        public:
            
            /// @brief default size to 0 and root to nullptr
            BST();

            /// @brief default destructor
            ~BST();

            /// @brief Insert data 
            /// @param data 
            void insert(T data);

            /// @brief Prints the tree using in-order
            void printTreeInorder();

            /// @brief Prints the tree using pre-order traversal
            void printTreePreorder();

            /// @brief Prints the tree using post-order traversal
            void printTreePostorder();
            
            /// @brief Prints the tree using level order traversal
            void printLevelOrder();

            /// @brief Removes node with value passed in. If there is more than one node with this value, only one will be deleted
            /// @param data 
            /// @return returns true if there is a node with that value
            bool remove(T data);

            /// @brief Gets the number of nodes in the tree
            /// @return size
            unsigned int size();

            /// @brief Returns if the tree is empty
            /// @return 
            bool empty();

            /// @brief Clears the tree and sets size to 0
            void clear();

            /// @brief BST class Iterator
            class Iterator {
                public:
                    using iterator_category = std::forward_iterator_tag;
                    using difference_type = std::ptrdiff_t;
                    using value_type = T;
                    using pointer = T*;
                    using reference = T&;

                    /// @brief default constructor, set to null if no parameter passed               
                    Iterator(Node* node = nullptr) : current(node) {}

                    /// @brief Dereference the iterator
                    /// @return Value at the Iterator
                    reference operator*() const {
                        return current->data;
                    }

                    /// @brief Dereference pointer
                    /// @return Pointer to the iterator
                    pointer operator->() const {
                        return &(current->data);
                    }

                    /// @brief Move to next value in tree
                    /// @return Reference to next Iterator
                    Iterator& operator++();

                    /// @brief Move the iterator forward by N values
                    /// @return Iterator at new value
                    Iterator operator++(int);

                    /// @brief Compares if iterators equal
                    /// @return True if iterators point to same value
                    bool operator==(const Iterator& other) const {
                        return current == other.current;
                    }

                    /// @brief Compares if Iterators not equal
                    /// @return True if they are not equal
                    bool operator!=(const Iterator& other) const {
                        return !(*this == other);
                    }

                private:
                    mystl::BST<T>::Node* current;
            };

            Iterator begin() {
                Node* node = root;
                while (node->left != nullptr) {
                    node = node->left;
                }
                return Iterator(node);
            }

            Iterator end() {
                return Iterator(nullptr);
            }

            // @brief findes for the data in the tree
            /// @param data 
            /// @return returns true if found, else returns false
            Iterator find(T data);

        private:
            unsigned int _size;

            /// @brief Needed for insert recursion
            /// @param data 
            /// @param curr 
            /// @return returns the new node inserted or increments counter
            Node* insertHelper(T data, Node* curr, Node* parent);
        
            /// @brief helps the tree inorder
            /// @param curr 
            void printInorderHelper(Node* curr);

            /// @brief helps the tree inorder
            /// @param curr 
            void printProrderHelper(Node* curr);

            /// @brief helps the tree inorder
            /// @param curr 
            void printPostorderHelper(Node* curr);

            /// @brief Used to hide remove implementation
            /// @param curr 
            /// @return return Node pointer to assign new left and right
            Node* removeHelper(T target, Node* curr, Node* parent);
    };
}

template <typename T>
mystl::BST<T>::Iterator& mystl::BST<T>::Iterator::operator++(){
        if (current->right != nullptr) {
            current = current->right;
            while (current->left != nullptr) {
                current = current->left;
            }
        }
        else {
            Node* temp = current->parent;
            while (temp != nullptr && current == temp->right) {
                current = temp;
                temp = temp->parent;
            }
            current = temp;
        }
        return *this;
}


template <typename T>
mystl::BST<T>::Iterator mystl::BST<T>::Iterator::operator++(int){
    Iterator temp(*this);
    ++(*this);
    return temp;
}

template <typename T>
mystl::BST<T>::Node::Node(T data){
    this->data = data;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    this->count = 1;
}

template <typename T>
mystl::BST<T>::BST(){
    this->_size = 0;
    this->root = nullptr;
}

template <typename T>
mystl::BST<T>::~BST(){
    clear();
}

template <typename T>
void mystl::BST<T>::insert(T data){
    this->_size++;
    this->root = insertHelper(data, this->root, nullptr);
}

template <typename T>
mystl::BST<T>::Node* mystl::BST<T>::insertHelper(T data, mystl::BST<T>::Node* curr, mystl::BST<T>::Node* parent){
    if(!curr){
        Node* newNode = new Node(data);
        newNode->parent = parent;
        return newNode;
    }
    if(data == curr->data){
        curr->count++;
    }
    else if(data < curr->data){
        curr->left = insertHelper(data, curr->left, curr);
    }
    else{
        curr->right = insertHelper(data, curr->right, curr);
    }
    return curr;
}

template <typename T>
void mystl::BST<T>::printTreeInorder(){
    printInorderHelper(this->root);
    std::cout << "\n";
}

template <typename T>
void mystl::BST<T>::printInorderHelper(mystl::BST<T>::Node* curr){
    if(!curr)
        return;
    if(curr->left)
        printInorderHelper(curr->left);
    for(unsigned int i = 0; i < curr->count; i++)
        std::cout << curr->data << " ";
    if(curr->right)
        printInorderHelper(curr->right);
}

template <typename T>
void mystl::BST<T>::printTreePreorder(){
    printProrderHelper(this->root);
    std::cout << "\n";
}

template <typename T>
void mystl::BST<T>::printProrderHelper(mystl::BST<T>::Node* curr){
    if(!curr)
        return;
    for(unsigned int i = 0; i < curr->count; i++)
        std::cout << curr->data << " ";
    if(curr->left)
        printProrderHelper(curr->left);
    if(curr->right)
        printProrderHelper(curr->right);
}

template <typename T>
void mystl::BST<T>::printTreePostorder(){
    printPostorderHelper(this->root);
    std::cout << "\n";
}

template <typename T>
void mystl::BST<T>::printPostorderHelper(mystl::BST<T>::Node* curr){
    if(!curr)
        return;
    if(curr->left)
        printPostorderHelper(curr->left);
    if(curr->right)
        printPostorderHelper(curr->right);
    for(unsigned int i = 0; i < curr->count; i++)
        std::cout << curr->data << " ";
}
template <typename T>
unsigned int mystl::BST<T>::size(){
    return this->_size;
}

template <typename T>
mystl::BST<T>::Iterator mystl::BST<T>::find(T data){
    if(this->_size == 0)
        return end();
    
    for(auto it = begin(); it != end(); it++){
        if((*it) > data)
            return end();
        if((*it) == data)
            return it;
    }
    return end();
}

template <typename T>
bool mystl::BST<T>::remove(T data){
    if(this->_size == 0 || find(data) == end())
        return false;
    this->root = removeHelper(data, root, nullptr);
    this->_size--;
    return true;
}

template <typename T>
typename mystl::BST<T>::Node* mystl::BST<T>::removeHelper(T target, mystl::BST<T>::Node* curr, mystl::BST<T>::Node* parent){
    if (!curr){
        return nullptr;
    }

    if (target < curr->data){
        curr->left = removeHelper(target, curr->left, curr);
    }
 
    else if (target > curr->data){
        curr->right = removeHelper(target, curr->right, curr);
    }
 
    else{
        if (curr->count > 1){
            curr->count--;
            return curr;
        }
        if (!curr->left){
            Node* temp = curr->right;
            if (parent){
                if (parent->left == curr){
                    parent->left = temp;
                }
                else{
                    parent->right = temp;
                }
            }
            delete curr;
            return temp;
        }
        else if (!curr->right)
        {
            Node* temp = curr->left;
            if (parent){
                if (parent->left == curr){
                    parent->left = temp;
                }
                else{
                    parent->right = temp;
                }
            }
            delete curr;
            return temp;
        }
        Node* temp = curr->right;
        while(temp->left){
            temp = temp->left;
        }

        curr->data = temp->data;
        curr->count = temp->count;
        temp->count = 0;
        curr->right = removeHelper(temp->data, curr->right, curr);
    }
    return curr;
}


template <typename T>
bool mystl::BST<T>::empty(){
    return this->_size == 0;
}

template <typename T>
void mystl::BST<T>::printLevelOrder(){
    if(!this->root)
        return;
    
    Queue<Node*> q;
    unsigned int level = 1;
    q.push(this->root);
    while(!q.empty()){
        unsigned int num = q.size();
        std::cout << "Level " << level << ": ";
        for(unsigned int i = 0; i < num; i++){
            Node* temp = q.front();
            q.pop();
            std::cout << temp->data << " ";
            if(temp->left)
                q.push(temp->left);
            if(temp->right)
                q.push(temp->right);
        }
        level++;
        std::cout << "\n";
    }
}

template <typename T>
void mystl::BST<T>::clear(){
    while(root)
        root = removeHelper(root->data, root, nullptr);
    this->_size = 0;
    this->root = nullptr;
}


#endif