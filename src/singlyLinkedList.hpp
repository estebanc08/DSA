#ifndef SINGLY_LINKED_LIST
#define SINGLY_LINKED_LIST

#include <iostream>


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


    private:
        struct Node{
            T data;
            Node* next;
            Node(T _data) : data(_data) {next = nullptr;};
        };
        unsigned int _size = 0;
        Node* head = nullptr;
};

template<typename T>
unsigned int SinglyLinkedList<T>::size(){
    return this->_size;
}

template<typename T>
void SinglyLinkedList<T>::push_front(T data){
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
void SinglyLinkedList<T>::push_back(T data){
    if(!head){
        push_front(data);
        return;
    }

    this->_size++;
    Node* temp = head;
    while(temp && temp->next){
        temp = temp->next;
    }
    Node* newTail = new Node(data);
    temp->next = newTail;
    return;
}

template<typename T>
void SinglyLinkedList<T>::insert(T data, unsigned int pos){
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
SinglyLinkedList<T>::~SinglyLinkedList(){
    clear();
}

template<typename T>
void SinglyLinkedList<T>::printList(){
    Node* temp = head;
    while(temp){
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << "\n";
}

template<typename T>
void SinglyLinkedList<T>::removeAt(unsigned int pos){
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
}

template <typename T>
bool SinglyLinkedList<T>::search(T data){
    Node* temp = head;
    while(temp){
        if(temp->data == data)
            return true;
        temp = temp->next;
    }
    return false;
}

template <typename T>
T SinglyLinkedList<T>::at(unsigned int pos){
    return T(operator[](pos));
}

template <typename T>
T& SinglyLinkedList<T>::operator[](unsigned int pos){
    if(pos >= this->_size)
        throw std::out_of_range("Invalid index");
    Node* temp = head;
    for(unsigned int i = 0; i < pos; i++){
        temp = temp->next;
    }
    return temp->data;
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& RHS){
    this->_size = RHS._size;
    Node* oldTemp = RHS.head;
    this->head = nullptr;
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
    this->head = newHead;
    return (*this);
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& RHS){
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
    this->head = newHead;
}

template <typename T>
void SinglyLinkedList<T>::clear(){
    if(!head)
        return;
    
    Node* temp = head;
    while (temp) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
    head = nullptr;
}

#endif