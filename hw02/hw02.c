#include <stdio.h>
#include <stdlib.h>

// 使用選擇排序按結束時間排序
void selectionSort(int validStart[], int validEnd[], int validDays[], int validCount) {
    for (int i = 0; i < validCount - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < validCount; j++) {
            if (validEnd[j] < validEnd[minIdx]) {
                minIdx = j;
            }
        }
        
        // 只有當需要時才交換
        if (minIdx != i) {
            // 交換結束時間
            int temp = validEnd[i];
            validEnd[i] = validEnd[minIdx];
            validEnd[minIdx] = temp;
            
            // 交換開始時間
            temp = validStart[i];
            validStart[i] = validStart[minIdx];
            validStart[minIdx] = temp;
            
            // 交換天數
            temp = validDays[i];
            validDays[i] = validDays[minIdx];
            validDays[minIdx] = temp;
        }
    }
}

int findMaxEarnings(int start[], int end[], int days[], int n, int U, int V) {
    int validStart[1000], validEnd[1000], validDays[1000];
    int validCount = 0;

    // 篩選有效工作 (開始日期:U, 結束日期:V)
    for (int i = 0; i < n; i++) {
        if (start[i] >= U && end[i] <= V) {
            validStart[validCount] = start[i];
            validEnd[validCount] = end[i];
            validDays[validCount] = days[i];
            validCount++;
        }
    }

    if (validCount == 0) return 0;

    // 使用選擇排序按結束時間排序
    selectionSort(validStart, validEnd, validDays, validCount);

    // 動態規劃
    int dp[1000]; // dp[i] 表示考慮到第i個工作時的最大收益
    
    // 初始化
    for (int i = 0; i < validCount; i++) {
        dp[i] = validDays[i];
    }
    
    // 計算最優解
    for (int i = 1; i < validCount; i++) {
        // 不選當前工作的情況
        if (i > 0 && dp[i-1] > dp[i]) {
            dp[i] = dp[i-1];
        }
        
        // 選當前工作，尋找前面不衝突的工作
        for (int j = 0; j < i; j++) {
            if (validEnd[j] <= validStart[i]) {  // 不衝突的判定
                if (dp[j] + validDays[i] > dp[i]) {
                    dp[i] = dp[j] + validDays[i];
                }
            }
        }
    }
    
    return (validCount > 0) ? dp[validCount-1] : 0;
}

int main() {
    int N;
    scanf("%d", &N);

    int start[1000], end[1000], days[1000];
    for (int i = 0; i < N; ++i) {
        scanf("%d %d", &start[i], &end[i]);
        days[i] = end[i] - start[i]; // 儲存每個工作的持續天數
    }

    int U, V;
    scanf("%d %d", &U, &V);

    int result = findMaxEarnings(start, end, days, N, U, V);
    printf("%d\n", result);

    return 0;
}
