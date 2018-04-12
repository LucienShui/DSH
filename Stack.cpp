#include <cstdio>
const int maxn = int(1e5) + 7;
char stack[maxn], str[maxn];
int mp[128], top, right[128];
int main() {
//    freopen("in.txt", "r", stdin);
    mp['('] = -1, mp[')'] = 1, mp['{'] = -2, mp['}'] = 2, mp['<'] = -3, mp['>'] = 3, right['('] = ')', right['<'] = '>', right['{'] = '}';
    scanf(" %s", str);
    for (int i = 0; str[i]; i++) {
        if (!mp[str[i]]) continue;
        if (mp[str[i]] > 0) {
            if (mp[str[i]] + mp[stack[top]]) return 0 * printf("The %d character '%c' is wrong.\n", i + 1, str[i]);
            else top--;
        } else stack[++top] = str[i];
    }
    if (top) {
        printf("loss of right character ");
        while (top) putchar(right[stack[top--]]);
        return 0 * puts(".");
    }
    return 0 * puts("right.");
}

