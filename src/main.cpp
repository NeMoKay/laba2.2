#include "iostream"
#include "sequence.hpp"
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "BitSequence.hpp"

int main(){

    BitSequence<char> A;


    A.Append(1);
    A.Append(1);
    A.Append(1);
    A.Append(1);
    A.Append(1);
    A.Append(0);
    A.Append(1);

    cout << A.GetInversions();



    return 0;

}