#pragma once

#include "iostream"
#include <cstddef>
#include <stdexcept>
using namespace std;


template <typename T>
class BitProxy{
private:

    T& start_data;
    size_t bitIndex;

public:
    BitProxy(T& value, size_t index) : start_data(value), bitIndex(index){}

    BitProxy& operator=(bool value){
        if(value == 1){
            start_data = start_data | (static_cast<T>(1) << bitIndex);
        }
        
        else{
            start_data = start_data & ~(static_cast<T>(1) << bitIndex);
        }
        return *this;
    }

    operator bool() const{
        return (start_data >> bitIndex) & static_cast<T>(1);
    }
};



template <typename T>
class Bit{
private:
    T value;

protected:

    void CheckIndex(size_t index){
        if(index >= sizeof(T) * 8){
            throw invalid_argument("Индекс вне диапазона");
        }
    }

public:

    Bit() : value(0) {} 

    Bit(T val) : value(val) {}

    Bit(const Bit& operand) : value(operand.value) {}


    Bit& operator=(const Bit& operand){
        if(this != &operand){
            value = operand.value;
        }
        return *this;
    }
    
    size_t GetBitCount(){
        return sizeof(T) * 8;
    }
    
    bool operator[](size_t index) const{
        CheckIndex(index);
        return (value >> index) & static_cast<T>(1);
    }
    
    BitProxy<T> operator[](size_t index){
        CheckIndex(index);
        return BitProxy<T>(value, index);
    }
    
    T GetValue() const{ 
        return value;
    
    }
    void SetValue(T val){ 
        value = val; 
    }
    
    operator bool() const{ 
        return value != 0; 
    }
    
    Bit operator&(const Bit& operand) const{
        return Bit(value & operand.value);
    }
    Bit operator|(const Bit& operand) const{
        return Bit(value | operand.value);
    }
    Bit operator^(const Bit& operand) const{
        return Bit(value ^ operand.value);
    }
    Bit operator~() const{
        return Bit(~value);
    }
    
    bool operator==(const Bit& operand) const{
        return value == operand.value;
    }
    
    bool operator!=(const Bit& operand) const{
        return value != operand.value;
    }
};