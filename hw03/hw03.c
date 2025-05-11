#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 1000

// 圖的鄰接矩陣
bool graph[MAX+1][MAX+1];

// 記錄 BFS 中哪些節點已被訪問，用於計算連通分量
bool visited[MAX+1];

// 記錄 DFS 中哪些節點已被訪問，用於檢測環
bool checked[MAX+1];

int N; // 城市數量
bool has_cycle = false; // 是否有環

// DFS 檢查是否有環，u 是當前城市，parent 是父城市
void check_cycle(int u, int parent) {
    checked[u] = true;
    for (int v = 1; v <= N; v++) {
        if (!graph[u][v]) continue; // 沒有邊，跳過
        if (!checked[v]) {
            check_cycle(v, u); // 繼續探索未訪問的城市
            if (has_cycle) return; // 已找到環，結束
        } else if (v != parent) {
            has_cycle = true; // 找到環
            return;
        }
    }
}

int main() {
    scanf("%d", &N); // 城市數量 N
    getchar(); // 清除換行符

    // 初始化圖，並將鄰接矩陣清零
    memset(graph, 0, sizeof(graph));

    // 讀取每行的邊
    char line[1000];
    for (int i = 0; i < N; i++) {
        fgets(line, sizeof(line), stdin);
        int u, v; // u: 起點城市, v: 終點城市
        char *token = strtok(line, " \t\r\n");
        if (token) {
            u = atoi(token); // 起點
        }
        while ((token = strtok(NULL, " \t\r\n"))) {
            v = atoi(token); // 終點
            if (u >= 1 && u <= N && v >= 1 && v <= N) {
                graph[u][v] = graph[v][u] = true; // 無向圖，雙向設邊
            }
        }
    }

    // (1) 計算連通分量數量
    memset(visited, 0, sizeof(visited));
    int components = 0;
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            components++;
            // 用簡單的 BFS 標記連通分量
            int queue[MAX+1];
            int front = 0; // 指向當前要處理的節點
            int rear = 0; // 指向下一個可插入的位置
            queue[rear++] = i;
            visited[i] = true;
            while (front < rear) {
                int u = queue[front++];
                for (int v = 1; v <= N; v++) {
                    if (graph[u][v] && !visited[v]) {
                        visited[v] = true;
                        queue[rear++] = v;
                    }
                }
            }
        }
    }
    int P; // 至少需要的邊數
    if (components > 0) {
        P = components - 1;
    } else {
        P = 0;
    }

    // (2) 檢查是否有環
    memset(checked, 0, sizeof(checked));
    for (int i = 1; i <= N && !has_cycle; i++) {
        if (!checked[i]) {
            check_cycle(i, 0); // 0 表示無父城市
        }
    }
    int Q; // 是否有環
    if (has_cycle == true) {
        Q = 1;
    } else {
        Q = 0;
    }

    printf("%d %d\n", P, Q);
    return 0;
}
