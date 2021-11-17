//
//  User.cpp
//  UserLogin
//
//  Created by Paul Rübenich on 08.11.21.
//

#include <iostream>
#include "user.hpp"

string User::getName(){
    return name;
}

string User::getPassword(){
    return password;
}

bool User::changePassword(){
    cout << "Hier kannst du das Passwort von " << name << " ändern" << endl;
    cout << "Gib das aktuelle Passwort ein um fortzufahren: ";
    string inputPassword;
    for (int i = 1; i<4; i++) {
        cin >> inputPassword;
        if (inputPassword == password) {
            break;
        }
        else {
            cout << "Passwort falsch, noch " << 3-i << " Versuche" << endl;
            if (i<3) {
                cout << i+1 << ". Versuch: ";
            }
        }
    }
    if (inputPassword != password) {
        cout << "Passwort konnte nicht geändert werden, da keine Versuche mehr verfügbar sind!" << endl;
        return false;
    }
    else if (inputPassword == password) {
        cout << "Gib das neue Passwort ein: ";
        string newPassword;
        cin >> newPassword;
        password = newPassword;
        cout << "Passwort von " << name << " wurde erfolgreich geändert" << endl;
        return true;
    }
    else {
        return false;
    }
}
