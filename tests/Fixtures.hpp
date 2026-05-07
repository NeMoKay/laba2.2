#include <gtest/gtest.h>
#include "BitSequence.hpp"
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "bit.hpp"
using namespace std;



class Dynamic_Array_Fixture : public testing::Test{
protected:
    int data_int[5] ={42, 52, 69, 67, 228};
    const char* data_str[5] ={"красный", "оранжевый", "желтный", "зеленый", "голубой"};

    DynamicArray<int> *array_int;
    DynamicArray<const char*> *array_str;
    
    void SetUp() override{
        array_int = new DynamicArray{data_int, 5};
        array_str = new DynamicArray{data_str, 5};
    }

    void TearDown() override{
        delete array_int;
        delete array_str;
    }
};



class LinkedList_Fixture : public testing::Test{
protected:
    int data_int[5] ={42, 52, 69, 67, 228};
    const char* data_str[5] ={"красный", "оранжевый", "желтный", "зеленый", "голубой"};

    LinkedList<int> *List_int;
    LinkedList<const char*> *List_str;

    void SetUp() override{
        List_int = new LinkedList<int>{data_int, 5};
        List_str = new LinkedList<const char*>{data_str, 5};
    }
    
    void TearDown() override{
        delete List_int;
        delete List_str;
    }

};


class Bit_Fixture : public testing::Test{
protected:
    Bit<char> bit8;
    Bit<int> bit32;

    void SetUp() override{
        bit8 = Bit<char>(0b01010101);
        bit32 = Bit<int>(0b00110011001100110011001100110011);
    }
};


class ArraySequence_Fixture : public testing::Test{
protected:
    int data_int[5] ={42, 52, 69, 67, 228};
    const char* data_str[3] ={"первый", "второй", "третий"};

    ArraySequence<int> *seq_int;
    ArraySequence<const char*> *seq_str;

    void SetUp() override{
        seq_int = new ArraySequence<int>{data_int, 5};
        seq_str = new ArraySequence<const char*>{data_str, 3};
    }

    void TearDown() override{
        delete seq_int;
        delete seq_str;
    }
};


class ListSequence_Fixture : public testing::Test{
protected:
    int data_int[5] ={42, 52, 69, 67, 228};
    const char* data_str[3] ={"первый", "второй", "третий"};

    ListSequence<int> *seq_int;
    ListSequence<const char*> *seq_str;

    void SetUp() override{
        seq_int = new ListSequence<int>{data_int, 5};
        seq_str = new ListSequence<const char*>{data_str, 3};
    }

    void TearDown() override{
        delete seq_int;
        delete seq_str;
    }
};


class BitSequence_Fixture : public testing::Test{
protected:
    Bit<char> data_bits[8] = {
        Bit<char>(1), Bit<char>(0), Bit<char>(1), Bit<char>(0),
        Bit<char>(1), Bit<char>(0), Bit<char>(1), Bit<char>(0)
    };

    MutableBitSequence<char> *Sequence;

    void SetUp() override{
        Sequence = new MutableBitSequence<char>{data_bits, 8};
    }

    void TearDown() override{
        delete Sequence;
    }
};




inline int double_val(int x){
     return x * 2; 
}
inline bool is_big(int x){ 
    return x > 60; 
}
inline int sum_func(int acc, int x){ 
    return acc + x; 
}
