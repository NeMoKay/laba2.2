#pragma once

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
    int size;
public:

    LinkedList (T* items, int count){

        if(count <= 0){
            throw invalid_argument("Размер <= 0 ");
        }
        if(items == nullptr){
            throw invalid_argument("Переданный масив пуст");
        }

        size = count;
        Node *prev_elem = nullptr;
        Node *now_elem = nullptr;

        for(int i = 0; i < count; i++){
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

    LinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    LinkedList(const LinkedList<T>& list) {
        head = nullptr;
        tail = nullptr;
        size = 0;

        Node* now_elem = list.head;

        for(int i = 0; i < list.size; i++){
            Append(now_elem->value);
            now_elem = now_elem->next;
        }
    }



    T GetFirst(){
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

    T Get(int index){
        if(index < 0 || index >= size){
            throw invalid_argument("Индекс вне списка");
        }

        if(index < size / 2){
            Node *now_elem = head;
            for(int i = 0; i < index; i++){
                now_elem = now_elem->next;
            }
            return now_elem->value;
        }
        else{
            Node *now_elem = tail;
            for(int i = 0; i < size - index - 1; i++){
                now_elem = now_elem->prev;
            }
            return now_elem->value;
            
        }
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex){
        if(startIndex < 0 || endIndex < 0 || endIndex < startIndex || startIndex >= size || endIndex >= size){
            throw invalid_argument("Ошибка индекса");
        }

        int len = endIndex - startIndex + 1;
        T* items = new T[len];

        Node *now_elem = head;
        int index = 0;
        for(int i = 0; i <= endIndex; i++){

            if(i >= startIndex){
                items[index] = now_elem->value;
                index++;
            }
            now_elem = now_elem->next;
        }
        LinkedList<T>* result = new LinkedList<T>(items, len);
        return result;
    }

    int GetLength(){
        return size;
    }

    void Append(T item){
        Node *new_elem = new Node;
        new_elem->value = item;
        
        if(size != 0){
            new_elem->prev = tail;
            tail->next = new_elem;
            tail = new_elem;
        }
        else{
            head = new_elem;
            tail = new_elem;
        }
        size++;
        
    }
    void Prepend(T item){
        Node *new_elem = new Node;
        new_elem->value = item;

        if(size != 0){
            new_elem->next = head;
            head->prev = new_elem;
            head = new_elem;
        }
        else{
            head = new_elem;
            tail = new_elem;
        }
        
        size++;
    }

    void InsertAt(T item, int index){
        if(index < 0 || index > size){
            throw invalid_argument("Индекс все диапазона + 1");
        }

        if(index == 0){
            this->Prepend(item);
            return;
        }
        if(index == size){
            this->Append(item);
            return;
        }

        Node *now_elem = head;
        Node *new_elem = new Node;
        for(int i = 0; i < index; i++){
            now_elem = now_elem->next;
        }

        new_elem->prev = now_elem->prev;
        new_elem->next = now_elem;
        (now_elem->prev)->next = new_elem;
        now_elem->prev = new_elem;
        
        new_elem->value = item;
        size++;
    }

    LinkedList<T>* Concat(LinkedList<T> *list){
        if(list == nullptr){
            LinkedList *copy_list(list);
            return copy_list;
        }

        int len = size + list->size;

        LinkedList<T> *adds_lists = new LinkedList;

        Node *now_elem = head;
        for(int i = 0; i < len; i++){
            
            if(i == size){
                now_elem = list->head;
            }
            adds_lists->Append(now_elem->value);
            now_elem = now_elem->next; 
        }

        return adds_lists;
    }


    void show(){
        Node *now_node = head;
        for(int i = 0; i < size; i++){
            cout << now_node->value << endl;
            now_node = now_node->next;
        }
    }


    ~LinkedList(){
        Node *now_elem = head;
        for(int i = 0; i < size; i++){
            Node *next_elem = now_elem->next;
            delete now_elem;
            now_elem = next_elem;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }


};



