





#include <iostream>
#include "Dynamic_Array.hpp"
#include "LinkedList.hpp"



using namespace std;


int main(){
    
    int size = 5;
    int B[5] ={1, 2, 3, 4, 5};
    LinkedList List_int(B, 5);


    LinkedList<int> *A;

    A = List_int.GetSubList(1,3);
    A->show();



    return 0;
}