#include <iostream>
#include <math.h>

using namespace std;

#define MAX_SIZE 524288 //2^19
#define FUNC_LOOP_TIME 100
#define NUMBER_OF_Sample 19

long long unsigned int a[MAX_SIZE];
long long unsigned int sum = 0;


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

int main()
{

    //initialize
    initialize();

    //func
    for(int i=0; i<NUMBER_OF_Sample; i++) {//²âÊÔÑùÀý£º2^1 ÖÁ 2^19
        int test_size = pow(2, i+1);
        cout<<"**********The current test_size is "<<test_size<<"."<<endl;
        for(int j=0; j<FUNC_LOOP_TIME; j++) {
            initialize();
            func1(test_size);
        }
        cout<<"func1 finished. The answer is "<<sum<<"."<<endl;

        for(int j=0; j<FUNC_LOOP_TIME; j++) {
            initialize();
            func2(test_size);
        }
        cout<<"func2 finished. The answer is "<<sum<<"."<<endl;

        for(int j=0; j<FUNC_LOOP_TIME; j++) {
            initialize();
            func3(test_size);
        }
        cout<<"func3 finished. The answer is "<<sum<<"."<<endl;

        for(int j=0; j<FUNC_LOOP_TIME; j++) {
            initialize();
            func4(test_size);
        }
        cout<<"func4 finished. The answer is "<<sum<<"."<<endl;

        //system("pause");
    }

    return 0;
}
