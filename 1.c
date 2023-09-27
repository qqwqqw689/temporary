#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Malloc(arg1) (int*)malloc(arg1*sizeof(int))
#define Zero(arg1,arg2) memset(arg1,0,arg2)

int main()
{
    int* A;
    int* B;
    int* C;
    int n;
    int w;
    float hits=0;
    float misses=0;

    scanf("%d %d", &n, &w);
    A = Malloc(n*n);
    B = Malloc(n*n);
    C = Malloc(n*n);
    Zero(A,n*n);
    Zero(B,n*n);
    Zero(C,n*n);

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            for(int k=0;k<n;k++)
            {
                if(C[i*n+j]==0)
                {
                    misses++;
                    Zero(C,n*n);
                    for(int m=0;m<w;m++)
                    {
                        if(i*n+j+w<n*n)
                           C[i*n+j+w]=1;
                        else
                            break;
                    }
                }
                else
                    hits++;

                if(A[i*n+k]==0)
                {
                    misses++;
                    Zero(A,n*n);
                    for(int m=0;m<w;m++)
                    {
                        if(i*n+j+w<n*n)
                           A[i*n+j+w]=1;
                        else
                            break;
                    }
                }
                else
                    hits++;

                if(B[k*n+j]==0)
                {
                    misses++;
                    Zero(C,n*n);
                    for(int m=0;m<w;m++)
                    {
                        if(i*n+j+w<n*n)
                           B[i*n+j+w]=1;
                        else
                            break;
                    }
                }
                else
                    hits++;
            }
    printf("%f %f", misses,hits);
    printf("Miss rate: %f \n", float(misses)/(misses+hits));
    misses=hits=0;

    for(int i=0;i<n;i++)
        for(int k=0;k<n;k++)
            for(int j=0;j<n;j++)
            {
                if(C[i*n+j]==0)
                {
                    misses++;
                    Zero(C,n*n);
                    for(int m=0;m<w;m++)
                    {
                        if(i*n+j+w<n*n)
                           C[i*n+j+w]=1;
                        else
                            break;
                    }
                }
                else
                    hits++;

                if(A[i*n+k]==0)
                {
                    misses++;
                    Zero(A,n*n);
                    for(int m=0;m<w;m++)
                    {
                        if(i*n+j+w<n*n)
                           A[i*n+j+w]=1;
                        else
                            break;
                    }
                }
                else
                    hits++;

                if(B[k*n+j]==0)
                {
                    misses++;
                    Zero(C,n*n);
                    for(int m=0;m<w;m++)
                    {
                        if(i*n+j+w<n*n)
                           B[i*n+j+w]=1;
                        else
                            break;
                    }
                }
                else
                    hits++;
            }

    printf("Miss rate: %f \n", double(misses)/(misses+hits));
    return 0;
}
