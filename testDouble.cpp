#include <iostream>
#include "Node.hpp"
#include "DoubleLinked.hpp"

using namespace std;

int main(){
    DoubleLinked dl;
    dl.push(0);
    dl.push(0);
    dl.push(0);
    dl.push(0);
    dl.insert(0,3);
    dl.insert(5,7); //Cannot be outside scope - WILL cause sigsegv
    dl.stitch(); //Converts to circular list
    dl.append(35);
    dl.shift(1);
    dl.replace(0,12);
    
    DoubleLinked F = dl;
    dl.stitch(); //needed after the copy to maintain dl as circular list
    
    F.push(-1);
    F.append(99);
    F.replace(0,222);
    F.insert(0,111);
    //F.rip(6); //Unlink circular list at 6
    cout << F;
    cout << dl.isCircular() << endl;
}