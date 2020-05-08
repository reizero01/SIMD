#include <stdio.h>
#include <nmmintrin.h>
#include <immintrin.h>

void fixed_avx_sum(int size){
    int size_m = size % 8;
    printf("size_m:%d\n", size_m);
    int size_8 = size - size_m;
    printf("size_8:%d\n", size_8);
    __m256d x1, x2;
    double result = 0.0;
    for (int i = 0; i < size_8; i+=8){
        // calculate 4 two-element horizontal sums
        x1 = _mm256_setr_pd(0.000001, 0.000001, 0.000001, 0.000001);
        x2 = _mm256_setr_pd(0.000001, 0.000001, 0.000001, 0.000001);
        __m256d sum = _mm256_hadd_pd(x1, x2);
        __m128d sum_upper = _mm256_extractf128_pd(sum, 1);
        __m128d result1 = _mm_add_pd(sum_upper, _mm256_castpd256_pd128(sum));
        result = result + result1[0] + result1[1];
    }
    if(size_m != 0){
        double temp[8] = {0};
        for(int i = 0; i < size_m; i++){
            temp[i] = 0.000001;
        }
        x1 = _mm256_setr_pd(temp[0], temp[1], temp[2], temp[3]);
        x2 = _mm256_setr_pd(temp[4], temp[5], temp[6], temp[7]);
        __m256d sum = _mm256_hadd_pd(x1, x2);
        __m128d sum_upper = _mm256_extractf128_pd(sum, 1);
        __m128d result1 = _mm_add_pd(sum_upper, _mm256_castpd256_pd128(sum));
        result = result + result1[0] + result1[1];
    }
    printf("total: %f\n", result);
}

void avx_sum(double *d, int size){
    // size_t size = sizeof(d)/sizeof(d[0]);
    int size_m = size % 8;
    printf("size_m:%d\n", size_m);
    int size_8 = size - size_m;
    printf("size_8:%d\n", size_8);
    __m256d x1, x2;
    double result = 0.0;
    for (int i = 0; i < size_8; i+=8){
        // calculate 4 two-element horizontal sums
        x1 = _mm256_setr_pd(d[i], d[i+1], d[i+2], d[i+3]);
        x2 = _mm256_setr_pd(d[i+4], d[i+5], d[i+6], d[i+7]);
        __m256d sum = _mm256_hadd_pd(x1, x2);
        __m128d sum_upper = _mm256_extractf128_pd(sum, 1);
        __m128d result1 = _mm_add_pd(sum_upper, _mm256_castpd256_pd128(sum));
        result = result + result1[0] + result1[1];
    }
    if(size_m != 0){
        double temp[8] = {0};
        for(int i = 0; i < size_m; i++){
            temp[i] = d[size - 1 - i];
        }
        x1 = _mm256_setr_pd(temp[0], temp[1], temp[2], temp[3]);
        x2 = _mm256_setr_pd(temp[4], temp[5], temp[6], temp[7]);
        __m256d sum = _mm256_hadd_pd(x1, x2);
        __m128d sum_upper = _mm256_extractf128_pd(sum, 1);
        __m128d result1 = _mm_add_pd(sum_upper, _mm256_castpd256_pd128(sum));
        result = result + result1[0] + result1[1];
    }
    printf("total: %f\n", result);
}

int main(int argc,char **argv){
    int size = 2000000000;
    // double d[size];
    // for(int i; i < size; i++){
    //     d[i] = 0.000001;
    // }
    // avx_sum(d, size);
    fixed_avx_sum(size);

}

