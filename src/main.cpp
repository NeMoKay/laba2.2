





#include <iostream>
#include "sequence.hpp"



using namespace std;


int main(){
    
    int size = 5;
    int sss[5] ={1, 2, 3, 4, 5};

    ImmutableArraySequence<int> A(sss,5);
    Sequence<int>* B;

    
    B = A.Append(10);


    A.show();

    cout << endl;

    B->show();
    

    

    
    

    return 0;
}