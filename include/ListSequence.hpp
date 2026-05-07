#pragma once

#include "sequence.hpp"
#include "LinkedList.hpp"
#include "iostream"
#include <cstddef>
#include <stdexcept>

using namespace std;

template <class T> 
class ListSequence : public Sequence<T>{
private:
    LinkedList<T>* items;
protected:

    virtual ListSequence<T>* Clone() const{
        return new ListSequence<T> (*this);
    }
    virtual ListSequence<T>* Instance(){
        return this;
        
    }

    void AppendInternal(T item){
        items->Append(item);
    }
    void PrependInternal(T item){
        items->Prepend(item);    
    }
    void InsertAtInternal(T item, size_t index){
        if(index > items->GetLength()){
            throw invalid_argument("Индекс вне диапазона");
        }
        items->InsertAt(item, index);
    }

    void ConcatInternal(Sequence<T>* list){
        if(list == nullptr){
            return;
        }
        for(size_t i = 0; i < list->GetLength(); i++){
            items->Append(list->Get(i));
        }
    }

public:

    ListSequence(T* new_items, size_t count) : items(new LinkedList<T>(new_items, count)) {}

    ListSequence() : items(new LinkedList<T>) {}

    ListSequence(const ListSequence <T> &list) : items(new LinkedList<T>(*(list.items))) {}

    ListSequence(const ArraySequence<T>& arraySeq) : ListSequence(){
        size_t count = arraySeq.GetLength();
        for(size_t i = 0; i < count; ++i){
            items->Append(arraySeq.Get(i));
        }
    }

    T GetFirst() const override{
        return items->Get(0);
    }
    T GetLast() const override{
        return items->Get(items->GetLength()-1);
    }

    T Get(size_t index)const override{
        return items->Get(index);
    }

    ListSequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override{
        if(endIndex < startIndex || startIndex >= items->GetLength() || endIndex >= items->GetLength()){
            throw invalid_argument("Ошибка индекса");
        }

        LinkedList<T>* items_sub_list;
        items_sub_list = items->GetSubList(startIndex, endIndex);

        ListSequence<T>* Sub_list = new ListSequence<T>;
        for(size_t i = 0; i < items_sub_list->GetLength(); i++){
            Sub_list->Append(items_sub_list->Get(i));
        }

        return Sub_list;
    }
    size_t GetLength() const override{
        return items->GetLength();

    }




    ListSequence<T>* Append(T item) override{
        ListSequence<T>* list = Instance();
        list->AppendInternal(item);
        return list;
    }
    ListSequence<T>* Prepend(T item) override{
        ListSequence<T>* list = Instance();
        list->PrependInternal(item);
        return list;     
    }
    ListSequence<T>* InsertAt(T item, size_t index) override{
        if(index > items->GetLength()){
            throw invalid_argument("Индекс вне диапазона");
        }
        ListSequence<T>* list = Instance();
        list->InsertAtInternal(item, index);
        return list;
    }
    Sequence <T>* Concat(Sequence <T> *list_p) override{
        ListSequence<T>* list = Instance();
        if(list_p == nullptr){
            return list;
        }
        else{
            for(size_t i = 0; i < list_p->GetLength(); i++){
                list->AppendInternal(list_p->Get(i));
            }
            return list;
        }
    }


    template<typename T2>
    Sequence<T2>* Map(T2 (*funk)(T)){

        Sequence<T2>* result = new ListSequence<T2>;

        for(size_t i = 0; i < this->GetLength(); i++){
            result->Append(funk(this->Get(i)));
        }
        return result;
    }


    template<typename T2>
    T2 Reduce(T2 (*funk)(T2, T), T2 start_val){
        T2 result = start_val;

        for(size_t i = 0; i < this->GetLength(); i++){
            result = funk(result, this->Get(i));
        }
        return result;
    }

    Sequence<T>* Where(bool (*check_funk)(T)){

        Sequence<T>* result = new ListSequence<T>;
        for(size_t i = 0; i < this->GetLength(); i++){
            T item = this->Get(i);
            if(check_funk(item)){
                result->Append(item);
            }
        }
        return result;
    }
    ~ListSequence(){
        delete items;
    }
};


template <typename T>
class MutableListSequence : public ListSequence<T>{
protected:
    ListSequence<T>* Clone() const override{
        return new MutableListSequence<T>(*this);
    }
    ListSequence<T>* Instance() override{
        return this;
    }
    
public:
    using ListSequence<T> :: ListSequence;
};


template <typename T>
class ImmutableListSequence : public ListSequence<T>{
protected:
    ListSequence<T>* Clone() const override{
        return new ImmutableListSequence<T>(*this);
    }
    ListSequence<T>* Instance() override{
        return Clone();
    }
public:
    using ListSequence<T> :: ListSequence;
};