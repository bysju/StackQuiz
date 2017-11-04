// Stack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "Helper.h"



void pop(unsigned int lastPushedItem, unsigned int endNum, const StackForQuiz & stack);
void push(unsigned int startNum, unsigned int endNum, const StackForQuiz & stack);

void push(unsigned int startNum, unsigned int endNum, const StackForQuiz & stack)
{

	for (unsigned int index = startNum; index <= endNum; ++index)
	{
		StackForQuiz newStack(stack);
		newStack.push(startNum, index);
		pop(index , endNum, newStack);
	}

}

void pop(unsigned int lastPushedItem, unsigned int endNum, const StackForQuiz & stack)
{

	if (lastPushedItem > endNum)
	{
		// exception
		//exception
		std::stringstream ss;
		ss << "pop End Num[" << endNum << "] must be equal or bigger than lastPushedItem[" << lastPushedItem << "]";
		throw std::invalid_argument(ss.str());
	}
	else if (0 == stack.size())
	{
		// exception
		std::stringstream ss;
		ss << "pop stack size must not be zero";
		throw std::invalid_argument(ss.str());
	}
	else if (lastPushedItem == endNum)	
	{
		// There is no number to push so we will pop every single number in stack.
		StackForQuiz newStack(stack);
		newStack.pop(newStack.size());
		std::cout << std::endl; // Add new line to indicate finishing one case.
		return;
	}
	else
	{
		unsigned int stackSize = stack.size();
	//	for (unsigned index = 1; index <= stackSize; ++index)

		for (unsigned index = stackSize; index >= 1; --index)
		{
			unsigned int times = index;
			StackForQuiz newStack(stack);
			newStack.pop(index);
			push(lastPushedItem + 1, endNum, newStack);
		}
	}
}


std::ostream& StackForQuiz::s_os = std::cout;
int main()
{
	try
	{
		StackForQuiz stack;
		push(1, 3, stack);
		return 0;
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what();
	}
	catch (...)
	{
		std::cerr << "Unknown exception";
	}
}

