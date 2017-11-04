// Stack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <list>
#include "Helper.h"

typedef std::list<unsigned int> POP_DATA;

void pop(unsigned int lastPushedItem, unsigned int endNum, const StackForQuiz & stack, const POP_DATA & popData);
void push(unsigned int startNum, unsigned int endNum, const StackForQuiz & stack, const POP_DATA & popData);

void push(unsigned int startNum, unsigned int endNum, const StackForQuiz & stack, const POP_DATA & popData)
{

	for (unsigned int index = startNum; index <= endNum; ++index)
	{
		StackForQuiz newStack(stack);
		newStack.push(startNum, index);
		pop(index , endNum, newStack, popData);
	}

}

void pop(unsigned int lastPushedItem, unsigned int endNum, const StackForQuiz & stack, const POP_DATA & popData)
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
	//	newStack.pop(newStack.size());

		POP_DATA newPopData(popData);
		unsigned int number = 0;
		while (newStack.pop(&number))
		{
			newPopData.push_back(number);
		}

		std::cout << " result: ";
		for (const POP_DATA::value_type & data : newPopData)
			std::cout << data;

		std::cout << std::endl; // Add new line to indicate finishing one case.
		return;
	}
	else
	{
		unsigned int stackSize = stack.size();
		for (unsigned index = stackSize; index >= 1; --index)
		{
			unsigned int times = index;
			StackForQuiz newStack(stack);
			POP_DATA newPopData(popData);
		//	newStack.pop(index);

			unsigned int number = 0;
			while (times--)
			{
				newStack.pop(&number);
				newPopData.push_back(number);

			}
			push(lastPushedItem + 1, endNum, newStack, newPopData);
		}
	}
}


std::ostream& StackForQuiz::s_os = std::cout;
int main()
{
	try
	{
		POP_DATA popData;
		StackForQuiz stack;
		push(1, 5, stack, popData);
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

