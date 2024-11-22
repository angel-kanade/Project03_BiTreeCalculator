#include "classDeclare.hpp"
#include <cmath>
using namespace std;

// typedef struct TreeNode {
//     char elem;
//     bool isLeaf;
//     struct TreeNode* left;
//     struct TreeNode* right;
//     TreeNode(char e = 0, bool isL = false,struct TreeNode* l = nullptr, struct TreeNode* r = nullptr): elem(e), isLeaf(isL), left(l), right(r) {}
// } TreeNode;

// class BinaryTree {
// private:
//     TreeNode* root;
//     string expr;
// public:
//     BinaryTree();
//     ~BinaryTree();
//     void ReadExpr(string& expr);
//     bool checkExpr(TreeNode* node);
//     void WriteExpr(TreeNode* node);
//     void Assign(char x, int val, TreeNode* node);
//     int Value(TreeNode* node);
//     BinaryTree* Diff(char x, TreeNode* node);
//     void MergeConst(TreeNode* node);
//     void DeleteTree(TreeNode* node);
//     void insertNode(char x, bool& done, TreeNode*& node);
//     friend BinaryTree* CompoundExpr(char op, BinaryTree* left, BinaryTree* right);
// };


BinaryTree::BinaryTree(){
    root = nullptr;
}

BinaryTree::~BinaryTree(){
    this->DeleteTree(root);
}

void BinaryTree::insertNode(char x, bool& done, TreeNode*& node){
    if (node == nullptr){
        node = new TreeNode(x);
        if ('0' <= x && x <= '9' || 'a' <= x && x <= 'z' || 'A' <= x && x <= 'Z') node->isLeaf = true;
        done = true;
        return;
    }
    if (node->isLeaf){
        return;
    }
    else{
        if (!done){
            if (node->left) insertNode(x, done, node->left);
            else{
                node->left = new TreeNode(x);
                if ('0' <= x && x <= '9' || 'a' <= x && x <= 'z' || 'A' <= x && x <= 'Z') node->left->isLeaf = true;
                done = true;
                return;
            }
        }
        if (!done){
            if (node->right) insertNode(x, done, node->right);
            else{
                node->right = new TreeNode(x);
                if ('0' <= x && x <= '9' || 'a' <= x && x <= 'z' || 'A' <= x && x <= 'Z') node->right->isLeaf = true;
                done = true;
                return;
            }
        }
        return;
    }
}

void BinaryTree::DeleteTree(TreeNode* node){
    if (node == nullptr) return;
    if (node->left) DeleteTree(node->left);
    if (node->right) DeleteTree(node->right);
    delete node;
    root = nullptr;
}

bool BinaryTree::checkExpr(TreeNode* node){
    if (node == nullptr) return true;
    if (!node->isLeaf){
        if (node->left == nullptr || node->right == nullptr) return false;
        if (!checkExpr(node->left) ||!checkExpr(node->right)) return false;
    }
    else return true;
}

void BinaryTree::ReadExpr(string& expr){
    this->DeleteTree(root);
    root = nullptr;
    for (int i = 0; i < expr.length(); i++){
        bool done = false;
        if (expr[i] != '+' && expr[i] != '-' && expr[i] != '*' && expr[i] != '/' && expr[i] != '^' && (expr[i] < '0' || expr[i] > '9') && (expr[i] < 'a' || expr[i] > 'z') &&  (expr[i] < 'A' || expr[i] > 'Z')) throw invalid_argument("Invalid expression");
        insertNode(expr[i], done, root);
        if (!done) throw invalid_argument("Invalid expression");
    }
    if (!checkExpr(root)) throw invalid_argument("Invalid expression");
    this->expr = expr;
}

void BinaryTree::WriteExpr(TreeNode* node){
    if (root == nullptr) return;
    if (!node->isLeaf){
        cout << "(";
        WriteExpr(node->left);
        cout << node->elem;
        WriteExpr(node->right);
        cout << ")";
    }
    else cout << node->elem;
}

void BinaryTree::Assign(char x, int val, TreeNode* node){
    if (!root) throw invalid_argument("Empty expression");
    if (node->isLeaf){
        if (node->elem == x) node->elem = val - '0';
        else return;
    }
    else{
        Assign(x, val, node->left);
        Assign(x, val, node->right);
        return;
    }
}

int BinaryTree::Value(TreeNode* node){
    if (root == nullptr) throw invalid_argument("Empty expression");
    if (node->isLeaf){
        if ('0' <= node->elem && node->elem <= '9') return node->elem - '0';
        else return 0;
    }
    else{
        int left = Value(node->left);
        int right = Value(node->right);
        if (node->elem == '+') return left + right;
        else if (node->elem == '-') return left - right;
        else if (node->elem == '*') return left * right;
        else if (node->elem == '/') return left / right;
        else if (node->elem == '^') return pow(left, (double)right);
    }
}

void BinaryTree::MergeConst(TreeNode* node){
    if (root == nullptr) return;
    if (!node) return;
    MergeConst(node->left);
    MergeConst(node->right);
    if (!node->isLeaf){
        if (node->left->isLeaf && node->right->isLeaf){
            if (node->left->elem >= '0' && node->left->elem <= '9' && node->right->elem >= '0' && node->right->elem <= '9'){
                int left = node->left->elem - '0';
                int right = node->right->elem - '0';
                if (node->elem == '+') node->elem = left + right + '0';
                else if (node->elem == '-') node->elem = left - right + '0';
                else if (node->elem == '*') node->elem = left * right + '0';
                else if (node->elem == '/') node->elem = left / right + '0';
                else if (node->elem == '^') node->elem = pow(left, (double)right) + '0';
                delete node->left;
                delete node->right;
                node->left = nullptr;
                node->right = nullptr;
                node->isLeaf = true;
                return;
            }
        }
    }
}

TreeNode* copyTree(TreeNode* node){
    if (node == nullptr) return nullptr;
    TreeNode* newNode = new TreeNode(node->elem, node->isLeaf, nullptr, nullptr);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
}

void getExpr(TreeNode* node, string& expr){
    if (node == nullptr) return;
    expr += node->elem;
    getExpr(node->left, expr);
    getExpr(node->right, expr);
}

BinaryTree* CompoundExpr(char op, BinaryTree* left, BinaryTree* right){
    BinaryTree* result = new BinaryTree();
    result->root = new TreeNode(op, false, nullptr, nullptr);
    result->root->left = copyTree(left->root);
    result->root->right = copyTree(right->root);
    getExpr(result->root, result->expr);
    return result;
}