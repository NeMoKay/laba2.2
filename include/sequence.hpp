#pragma once
#include "sequence.hpp"
#include "Dynamic_Array.hpp"
#include "LinkedList.hpp"
#include "bit.hpp"
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
        if(index < 0 || index > items->GetSize()){
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
        for(int i = items->GetSize() - 1; i > index; --i){
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
        if(count < 0){
            throw invalid_argument("Размер не может быть отрицательным");
        }
        items = new DynamicArray<T>(new_items, count);

    }
    ArraySequence(){
        items = new DynamicArray<T>;
    }

    ArraySequence(const ArraySequence<T>& operand){
        items = new DynamicArray<T>(*(operand.items)); 
    }

    ArraySequence(const LinkedList<T>& list){
        int count = list.GetLength();
        if(count == 0){
            items = new DynamicArray<T>;
            return;
        }
        T* temp_arr = new T[count];
        for(int i = 0; i < count; ++i){
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

        for(int i = 0; i < this->GetLength();i++){

            result->Append(funk(this->Get(i)));
        }
        return result;
    }

    template<typename T2>
    T2 Reduce(T2 (*func)(T2, T), T2 start_val){
        T2 result = start_val;
        
        for(int i = 0; i < this->GetLength(); i++){
            result = func(result, this->Get(i));
        }
        return result;
    }


    Sequence<T>* Where(bool (*check_funk)(T)){

        Sequence<T>* result = new ArraySequence<T>;

        for(int i = 0; i < this->GetLength(); i++){
            T item = this->Get(i);
            if(check_funk(item)){
                result->Append(item);
            }
        }
        return result;
    }


    void show() override{
        items->show();
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






//list--------------------------------------------------
//list--------------------------------------------------
//list--------------------------------------------------
//list--------------------------------------------------





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
    void InsertAtInternal(T item, int index){
        if(index < 0 || index > items->GetLength()){
            throw invalid_argument("Индекс все диапазона + 1");
        }
        items->InsertAt(item, index);
    }

    void ConcatInternal(Sequence<T>* list){
        if(list == nullptr){
            return;
        }
        for(int i = 0; i < list->GetLength(); i++){
            items->Append(list->Get(i));
        }
    }

public:

    ListSequence(T* new_items, int count){
        if(count < 0){
            throw invalid_argument("Размер не может быть отрицательным");
        }
        items = new LinkedList<T>(new_items, count);
    }
    ListSequence(){
        items = new LinkedList<T>;
    }

    ListSequence (const ListSequence <T> &list){
        items = new LinkedList<T>(*(list.items));
    }
    ListSequence(const ArraySequence<T>& arraySeq){
        items = new LinkedList<T>;
        int count = arraySeq.GetLength();
        for(int i = 0; i < count; ++i){
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

        ListSequence<T>* Sub_list = new ListSequence<T>;
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


    template<typename T2>
    Sequence<T2>* Map(T2 (*funk)(T)){

        Sequence<T2>* result = new ListSequence<T2>;

        for(int i = 0; i < this->GetLength(); i++){
            result->Append(funk(this->Get(i)));
        }
        return result;
    }


    template<typename T2>
    T2 Reduce(T2 (*funk)(T2, T), T2 start_val){
        T2 result = start_val;

        for(int i = 0; i < this->GetLength(); i++){
            result = funk(result, this->Get(i));
        }
        return result;
    }

    Sequence<T>* Where(bool (*check_funk)(T)){

        Sequence<T>* result = new ListSequence<T>;
        for(int i = 0; i < this->GetLength(); i++){
            T item = this->Get(i);
            if(check_funk(item)){
                result->Append(item);
            }
        }
        return result;
    }

    void show() override{
        items->show();
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













template <typename T>
class BitSequence : public Sequence<Bit<T>>{
private:
    DynamicArray<T>* data;
    int bits_in_T;
    int length_bits;

    int GetByteIndex(int bitIndex) const{
        return bitIndex / bits_in_T;
    }
    int Get_i_bit_in_byte(int bitIndex) const{
        int ost = bitIndex % bits_in_T;
        return (bits_in_T - 1) - ost;
    }

    void SetBit(int bitIndex, bool value){
        int byte_index = GetByteIndex(bitIndex);
        int bit_in_byte_index = Get_i_bit_in_byte(bitIndex);
        T byte_in_arr = data->Get(byte_index);
        T mask = static_cast<T>(1) << bit_in_byte_index;
        if(value){
            data->Set(byte_index, byte_in_arr | mask);
        } 
        else{
            data->Set(byte_index, byte_in_arr & ~mask);
        }
    }

    bool GetBit(int bitIndex) const{
        int byte_index = GetByteIndex(bitIndex);
        int bit_in_byte_index = Get_i_bit_in_byte(bitIndex);
        T byte_in_arr = data->Get(byte_index);
        return (byte_in_arr >> bit_in_byte_index) & static_cast<T>(1);
    }

protected:
    virtual BitSequence<T>* Clone() const{
        BitSequence<T>* copy = new BitSequence<T>(*this);
        return copy;
    }

    virtual BitSequence<T>* Instance(){
        return this;
    }

    void AppendInternal(Bit<T> item){
        bool val = item.operator bool();
        int oldLen = length_bits;

        int oldByteCount = (oldLen  + bits_in_T - 1) / bits_in_T;

        int newByteCount = (oldLen  + bits_in_T) / bits_in_T;

        if(newByteCount > oldByteCount){
            data->Resize(newByteCount);
            data->Set(newByteCount - 1, 0);
        }


        SetBit(oldLen, val);
        length_bits++;
    }

    void PrependInternal(Bit<T> item){
        InsertAtInternal(item, 0);
    }

    void InsertAtInternal(Bit<T> item, int index){

        if(index < 0 || index > length_bits){
            throw invalid_argument("Ошибка индекса");
        }
        bool val = item.operator bool();
        int oldLen = length_bits;
        if(index == oldLen){
            AppendInternal(item);
            return;
        }
        int oldByteCount = (oldLen  + bits_in_T - 1) / bits_in_T;

        int newByteCount = (oldLen  + bits_in_T) / bits_in_T;


        if(newByteCount > oldByteCount){
            data->Resize(newByteCount);
            data->Set(newByteCount - 1, 0);
        }

        for (int i = oldLen; i > index; --i){
            bool bitVal = GetBit(i - 1);
            SetBit(i, bitVal);
        }

        SetBit(index, val);
        length_bits++;
    }

    void ConcatInternal(Sequence<Bit<T>>* list){
        if(list == nullptr){
            return;
        }
        for (int i = 0; i < list->GetLength(); i++){
            this->AppendInternal(list->Get(i));
        }
    }

public:

    BitSequence(){
        data = new DynamicArray<T>;
        bits_in_T = sizeof(T) * 8;
        length_bits = 0;
    }

    BitSequence(Bit<T>* new_items, int count){
        if(count < 0){
            throw invalid_argument("Размер не может быть отрицательным");
        }
        bits_in_T = sizeof(T) * 8;
        int bytesNeeded = (count + bits_in_T - 1) / bits_in_T;
        data = new DynamicArray<T>(bytesNeeded);
        for(int i = 0; i < bytesNeeded; i++){
            data->Set(i, 0);
        }
        for(int i = 0; i < count; i++){
            bool val = new_items[i].operator bool();
            SetBit(i, val);
        }
        length_bits = count;
    }

    BitSequence(const BitSequence<T>& operand){
        data = new DynamicArray<T>(*(operand.data));
        bits_in_T = operand.bits_in_T;
        length_bits = operand.length_bits;
    }

    Bit<T> GetFirst() const override{
        if(length_bits == 0){
            throw invalid_argument("Список пуст");
        }
        return Get(0);
    }

    Bit<T> GetLast() const override{
        if(length_bits == 0){
            throw invalid_argument("Список пуст");
        }
        return Get(length_bits - 1);
    }

    Bit<T> Get(int index) const override{
        if(index < 0 || index >= length_bits){
            throw invalid_argument("Ошибка индекса");
        }
        bool isBitSet = GetBit(index);
        T correct_val;
        if(isBitSet == true){
            correct_val = static_cast<T>(1);
        } 
        else{
            correct_val = static_cast<T>(0);
        }
        return Bit<T>(correct_val);
    }

    int GetLength() const override{
        return length_bits;
    }



    BitSequence<T>* GetSubsequence(int startIndex, int endIndex) const override{
        if(startIndex < 0 || endIndex < 0 || endIndex < startIndex || startIndex >= length_bits || endIndex >= length_bits){
            throw invalid_argument("Ошибка индекса");
        }

        BitSequence<T>* result = new BitSequence<T>;
        for(int i = startIndex; i <= endIndex; i++){
            result->Append(Get(i));
        }
        return result;
    }

    BitSequence<T>* Append(Bit<T> item) override{
        BitSequence<T>* arr = this->Instance();
        arr->AppendInternal(item);
        return arr;

    }

    BitSequence<T>* Prepend(Bit<T> item) override{
        BitSequence<T>* arr = this->Instance();
        arr->PrependInternal(item);
        return arr;
    }

    BitSequence<T>* InsertAt(Bit<T> item, int index) override{
        BitSequence<T>* arr = this->Instance();
        arr->InsertAtInternal(item, index);
        return arr;
    }

    BitSequence<T>* Concat(Sequence<Bit<T>>* list) override{
        if(list == nullptr){
            return this;
        }
        BitSequence<T>* arr = this->Instance();
        arr->ConcatInternal(list);
        return arr;
    }

    void show() override{

        for(int i = 0; i < length_bits; i++){
            bool bit = GetBit(i);
            if(bit == true){
                cout << 1 << endl;
            } 
            else{
                cout << 0 << endl;
            }
        }
        
    }

    BitSequence<T> operator&(const BitSequence<T>& operand) const{

        if(this->length_bits != operand.length_bits){
            throw invalid_argument("Длины последовательностей не совпадают");
        }
        BitSequence<T> result;
        for (int i = 0; i < this->length_bits; i++){
            result.Append(this->Get(i) & operand.Get(i));
        }
        return result;
    }

    BitSequence<T> operator|(const BitSequence<T>& operand) const{
        if(this->length_bits != operand.length_bits){
            throw invalid_argument("Длины последовательностей не совпадают");
        }
        BitSequence<T> result;
        for (int i = 0; i < this->length_bits; i++){
            result.Append(this->Get(i) | operand.Get(i));
        }
        return result;
    }

    BitSequence<T> operator^(const BitSequence<T>& operand) const{
        if(this->length_bits != operand.length_bits){
            throw invalid_argument("Длины последовательностей не совпадают");
        }
        BitSequence<T> result;
        for (int i = 0; i < this->length_bits; i++){
            result.Append(this->Get(i) ^ operand.Get(i));
        }
        return result;
    }

    BitSequence<T> operator~() const{
        BitSequence<T> result;
        for (int i = 0; i < length_bits; i++){
            result.Append(~this->Get(i));
        }
        return result;
    }

    ~BitSequence(){
        delete data;
    }
};


template <typename T>
class MutableBitSequence : public BitSequence<T>{
protected:
    BitSequence<T>* Clone() const override{
        return new MutableBitSequence<T>(*this);
    }
    BitSequence<T>* Instance() override{
        return this;
    }
public:
    using BitSequence<T>::BitSequence;
};

template <typename T>
class ImmutableBitSequence : public BitSequence<T>{
protected:
    BitSequence<T>* Clone() const override{
        return new ImmutableBitSequence<T>(*this);
    }
    BitSequence<T>* Instance() override{
        return this->Clone();
    }
public:
    using BitSequence<T>::BitSequence;
};


