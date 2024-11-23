#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <climits>
#include <algorithm>
using namespace std;

typedef struct TreeNode {
    char elem;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode(char e = 0, struct TreeNode* l = nullptr, struct TreeNode* r = nullptr): elem(e), left(l), right(r) {}
} TreeNode;

class BinaryTree {
private:
    TreeNode* root;
public:
    BinaryTree();
    ~BinaryTree();
    void ReadExpr(string& expr);
    void WriteExpr();
    void Assign(char x, int val);
    int Value();
    BinaryTree* Diff(char x);
    void MergeConst();
    void DeleteTree();
    friend BinaryTree* CompoundExpr(char op, BinaryTree* left, BinaryTree* right);
};
