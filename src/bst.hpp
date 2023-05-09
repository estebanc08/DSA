#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <iostream>
#include <queue>

template <typename T>
class BST{
    public:

        /// @brief default size to 0 and head to nullptr
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

        /// @brief Searches for the data in the tree
        /// @param data 
        /// @return returns true if found, else returns false
        bool search(T data);

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

    private:
        struct Node{
            unsigned int count;
            T data;
            Node* left;
            Node* right;
            Node(T data);
        };
        unsigned int _size;
        Node* head;

        /// @brief Needed for insert recursion
        /// @param data 
        /// @param curr 
        /// @return returns the new node inserted or increments counter
        Node* insertHelper(T data, Node* curr);
    
        /// @brief helps the tree inorder
        /// @param curr 
        void printInorderHelper(Node* curr);

        /// @brief Used to hide search implementation
        /// @param curr 
        /// @return returns true if found
        bool searchHelper(T target, Node* curr);

        /// @brief helps the tree inorder
        /// @param curr 
        void printProrderHelper(Node* curr);

        /// @brief helps the tree inorder
        /// @param curr 
        void printPostorderHelper(Node* curr);

        /// @brief Used to hide remove implementation
        /// @param curr 
        /// @return return Node pointer to assign new left and right
        Node* removeHelper(T target, Node* curr);

};

template <typename T>
BST<T>::Node::Node(T data){
    this->data = data;
    left = nullptr;
    right = nullptr;
    this->count = 1;
}

template <typename T>
BST<T>::BST(){
    this->_size = 0;
    this->head = nullptr;
}

template <typename T>
BST<T>::~BST(){
    clear();
}

template <typename T>
void BST<T>::insert(T data){
    this->_size++;
    this->head = insertHelper(data, this->head);
}

template <typename T>
BST<T>::Node* BST<T>::insertHelper(T data, BST<T>::Node* curr){
    if(!curr){
        Node* newNode = new Node(data);
        return newNode;
    }
    if(data == curr->data){
        curr->count++;
    }
    else if(data < curr->data){
        curr->left = insertHelper(data, curr->left);
    }
    else{
        curr->right = insertHelper(data, curr->right);
    }
    return curr;
}

template <typename T>
void BST<T>::printTreeInorder(){
    printInorderHelper(this->head);
    std::cout << "\n";
}

template <typename T>
void BST<T>::printInorderHelper(BST<T>::Node* curr){
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
void BST<T>::printTreePreorder(){
    printProrderHelper(this->head);
    std::cout << "\n";
}

template <typename T>
void BST<T>::printProrderHelper(BST<T>::Node* curr){
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
void BST<T>::printTreePostorder(){
    printPostorderHelper(this->head);
    std::cout << "\n";
}

template <typename T>
void BST<T>::printPostorderHelper(BST<T>::Node* curr){
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
unsigned int BST<T>::size(){
    return this->_size;
}

template <typename T>
bool BST<T>::search(T data){
    return searchHelper(data, this->head);
}

template <typename T>
bool BST<T>::searchHelper(T target, Node* curr){
    if(!curr)
        return false;
    if(target == curr->data)
        return true;
    else if(curr->data < target)
        return searchHelper(target, curr->right);
    else{
        return searchHelper(target, curr->left);
    }
}

template <typename T>
bool BST<T>::remove(T data){
    if(!search(data))
        return false;
    removeHelper(data, head);
    this->_size--;
    return true;
}

template <typename T>
BST<T>::Node* BST<T>::removeHelper(T target, Node* curr){
    if (!curr){
        return nullptr;
    }

    if (target < curr->data){
        curr->left = removeHelper(target, curr->left);
    }
 
    else if (target > curr->data){
        curr->right = removeHelper(target, curr->right);
    }
 
    else{
        if (curr->count > 1){
            curr->count--;
            return curr;
        }
        if (!curr->left){
            Node* temp = curr->right;
            delete curr;
            return temp;
        }
        else if (!curr->right)
        {
            Node* temp = curr->left;
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
        curr->right = removeHelper(temp->data, curr->right);
    }
    return curr;
}

template <typename T>
bool BST<T>::empty(){
    return this->_size == 0;
}

template <typename T>
void BST<T>::printLevelOrder(){
    if(!this->head)
        return;
    
    std::queue<Node*> q;
    unsigned int level = 1;
    q.push(this->head);
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
void BST<T>::clear(){
    while(head)
        head = removeHelper(head->data, head);
    this->_size = 0;
    this->head = nullptr;
}


#endif