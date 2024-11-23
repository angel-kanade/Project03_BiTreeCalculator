#include "classDeclare.hpp"

// typedef struct TreeNode {
//     char elem;
//     struct TreeNode* left;
//     struct TreeNode* right;
//     TreeNode(char e = 0, struct TreeNode* l = nullptr, struct TreeNode* r = nullptr): elem(e), left(l), right(r) {}
// } TreeNode;

// class BinaryTree {
// private:
//     TreeNode* root;
// public:
//     BinaryTree();
//     ~BinaryTree();
//     void ReadExpr(string& expr);
//     void WriteExpr();
//     void Assign(char x, int val);
//     int Value();
//     BinaryTree* Diff(char x);
//     void MergeConst();
//     void DeleteTree();
//     void insertNode(char x, bool& done);
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
        else throw invalid_argument("Variable not assigned");
    }
    else{
        int left = Value(node->left);
        int right = Value(node->right);
        if (node->elem == '+') return left + right;
        else if (node->elem == '-') return left - right;
        else if (node->elem == '*') return left * right;
        else if (node->elem == '/') return left / right;
        else if (node->elem == '^') return pow(left, right);
    }
}

void BinaryTree::MergeConst(TreeNode* node){
    if (root == nullptr) return;
    if (!node->isLeaf){
        if (node->left->isLeaf && node->right->isLeaf){
            if (node->left->elem >= '0' && node->left->elem <= '9' && node->right->elem >= '0' && node->right->elem <= '9'){
                int left = node->left->elem - '0';
                int right = node->right->elem - '0';
                if (node->elem == '+') node->elem = left + right + '0';
                else if (node->elem == '-') node->elem = left - right + '0';
                else if (node->elem == '*') node->elem = left * right + '0';
                else if (node->elem == '/') node->elem = left / right + '0';
                else if (node->elem == '^') node->elem = pow(left, right) + '0';
                delete node->left;
                delete node->right;
                node->left = nullptr;
                node->right = nullptr;
                node->isLeaf = true;
                return;
            }
        }
        else{
            MergeConst(node->left);
            MergeConst(node->right);
            return;
        }
    }
}