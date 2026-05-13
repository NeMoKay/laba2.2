#include "Fixtures.hpp"


//Тесты конструкторов--------------------------------------------

TEST_F(BitSequence_Fixture, defolt_constructor){
    BitSequence<char> bs;
    EXPECT_EQ(bs.GetLength(), 0) << "Ожидаемая длина 0. По факту : " << bs.GetLength();
    EXPECT_THROW(bs.GetFirst(), EmptySequenceException) << "Ожидается EmptySequenceException. По факту : исключение не выброшено";
}

TEST_F(BitSequence_Fixture, array_constructor){
    BitSequence<char> array(data_bits, 8);
    EXPECT_EQ(array.GetLength(), 8) << "Ожидаемая длина 8. По факту : " << array.GetLength();
    EXPECT_EQ(bool(array.Get(0)), true) << "Ожидаемый элемент 1. По факту : " << bool(array.Get(0));
    EXPECT_EQ(bool(array.Get(1)), false) << "Ожидаемый элемент 0. По факту : " << bool(array.Get(1));
    EXPECT_EQ(bool(array.Get(7)), false) << "Ожидаемый элемент 0. По факту : " << bool(array.Get(7));
}

TEST_F(BitSequence_Fixture, array_invalid_argument){
    EXPECT_THROW(BitSequence<char>(nullptr, 5), NullPtrException) << "Ожидается NullPtrException. По факту : исключение не выброшено";
}

TEST_F(BitSequence_Fixture, copy_constructor){
    BitSequence<char> copy(*Sequence);
    EXPECT_EQ(copy.GetLength(), 8) << "Ожидаемая длина 8. По факту : " << copy.GetLength();
    EXPECT_EQ(bool(copy.Get(2)), true) << "Ожидаемый элемент 1. По факту : " << bool(copy.Get(2));
    copy.Append(Bit<char>(1));
    EXPECT_EQ(Sequence->GetLength(), 8) << "Ожидаемая длина 8. По факту : " << Sequence->GetLength();
}

//Методы--------------------------------------------------------

TEST_F(BitSequence_Fixture, get_first_last){
    EXPECT_EQ(bool(Sequence->GetFirst()), true) << "Ожидаемый элемент 1. По факту : " << bool(Sequence->GetFirst());
    EXPECT_EQ(bool(Sequence->GetLast()), false) << "Ожидаемый элемент 0. По факту : " << bool(Sequence->GetLast());
}

TEST_F(BitSequence_Fixture, get_first_last_invalid_argument){
    BitSequence<char> empty;
    EXPECT_THROW(empty.GetFirst(), EmptySequenceException) << "Ожидается EmptySequenceException при GetFirst()";
    EXPECT_THROW(empty.GetLast(), EmptySequenceException) << "Ожидается EmptySequenceException при GetLast()";
}

TEST_F(BitSequence_Fixture, get){
    EXPECT_EQ(bool(Sequence->Get(0)), true) << "Ожидаемый элемент 1. По факту : " << bool(Sequence->Get(0));
    EXPECT_EQ(bool(Sequence->Get(2)), true) << "Ожидаемый элемент 1. По факту : " << bool(Sequence->Get(2));
    EXPECT_EQ(bool(Sequence->Get(1)), false) << "Ожидаемый элемент 0. По факту : " << bool(Sequence->Get(1));
    EXPECT_EQ(bool(Sequence->Get(7)), false) << "Ожидаемый элемент 0. По факту : " << bool(Sequence->Get(7));
}

TEST_F(BitSequence_Fixture, get_invalid_argument){
    EXPECT_THROW(Sequence->Get(8), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для индекса 8";
    EXPECT_THROW(Sequence->Get(100), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для индекса 100";
}

TEST_F(BitSequence_Fixture, get_length){
    EXPECT_EQ(Sequence->GetLength(), 8) << "Ожидаемая длина 8. По факту : " << Sequence->GetLength();
}

TEST_F(BitSequence_Fixture, append){
    Sequence->Append(Bit<char>(1));
    EXPECT_EQ(Sequence->GetLength(), 9) << "Ожидаемая длина 9. По факту : " << Sequence->GetLength();
    EXPECT_EQ(bool(Sequence->GetLast()), true) << "Ожидаемый элемент 1. По факту : " << bool(Sequence->GetLast());
}

TEST_F(BitSequence_Fixture, prepend){
    Sequence->Prepend(Bit<char>(0));
    EXPECT_EQ(Sequence->GetLength(), 9) << "Ожидаемая длина 9. По факту : " << Sequence->GetLength();
    EXPECT_EQ(bool(Sequence->GetFirst()), false) << "Ожидаемый элемент 0. По факту : " << bool(Sequence->GetFirst());
    EXPECT_EQ(bool(Sequence->Get(1)), true) << "Ожидаемый элемент 1. По факту : " << bool(Sequence->Get(1));
}

TEST_F(BitSequence_Fixture, insert_begin){
    Sequence->InsertAt(Bit<char>(0), 0);
    EXPECT_EQ(Sequence->GetLength(), 9) << "Ожидаемая длина 9. По факту : " << Sequence->GetLength();
    EXPECT_EQ(bool(Sequence->GetFirst()), false) << "Ожидаемый элемент 0. По факту : " << bool(Sequence->GetFirst());
    EXPECT_EQ(bool(Sequence->Get(1)), true) << "Ожидаемый элемент 1. По факту : " << bool(Sequence->Get(1));
}

TEST_F(BitSequence_Fixture, insert_middle){
    Sequence->InsertAt(Bit<char>(1), 3);
    EXPECT_EQ(Sequence->GetLength(), 9) << "Ожидаемая длина 9. По факту : " << Sequence->GetLength();
    EXPECT_EQ(bool(Sequence->Get(3)), true) << "Ожидаемый элемент 1. По факту : " << bool(Sequence->Get(3));
    EXPECT_EQ(bool(Sequence->Get(4)), false) << "Ожидаемый элемент 0. По факту : " << bool(Sequence->Get(4));
}

TEST_F(BitSequence_Fixture, insert_end){
    size_t len = Sequence->GetLength();
    Sequence->InsertAt(Bit<char>(1), len);
    EXPECT_EQ(Sequence->GetLength(), len + 1) << "Ожидаемая длина " << len + 1 << ". По факту : " << Sequence->GetLength();
    EXPECT_EQ(bool(Sequence->GetLast()), true) << "Ожидаемый элемент 1. По факту : " << bool(Sequence->GetLast());
}

TEST_F(BitSequence_Fixture, insert_invalid_argument){
    EXPECT_THROW(Sequence->InsertAt(Bit<char>(1), 9), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для индекса 9";
    EXPECT_THROW(Sequence->InsertAt(Bit<char>(1), 100), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для индекса 100";
}

TEST_F(BitSequence_Fixture, concat){
    Bit<char> extra[2] ={Bit<char>(1), Bit<char>(0)};
    BitSequence<char> extraSeq(extra, 2);
    size_t initLen = Sequence->GetLength();
    Sequence->Concat(&extraSeq);
    EXPECT_EQ(Sequence->GetLength(), initLen + 2) << "Ожидаемая длина " << initLen + 2 << ". По факту : " << Sequence->GetLength();
    EXPECT_EQ(bool(Sequence->Get(8)), true) << "Ожидаемый элемент 1. По факту : " << bool(Sequence->Get(8));
    EXPECT_EQ(bool(Sequence->Get(9)), false) << "Ожидаемый элемент 0. По факту : " << bool(Sequence->Get(9));
}

TEST_F(BitSequence_Fixture, concat_null){
    Bit<char> first = Sequence->GetFirst();
    Sequence->Concat(nullptr);
    EXPECT_EQ(Sequence->GetLength(), 8) << "Ожидаемая длина 8. По факту : " << Sequence->GetLength();
    EXPECT_EQ(bool(Sequence->GetFirst()), bool(first)) << "Ожидаемый элемент " << bool(first) << ". По факту : " << bool(Sequence->GetFirst());
}

TEST_F(BitSequence_Fixture, subseq){
    BitSequence<char>* sub = Sequence->GetSubsequence(1, 4);
    EXPECT_EQ(sub->GetLength(), 4) << "Ожидаемая длина 4. По факту : " << sub->GetLength();
    EXPECT_EQ(bool(sub->Get(0)), false) << "Ожидаемый элемент 0. По факту : " << bool(sub->Get(0));
    EXPECT_EQ(bool(sub->Get(1)), true) << "Ожидаемый элемент 1. По факту : " << bool(sub->Get(1));
    EXPECT_EQ(bool(sub->Get(2)), false) << "Ожидаемый элемент 0. По факту : " << bool(sub->Get(2));
    EXPECT_EQ(bool(sub->Get(3)), true) << "Ожидаемый элемент 1. По факту : " << bool(sub->Get(3));
    delete sub;
}

TEST_F(BitSequence_Fixture, Sequence_invalid_argument){
    EXPECT_THROW(Sequence->GetSubsequence(2, 1), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для диапазона (2,1)";
    EXPECT_THROW(Sequence->GetSubsequence(2, 10), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для диапазона (2,10)";
    EXPECT_THROW(Sequence->GetSubsequence(5, 8), IndexOutOfRangeException) << "Ожидается IndexOutOfRangeException для диапазона (5,8)";
}

//Битовые операции----------------------------------------------

TEST_F(BitSequence_Fixture, AND){
    Bit<char> other_bits[8] ={
        Bit<char>(1), Bit<char>(1), Bit<char>(0), Bit<char>(0),
        Bit<char>(1), Bit<char>(1), Bit<char>(0), Bit<char>(0)
    };
    BitSequence<char> other(other_bits, 8);
    
    BitSequence<char> result = (*Sequence) & other;
    
    EXPECT_EQ(result.GetLength(), 8) << "Функция выполнения AND (&)" << endl << "Ожидаемая длина 8. По факту : " << result.GetLength();
    EXPECT_EQ(bool(result.Get(0)), true)   << "Функция выполнения AND (&)" << endl << "Ожидаемый элемент 1. По факту : " << bool(result.Get(0));
    EXPECT_EQ(bool(result.Get(1)), false)  << "Функция выполнения AND (&)" << endl << "Ожидаемый элемент 0. По факту : " << bool(result.Get(1));
    EXPECT_EQ(bool(result.Get(2)), false)  << "Функция выполнения AND (&)" << endl << "Ожидаемый элемент 0. По факту : " << bool(result.Get(2));
    EXPECT_EQ(bool(result.Get(7)), false)  << "Функция выполнения AND (&)" << endl << "Ожидаемый элемент 0. По факту : " << bool(result.Get(7));
}

TEST_F(BitSequence_Fixture, AND_diff_length){
    Bit<char> short_bits[4] ={Bit<char>(1), Bit<char>(0), Bit<char>(1), Bit<char>(0)};
    BitSequence<char> short_seq(short_bits, 4);
    
    EXPECT_THROW((*Sequence) & short_seq, LengthMismatchException) << "Ожидается LengthMismatchException при разных длинах";
}

TEST_F(BitSequence_Fixture, OR){
    Bit<char> other_bits[8] ={
        Bit<char>(0), Bit<char>(0), Bit<char>(1), Bit<char>(1),
        Bit<char>(0), Bit<char>(0), Bit<char>(1), Bit<char>(1)
    };
    BitSequence<char> other(other_bits, 8);
    
    BitSequence<char> result = (*Sequence) | other;
    
    EXPECT_EQ(result.GetLength(), 8) << "Функция выполнения OR (|)" << endl << "Ожидаемая длина 8. По факту : " << result.GetLength();
    EXPECT_EQ(bool(result.Get(0)), true)   << "Функция выполнения OR (|)" << endl << "Ожидаемый элемент 1. По факту : " << bool(result.Get(0));
    EXPECT_EQ(bool(result.Get(1)), false)  << "Функция выполнения OR (|)" << endl << "Ожидаемый элемент 0. По факту : " << bool(result.Get(1));
    EXPECT_EQ(bool(result.Get(2)), true)   << "Функция выполнения OR (|)" << endl << "Ожидаемый элемент 1. По факту : " << bool(result.Get(2));
    EXPECT_EQ(bool(result.Get(3)), true)   << "Функция выполнения OR (|)" << endl << "Ожидаемый элемент 1. По факту : " << bool(result.Get(3));
}

TEST_F(BitSequence_Fixture, XOR){
    Bit<char> other_bits[8] ={
        Bit<char>(1), Bit<char>(1), Bit<char>(0), Bit<char>(0),
        Bit<char>(0), Bit<char>(0), Bit<char>(1), Bit<char>(1)
    };
    BitSequence<char> other(other_bits, 8);
    
    BitSequence<char> result = (*Sequence) ^ other;
    
    EXPECT_EQ(result.GetLength(), 8) << "Функция выполнения XOR (^)" << endl << "Ожидаемая длина 8. По факту : " << result.GetLength();
    EXPECT_EQ(bool(result.Get(0)), false)  << "Функция выполнения XOR (^)" << endl << "Ожидаемый элемент 0. По факту : " << bool(result.Get(0));
    EXPECT_EQ(bool(result.Get(1)), true)   << "Функция выполнения XOR (^)" << endl << "Ожидаемый элемент 1. По факту : " << bool(result.Get(1));
    EXPECT_EQ(bool(result.Get(2)), true)   << "Функция выполнения XOR (^)" << endl << "Ожидаемый элемент 1. По факту : " << bool(result.Get(2));
    EXPECT_EQ(bool(result.Get(4)), true)   << "Функция выполнения XOR (^)" << endl << "Ожидаемый элемент 1. По факту : " << bool(result.Get(4));
}

TEST_F(BitSequence_Fixture, NOT){
    BitSequence<char> result = ~(*Sequence);
    
    EXPECT_EQ(result.GetLength(), 8) << "Функция выполнения NOT (~)" << endl << "Ожидаемая длина 8. По факту : " << result.GetLength();
    EXPECT_EQ(bool(result.Get(0)), false)  << "Функция выполнения NOT (~)" << endl << "Ожидаемый элемент 0. По факту : " << bool(result.Get(0));
    EXPECT_EQ(bool(result.Get(1)), true)   << "Функция выполнения NOT (~)" << endl << "Ожидаемый элемент 1. По факту : " << bool(result.Get(1));
    EXPECT_EQ(bool(result.Get(2)), false)  << "Функция выполнения NOT (~)" << endl << "Ожидаемый элемент 0. По факту : " << bool(result.Get(2));
    EXPECT_EQ(bool(result.Get(7)), true)   << "Функция выполнения NOT (~)" << endl << "Ожидаемый элемент 1. По факту : " << bool(result.Get(7));
}

//Деструктор----------------------------------------------------

TEST_F(BitSequence_Fixture, destructor){
    BitSequence<char>* bs = new BitSequence<char>(data_bits, 8);
    delete bs;
    SUCCEED();
}