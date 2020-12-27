#include "Calculator.h"

string opers[] = { "(", ")","+", "-","*", "/", "^","sqrt","abs","exp","log","ln","sin","cos","tg","ctg" };

string constants[] = { "pi", "e" };

void calc::readExpression() 
{
    getline(cin, infix);
	size_t i = 0;
	size_t brackets_counter = 0;
	size_t space_counter = 0;
	while (i < infix.size())
	{
		if(isspace(infix[i]))
			space_counter++;
		if (infix[i] == '(')
			brackets_counter++;
		if (infix[i] == ')')
			brackets_counter--;
		i++;
	}
	if (space_counter == infix.size())
		throw "Expression is empty!";
	if (brackets_counter != 0)
		throw "Syntax error : brackets counter is not even";
}

string calc::getExpression()
{
	return infix;
}

void calc::printExpression()
{
	cout << infix << endl;
}

bool calc::minusCheck(string str, size_t n)
{
	if (n == 0)
	{
		return true;
	}
	while (n > 0)
	{
		if (isspace(str[n - 1]))
		{
			n--;
			continue;
		}
		if (str[n - 1] == '(')
			return true;
		else
			return false;
	}
	return false;
}

int calc::precedence(string str)
{
	if (str == "+" || str == "-")
		return 1;
	else if (str == "*" || str == "/" || str == "%")
		return 2;
	else if (str == "^")
		return 3;
	else if (str == "cos" || str == "sin" || str == "tg" || str == "ctg" || str == "ln" || str == "log" || str == "ln" || str == "sqrt")
		return 4;
	else
		return 0;
}

void calc::infixToPostfix()
{
	size_t i = 0;
	string postfix;
	Stack oper;
	while (i < infix.size())
	{
		if (isspace(infix[i]))
		{
			i++;
			continue;
		}
		else if (isdigit(infix[i]))
		{
			string number;
			while (isdigit(infix[i]) || infix[i] == '.')
			{
				number.push_back(infix[i]);
				i++;
			}
			outstream.push(number);
			postfix += number + ' ';
			continue;
		}
		bool flag = true;
		for (string& p : opers)
		{
			if (infix.find(p.c_str(), i) == i)
			{
				i += p.size();
				flag = false;
				if (p == "(")
				{
					operators.push(p);
					break;
				}
				else if (p == ")")
				{
					if (operators.getTop() == "(")
					{
						operators.pop();
						break;
					}
					while (!operators.isEmpty() && operators.getTop() != "(")
					{
						postfix += operators.pop() + " ";
					}
					operators.pop();
					break;
				}
				else
				{
					if (p == "-" && minusCheck(p,i - p.size()))
					{
							postfix += "0 ";
							operators.push(p);
					}
					else if (!operators.isEmpty() && precedence(operators.getTop()) >= precedence(p))
					{
						do {
							postfix += operators.pop() + " ";
						} while (!operators.isEmpty() && precedence(operators.getTop()) >= precedence(p));
						operators.push(p);
					}
					else
					{
						operators.push(p);
					}
					break;
				}
			}
		}
		if (flag)
		{
			for (string& c : constants)
			{
				if (infix.find(c.c_str(), i) == i)
				{
					flag = false;
					i += c.size();
					stringstream double_const;
					string temp;
					if (c == "e")
					{
						double_const << Exp;
						double_const >> temp;
						postfix += temp + " ";
					}
					else if (c == "pi")
					{
						double_const << pi;
						double_const >> temp;
						postfix += temp + " ";
					}
					break;
				}
			}
		}
		if (flag)
		{
			throw "Syntax error";
		}
	}
	while (!operators.isEmpty())
	{
		if (operators.getTop() == "(")
		{
			operators.pop();
		}
		else
		{
			postfix += operators.pop() + " ";
		}
	}
	this->infix = postfix;
}

double calc::calculate()
{
	double res;
	size_t i = 0;
	while (i < infix.size())
	{
		if (isspace(infix[i]))
		{
			i++;
			continue;
		}
		else if (isdigit(infix[i]))
		{
			string number;
			while (isdigit(infix[i]) || infix[i] == '.')
			{
				number.push_back(infix[i]);
				i++;
			}
			result.push(number);
			continue;
		}
		else if (infix[i] == '+')
		{
			i++;
			res = strtod(result.pop().c_str(), nullptr) + strtod(result.pop().c_str(), nullptr);
			stringstream double_smth;
			string temp;
			double_smth << res;
			double_smth >> temp;
			result.push(temp);
			continue;
		}
		else if (infix[i] == '-')
		{
			i++;
			double value2 = strtod(result.pop().c_str(), nullptr);
			double value1 = strtod(result.pop().c_str(), nullptr);
			value1 -= value2;
			stringstream double_smth;
			string temp;
			double_smth << value1;
			double_smth >> temp;
			result.push(temp);
			continue;
		}
		else if (infix[i] == '*')
		{
			i++;
			res = strtod(result.pop().c_str(), nullptr) * strtod(result.pop().c_str(), nullptr);
			stringstream double_smth;
			string temp;
			double_smth << res;
			double_smth >> temp;
			result.push(temp);
			continue;
		}
		else if (infix[i] == '^')
		{
			i++;
			res = pow(strtod(result.pop().c_str(), nullptr), strtod(result.pop().c_str(), nullptr));
			stringstream double_smth;
			string temp;
			double_smth << res;
			double_smth >> temp;
			result.push(temp);
			continue;
		}
		else if (infix[i] == '/')
		{
			i++;
			double valuev1 = strtod(result.pop().c_str(), nullptr);
			double valuev2 = strtod(result.pop().c_str(), nullptr);
			if (valuev2 == 0.0)
			{
				throw "Division by zero!!!";
			}
			res = valuev1 / valuev2;
			stringstream double_smth;
			string temp;
			double_smth << res;
			double_smth >> temp;
			result.push(temp);
			continue;
		}
		for (string& p : opers)
		{
			if (infix.find(p.c_str(), i) == i)
			{
				i += p.size();
				if (p == "sin")
				{
					double value = strtod(result.pop().c_str(), nullptr);
					value = sin(value);
					stringstream double_smth;
					string temp;
					double_smth << value;
					double_smth >> temp;
					result.push(temp);
				}
				if (p == "cos")
				{
					double value = strtod(result.pop().c_str(), nullptr);
					value = cos(value);
					stringstream double_smth;
					string temp;
					double_smth << value;
					double_smth >> temp;
					result.push(temp);
				}
				if (p == "tg")
				{
					double value = strtod(result.pop().c_str(), nullptr);
					res = tan(value);
					stringstream double_smth;
					string temp;
					double_smth << res;
					double_smth >> temp;
					result.push(temp);
				}
				if (p == "ctg")
				{
					double value = strtod(result.pop().c_str(), nullptr);
					if (tan(value) == 0.0)
					{
						throw "Division by zero!!!";
					}
					else
					{
						res = 1.0 / tan(value);
					}
					stringstream double_smth;
					string temp;
					double_smth << res;
					double_smth >> temp;
					result.push(temp);
				}
				if (p == "ln")
				{
					double value = strtod(result.pop().c_str(), nullptr);
					if (value < 0)
						throw "Error in calculating the logarithm: the number is less than zero";
					res = log(value);
					stringstream double_smth;
					string temp;
					double_smth << res;
					double_smth >> temp;
					result.push(temp);
				}
				if (p == "log")
				{
					double value = strtod(result.pop().c_str(), nullptr);
					if (value < 0)
						throw "Error in calculating the logarithm: the number is less than zero";
					res = log10(value);
					stringstream double_smth;
					string temp;
					double_smth << res;
					double_smth >> temp;
					result.push(temp);
				}
				if (p == "sqrt")
				{
					double value = strtod(result.pop().c_str(), nullptr);
					res = sqrt(value);
					stringstream double_smth;
					string temp;
					double_smth << res;
					double_smth >> temp;
					result.push(temp);
				}
				if (p == "exp")
				{
					double value = strtod(result.pop().c_str(), nullptr);
					res = (value);
					stringstream double_smth;
					string temp;
					double_smth << res;
					double_smth >> temp;
					result.push(temp);
				}
				if (p == "abs")
				{
					double value = strtod(result.pop().c_str(), nullptr);
					res = abs(value);
					stringstream double_smth;
					string temp;
					double_smth << res;
					double_smth >> temp;
					result.push(temp);
				}
			}
			break;
		}
	}
	return strtod(result.pop().c_str(), nullptr);
}