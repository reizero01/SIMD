#include <stdio.h>
#include <stdlib.h>


void sum_naive( int n)
    {
        double sum = 0.0;
        for( int i = 0; i < n; i++ )
            sum += 0.000001;
        printf("total: %f\n", sum);
    }

int main(int argc,char **argv){
    int n = 2000000000;
	sum_naive(n);
}
