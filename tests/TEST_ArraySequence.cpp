
#include "Fixtures.hpp"

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

TEST_F(ArraySequence_Fixture, array_constructor_invalid_argument){
    EXPECT_THROW(ArraySequence<int>(nullptr, 5), invalid_argument);
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

TEST_F(ArraySequence_Fixture, get_first_last_invalid_argument){
    ArraySequence<int> empty;
    EXPECT_THROW(empty.GetFirst(), invalid_argument);
    EXPECT_THROW(empty.GetLast(), invalid_argument);
}

TEST_F(ArraySequence_Fixture, get){
    EXPECT_EQ(seq_int->Get(0), 42);
    EXPECT_EQ(seq_int->Get(2), 69);
    EXPECT_EQ(seq_int->Get(4), 228);
}

TEST_F(ArraySequence_Fixture, get_invalid_argument){
    EXPECT_THROW(seq_int->Get(5), invalid_argument);
    EXPECT_THROW(seq_int->Get(100), invalid_argument);
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
    EXPECT_THROW(seq_int->InsertAt(10, 6), invalid_argument);
    EXPECT_THROW(seq_int->InsertAt(10, 100), invalid_argument);
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

TEST_F(ArraySequence_Fixture, subseq_invalid_argument){
    EXPECT_THROW(seq_int->GetSubsequence(2, 1), invalid_argument);
    EXPECT_THROW(seq_int->GetSubsequence(2, 10), invalid_argument);
    EXPECT_THROW(seq_int->GetSubsequence(5, 6), invalid_argument);
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