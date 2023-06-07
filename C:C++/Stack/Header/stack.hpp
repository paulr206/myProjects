//
//  stack.hpp
//  Uebung_3
//
//  Created by Paul Rübenich on 26.10.21.
//

#ifndef stack_hpp
#define stack_hpp

class Stack {
private:
    unsigned int depth; // Tiefe des Stacks
    char *content;      // Inhalt des Stacks
    unsigned int top;   // Index des obersten freien Elements
public:
    Stack* create_stack(unsigned int);
    Stack(unsigned int);
    ~Stack();
    void push(char);
    char pop();
    int isEmpty();
    void destroy_stack();
};


#endif /* stack_hpp */
