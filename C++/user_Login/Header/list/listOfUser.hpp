//
//  listOfUser.hpp
//  UserLogin
//
//  Created by Paul Rübenich on 08.11.21.
//

#ifndef listOfUser_hpp
#define listOfUser_hpp

#include <iostream>
#include "user.hpp"

class userList {
private:
    userList *previous;
    User *content;
    userList *next;
public:
    bool insertUser(string);
    bool deleteUser();
    void printUsers();
    User* getContent();
    userList(string name){
        this->previous = NULL;
        this->content = new User(name);
        this->next = NULL;
    };
};


#endif /* listOfUser_hpp */
