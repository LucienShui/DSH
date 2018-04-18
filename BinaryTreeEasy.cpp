#include <bits/stdc++.h>

template <typename Type>
class Tree {
private:
    Type lastVal, endFlag, tmp;
    int Height, nodeSize, leafSize;
    struct Node {
        Node *left, *right;
        Type data;
        Node(Type val = 0, Node *l = nullptr, Node *r = nullptr) {
            data = val;
            left = l;
            right = r;
        }
    } *root;
    Node* build_(int tmp_Height) {
        if (std::cin >> tmp, tmp == endFlag) return nullptr;
        nodeSize++;
        Height = std::max(Height, tmp_Height);
        Node *cur = new Node(tmp);
        cur->left = build_(tmp_Height + 1);
        cur->right = build_(tmp_Height + 1);
        if (cur->right == nullptr && cur->left == nullptr) leafSize++;
        return cur;
    }
    void preOrder_(Node *cur) {
        std::cout << cur->data << ' ';
        lastVal = cur->data;
        if (cur->left) preOrder_(cur->left);
        if (cur->right) preOrder_(cur->right);
    }
    void inOrder_(Node *cur) {
        if (cur->left) inOrder_(cur->left);
        std::cout << cur->data << ' ';
        if (cur->right) inOrder_(cur->right);
    }
    void postOrder_(Node *cur) {
        if (cur->left) postOrder_(cur->left);
        if (cur->right) postOrder_(cur->right);
        std::cout << cur->data << ' ';
    }
    int numberOf_(Node *cur, Type val) {
        int ans = 0;
        if (cur->data == val) ans = 1;
        if (cur->left) ans = ans + numberOf_(cur->left, val);
        if (cur->right) ans = ans + numberOf_(cur->right, val);
        return ans;
    }
    void print_(Node *cur, int dep) {
        int tmp = dep;
        while (tmp--) std::cout << "  ";
        std::cout << cur->data;
        std::cout << (cur->data == lastVal ? "" : "\n");
        if (cur->left) print_(cur->left, dep + 1);
        if (cur->right) print_(cur->right, dep + 1);
    }
public:
    Tree(Type endval) {
        root = nullptr, lastVal = endFlag = endval;
        Height = nodeSize = leafSize = 0;
    }
    void build() { root = build_(1); }
    
    int height() { return Height; }
    
    int numOfLeaves() { return leafSize; }
    
    int numOfNodes() { return nodeSize; }
    
    void preOrder() { if (root) preOrder_(root); }
    
    void inOrder() { if (root) inOrder_(root); }
    
    void postOrder() { if (root) postOrder_(root); }
    
    int numberOf(Type val) { return numberOf_(root, val); }
    
    void print() { if (root) print_(root, 0); }
};

int main() {
//    freopen("in.txt", "r", stdin);
    char op, ch;
    Tree<char> tree = '#';
    while (~scanf(" %c", &op)) {
        if (op == 'C') {
            tree.build();
            puts("Created success!");
        } else if (op == 'H') printf("Height=%d.\n", tree.height());
        else if (op == 'L') printf("Leaf=%d.\n", tree.numOfLeaves());
        else if (op == 'N') printf("Nodes=%d.\n", tree.numOfNodes());
        else if (op == '1') {
            printf("Preorder is:");
            tree.preOrder();
            puts(".");
        } else if (op == '2') {
            printf("Inorder is:");
            tree.inOrder();
            puts(".");
        } else if (op == '3') {
            printf("Postorder is:");
            tree.postOrder();
            puts(".");
        } else if (op == 'F') {
            scanf(" %c", &ch);
            printf("The count of %c is %d.\n", ch, tree.numberOf(ch));
        } else {
            puts("The tree is:");
            tree.print();
        }
    }
    return 0;
}
