#include <iostream>
#include "Node.hpp"

using namespace std;

//Space to define functions of a node if needed
//UPDATE:: It was needed
Node::Node(){
    this->data = 0;
    this->next = NULL; // Broke the code in hpp file
    this->prev = NULL; // Broke the code in hpp file
}
Node::Node(int data){
    this->data = data;
    this->next = NULL; // Broke the code in hpp file
    this->prev = NULL; // Broke the code in hpp file
}

Node::~Node(){
    next = NULL;
    prev = NULL;
    //data = NULL;
}