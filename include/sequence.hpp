#pragma once
#include "sequence.hpp"
#include "Dynamic_Array.hpp"
#include "LinkedList.hpp"
using namespace std;


template <typename T>
class Sequence{
    public:
        virtual ~Sequence() = default;
        virtual T GetFirst()  const = 0;
        virtual T GetLast() const = 0;
        virtual T Get(int index) const = 0;
        virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
        virtual int GetLength() const = 0; 
        virtual Sequence<T>* Append(T item) = 0;
        virtual Sequence<T>* Prepend(T item) = 0;
        virtual Sequence<T>* InsertAt(T item, int index) = 0;
        virtual Sequence <T>* Concat(Sequence <T> *list) = 0;
        virtual void show() = 0;

        T operator[](int index){ 
            return Get(index); 
        }
};


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
        
        for(int i = items->GetSize() - 1; i >= 1; i--){
            items->Set(i, items->Get(i-1));
        }
        items->Set(0, item);
    }

    void InsertAtInternal(T item, int index){
        if (index < 0 || index > items->GetSize()) {
            throw invalid_argument("Ошибка индекса");
        }

        if (index == 0) {
            PrependInternal(item);
        }
        
        if (index == items->GetSize()) {
            AppendInternal(item);
        }

        items->Resize(items->GetSize() + 1);
        for (int i = items->GetSize() - 1; i > index; --i) {
            items->Set(i, items->Get(i - 1));
        }
        
        items->Set(index, item);
    }


    void ConcatInternal(Sequence <T> *list){
        for(int i = 0; i < list->GetLength(); i++){
            this->AppendInternal(list->Get(i));
        }
    }

public:
    ArraySequence (T* new_items, int count){
        if (count < 0){
            throw invalid_argument("Размер не может быть отрицательным");
        }
        items = new DynamicArray<T>(new_items, count);

    }
    ArraySequence(){
        items = new DynamicArray<T>();
    }

    ArraySequence(const ArraySequence<T>& other){
        items = new DynamicArray<T>(*(other.items)); 
    }

    ArraySequence(const LinkedList<T>& list) {
        int count = list.GetLength();
        if (count == 0) {
            items = new DynamicArray<T>();
            return;
        }
        T* temp_arr = new T[count];
        for (int i = 0; i < count; ++i) {
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

    T Get(int index)const override{
        if(index >= items->GetSize() || index < 0){
            throw invalid_argument("Ошибка индекса");
        }
        return items->Get(index);
    }
    
    int GetLength() const override{
        return items->GetSize();
    }


    ArraySequence<T>* GetSubsequence(int startIndex, int endIndex) const override{
        if(startIndex < 0 || endIndex < 0 || endIndex < startIndex || startIndex >= items->GetSize() || endIndex >= items->GetSize()){
            throw invalid_argument("Ошибка индекса");
        }
        int len = endIndex-startIndex+1;
        ArraySequence<T>* new_arr = new ArraySequence<T>;

        for(int i = 0; i < len; i++){
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

    ArraySequence<T>* InsertAt(T item, int index) override{
        ArraySequence<T>* target = this->Instance();
        target->InsertAtInternal(item, index);
        return target;
    }

    ArraySequence<T>* Concat(Sequence<T>* list) override{
        if (list == nullptr){
             return this;
        }
        ArraySequence<T>* type_Arr = this->Instance();
        type_Arr->ConcatInternal(list);
        return type_Arr;
    }


    void show() override{
        items->show();
    }

    ~ArraySequence() {
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
    ArraySequence<T>* Clone() const override {
        return new ImmutableArraySequence<T>(*this);
    }
    ArraySequence<T>* Instance() override{
        return Clone();
    }

public:
    using ArraySequence<T> ::  ArraySequence;

};






//list--------------------------------------------------
//list--------------------------------------------------
//list--------------------------------------------------
//list--------------------------------------------------





template <class T> 
class ListSequence : public Sequence<T>{
private:
    LinkedList<T>* items;
protected:

    virtual ListSequence<T>* Clone() const {
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
    void InsertAtInternal(T item, int index){
        if(index < 0 || index > items->GetLength()){
            throw invalid_argument("Индекс все диапазона + 1");
        }
        items->InsertAt(item, index);
    }

    void ConcatInternal(Sequence<T>* list) {
        if (list == nullptr){
            return;
        }
        for (int i = 0; i < list->GetLength(); i++) {
            items->Append(list->Get(i));
        }
    }

public:

    ListSequence(T* new_items, int count){
        if (count < 0){
            throw invalid_argument("Размер не может быть отрицательным");
        }
        items = new LinkedList<T>(new_items, count);
    }
    ListSequence(){
        items = new LinkedList<T>;
    }

    ListSequence (const ListSequence <T> &list){
        items = new LinkedList(*(list.items));
    }
    ListSequence(const ArraySequence<T>& arraySeq) {
        items = new LinkedList<T>();
        int count = arraySeq.GetLength();
        for (int i = 0; i < count; ++i) {
            items->Append(arraySeq.Get(i));
        }
    }

    T GetFirst() const override{
        return items->Get(0);
    }
    T GetLast() const override{
        return items->Get(items->GetLength()-1);
    }

    T Get(int index)const override{
        return items->Get(index);
    }

    ListSequence<T>* GetSubsequence(int startIndex, int endIndex) const override{
        if(startIndex < 0 || endIndex < 0 || endIndex < startIndex || startIndex >= items->GetLength() || endIndex >= items->GetLength()){
            throw invalid_argument("Ошибка индекса");
        }

        LinkedList<T>* items_sub_list;
        items_sub_list = items->GetSubList(startIndex, endIndex);

        ListSequence<T>* Sub_list = new ListSequence<T>();
        for(int i = 0; i < items_sub_list->GetLength(); i++){
            Sub_list->Append(items_sub_list->Get(i));
        }

        return Sub_list;
    }
    int GetLength() const override{
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
    ListSequence<T>* InsertAt(T item, int index) override{
        if(index < 0 || index > items->GetLength()){
            throw invalid_argument("Индекс все диапазона + 1");
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
            for(int i = 0; i < list_p->GetLength(); i++){
                list->AppendInternal(list_p->Get(i));
            }
            return list;
        }
    }

    void show() override{
        items->show();
    }

    ~ListSequence() {
        delete items;
    }
};


template <typename T>
class MutableListSequence : public ListSequence<T>{
protected:
    ListSequence<T>* Clone() const override{
        return new MutableListSequence<T>(*this);
    }
    ListSequence<T>* Instance(){
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
    ListSequence<T>* Instance(){
        return Clone();
    }
public:
    using ListSequence<T> :: ListSequence;
};












