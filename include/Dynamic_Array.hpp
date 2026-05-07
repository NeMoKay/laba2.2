#pragma once

#include "sequence.hpp"
#include <iostream>
#include <stdexcept>
#include <cstddef>
using namespace std;


template <class T>
class DynamicArray{
private:
    T* data;
    size_t size;
public:

    DynamicArray() : data(nullptr), size(0) {}

    DynamicArray(size_t count){
        if(count == 0){
            throw invalid_argument("Длинна массива < 1");
        }
        size = count;
        data = new T[size];
    }

    DynamicArray(T* items, size_t count) : DynamicArray(count){
        if(items == nullptr){
            throw invalid_argument("Переданный массив пуст");
        }
        for(size_t i = 0; i < size; i++){
            data[i] = items[i];
        }
    }

    DynamicArray(const DynamicArray<T> & array) : size(array.size){
        data = new T[size];
        for(size_t i = 0; i < size; i++){
            data[i] = array.data[i];
        }
    }

    T Get(size_t index){
        if(index >= size){
            throw invalid_argument("Ошибка индекса");
        }
        return data[index];
    }


    void Set(size_t index, T value){
        if(index >= size){
            throw invalid_argument("Ошибка индекса");
        }
        data[index] = value;

    }
    void Resize(size_t newSize){

        T *new_data = new T[newSize];
        if(size != 0){
            for(size_t i = 0; i < newSize; i++){
                if(i == size-1){
                    new_data[i] = data[i];
                    break;
                }
                new_data[i] = data[i];
            }
        }
        
        delete[] data;
        data = new_data;
        size = newSize;
    };

    size_t GetSize(){
        return size;
    }
    T operator[](size_t index){
        return Get(index); 
    }

    ~DynamicArray(){
        delete[] data;
    }
};