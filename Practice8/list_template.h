//
// Created by lutsi on 12.01.2022.
//

#ifndef PRACTICE8_LIST_TEMPLATE_H
#define PRACTICE8_LIST_TEMPLATE_H

#include "Node_Template.h"

template <class T> //шаблонизированный класс для итераторов для range based for
class List_Iterator{
public:

    Node_Template<T>* node_ptr; //указатель для итератора

    // контруктор, принимающий указатель
    List_Iterator(Node_Template<T>* ptr){
        node_ptr = ptr;
    }

    // конструктор, принимающий объект класса
    List_Iterator(const List_Iterator<T>& rhs_it){
        node_ptr = rhs_it.node_ptr;
    }

    //перегрузка префиксного инкремента
    List_Iterator<T>& operator++(){
        if (node_ptr != nullptr) {
            node_ptr = node_ptr->getNext();
        }
        return *this;
    }

    //перегрузка оператора !=
    bool operator!=(List_Iterator<T> rhs_it){
        return node_ptr != rhs_it.node_ptr;
    }

    //перегрузка оператора *(разыменовывание)
    T operator*(){
        return node_ptr->value;
    }

    List_Iterator<T> operator+(int index){
        List_Iterator<T> temp = *this;
        for (int i = 0; i < index; i++){
            if (temp.node_ptr == nullptr){
                exit(2);
            }
            temp.node_ptr = temp.node_ptr->getNext();
        }
        return temp;
    }

};

template <class T>
class List_Template{
public:

    Node_Template<T>* head; // указатель на начало листа
    int count_of_elem; // количество элементов в листе

    //конструктор по умолчанию //работает
    List_Template(){
        head = nullptr;
        count_of_elem = 0;
    }

    //однопараметрический конструктор, создающий лист из countElements
    //работает
    List_Template(int countElements){
        if (countElements < 0){
            std::cout<<("Wrong value for count of elements")<<'\n';
        }
        else if(countElements == 0){
            head = nullptr;
            count_of_elem = 0;
        }
        else if(countElements == 1){
            auto node = new Node_Template<T>;
            head = node;
            count_of_elem = 1;
        }
        else if(countElements > 1){
            auto node = new Node_Template<T>;
            head = node;
            count_of_elem = 1;
            for (int i = 0; i < countElements - 1; i++){
                node->ptr_to_next = new Node_Template<T>;
                node = node->ptr_to_next;
                count_of_elem++;
            }
        }
    }

    //конструктор с параметром initializer_list
    //работает
    List_Template(std::initializer_list<T> init_list){
        if(init_list.size() == 0){
            head = nullptr;
            count_of_elem = 0;
        }
        else if(init_list.size()  == 1){
            auto node = new Node_Template<T>;
            head = node;
            count_of_elem = 1;
        }
        else if(init_list.size()  > 1){
            auto node = new Node_Template<T>;
            head = node;
            count_of_elem = 1;
            for (int i = 0; i < init_list.size()  - 1; i++){
                node->ptr_to_next = new Node_Template<T>();
                node = node->ptr_to_next;
                count_of_elem++;
            }
        }
        Node_Template<T>* temp = head;
        for (auto i: init_list){
            temp->value = i;
            temp = temp->getNext();
        }
    }

    //перегрузка оператора = для std:initializer_list
    //работает
    List_Template<T>& operator=(const std::initializer_list<T>& rhs_init_list){
        if (rhs_init_list.size() == count_of_elem){ //работает
            Node_Template<T>* temp = head; //если длины равны, то копирую данные из init_list в лист
            for (auto i: rhs_init_list){
                temp->value = i;
                temp = temp->getNext();
            }
        }
        else if(rhs_init_list.size() < count_of_elem){ //работает
            Node_Template<T>* temp = head; //если init_list меньше листа, то копирую все элементы в лист, остальные элементы удаляю
            Node_Template<T>* last = nullptr;
            for (auto i: rhs_init_list){ //процесс копирования
                temp->value = i;
                last = temp;
                temp = temp->getNext();
            }
            last->ptr_to_next = nullptr;
            Node_Template<T>* deleting_ptr = temp; //процесс удаления
            while(temp != nullptr){
                deleting_ptr = temp;
                temp = temp->getNext();
                delete deleting_ptr;
                count_of_elem--;
            }
        }
        else if(rhs_init_list.size() > count_of_elem){ //работает
            Node_Template<T>* temp = head; //если init_list больше, то копирую сколько вместиться элементов, создаю новые пустые элементы и оставшиеся значения копирую в них
            Node_Template<T>* last_for_new = nullptr;
            Node_Template<T>* last_for_copy_value = nullptr;
            for (auto i = rhs_init_list.begin(); i != rhs_init_list.begin() + count_of_elem; i++){ //процесс копирования первых count_of_elem элементов
                temp->value = *i;
                last_for_new = temp;
                last_for_copy_value = temp;
                temp = temp->getNext();
            }
            int lhs_count_of_elem = count_of_elem;
            for (int i = 0; i < rhs_init_list.size() - lhs_count_of_elem; i++) { //выделение памяти для оставшихся элементов
                auto newElem = new Node_Template<T>;
                count_of_elem++;
                last_for_new->ptr_to_next = newElem;
                last_for_new = last_for_new->ptr_to_next;
            }
            for (auto i = rhs_init_list.begin() + lhs_count_of_elem; i != rhs_init_list.end(); i++){ //копирование оставшихся значений
                last_for_copy_value->ptr_to_next->value = *i;
                last_for_copy_value = last_for_copy_value->getNext();
            }
        }
        return *this;
    }

    //перегрузка оператора = для объектов класса List_Template
    List_Template<T>& operator=(const List_Template<T>& rhs_list){
        if (count_of_elem == rhs_list.count_of_elem){ //работает
            Node_Template<T>* temp_r = rhs_list.head;//если длины равны, копируем элементы
            Node_Template<T>* temp_l = head;
            while (temp_r != nullptr){
                temp_l->value = temp_r->value;
                temp_r = temp_r->getNext();
                temp_l = temp_l->getNext();
            }
        }
        else if(count_of_elem > rhs_list.count_of_elem){ //работает
            Node_Template<T>* temp_r = rhs_list.head;//если длина текущего больше, копируем все элементы, ненужную память чистим
            Node_Template<T>* temp_l = head;
            Node_Template<T>* last = nullptr;
            while (temp_r != nullptr){
                temp_l->value = temp_r->value;
                temp_r = temp_r->getNext();
                last = temp_l;
                temp_l = temp_l->getNext();
            }
            last->ptr_to_next = nullptr;
            Node_Template<T>* deleting_ptr = temp_l;
            while(temp_l != nullptr){
                deleting_ptr = temp_l;
                temp_l = temp_l->getNext();
                delete deleting_ptr;
                count_of_elem--;
            }

        }
        else if(count_of_elem < rhs_list.count_of_elem){ //работает
            Node_Template<T>* temp_r = rhs_list.head;//если длина текущего меньше, копируем сколко влезет, выделяем память по оставшиеся, копируем значения
            Node_Template<T>* temp_l = head;
            Node_Template<T>* last_for_new = nullptr;
            Node_Template<T>* last_for_copy_values = nullptr;
            for (int i = 0; i < count_of_elem; i++){
                temp_l->value = temp_r->value;
                temp_r = temp_r->getNext();
                last_for_new = temp_l;
                last_for_copy_values = temp_l;
                temp_l = temp_l->getNext();
            }
            int lhs_count_of_elem = count_of_elem;
            for(int i = 0; i < rhs_list.count_of_elem - lhs_count_of_elem; i++) {
                auto newElem = new Node_Template<T>;
                count_of_elem++;
                last_for_new->ptr_to_next = newElem;
                last_for_new = last_for_new->ptr_to_next;
            }
            for(int i = 0; i < rhs_list.count_of_elem - lhs_count_of_elem; i++){
                last_for_copy_values->ptr_to_next->value = temp_r->value;
                temp_r = temp_r->getNext();
                last_for_copy_values = last_for_copy_values->getNext();
            }
        }
        return *this;
    }

    //итератор begin
    //работает
    List_Iterator<T> begin(){
        List_Iterator<T> it_begin(head);
        return it_begin;
    }

    //итератор end
    //работает
    List_Iterator<T> end(){
        List_Iterator<T> it_end(nullptr);
        return it_end;
    }

    //деструктор
    //работает
    ~List_Template(){
        Node_Template<T>* temp_ptr = head;
        Node_Template<T>* deleting_ptr = head;
        while(temp_ptr != nullptr){
            deleting_ptr = temp_ptr;
            temp_ptr = temp_ptr->getNext();
            delete deleting_ptr;
        }
        count_of_elem = 0;
    }

    //возвращает количество элементов в листе
    //работает
    int getCount() const{
        return count_of_elem;
    }

    //возвращает пуст ли лист
    //работает
    bool isEmpty() const{
        return (count_of_elem == 0);
    }

    //получение значения элемента списка по указателю на этот элемент
    //работает
    T getValue(Node_Template<T>* ptr) const{
        return (*ptr).value; //ptr->value
    }

    //изменение значения элемента по указателю
    //работает
    void changeValue(Node_Template<T>* ptr, T newValue){
        (*ptr).value = newValue;
    }

    //получение первого элемента списка
    //работает
    Node_Template<T>* getFirst(){
        return head;
    }

    //получение последнего элемента списка
    //работает
    Node_Template<T>* getLast(){
        Node_Template<T>* temp_ptr = head;
        while(temp_ptr->ptr_to_next != nullptr){
            temp_ptr = temp_ptr->getNext();
        }
        return temp_ptr;
    }


    //добавление элемента в конец списка
    //работает
    void addToEnd(T value) {
        auto elem = new Node_Template<T>(value);
        count_of_elem++;
        if (head == nullptr){
            head = elem;
        } else{
            getLast()->ptr_to_next = elem;
        }
    }

    //добавление элемента в конец списка
    //работает
    void pushBack(T value){
        auto elem = new Node_Template<T>(value);
        count_of_elem++;
        if (head == nullptr){
            head = elem;
        } else{
            getLast()->ptr_to_next = elem;
        }
    }

    //добавление элемента после указанного
    //работает
    void addToMid(T value, Node_Template<T>* ptr){
        auto elem = new Node_Template<T>(value);
        count_of_elem++;
        Node_Template<T>* next = ptr->ptr_to_next;
        ptr->ptr_to_next = elem;
        elem->ptr_to_next = next;
    }

    //добавление элемента в начало списка
    //работает
    void addToBegin(int value){
        auto elem = new Node_Template<T>(value);
        count_of_elem++;
        Node_Template<T>* next = head;
        head = elem;
        elem->ptr_to_next = next;
    }

    void insert(List_Iterator<T> it, T value){
        if (it.node_ptr == head){
            auto elem = new Node_Template<T>(value);
            count_of_elem++;
            Node_Template<T>* next = head;
            head = elem;
            elem->ptr_to_next = next;
        }
        else if (it.node_ptr == nullptr){
           std::cout<<"Use method pushBack";
        }
        else{
            auto elem = new Node_Template<T>(value);
            count_of_elem++;
            Node_Template<T>* next = it.node_ptr->ptr_to_next;
            it.node_ptr->ptr_to_next = elem;
            elem->ptr_to_next = next;
        }
    }

    //удаление последнего элемента по указателю
    //работает
    void deleteNodeLast() {
        if (!isEmpty() and count_of_elem > 1) {
            Node_Template<T>* temp_ptr = head;
            Node_Template<T>* last = getLast();
            while(temp_ptr->ptr_to_next != last){
                temp_ptr = temp_ptr->getNext();
            }
            delete temp_ptr->ptr_to_next;
            temp_ptr->ptr_to_next = nullptr;
            count_of_elem--;
        } else if (!isEmpty() and count_of_elem == 1){
            delete head;
            head = nullptr;
            count_of_elem--;
        } else if(isEmpty()){
            std::cout<<"list is empty. There are not elements for deleting"<<'\n';
        }
    }

    //удаление из внутренних элементов списка
    //работает
    void deleteNodeMid(Node_Template<T>* ptr){
        if (!isEmpty() and count_of_elem > 2) {
            Node_Template<T>* next = ptr->ptr_to_next;
            Node_Template<T>* temp_ptr = head;
            while(temp_ptr->ptr_to_next != ptr){
                temp_ptr = temp_ptr->getNext();
            }
            delete temp_ptr->ptr_to_next;
            temp_ptr->ptr_to_next = next;
            count_of_elem--;
        } else if (!isEmpty() and count_of_elem == 2){
            Node_Template<T>* next = ptr->ptr_to_next;
            delete head;
            head = next;
            count_of_elem--;
        }  else if(isEmpty()){
            std::cout<<"list is empty. There are not elements for deleting"<<'\n';
        }
    }

    //удаление первого элемента
    //работает
    void deleteNodeFirst(){
        if (!isEmpty() and count_of_elem > 1) {
            Node_Template<T>* next = head->ptr_to_next;
            delete head;
            head = next;
            count_of_elem--;
        } else if (!isEmpty() and count_of_elem == 1){
            delete head;
            head = nullptr;
            count_of_elem--;
        } else if(isEmpty()){
            std::cout<<"list is empty. There are not elements for deleting"<<'\n';
        }
    }

    //вывод значений элементов списка
    //работает
    void print(){
        Node_Template<T>* temp_ptr = head;
        while(temp_ptr != nullptr){
            std::cout<<temp_ptr->value<<'\n';
            temp_ptr = temp_ptr->getNext();
        }
    }

    //нахождение элемента списка
    //работает
    Node_Template<T>* find(T valueFind){
        Node_Template<T>* temp_ptr = head;
        while(valueFind != temp_ptr->value){
            temp_ptr = temp_ptr->getNext();
        }
        return (temp_ptr);
    }

};

//специализация для char
template<>
class List_Template<char>{
public:

    Node_Template<char>* head;
    int count_of_elem;

    //конструктор по умолчанию
    List_Template(){
        head = nullptr;
        count_of_elem = 0;
    }

    //однопараметрический конструктор, создающий лист из countElements
    List_Template(int countElements){
        if (countElements < 0){
            std::cout<<("Wrong value for count of elements")<<'\n';
        }
        else if(countElements == 0){
            head = nullptr;
            count_of_elem = 0;
        }
        else if(countElements == 1){
            auto node = new Node_Template<char>;
            head = node;
            count_of_elem = 1;
        }
        else if(countElements > 1){
            auto node = new Node_Template<char>;
            head = node;
            count_of_elem = 1;
            for (int i = 0; i < countElements - 1; i++){
                node->ptr_to_next = new Node_Template<char>;
                node = node->ptr_to_next;
                count_of_elem++;
            }
        }
    }

    //конструктор с параметром initializer_list
    List_Template(std::initializer_list<char> init_list){
        if(init_list.size() == 0){
            head = nullptr;
            count_of_elem = 0;
        }
        else if(init_list.size()  == 1){
            auto node = new Node_Template<char>;
            head = node;
            count_of_elem = 1;
        }
        else if(init_list.size()  > 1){
            auto node = new Node_Template<char>;
            head = node;
            count_of_elem = 1;
            for (int i = 0; i < init_list.size()  - 1; i++){
                node->ptr_to_next = new Node_Template<char>();
                node = node->ptr_to_next;
                count_of_elem++;
            }
        }
        Node_Template<char>* temp = head;
        for (auto i: init_list){
            temp->value = i;
            temp = temp->getNext();
        }
    }

    //конструктор принимающий std::string
    List_Template(std::string str){
        if(str.size() == 0){
            head = nullptr;
            count_of_elem = 0;
        }
        else if(str.size() == 1){
            auto node = new Node_Template<char>;
            head = node;
            head->value = str[0];
            count_of_elem = 1;
        }
        else if(str.size() > 1){
            auto node = new Node_Template<char>;
            head = node;
            head->value = str[0];
            count_of_elem = 1;
            for(auto i = str.begin() + 1; i != str.end(); i++){
                node->ptr_to_next = new Node_Template<char>;
                node = node->ptr_to_next;
                node->value = *i;
                count_of_elem++;
            }
        }
    }

    //перегрузка оператора = для std::string
    List_Template<char>& operator=(std::string rhs_string){
        if (count_of_elem == rhs_string.size()){ //работает
            Node_Template<char>* temp = head;
            for(char c: rhs_string){
                temp->value = c;
                temp = temp->getNext();
            }
        }
        else if (count_of_elem > rhs_string.size()){ //работает
            Node_Template<char>* temp = head;
            Node_Template<char>* last = nullptr;
            for(char c: rhs_string){
                temp->value = c;
                last = temp;
                temp = temp->getNext();
            }
            last->ptr_to_next = nullptr;
            Node_Template<char>* deleting_ptr = temp;
            while(temp != nullptr){
                deleting_ptr = temp;
                temp = temp->getNext();
                delete deleting_ptr;
                count_of_elem--;
            }
        }
        else if (count_of_elem < rhs_string.size()){ //работает
            Node_Template<char>* temp = head;
            Node_Template<char>* last_for_new = nullptr;
            Node_Template<char>* last_for_copy_values = nullptr;
            for (auto i = rhs_string.begin(); i != rhs_string.begin() + count_of_elem; i++){
                temp->value = *i;
                last_for_new = temp;
                last_for_copy_values = temp;
                temp = temp->getNext();
            }
            int lhs_count_of_elem = count_of_elem;

            for (auto i = rhs_string.begin() + lhs_count_of_elem; i != rhs_string.end(); i++){
                auto node = new Node_Template<char>;
                last_for_new->ptr_to_next = node;
                last_for_new = last_for_new->ptr_to_next;
                count_of_elem++;
            }
            for (auto i = rhs_string.begin() + lhs_count_of_elem; i != rhs_string.end(); i++){
                last_for_copy_values->ptr_to_next->value = *i;
                last_for_copy_values = last_for_copy_values->ptr_to_next;
            }
        }
        return *this;
    }

    //перегрузка оператора = для std:initializer_list
    List_Template<char>& operator=(const std::initializer_list<char>& rhs_init_list){
        if (rhs_init_list.size() == count_of_elem){ //работает
            Node_Template<char>* temp = head;
            for (auto i: rhs_init_list){
                temp->value = i;
                temp = temp->getNext();
            }
        }
        else if(rhs_init_list.size() < count_of_elem){ //работает
            Node_Template<char>* temp = head;
            Node_Template<char>* last = nullptr;
            for (auto i: rhs_init_list){
                temp->value = i;
                last = temp;
                temp = temp->getNext();
            }
            last->ptr_to_next = nullptr;
            Node_Template<char>* deleting_ptr = temp;
            while(temp != nullptr){
                deleting_ptr = temp;
                temp = temp->getNext();
                delete deleting_ptr;
                count_of_elem--;
            }
        }
        else if(rhs_init_list.size() > count_of_elem){ //работает
            Node_Template<char>* temp = head;
            Node_Template<char>* last_for_new = nullptr;
            Node_Template<char>* last_for_copy_value = nullptr;
            for (auto i = rhs_init_list.begin(); i != rhs_init_list.begin() + count_of_elem; i++){
                temp->value = *i;
                last_for_new = temp;
                last_for_copy_value = temp;
                temp = temp->getNext();
            }
            int lhs_count_of_elem = count_of_elem;
            for (int i = 0; i < rhs_init_list.size() - lhs_count_of_elem; i++) {
                auto newElem = new Node_Template<char>;
                count_of_elem++;
                last_for_new->ptr_to_next = newElem;
                last_for_new = last_for_new->ptr_to_next;
            }
            for (auto i = rhs_init_list.begin() + lhs_count_of_elem; i != rhs_init_list.end(); i++){
                last_for_copy_value->ptr_to_next->value = *i;
                last_for_copy_value = last_for_copy_value->getNext();
            }
        }
        return *this;
    }

    //перегрузка оператора = для объектов класса List_Template
    List_Template<char>& operator=(const List_Template<char>& rhs_list){
        if (count_of_elem == rhs_list.count_of_elem){ //работает
            Node_Template<char>* temp_r = rhs_list.head;
            Node_Template<char>* temp_l = head;
            while (temp_r != nullptr){
                temp_l->value = temp_r->value;
                temp_r = temp_r->getNext();
                temp_l = temp_l->getNext();
            }
        }
        else if(count_of_elem > rhs_list.count_of_elem){ //работает
            Node_Template<char>* temp_r = rhs_list.head;
            Node_Template<char>* temp_l = head;
            Node_Template<char>* last = nullptr;
            while (temp_r != nullptr){
                temp_l->value = temp_r->value;
                temp_r = temp_r->getNext();
                last = temp_l;
                temp_l = temp_l->getNext();
            }
            last->ptr_to_next = nullptr;
            Node_Template<char>* deleting_ptr = temp_l;
            while(temp_l != nullptr){
                deleting_ptr = temp_l;
                temp_l = temp_l->getNext();
                delete deleting_ptr;
                count_of_elem--;
            }

        }
        else if(count_of_elem < rhs_list.count_of_elem){ //работает
            Node_Template<char>* temp_r = rhs_list.head;
            Node_Template<char>* temp_l = head;
            Node_Template<char>* last_for_new = nullptr;
            Node_Template<char>* last_for_copy_values = nullptr;
            for (int i = 0; i < count_of_elem; i++){
                temp_l->value = temp_r->value;
                temp_r = temp_r->getNext();
                last_for_new = temp_l;
                last_for_copy_values = temp_l;
                temp_l = temp_l->getNext();
            }
            int lhs_count_of_elem = count_of_elem;
            for(int i = 0; i < rhs_list.count_of_elem - lhs_count_of_elem; i++) {
                auto newElem = new Node_Template<char>;
                count_of_elem++;
                last_for_new->ptr_to_next = newElem;
                last_for_new = last_for_new->ptr_to_next;
            }
            for(int i = 0; i < rhs_list.count_of_elem - lhs_count_of_elem; i++){
                last_for_copy_values->ptr_to_next->value = temp_r->value;
                temp_r = temp_r->getNext();
                last_for_copy_values = last_for_copy_values->getNext();
            }
        }
        return *this;
    }

    //итератор begin
    List_Iterator<char> begin(){
        List_Iterator<char> it_begin(head);
        return it_begin;
    }

    //итератор end
    List_Iterator<char> end(){
        List_Iterator<char> it_end(nullptr);
        return it_end;
    }

    //деструктор
    ~List_Template(){
        Node_Template<char>* temp_ptr = head;
        Node_Template<char>* deleting_ptr = head;
        while(temp_ptr != nullptr){
            deleting_ptr = temp_ptr;
            temp_ptr = temp_ptr->getNext();
            delete deleting_ptr;
        }
        count_of_elem = 0;
    }

    //возвращает количество элементов в листе
    int getCount(){
        return count_of_elem;
    }

    //возвращает пуст ли лист
    bool isEmpty(){
        return (count_of_elem == 0);
    }

    //получение значения элемента списка по указателю на этот элемент
    char getValue(Node_Template<char>* ptr){
        return (*ptr).value; //ptr->value
    }

    //изменение значения элемента по указателю
    void changeValue(Node_Template<char>* ptr, char newValue){
        (*ptr).value = newValue;
    }

    //получение первого элемента списка
    Node_Template<char>* getFirst(){
        return head;
    }

    //получение последнего элемента списка
    Node_Template<char>* getLast(){
        Node_Template<char>* temp_ptr = head;
        while(temp_ptr->ptr_to_next != nullptr){
            temp_ptr = temp_ptr->getNext();
        }
        return temp_ptr;
    }

    //очистка списка
    void Clear(){
        Node_Template<char>* temp_ptr = head;
        Node_Template<char>* deleting_ptr = head;
        while(temp_ptr != nullptr){
            deleting_ptr = temp_ptr;
            temp_ptr = temp_ptr->getNext();
            delete deleting_ptr;
        }
    }

    //добавление элемента в конец списка
    void addToEnd(char value) {
        auto elem = new Node_Template<char>(value);
        count_of_elem++;
        if (head == nullptr){
            head = elem;
        } else{
            getLast()->ptr_to_next = elem;
        }
    }

    //добавление элемента после указанного
    void addToMid(char value, Node_Template<char>* ptr){
        auto elem = new Node_Template<char>(value);
        count_of_elem++;
        Node_Template<char>* next = ptr->ptr_to_next;
        ptr->ptr_to_next = elem;
        elem->ptr_to_next = next;
    }

    //добавление элемента в начало списка
    void addToBegin(int value){
        auto elem = new Node_Template<char>(value);
        count_of_elem++;
        Node_Template<char>* next = head;
        head = elem;
        elem->ptr_to_next = next;
    }

    //удаление последнего элемента по указателю
    void deleteNodeLast() {
        if (!isEmpty() and count_of_elem > 1) {
            Node_Template<char>* temp_ptr = head;
            Node_Template<char>* last = getLast();
            while(temp_ptr->ptr_to_next != last){
                temp_ptr = temp_ptr->getNext();
            }
            delete temp_ptr->ptr_to_next;
            temp_ptr->ptr_to_next = nullptr;
            count_of_elem--;
        } else if (!isEmpty() and count_of_elem == 1){
            delete head;
            head = nullptr;
            count_of_elem--;
        } else if(isEmpty()){
            std::cout<<"list is empty. There are not elements for deleting"<<'\n';
        }
    }

    //удаление из внутренних элементов списка
    void deleteNodeMid(Node_Template<char>* ptr){
        if (!isEmpty() and count_of_elem > 2) {
            Node_Template<char>* next = ptr->ptr_to_next;
            Node_Template<char>* temp_ptr = head;
            while(temp_ptr->ptr_to_next != ptr){
                temp_ptr = temp_ptr->getNext();
            }
            delete temp_ptr->ptr_to_next;
            temp_ptr->ptr_to_next = next;
            count_of_elem--;
        } else if (!isEmpty() and count_of_elem == 2){
            Node_Template<char>* next = ptr->ptr_to_next;
            delete head;
            head = next;
            count_of_elem--;
        }  else if(isEmpty()){
            std::cout<<"list is empty. There are not elements for deleting"<<'\n';
        }
    }

    //удаление первого элемента
    void deleteNodeFirst(){
        if (!isEmpty() and count_of_elem > 1) {
            Node_Template<char>* next = head->ptr_to_next;
            delete head;
            head = next;
            count_of_elem--;
        } else if (!isEmpty() and count_of_elem == 1){
            delete head;
            head = nullptr;
            count_of_elem--;
        } else if(isEmpty()){
            std::cout<<"list is empty. There are not elements for deleting"<<'\n';
        }
    }

    //вывод значений элементов списка
    void print(){
        Node_Template<char>* temp_ptr = head;
        while(temp_ptr != nullptr){
            std::cout<<temp_ptr->value<<'\n';
            temp_ptr = temp_ptr->getNext();
        }
    }

    //нахождение элемента списка
    Node_Template<char>* find(char valueFind){
        Node_Template<char>* temp_ptr = head;
        while(valueFind != temp_ptr->value){
            temp_ptr = temp_ptr->getNext();
        }
        return (temp_ptr);
    }

};

#endif //PRACTICE8_LIST_TEMPLATE_H
