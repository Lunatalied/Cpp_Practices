//
// Created by lutsi on 08.01.2022.
//



#ifndef PRACTICE8_LIST_H
#define PRACTICE8_LIST_H

#include "Node.h"

class List{
public:
    Node* head; //указатель на первый элемент списка
    int count_of_elem; //кол-во элементов в списке
    List(); //конструктор списка
    int getCount(); //получение количества элементов списка
    bool isEmpty(); //проверка пуст ли список
    int getValue(Node* ptr); //получение значения элемента списка по указателю на этот элемент
    void changeValue(Node* ptr, int newValue); //изменение значения элемента по указателю
    Node* getFirst(); //получение первого элемента списка
    Node* getNext(Node* ptr); //получение следующего элемента
    Node* getLast(); //получение последнего элемента списка
    void Clear(); //очистка списка
    void addToEnd(int value); //добавление элемента в конец списка
    void addToMid(int value, Node* ptr); //добавление элемента после указанного
    void addToBegin(int value); //добавление элемента в начало списка
    void deleteNodeLast(); //удаление последнего элемента по указателю
    void deleteNodeMid(Node* ptr); //удаление из внутренних элементов списка
    void deleteNodeFirst(); //удаление первого элемента
    void print(); //вывод значений элементов списка
    Node* find(int valueFind); // нахождение элемента списка
};

#endif //PRACTICE8_LIST_H
