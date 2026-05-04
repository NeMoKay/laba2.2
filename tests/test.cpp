#include <gtest/gtest.h>
#include "iostream"
#include "sequence.hpp"
using namespace std;


//-----------------------------------БЛОК Dynamic_Array---------------------------------------
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

//тесты ддя Dynamic_Array---------------------------------------
//Тесты констукторов--------------------------------------------

TEST_F(Dynamic_Array_Fixture, Defoult_Constructor_invalid_argument){
    DynamicArray<int> arr;
    EXPECT_THROW(arr.Get(0), invalid_argument);
}

TEST_F(Dynamic_Array_Fixture, SizeConstructor){
    DynamicArray<int> arr(3);

    arr.Set(0, 10);
    arr.Set(2, 30);

    EXPECT_EQ(arr.Get(0), 10);
    EXPECT_EQ(arr.Get(2), 30);
}

TEST_F(Dynamic_Array_Fixture, SizeConstructor_invalid_argument){
    EXPECT_THROW(DynamicArray<int>(0), invalid_argument);
    EXPECT_THROW(DynamicArray<int>(-5), invalid_argument);
}


TEST_F(Dynamic_Array_Fixture, ArrayConstructor){
    int data[3] ={1, 2, 3};
    DynamicArray<int> arr(data, 3);

    EXPECT_EQ(arr.Get(0), 1);
    EXPECT_EQ(arr.Get(1), 2);
    EXPECT_EQ(arr.Get(2), 3);
}

TEST_F(Dynamic_Array_Fixture, ArrayConstructor_invalid_argument){
    EXPECT_THROW(DynamicArray<int>(nullptr, 5), invalid_argument);
}

TEST_F(Dynamic_Array_Fixture, CopyConstructor){
    DynamicArray<int> copy(*array_int);

    EXPECT_EQ(copy.Get(0), 42);
    EXPECT_EQ(copy.Get(2), 69);
    EXPECT_EQ(copy.Get(4), 228);

    copy.Set(0, 999);
    EXPECT_EQ(array_int->Get(0), 42);
}

//Методы--------------------------------------------------------

TEST_F(Dynamic_Array_Fixture, GET){
    EXPECT_EQ(array_int->Get(0), 42);
    EXPECT_EQ(array_int->Get(2), 69);
    EXPECT_EQ(array_int->Get(4), 228);

    EXPECT_STREQ(array_str->Get(0), "красный");
    EXPECT_STREQ(array_str->Get(3), "зеленый");
    EXPECT_STREQ(array_str->Get(4), "голубой");
}

TEST_F(Dynamic_Array_Fixture, GET_invalid_argument){
    EXPECT_THROW(array_int->Get(-1), invalid_argument);
    EXPECT_THROW(array_int->Get(100), invalid_argument);
}


TEST_F(Dynamic_Array_Fixture, SET){
    array_int->Set(4, 4);
    array_str->Set(4, "розовый");

    EXPECT_EQ(array_int->Get(4), 4);
    EXPECT_STREQ(array_str->Get(4), "розовый");
}
TEST_F(Dynamic_Array_Fixture, SET_invalid_argument){
    EXPECT_THROW(array_int->Set(-1, 42), invalid_argument);
    EXPECT_THROW(array_int->Set(100, 42), invalid_argument);
}

TEST_F(Dynamic_Array_Fixture, Resize_positive){
    array_int->Resize(7);

    EXPECT_EQ(array_int->Get(0), 42);
    EXPECT_EQ(array_int->Get(2), 69);
    EXPECT_EQ(array_int->Get(4), 228);
}

TEST_F(Dynamic_Array_Fixture, Resize_negative){
    array_int->Resize(3);

    EXPECT_EQ(array_int->Get(0), 42);
    EXPECT_EQ(array_int->Get(2), 69);
    EXPECT_THROW(array_int->Get(3), invalid_argument);
}


TEST_F(Dynamic_Array_Fixture, Resize_ToZero){
    array_int->Resize(0);

    EXPECT_THROW(array_int->Get(0), invalid_argument);
}




TEST_F(Dynamic_Array_Fixture, Resize_invalid_argument){
    EXPECT_THROW(array_int->Resize(-1), invalid_argument);
}

TEST_F(Dynamic_Array_Fixture, Resize_1){
    array_int->Resize(1);

    EXPECT_EQ(array_int->Get(0), 42);
    EXPECT_THROW(array_int->Get(1), invalid_argument);
}

TEST_F(Dynamic_Array_Fixture, Resize_Set){
    array_int->Resize(6);
    array_int->Set(5, 999);

    EXPECT_EQ(array_int->Get(5), 999);
}

// Дестурктор----------------------------------------------

TEST_F(Dynamic_Array_Fixture, Destructor){
    DynamicArray<int>* arr = new DynamicArray<int>(3);
    delete arr;
    SUCCEED();
}




//-----------------------------------БЛОК LinkedList---------------------------------------

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

//тесты ддя LinkedList------------------------------------------
//Тесты констукторов--------------------------------------------

TEST_F(LinkedList_Fixture, Defoult_Constructor_invalid_argument){
    LinkedList<int> list;
    EXPECT_EQ(list.GetLength(), 0);
    EXPECT_THROW(list.GetFirst(), invalid_argument);
    EXPECT_THROW(list.GetLast(), invalid_argument);
    EXPECT_THROW(list.Get(0), invalid_argument);
}

TEST_F(LinkedList_Fixture, SizeConstructor){
    LinkedList<int> list(data_int, 5);
    EXPECT_EQ(list.GetLength(), 5);
    EXPECT_EQ(list.GetFirst(), 42);
    EXPECT_EQ(list.GetLast(), 228);
    EXPECT_EQ(list.Get(2), 69);
}

TEST_F(LinkedList_Fixture, ArrayConstructor_invalid_argument){
    EXPECT_THROW(LinkedList<int>(nullptr, 5), invalid_argument);
    EXPECT_THROW(LinkedList<int>(data_int, 0), invalid_argument);
    EXPECT_THROW(LinkedList<int>(data_int, -3), invalid_argument);
}

TEST_F(LinkedList_Fixture, CopyConstructor_separation){
    LinkedList<int> copy(*List_int);
    EXPECT_EQ(copy.GetLength(), 5);
    EXPECT_EQ(copy.Get(0), 42);
    EXPECT_EQ(copy.Get(4), 228);

    copy.Append(42);
    EXPECT_EQ(copy.GetLength(), 6);
    EXPECT_EQ(List_int->GetLength(), 5);
    EXPECT_THROW(List_int->Get(5), invalid_argument);
}

//Методы--------------------------------------------------------

TEST_F(LinkedList_Fixture, GetFirst){
    EXPECT_EQ(List_int->GetFirst(), 42);
    EXPECT_STREQ(List_str->GetFirst(), "красный");
}

TEST_F(LinkedList_Fixture, GetFirst_invalid_argument){
    LinkedList<int> list;
    EXPECT_THROW(list.GetFirst(), invalid_argument);
}

TEST_F(LinkedList_Fixture, GetLast){
    EXPECT_EQ(List_int->GetLast(), 228);
    EXPECT_STREQ(List_str->GetLast(), "голубой");
}

TEST_F(LinkedList_Fixture, GetLast_invalid_argument){
    LinkedList<int> list;
    EXPECT_THROW(list.GetLast(), invalid_argument);
}


TEST_F(LinkedList_Fixture, Get){
    EXPECT_EQ(List_int->Get(0), 42);
    EXPECT_EQ(List_int->Get(2), 69);
    EXPECT_EQ(List_int->Get(4), 228);
    EXPECT_STREQ(List_str->Get(1), "оранжевый");
    EXPECT_STREQ(List_str->Get(3), "зеленый");
}

TEST_F(LinkedList_Fixture, Get_invalid_argument){
    EXPECT_THROW(List_int->Get(-1), invalid_argument);
    EXPECT_THROW(List_int->Get(5), invalid_argument);
    EXPECT_THROW(List_int->Get(100), invalid_argument);
}

TEST_F(LinkedList_Fixture, GetSubList){
    LinkedList<int>* sub = List_int->GetSubList(1, 3);
    ASSERT_EQ(sub->GetLength(), 3);
    EXPECT_EQ(sub->Get(0), 52);
    EXPECT_EQ(sub->Get(1), 69);
    EXPECT_EQ(sub->Get(2), 67);
    delete sub;
}

TEST_F(LinkedList_Fixture, GetSubList_1){
    LinkedList<int>* sub = List_int->GetSubList(2, 2);
    EXPECT_EQ(sub->GetLength(), 1);
    EXPECT_EQ(sub->GetFirst(), 69);
    delete sub;
}

TEST_F(LinkedList_Fixture, GetSubList_invalid_argument){
    EXPECT_THROW(List_int->GetSubList(-1, 2), invalid_argument);
    EXPECT_THROW(List_int->GetSubList(2, 1), invalid_argument);
    EXPECT_THROW(List_int->GetSubList(2, 10), invalid_argument);
    EXPECT_THROW(List_int->GetSubList(5, 6), invalid_argument);
}


TEST_F(LinkedList_Fixture, GetLength_After){
    LinkedList<int> list;
    EXPECT_EQ(list.GetLength(), 0);
    list.Append(10);
    EXPECT_EQ(list.GetLength(), 1);
    list.Prepend(5);
    EXPECT_EQ(list.GetLength(), 2);
    list.InsertAt(7, 1);
    EXPECT_EQ(list.GetLength(), 3);
}


TEST_F(LinkedList_Fixture, Append_5){
    LinkedList<int> list;
    list.Append(100);
    EXPECT_EQ(list.GetLength(), 1);
    EXPECT_EQ(list.GetFirst(), 100);
    EXPECT_EQ(list.GetLast(), 100);
}

TEST_F(LinkedList_Fixture, Append_0){
    List_int->Append(42);
    EXPECT_EQ(List_int->GetLength(), 6);
    EXPECT_EQ(List_int->GetLast(), 42);
    EXPECT_EQ(List_int->Get(0), 42);
    EXPECT_EQ(List_int->Get(4), 228);
}


TEST_F(LinkedList_Fixture, Prepend_5){
    LinkedList<int> list;
    list.Prepend(67);
    EXPECT_EQ(list.GetLength(), 1);
    EXPECT_EQ(list.GetFirst(), 67);
    EXPECT_EQ(list.GetLast(), 67);
}

TEST_F(LinkedList_Fixture, Prepend_0){
    List_int->Prepend(52);
    EXPECT_EQ(List_int->GetLength(), 6);
    EXPECT_EQ(List_int->GetFirst(), 52);
    EXPECT_EQ(List_int->Get(1), 42);
    EXPECT_EQ(List_int->GetLast(), 228);
}


TEST_F(LinkedList_Fixture, InsertAt_first){
    List_int->InsertAt(67, 0);
    EXPECT_EQ(List_int->GetLength(), 6);
    EXPECT_EQ(List_int->GetFirst(), 67);
    EXPECT_EQ(List_int->Get(1), 42);
}

TEST_F(LinkedList_Fixture, InsertAt_End){
    List_int->InsertAt(666, List_int->GetLength());
    EXPECT_EQ(List_int->GetLength(), 6);
    EXPECT_EQ(List_int->GetLast(), 666);
    EXPECT_EQ(List_int->Get(4), 228);
}

TEST_F(LinkedList_Fixture, InsertAt_middle){
    List_int->InsertAt(111, 2);
    EXPECT_EQ(List_int->GetLength(), 6);
    EXPECT_EQ(List_int->Get(1), 52);
    EXPECT_EQ(List_int->Get(2), 111);
    EXPECT_EQ(List_int->Get(3), 69);
}

TEST_F(LinkedList_Fixture, InsertAt_invalid_argument){
    EXPECT_THROW(List_int->InsertAt(10, -1), invalid_argument);
    EXPECT_THROW(List_int->InsertAt(10, 10), invalid_argument);
}


TEST_F(LinkedList_Fixture, Concat){
    int extraData[2] ={1, 2};
    LinkedList<int> extraList(extraData, 2);
    int initialLen = List_int->GetLength();
    LinkedList<int>* concatenated = List_int->Concat(&extraList);
    EXPECT_EQ(concatenated, List_int);
    EXPECT_EQ(List_int->GetLength(), initialLen + 2);
    EXPECT_EQ(List_int->Get(0), 42);
    EXPECT_EQ(List_int->Get(4), 228);
    EXPECT_EQ(List_int->Get(5), 1);
    EXPECT_EQ(List_int->Get(6), 2);
}

TEST_F(LinkedList_Fixture, Concat_0){
    LinkedList<int> empty;
    int firstVal = List_int->Get(0);
    int lastVal = List_int->Get(4);
    int initialLen = List_int->GetLength();
    LinkedList<int>* result = List_int->Concat(&empty);
    EXPECT_EQ(result, List_int);
    EXPECT_EQ(result->GetLength(), initialLen);
    EXPECT_EQ(result->Get(0), firstVal);
    EXPECT_EQ(result->Get(4), lastVal);
}

TEST_F(LinkedList_Fixture, 0_Concat){
    LinkedList<int> empty;
    int extraData[2] ={1, 2};
    LinkedList<int> extra(extraData, 2);
    LinkedList<int>* result = empty.Concat(&extra);
    EXPECT_EQ(result, &empty);
    EXPECT_EQ(result->GetLength(), 2);
    EXPECT_EQ(result->Get(0), 1);
    EXPECT_EQ(result->Get(1), 2);
}

//Деструктор---------------------------------------------------------------------

TEST_F(LinkedList_Fixture, Destructor_NoLeak){
    LinkedList<int>* list = new LinkedList<int>(data_int, 5);
    delete list;
    SUCCEED();
}







//-----------------------------------БЛОК Bit---------------------------------------
class Bit_Fixture : public testing::Test{
protected:
    Bit<char> bit8;
    Bit<int> bit32;

    void SetUp() override{
        bit8 = Bit<char>(0b01010101);
        bit32 = Bit<int>(0b00110011001100110011001100110011);
    }
};

//тесты ддя Bit------------------------------------------
//Тесты констукторов--------------------------------------------

TEST_F(Bit_Fixture, DefoltConstructor){
    Bit<char> b;
    EXPECT_EQ(b.GetValue(), 0b00000000);
    EXPECT_FALSE(b.operator bool());
}

TEST_F(Bit_Fixture, ValueConstructor){
    Bit<char> b(0b11110000);
    EXPECT_EQ(b.GetValue(), char(0b11110000));
    EXPECT_TRUE(b.operator bool());
}

TEST_F(Bit_Fixture, CopyConstructor){
    Bit<char> copy(bit8);
    EXPECT_EQ(copy.GetValue(), bit8.GetValue());
    EXPECT_EQ(copy[0], bit8[0]);
    EXPECT_EQ(copy[7], bit8[7]);
    copy.SetValue(0b00000000);
    EXPECT_EQ(bit8.GetValue(), 0b01010101);
}

//Методы--------------------------------------------------------

TEST_F(Bit_Fixture, rovno){
    Bit<char> b1, b2(0b00110011);
    b1 = b2;
    EXPECT_EQ(b1.GetValue(), b2.GetValue());
}

TEST_F(Bit_Fixture, val){
    bit8 = bit8;
    EXPECT_EQ(bit8.GetValue(), 0b01010101);
}

TEST_F(Bit_Fixture, GetBitCount){
    EXPECT_EQ(Bit<char>().GetBitCount(), 8);
    EXPECT_EQ(Bit<short int>().GetBitCount(), 16);
    EXPECT_EQ(Bit<int>().GetBitCount(), 32);
}

TEST_F(Bit_Fixture, GetValue_SetValue){
    Bit<char> b(0b00000000);
    b.SetValue(0b10101010);
    EXPECT_EQ(b.GetValue(), char(0b10101010));
}

TEST_F(Bit_Fixture, OperatorBool_True){
    Bit<char> b(0b00000001);
    EXPECT_TRUE(b.operator bool());
}

TEST_F(Bit_Fixture, OperatorBool_False){
    Bit<char> b(0b00000000);
    EXPECT_FALSE(b.operator bool());
}

TEST_F(Bit_Fixture, IndexOperator_Read_Char){
    EXPECT_EQ(bit8[0], 1);
    EXPECT_EQ(bit8[1], 0);
    EXPECT_EQ(bit8[2], 1);
    EXPECT_EQ(bit8[3], 0);
    EXPECT_EQ(bit8[6], 1);
    EXPECT_EQ(bit8[7], 0);
}

TEST_F(Bit_Fixture, IndexOperator_Int){
    EXPECT_EQ(bit32[0], 1);
    EXPECT_EQ(bit32[1], 1);
    EXPECT_EQ(bit32[2], 0);
    EXPECT_EQ(bit32[3], 0);
}

TEST_F(Bit_Fixture, invalid_argument){
    EXPECT_THROW(bit8[-1], invalid_argument);
    EXPECT_THROW(bit8[8], invalid_argument);
    EXPECT_THROW(bit32[-1], invalid_argument);
    EXPECT_THROW(bit32[32], invalid_argument);
}

TEST_F(Bit_Fixture, IndexOperator_Write_Set1){
    Bit<char> b(0b00000000);
    b[3] = true;
    EXPECT_EQ(b.GetValue(), 0b00001000);
}

TEST_F(Bit_Fixture, IndexOperator_Write_Set0){
    Bit<char> b(0b11111111);
    b[3] = false;
    EXPECT_EQ(b.GetValue(), char(0b11110111));
}

TEST_F(Bit_Fixture, AND){
    Bit<char> a(0b11110000), b(0b00001111);
    EXPECT_EQ((a & b).GetValue(), 0b00000000);
}

TEST_F(Bit_Fixture, OR){
    Bit<char> a(0b10100000), b(0b00000101);
    EXPECT_EQ((a | b).GetValue(), char(0b10100101));
}

TEST_F(Bit_Fixture, XOR){
    Bit<char> a(0b11111111), b(0b00001111);
    EXPECT_EQ((a ^ b).GetValue(), char(0b11110000));
}

TEST_F(Bit_Fixture, NOT){
    Bit<char> a(0b00000000);
    EXPECT_EQ((~a).GetValue(), char(0b11111111));
}

TEST_F(Bit_Fixture, Comparison_Equal){
    Bit<char> a(0b01010101), b(0b01010101);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST_F(Bit_Fixture, dont_ecv_ecv){
    Bit<char> a(0b01010101), b(0b10101010);
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a == b);
}



int double_val(int x){
     return x * 2; 
}
bool is_big(int x){ 
    return x > 60; 
}
int sum_func(int acc, int x){ 
    return acc + x; 
}



//-----------------------------------БЛОК ArraySequence---------------------------------------
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

//тесты для ArraySequence------------------------------------------
//Тесты констукторов--------------------------------------------

TEST_F(ArraySequence_Fixture, def_constructor){
    ArraySequence<int> arr;
    EXPECT_EQ(arr.GetLength(), 0);
    EXPECT_THROW(arr.GetFirst(), invalid_argument);
}

TEST_F(ArraySequence_Fixture, array_constructor){
    ArraySequence<int> arr(data_int, 5);
    EXPECT_EQ(arr.GetLength(), 5);
    EXPECT_EQ(arr.Get(0), 42);
    EXPECT_EQ(arr.Get(4), 228);
}

TEST_F(ArraySequence_Fixture, array_constructor_bad){
    EXPECT_THROW(ArraySequence<int>(nullptr, 5), invalid_argument);
    EXPECT_THROW(ArraySequence<int>(data_int, -1), invalid_argument);
}

TEST_F(ArraySequence_Fixture, copy_constructor){
    ArraySequence<int> copy(*seq_int);
    EXPECT_EQ(copy.GetLength(), 5);
    EXPECT_EQ(copy.Get(2), 69);
    copy.Append(999);
    EXPECT_EQ(seq_int->GetLength(), 5);
}

TEST_F(ArraySequence_Fixture, from_list){
    LinkedList<int> list(data_int, 5);
    ArraySequence<int> arr(list);
    EXPECT_EQ(arr.GetLength(), 5);
    EXPECT_EQ(arr.Get(0), 42);
    EXPECT_EQ(arr.Get(4), 228);
}

//Методы--------------------------------------------------------

TEST_F(ArraySequence_Fixture, get_first_last){
    EXPECT_EQ(seq_int->GetFirst(), 42);
    EXPECT_EQ(seq_int->GetLast(), 228);
    EXPECT_STREQ(seq_str->GetFirst(), "первый");
    EXPECT_STREQ(seq_str->GetLast(), "третий");
}

TEST_F(ArraySequence_Fixture, get_first_last_bad){
    ArraySequence<int> empty;
    EXPECT_THROW(empty.GetFirst(), invalid_argument);
    EXPECT_THROW(empty.GetLast(), invalid_argument);
}

TEST_F(ArraySequence_Fixture, get){
    EXPECT_EQ(seq_int->Get(0), 42);
    EXPECT_EQ(seq_int->Get(2), 69);
    EXPECT_EQ(seq_int->Get(4), 228);
}

TEST_F(ArraySequence_Fixture, get_bad){
    EXPECT_THROW(seq_int->Get(-1), invalid_argument);
    EXPECT_THROW(seq_int->Get(5), invalid_argument);
}

TEST_F(ArraySequence_Fixture, get_length){
    EXPECT_EQ(seq_int->GetLength(), 5);
    EXPECT_EQ(seq_str->GetLength(), 3);
}

TEST_F(ArraySequence_Fixture, append){
    seq_int->Append(100);
    EXPECT_EQ(seq_int->GetLength(), 6);
    EXPECT_EQ(seq_int->GetLast(), 100);
}

TEST_F(ArraySequence_Fixture, prepend){
    seq_int->Prepend(1);
    EXPECT_EQ(seq_int->GetLength(), 6);
    EXPECT_EQ(seq_int->GetFirst(), 1);
    EXPECT_EQ(seq_int->Get(1), 42);
}

TEST_F(ArraySequence_Fixture, insert_begin){
    seq_int->InsertAt(0, 0);
    EXPECT_EQ(seq_int->GetLength(), 6);
    EXPECT_EQ(seq_int->GetFirst(), 0);
    EXPECT_EQ(seq_int->Get(1), 42);
}

TEST_F(ArraySequence_Fixture, insert_middle){
    seq_int->InsertAt(99, 2);
    EXPECT_EQ(seq_int->GetLength(), 6);
    EXPECT_EQ(seq_int->Get(2), 99);
    EXPECT_EQ(seq_int->Get(3), 69);
}

TEST_F(ArraySequence_Fixture, insert_end){
    int len = seq_int->GetLength();
    seq_int->InsertAt(777, len);
    EXPECT_EQ(seq_int->GetLength(), len + 1);
    EXPECT_EQ(seq_int->GetLast(), 777);
}

TEST_F(ArraySequence_Fixture, invalid_argument){
    EXPECT_THROW(seq_int->InsertAt(10, -1), invalid_argument);
    EXPECT_THROW(seq_int->InsertAt(10, 6), invalid_argument);
}

TEST_F(ArraySequence_Fixture, concat){
    int extra[2] ={1, 2};
    ArraySequence<int> extraSeq(extra, 2);
    int initLen = seq_int->GetLength();
    seq_int->Concat(&extraSeq);
    EXPECT_EQ(seq_int->GetLength(), initLen + 2);
    EXPECT_EQ(seq_int->Get(5), 1);
    EXPECT_EQ(seq_int->Get(6), 2);
}

TEST_F(ArraySequence_Fixture, concat_null){
    int first = seq_int->GetFirst();
    seq_int->Concat(nullptr);
    EXPECT_EQ(seq_int->GetLength(), 5);
    EXPECT_EQ(seq_int->GetFirst(), first);
}

TEST_F(ArraySequence_Fixture, subseq){
    ArraySequence<int>* sub = seq_int->GetSubsequence(1, 3);
    EXPECT_EQ(sub->GetLength(), 3);
    EXPECT_EQ(sub->Get(0), 52);
    EXPECT_EQ(sub->Get(1), 69);
    EXPECT_EQ(sub->Get(2), 67);
    delete sub;
}

TEST_F(ArraySequence_Fixture, subseq_bad){
    EXPECT_THROW(seq_int->GetSubsequence(-1, 2), invalid_argument);
    EXPECT_THROW(seq_int->GetSubsequence(2, 1), invalid_argument);
    EXPECT_THROW(seq_int->GetSubsequence(2, 10), invalid_argument);
}


TEST_F(ArraySequence_Fixture, map){
    Sequence<int>* mapped = seq_int->Map(double_val);
    EXPECT_EQ(mapped->GetLength(), 5);
    EXPECT_EQ(mapped->Get(0), 84);
    EXPECT_EQ(mapped->Get(2), 138);
    delete mapped;
}

TEST_F(ArraySequence_Fixture, where){
    Sequence<int>* filtered = seq_int->Where(is_big);
    EXPECT_EQ(filtered->GetLength(), 3);
    EXPECT_EQ(filtered->Get(0), 69);
    EXPECT_EQ(filtered->Get(1), 67);
    EXPECT_EQ(filtered->Get(2), 228);
    delete filtered;
}

TEST_F(ArraySequence_Fixture, reduce){
    int total = seq_int->Reduce(sum_func, 0);
    EXPECT_EQ(total, 42 + 52 + 69 + 67 + 228);
}


//Деструктор----------------------------------------------------

TEST_F(ArraySequence_Fixture, destructor){
    ArraySequence<int>* arr = new ArraySequence<int>(data_int, 5);
    delete arr;
    SUCCEED();
}





//-----------------------------------БЛОК ListSequence---------------------------------------
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

//тесты для ListSequence------------------------------------------
//Тесты констукторов--------------------------------------------

TEST_F(ListSequence_Fixture, def_constructor){
    ListSequence<int> list;
    EXPECT_EQ(list.GetLength(), 0);
    EXPECT_THROW(list.GetFirst(), invalid_argument);
}

TEST_F(ListSequence_Fixture, array_constructor){
    ListSequence<int> list(data_int, 5);
    EXPECT_EQ(list.GetLength(), 5);
    EXPECT_EQ(list.Get(0), 42);
    EXPECT_EQ(list.Get(4), 228);
}

TEST_F(ListSequence_Fixture, copy_constructor){
    ListSequence<int> copy(*seq_int);
    EXPECT_EQ(copy.GetLength(), 5);
    copy.Append(999);
    EXPECT_EQ(seq_int->GetLength(), 5);
}

TEST_F(ListSequence_Fixture, from_array){
    ArraySequence<int> arr(data_int, 5);
    ListSequence<int> list(arr);
    EXPECT_EQ(list.GetLength(), 5);
    EXPECT_EQ(list.Get(0), 42);
}

//Методы--------------------------------------------------------

TEST_F(ListSequence_Fixture, get_first_last){
    EXPECT_EQ(seq_int->GetFirst(), 42);
    EXPECT_EQ(seq_int->GetLast(), 228);
    EXPECT_STREQ(seq_str->GetFirst(), "первый");
}

TEST_F(ListSequence_Fixture, get){
    EXPECT_EQ(seq_int->Get(0), 42);
    EXPECT_EQ(seq_int->Get(2), 69);
    EXPECT_EQ(seq_int->Get(4), 228);
}

TEST_F(ListSequence_Fixture, get_bad){
    EXPECT_THROW(seq_int->Get(-1), invalid_argument);
    EXPECT_THROW(seq_int->Get(5), invalid_argument);
}


TEST_F(ListSequence_Fixture, append){
    seq_int->Append(100);
    EXPECT_EQ(seq_int->GetLength(), 6);
    EXPECT_EQ(seq_int->GetLast(), 100);
}

TEST_F(ListSequence_Fixture, prepend){
    seq_int->Prepend(1);
    EXPECT_EQ(seq_int->GetLength(), 6);
    EXPECT_EQ(seq_int->GetFirst(), 1);
}

TEST_F(ListSequence_Fixture, insert){
    seq_int->InsertAt(99, 2);
    EXPECT_EQ(seq_int->GetLength(), 6);
    EXPECT_EQ(seq_int->Get(2), 99);
    EXPECT_EQ(seq_int->Get(3), 69);
}

TEST_F(ListSequence_Fixture, insert_bad){
    EXPECT_THROW(seq_int->InsertAt(10, -1), invalid_argument);
    EXPECT_THROW(seq_int->InsertAt(10, 6), invalid_argument);
}

TEST_F(ListSequence_Fixture, concat){
    int extra[2] ={1, 2};
    ListSequence<int> extraSeq(extra, 2);
    seq_int->Concat(&extraSeq);
    EXPECT_EQ(seq_int->GetLength(), 7);
    EXPECT_EQ(seq_int->Get(5), 1);
}

TEST_F(ListSequence_Fixture, subseq){
    ListSequence<int>* sub = seq_int->GetSubsequence(1, 3);
    EXPECT_EQ(sub->GetLength(), 3);
    EXPECT_EQ(sub->Get(0), 52);
    delete sub;
}

TEST_F(ListSequence_Fixture, map){
    Sequence<int>* mapped = seq_int->Map(double_val);
    EXPECT_EQ(mapped->Get(0), 84);
    delete mapped;
}

TEST_F(ListSequence_Fixture, where){
    Sequence<int>* filtered = seq_int->Where(is_big);
    EXPECT_EQ(filtered->GetLength(), 3);
    delete filtered;
}

TEST_F(ListSequence_Fixture, reduce){
    int total = seq_int->Reduce(sum_func, 0);
    EXPECT_EQ(total, 42 + 52 + 69 + 67 + 228);
}

//Деструктор----------------------------------------------------

TEST_F(ListSequence_Fixture, destructor){
    ListSequence<int>* list = new ListSequence<int>(data_int, 5);
    delete list;
    SUCCEED();
}





//-----------------------------------БЛОК Mutable/Immutable---------------------------------------
class MutableImmutable_Fixture : public testing::Test{
protected:
    int data[3] ={1, 2, 3};
};

TEST_F(MutableImmutable_Fixture, mutable_array_changes){
    MutableArraySequence<int> seq(data, 3);
    EXPECT_EQ(seq.GetLength(), 3);
    seq.Append(4);
    EXPECT_EQ(seq.GetLength(), 4);
    EXPECT_EQ(seq.GetLast(), 4);
}

TEST_F(MutableImmutable_Fixture, immutable_array_copy){
    ImmutableArraySequence<int> seq(data, 3);
    EXPECT_EQ(seq.GetLength(), 3);
    Sequence<int>* seq2 = seq.Append(4);
    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(seq2->GetLength(), 4);
    EXPECT_EQ(seq2->GetLast(), 4);
    delete seq2;
}

TEST_F(MutableImmutable_Fixture, mutable_list_changes){
    MutableListSequence<int> seq(data, 3);
    seq.Prepend(0);
    EXPECT_EQ(seq.GetFirst(), 0);
    EXPECT_EQ(seq.GetLength(), 4);
}

TEST_F(MutableImmutable_Fixture, immutable_list_copy){
    ImmutableListSequence<int> seq(data, 3);
    Sequence<int>* seq2 = seq.Prepend(0);
    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(seq2->GetFirst(), 0);
    EXPECT_EQ(seq2->GetLength(), 4);
    delete seq2;
}

