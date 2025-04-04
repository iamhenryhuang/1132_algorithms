#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX_SIZE 100000

int main() {
    int inputData[MAX_SIZE], totalnum = 0, num;

    while (scanf("%d", &num) == 1 && totalnum < MAX_SIZE) {
        inputData[totalnum++] = num;
    }

    // 處理特殊情況
    if (totalnum == 0) {
        printf("0\n");
        return 0;
    }
    
    if (totalnum == 1) {
        printf("%d\n", MAX(0, inputData[0]));
        return 0;
    }

    // 計算非環狀的最大子序列和
    int maxNonCircular = 0;
    int currentMaxSum = 0;
    for (int i = 0; i < totalnum; i++) {
        currentMaxSum = MAX(0, currentMaxSum + inputData[i]);
        maxNonCircular = MAX(maxNonCircular, currentMaxSum);
    }
    
    // 計算總和
    int totalSum = 0;
    for (int i = 0; i < totalnum; i++) {
        totalSum += inputData[i];
    }
    
    // 計算最小子序列和
    int minSum = 0;
    int currentMinSum = 0;
    for (int i = 0; i < totalnum; i++) {
        currentMinSum = MIN(0, currentMinSum + inputData[i]);
        minSum = MIN(minSum, currentMinSum);
    }
    
    // 計算環狀最大子序列和 = 總和 - 最小子序列和
    int maxCircular = totalSum - minSum;

    // 處理邊界情況
    if (maxCircular == totalSum && totalSum <= 0) {
        printf("0\n");
        return 0;
    }

    printf("%d\n", MAX(maxNonCircular, maxCircular));

    return 0;
}
