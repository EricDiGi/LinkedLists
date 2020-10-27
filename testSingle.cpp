#include <iostream>
#include <fstream>
#include "Node.hpp"
#include "SingleLinked.hpp"

using namespace std;

int main(){
    SingleLinked list = SingleLinked();
    list.stitch(); // Cannot stitch empty list - AKA this line does nothing
    list.append(0);
    list.stitch();
    /* If ^ I stitch here
    then every following function should
    maintain the circular shape by the end of the program
    WITHOUT needed to stitch after every function*/
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);

    list.push(-1);
    list.push(-2);

    list.insert(0, 888);
    list.insert(2, 777);
    list.insert(1, 333);
    
    //list.remove(1);
    //list.remove(0);
    //list.remove(80);
    
    cout << list;
    
    SingleLinked listPop(list.pop());
    list.reverse();
    
    cout << "Search returns: " << list.search(111)->data << endl;
    //Invalid search returns new Node()

    list.sort(SingleLinked::DESCENDING);
    
    cout << list;
    //cout << l.isCircular() << endl;
    
}
