#ifndef CALCULATOR_H
#define CALCULATOR_H
#include<string>
#include<vector>
 
using namespace std;
class Calculator
{
public:
	Calculator(int num = 0)
	{
		init(num);
	}
	bool isValid(const string &expression) const;
	double calculate(const string &expression) const;    //主要是对后缀表达式求解结果
	double arithmeticSign(char sign, double num1, double num2) const;   //用于计算两个数之间的结果  
	friend double string_to_digit(const string &str);  //将字符串转化为数字
private:
	int m_num;
	vector<char> m_standard;
	void init(int num);
	bool isStandard(const string &expression) const;
	bool isSign(char ch) const;      //判断一个字符是否是运算符
	void infixToSuffix(const string &expression, vector<double> &num_vec, vector<char> &cmp_vec, vector<bool> &loc_vec)const;   //将一个中缀表达式转化为后缀表达式
};
#endif

