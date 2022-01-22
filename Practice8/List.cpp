//
// Created by lutsi on 08.01.2022.
//

#include "List.h"
#include <iostream>

List::List(){
    head = nullptr;
    count_of_elem = 0;
}

int List::getCount(){
    return count_of_elem;
}

bool List::isEmpty(){
    return (count_of_elem == 0);
}

int List::getValue(Node* ptr){
    return (*ptr).value; //ptr->value
}

void List::changeValue(Node* ptr, int newValue){
    (*ptr).value = newValue;
}

Node* List::getFirst(){
    return head;
}

Node* List::getNext(Node* ptr){
    return(ptr->ptr_to_next);
}

Node* List::getLast(){
    Node* temp_ptr = head;
    while(temp_ptr->ptr_to_next != nullptr){
        temp_ptr = getNext(temp_ptr);
    }
    return temp_ptr;
}

void List::Clear(){
    Node* temp_ptr = head;
    Node* deleting_ptr = head;
    while(temp_ptr != nullptr){
        deleting_ptr = temp_ptr;
        temp_ptr = getNext(temp_ptr);
        delete deleting_ptr;
    }
}

void List::addToEnd(int value) {
    Node* elem = new Node(value);
    count_of_elem++;
    if (head == nullptr){
        head = elem;
    } else{
       getLast()->ptr_to_next = elem;
    }
}

void List::addToMid(int value, Node* ptr){
    Node* elem = new Node(value);
    count_of_elem++;
    Node* next = ptr->ptr_to_next;
    ptr->ptr_to_next = elem;
    elem->ptr_to_next = next;
}

void List::addToBegin(int value){
    Node* elem = new Node(value);
    count_of_elem++;
    Node* next = head;
    head = elem;
    elem->ptr_to_next = next;
}

void List::deleteNodeLast() {
    if (!isEmpty() and count_of_elem > 1) {
      Node* temp_ptr = head;
      Node* last = getLast();
      while(temp_ptr->ptr_to_next != last){
          temp_ptr = getNext(temp_ptr);
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

void List::deleteNodeMid(Node* ptr){
    if (!isEmpty() and count_of_elem > 2) {
        Node* next = ptr->ptr_to_next;
        Node* temp_ptr = head;
        while(temp_ptr->ptr_to_next != ptr){
            temp_ptr = getNext(temp_ptr);
        }
        delete temp_ptr->ptr_to_next;
        temp_ptr->ptr_to_next = next;
        count_of_elem--;
    } else if (!isEmpty() and count_of_elem == 2){
        Node* next = ptr->ptr_to_next;
        delete head;
        head = next;
        count_of_elem--;
    }  else if(isEmpty()){
        std::cout<<"list is empty. There are not elements for deleting"<<'\n';
        }
}

void List::deleteNodeFirst(){
    if (!isEmpty() and count_of_elem > 1) {
        Node* next = head->ptr_to_next;
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


void List::print(){
    Node* temp_ptr = head;
    while(temp_ptr != nullptr){
        std::cout<<temp_ptr->value<<'\n';
        temp_ptr = getNext(temp_ptr);
    }
}

Node* List::find(int valueFind){
    Node* temp_ptr = head;
    while(valueFind != temp_ptr->value){
        temp_ptr = getNext(temp_ptr);
    }
    return (temp_ptr);
}
