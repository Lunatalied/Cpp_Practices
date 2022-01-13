//
// Created by lutsi on 12.01.2022.
//

#ifndef PRACTICE8_NODE_TEMPLATE_H
#define PRACTICE8_NODE_TEMPLATE_H

template <class T>
class Node_Template{
public:
    T value;
    Node_Template<T>* ptr_to_next;

    //однопараметрический конструктор
    Node_Template(T newValue){
        value = newValue;
        ptr_to_next = nullptr;
    };

    //конструктор по умолчанию
    Node_Template(){
        value = T();
        ptr_to_next = nullptr;
    }

    //метод, возвращающий следующий элемент
    Node_Template<T>* getNext(){
        return this->ptr_to_next;
    }
};

#endif //PRACTICE8_NODE_TEMPLATE_H
