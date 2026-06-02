#include "Fixtures.hpp"
#include "exceptions.hpp"

// Тесты конструкторов
TEST_F(Dynamic_Array_Fixture, Defoult_Constructor_invalid_argument){
    DynamicArray<int> arr;
    EXPECT_THROW(arr.Get(0), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException. По факту : исключение не выброшено";
}

TEST_F(Dynamic_Array_Fixture, SizeConstructor){
    DynamicArray<int> arr(3);

    arr.Set(0, 10);
    arr.Set(2, 30);

    EXPECT_EQ(arr.Get(0), 10) << "Ожидаемый элемент 10. По факту : " << arr.Get(0);
    EXPECT_EQ(arr.Get(2), 30) << "Ожидаемый элемент 30. По факту : " << arr.Get(2);
}

TEST_F(Dynamic_Array_Fixture, ArrayConstructor){
    int data[] = {1, 2, 3};
    DynamicArray<int> arr(data);

    EXPECT_EQ(arr.Get(0), 1) << "Ожидаемый элемент 1. По факту : " << arr.Get(0);
    EXPECT_EQ(arr.Get(1), 2) << "Ожидаемый элемент 2. По факту : " << arr.Get(1);
    EXPECT_EQ(arr.Get(2), 3) << "Ожидаемый элемент 3. По факту : " << arr.Get(2);
}

TEST_F(Dynamic_Array_Fixture, CopyConstructor){
    DynamicArray<int> copy(*array_int);

    EXPECT_EQ(copy.Get(0), 42) << "Ожидаемый элемент 42. По факту : " << copy.Get(0);
    EXPECT_EQ(copy.Get(2), 69) << "Ожидаемый элемент 69. По факту : " << copy.Get(2);
    EXPECT_EQ(copy.Get(4), 228) << "Ожидаемый элемент 228. По факту : " << copy.Get(4);

    copy.Set(0, 999);
    EXPECT_EQ(array_int->Get(0), 42) << "Ожидаемый элемент 42. По факту : " << array_int->Get(0);
}

// Методы
TEST_F(Dynamic_Array_Fixture, GET){
    EXPECT_EQ(array_int->Get(0), 42) << "Ожидаемый элемент 42. По факту : " << array_int->Get(0);
    EXPECT_EQ(array_int->Get(2), 69) << "Ожидаемый элемент 69. По факту : " << array_int->Get(2);
    EXPECT_EQ(array_int->Get(4), 228) << "Ожидаемый элемент 228. По факту : " << array_int->Get(4);

    EXPECT_STREQ(array_str->Get(0), "красный") << "Ожидаемый элемент красный. По факту : " << array_str->Get(0);
    EXPECT_STREQ(array_str->Get(3), "зеленый") << "Ожидаемый элемент зеленый. По факту : " << array_str->Get(3);
    EXPECT_STREQ(array_str->Get(4), "голубой") << "Ожидаемый элемент голубой. По факту : " << array_str->Get(4);
}

TEST_F(Dynamic_Array_Fixture, GET_invalid_argument){
    EXPECT_THROW(array_int->Get(100), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для индекса 100";
}

TEST_F(Dynamic_Array_Fixture, SET){
    array_int->Set(4, 4);
    array_str->Set(4, "розовый");

    EXPECT_EQ(array_int->Get(4), 4) << "Ожидаемый элемент 4. По факту : " << array_int->Get(4);
    EXPECT_STREQ(array_str->Get(4), "розовый") << "Ожидаемый элемент розовый. По факту : " << array_str->Get(4);
}

TEST_F(Dynamic_Array_Fixture, SET_invalid_argument){
    EXPECT_THROW(array_int->Set(100, 42), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для индекса 100";
}

TEST_F(Dynamic_Array_Fixture, Resize_positive){
    array_int->Resize(7);

    EXPECT_EQ(array_int->Get(0), 42) << "Ожидаемый элемент 42. По факту : " << array_int->Get(0);
    EXPECT_EQ(array_int->Get(2), 69) << "Ожидаемый элемент 69. По факту : " << array_int->Get(2);
    EXPECT_EQ(array_int->Get(4), 228) << "Ожидаемый элемент 228. По факту : " << array_int->Get(4);
}

TEST_F(Dynamic_Array_Fixture, Resize_negative){
    array_int->Resize(3);

    EXPECT_EQ(array_int->Get(0), 42) << "Ожидаемый элемент 42. По факту : " << array_int->Get(0);
    EXPECT_EQ(array_int->Get(2), 69) << "Ожидаемый элемент 69. По факту : " << array_int->Get(2);
    EXPECT_THROW(array_int->Get(3), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для индекса 3";
}

TEST_F(Dynamic_Array_Fixture, Resize_ToZero){
    array_int->Resize(0);

    EXPECT_THROW(array_int->Get(0), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для индекса 0";
}

TEST_F(Dynamic_Array_Fixture, Resize_1){
    array_int->Resize(1);

    EXPECT_EQ(array_int->Get(0), 42) << "Ожидаемый элемент 42. По факту : " << array_int->Get(0);
    EXPECT_THROW(array_int->Get(1), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для индекса 1";
}

TEST_F(Dynamic_Array_Fixture, Resize_Set){
    array_int->Resize(6);
    array_int->Set(5, 999);

    EXPECT_EQ(array_int->Get(5), 999) << "Ожидаемый элемент 999. По факту : " << array_int->Get(5);
}

// Деструктор
TEST_F(Dynamic_Array_Fixture, Destructor){
    DynamicArray<int>* arr = new DynamicArray<int>(3);
    delete arr;
    SUCCEED();
}