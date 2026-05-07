#include "Fixtures.hpp"


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

TEST_F(ListSequence_Fixture, get_invalid_argument){
    EXPECT_THROW(seq_int->Get(5), invalid_argument);
    EXPECT_THROW(seq_int->Get(100), invalid_argument);
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

TEST_F(ListSequence_Fixture, insert_invalid_argument){
    EXPECT_THROW(seq_int->InsertAt(10, 6), invalid_argument);
    EXPECT_THROW(seq_int->InsertAt(10, 100), invalid_argument);
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