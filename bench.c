// Linear + binary search benchmark. Build: gcc -O2 bench.c -o bench_c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
static double now(void){struct timespec t;clock_gettime(CLOCK_MONOTONIC,&t);return t.tv_sec+t.tv_nsec*1e-9;}
static int linear(const int*a,int n,int x){for(int i=0;i<n;i++)if(a[i]==x)return i;return -1;}
static int binary(const int*a,int n,int x){int lo=0,hi=n-1;while(lo<=hi){int m=lo+(hi-lo)/2;if(a[m]==x)return m;if(a[m]<x)lo=m+1;else hi=m-1;}return -1;}
int main(void){
  int sizes[]={1000,10000,100000,1000000,10000000};
  printf("n,linear_ms,binary_us\n");
  for(int s=0;s<5;s++){
    int n=sizes[s];int*a=malloc(n*sizeof(int));
    for(int i=0;i<n;i++)a[i]=2*i;            // sorted, even numbers only
    int target=-1;                            // worst case: not present
    volatile int sink=0;
    int reps=(n<=100000)?200:(n<=1000000?50:10);
    double best=1e9;
    for(int r=0;r<5;r++){double t=now();for(int k=0;k<reps;k++)sink+=linear(a,n,target);t=(now()-t)/reps;if(t<best)best=t;}
    int breps=1000000;double bb=1e9;
    for(int r=0;r<5;r++){double t=now();for(int k=0;k<breps;k++)sink+=binary(a,n,2*(k%n)+1);t=(now()-t)/breps;if(t<bb)bb=t;}
    printf("%d,%.6f,%.4f\n",n,best*1e3,bb*1e6);
    free(a);
  }
}
