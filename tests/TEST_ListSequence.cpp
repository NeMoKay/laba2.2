#include "Fixtures.hpp"
#include "exceptions.hpp"


//Тесты конструкторов--------------------------------------------

TEST_F(ListSequence_Fixture, def_constructor){
    ListSequence<int> list;
    EXPECT_EQ(list.GetLength(), 0) << "Ожидаемая длина 0. По факту : " << list.GetLength();
    EXPECT_THROW(list.GetFirst(), EmptySequenceException) << "Ожидается EmptySequenceException. По факту : исключение не выброшено";
}

TEST_F(ListSequence_Fixture, array_constructor){
    ListSequence<int> list(data_int, 5);
    EXPECT_EQ(list.GetLength(), 5) << "Ожидаемая длина 5. По факту : " << list.GetLength();
    EXPECT_EQ(list.Get(0), 42) << "Ожидаемый элемент 42. По факту : " << list.Get(0);
    EXPECT_EQ(list.Get(4), 228) << "Ожидаемый элемент 228. По факту : " << list.Get(4);
}

TEST_F(ListSequence_Fixture, copy_constructor){
    ListSequence<int> copy(*seq_int);
    EXPECT_EQ(copy.GetLength(), 5) << "Ожидаемая длина 5. По факту : " << copy.GetLength();
    copy.Append(999);
    EXPECT_EQ(seq_int->GetLength(), 5) << "Ожидаемая длина 5. По факту : " << seq_int->GetLength();
}

TEST_F(ListSequence_Fixture, from_array){
    ArraySequence<int> arr(data_int, 5);
    ListSequence<int> list(arr);
    EXPECT_EQ(list.GetLength(), 5) << "Ожидаемая длина 5. По факту : " << list.GetLength();
    EXPECT_EQ(list.Get(0), 42) << "Ожидаемый элемент 42. По факту : " << list.Get(0);
}

//Методы--------------------------------------------------------

TEST_F(ListSequence_Fixture, get_first_last){
    EXPECT_EQ(seq_int->GetFirst(), 42) << "Ожидаемый элемент 42. По факту : " << seq_int->GetFirst();
    EXPECT_EQ(seq_int->GetLast(), 228) << "Ожидаемый элемент 228. По факту : " << seq_int->GetLast();
    EXPECT_STREQ(seq_str->GetFirst(), "первый") << "Ожидаемый элемент первый. По факту : " << seq_str->GetFirst();
}

TEST_F(ListSequence_Fixture, get){
    EXPECT_EQ(seq_int->Get(0), 42) << "Ожидаемый элемент 42. По факту : " << seq_int->Get(0);
    EXPECT_EQ(seq_int->Get(2), 69) << "Ожидаемый элемент 69. По факту : " << seq_int->Get(2);
    EXPECT_EQ(seq_int->Get(4), 228) << "Ожидаемый элемент 228. По факту : " << seq_int->Get(4);
}

TEST_F(ListSequence_Fixture, get_invalid_argument){
    EXPECT_THROW(seq_int->Get(5), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для индекса 5";
    EXPECT_THROW(seq_int->Get(100), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для индекса 100";
}


TEST_F(ListSequence_Fixture, append){
    seq_int->Append(100);
    EXPECT_EQ(seq_int->GetLength(), 6) << "Ожидаемая длина 6. По факту : " << seq_int->GetLength();
    EXPECT_EQ(seq_int->GetLast(), 100) << "Ожидаемый элемент 100. По факту : " << seq_int->GetLast();
}

TEST_F(ListSequence_Fixture, prepend){
    seq_int->Prepend(1);
    EXPECT_EQ(seq_int->GetLength(), 6) << "Ожидаемая длина 6. По факту : " << seq_int->GetLength();
    EXPECT_EQ(seq_int->GetFirst(), 1) << "Ожидаемый элемент 1. По факту : " << seq_int->GetFirst();
}

TEST_F(ListSequence_Fixture, insert){
    seq_int->InsertAt(99, 2);
    EXPECT_EQ(seq_int->GetLength(), 6) << "Ожидаемая длина 6. По факту : " << seq_int->GetLength();
    EXPECT_EQ(seq_int->Get(2), 99) << "Ожидаемый элемент 99. По факту : " << seq_int->Get(2);
    EXPECT_EQ(seq_int->Get(3), 69) << "Ожидаемый элемент 69. По факту : " << seq_int->Get(3);
}

TEST_F(ListSequence_Fixture, insert_invalid_argument){
    EXPECT_THROW(seq_int->InsertAt(10, 6), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для индекса 6";
    EXPECT_THROW(seq_int->InsertAt(10, 100), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для индекса 100";
}

TEST_F(ListSequence_Fixture, concat){
    int extra[2] ={1, 2};
    ListSequence<int> extraSeq(extra, 2);
    seq_int->Concat(&extraSeq);
    EXPECT_EQ(seq_int->GetLength(), 7) << "Ожидаемая длина 7. По факту : " << seq_int->GetLength();
    EXPECT_EQ(seq_int->Get(5), 1) << "Ожидаемый элемент 1. По факту : " << seq_int->Get(5);
}

TEST_F(ListSequence_Fixture, subseq){
    ListSequence<int>* sub = seq_int->GetSubsequence(1, 3);
    EXPECT_EQ(sub->GetLength(), 3) << "Ожидаемая длина 3. По факту : " << sub->GetLength();
    EXPECT_EQ(sub->Get(0), 52) << "Ожидаемый элемент 52. По факту : " << sub->Get(0);
    delete sub;
}

TEST_F(ListSequence_Fixture, map){
    Sequence<int>* mapped = Map(seq_int, double_val);
    EXPECT_EQ(mapped->Get(0), 84) << "Функция выполнения map (x * 2)" << endl << "Ожидаемый элемент 84. По факту : " << mapped->Get(0);
    delete mapped;
}

TEST_F(ListSequence_Fixture, where){
    Sequence<int>* filtered = Where(seq_int, is_big);
    EXPECT_EQ(filtered->GetLength(), 3) << "Функция выполнения Where (x > 60)" << endl << "Ожидаемая длина 3. По факту : " << filtered->GetLength();
    delete filtered;
}

TEST_F(ListSequence_Fixture, reduce){
    int total = Reduce(seq_int, sum_func, 0);
    EXPECT_EQ(total, 42 + 52 + 69 + 67 + 228) << "Функция выполнения reduce (sum(xi))" << endl << "Ожидаемый элемент " << 42 + 52 + 69 + 67 + 228 << ". По факту : " << total;
}

//Деструктор----------------------------------------------------

TEST_F(ListSequence_Fixture, destructor){
    ListSequence<int>* list = new ListSequence<int>(data_int, 5);
    delete list;
    SUCCEED();
}