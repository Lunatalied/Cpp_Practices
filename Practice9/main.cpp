#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <thread>
#include <map>
#include <iomanip>
int main() {
    //9.1 1)
    /*
    int N = 0;
    std::cin>>N;
    auto begin1 = std::chrono::steady_clock::now();
    std::vector<int> vec1(N);

    for (int i = 0; i < N; i++){
        vec1.push_back(i);
    }
    auto end1 = std::chrono::steady_clock::now();
    auto time_work_1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - begin1);
    std::cout << time_work_1.count();
     */
    //9.1 2)
    /*
    std::cin>>N;
    auto begin2 = std::chrono::steady_clock::now();
    std::vector<int> vec2(N);

    for (int i = 0; i < N; i++){
        vec2.insert(vec2.begin(), i);
    }
    auto end2 = std::chrono::steady_clock::now();
    auto time_work_2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - begin2);

    std::cout << time_work_2.count();
     */
    //9.1 3)
    /*
    int N = 0;
    std::cin>>N;
    std::vector<int> vec3(N);
    vec3.reserve(N + 15);


    std::mt19937 mt_engine;
    auto clock = std::chrono::system_clock();
    auto now = clock.now();
    auto duration_since_epoch = now.time_since_epoch();
    long long nanoseconds_since_epoch =
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                    duration_since_epoch).count();
    mt_engine.seed(nanoseconds_since_epoch);

    auto begin3 = std::chrono::steady_clock::now();
    vec3.insert(vec3.begin() + mt_engine() % 14, 666);
    auto end3 = std::chrono::steady_clock::now();

    auto time_work_3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3 - begin3);
    std::cout << time_work_3.count();
     */
    /*for (int i = 0; i < vec3.size(); i++){
        std::cout<<vec3[i]<<'\n';
    }*/

    //9.2 в Practice8

    //9.3
    /*
    const double d = 0.5;
    const int m = 9;
    const int k = 10;
    const double w = 1;
    double x = 5;
    std::vector<int> columns;
    columns.resize(k);
    int countPins = int((w*k) / d);

    std::mt19937 mt_engine;
    auto clock = std::chrono::system_clock();
    auto now = clock.now();
    auto duration_since_epoch = now.time_since_epoch();
    long long nanoseconds_since_epoch =
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                    duration_since_epoch).count();
    mt_engine.seed(nanoseconds_since_epoch);

    int flag = 0;
    double border = w;
    int cell = 0;
    for (int i = 0; i <= 10000; i++){
        x = 5;
        for (int j = 0; j < m; j++){
            flag = mt_engine() % 2;
            if (flag == 1){
                x = x + d;
            }
            else{
                x = x - d;
            }
        }
        if (x >= 0 && x <= w || x < 0){
            columns[0]++;
        }
        else if(x >= (countPins+1)*d && x <= w*k || x > w*k){
            columns[k]++;
        }
        else{
            while (x > border){
                border = border + w;
                cell++;
            }
            columns[cell]++;
            border = w;
            cell = 0;

           //int index = int(x/w);
           //std::cout<<index<<'\n';
           //columns[index]++;
        }
    }

    for(int i = 0; i < k; i++) {
        std::cout << std::setw(2)
                  << i << ' ' << std::string(columns[i]/200, '*') << '\n';
    }

    std::random_device rd{};
    std::mt19937 gen{rd()};

    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::normal_distribution<> normDistb{5,2};

    std::map<int, int> hist{};
    for(int n=0; n<10000; ++n) {
        ++hist[std::round(normDistb(gen))];
    }
    for(auto p : hist) {
        std::cout << std::setw(2)
                  << p.first << ' ' << std::string(p.second/200, '*') << '\n';
    }
     */
    return 0;
}