//
//  stack.cpp
//  Uebung_3
//
//  Created by Paul Rübenich on 26.10.21.
//

#include "stack.hpp"
#include <iostream>

using namespace std;

Stack::Stack(unsigned int depth) {
    if (depth > 0) {
        this->depth = depth;
        // array allokieren mit depth Plätzen
        this->content = new char[depth];
        for (int i = 0; i<depth; i++) {
            this->content[i] = '\0';
        }
        // 0 bedeutet kein Top, weil leer
        this->top = 0;
    }
    else {
        cout << "Stack konnte nicht erstellt werden, da depth nicht groesser 0!" << endl;
    }
}

Stack::~Stack() {
    delete[] content;
    cout << "Inhalt des Stacks wurde gelöscht!" << endl;
}

void Stack::push(char myChar) {
    // wenn Stack voll
    if (top == depth) {
        cout << "Stack voll, " << myChar << " wurde nicht hinzugefügt"<< endl;
        return;
    }
    // Stack nicht voll, also füge hinzu
    content[top] = myChar;
    top++;
    return;
}

// an Stelle top wird eingefügt -> wenn top = 0 dann nicht drin
char Stack::pop() {
    // leerer Stack
    if (top == 0) {
        cout << "Error - Stack ist leer" << endl;
        return '\0';
    }
    // ansonsten lösche top und setze top--
    top--;
    char value = content[top];
    return value;
}


int Stack::isEmpty() {
    if (top == 0) {
        return 1;
    }
    return 0;
}
