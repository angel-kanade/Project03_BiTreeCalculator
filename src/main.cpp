#include <iostream>
#include "add.hpp"
using namespace std;

int main(void){
    int a = 10, b = 20;
    cout << "The sum of " << a << " and " << b << " is " << add(a, b) << endl;
    system("pause");
    return 0;
}
