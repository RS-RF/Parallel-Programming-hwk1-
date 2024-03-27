#include <iostream>
#include <math.h>
#include <fstream>
#include <ctime>

using namespace std;

#define MAX_SIZE 524288 //2^19
#define FUNC_LOOP_TIME 1000
#define NUMBER_OF_Sample 19

long long unsigned int a[MAX_SIZE];
long long unsigned int sum = 0;

#define FILE_NAME1 "result1.txt"
#define FILE_NAME2 "result2.txt"
#define FILE_NAME3 "result3.txt"
#define FILE_NAME4 "result4.txt"
bool enable_file_print[] = {true, true, true, true};
ofstream outputFile1;
ofstream outputFile2;
ofstream outputFile3;
ofstream outputFile4;


double cost_time[FUNC_LOOP_TIME];

timespec head, tail;

//normal
void func1(int n) {
    for(int i=0; i<n; i++) {
        sum+=a[i];
    }
}

//multi-link
void func2(int n) {
    long long unsigned int sum1 = 0;
    long long unsigned int sum2 = 0;
    for(int i=0; i<n; i+=2) {
        sum1+=a[i];
        sum2+=a[i+1];
    }
    sum = sum1+sum2;
}


//recursive 1
void func3(int n) {
    for(int m=n; m>1; m/=2) {
        for(int i=0; i<m/2; i++) {
            a[i] = a[i*2] + a[i*2+1];
        }
    }
    sum = a[0];
}

//recursive 2
void func4(int n) {
    if(n==1) return;
    for(int i=0; i<n/2; i++) {
        a[i] += a[n-i-1];
    }
    n=n/2;
    func4(n);
    sum = a[0];
}

//initialize a and sum
void initialize() {
    for(int i=0; i<MAX_SIZE; i++) {
        a[i]=i;
    }
    sum = 0;
}

void startTimer() {
    clock_gettime(CLOCK_MONOTONIC, &head);
}
void endTimer() {
    clock_gettime(CLOCK_MONOTONIC, &tail);
}
void printTime(int num, double val) {
    cout<<"Col: "<<val<<"ms"<<endl;

    if(num==1 && enable_file_print[num-1]) {
        outputFile1 << val<<endl;
    }
    if(num==2 && enable_file_print[num-1]) {
        outputFile2 << val<<endl;
    }
    if(num==3 && enable_file_print[num-1]) {
        outputFile3 << val<<endl;
    }
    if(num==4 && enable_file_print[num-1]) {
        outputFile4 << val<<endl;
    }
}

double calculate_avg_time() {
    double avg = 0;
    for(int i=0; i<FUNC_LOOP_TIME; i++) {
        avg+=cost_time[i];
    }
    avg/=FUNC_LOOP_TIME;
    return avg;
}



int main()
{

    //initialize
    initialize();
    outputFile1.open(FILE_NAME1, ios::out | ios::trunc); // Open file in truncate mode (clears previous content)
    outputFile2.open(FILE_NAME2, ios::out | ios::trunc); // Open file in truncate mode (clears previous content)
    outputFile3.open(FILE_NAME3, ios::out | ios::trunc); // Open file in truncate mode (clears previous content)
    outputFile4.open(FILE_NAME4, ios::out | ios::trunc); // Open file in truncate mode (clears previous content)

    //func
    for(int i=0; i<NUMBER_OF_Sample; i++) {
        int test_size = pow(2, i+1);
        cout<<"**********The current test_size is "<<test_size<<"."<<endl;
        for(int j=0; j<FUNC_LOOP_TIME; j++) {
            initialize();
            startTimer();
            func1(test_size);
            endTimer();
            cost_time[j] = (tail.tv_sec - head.tv_sec) * 1000.0 + (tail.tv_nsec - head.tv_nsec) / 1000000.0;
        }
        double avg1 = calculate_avg_time();
        printTime(1, avg1);

        //cout<<"func1 finished. The answer is "<<sum<<"."<<endl;

        for(int j=0; j<FUNC_LOOP_TIME; j++) {
            initialize();
            startTimer();
            func2(test_size);
            endTimer();
            cost_time[j] = (tail.tv_sec - head.tv_sec) * 1000.0 + (tail.tv_nsec - head.tv_nsec) / 1000000.0;
        }
        double avg2 = calculate_avg_time();
        printTime(2, avg2);
        //cout<<"func2 finished. The answer is "<<sum<<"."<<endl;

        for(int j=0; j<FUNC_LOOP_TIME; j++) {
            initialize();
            startTimer();
            func3(test_size);
            endTimer();
            cost_time[j] = (tail.tv_sec - head.tv_sec) * 1000.0 + (tail.tv_nsec - head.tv_nsec) / 1000000.0;
        }
        double avg3 = calculate_avg_time();
        printTime(3, avg3);
        //cout<<"func3 finished. The answer is "<<sum<<"."<<endl;

        for(int j=0; j<FUNC_LOOP_TIME; j++) {
            initialize();
            startTimer();
            func4(test_size);
            endTimer();
            cost_time[j] = (tail.tv_sec - head.tv_sec) * 1000.0 + (tail.tv_nsec - head.tv_nsec) / 1000000.0;
        }
        double avg4 = calculate_avg_time();
        printTime(4, avg4);
        //cout<<"func4 finished. The answer is "<<sum<<"."<<endl;

        //system("pause");
    }

    return 0;
}