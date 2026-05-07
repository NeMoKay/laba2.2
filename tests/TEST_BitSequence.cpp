#include "Fixtures.hpp"




//Тесты конструкторов--------------------------------------------
TEST_F(BitSequence_Fixture, defolt_constructor){
    BitSequence<char> bs;
    EXPECT_EQ(bs.GetLength(), 0);
    EXPECT_THROW(bs.GetFirst(), invalid_argument);
}

TEST_F(BitSequence_Fixture, array_constructor){
    BitSequence<char> array(data_bits, 8);
    EXPECT_EQ(array.GetLength(), 8);
    EXPECT_EQ(array.Get(0).operator bool(), true);
    EXPECT_EQ(array.Get(1).operator bool(), false);
    EXPECT_EQ(array.Get(7).operator bool(), false);
}

TEST_F(BitSequence_Fixture, array_invalid_argument){
    EXPECT_THROW(BitSequence<char>(nullptr, 5), invalid_argument);
}

TEST_F(BitSequence_Fixture, copy_constructor){
    BitSequence<char> copy(*Sequence);
    EXPECT_EQ(copy.GetLength(), 8);
    EXPECT_EQ(copy.Get(2).operator bool(), true);
    copy.Append(Bit<char>(1));
    EXPECT_EQ(Sequence->GetLength(), 8);
}

//Методы--------------------------------------------------------

TEST_F(BitSequence_Fixture, get_first_last){
    EXPECT_EQ(Sequence->GetFirst().operator bool(), true);
    EXPECT_EQ(Sequence->GetLast().operator bool(), false);
}
TEST_F(BitSequence_Fixture, get_first_last_invalid_argument){
    BitSequence<char> empty;
    EXPECT_THROW(empty.GetFirst(), invalid_argument);
    EXPECT_THROW(empty.GetLast(), invalid_argument);
}

TEST_F(BitSequence_Fixture, get){
    EXPECT_EQ(Sequence->Get(0).operator bool(), true);
    EXPECT_EQ(Sequence->Get(2).operator bool(), true);
    EXPECT_EQ(Sequence->Get(1).operator bool(), false);
    EXPECT_EQ(Sequence->Get(7).operator bool(), false);
}

TEST_F(BitSequence_Fixture, get_invalid_argument){
    EXPECT_THROW(Sequence->Get(8), invalid_argument);
    EXPECT_THROW(Sequence->Get(100), invalid_argument);
}

TEST_F(BitSequence_Fixture, get_length){
    EXPECT_EQ(Sequence->GetLength(), 8);
}

TEST_F(BitSequence_Fixture, append){
    Sequence->Append(Bit<char>(1));
    EXPECT_EQ(Sequence->GetLength(), 9);
    EXPECT_EQ(Sequence->GetLast().operator bool(), true);
}

TEST_F(BitSequence_Fixture, prepend){
    Sequence->Prepend(Bit<char>(0));
    EXPECT_EQ(Sequence->GetLength(), 9);
    EXPECT_EQ(Sequence->GetFirst().operator bool(), false);
    EXPECT_EQ(Sequence->Get(1).operator bool(), true);
}

TEST_F(BitSequence_Fixture, insert_begin){
    Sequence->InsertAt(Bit<char>(0), 0);
    EXPECT_EQ(Sequence->GetLength(), 9);
    EXPECT_EQ(Sequence->GetFirst().operator bool(), false);
    EXPECT_EQ(Sequence->Get(1).operator bool(), true);
}

TEST_F(BitSequence_Fixture, insert_middle){
    Sequence->InsertAt(Bit<char>(1), 3);
    EXPECT_EQ(Sequence->GetLength(), 9);
    EXPECT_EQ(Sequence->Get(3).operator bool(), true);
    EXPECT_EQ(Sequence->Get(4).operator bool(), false);
}

TEST_F(BitSequence_Fixture, insert_end){
    size_t len = Sequence->GetLength();
    Sequence->InsertAt(Bit<char>(1), len);
    EXPECT_EQ(Sequence->GetLength(), len + 1);
    EXPECT_EQ(Sequence->GetLast().operator bool(), true);
}

TEST_F(BitSequence_Fixture, insert_invalid_argument){
    EXPECT_THROW(Sequence->InsertAt(Bit<char>(1), 9), invalid_argument);
    EXPECT_THROW(Sequence->InsertAt(Bit<char>(1), 100), invalid_argument);
}

TEST_F(BitSequence_Fixture, concat){
    Bit<char> extra[2] = {Bit<char>(1), Bit<char>(0)};
    BitSequence<char> extraSeq(extra, 2);
    size_t initLen = Sequence->GetLength();
    Sequence->Concat(&extraSeq);
    EXPECT_EQ(Sequence->GetLength(), initLen + 2);
    EXPECT_EQ(Sequence->Get(8).operator bool(), true);
    EXPECT_EQ(Sequence->Get(9).operator bool(), false);
}

TEST_F(BitSequence_Fixture, concat_null){
    Bit<char> first = Sequence->GetFirst();
    Sequence->Concat(nullptr);
    EXPECT_EQ(Sequence->GetLength(), 8);
    EXPECT_EQ(Sequence->GetFirst().operator bool(), first.operator bool());
}

TEST_F(BitSequence_Fixture, subseq){
    BitSequence<char>* sub = Sequence->GetSubsequence(1, 4);
    EXPECT_EQ(sub->GetLength(), 4);
    EXPECT_EQ(sub->Get(0).operator bool(), false);
    EXPECT_EQ(sub->Get(1).operator bool(), true);
    EXPECT_EQ(sub->Get(2).operator bool(), false);
    EXPECT_EQ(sub->Get(3).operator bool(), true);
    delete sub;
}

TEST_F(BitSequence_Fixture, Sequence_invalid_argument){
    EXPECT_THROW(Sequence->GetSubsequence(2, 1), invalid_argument);
    EXPECT_THROW(Sequence->GetSubsequence(2, 10), invalid_argument);
    EXPECT_THROW(Sequence->GetSubsequence(5, 8), invalid_argument);
}

TEST_F(BitSequence_Fixture, AND){
    Bit<char> other_bits[8] = {
        Bit<char>(1), Bit<char>(1), Bit<char>(0), Bit<char>(0),
        Bit<char>(1), Bit<char>(1), Bit<char>(0), Bit<char>(0)
    };
    BitSequence<char> other(other_bits, 8);
    
    BitSequence<char> result = (*Sequence) & other;
    
    EXPECT_EQ(result.GetLength(), 8);
    EXPECT_EQ(result.Get(0).operator bool(), true);   
    EXPECT_EQ(result.Get(1).operator bool(), false);  
    EXPECT_EQ(result.Get(2).operator bool(), false);  
    EXPECT_EQ(result.Get(7).operator bool(), false);  
}

TEST_F(BitSequence_Fixture, AND_diff_length){
    Bit<char> short_bits[4] = {Bit<char>(1), Bit<char>(0), Bit<char>(1), Bit<char>(0)};
    BitSequence<char> short_seq(short_bits, 4);
    
    EXPECT_THROW((*Sequence) & short_seq, invalid_argument);
}

TEST_F(BitSequence_Fixture, OR){
    Bit<char> other_bits[8] = {
        Bit<char>(0), Bit<char>(0), Bit<char>(1), Bit<char>(1),
        Bit<char>(0), Bit<char>(0), Bit<char>(1), Bit<char>(1)
    };
    BitSequence<char> other(other_bits, 8);
    
    BitSequence<char> result = (*Sequence) | other;
    
    EXPECT_EQ(result.GetLength(), 8);
    EXPECT_EQ(result.Get(0).operator bool(), true);   
    EXPECT_EQ(result.Get(1).operator bool(), false);  
    EXPECT_EQ(result.Get(2).operator bool(), true);   
    EXPECT_EQ(result.Get(3).operator bool(), true);   
}

TEST_F(BitSequence_Fixture, XOR){
    Bit<char> other_bits[8] = {
        Bit<char>(1), Bit<char>(1), Bit<char>(0), Bit<char>(0),
        Bit<char>(0), Bit<char>(0), Bit<char>(1), Bit<char>(1)
    };
    BitSequence<char> other(other_bits, 8);
    
    BitSequence<char> result = (*Sequence) ^ other;
    
    EXPECT_EQ(result.GetLength(), 8);
    EXPECT_EQ(result.Get(0).operator bool(), false);  
    EXPECT_EQ(result.Get(1).operator bool(), true);   
    EXPECT_EQ(result.Get(2).operator bool(), true);   
    EXPECT_EQ(result.Get(4).operator bool(), true);   
}

TEST_F(BitSequence_Fixture, NOT){
    BitSequence<char> result = ~(*Sequence);
    
    EXPECT_EQ(result.GetLength(), 8);
    EXPECT_EQ(result.Get(0).operator bool(), false);  
    EXPECT_EQ(result.Get(1).operator bool(), true);   
    EXPECT_EQ(result.Get(2).operator bool(), false);  
    EXPECT_EQ(result.Get(7).operator bool(), true);   
}

//Деструктор----------------------------------------------------

TEST_F(BitSequence_Fixture, destructor){
    BitSequence<char>* bs = new BitSequence<char>(data_bits, 8);
    delete bs;
    SUCCEED();
}