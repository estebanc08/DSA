#ifndef Red_Black_TREE
#define Red_Black_TREE

#include <iterator>
#include <iostream>

/// @brief Standard container for red black tree with logarithmic search, deletion, and insertion
template <typename T>
class RedBlackTree{
     private:
        /// @brief Holds the data for each element in the tree
        struct Node{
            unsigned int count = 0;
            enum Color {Black, Red, DoubleBlack};
            Color color;
            T data;
            Node* left;
            Node* right;
            Node* parent;
            Node(T _data) : data(_data) {color = Color::Red; this->count = 1;};
        };
        Node* root;
    
    public:

        /// @brief Default Constructor. Size set to 0 and root is null
        RedBlackTree();

        /// @brief Destructor. Free all memory from nodes
        ~RedBlackTree();

        /// @brief Gets the size of the tree
        /// @return Size of the tree
        unsigned int size();

        /// @brief Insert new value into tree
        /// @param data Value to be inserted
        void insert(T data);

        /// @brief Remove value from tree
        /// @param data Value to remove
        void remove(T data);

        /// @brief Checks if the tree is empty
        /// @return Returns true if tree is empty
        bool empty();


    /// @brief Red-Black Tree class Iterator
        class Iterator {
            public:
                using iterator_category = std::forward_iterator_tag;
                using difference_type = std::ptrdiff_t;
                using value_type = T;
                using pointer = T*;
                using reference = T&;

                /// @brief default constructor, set to null if no parameter passed               
                Iterator(Node* node = nullptr, unsigned int _count = 0) : current(node), count(_count) {}

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
                RedBlackTree<T>::Node* current;
                unsigned int count = 0;
        };

        /// @brief Points to min value in the tree
        /// @return Returns iterator to the start of the tree 
        Iterator begin() {
            Node* node = root;
            while (node->left != nullptr) {
                node = node->left;
            }
            unsigned int count = 0;
            if(node){
                count = node->count;
            }
            return Iterator(node, count);
        }

        /// @brief Gets the end of available data for tree
        /// @return Returns Iterator that points past the end of the tree
        Iterator end() {
            return Iterator(nullptr);
        }

        /// @brief Finds value in the tree
        /// @param data Value to find
        /// @return Returns Iterator to value if found in tree, otherwise returns end
        Iterator find(T data);
    
    private:

        void rotateLeft(Node* curr);

        void rotateRight(Node* curr);

        unsigned int _size;

        Node* insertHelper(Node* curr, Node* parent);

        bool isBlack(Node* curr);

        Node* inorderSuccessor(Node* curr);

        Node* removeHelper(T data, Node* curr);

        void fixRemove(Node* curr);

        void recolor(Node* curr, Node::Color color);

        int checkBlackHeight(Node* curr);

        void fixInsert(Node* curr);

        void postOrderDelete(Node* curr);

        /// @brief Testing purpose, Used to make sure all paths contain same number of black nodes
        /// @return  Return true if valid
        bool isValid();
};

template <typename T>
RedBlackTree<T>::Iterator& RedBlackTree<T>::Iterator::operator++(){
    if (current->right != nullptr) {
        if(count > 1){
            count--;
        }
        else{
            current = current->right;
            while (current->left != nullptr) {
                current = current->left;
            }
            if(current){
                count = current->count;
            }
        }
    }
    else {
        if(count > 1){
            count--;
        }
        else{
            Node* temp = current->parent;
            while (temp != nullptr && current == temp->right) {
                current = temp;
                temp = temp->parent;
            }
            current = temp;
            if(current){
                count = current->count;
            }
        }
    }
    return *this;
}

template <typename T>
RedBlackTree<T>::Iterator RedBlackTree<T>::Iterator::operator++(int){
    Iterator temp(*this);
    ++(*this);
    return temp;
}


template <typename T>
unsigned int RedBlackTree<T>::size(){
    return this->_size;
}

template <typename T>
RedBlackTree<T>::RedBlackTree(){
    this->_size = 0;
    this->root = nullptr;
}

template <typename T>
RedBlackTree<T>::~RedBlackTree() {
    postOrderDelete(root);
}

template <typename T>
void RedBlackTree<T>::postOrderDelete(RedBlackTree<T>::Node* curr) {
    if (curr == nullptr) {
        return;
    }
    postOrderDelete(curr->left);
    postOrderDelete(curr->right);
    delete curr;
}


template <typename T>
RedBlackTree<T>::Iterator RedBlackTree<T>::find(T data){
    if(this->_size == 0)
        end();

    for(auto it = begin(); it != end(); it++){
        if((*it) == data)
            return it;
        if((*it) > data)
            return end();
    }

    return end();
}


template <typename T>
void RedBlackTree<T>::insert(T data){
    Node* newNode = new Node(data);
    this->root = insertHelper(root, newNode);
    fixInsert(newNode);
    this->_size++;
};

template <typename T>
void RedBlackTree<T>::rotateLeft(RedBlackTree<T>::Node* curr){
    Node* rightChild = curr->right;
    curr->right = rightChild->left;

    if (curr->right != nullptr)
        curr->right->parent = curr;

    rightChild->parent = curr->parent;

    if (curr->parent == nullptr)
        root = rightChild;
    else if (curr == curr->parent->left)
        curr->parent->left = rightChild;
    else
        curr->parent->right = rightChild;

    rightChild->left = curr;
    curr->parent = rightChild;
}

template <typename T>
void RedBlackTree<T>::rotateRight(RedBlackTree<T>::Node* curr){
    Node* leftChild = curr->left;
    curr->left = leftChild->right;

    if (curr->left != nullptr)
        curr->left->parent = curr;

    leftChild->parent = curr->parent;

    if (curr->parent == nullptr)
        root = leftChild;
    else if (curr == curr->parent->left)
        curr->parent->left = leftChild;
    else
        curr->parent->right = leftChild;

    leftChild->right = curr;
    curr->parent = leftChild;
}

template <typename T>
RedBlackTree<T>::Node* RedBlackTree<T>::insertHelper(RedBlackTree<T>::Node* root, RedBlackTree<T>::Node* curr){
    if (root == nullptr)
        return curr;

    if (curr->data < root->data) {
        root->left = insertHelper(root->left, curr);
        root->left->parent = root;
    } else if (curr->data > root->data) {
        root->right = insertHelper(root->right, curr);
        root->right->parent = root;
    }
    else{
        root->count++;
    }

    return root;
}

template <typename T>
void RedBlackTree<T>::fixInsert(RedBlackTree<T>::Node* curr){
    Node *_parent = nullptr;
    Node *grandparent = nullptr;
    while (curr != root && !isBlack(curr) && !isBlack(curr->parent)) {
        _parent = curr->parent;
        grandparent = _parent->parent;
        if (grandparent && _parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (!isBlack(uncle)) {
                recolor(uncle, Node::Color::Black);
                recolor(_parent, Node::Color::Black);
                recolor(grandparent, Node::Color::Red);
                curr = grandparent;
            } 
            else {
                if (curr == _parent->right) {
                    rotateLeft(_parent);
                    curr = _parent;
                    _parent = curr->parent;
                }
                rotateRight(grandparent);
                typename Node::Color temp = _parent->color;
                _parent->color = grandparent->color;
                grandparent->color = temp;
                curr = _parent;
            }
        } 
        else {
            Node *uncle = grandparent->left;
            if (!isBlack(uncle)) {
                recolor(uncle, Node::Color::Black);
                recolor(_parent, Node::Color::Black);
                recolor(grandparent, Node::Color::Red);
                curr = grandparent;
            } 
            else {
                if (curr == _parent->left) {
                    rotateRight(_parent);
                    curr = _parent;
                    _parent = curr->parent;
                }
                rotateLeft(grandparent);
                typename Node::Color temp = _parent->color;
                _parent->color = grandparent->color;
                grandparent->color = temp;
                curr = _parent;
            }
        }
    }
    recolor(root, Node::Color::Black);
}

template <typename T>
void RedBlackTree<T>::remove(T data){
    Node* curr = removeHelper(data, root);
    this->_size--;
    fixRemove(curr);
}


template <typename T>
RedBlackTree<T>::Node* RedBlackTree<T>::removeHelper(T data, RedBlackTree<T>::Node* curr){
    if(!curr){
        throw std::out_of_range("Value not in tree");
    }
    if(curr->data < data){
        return removeHelper(data, curr->right);
    }
    if(curr->data > data){
        return removeHelper(data, curr->left);
    }
    if(curr->count > 1){
        curr->count--;
        return curr;
    }
    if(!curr->left || !curr->right)
        return curr;
    curr->count = 0;
    Node* inorder = inorderSuccessor(curr);
    curr->data = inorder->data;
    return removeHelper(inorder->data, curr->right);
}

template <typename T>
void RedBlackTree<T>::fixRemove(RedBlackTree<T>::Node* curr){
    if (curr == nullptr)
        return;

    if (curr == root) {
        root = nullptr;
        return;
    }
    if(curr->count > 0){
        return;
    }
    if (!isBlack(curr) || !isBlack(curr->left) || !isBlack(curr->right)) {
        Node *child = curr->left != nullptr ? curr->left : curr->right;

        if (curr == curr->parent->left) {
            curr->parent->left = child;
            if (child != nullptr)
                child->parent = curr->parent;
            recolor(child, Node::Color::Black);
            delete curr;
        } else {
            curr->parent->right = child;
            if (child != nullptr)
                child->parent = curr->parent;
            recolor(child, Node::Color::Black);
            delete curr;
        }
    } else {
        Node *sibling = nullptr;
        Node *parent = nullptr;
        Node *ptr = curr;
        recolor(ptr, Node::Color::DoubleBlack);
        while (ptr && ptr != root && ptr->color == Node::Color::DoubleBlack) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (!isBlack(sibling)) {
                    recolor(sibling, Node::Color::Black);
                    recolor(parent, Node::Color::Red);
                    rotateLeft(parent);
                } else {
                    if (isBlack(sibling->left) && isBlack(sibling->right)) {
                        recolor(sibling, Node::Color::Red);
                        if(!isBlack(parent))
                            recolor(parent, Node::Color::Black);
                        else
                            recolor(parent, Node::Color::DoubleBlack);
                        ptr = parent;
                    } else {
                        if (isBlack(sibling->right)) {
                            recolor(sibling->left, Node::Color::Black);
                            recolor(sibling, Node::Color::Red);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }
                        recolor(sibling, parent->color);
                        recolor(parent, Node::Color::Black);
                        recolor(sibling->right, Node::Color::Black);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                sibling = parent->left;
                if (!isBlack(sibling)) {
                    recolor(sibling, Node::Color::Black);
                    recolor(parent, Node::Color::Red);
                    rotateRight(parent);
                } else {
                    if (isBlack(sibling->left) && isBlack(sibling->right)) {
                        recolor(sibling, Node::Color::Red);
                        if (!isBlack(parent))
                            recolor(parent, Node::Color::Black);
                        else
                            recolor(parent, Node::Color::DoubleBlack);
                        ptr = parent;
                    } else {
                        if (isBlack(sibling->left)) {
                            recolor(sibling->right, Node::Color::Black);
                            recolor(sibling, Node::Color::Red);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        recolor(sibling, parent->color);
                        recolor(parent, Node::Color::Black);
                        recolor(sibling->left, Node::Color::Black);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (curr == curr->parent->left)
            curr->parent->left = nullptr;
        else
            curr->parent->right = nullptr;
        delete curr;

        recolor(root, Node::Color::Black);
    }
}

template <typename T>
RedBlackTree<T>::Node* RedBlackTree<T>::inorderSuccessor(RedBlackTree<T>::Node* curr){
    if(!curr->right)
        return nullptr;
    Node* temp = curr->right;
    while(temp->left){
        temp = temp->left;
    }
    return temp;
}

template <typename T>
void RedBlackTree<T>::recolor(RedBlackTree<T>::Node* curr, RedBlackTree<T>::Node::Color color){
    if(!curr)
        return;
    curr->color = color;
}

template <typename T>
bool RedBlackTree<T>::isBlack(RedBlackTree<T>::Node* curr){
    if(curr && curr->color == Node::Color::Red)
        return false;
    else return true;
}



template <typename T>
bool RedBlackTree<T>::empty(){
    return this->_size == 0;
}

template <typename T>
bool RedBlackTree<T>::isValid(){
    if (root == nullptr) {
        return true;
    }

    if (root->color != Node::Color::Black) {
        std::cout << "root not black\n";
        return false;
    }

    return checkBlackHeight(root) != -1;
}

template <typename T>
int RedBlackTree<T>::checkBlackHeight(RedBlackTree<T>::Node* curr){
    if (curr == nullptr) {
        return 1;
    }

    int leftHeight = checkBlackHeight(curr->left);
    int rightHeight = checkBlackHeight(curr->right);

    if (leftHeight == -1 || rightHeight == -1 || leftHeight != rightHeight) {
        std::cout << "left and right height dont match: " << leftHeight << " " << rightHeight << "\n";
        return -1;
    }

    if (curr->color == Node::Color::Red && !isBlack(curr->left) && !isBlack(curr->right)){
        std::cout << "red node with two red children\n";
        return -1;
    }

    return (curr->color == Node::Color::Black ? leftHeight + 1 : leftHeight);
}
#endif