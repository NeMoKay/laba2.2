
#pragma once
#include "sequence.hpp"
using namespace std;


template <class T>
class DynamicArray{
private:
    T* data;
    int size;
public:

    DynamicArray(){
        data = nullptr;
        size = 0;
    }
    DynamicArray(int count){
        if(count <= 0){
            throw invalid_argument("Длинна массива < 1");
        }
        size = count;
        data = new T[size];
    }

    DynamicArray(T* items, int count) :  DynamicArray(count){
        if(items == nullptr){
            throw invalid_argument("Переданный массив пуст");
        }
        for(int i = 0; i < size; i++){
            data[i] = items[i];
        }
    }

    DynamicArray(const DynamicArray<T> & other){
        size = other.size;
        data = new T[size];
        for(int i = 0; i < size; i++){
            data[i] = other.data[i];
        }
    }

    T Get(int index){
        if(index < 0 || index >= size){
            throw invalid_argument("Ошибка индекса");
        }
        return data[index];
    }


    void Set(int index, T value){
        if(index < 0 || index >= size){
            throw invalid_argument("Ошибка индекса");
        }
        data[index] = value;

    }
    void Resize(int newSize){
        if(newSize < 0){
            throw invalid_argument("Индекс < 0");
        }

        T *new_data = new T[newSize];
        if(size != 0){
            for(int i = 0; i < newSize; i++){
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


    void show(){
        for(int i = 0; i < size; i++){
            cout << data[i] << endl;
        }
    }
    ~DynamicArray(){
        delete[] data;
    }
};





