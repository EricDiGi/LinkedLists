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
    //dl.replace(0,-1);
    // dl.replace(1,1);
    //dl.append(5);
    dl.insert(0,3);
    dl.insert(5,7); //Cannot be outside scope - WILL cause sigsegv
    dl.stitch(); //Converts to circular list
    dl.append(35);
    //dl.push(36);
    //dl.push(36);
    //dl.push(36);
    //dl.rip(3); //Converts to non-circular list
    //dl.shift(1);
    //dl.replace(0,12);
    DoubleLinked F = dl;
    
    F.push(-1);
    F.append(99);
    cout << F;
    cout << F.isCircular() << endl;
}