#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

#define MAX_SIZE 2500
#define FUNC_LOOP_TIME 100

double A[MAX_SIZE][MAX_SIZE];
double B[MAX_SIZE];
double sum[MAX_SIZE];
int test_size[] = {10,30,50,80,100,200,300,400,500,
600,700,800,900,1000,1100,1200,1300,1400,1500,1600,
1700,1800,1900,2000,2100,2200
}; //10~2200 : 总共26个测试案例

long long head, tail, freq;

double cost_time[FUNC_LOOP_TIME];

#define FILE_NAME1 "result1.txt"
#define FILE_NAME2 "result2.txt"
bool enable_file_print[] = {true, true};
ofstream outputFile1;
ofstream outputFile2;




//normal
void func1(int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            sum[i] +=A[j][i]*B[j];
        }
    }
}

//optimize
void func2(int n) {
    for(int j=0; j<n; j++) {
        for(int i=0; i<n; i++) {
            sum[i] += A[j][i] * B[j];
        }
    }
}

//initialize matrix
void matrix_reset()
{
    cout<<"开始初始化矩阵A"<<endl;
    for(int i=0; i<MAX_SIZE; i++) {
        for(int j=0; j<MAX_SIZE; j++) {
            A[i][j] = i+j;
        }
    }
    cout<<"开始初始化矩阵B"<<endl;
    for(int i=0; i<MAX_SIZE; i++) {
        B[i] = i;
    }
    cout<<"初始化工作结束！"<<endl;
}
void sum_reset() {
    for(int i=0; i<MAX_SIZE; i++) {
        sum[i] = 0;
    }
}
void print_sum(int n) {
    for(int i=0; i<n; i++) {
        cout<<sum[i]<<" ";
    }
    cout<<endl;
}

void startTimer() {
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
    QueryPerformanceCounter((LARGE_INTEGER*)&head);
}
void endTimer() {
    QueryPerformanceCounter((LARGE_INTEGER*)&tail);
}
void printTime(int num, double val) {
    cout<<"Col: "<<val<<"ms"<<endl;

    if(num==1 && enable_file_print[num-1]) {
        outputFile1 << val<<endl;
    }
    if(num==2 && enable_file_print[num-1]) {
        outputFile2 << val<<endl;
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
    matrix_reset();
    outputFile1.open(FILE_NAME1, ios::out | ios::trunc); // Open file in truncate mode (clears previous content)
    outputFile2.open(FILE_NAME2, ios::out | ios::trunc); // Open file in truncate mode (clears previous content)


    for(int i=0; i<26; i++) {
        int curr_test_size = test_size[i];
        cout<<"**********The current test_size is "<<curr_test_size<<"."<<endl;


        for(int j=0; j<FUNC_LOOP_TIME; j++) {
            sum_reset();
            startTimer();
            func1(curr_test_size);
            endTimer();
            cost_time[j] = (tail-head)*1000.0/freq;
        }
        double avg1 = calculate_avg_time();
        printTime(1, avg1);
        //cout<<"func1 finished. The answer is "<<endl;
        //print_sum(curr_test_size);

        for(int j=0; j<FUNC_LOOP_TIME; j++) {
            sum_reset();
            startTimer();
            func2(curr_test_size);
            endTimer();
            cost_time[j] = (tail-head)*1000.0/freq;
        }
        double avg2 = calculate_avg_time();
        printTime(2, avg2);
        //cout<<"func2 finished. The answer is "<<endl;
        //print_sum(curr_test_size);

        //system("pause");

    }

    return 0;
}

