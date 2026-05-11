#include "iostream"
#include "sequence.hpp"
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "BitSequence.hpp"

int main(){
    int sss[5] ={1, 2,3,4,5};


    ArraySequence<int> A(sss, 5);

    A.InsertAt(12, 10);







    return 0;

}