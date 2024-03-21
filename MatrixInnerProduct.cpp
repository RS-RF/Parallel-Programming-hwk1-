#include <iostream>

using namespace std;

#define MAX_SIZE 2500
#define FUNC_LOOP_TIME 1000

double A[MAX_SIZE][MAX_SIZE];
double B[MAX_SIZE];
double sum[MAX_SIZE];
int test_size[] = {10,30,50,80,100,200,300,400,500,
600,700,800,900,/*之后会导致double越界*/1000,1100,1200,1300,1400,1500,1600,
1700,1800,1900,2000,2100,2200
}; //10~2200 : 总共26个测试案例

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
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            A[i][j] = 0;
        }
        A[i][i] = 1.0;
        for (int j = i + 1; j < MAX_SIZE; j++)
        {
            A[i][j] = rand();
        }
    }
    for (int k = 0; k < MAX_SIZE; k++)
    {
        for (int i = k + 1; i < MAX_SIZE; i++)
        {
            for (int j = 0; j < MAX_SIZE; j++)
            {
                A[i][j] += A[k][j];
            }
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



int main()
{
    matrix_reset();

    for(int i=0; i<26; i++) {
        int curr_test_size = test_size[i];
        cout<<"**********The current test_size is "<<curr_test_size<<"."<<endl;


        for(int j=0; j<FUNC_LOOP_TIME; j++) {
            sum_reset();
            func1(curr_test_size);
        }
        cout<<"func1 finished. The answer is "<<endl;
        print_sum(curr_test_size);

        for(int j=0; j<FUNC_LOOP_TIME; j++) {
            sum_reset();
            func2(curr_test_size);
        }
        cout<<"func2 finished. The answer is "<<endl;
        print_sum(curr_test_size);

        system("pause");

    }

    return 0;
}

