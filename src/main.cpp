#include "classDeclare.hpp"
using namespace std;

void terminalInteract();

int main(void){
    while (true){
        cout << "本程序是基于二叉树表示的算术表达式计算器。" << endl;
        cout << "如要继续程序，请输入\"1\"，退出程序请输入\"0\":" << endl;
        string choice;
        cin.clear();
        getline(cin, choice);
        if (choice == "0"){
            cout << "感谢使用，客官下次再来喵！" << endl;
            break;
        }
        else if (choice == "1"){
            terminalInteract();
        }
        else {
            cout << "输入错误，请重新输入！" << endl << endl << endl;
            continue;
        }
    }
    return 0;
}