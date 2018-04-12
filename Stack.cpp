#include <cstdio>
const int maxn = int(1e5) + 7;
char stack[maxn], str[maxn];
int mp[128], top, right[128];
int main() {
//    freopen("in.txt", "r", stdin);
    mp['('] = -1, mp[')'] = 1, mp['{'] = -2, mp['}'] = 2, mp['<'] = -3, mp['>'] = 3, right['('] = ')', right['<'] = '>', right['{'] = '}';
    scanf(" %s", str);
    for (int i = 0; str[i]; i++) { // 遍历每个字符
        if (!mp[str[i]]) continue; // 如果这个字符不是括号就跳过
        if (mp[str[i]] > 0) { // 如果是右括号
            if (mp[str[i]] + mp[stack[top]]) return 0 * printf("The %d character '%c' is wrong.\n", i + 1, str[i]); // 如果两个括号的权值和不为零，即不匹配
            else top--; // 匹配的话就出栈
        } else stack[++top] = str[i]; // 左括号直接push
    }
    if (top) { // 如果栈不为空
        printf("loss of right character ");
        while (top) putchar(right[stack[top--]]); // 输出与之匹配的右括号
        return 0 * puts(".");
    }
    return 0 * puts("right.");
}

