#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <algorithm>

#include <cstdlib>
#include <cmath>
#include <stdlib.h>
#include <unistd.h>

#if defined(_OPENMP)
    #include <omp.h>
#else
    int omp_get_num_procs() { return 1;}
#endif


using namespace std;


void selectionSort(vector<double> &sort) {
    const int vecsize = sort.size();

    #pragma omp parallel sections
    {
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
}

template <typename T>
void printArr(vector<T> arr) {
    for (auto el : arr) {
        cout << el << " ";
    }
}

template <typename T>
void sort(vector<T> &arr){

    int n = arr.size();
    vector<T> leftHalf(arr.begin(), arr.begin() + n/2);
    vector<T> rightHalf(arr.begin() + n/2, arr.end());

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            selectionSort(leftHalf);
        }
        #pragma omp section
        {
            selectionSort(rightHalf);
        }
    }

    vector<T> dst;
    merge(leftHalf.begin(), leftHalf.end(), rightHalf.begin(), rightHalf.end(), back_inserter(dst));

}

int experimentsCount = 100;

bool isProgrammFinished = false;
int iterationsCompleteCounter = 0;

void printProgress() {
    while (!isProgrammFinished) {
        //printf("Текущий прогресс: %lf%\n", (static_cast<double>(iterationsCompleteCounter) / static_cast<double>(experimentsCount)) * 100.0);
        //sleep(1);
    }
}

int main(int argc, char* argv[]) {
    omp_set_num_threads(20); 

    
    if (argc < 3) {
        printf("need %d more arguments\n", 3 - argc);
        return -1;
    }

    int N = atoi(argv[1]),
        A = atoi(argv[2]);
   
    //omp_set_schedule(static_cast<omp_sched_t>(SHED), CHUNK_SIZE);

    vector<double> M1(N), M2(N/2), M2_copy(N/2);

    
    auto started = std::chrono::steady_clock::now();

    #pragma omp parallel
    #pragma omp single
    {
        #pragma omp task
        {
            #pragma omp task
            {
                printProgress();
            }

            #pragma omp task
            {
                for (int exp = 0; exp < experimentsCount; exp++) {
                    // Init arrays (Generate)
                    #pragma omp parallel for default(none) shared(M1, A)
                    for (size_t i = 0; i < M1.size(); i++) {
                        time_t temp = i * 10000 + chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
                        unsigned int temp2 = temp;
                        srand(time(&temp));
                        M1[i] = (rand_r(&temp2) % A + 1);
                    }
                    
                    #pragma omp parallel for default(none) shared(M2, A) schedule(dynamic, 1)
                    for (size_t i = 0; i < M2.size(); i++) {
                        time_t temp = i * 10000 + chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
                        unsigned int temp2 = temp;
                        srand(time(&temp));
                        M2[i] = (rand_r(&temp2) % A + 1);
                    }
                    M2_copy = M2;
                    
                    // part1
                    #pragma omp parallel for default(none) shared(M1) schedule(static)
                    for (auto &el : M1) {
                        el = pow(sinh(el), 2);
                    }

                    #pragma omp parallel for default(none) shared(M2, M2_copy) schedule(static)
                    for (size_t i = 1; i < M2.size(); i++) {
                        M2[i] = abs(sin(M2_copy[i] + M2_copy[i-1]));
                    }

                    // part3
                    #pragma omp parallel for default(none) shared(M1, M2) schedule(static)
                    for (size_t i = 0; i < M2.size(); i++) {
                        M2[i] = M1[i]/M2[i];
                    }

                    // part4
                    sort(M2);

                    // part5
                    double minNonZeroElement = *max_element(M2.begin(), M2.end());

                    #pragma omp parallel for default(none) private(minNonZeroElement) shared(M2) schedule(static)
                    for (auto el : M2) {
                        if (el < minNonZeroElement && el != 0.0) {
                            minNonZeroElement = el;
                        }
                    }
                    
                    double sinSum = 0.0;
                    #pragma omp parallel for default(none) private(sinSum) shared(minNonZeroElement, M2) schedule(static)
                    for (auto el : M2) {
                        if (static_cast<int>(minNonZeroElement) != 0) {
                            if ((static_cast<int>(el) / static_cast<int>(minNonZeroElement)) % 2 == 0) {
                                sinSum += sin(el);
                            }
                        }
                    }

                    iterationsCompleteCounter++;
                }
                isProgrammFinished = true;
            }

            #pragma omp taskwait
        }
    }
    auto done = chrono::steady_clock::now();
    const std::chrono::duration<double> diff = done - started;
    std::cout << diff.count() << " s.\n";

    return 0;
}