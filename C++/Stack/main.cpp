//
//  main.cpp
//  Uebung3_1
//
//  Created by Paul Rübenich on 15.11.21.
//

#include <iostream>
#include "stack.hpp"

using namespace std;

int main() {
    Stack *s = new Stack(3);
    
    s->push('a');
    s->push('b');
    s->push('c');
    s->push('d');
    
    s->~Stack();
    
    return 0;
}
