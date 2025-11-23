/*
 * 程式名稱：function_01.c
 * 功能說明：演示字串操作、輸入輸出和動態記憶體管理，並實現學號輸入與顯示
 * 編譯方式：gcc function_01.c -o function_01
 * 執行方式：./function_01
 */

#include <stdio.h>     // 標準輸入輸出標頭檔
#include <stdlib.h>    // 標準函式庫標頭檔（用於 malloc、free）
#include <string.h>    // 字串處理標頭檔（用於 strcpy）
#include <ctype.h>     // 字元類型檢查標頭檔（用於 isdigit）

/*
 * isValidStudentID - 檢查學號格式是否正確
 * 參數：studentID - 待檢查的學號字串
 * 回傳值：1 表示格式正確，0 表示格式不正確
 * 格式要求：學號必須為 10 位數字
 */
int isValidStudentID(char* studentID) {
   // 檢查學號長度是否為 10 位
   if (strlen(studentID) != 10) {
       return 0;  // 長度不對，返回 0（不正確）
   }
   
   // 逐字符檢查是否都是數字
   for (int i = 0; i < 10; i++) {
       if (!isdigit(studentID[i])) {  // 如果有非數字字符，返回 0
           return 0;
       }
   }
   
   return 1;  // 格式正確，返回 1
}

/*
 * main - 主程式函式
 * 功能：
 *   1. 宣告字元陣列並複製字串
 *   2. 輸出問候訊息
 *   3. 輸入並顯示學號
 *   4. 檢查學號格式是否正確
 *   5. 動態配置記憶體
 *   6. 檢查記憶體配置是否成功
 *   7. 設置數據並輸出
 *   8. 釋放動態配置的記憶體
 * 回傳值：0 表示程式執行成功
 */
int main() {
   char name[20];  // 宣告長度為 20 的字元陣列，用於存儲名字
   char studentID[20];  // 宣告長度為 20 的字元陣列，用於存儲學號
   strcpy(name, "Julian");  // 使用 strcpy() 複製字串 "Julian" 到 name 陣列
   printf("Hello, %s\n", name);  // 使用 printf() 輸出問候訊息，%s 表示字串

   // 輸入和顯示學號
   printf("請輸入學號: ");  // 提示用戶輸入學號
   scanf("%s", studentID);  // 使用 scanf() 讀取用戶輸入的學號，存儲到 studentID 陣列
   
   // 檢查學號格式是否正確
   if (isValidStudentID(studentID)) {
       printf("✓ 學號格式正確: %s\n", studentID);  // 學號格式正確
   } else {
       printf("✗ 學號格式不正確! 學號必須為 10 位數字\n");  // 學號格式不正確
   }

   // 動態配置記憶體區塊
   int* p = malloc(sizeof(int) * 5);  // 分配 5 個整數大小的記憶體
   if (p != NULL) {  // 檢查 malloc() 是否成功（指標不為 NULL）
       p[0] = 100;  // 設置指標指向的第一個整數為 100
       printf("Value: %d\n", p[0]);  // 輸出該整數值，%d 表示整數
       free(p);  // 使用 free() 釋放動態配置的記憶體，避免記憶體洩漏
    }
    return 0;  // 回傳 0，表示程式正常結束
}