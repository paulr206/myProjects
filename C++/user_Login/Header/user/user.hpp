//
//  user.hpp
//  UserLogin
//
//  Created by Paul Rübenich on 06.11.21.
//

#ifndef user_hpp
#define user_hpp

#include <iostream>
using namespace std;

class User {
private:
    string password;
    string name;
    
public:
    bool isFirstLogin;
    string getName();
    string getPassword();
    bool changePassword();
    // Constructor
    User(string name){
        this->name = name;
        this->password = "!noPassword!";
    }
};

#endif /* user_hpp */
