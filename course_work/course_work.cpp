#include <iostream>
#include "Calculator.h"

using namespace std;

int main()
{
	calc expression;
	cout << "Enter expression :" << endl;
	expression.readExpression();
	expression.infixToPostfix();
	cout << "Postfix form :" << endl;
	expression.printExpression();
	double ans = expression.calculate();
	cout << "Answer :" << endl;
	cout << ans << endl;
	return 0;
}
  