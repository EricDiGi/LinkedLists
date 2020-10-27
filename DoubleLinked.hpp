#ifndef DoubleLinked_HPP
#define DoubleLinked_HPP

#include <iostream>
#include "Node.hpp"

class DoubleLinked{
    private:
        Node* list;
    public:
        static const bool ASCENDING = false;
        static const bool DESCENDING = true;
        DoubleLinked();
        DoubleLinked(Node* node);
        DoubleLinked(const DoubleLinked &L);
        ~DoubleLinked();

        //List manips
        void push(int ndat);
        void append(int ndat);
        void replace(int loc, int ndat);
        void insert(int loc, int ndat);
        void remove(int loc);
        Node* search(int data);

        //List transformations
        void stitch(); //Converts to circular list
        void rip(int loc); //Will only rip circular lists
        void shift(int i);

        //Sorting Funcs
        void sort(bool desc);

        //Metrix
        bool isCircular();
        bool isEmpty();
        int length();
        int getMax();
        int getMin();


        //Just because
        void reverse(); //Supports circular
        Node* Get();

        friend std::ostream &operator<< (std::ostream &out, const DoubleLinked &L){
            Node* ll = L.list;
            Node* head = L.list;
            while(ll != NULL){
                out << ll->data << " ";
                ll = ll->next;
                if(ll == head){break;} //circular case
            }
            out << std::endl;
            //out << "list len: " << std::endl;
            return out;
        }
};

#endif