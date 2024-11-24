#include "classDeclare.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;

void terminalInteract(){
    while (true){
        cout << "欢迎使用基于二叉树的表达式计算器！" << endl;
        cout << "本程序提供以下功能：" << endl;
        cout << "输入\"1\"，用带括号的中缀表达式输出表达式。" << endl;
        cout << "输入\"2\"，实现对表达式中某一个变量的赋值。" << endl;
        cout << "输入\"3\"，计算表达式的值。" << endl;
        cout << "输入\"4\"，合并两个表达式，形成一个新的复合表达式。" << endl;
        cout << "输入\"5\"，合并表达式中的常量项。" << endl;
        cout << "输入\"6\"，退出程序。" << endl;
        cout << "请输入您的选择：" << endl;
        string choice;
        cin.clear();
        getline(cin, choice);
        if (choice == "1"){
            cout << "请按要求输入前缀表达式，";
            cout << "算术表达式内可以含有变量(a~z)、常量(0~9)和二元运算符(+,-,*,/,^(乘幂))。" << endl;
            cout << "请输入你需要的表达式：" << endl;
            string expression;
            cin.clear();
            getline(cin, expression);
            BinaryTree bt;
            try{
                bt.ReadExpr(expression);
                cout << "带括号的中缀表达式为：" << endl;
                bt.WriteExpr(bt.root);
                cout << endl << endl;
            }
            catch (exception& e){
                cout << e.what() << endl << endl;
                continue;
            }
        }
        else if (choice == "2"){
            cout << "请按要求输入前缀表达式，";
            cout << "算术表达式内可以含有变量(a~z)、常量(0~9)和二元运算符(+,-,*,/,^(乘幂))。" << endl;
            cout << "请输入你需要的表达式：" << endl;
            string expression;
            cin.clear();
            getline(cin, expression);
            BinaryTree bt;
            try{
                bt.ReadExpr(expression);
                cout << "请输入你需要赋值的变量：" << endl;
                string var;
                cin.clear();
                getline(cin, var);
                if (var.length() != 1 || (var[0] < 'a' || var[0] > 'z')){
                    cout << "输入的变量名不合法！" << endl;
                    continue;
                }
                cout << "请输入你需要赋值的数值：" << endl;
                int value;
                cin.clear();
                cin >> value;
                bt.Assign(var[0], value, bt.root);
                cout << "赋值后的表达式为：" << endl;
                bt.WriteExpr(bt.root);
                cout << endl << endl;
            }
            catch (exception& e){
                cout << e.what() << endl << endl;
                continue;
            }
        }
        else if (choice == "3"){
            cout << "请按要求输入前缀表达式，";
            cout << "算术表达式内可以含有变量(a~z)、常量(0~9)和二元运算符(+,-,*,/,^(乘幂))。" << endl;
            cout << "请输入你需要的表达式：" << endl;
            string expression;
            cin.clear();
            getline(cin, expression);
            BinaryTree bt;
            try{
                bt.ReadExpr(expression);
                cout << "如果表达式中含有变量，将会默认赋值为0进行计算，下边是计算结果：" << endl;
                cout << bt.Value(bt.root) << endl << endl;
            }
            catch (exception& e){
                cout << e.what() << endl << endl;
                continue;
            }
        }
        else if (choice == "4"){
            cout << "请按要求输入前缀表达式，";
            cout << "算术表达式内可以含有变量(a~z)、常量(0~9)和二元运算符(+,-,*,/,^(乘幂))。" << endl;
            cout << "请输入第一个表达式：" << endl;
            string expression1;
            cin.clear();
            getline(cin, expression1);
            BinaryTree bt1;
            try{
                bt1.ReadExpr(expression1);
                cout << "请输入第二个表达式：" << endl;
                string expression2;
                cin.clear();
                getline(cin, expression2);
                BinaryTree bt2;
                bt2.ReadExpr(expression2);
                cout << "请输入合并的运算符：" << endl;
                string op;
                cin.clear();
                getline(cin, op);
                if (op != "+" && op != "-" && op != "*" && op != "/" && op != "^"){
                    cout << "输入的运算符不合法！" << endl;
                    continue;
                }
                BinaryTree* bt3 = CompoundExpr(op[0], &bt1, &bt2);
                cout << "合并后的中缀表达式为：" << endl;
                bt3->WriteExpr(bt3->root);
                cout << endl;
                cout << "合并后的前缀表达式为：" << endl;
                cout << bt3->expr;
                cout << endl << endl;
                delete bt3;
            }
            catch (exception& e){
                cout << e.what() << endl << endl;
                continue;
            }
        }
        else if (choice == "5"){
            cout << "请按要求输入前缀表达式，";
            cout << "算术表达式内可以含有变量(a~z)、常量(0~9)和二元运算符(+,-,*,/,^(乘幂))。" << endl;
            cout << "请输入你需要的表达式：" << endl;
            string expression;
            cin.clear();
            getline(cin, expression);
            BinaryTree bt;
            try{
                bt.ReadExpr(expression);
                cout << "合并后的中缀表达式为：" << endl;
                bt.WriteExpr(bt.root);
                cout << endl;
                cout << "合并后的前缀表达式为：" << endl;
                bt.MergeConst(bt.root);
                cout << bt.expr << endl << endl;
            }
            catch (exception& e){
                cout << e.what() << endl << endl;
                continue;
            }
        }
        else if (choice == "6"){
            cout << "感谢使用，欢迎客官再次使用喵！" << endl << endl << endl;
            break;
        }
        else{
            cout << "输入的选项不合法！" << endl << endl;
            continue;
        }
    }
}
