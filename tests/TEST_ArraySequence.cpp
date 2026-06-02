#include "Fixtures.hpp"


TEST_F(ArraySequence_Fixture, def_constructor){
    ArraySequence<int> arr;
    EXPECT_EQ(arr.GetLength(), 0) << "Ожидаемая длинна 0. По факту : " << arr.GetLength();
    EXPECT_THROW(arr.GetFirst(), EmptySequenceException) << "Ожидается EmptySequenceException. По факту : " << arr.GetFirst();
}

TEST_F(ArraySequence_Fixture, array_constructor){
    ArraySequence<int> arr(data_int, 5);
    EXPECT_EQ(arr.GetLength(), 5) << "Ожидаемая длинна 5. По факту : " << arr.GetLength();
    EXPECT_EQ(arr.Get(0), 42) << "Ожидаемый элемент 42. По факту : " << arr.Get(0);
    EXPECT_EQ(arr.Get(4), 228) << "Ожидаемый элемент 228. По факту : " << arr.Get(4);
}

TEST_F(ArraySequence_Fixture, array_constructor_invalid_argument){
    EXPECT_THROW(ArraySequence<int>(nullptr, 5), NullPtrException) << "Ожидается NullPtrException. По факту исключение не выброшено";
}

TEST_F(ArraySequence_Fixture, copy_constructor){
    ArraySequence<int> copy(*seq_int);
    EXPECT_EQ(copy.GetLength(), 5) << "Ожидаемая длинна 5. По факту : " << copy.GetLength();
    EXPECT_EQ(copy.Get(2), 69) << "Ожидаемый элемент 69. По факту : " << copy.Get(2);
    copy.Append(999);
    EXPECT_EQ(seq_int->GetLength(), 5) << "Ожидаемая длинна 5. По факту : " << seq_int->GetLength();
}

TEST_F(ArraySequence_Fixture, copy_list_Linked){
    LinkedList<int> list(data_int, 5);
    ArraySequence<int> arr(list);
    EXPECT_EQ(arr.GetLength(), 5) << "Ожидаемая длинна 5. По факту : " << arr.GetLength();
    EXPECT_EQ(arr.Get(0), 42) << "Ожидаемый элемент 42. По факту : " << arr.Get(0);
    EXPECT_EQ(arr.Get(4), 228) << "Ожидаемый элемент 228. По факту : " << arr.Get(4);
}

// TEST(ArraySeq, arr_init) {
//     int a[5] = {1,2,3,4,5};
//     ArraySequence<int> arr(a);
// }

//Методы--------------------------------------------------------

TEST_F(ArraySequence_Fixture, get_first_last){
    EXPECT_EQ(seq_int->GetFirst(), 42) << "Ожидаемый элемент 42. По факту : " << seq_int->GetFirst();
    EXPECT_EQ(seq_int->GetLast(), 228) << "Ожидаемый элемент 228. По факту : " << seq_int->GetLast();
    EXPECT_STREQ(seq_str->GetFirst(), "первый") << "Ожидаемый элемент первый. По факту : " << seq_str->GetFirst();
    EXPECT_STREQ(seq_str->GetLast(), "третий") << "Ожидаемый элемент третий. По факту : " << seq_str->GetLast();
}

TEST_F(ArraySequence_Fixture, get_first_last_invalid_argument){
    ArraySequence<int> empty;
    EXPECT_THROW(empty.GetFirst(), EmptySequenceException) << "Ожидается EmptySequenceException при GetFirst()";
    EXPECT_THROW(empty.GetLast(), EmptySequenceException) << "Ожидается EmptySequenceException при GetLast()";
}

TEST_F(ArraySequence_Fixture, get){
    EXPECT_EQ(seq_int->Get(0), 42) << "Ожидаемый элемент 42. По факту : " << seq_int->Get(0);
    EXPECT_EQ(seq_int->Get(2), 69) << "Ожидаемый элемент 69. По факту : " << seq_int->Get(2);
    EXPECT_EQ(seq_int->Get(4), 228) << "Ожидаемый элемент 228. По факту : " << seq_int->Get(4);
}

TEST_F(ArraySequence_Fixture, get_invalid_argument){
    EXPECT_THROW(seq_int->Get(5), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для индекса 5";
    EXPECT_THROW(seq_int->Get(100), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для индекса 100";
}

TEST_F(ArraySequence_Fixture, get_length){
    EXPECT_EQ(seq_int->GetLength(), 5) << "Ожидаемая длинна 5. По факту : " << seq_int->GetLength();
    EXPECT_EQ(seq_str->GetLength(), 3) << "Ожидаемая длинна 3. По факту : " << seq_str->GetLength();
}

TEST_F(ArraySequence_Fixture, append){
    seq_int->Append(100);
    EXPECT_EQ(seq_int->GetLength(), 6) << "Ожидаемая длинна 6. По факту : " << seq_int->GetLength();
    EXPECT_EQ(seq_int->GetLast(), 100) << "Ожидаемый элемент 100. По факту : " << seq_int->GetLast();
}

TEST_F(ArraySequence_Fixture, prepend){
    seq_int->Prepend(1);
    EXPECT_EQ(seq_int->GetLength(), 6) << "Ожидаемая длинна 6. По факту : " << seq_int->GetLength();
    EXPECT_EQ(seq_int->GetFirst(), 1) << "Ожидаемый элемент 1. По факту : " << seq_int->GetFirst();
    EXPECT_EQ(seq_int->Get(1), 42) << "Ожидаемый элемент 42. По факту : " << seq_int->Get(1);
}

TEST_F(ArraySequence_Fixture, insert_begin){
    seq_int->InsertAt(0, 0);
    EXPECT_EQ(seq_int->GetLength(), 6) << "Ожидаемая длинна 6. По факту : " << seq_int->GetLength();
    EXPECT_EQ(seq_int->GetFirst(), 0) << "Ожидаемый элемент 0. По факту : " << seq_int->GetFirst();
    EXPECT_EQ(seq_int->Get(1), 42) << "Ожидаемый элемент 42. По факту : " << seq_int->Get(1);
}

TEST_F(ArraySequence_Fixture, insert_middle){
    seq_int->InsertAt(99, 2);
    EXPECT_EQ(seq_int->GetLength(), 6) << "Ожидаемая длинна 6. По факту : " << seq_int->GetLength();
    EXPECT_EQ(seq_int->Get(2), 99) << "Ожидаемый элемент 99. По факту : " << seq_int->Get(2);
    EXPECT_EQ(seq_int->Get(3), 69) << "Ожидаемый элемент 69. По факту : " << seq_int->Get(3);
}

TEST_F(ArraySequence_Fixture, insert_end){
    int len = seq_int->GetLength();
    seq_int->InsertAt(777, len);
    EXPECT_EQ(seq_int->GetLength(), len + 1) << "Ожидаемая длинна " << len + 1 << ". По факту : " << seq_int->GetLength();
    EXPECT_EQ(seq_int->GetLast(), 777) << "Ожидаемый элемент 777. По факту : " << seq_int->GetLast();
}

TEST_F(ArraySequence_Fixture, invalid_argument){
    EXPECT_THROW(seq_int->InsertAt(10, 6), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для индекса 6";
    EXPECT_THROW(seq_int->InsertAt(10, 100), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для индекса 100";
}

TEST_F(ArraySequence_Fixture, concat){
    int extra[2] ={1, 2};
    ArraySequence<int> extraSeq(extra, 2);
    int initLen = seq_int->GetLength();
    seq_int->Concat(&extraSeq);
    EXPECT_EQ(seq_int->GetLength(), initLen + 2) << "Ожидаемая длинна " << initLen + 2 << ". По факту : " << seq_int->GetLength();
    EXPECT_EQ(seq_int->Get(5), 1) << "Ожидаемый элемент 1. По факту : " << seq_int->Get(5);
    EXPECT_EQ(seq_int->Get(6), 2) << "Ожидаемый элемент 2. По факту : " << seq_int->Get(6);
}

TEST_F(ArraySequence_Fixture, concat_null){
    int first = seq_int->GetFirst();
    seq_int->Concat(nullptr);
    EXPECT_EQ(seq_int->GetLength(), 5) << "Ожидаемая длинна 5. По факту : " << seq_int->GetLength();
    EXPECT_EQ(seq_int->GetFirst(), first) << "Ожидаемый элемент " << first << ". По факту : " << seq_int->GetFirst();
}

TEST_F(ArraySequence_Fixture, subseq){
    ArraySequence<int>* sub = seq_int->GetSubsequence(1, 3);
    EXPECT_EQ(sub->GetLength(), 3) << "Ожидаемая длинна 3. По факту : " << sub->GetLength();
    EXPECT_EQ(sub->Get(0), 52) << "Ожидаемый элемент 52. По факту : " << sub->Get(0);
    EXPECT_EQ(sub->Get(1), 69) << "Ожидаемый элемент 69. По факту : " << sub->Get(1);
    EXPECT_EQ(sub->Get(2), 67) << "Ожидаемый элемент 67. По факту : " << sub->Get(2);
    delete sub;
}

TEST_F(ArraySequence_Fixture, subseq_invalid_argument){
    EXPECT_THROW(seq_int->GetSubsequence(2, 1), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для диапазона (2,1)";
    EXPECT_THROW(seq_int->GetSubsequence(2, 10), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для диапазона (2,10)";
    EXPECT_THROW(seq_int->GetSubsequence(5, 6), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для диапазона (5,6)";
}


TEST_F(ArraySequence_Fixture, map){
    Sequence<int>* mapped = Map(seq_int, double_val);
    EXPECT_EQ(mapped->GetLength(), 5) << "Функция выволнения map (x * 2)" << endl << "Ожидаемая длинна 5. По факту : " << mapped->GetLength();
    EXPECT_EQ(mapped->Get(0), 84) <<  "Функция выволнения map (x * 2)" << endl << "Ожидаемый элемент 84. По факту : " << mapped->Get(0);
    EXPECT_EQ(mapped->Get(2), 138) << "Функция выволнения map (x * 2)" << endl << "Ожидаемый элемент 138. По факту : " << mapped->Get(2);
    delete mapped;
}

TEST_F(ArraySequence_Fixture, where){
    Sequence<int>* filtered = Where(seq_int, is_big);
    EXPECT_EQ(filtered->GetLength(), 3) << "Ожидаемая длинна 3. По факту : " << filtered->GetLength();
    EXPECT_EQ(filtered->Get(0), 69) << "Функция выволнения Where (x > 60)" << endl << "Ожидаемый элемент 69. По факту : " << filtered->Get(0);
    EXPECT_EQ(filtered->Get(1), 67) <<  "Функция выволнения Where (x > 60)" << endl <<"Ожидаемый элемент 67. По факту : " << filtered->Get(1);
    EXPECT_EQ(filtered->Get(2), 228) <<  "Функция выволнения Where (x > 60)" << endl <<"Ожидаемый элемент 228. По факту : " << filtered->Get(2);
    delete filtered;
}

TEST_F(ArraySequence_Fixture, reduce){
    int total = Reduce(seq_int, sum_func, 0);
    EXPECT_EQ(total, 42 + 52 + 69 + 67 + 228) <<  "Функция выволнения reduce (sum(xi))" << endl <<"Ожидаемый элемент " << 42 + 52 + 69 + 67 + 228 << ". По факту : " << total;
}


//Деструктор----------------------------------------------------

TEST_F(ArraySequence_Fixture, destructor){
    ArraySequence<int>* arr = new ArraySequence<int>(data_int, 5);
    delete arr;
    SUCCEED();
}