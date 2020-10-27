#ifndef SingleLinked_HPP
#define SingleLinked_HPP

#include "Node.hpp"
#include <iostream>

class SingleLinked{
    private:
        Node* list;

    public:
        static const bool ASCENDING = false;
        static const bool DESCENDING = true;

        //De/Constructors
        SingleLinked();
        SingleLinked(Node* l);
        ~SingleLinked();

        //Data io
        void append(int ndat);
        void push(int ndat);
        void insert(int loc, int ndat);
        void remove(int loc);
        int at(int loc);
        Node* search(int data);

        //Sorting stuff
        void sort(bool desc);

        //Manips
        void reverse();
        Node* pop();
        void sublist(int from, int to);



        //Circular
        void stitch();
        void rip(int loc);
        void shift(int by);

        //Metrics
        int size();
        bool isCircular();
        bool isEmpty();

        friend std::ostream &operator<< (std::ostream &out, const SingleLinked &L){
            Node* ll = L.list;
            while(ll != NULL){
                out << ll->data << " ";
                ll = ll->next;
                if(ll == L.list){break;}
            }
            out << std::endl;
            //out << "list len: " << std::endl;
            return out;
        }
};


#endif