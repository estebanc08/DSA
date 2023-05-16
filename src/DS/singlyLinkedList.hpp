#ifndef SINGLY_LINKED_LIST
#define SINGLY_LINKED_LIST

#include <iostream>

namespace mystl{
    /// @brief Singly Linked List with head and tail pointers
    template <class T> 
    class SinglyLinkedList{
        public:
            /// @brief Default constructor
            SinglyLinkedList(){};

            /// @brief Default linked list destructor
            ~SinglyLinkedList();

            /// @brief get the size of the list
            /// @return returns an unsigned integer value with the size of the list
            unsigned int size();

            /// @brief Push data to end of the list
            /// @param data 
            void push_back(T data);

            /// @brief Creates a new head of the list
            /// @param data 
            void push_front(T data);

            /// @brief Insert  data into specified position if that position within bounds of list
            /// @param data 
            /// @param pos 
            void insert(T data, unsigned int pos);

            /// @brief Remove an item from the list at the given position if it exists
            /// @param pos 
            void removeAt(unsigned int pos);

            /// @brief Iterate the list and print all values
            void printList();

            /// @brief Search for a value in the list, will only return first value
            /// @param data 
            /// @return retrun true if value found
            bool search(T data);

            /// @brief Returns reference to the value at the given position if valid, otherwise throws error
            /// @param pos 
            /// @return 
            T& operator[](unsigned int pos);

            /// @brief creates deep copy of list
            /// @return new List
            SinglyLinkedList& operator=(const SinglyLinkedList& RHS);

            /// @brief instantiates new list
            /// @return new List
            SinglyLinkedList(const SinglyLinkedList& RHS);

            /// @brief clears all data from the list and resets size to 0
            void clear();

            /// @brief Returns the value at the given position if valid, otherwise throws error
            /// @param pos 
            /// @return value at that position
            T at(unsigned int pos);

            /// @brief Returns if the list is empty
            /// @return 
            bool empty();


        private:
            struct Node{
                T data;
                Node* next;
                Node(T _data) : data(_data) {next = nullptr;};
            };
            unsigned int _size = 0;
            Node* head = nullptr;
            Node* tail = nullptr;
    };
}

template<typename T>
unsigned int mystl::SinglyLinkedList<T>::size(){
    return this->_size;
}

template<typename T>
void mystl::SinglyLinkedList<T>::push_front(T data){
    this->_size++;
    if(head){
        Node* newHead = new Node(data);
        newHead->next = this->head;
        this->head = newHead;
    }
    else{
        Node* head = new Node(data);
        this->head = head;
    }
}

template<typename T>
void mystl::SinglyLinkedList<T>::push_back(T data){
    if(!head){
        push_front(data);
        this->tail = this->head;
        return;
    }

    this->_size++;
    Node* newTail = new Node(data);
    tail->next = newTail;
    tail = newTail;
    return;
}

template<typename T>
void mystl::SinglyLinkedList<T>::insert(T data, unsigned int pos){
    if(pos == 0){
        push_front(data);
        return;
    }
    if(pos == _size){
        push_back(data);
        return;
    }
    if(pos > _size){
        throw std::out_of_range("Invalid index");
    }

    Node* temp = head;
    for(unsigned int i = 0; i < pos-1; i++){
        temp = temp->next;
    }
    Node* newNode = new Node(data);
    Node* newNext = temp->next;
    temp->next = newNode;
    newNode->next = newNext;
    this->_size++;
}


template<typename T>
mystl::SinglyLinkedList<T>::~SinglyLinkedList(){
    clear();
}

template<typename T>
void mystl::SinglyLinkedList<T>::printList(){
    Node* temp = head;
    while(temp){
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << "\n";
}

template<typename T>
void mystl::SinglyLinkedList<T>::removeAt(unsigned int pos){
    if(pos >= this->_size || this->_size == 0)
        throw std::out_of_range("Invalid index");
    this->_size--;
    Node* temp = head;
    if(pos == 0){
        temp = temp->next;
        Node* currHead = head;
        head = temp;
        delete currHead;
        return;
    }

    for(unsigned int i = 0; i < pos-1; i++){
        temp = temp->next;
    }
    Node* newNext = temp->next->next;
    delete temp->next;
    temp->next = newNext;
    if(!newNext){
        this->tail = temp;
    }
}

template <typename T>
bool mystl::SinglyLinkedList<T>::search(T data){
    Node* temp = head;
    while(temp){
        if(temp->data == data)
            return true;
        temp = temp->next;
    }
    return false;
}

template <typename T>
T mystl::SinglyLinkedList<T>::at(unsigned int pos){
    return T(operator[](pos));
}

template <typename T>
T& mystl::SinglyLinkedList<T>::operator[](unsigned int pos){
    if(pos >= this->_size)
        throw std::out_of_range("Invalid index");
    Node* temp = head;
    for(unsigned int i = 0; i < pos; i++){
        temp = temp->next;
    }
    return temp->data;
}

template <typename T>
mystl::SinglyLinkedList<T>& mystl::SinglyLinkedList<T>::operator=(const mystl::SinglyLinkedList<T>& RHS){
    this->_size = RHS._size;
    Node* oldTemp = RHS.head;
    this->head = nullptr;
    this->tail = nullptr;
    if(this->_size == 0)
        return (*this);
    Node* newHead = new Node(oldTemp->data);
    Node* temp = newHead;
    oldTemp = oldTemp->next;
    while(oldTemp){
        Node* curr = new Node(oldTemp->data);
        temp->next = curr;
        oldTemp = oldTemp->next;
        temp = curr;
    }
    this->tail = temp;
    this->head = newHead;
    return (*this);
}

template <typename T>
mystl::SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& RHS){
    this->_size = RHS._size;
    Node* oldTemp = RHS.head;
    this->head = nullptr;
    if(this->_size == 0)
        return;
    Node* newHead = new Node(oldTemp->data);
    Node* temp = newHead;
    oldTemp = oldTemp->next;
    while(oldTemp){
        Node* curr = new Node(oldTemp->data);
        temp->next = curr;
        oldTemp = oldTemp->next;
        temp = curr;
    }
    this->tail = temp;
    this->head = newHead;
}

template <typename T>
void mystl::SinglyLinkedList<T>::clear(){
    if(!head)
        return;
    
    Node* temp = head;
    while (temp) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
    this->head = nullptr;
    this->tail = nullptr;
}

template <typename T>
bool mystl::SinglyLinkedList<T>::empty(){
    return this->_size == 0;
}

#endif