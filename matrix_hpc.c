#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// 定義矩陣大小 (建議設定 1024 或 2048 來觀察明顯差異)
#define N 1024

// 初始化矩陣為隨機數
void init_matrix(double *mat, int size) {
    for (int i = 0; i < size * size; i++) {
        mat[i] = (double)rand() / RAND_MAX;
    }
}

// 1. Naive Implementation (未優化版本：傳統三層迴圈)
// 缺點：Cache Miss 高，無平行化
void naive_multiply(double *A, double *B, double *C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double sum = 0.0;
            for (int k = 0; k < size; k++) {
                sum += A[i * size + k] * B[k * size + j];
            }
            C[i * size + j] = sum;
        }
    }
}

// 2. Optimized Implementation (優化版本：記憶體局部性 + OpenMP 平行化)
// 優點 1：Loop Reordering (i-k-j) 提升 Cache Hit Rate
// 優點 2：OpenMP 利用多核心 CPU 平行運算
void optimized_multiply(double *A, double *B, double *C, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        for (int k = 0; k < size; k++) {
            double r = A[i * size + k];
            for (int j = 0; j < size; j++) {
                C[i * size + j] += r * B[k * size + j];
            }
        }
    }
}

int main() {
    size_t bytes = N * N * sizeof(double);
    double *A = (double *)malloc(bytes);
    double *B = (double *)malloc(bytes);
    double *C_naive = (double *)malloc(bytes);
    double *C_opt = (double *)malloc(bytes); // 修正：將 calloc 改為 malloc 並手動歸零或在邏輯中處理，這邊配合優化算法需先歸零

    // 初始化
    srand(time(NULL));
    init_matrix(A, N);
    init_matrix(B, N);
    
    // 確保 C_opt 歸零 (因為優化演算法是累加 +=)
    for(int i=0; i<N*N; i++) C_opt[i] = 0.0;

    printf("Matrix Size: %d x %d\n", N, N);
    printf("Calculating...\n");

    // --- 測試 Naive 版本 ---
    double start_time = omp_get_wtime();
    naive_multiply(A, B, C_naive, N);
    double end_time = omp_get_wtime();
    double naive_duration = end_time - start_time;
    printf("1. Naive Implementation Time: %.4f seconds\n", naive_duration);

    // --- 測試 Optimized 版本 ---
    start_time = omp_get_wtime();
    optimized_multiply(A, B, C_opt, N);
    end_time = omp_get_wtime();
    double opt_duration = end_time - start_time;
    printf("2. Optimized Implementation Time: %.4f seconds\n", opt_duration);

    // --- 計算加速倍率 ---
    printf("------------------------------------------------\n");
    printf("Speedup: %.2fx faster!\n", naive_duration / opt_duration);
    printf("------------------------------------------------\n");

    // 釋放記憶體
    free(A);
    free(B);
    free(C_naive);
    free(C_opt);

    return 0;
}