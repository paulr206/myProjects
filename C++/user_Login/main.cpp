//
//  main.cpp
//  UserLogin
//
//  Created by Paul Rübenich on 06.11.21.
//

#include <iostream>
#include "user.hpp"
#include "listOfUser.hpp"

using namespace std;


int main() {
    
    userList users("Test");
    
    string arr[] = {
        "Paul",
        "Lisa",
        "Tim"
    };
    
    for (int i = 0; i < (sizeof(arr)/sizeof(arr[0])); i++) {
        users.insertUser(arr[i]);
    }
    
    users.printUsers();
    
    return 0;
}
