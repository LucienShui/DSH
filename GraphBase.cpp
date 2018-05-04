#include <bits/stdc++.h>
const int maxn = 1007;

template <typename Type>
class queue { // 手写队列
    Type data[maxn];
    int head, tail; // 队首，队尾
public:
    queue() { head = tail = 0; }
    bool empty() { return head == tail; } // 如果队首和队尾下标相等，就说明队列空了
    void push(Type val) { data[tail++] = val; } // 将元素压入队尾
    void pop() { head++; } // 队首元素出队
    Type front() { return data[head]; } // 取队首元素
};

int n, m; // n个点，m条边
int edge[maxn][maxn]; // 存储邻接表的信息
int size_edge[maxn]; // 记录每个点有多少个后继
char alpha[maxn]; // 记录每个点对应的字符
void addedge(int u, int v) { // 加边
    edge[u][size_edge[u]++] = v;
}

bool vis_dfs[maxn]; // 深搜的辅助数组
void dfs(int u) {
    printf("%c ", alpha[u]);
    vis_dfs[u] = true;
    for (int i = 0; i < size_edge[u]; i++) {
        int v = edge[u][i];
        if (!vis_dfs[v]) dfs(v);
    }
}


bool vis_bfs[maxn]; // 宽搜的辅助数组
void bfs(int u) {
    queue<int> que;
    que.push(u);
    vis_bfs[u] = true;
    while (!que.empty()) {
        u = que.front();
        que.pop();
        printf("%c ", alpha[u]);
        for (int i = 0; i < size_edge[u]; i++) {
            int v = edge[u][i];
            if (!vis_bfs[v]) {
                vis_bfs[v] = true;
                que.push(v);
            }
        }
    }
}

struct Ans { // 这道题出的十分不合理，无奈开了一个结构体数组来离线答案
    int u, v, val;
} ans[maxn];

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf(" %c", alpha + i);
    scanf("%d", &m);
    for (int i = 0, u, v, val; i < m; i++) {
        scanf("%d%d%d", &u, &v, &val);
        // 观察了一下样例输出的dfs序，发现是双向边
        addedge(u, v);
        addedge(v, u);
        ans[i] = {u, v, val}; // 记录答案
    }
    printf("DFS:");
    dfs(0);
    printf("\nBFS:");
    bfs(0);
    printf("\nedges are:\n");
    for (int i = 0; i < m; i++) {
        printf("%c-%c:%d\n", alpha[ans[i].u], alpha[ans[i].v], ans[i].val);
    }
    return 0;
}
