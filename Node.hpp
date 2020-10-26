#ifndef Node_hpp
#define Node_hpp


class Node{
    public:
        int data;
        Node* next;
        Node* prev;
        Node();
        Node(int data);
        ~Node();
};


#endif
