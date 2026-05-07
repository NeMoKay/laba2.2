#include "Fixtures.hpp"


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
    EXPECT_THROW(List_int->InsertAt(10, 10), invalid_argument);
    EXPECT_THROW(List_int->InsertAt(10, 100), invalid_argument);
}


TEST_F(LinkedList_Fixture, Concat){
    int extraData[2] ={1, 2};
    LinkedList<int> extraList(extraData, 2);
    size_t initialLen = List_int->GetLength();
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
    size_t initialLen = List_int->GetLength();
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