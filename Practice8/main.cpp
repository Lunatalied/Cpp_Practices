#include <iostream>
#include <chrono>
#include <random>
#include "Node_Template.h"
#include "list_template.h"


int main() {
    int N = 0;
    //===================================================================
    /*
    std::cin>>N;
    auto begin1 = std::chrono::steady_clock::now();
    List_Template<int> list1;
    for (int i = 0; i < N; i++){
        list1.pushBack(i);
    }
    auto end1 = std::chrono::steady_clock::now();
    auto time_work_1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - begin1);
    std::cout << time_work_1.count()<<'\n';
    list1.print();
    */
    //=================================================================
    /*
    std::cin>>N;
    auto begin2 = std::chrono::steady_clock::now();
    List_Template<int> list2;
    for (int i = 0; i < N; i++){
        list2.insert(list2.begin(), i);
    }
    auto end2 = std::chrono::steady_clock::now();
    auto time_work_2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - begin2);
    std::cout << time_work_2.count()<<'\n';
    list2.print();
    */
    //================================================================

    /*
    std::cin>>N;
    List_Template<int> list3(N);
    auto begin3 = std::chrono::steady_clock::now();

    std::mt19937 mt_engine;
    auto clock = std::chrono::system_clock();
    auto now = clock.now();
    auto duration_since_epoch = now.time_since_epoch();
    long long nanoseconds_since_epoch =
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                    duration_since_epoch).count();
    mt_engine.seed(nanoseconds_since_epoch);

    list3.insert(list3.begin() + mt_engine() % (N-1), 666);
    auto end3 = std::chrono::steady_clock::now();
    auto time_work_3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3 - begin3);
    std::cout << time_work_3.count()<<'\n';
    list3.print();
    */
    return 0;
}
