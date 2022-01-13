#include <iostream>
#include "Node_Template.h"
#include "list_template.h"


int main() {
    List_Template<int> list1{1, 2, 3};
    List_Template<int> list2{4, 5, 6};
    List_Template<int> list3{7, 8};
    List_Template<int> list4{9, 10, 11, 12, 13};
    List_Template<char> list5{"Hello"};
    List_Template<char> list6{"lkjhgfghjkjhg"};
    List_Template<int> list7(0);

    list4.addToEnd(98);
    list4.addToMid(0, list4.find(11));
    list4.addToBegin(5);
    list4.deleteNodeLast();
    list4.deleteNodeMid(list4.find(0));
    list4.deleteNodeFirst();
    list4.print();
    return 0;
}
