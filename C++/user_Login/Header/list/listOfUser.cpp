//
//  listOfUser.cpp
//  UserLogin
//
//  Created by Paul Rübenich on 08.11.21.
//

#include "listOfUser.hpp"
#include "user.hpp"


User* userList::getContent(){
    return this->content;
}

void userList::printUsers(){
    userList *temp = this;
    for (int i = 0; i<4; i++) {
        cout << temp->getContent()->getName() << endl;
        temp = temp->next;
    }
}


bool userList::insertUser(string name){
    userList *temp = this;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    userList *nextElement = new userList(name);
    temp->next = nextElement;
    nextElement->previous = this;
    nextElement->next = NULL;
    return true;
}


bool userList::deleteUser(){
    userList *temp = this;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    
    delete temp->next;
    temp->next = NULL;
    return true;
}

