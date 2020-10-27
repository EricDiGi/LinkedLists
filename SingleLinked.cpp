#include <iostream>
#include "SingleLinked.hpp"
#include "Node.hpp"

using namespace std;

/*##################################
    Constructors & Deconstructors
####################################*/

SingleLinked::SingleLinked(){
    this->list = NULL;
}

SingleLinked::SingleLinked(Node* l){
    this->list = l;
}

SingleLinked::~SingleLinked(){
    delete this->list;
}

/*##################################
               Data IO
####################################*/

void SingleLinked::append(int ndat){
    bool needFix = isCircular();
    if(needFix){rip(0);}
    Node* last = list;

    //build node to append
    Node* newNode = new Node();
    newNode->data = ndat;
    newNode->next = NULL;

    //will be first in list
    if(list == NULL){
        list = newNode;
        return;
    }
    //else
    //traverse to last node
    //assign this node to last pos
    while(last->next != NULL){
        last = last->next;
    }
    last->next = newNode;
    if(needFix){stitch();}
    return;
}

void SingleLinked::push(int ndat){
    bool needFix = isCircular();
    if(needFix){rip(0);}
    Node* last = this->list;

    Node* newNode = new Node();
    newNode->data = ndat;
    newNode->next = this->list;
    last = newNode;

    this->list = last;
    if(needFix){stitch();}
}

void SingleLinked::insert(int loc, int ndat){
    bool needFix = isCircular();
    if(needFix){rip(0);}
   if(loc == 0){
		push(ndat);
        if(needFix){stitch();}
		return;
	}

	Node* temp = list;
	Node* newNode = new Node(ndat);
	for(int i = 0; i < loc-1; i++){
		temp = temp->next;
	}
	newNode->next = temp->next;
	temp->next = newNode;
    if(needFix){stitch();}
	return;
}

void SingleLinked::remove(int loc){
    bool needFix = isCircular();
    //rip(0);
	if(this->list == NULL)
        return;

    Node* temp = NULL;
    Node* cursor = NULL;

    if(loc == 0){
        this->list = this->list->next;
        temp = this->list;
        while(temp->next != NULL){
            if(temp->next->next == this->list){break;}
            temp = temp->next;
        }
        if(needFix){cursor = this->list;}
        temp->next = cursor;
        return;
    }

    temp = this->list;
	cursor = this->list->next;
    if(loc > size()-1){loc = size();}
	for(int i = 0; i < loc-1; i++){
		temp = temp->next;
        cursor = cursor->next;
	}
	temp->next = cursor->next;
    if(needFix){stitch();}
	return;

}

int SingleLinked::at(int loc){
    if((list == NULL) || (loc > size()-1))
        return -1111;
    if(loc == 0)
        return list->data;

    Node* temp = list;
    for(int i = 0; i < loc; i++){
        temp = temp->next;
    }
    return temp->data;
}

Node* SingleLinked::search(int data){
    if(isEmpty()){return new Node();}
    Node* temp = this->list;
    while(temp!= NULL){
        if(temp->data == data){
            return temp;
        }
        temp = temp->next;
        if(temp == this->list){
            break;
        }
    }
    return new Node();
}

/*##################################
                Sorting
####################################*/

void SingleLinked::sort(bool desc){
    if(isEmpty() || size() == 1){return;}

    bool circ = isCircular();
    if(circ){rip(0);}

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
        if(counter == size()+1){break;}
    }
    if(desc){reverse();}
    if(circ){stitch();}
}


/*##################################
                Manips
####################################*/

void SingleLinked::reverse(){
    bool needFix = isCircular();
    if(needFix){rip(0);}
    Node* curr = list;
    Node* prev = NULL;
    Node* next = NULL;

    while(curr != NULL){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    list = prev;
    if(needFix){stitch();}
    //Look idk either but it works
}

Node* SingleLinked::pop(){
    Node* out = new Node();
    Node* cursor = NULL;
    if(this->list == NULL)
        return out;

    if(size()-1 <= 0){
        this->list = NULL;
        return out;
    }

    bool circ = isCircular();
    if(circ){cursor = this->list->next;}

    Node* temp = this->list;
    for(int i = 0; i < size()-1; i++){
        temp = temp->next;
        cursor = circ ? cursor->next : NULL;
    }
    out->data = temp->next->data;
    out->next = NULL;
    temp->next = circ ? cursor->next : NULL;
    return out;
}
//COPY ORIGINAL FIRST
//Does not return sublist, becomes sublist
void SingleLinked::sublist(int from, int to){
    Node* temp = list;
    for(int i = 0; i < to; i++){
        temp = temp->next;
    }
    temp->next = NULL;
    for(int i = 0; i < from; i++){
        list = list->next;
    }
}

/*##################################
               Circular
###################################*/

void SingleLinked::stitch(){
    if(this->list == NULL){return;}
    if(isCircular()){return;} //shouldn't stitch an already circular list
    Node* temp = this->list;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = this->list;
}

void SingleLinked::rip(int loc){
    //Cant operate on NULL or nonCircular list
    if(this->list == NULL){return;}
    if(!isCircular()){return;}
    //Special case
    if(loc == 0){
        Node* temp = this->list;
        while(temp->next!=this->list){
            temp = temp->next;
        }
        temp->next = NULL;
        return;
    }
    //generic case
    Node* temp = this->list;
    Node* cursor = temp->next;
    for(int i = 0; i < loc-1; i++){
        temp = temp->next;
        cursor = cursor->next;
    }
    temp->next = NULL;
    this->list = cursor;
}

void SingleLinked::shift(int by){
    if(this->list == NULL){return;}
    if(isCircular()){
        rip(by);
        stitch();
    }
    else{
        stitch();
        rip(by);
    }
}

/*##################################
                Metrics
####################################*/

int SingleLinked::size(){
    Node* temp = this->list;
    Node* head = this->list;
    int iter = 0;
    while(temp->next != NULL){
        if(temp->next == head){break;}
        iter++;
        temp = temp->next;
    }
    return iter;
}

bool SingleLinked::isCircular(){
    Node* head = this->list;
    Node* temp = this->list;
    while(temp != NULL){
        if(temp->next == head){return true;}
        temp = temp->next;
    }
    return false;
}

bool SingleLinked::isEmpty(){
    return (this->list == NULL);
}


