#include "main.hpp"

int main(){

    SinglyLinkedList<int> list;
    for(unsigned int i = 0; i < 10; i++){
        list.push_front(i);
    }
    for(unsigned int i = 10; i < 20; i++){
        list.push_back(i);
    }
    for(unsigned int i = 0; i < 20; i+=2){
        list.insert(i*20, i);
    }
    list.removeAt(29);
    list.removeAt(0);
    SinglyLinkedList<int> newList;
    newList = list;
    newList[1] = 30;
    SinglyLinkedList<int> copyList = newList;
    copyList[1] = 1000;
    copyList.clear();
    copyList.push_back(50);
    list.printList();
    newList.printList();
    copyList.printList();
    std::cout << list.at(0) << "\n";
    return 0;

}
    // sf::VideoMode fullScreen = sf::VideoMode::getDesktopMode();
    // sf::RenderWindow window(fullScreen, "Data structures");
    // sf::Event event;
    // while(window.isOpen()){
    //     while(window.pollEvent(event)){
    //         if(event.type == sf::Event::Closed){
    //             window.close();
    //             break;
    //         }
    //     }
    //     window.clear();
    //     window.display();
    // }