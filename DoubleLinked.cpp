#include <iostream>
#include "Node.hpp"
#include "DoubleLinked.hpp"

using namespace std;

DoubleLinked::DoubleLinked(){
    this->list = NULL;
    //this->length = -1;
}

DoubleLinked::DoubleLinked(Node* node){
    this->list = new Node();
    this->list->data = node->data;
    this->list->prev = NULL;
    this->list->next = NULL;
}

//Should cover the circular case and linear case
DoubleLinked::DoubleLinked(const DoubleLinked &L){
    if(L.list == NULL){
        this->list = NULL;
    }
    else{
        //Circular Case
        bool circ = ((L.list->prev != NULL )&&(L.list->prev->next == L.list));
        Node* JAIL = L.list;
        if(circ){
            JAIL->prev->next = NULL;
            JAIL->prev = NULL;
        }
        //---------
        Node * ptrCurr = JAIL;
        Node * ptrNew = nullptr;
        Node * newHead = nullptr;
        Node * newPrev = nullptr;

        while(ptrCurr!=nullptr){
            ptrNew = new Node();
            ptrNew->data = ptrCurr->data;
            if (!newHead){
                newHead = ptrNew;
                ptrNew->prev = nullptr;
            }else{
                ptrNew->prev = newPrev;
                newPrev->next = ptrNew; 
                }
                newPrev = ptrNew;
                ptrCurr = ptrCurr->next;
            }
        newPrev->next = nullptr;
        this->list = newHead;
        //Circular case cont.
        if(circ){
            Node* head = this->list;
            Node* temp = this->list;
            while((this->list->prev == NULL) && temp->next != NULL){
                temp = temp->next;
            }
            head->prev = temp;
            temp->next = head;
        }
        }
}


DoubleLinked::~DoubleLinked(){
    delete this->list;
}

void DoubleLinked::push(int ndat){
    Node* newNode = new Node(ndat);
    Node* temp = this->list;
    Node* end = this->list;
    while(end != NULL){
        end = end->next;
        if((end != NULL) && (end->next == this->list)){
            end->next = newNode;
            temp->prev = newNode;
            break;}
    }
    newNode->next = temp;
    newNode->prev = end;
    if(this->list != NULL)
        temp->prev = newNode;
    this->list = newNode;
}

void DoubleLinked::append(int ndat){
    Node* newNode = new Node(ndat);
    Node* iter = this->list;
    Node* head = this->list;
    while((iter->next != NULL) && (iter->next != head)){
        iter = iter->next;
    }
    if(iter->next == head){
        newNode->next = head;
    }
    newNode->prev = iter;
    iter->next = newNode;
}

void DoubleLinked::insert(int loc, int ndat){
    if(list == NULL || loc == 0){
        push(ndat);
        return;
    }
    else{
    Node* newNode = new Node(ndat);
    Node* iter = this->list;
    for(int i = 0; i < loc-1; i++){
        iter = iter->next;
    }
    newNode->next = iter->next;
    newNode->prev = iter->prev;
    iter->next = newNode;
    }
}

void DoubleLinked::replace(int loc, int ndat){
    if(list == NULL){
        push(ndat);
        return;
    }
    Node* iter = this->list;
    for(int i = 0; i < loc; i++){
        iter = iter->next;
    }
    iter->data = ndat;

}

void DoubleLinked::remove(int loc){
    Node* prev = NULL;
    Node* curr = NULL;
    if(this->list == NULL){
        return;
    }
    //Only modify length if not circular, otherwise it doesnt matter
    if(loc > length() && !isCircular()){loc = loc%length();}

    if(loc == 0){
        Node* prev = this->list->prev;
        if(prev != NULL){
            prev->next = this->list->next;
        }
        this->list->next->prev = prev;
        this->list = this->list->next;
        return;
    }


    prev = this->list;
    curr = this->list->next;
    for(int i = 0;i < loc - 1; i++){
        prev = prev->next;
        curr = curr->next;
    }
    if(curr!=NULL)
        curr->prev = prev->prev;
    if(prev->prev != NULL){
        prev->prev->next = curr;
    }
    
}

Node* DoubleLinked::search(int data){
    Node* temp = this->list;
    while(temp!=NULL){
        //circular case
        if(temp->next==this->list)
            break;
        if(temp->data == data){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void DoubleLinked::stitch(){
    //replace NULLs with the locations of the corresponding elements
    Node* iter = this->list;
    Node* head = this->list;
    while(iter!=NULL){
        iter = iter->next;
        if(iter->next == NULL){break;}
    }
    head->prev = iter;
    iter->next = head;
}

void DoubleLinked::rip(int loc){
    //Cant rip non-circular list
    if(isCircular() == false){
        return;
    }
    //0 is a special case
    if(loc == 0){
        this->list->prev->next = NULL;
        this->list->prev = NULL;
        return;
    }
    //All other locations
    Node* iter = this->list;
    Node* cursor = NULL;
    for(int i = 0; i < loc; i++){
        cursor = iter;
        iter = iter->next;
    }
    cursor->next = NULL;
    iter->prev = NULL;
    this->list = iter;
}

void DoubleLinked::shift(int i){
    //Its easiers to connect everything
    //move to the right location
    // and then break the circle
    if(!isCircular()){
        stitch();
        rip(i);
    }
    else{
        rip(i);
        stitch();
    }
}

void DoubleLinked::sort(bool desc){
    bool needFix = false;
    if(isCircular()){rip(0); needFix = true;}
    //this is like, my third time trying to make this work
    //iterate through swapping data values
    //if the swap condition is NOT met increment a counter
    //if the counter is equal to the length of the list, break.
    int counter = 0;
    int buf;
    Node* temp = NULL;
    while(1){
        counter = 0;
        temp = this->list; //start at beginning after each list traversal
        while(temp != NULL){
            //SWAP
            if((temp->next != NULL)&&(temp->data > temp->next->data)){
                buf = temp->data;
                temp->data = temp->next->data;
                temp->next->data = buf;
            }
            //NOT
            else{
                counter++;
            }
            temp = temp->next; //swap or not, still iterate
        }
        if(counter == length()){break;}
    }
    //reverse condition // true is descending
    if(desc){reverse();}
    if(needFix){stitch();}
}

int DoubleLinked::length(){
    Node* temp = this->list;
    int iter = 0;
    while(temp!=NULL){
        if(temp->next==this->list)
            break;
        temp = temp->next;
        iter++;
    }
    return iter;
}

bool DoubleLinked::isCircular(){
    Node* temp = this->list;
    Node* head = this->list;
    while(temp->next != NULL){
        temp = temp->next;
        if(temp == head){return true;}
    }
    return false;
}

bool DoubleLinked::isEmpty(){
    return (this->list == NULL);
}

Node* DoubleLinked::Get(){return this->list;}

int DoubleLinked::getMax(){
    Node* temp = this->list;
    int buf = temp->data;
    while((temp!=NULL)&&(temp->next!=this->list)){
        if(temp->data > buf){
            buf = temp->data;
        }
        temp = temp->next;
    }
    return buf;
}

int DoubleLinked::getMin(){
    Node* temp = this->list;
    int buf = temp->data;
    while((temp!=NULL)&&(temp->next!=this->list)){
        if(temp->data < buf){
            buf = temp->data;
        }
        temp = temp->next;
    }
    return buf;
}

void DoubleLinked::reverse(){
    bool needsFix = false;
    if(isCircular()){rip(0);needsFix=true;}

    //This part only works with linear lists
    //was easier to rip and stitch than make changes to the logic
    Node* temp = NULL;
    Node* curr = this->list;
    while(curr != NULL){ // <------ would've run forever on circular list
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }
    if(temp!=NULL)
        this->list = temp->prev;

    if(needsFix){stitch();}
}