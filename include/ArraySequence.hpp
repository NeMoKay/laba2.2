#pragma once

#include "sequence.hpp"
#include "Dynamic_Array.hpp"
#include "LinkedList.hpp"
#include "iostream"
#include <cstddef>
#include <stdexcept>
using namespace std;

template <class T>
class ArraySequence : public Sequence<T>{
private:
    DynamicArray<T>* items;
protected:
    virtual ArraySequence<T>* Clone() const{
        ArraySequence<T>* copy = new  ArraySequence<T>(*this);
        return copy;
        
    }
    virtual ArraySequence<T>* Instance(){
        return this;
        
    }
    
    void AppendInternal(T item){
        
        items->Resize(items->GetSize()+1);
        items->Set(items->GetSize()-1, item);
    }

    void PrependInternal(T item){
        items->Resize(items->GetSize()+1);
        
        for(size_t i = items->GetSize() - 1; i >= 1; i--){
            items->Set(i, items->Get(i-1));
        }
        items->Set(0, item);
    }

    void InsertAtInternal(T item, size_t index){
        if(index > items->GetSize()){
            throw invalid_argument("Ошибка индекса");
        }

        if(index == 0){
            PrependInternal(item);
            return;
        }
        
        if(index == items->GetSize()){
            AppendInternal(item);
            return;
        }

        items->Resize(items->GetSize() + 1);
        for(size_t i = items->GetSize() - 1; i > index; --i){
            items->Set(i, items->Get(i - 1));
        }
        
        items->Set(index, item);
    }


    void ConcatInternal(Sequence <T> *list){
        for(size_t i = 0; i < list->GetLength(); i++){
            this->AppendInternal(list->Get(i));
        }
    }

public:
    ArraySequence(T* new_items, size_t count) : items(new DynamicArray<T>(new_items, count)){}

    ArraySequence() : items(new DynamicArray<T>) {}

    ArraySequence(const ArraySequence<T>& operand) : items(new DynamicArray<T>(*(operand.items))){}

    ArraySequence(const LinkedList<T>& list){
        size_t count = list.GetLength();
        if(count == 0){
            items = new DynamicArray<T>;
            return;
        }
        T* temp_arr = new T[count];

        for(size_t i = 0; i < count; ++i){
            temp_arr[i] = list.Get(i);
        }
        items = new DynamicArray<T>(temp_arr, count);
        delete[] temp_arr;
    }
 
    T GetFirst() const override{
        if(items->GetSize() == 0){
            throw invalid_argument("Список пуст");
        }
        return items->Get(0);
    }
    T GetLast() const override{
        if(items->GetSize() == 0){
            throw invalid_argument("Список пуст");
        }
        return items->Get(items->GetSize() - 1);
    }

    T Get(size_t index)const override{
        if(index >= items->GetSize()){
            throw invalid_argument("Ошибка индекса");
        }
        return items->Get(index);
    }
    
    size_t GetLength() const override{
        return items->GetSize();
    }


    ArraySequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override{
        if(endIndex < startIndex || startIndex >= items->GetSize() || endIndex >= items->GetSize()){
            throw invalid_argument("Ошибка индекса");
        }
        size_t len = endIndex-startIndex+1;
        ArraySequence<T>* new_arr = new ArraySequence<T>;

        for(size_t i = 0; i < len; i++){
            new_arr->Append(items->Get(startIndex + i));
        }
        return new_arr;
    }

    ArraySequence<T>* Append(T item) override{
        ArraySequence<T>* type_Arr = this->Instance();
        type_Arr->AppendInternal(item);
        return type_Arr;
    }

    ArraySequence<T>* Prepend(T item) override{
        ArraySequence<T>* type_Arr = this->Instance();
        type_Arr->PrependInternal(item);
        return type_Arr;
    }

    ArraySequence<T>* InsertAt(T item, size_t index) override{
        ArraySequence<T>* arr = this->Instance();
        arr->InsertAtInternal(item, index);
        return arr;
    }

    ArraySequence<T>* Concat(Sequence<T>* list) override{
        if(list == nullptr){
             return this;
        }
        ArraySequence<T>* type_Arr = this->Instance();
        type_Arr->ConcatInternal(list);
        return type_Arr;
    }

    template<typename T2>
    Sequence<T2>* Map(T2 (*funk)(T)){

        Sequence<T2>* result = new ArraySequence<T2>;

        for(size_t i = 0; i < this->GetLength();i++){

            result->Append(funk(this->Get(i)));
        }
        return result;
    }

    template<typename T2>
    T2 Reduce(T2 (*func)(T2, T), T2 start_val){
        T2 result = start_val;
        
        for(size_t i = 0; i < this->GetLength(); i++){
            result = func(result, this->Get(i));
        }
        return result;
    }


    Sequence<T>* Where(bool (*check_funk)(T)){

        Sequence<T>* result = new ArraySequence<T>;

        for(size_t i = 0; i < this->GetLength(); i++){
            T item = this->Get(i);
            if(check_funk(item)){
                result->Append(item);
            }
        }
        return result;
    }

    ~ArraySequence(){
        delete items;
    }
};

template <typename T>
class MutableArraySequence : public ArraySequence<T>{
protected:
    ArraySequence<T>* Clone() const override{
        return new MutableArraySequence<T>(*this);
    }
    ArraySequence<T>* Instance() override{
        return this;
    }
public:
    using ArraySequence<T> ::  ArraySequence;
};

template <typename T>
class ImmutableArraySequence : public ArraySequence<T>{
protected:
    ArraySequence<T>* Clone() const override{
        return new ImmutableArraySequence<T>(*this);
    }
    ArraySequence<T>* Instance() override{
        return Clone();
    }

public:
    using ArraySequence<T> ::  ArraySequence;

};