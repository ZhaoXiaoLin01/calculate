#include<iostream>
#include"calculator.h"
using namespace std;
 
int main()
{
	Calculator calculator;
	string str1,str2,str3,str4,str5;
	str1="1+2";
	str2="1-2";
	str3="1*2";
	str4="1/2";
	str5="001+002";
	double result1 = calculator.calculate(str1);
	cout << str1<<"="<<result1<< endl;
	double result2 = calculator.calculate(str2);
	cout << str1<<"="<<result2<< endl;
	double result3 = calculator.calculate(str3);
	cout << str1<<"="<<result3<< endl;
	double result4 = calculator.calculate(str4);
	cout << str1<<"="<<result4<< endl;
	double result5 = calculator.calculate(str5);
	cout << str1<<"="<<result5<< endl;
	return 0;
 
}
