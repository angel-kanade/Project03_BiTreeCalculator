#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <climits>
#include <algorithm>
#include <exception>
using namespace std;

typedef struct TreeNode {
    char elem;
    bool isLeaf;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode(char e = 0, bool isL = false,struct TreeNode* l = nullptr, struct TreeNode* r = nullptr): elem(e), isLeaf(isL), left(l), right(r) {}
} TreeNode;

class BinaryTree {
private:
    TreeNode* root;
    string expr;
public:
    BinaryTree();
    ~BinaryTree();
    void ReadExpr(string& expr);
    bool checkExpr(TreeNode* node);
    void WriteExpr(TreeNode* node);
    void Assign(char x, int val, TreeNode* node);
    int Value(TreeNode* node);
    BinaryTree* Diff(char x, TreeNode* node);
    void MergeConst(TreeNode* node);
    void DeleteTree(TreeNode* node);
    void insertNode(char x, bool& done, TreeNode*& node);
    friend BinaryTree* CompoundExpr(char op, BinaryTree* left, BinaryTree* right);
};
