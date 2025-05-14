#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 1000

typedef struct {
    int x;  // 浮木的左端點
    int y;  // 浮木的右端點
} Log;

int main() {
    int N; // 浮木數量
    Log logs[MAX]; // 存放所有浮木
    bool visited[MAX]; // 記錄哪些浮木已經訪問過
    int queue[MAX]; // 存放浮木編號
    int jumps[MAX]; // 記錄到達每個浮木需要的最少跳躍次數

    scanf("%d", &N); // 浮木數量
    
    // 讀取每個浮木的左右端點
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &logs[i].x, &logs[i].y);
    }
    
    // 初始化
    for (int i = 0; i < N; i++) {
        visited[i] = false;
        jumps[i] = -1;  // -1 表示還未訪問
    }
    
    // BFS
    int front = 0, rear = 0;  // queue的前端和後端
    
    // 將起點（第一個浮木）加入queue
    queue[rear++] = 0;  // 第一個浮木的編號是 0
    visited[0] = true;
    jumps[0] = 0;       // 起點跳躍次數為 0
    
    while (front < rear) {  // 當queue不為空時
        int current = queue[front++];  // 取出隊列前端的浮木
        
        // 如果找到終點（最後一個浮木）
        if (current == N - 1) {
            printf("%d\n", jumps[current]);
            return 0;
        }
        
        // 嘗試從當前浮木跳到其他浮木
        for (int i = 0; i < N; i++) {
            // 如果浮木 i 還未訪問過，且可以從當前浮木跳到浮木 i
            if (!visited[i] && 
                logs[current].x < logs[i].y && logs[i].x < logs[current].y) {    
                visited[i] = true;
                jumps[i] = jumps[current] + 1;  // 增加一次跳躍
                queue[rear++] = i;  // 將浮木 i 加入隊列
            }
        }
    }

    return 0;
}
