#ifndef TRIE
#define TRIE

#include <iostream>
#include <vector>

namespace mystl{
    /// @brief Container to retrieve words in linear time
    class Trie{
        public:
            
            /// @brief Default Trie constructor
            Trie();

            /// @brief Default Trie destructor
            ~Trie();

            /// @brief Insert new word into Trie
            /// @param word Word to insert
            void insert(std::string word);

            /// @brief Remove word from Trie
            /// @param word Word to remove
            /// @return Return true if word was removed
            bool remove(std::string word);

            /// @brief Gets the number of words in the Trie
            unsigned int size();

            /// @brief Searches for word in Trie
            /// @param word Word to search
            /// @return Returns true if word is in Trie
            bool search(std::string word);

            /// @brief Finds all words that start with given prefix
            /// @return Vector with all words that start with given prefix
            std::vector<std::string> startsWith(std::string prefix);

            /// @brief Returns if Trie is empty
            bool empty();

            /// @brief Clears all values in the trie
            void clear();

        private:
            struct Node{
                Node();

                std::vector<Node*> children;
                
                bool terminal;
            };
            
            Node* root;

            unsigned int _size;

            int getIndex(char letter);

            void clearHelper(Node* curr);

            void startsWithHelper(Node* curr, std::string& currentPrefix, std::vector<std::string>& words);

    };
}

mystl::Trie::Node::Node(){
    this->children.resize(52);
    this->children.shrink_to_fit();
    this->terminal = false;
}

mystl::Trie::Trie(){
    this->_size = 0;
    this->root = new Node();
}

mystl::Trie::~Trie(){
    clear();
}

void mystl::Trie::insert(std::string word){
    Node* curr = this->root;

    if(search(word))
        return;
    
    for(unsigned int i = 0; i < word.size(); i++){
        int index = getIndex(word[i]);
        if(index == -1)
            return;
        if(!curr->children[index]){
            Node* newChild = new Node();
            curr->children[index] = newChild;
        }
        curr = curr->children[index];
    }
    
    curr->terminal = true;
    this->_size++;
}

bool mystl::Trie::search(std::string word){
    Node* curr = this->root;

    for(unsigned int i = 0; i < word.size(); i++){
        int index = getIndex(word[i]);

        if(index == -1 || !curr->children[index])
            return false;
        
        curr = curr->children[index];
    }

    return curr->terminal;
}

bool mystl::Trie::remove(std::string word){
    Node* curr = this->root;

    std::vector<Node*> path;
    for(unsigned int i = 0; i < word.size(); i++){
        int index = getIndex(word[i]);

        if(index == -1 || !curr->children[index])
            return false;
        
        path.push_back(curr);
        curr = curr->children[index];
    }

    curr->terminal = false;

    while(!path.empty()){
        Node* curr = path.back();
        path.pop_back();

        bool hasChildren = false;
        for(auto* temp : curr->children){
            if(temp){
                hasChildren = true;
                break;
            }
        }
        if(hasChildren)
            break;
        int index = getIndex(word[path.size()]);
        delete curr->children[index];
    }

    this->_size--;
    return true;
}

unsigned int mystl::Trie::size(){
    return this->_size;
}

bool mystl::Trie::empty(){
    return this->_size == 0;
}

void mystl::Trie::clear(){
    clearHelper(this->root);
    this->_size = 0;
}

void mystl::Trie::clearHelper(mystl::Trie::Node* curr){
    if(!curr)
        return;
    
    for(unsigned int i = 0; i < curr->children.size(); i++){
        clearHelper(curr->children[i]);
    }

    delete curr;
}

std::vector<std::string> mystl::Trie::startsWith(std::string prefix) {
    Node* curr = this->root;

    for (unsigned int i = 0; i < prefix.size(); i++) {
        int index = getIndex(prefix[i]);
        if (index == -1 || !curr->children[index])
            return {};
        
        curr = curr->children[index];
    }

    std::vector<std::string> words;
    std::string currentPrefix = prefix;
    startsWithHelper(curr, currentPrefix, words);

    return words;
}

void mystl::Trie::startsWithHelper(Node* curr, std::string& currentPrefix, std::vector<std::string>& words) {
    if (curr->terminal) {
        words.push_back(currentPrefix);
    }

    for (unsigned int i = 0; i < curr->children.size(); i++) {
        Node* child = curr->children[i];
        if (child) {
            if(i < 26)
                currentPrefix.push_back('a' + i);
            else
                currentPrefix.push_back('A' + i - 26);
            startsWithHelper(child, currentPrefix, words);
            currentPrefix.pop_back();
        }
    }
}


int mystl::Trie::getIndex(char letter){
    if(letter >= 'a' && letter <= 'z')
        return letter - 'a';
    else if(letter >= 'A' && letter <= 'Z') //capitalization matters
        return letter - 'A' + 26;
    return -1;
}


#endif