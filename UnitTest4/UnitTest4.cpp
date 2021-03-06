#include "pch.h"
#include "CppUnitTest.h"
#include "../course_work/Calculator.h"
#include "../course_work/Calculator.cpp"
#include "../course_work/Stack.h"
#include "../course_work/Stack.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest4
{
	TEST_CLASS(UnitTest4)
	{
	public:
		calc calculator;

		TEST_METHOD(TestMethod1)
		{
			string infix = "-1";
			calculator = calc(infix);
			calculator.infixToPostfix();
			string postfix = calculator.getExpression();
			string exp = "0 1 - ";
			Assert::AreEqual(postfix, exp);
		}
		TEST_METHOD(TestMethod2)
		{
			string infix = "(9 + 5)";
			calculator = calc(infix);
			calculator.infixToPostfix();
			string postfix = calculator.getExpression();
			string exp = "9 5 + ";
			Assert::AreEqual(postfix, exp);
		}
		TEST_METHOD(TestMethod3)
		{
			try {
				string infix = "(9 + 5) * can(pi)";
				calculator = calc(infix);
				calculator.infixToPostfix();
			}
			catch (char* e) {
				Assert::AreEqual("Syntax error", e);
			}
		}
		TEST_METHOD(TestMethod4)
		{
			string infix = "9 + 5 + 1";
			calculator = calc(infix);
			calculator.infixToPostfix();
			Assert::AreEqual(int(calculator.calculate()), 15);
		}
		TEST_METHOD(TestMethod5)
		{
			string infix = "2*pi";
			calculator = calc(infix);
			calculator.infixToPostfix();
			Assert::AreEqual(calculator.calculate(), 6.28318);
		}
		TEST_METHOD(TestMethod6)
		{
			string infix = "2^6";
			calculator = calc(infix);
			calculator.infixToPostfix();
			Assert::AreEqual(int(calculator.calculate()), 64);
		}
		TEST_METHOD(TestMethod7)
		{
			string infix = "7 + 8* (9^2) /2";
			calculator = calc(infix);
			calculator.infixToPostfix();
			Assert::AreEqual(calculator.calculate(), 7.00309);
		}
		TEST_METHOD(TestMethod8)
		{
			string infix = "cos(1)";
			calculator = calc(infix);
			calculator.infixToPostfix();
			Assert::AreEqual(calculator.calculate(), 0.540302);
		}
		
			TEST_METHOD(TestMethod9)
		{
			string infix = "sin(2*pi)";
			calculator = calc(infix);
			calculator.infixToPostfix();
			Assert::AreEqual(calculator.calculate(), -5.30718e-06);
		}
			TEST_METHOD(TestMethod10)
			{
				string infix = "tg(10)";
				calculator = calc(infix);
				calculator.infixToPostfix();
				Assert::AreEqual(calculator.calculate(), 0.648361);
			}
			TEST_METHOD(TestMethod11)
			{
				string infix = "ctg(10)";
				calculator = calc(infix);
				calculator.infixToPostfix();
				Assert::AreEqual(calculator.calculate(), 1.54235);
			}
			TEST_METHOD(TestMethod12)
			{
				string infix = "sqrt(16)";
				calculator = calc(infix);
				calculator.infixToPostfix();
				Assert::AreEqual(int(calculator.calculate()), 4);
			}
	};
}
