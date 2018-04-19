#include <cstdio>

class Tree {
private:
    char endFlag, tmp, *expression;
    int nodeSize, level[128], expression_len;
    struct Node {
        Node *left, *right;
        char data;
        Node(char val = 0, Node *l = nullptr, Node *r = nullptr) {
            data = val;
            left = l;
            right = r;
        }
    } *root;
    Node* build_() {
        if (scanf("%c", &tmp), tmp == endFlag) return nullptr;
        nodeSize++;
        Node *cur = new Node(tmp);
        cur->left = build_();
        cur->right = build_();
        return cur;
    }
    void print_(Node *cur, bool flag = false) {
        if (flag) expression[expression_len++] = '(';
        if (cur->left) {
            print_(cur->left, level[cur->data] && level[cur->left->data]
                              && level[cur->data] > level[cur->left->data]);
        }
        expression[expression_len++] = cur->data;
        if (cur->right) {
            print_(cur->right, level[cur->data] && level[cur->right->data]
                              && level[cur->data] > level[cur->right->data]);
        }
        if (flag) expression[expression_len++] = ')';
    }
    int calc_(Node *cur) {
        if (cur == nullptr) return 0;
        int left = 0, right = 0;
        if (cur->left) left = calc_(cur->left);
        if (cur->right) right = calc_(cur->right);
        if (cur->data == '+') return left + right;
        if (cur->data == '-') return left - right;
        if (cur->data == '*') return left * right;
        if (cur->data == '/') return left / right;
        return cur->data ^ '0';
    }
public:
    Tree(char endval) { 
        root = nullptr, endFlag = endval, nodeSize = 0;
        expression = nullptr;
        level['*'] = level['/'] = 1;
        level['+'] = level['-'] = -1;
        root = build_();
    }
    char* toChar() {
        if (expression) delete []expression;
        expression = new char[nodeSize << 1];
        expression_len = 0;
        print_(root, false);
        expression[expression_len] = '\0';
        return expression;
    }
    int calc() {
        return calc_(root);
    }
};

int main() {
//    freopen("in.txt", "r", stdin);
    Tree tree = '@';
    printf("%s=%d", tree.toChar(), tree.calc());
    return 0;
}
