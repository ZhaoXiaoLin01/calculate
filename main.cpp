#include<iostream>
#include"calculator.h"
using namespace std;
 
int main()
{
	Calculator calculator;
	string str;
	cout << "请输入一个数学表达式（其中要求符号是英文，且无空白符）：" << endl;
	cin >> str;
	double result = calculator.calculate(str);
	cout << result << endl;
	return 0;
 
}
