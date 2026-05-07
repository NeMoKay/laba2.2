#include "Fixtures.hpp"





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
    EXPECT_THROW(array_int->Get(100), invalid_argument);
}


TEST_F(Dynamic_Array_Fixture, SET){
    array_int->Set(4, 4);
    array_str->Set(4, "розовый");

    EXPECT_EQ(array_int->Get(4), 4);
    EXPECT_STREQ(array_str->Get(4), "розовый");
}
TEST_F(Dynamic_Array_Fixture, SET_invalid_argument){
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

//----------------Дестуктор

TEST_F(Dynamic_Array_Fixture, Destructor){
    DynamicArray<int>* arr = new DynamicArray<int>(3);
    delete arr;
    SUCCEED();
}