#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

#include <cstdlib>
#include <cmath>

using namespace std;

template<typename T>
void printArr(vector<T> arr) {
    for(auto el : arr) {
        cout << el << endl;
    }
}

void selectionSort(vector<double> &sort) {
int vecsize = sort.size();
for (int j = 0; j < vecsize - 1; ++j) {

    int min = j;
    for (int i = j+1; i < vecsize; ++i) {
        if (sort.at(min) > sort.at(i)) {
            min = i;
        }

    }  
    if (min != j)
        swap(sort.at(j), sort.at(min));
}
}

int main(int argc, char* argv[]) {

    if (argc < 3) {
        printf("need %d more arguments\n", 3 - argc);
        return -1;
    }

    int N = atoi(argv[1]),
        A = atoi(argv[2]);

    vector<double> M1(N), M2(N/2), M2_copy(N/2);

    srand(time(nullptr));
    
    auto started = std::chrono::high_resolution_clock::now();
    for (int exp = 0; exp < 100; exp++) {

        // Init arrays
        for (auto &el : M1) {
            el = (rand() % A + 1);
        }
        for (auto &el : M2) {
            el = (rand() % A + 1);
        }
        M2_copy = M2;

        // part1
        for (auto &el : M1) {
            el = cosh(el) + 1;
        }

        // part2
        for (size_t i = 1; i < M2.size(); i++) {
            M2[i] = abs(sin(M2_copy[i] + M2_copy[i-1]));
        }

        // part3
        for (size_t i = 0; i < M2.size(); i++) {
            M2[i] =  max(M1[i],M2[i]);
        }

        // part4
        selectionSort(M2);

        // part5
        double minNonZeroElement = *max_element(M2.begin(), M2.end());
        for (auto el : M2) {
            if (el < minNonZeroElement && el != 0.0) {
                minNonZeroElement = el;
            }
        }

        double sinSum = 0.0;
        for (auto el : M2) {
            if (static_cast<int>(minNonZeroElement) != 0) {
                if ((static_cast<int>(el) / static_cast<int>(minNonZeroElement)) % 2 == 0) {
                    sinSum += sin(el);
                }
            }
        }

    }
    auto done = chrono::high_resolution_clock::now();
    const std::chrono::duration<double> diff = done - started;
    std::cout << diff.count() << " s.\n";

    return 0;
}