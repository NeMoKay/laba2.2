





#include <iostream>
#include "sequence.hpp"



using namespace std;



int main(){
    
    BitSequence<int> A;

    A.Append(1);
    A.Append(1);
    A.Append(1);
    A.Append(0);
    A.Append(1);
    A.Append(0);
    A.Append(0);
    A.Append(0);
    A.Append(0);
    A.Append(0);

    cout << (A[7] ^ A[4]) << endl;
    
    // A.show();
    return 0;
}