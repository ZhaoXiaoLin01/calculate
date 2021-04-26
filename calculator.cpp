#include<stack>
#include<iostream>
#include<map>
#include <algorithm>
#include"calculator.h"

using namespace std;

void Calculator::init(int num)
{
	char str[16] = { '0','1','2','3','4','5','6','7','8','9','.','+','-','*','/' };
	m_num = num;
	for (int i = 0; str[i] != '\0'; i++)
		m_standard.push_back(str[i]);
}

bool Calculator::isStandard(const string &expression) const
{
	for (int i = 0; i<expression.size(); i++)
	{
		if (find(m_standard.begin(), m_standard.end(), expression[i]) == m_standard.end())
			return false;
	}
	return true;
}
bool Calculator::isSign(char ch) const
{
	if (find(m_standard.begin() + 11, m_standard.end(), ch) == m_standard.end())
		return false;
	return true;
}

double string_to_digit(const string &str)
{
	double digit = 0;
	if (find(str.begin(), str.end(), '.') == str.end())
	{
		int n = 1;
		for (int i = str.size() - 1; i >= 0; i--)
		{
			digit += (str[i] - '0')*n;
			n *= 10;
		}
	}
	else
	{
		int n = 1;
		int location = find(str.begin(), str.end(), '.') - str.begin();
		for (int i = location - 1; i >= 0; i--)
		{
			digit += (str[i] - '0')*n;
			n *= 10;
		}
		double m = 0.1;
		for (int i = location + 1; i<str.size(); i++)
		{
			digit += (str[i] - '0')*m;
			m *= 0.1;
		}
	}
	return digit;
}
void Calculator::infixToSuffix(const string &expression, vector<double> &num_vec, vector<char> &cmp_vec, vector<bool> &loc_vec)const
{
	if (!isStandard(expression))
	{
		cerr << "**********输入有误**********" << endl;
		exit(EXIT_FAILURE);
	}
	int first = 0;
	stack<char> stackChar;
	for (int i = 0; i<expression.size(); i++)
	{
		if (isSign(expression[i]) || (i == expression.size() - 1))
		{
			string substr(expression.begin() + first, expression.begin() + i);
			if (i == expression.size() - 1 && !isSign(expression[i]))   //当i代表最后一个字符且不是运算符的时候，那么这个数字得合并向前一个数字中
				substr += expression[i];
			if (!substr.empty())   //此时处理的是数字
			{
				double num = string_to_digit(substr);
				num_vec.push_back(num);
				loc_vec.push_back(false);
			}
			if(isSign(expression[i]))    //处理字符的时候
			{
				if(!stackChar.empty())
				{
					char ch = stackChar.top();
					cmp_vec.push_back(ch);
					stackChar.pop();
					loc_vec.push_back(true);
				}
				else
					stackChar.push(expression[i]);	
			}
			first=i+1;
		}
	}
	while (!stackChar.empty())
	{
		cmp_vec.push_back(stackChar.top());
		stackChar.pop();
		loc_vec.push_back(true);
	}
}
double Calculator::calculate(const string &expression) const
{
	vector<double> num_vec;
	vector<char> cmp_vec;
	vector<bool> loc_vec;
	stack<double> stackDouble;
	stack<char> stackChar;
	int index_num = 0, index_cmp = 0;
	infixToSuffix(expression, num_vec, cmp_vec, loc_vec);
 
	for (int i = 0; i < loc_vec.size(); i++)
	{
		if (!loc_vec[i])      //当i位置处是数字的时候
		{
			stackDouble.push(num_vec[index_num++]);
		}
		else
		{
			if (stackDouble.size() < 2)
			{
				cerr << "输入的表达式有误，无法计算" << endl;
				exit(EXIT_FAILURE);
			}
			double num1 = stackDouble.top();
			stackDouble.pop();
			double num2 = stackDouble.top();
			stackDouble.pop();
			stackDouble.push(arithmeticSign(cmp_vec[index_cmp++], num2, num1));
		}
	}
	if (stackDouble.size() != 1 || !stackChar.empty())
	{
		cerr << "输入的表达式有误，无法计算" << endl;
		exit(EXIT_FAILURE);
	}
	return stackDouble.top();
}
double Calculator::arithmeticSign(char sign, double num1, double num2) const
{
	if (sign == '+')
		return num1 + num2;
	else if (sign == '-')
		return num1 - num2;
	else if (sign == '*')
		return num1*num2;
	else if (sign == '/')
	{
		if (num2 == 0)
		{
			cerr << "********除数不能为0*******" << endl;
			exit(EXIT_FAILURE);
		}
		return num1 / num2;
	}
}
