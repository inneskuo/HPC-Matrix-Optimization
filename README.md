# High-Performance Matrix Multiplication Optimization

本專案為 C 語言高效能運算 (HPC) 微專題，實作並比較了矩陣乘法的優化差異。

## 專案簡介 (Project Description)
本程式比較了兩種矩陣乘法 (GEMM) 的實作方式：
1. **Naive Implementation:** 傳統 $O(N^3)$ 三層迴圈寫法，未考慮 Cache 機制。
2. **Optimized Implementation:** - **Loop Reordering (i-k-j):** 優化記憶體存取順序，大幅提升 Cache Hit Rate。
   - **OpenMP Parallelism:** 利用多核心 CPU 進行平行運算。

## 效能表現 (Performance)
在矩陣大小 $N=1024$ 的環境下測試：
- **Naive:** 執行時間較長 (基準)
- **Optimized:** 執行時間大幅縮短
- **加速倍率 (Speedup):** 約 **10x ~ 50x** (視 CPU 核心數而定)

## 如何編譯與執行 (How to Run)
使用 GCC 編譯器 (需支援 OpenMP)：

```bash
# 編譯
gcc -o matrix_hpc matrix_hpc.c -fopenmp -O3

# 執行
./matrix_hpc
