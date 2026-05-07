#include "Fixtures.hpp"


//Тесты констукторов--------------------------------------------

TEST_F(Bit_Fixture, DefoltConstructor){
    Bit<char> b;
    EXPECT_EQ(b.GetValue(), 0b00000000);
    EXPECT_FALSE(b.operator bool());
}

TEST_F(Bit_Fixture, ValueConstructor){
    Bit<char> b(0b11110000);
    EXPECT_EQ(b.GetValue(), char(0b11110000));
    EXPECT_TRUE(b.operator bool());
}

TEST_F(Bit_Fixture, CopyConstructor){
    Bit<char> copy(bit8);
    EXPECT_EQ(copy.GetValue(), bit8.GetValue());
    EXPECT_EQ(copy[0], bit8[0]);
    EXPECT_EQ(copy[7], bit8[7]);
    copy.SetValue(0b00000000);
    EXPECT_EQ(bit8.GetValue(), 0b01010101);
}

//Методы--------------------------------------------------------

TEST_F(Bit_Fixture, rovno){
    Bit<char> b1, b2(0b00110011);
    b1 = b2;
    EXPECT_EQ(b1.GetValue(), b2.GetValue());
}

TEST_F(Bit_Fixture, val){
    bit8 = bit8;
    EXPECT_EQ(bit8.GetValue(), 0b01010101);
}

TEST_F(Bit_Fixture, GetBitCount){
    EXPECT_EQ(Bit<char>().GetBitCount(), 8);
    EXPECT_EQ(Bit<short int>().GetBitCount(), 16);
    EXPECT_EQ(Bit<int>().GetBitCount(), 32);
}

TEST_F(Bit_Fixture, GetValue_SetValue){
    Bit<char> b(0b00000000);
    b.SetValue(0b10101010);
    EXPECT_EQ(b.GetValue(), char(0b10101010));
}

TEST_F(Bit_Fixture, OperatorBool_True){
    Bit<char> b(0b00000001);
    EXPECT_TRUE(b.operator bool());
}

TEST_F(Bit_Fixture, OperatorBool_False){
    Bit<char> b(0b00000000);
    EXPECT_FALSE(b.operator bool());
}

TEST_F(Bit_Fixture, IndexOperator_Read_Char){
    EXPECT_EQ(bit8[0], 1);
    EXPECT_EQ(bit8[1], 0);
    EXPECT_EQ(bit8[2], 1);
    EXPECT_EQ(bit8[3], 0);
    EXPECT_EQ(bit8[6], 1);
    EXPECT_EQ(bit8[7], 0);
}

TEST_F(Bit_Fixture, IndexOperator_Int){
    EXPECT_EQ(bit32[0], 1);
    EXPECT_EQ(bit32[1], 1);
    EXPECT_EQ(bit32[2], 0);
    EXPECT_EQ(bit32[3], 0);
}

TEST_F(Bit_Fixture, invalid_argument){
    EXPECT_THROW(bit8[8], invalid_argument);
    EXPECT_THROW(bit32[32], invalid_argument);
    EXPECT_THROW(bit32[100], invalid_argument);
}

TEST_F(Bit_Fixture, IndexOperator_Write_Set1){
    Bit<char> b(0b00000000);
    b[3] = true;
    EXPECT_EQ(b.GetValue(), 0b00001000);
}

TEST_F(Bit_Fixture, IndexOperator_Write_Set0){
    Bit<char> b(0b11111111);
    b[3] = false;
    EXPECT_EQ(b.GetValue(), char(0b11110111));
}

TEST_F(Bit_Fixture, AND){
    Bit<char> a(0b11110000), b(0b00001111);
    EXPECT_EQ((a & b).GetValue(), 0b00000000);
}

TEST_F(Bit_Fixture, OR){
    Bit<char> a(0b10100000), b(0b00000101);
    EXPECT_EQ((a | b).GetValue(), char(0b10100101));
}

TEST_F(Bit_Fixture, XOR){
    Bit<char> a(0b11111111), b(0b00001111);
    EXPECT_EQ((a ^ b).GetValue(), char(0b11110000));
}

TEST_F(Bit_Fixture, NOT){
    Bit<char> a(0b00000000);
    EXPECT_EQ((~a).GetValue(), char(0b11111111));
}

TEST_F(Bit_Fixture, Comparison_Equal){
    Bit<char> a(0b01010101), b(0b01010101);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST_F(Bit_Fixture, dont_ecv_ecv){
    Bit<char> a(0b01010101), b(0b10101010);
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a == b);
}