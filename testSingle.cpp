#include <iostream>
#include <fstream>
#include "Node.hpp"
#include "SingleLinked.hpp"

using namespace std;

int main(){
    SingleLinked list = SingleLinked();
    list.stitch(); // Cannot stitch empty list
    list.append(0);
    list.stitch();
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);

    list.push(-1);
    list.push(-2);

    list.insert(0, 888);
    list.insert(2, 777);
    list.insert(1, 333);
    
    list.remove(1);
    list.remove(0);
    list.remove(80);
    
    cout << list;
    cout << list.isCircular() << endl;
    
    SingleLinked listPop(list.pop());

    cout << list.isCircular() << endl;
    list.reverse();
    
    SingleLinked l = list;
    
    cout << list;
    cout << l.isCircular() << endl;
    
}
