#pragma once

#include <iostream>
#include <stdexcept>
#include <cstddef>

using namespace std;


template <class T> 
class LinkedList{
private:
    struct Node{
        T value;
        Node *next;
        Node *prev;

        Node(T new_value, Node *new_next, Node *new_prev){
            value = new_value;
            next = new_next;
            prev = new_prev;
        }
        Node(){
            next = nullptr;
            prev = nullptr;
        }
        Node(T val){
            next = nullptr;
            prev = nullptr;
            value = val;
        }

    };
    
    Node *head = nullptr;
    Node *tail = nullptr;
    
public:

    LinkedList(T* items, size_t count){
        if(count == 0){
            throw invalid_argument("Размер <= 0 ");
        }
        if(items == nullptr){
            throw invalid_argument("Переданный масив пуст");
        }

        Node *prev_elem = nullptr;
        Node *now_elem = nullptr;

        for(size_t i = 0; i < count; i++){
            now_elem = new Node;

            now_elem->value = items[i];
            now_elem->prev = prev_elem;
            if(i != 0){
                prev_elem->next = now_elem;
            }

            prev_elem = now_elem;
            if(i == 0){
                head = now_elem;

            }
            if(i == count - 1){
                tail = now_elem;
            }

        }
    }

    LinkedList() : head(nullptr), tail(nullptr) {}

    LinkedList(const LinkedList<T>& list) : head(nullptr), tail(nullptr){
        Node* now_elem = list.head;

        while(now_elem != nullptr){
            Append(now_elem->value);
            now_elem = now_elem->next;
        }
    }



    T GetFirst() {
        if(head == nullptr){
            throw invalid_argument("Список пуст");
        }
        return head->value;
    }
    T GetLast(){
        if(tail == nullptr){
            throw invalid_argument("Список пуст");
        }
        return tail->value;
    }

    T Get(size_t index) const{
        size_t length = GetLength(); // ИСПРАВЛЕНО
        if(index >= length){
            throw invalid_argument("Индекс вне списка");
        }

        if(index < length / 2){
            Node *now_elem = head;
            for(size_t i = 0; i < index; i++){
                now_elem = now_elem->next;
            }
            return now_elem->value;
        }
        else{
            Node *now_elem = tail;
            for(size_t i = 0; i < length - index - 1; i++){
                now_elem = now_elem->prev;
            }
            return now_elem->value;
            
        }
    }

    LinkedList<T>* GetSubList(size_t startIndex, size_t endIndex){
        size_t length = GetLength(); // ИСПРАВЛЕНО
        if(endIndex < startIndex || startIndex >= length || endIndex >= length){
            throw invalid_argument("Ошибка индекса");
        }

        size_t len = endIndex - startIndex + 1;
        T* items = new T[len];

        Node *now_elem = head;
        size_t index = 0;
        size_t current_pos = 0;
        while(now_elem != nullptr){

            if(current_pos >= startIndex && current_pos <= endIndex){
                items[index] = now_elem->value;
                index++;
            }
            now_elem = now_elem->next;
            current_pos++;
        }
        LinkedList<T>* result = new LinkedList<T>(items, len);
        delete[] items;
        return result;
    }

    size_t GetLength() const{
        size_t count = 0;
        Node *now_elem = head;
        while(now_elem != nullptr){
            count++;
            now_elem = now_elem->next;
        }
        return count;
    }

    void Append(T item){
        Node *new_elem = new Node;
        new_elem->value = item;
        
        if(head != nullptr){
            new_elem->prev = tail;
            tail->next = new_elem;
            tail = new_elem;
        }
        else{
            head = new_elem;
            tail = new_elem;
        }
        
    }
    void Prepend(T item){
        Node *new_elem = new Node;
        new_elem->value = item;

        if(head != nullptr){
            new_elem->next = head;
            head->prev = new_elem;
            head = new_elem;
        }
        else{
            head = new_elem;
            tail = new_elem;
        }
        
    }

    void InsertAt(T item, size_t index){
        size_t length = GetLength(); // ИСПРАВЛЕНО
        if(index > length){
            throw invalid_argument("Индекс вне диапазона + 1");
        }

        if(index == 0){
            this->Prepend(item);
            return;
        }
        if(index == length){
            this->Append(item);
            return;
        }

        Node *now_elem = head;
        for(size_t i = 0; i < index; i++){
            now_elem = now_elem->next;
        }

        Node *new_elem = new Node;
        new_elem->value = item;
        new_elem->prev = now_elem->prev;
        new_elem->next = now_elem;
        (now_elem->prev)->next = new_elem;
        now_elem->prev = new_elem;
    }

    LinkedList<T>* Concat(LinkedList<T> *list){
        if(list == nullptr){
            return this;
        }
        
        size_t other_length = list->GetLength();
        for(size_t i = 0; i < other_length; i++){
            this->Append(list->Get(i));
        }
        return this;
    }

    ~LinkedList(){
        Node *now_elem = head;
        while(now_elem != nullptr){
            Node *next_elem = now_elem->next;
            delete now_elem;
            now_elem = next_elem;
        }
        head = nullptr;
        tail = nullptr;
    }


};