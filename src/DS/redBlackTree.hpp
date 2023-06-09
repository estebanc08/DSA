#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE

#include <iterator>
#include <iostream>

namespace mystl{
    /// @brief Standard container for red black tree with logarithmic search, deletion, and insertion
    /// @tparam Key constant Key value
    /// @tparam Value type of mapped object
    template <typename Key, typename Value>
    class RedBlackTree{
        private:
            /// @brief Holds the key for each element in the tree
            struct Node{
                enum Color {Black, Red, DoubleBlack};
                Color color;
                std::pair<Key, Value> data;
                Node* left;
                Node* right;
                Node* parent;
                Node(std::pair<Key, Value>&& _pair);
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

            /// @brief Checks if the tree is empty
            /// @return Returns true if tree is empty
            bool empty();


        /// @brief Red-Black Tree class Iterator
            class Iterator {
                public:
                    using iterator_category = std::forward_iterator_tag;
                    using difference_type = std::ptrdiff_t;
                    using value_type = std::pair<Key, Value>;
                    using pointer = value_type*;
                    using reference = value_type&;

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
                        return &current->data;
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
                    mystl::RedBlackTree<Key, Value>::Node* current;
            };

            /// @brief Points to min value in the tree
            /// @return Returns iterator to the start of the tree 
            Iterator begin() {
                Node* node = root;
                while (node->left != nullptr) {
                    node = node->left;
                }
                return Iterator(node);
            }

            /// @brief Gets the end of available key for tree
            /// @return Returns Iterator that points past the end of the tree
            Iterator end() {
                return Iterator(nullptr);
            }

            /// @brief Finds value in the tree
            /// @param key Value to find
            /// @return Returns Iterator to value if found in tree, otherwise returns end
            Iterator find(const Key key);

            /// @brief Insert new value into tree
            /// @param key Key to be inserted
            /// @param value Value to be inserted
            Iterator insert(std::pair<const Key, Value> pair);

            /// @brief Remove value from tree
            /// @param key Key to be removed
            /// @return Iterator to element before removal
            Iterator remove(Key key);
        
        private:

            /// @brief Rotate Left on delete or insert
            /// @param curr 
            void rotateLeft(Node* curr);

            /// @brief Rotate Right on delete or insert
            /// @param curr 
            void rotateRight(Node* curr);

            unsigned int _size;

            /// @brief Used to recursively insert
            /// @param curr Current Node
            /// @param parent Parent Node
            /// @return Return New Node
            Node* insertHelper(Node* _root, Node* curr);

            /// @brief Returns if the node is black
            /// @param curr Current Node to check
            /// @return True if Black, red if false
            bool isBlack(Node* curr);

            /// @brief Get the Inorder Sucessor
            /// @param curr Node to get the successor of
            /// @return Return Inorder Succesor
            Node* inorderSuccessor(Node* curr);

            /// @brief Helper function to recursively remove
            /// @param key Value of node to delete
            /// @param curr Current Node to look at
            /// @return Node to delete
            Node* removeHelper(Key key, Node* curr);

            /// @brief Helps balance tree after remove
            /// @param curr Node that was removed
            void fixRemove(Node* curr);

            /// @brief Change color of Node
            /// @param curr Node to change
            /// @param color New color
            void recolor(Node* curr, Node::Color color);

            /// @brief Checks the number of nodes in path from root to leaf
            /// @param curr Current Node
            /// @return Number of black nodes on patg
            int checkBlackHeight(Node* curr);

            /// @brief helps balance tree after insert
            /// @param curr Node that was inserted
            void fixInsert(Node* curr);

            /// @brief Helper function to make destructor faster
            /// @param curr Current Node to delete
            void postOrderDelete(Node* curr);

            /// @brief Testing purpose, Used to make sure all paths contain same number of black nodes
            /// @return  Return true if valid
            bool isValid();
    };
}

template <typename Key, typename Value>
mystl::RedBlackTree<Key, Value>::Node::Node(std::pair<Key, Value>&& _pair) : data(_pair){
    this->color = Color::Red;
    this->right = nullptr;
    this->left = nullptr;
    this->parent = nullptr;
}

template <typename Key, typename Value>
mystl::RedBlackTree<Key, Value>::Iterator& mystl::RedBlackTree<Key, Value>::Iterator::operator++(){
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

template <typename Key, typename Value>
mystl::RedBlackTree<Key, Value>::Iterator mystl::RedBlackTree<Key, Value>::Iterator::operator++(int){
    Iterator temp(*this);
    ++(*this);
    return temp;
}


template <typename Key, typename Value>
unsigned int mystl::RedBlackTree<Key, Value>::size(){
    return this->_size;
}

template <typename Key, typename Value>
mystl::RedBlackTree<Key, Value>::RedBlackTree(){
    this->_size = 0;
    this->root = nullptr;
}

template <typename Key, typename Value>
mystl::RedBlackTree<Key, Value>::~RedBlackTree() {
    postOrderDelete(root);
}

template <typename Key, typename Value>
void mystl::RedBlackTree<Key, Value>::postOrderDelete(mystl::RedBlackTree<Key, Value>::Node* curr) {
    if (!curr) {
        return;
    }
    postOrderDelete(curr->left);
    postOrderDelete(curr->right);
    delete curr;
}


template <typename Key, typename Value>
mystl::RedBlackTree<Key, Value>::Iterator mystl::RedBlackTree<Key, Value>::find(const Key key){
    if(this->_size == 0)
        end();

    Node* current = this->root;
    while(current){
        if(current->data.first > key){
            current = current->left;
        }
        else if(current->data.first < key){
            current = current->right;
        }
        else break; //found
    }
    if(!current)
        return end();
    return Iterator(current);
}


template <typename Key, typename Value>
mystl::RedBlackTree<Key, Value>::Iterator mystl::RedBlackTree<Key, Value>::insert(std::pair<const Key, Value> pair){
    Iterator it = find(pair.first);
    if(it != end())
        return it;

    unsigned int currSize = ++this->_size;
    Node* newNode = new Node(std::move(pair));
    this->root = insertHelper(root, newNode);
    fixInsert(newNode);
    return Iterator(newNode);
};


template <typename Key, typename Value>
mystl::RedBlackTree<Key, Value>::Node* mystl::RedBlackTree<Key, Value>::insertHelper(mystl::RedBlackTree<Key, Value>::Node* _root, mystl::RedBlackTree<Key, Value>::Node* curr){
    if (!_root){
        return curr;
    }

    if (curr->data.first < _root->data.first) {
        _root->left = insertHelper(_root->left, curr);
        _root->left->parent = _root;
    } 
    else if (curr->data.first > _root->data.first) {
        _root->right = insertHelper(_root->right, curr);
        _root->right->parent = _root;
    }
    return _root;
}

template <typename Key, typename Value>
void mystl::RedBlackTree<Key, Value>::rotateLeft(mystl::RedBlackTree<Key, Value>::Node* curr){
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

template <typename Key, typename Value>
void mystl::RedBlackTree<Key, Value>::rotateRight(mystl::RedBlackTree<Key, Value>::Node* curr){
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

template <typename Key, typename Value>
void mystl::RedBlackTree<Key, Value>::fixInsert(mystl::RedBlackTree<Key, Value>::Node* curr){
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

template <typename Key, typename Value>
mystl::RedBlackTree<Key, Value>::Iterator mystl::RedBlackTree<Key, Value>::remove(Key key){
    if(empty() || find(key) == end())
        return end();
    Node* curr = removeHelper(key, root);
    this->_size--;
    fixRemove(curr);
    return Iterator(curr);
}


template <typename Key, typename Value>
mystl::RedBlackTree<Key, Value>::Node* mystl::RedBlackTree<Key, Value>::removeHelper(Key key, mystl::RedBlackTree<Key, Value>::Node* curr){
    if(!curr){
        throw std::out_of_range("Value not in tree");
    }
    if(curr->data.first < key){
        return removeHelper(key, curr->right);
    }
    if(curr->data.first > key){
        return removeHelper(key, curr->left);
    }
    if(!curr->left || !curr->right)
        return curr;
    Node* inorder = inorderSuccessor(curr);
    curr->data.first = inorder->data.first;
    return removeHelper(inorder->data.first, curr->right);
}

template <typename Key, typename Value>
void mystl::RedBlackTree<Key, Value>::fixRemove(mystl::RedBlackTree<Key, Value>::Node* curr){
    if (curr == nullptr)
        return;

    if (curr == root) {
        root = nullptr;
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

template <typename Key, typename Value>
mystl::RedBlackTree<Key, Value>::Node* mystl::RedBlackTree<Key, Value>::inorderSuccessor(mystl::RedBlackTree<Key, Value>::Node* curr){
    if(!curr->right)
        return nullptr;
    Node* temp = curr->right;
    while(temp->left){
        temp = temp->left;
    }
    return temp;
}

template <typename Key, typename Value>
void mystl::RedBlackTree<Key, Value>::recolor(mystl::RedBlackTree<Key, Value>::Node* curr, mystl::RedBlackTree<Key, Value>::Node::Color color){
    if(!curr)
        return;
    curr->color = color;
}

template <typename Key, typename Value>
bool mystl::RedBlackTree<Key, Value>::isBlack(mystl::RedBlackTree<Key, Value>::Node* curr){
    if(curr && curr->color == Node::Color::Red)
        return false;
    else return true;
}



template <typename Key, typename Value>
bool mystl::RedBlackTree<Key, Value>::empty(){
    return this->_size == 0;
}

template <typename Key, typename Value>
bool mystl::RedBlackTree<Key, Value>::isValid(){
    if (root == nullptr) {
        return true;
    }

    if (root->color != Node::Color::Black) {
        return false;
    }

    return checkBlackHeight(root) != -1;
}

template <typename Key, typename Value>
int mystl::RedBlackTree<Key, Value>::checkBlackHeight(mystl::RedBlackTree<Key, Value>::Node* curr){
    if (curr == nullptr) {
        return 1;
    }

    int leftHeight = checkBlackHeight(curr->left);
    int rightHeight = checkBlackHeight(curr->right);

    if (leftHeight == -1 || rightHeight == -1 || leftHeight != rightHeight) {
        return -1;
    }

    if (curr->color == Node::Color::Red && !isBlack(curr->left) && !isBlack(curr->right)){
        return -1;
    }

    return (curr->color == Node::Color::Black ? leftHeight + 1 : leftHeight);
}
#endif