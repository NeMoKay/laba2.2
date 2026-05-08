#include "Fixtures.hpp"


//Тесты конструкторов--------------------------------------------

TEST_F(LinkedList_Fixture, Defoult_Constructor_invalid_argument){
    LinkedList<int> list;
    EXPECT_EQ(list.GetLength(), 0) << "Ожидаемая длина 0. По факту : " << list.GetLength();
    EXPECT_THROW(list.GetFirst(), invalid_argument) << "Ожидается invalid_argument. По факту : исключение не выброшено";
    EXPECT_THROW(list.GetLast(), invalid_argument) << "Ожидается invalid_argument. По факту : исключение не выброшено";
    EXPECT_THROW(list.Get(0), invalid_argument) << "Ожидается invalid_argument. По факту : исключение не выброшено";
}

TEST_F(LinkedList_Fixture, SizeConstructor){
    LinkedList<int> list(data_int, 5);
    EXPECT_EQ(list.GetLength(), 5) << "Ожидаемая длина 5. По факту : " << list.GetLength();
    EXPECT_EQ(list.GetFirst(), 42) << "Ожидаемый элемент 42. По факту : " << list.GetFirst();
    EXPECT_EQ(list.GetLast(), 228) << "Ожидаемый элемент 228. По факту : " << list.GetLast();
    EXPECT_EQ(list.Get(2), 69) << "Ожидаемый элемент 69. По факту : " << list.Get(2);
}

TEST_F(LinkedList_Fixture, ArrayConstructor_invalid_argument){
    EXPECT_THROW(LinkedList<int>(nullptr, 5), invalid_argument) << "Ожидается invalid_argument. По факту : исключение не выброшено";
    EXPECT_THROW(LinkedList<int>(data_int, 0), invalid_argument) << "Ожидается invalid_argument. По факту : исключение не выброшено";
}

TEST_F(LinkedList_Fixture, CopyConstructor_separation){
    LinkedList<int> copy(*List_int);
    EXPECT_EQ(copy.GetLength(), 5) << "Ожидаемая длина 5. По факту : " << copy.GetLength();
    EXPECT_EQ(copy.Get(0), 42) << "Ожидаемый элемент 42. По факту : " << copy.Get(0);
    EXPECT_EQ(copy.Get(4), 228) << "Ожидаемый элемент 228. По факту : " << copy.Get(4);

    copy.Append(42);
    EXPECT_EQ(copy.GetLength(), 6) << "Ожидаемая длина 6. По факту : " << copy.GetLength();
    EXPECT_EQ(List_int->GetLength(), 5) << "Ожидаемая длина 5. По факту : " << List_int->GetLength();
    EXPECT_THROW(List_int->Get(5), invalid_argument) << "Ожидается invalid_argument для индекса 5";
}

//Методы--------------------------------------------------------

TEST_F(LinkedList_Fixture, GetFirst){
    EXPECT_EQ(List_int->GetFirst(), 42) << "Ожидаемый элемент 42. По факту : " << List_int->GetFirst();
    EXPECT_STREQ(List_str->GetFirst(), "красный") << "Ожидаемый элемент красный. По факту : " << List_str->GetFirst();
}

TEST_F(LinkedList_Fixture, GetFirst_invalid_argument){
    LinkedList<int> list;
    EXPECT_THROW(list.GetFirst(), invalid_argument) << "Ожидается invalid_argument. По факту : исключение не выброшено";
}

TEST_F(LinkedList_Fixture, GetLast){
    EXPECT_EQ(List_int->GetLast(), 228) << "Ожидаемый элемент 228. По факту : " << List_int->GetLast();
    EXPECT_STREQ(List_str->GetLast(), "голубой") << "Ожидаемый элемент голубой. По факту : " << List_str->GetLast();
}

TEST_F(LinkedList_Fixture, GetLast_invalid_argument){
    LinkedList<int> list;
    EXPECT_THROW(list.GetLast(), invalid_argument) << "Ожидается invalid_argument. По факту : исключение не выброшено";
}


TEST_F(LinkedList_Fixture, Get){
    EXPECT_EQ(List_int->Get(0), 42) << "Ожидаемый элемент 42. По факту : " << List_int->Get(0);
    EXPECT_EQ(List_int->Get(2), 69) << "Ожидаемый элемент 69. По факту : " << List_int->Get(2);
    EXPECT_EQ(List_int->Get(4), 228) << "Ожидаемый элемент 228. По факту : " << List_int->Get(4);
    EXPECT_STREQ(List_str->Get(1), "оранжевый") << "Ожидаемый элемент оранжевый. По факту : " << List_str->Get(1);
    EXPECT_STREQ(List_str->Get(3), "зеленый") << "Ожидаемый элемент зеленый. По факту : " << List_str->Get(3);
}

TEST_F(LinkedList_Fixture, Get_invalid_argument){
    EXPECT_THROW(List_int->Get(5), invalid_argument) << "Ожидается invalid_argument для индекса 5";
    EXPECT_THROW(List_int->Get(100), invalid_argument) << "Ожидается invalid_argument для индекса 100";
}

TEST_F(LinkedList_Fixture, GetSubList){
    LinkedList<int>* sub = List_int->GetSubList(1, 3);
    ASSERT_EQ(sub->GetLength(), 3) << "Ожидаемая длина 3. По факту : " << sub->GetLength();
    EXPECT_EQ(sub->Get(0), 52) << "Ожидаемый элемент 52. По факту : " << sub->Get(0);
    EXPECT_EQ(sub->Get(1), 69) << "Ожидаемый элемент 69. По факту : " << sub->Get(1);
    EXPECT_EQ(sub->Get(2), 67) << "Ожидаемый элемент 67. По факту : " << sub->Get(2);
    delete sub;
}

TEST_F(LinkedList_Fixture, GetSubList_1){
    LinkedList<int>* sub = List_int->GetSubList(2, 2);
    EXPECT_EQ(sub->GetLength(), 1) << "Ожидаемая длина 1. По факту : " << sub->GetLength();
    EXPECT_EQ(sub->GetFirst(), 69) << "Ожидаемый элемент 69. По факту : " << sub->GetFirst();
    delete sub;
}

TEST_F(LinkedList_Fixture, GetSubList_invalid_argument){
    EXPECT_THROW(List_int->GetSubList(2, 1), invalid_argument) << "Ожидается invalid_argument для диапазона (2,1)";
    EXPECT_THROW(List_int->GetSubList(2, 10), invalid_argument) << "Ожидается invalid_argument для диапазона (2,10)";
    EXPECT_THROW(List_int->GetSubList(5, 6), invalid_argument) << "Ожидается invalid_argument для диапазона (5,6)";
}


TEST_F(LinkedList_Fixture, GetLength_After){
    LinkedList<int> list;
    EXPECT_EQ(list.GetLength(), 0) << "Ожидаемая длина 0. По факту : " << list.GetLength();
    list.Append(10);
    EXPECT_EQ(list.GetLength(), 1) << "Ожидаемая длина 1. По факту : " << list.GetLength();
    list.Prepend(5);
    EXPECT_EQ(list.GetLength(), 2) << "Ожидаемая длина 2. По факту : " << list.GetLength();
    list.InsertAt(7, 1);
    EXPECT_EQ(list.GetLength(), 3) << "Ожидаемая длина 3. По факту : " << list.GetLength();
}


TEST_F(LinkedList_Fixture, Append_5){
    LinkedList<int> list;
    list.Append(100);
    EXPECT_EQ(list.GetLength(), 1) << "Ожидаемая длина 1. По факту : " << list.GetLength();
    EXPECT_EQ(list.GetFirst(), 100) << "Ожидаемый элемент 100. По факту : " << list.GetFirst();
    EXPECT_EQ(list.GetLast(), 100) << "Ожидаемый элемент 100. По факту : " << list.GetLast();
}

TEST_F(LinkedList_Fixture, Append_0){
    List_int->Append(42);
    EXPECT_EQ(List_int->GetLength(), 6) << "Ожидаемая длина 6. По факту : " << List_int->GetLength();
    EXPECT_EQ(List_int->GetLast(), 42) << "Ожидаемый элемент 42. По факту : " << List_int->GetLast();
    EXPECT_EQ(List_int->Get(0), 42) << "Ожидаемый элемент 42. По факту : " << List_int->Get(0);
    EXPECT_EQ(List_int->Get(4), 228) << "Ожидаемый элемент 228. По факту : " << List_int->Get(4);
}


TEST_F(LinkedList_Fixture, Prepend_5){
    LinkedList<int> list;
    list.Prepend(67);
    EXPECT_EQ(list.GetLength(), 1) << "Ожидаемая длина 1. По факту : " << list.GetLength();
    EXPECT_EQ(list.GetFirst(), 67) << "Ожидаемый элемент 67. По факту : " << list.GetFirst();
    EXPECT_EQ(list.GetLast(), 67) << "Ожидаемый элемент 67. По факту : " << list.GetLast();
}

TEST_F(LinkedList_Fixture, Prepend_0){
    List_int->Prepend(52);
    EXPECT_EQ(List_int->GetLength(), 6) << "Ожидаемая длина 6. По факту : " << List_int->GetLength();
    EXPECT_EQ(List_int->GetFirst(), 52) << "Ожидаемый элемент 52. По факту : " << List_int->GetFirst();
    EXPECT_EQ(List_int->Get(1), 42) << "Ожидаемый элемент 42. По факту : " << List_int->Get(1);
    EXPECT_EQ(List_int->GetLast(), 228) << "Ожидаемый элемент 228. По факту : " << List_int->GetLast();
}


TEST_F(LinkedList_Fixture, InsertAt_first){
    List_int->InsertAt(67, 0);
    EXPECT_EQ(List_int->GetLength(), 6) << "Ожидаемая длина 6. По факту : " << List_int->GetLength();
    EXPECT_EQ(List_int->GetFirst(), 67) << "Ожидаемый элемент 67. По факту : " << List_int->GetFirst();
    EXPECT_EQ(List_int->Get(1), 42) << "Ожидаемый элемент 42. По факту : " << List_int->Get(1);
}

TEST_F(LinkedList_Fixture, InsertAt_End){
    List_int->InsertAt(666, List_int->GetLength());
    EXPECT_EQ(List_int->GetLength(), 6) << "Ожидаемая длина 6. По факту : " << List_int->GetLength();
    EXPECT_EQ(List_int->GetLast(), 666) << "Ожидаемый элемент 666. По факту : " << List_int->GetLast();
    EXPECT_EQ(List_int->Get(4), 228) << "Ожидаемый элемент 228. По факту : " << List_int->Get(4);
}

TEST_F(LinkedList_Fixture, InsertAt_middle){
    List_int->InsertAt(111, 2);
    EXPECT_EQ(List_int->GetLength(), 6) << "Ожидаемая длина 6. По факту : " << List_int->GetLength();
    EXPECT_EQ(List_int->Get(1), 52) << "Ожидаемый элемент 52. По факту : " << List_int->Get(1);
    EXPECT_EQ(List_int->Get(2), 111) << "Ожидаемый элемент 111. По факту : " << List_int->Get(2);
    EXPECT_EQ(List_int->Get(3), 69) << "Ожидаемый элемент 69. По факту : " << List_int->Get(3);
}

TEST_F(LinkedList_Fixture, InsertAt_invalid_argument){
    EXPECT_THROW(List_int->InsertAt(10, 10), invalid_argument) << "Ожидается invalid_argument для индекса 10";
    EXPECT_THROW(List_int->InsertAt(10, 100), invalid_argument) << "Ожидается invalid_argument для индекса 100";
}


TEST_F(LinkedList_Fixture, Concat){
    int extraData[2] ={1, 2};
    LinkedList<int> extraList(extraData, 2);
    size_t initialLen = List_int->GetLength();
    LinkedList<int>* concatenated = List_int->Concat(&extraList);
    EXPECT_EQ(concatenated, List_int) << "Ожидаемый тот же объект. По факту : адрес не совпадает";
    EXPECT_EQ(List_int->GetLength(), initialLen + 2) << "Ожидаемая длина " << initialLen + 2 << ". По факту : " << List_int->GetLength();
    EXPECT_EQ(List_int->Get(0), 42) << "Ожидаемый элемент 42. По факту : " << List_int->Get(0);
    EXPECT_EQ(List_int->Get(4), 228) << "Ожидаемый элемент 228. По факту : " << List_int->Get(4);
    EXPECT_EQ(List_int->Get(5), 1) << "Ожидаемый элемент 1. По факту : " << List_int->Get(5);
    EXPECT_EQ(List_int->Get(6), 2) << "Ожидаемый элемент 2. По факту : " << List_int->Get(6);
}

TEST_F(LinkedList_Fixture, Concat_0){
    LinkedList<int> empty;
    int firstVal = List_int->Get(0);
    int lastVal = List_int->Get(4);
    size_t initialLen = List_int->GetLength();
    LinkedList<int>* result = List_int->Concat(&empty);
    EXPECT_EQ(result, List_int) << "Ожидаемый тот же объект. По факту : адрес не совпадает";
    EXPECT_EQ(result->GetLength(), initialLen) << "Ожидаемая длина " << initialLen << ". По факту : " << result->GetLength();
    EXPECT_EQ(result->Get(0), firstVal) << "Ожидаемый элемент " << firstVal << ". По факту : " << result->Get(0);
    EXPECT_EQ(result->Get(4), lastVal) << "Ожидаемый элемент " << lastVal << ". По факту : " << result->Get(4);
}

TEST_F(LinkedList_Fixture, 0_Concat){
    LinkedList<int> empty;
    int extraData[2] ={1, 2};
    LinkedList<int> extra(extraData, 2);
    LinkedList<int>* result = empty.Concat(&extra);
    EXPECT_EQ(result, &empty) << "Ожидаемый тот же объект. По факту : адрес не совпадает";
    EXPECT_EQ(result->GetLength(), 2) << "Ожидаемая длина 2. По факту : " << result->GetLength();
    EXPECT_EQ(result->Get(0), 1) << "Ожидаемый элемент 1. По факту : " << result->Get(0);
    EXPECT_EQ(result->Get(1), 2) << "Ожидаемый элемент 2. По факту : " << result->Get(1);
}

//Деструктор----------------------------------------------------

TEST_F(LinkedList_Fixture, Destructor_NoLeak){
    LinkedList<int>* list = new LinkedList<int>(data_int, 5);
    delete list;
    SUCCEED();
}