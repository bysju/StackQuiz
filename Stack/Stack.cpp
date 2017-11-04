// Stack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "Helper.h"


/*

void push(unsigned int startNum, unsigned int endNum, const RemainItems & remainItems)
{

	unsigned int lastNumber = startNum;

	while (lastNumber <= endNum)
	{
		unsigned int index = startNum;
		for ( ; index <= lastNumber; ++index)
		{
			std::cout << index;
		}
		++lastNumber;
		pop(index, endNum, remainItems);
		std::cout << std::endl;
	}
	
}

void pop(unsigned int lastItem, unsigned int endNum, const RemainItems & remainItems)
{
	int firstItem = remainItems.GetFirstItem();

	if (lastItem > endNum)
	{
		// exception
	}
	else if (lastItem == endNum)
	{
		// Pop every remain numbers if there is no item to push.
		for (unsigned index = lastItem; firstItem <= index; index = remainItems.GetNextItem(index))
		{
			std::cout << index;
		}
		
		return;
	}
	else
	{

		unsigned int stopNumber = lastItem;
		while (stopNumber >= firstItem)
		{
			RemainItems newRemainItems(remainItems);
			unsigned int index = lastItem;
			for (; index >= stopNumber; index = remainItems.GetNextItem(index))
			{
				std::cout << index;
				newRemainItems.AddGap(index);
			}
			
			push(lastItem + 1, endNum, newRemainItems);
		}
	}
}

*/

/*
void pop(unsigned int startNum, unsigned int lastPushedItem, unsigned int endNum);
void PopWithoutPush(unsigned int startNum, unsigned int endNum);

unsigned int push(unsigned int startNum, unsigned int endNum)
{

	unsigned int lastNumber = startNum;

	while (lastNumber <= endNum)
	{
		unsigned int index = startNum;
		for (; index <= lastNumber; ++index)
		{
			std::cout << index;
		}
		pop(startNum, index-1, endNum);
		std::cout << std::endl;	//for test
		++lastNumber;
	}

	return endNum;

}

void pop(unsigned int startNum, unsigned int lastPushedItem, unsigned int endNum)
{

	if (lastPushedItem > endNum)
	{
		// exception
	}
	else if (lastPushedItem == endNum)
	{
		// Pop every remain numbers if there is no item to push.
		for (unsigned int index = lastPushedItem; startNum <= index; --index)
		{
			std::cout << index;
		}

		return;
	}
	else
	{

		unsigned int stopNumber = lastPushedItem;
		while (stopNumber >= startNum)
		{
			unsigned int index = lastPushedItem;
			for (; index >= stopNumber; --index)
			{
				std::cout << index;
			}

			unsigned int newLastPushedItem = push(lastPushedItem + 1, endNum); //Push remained numbers to stack

			if (index != startNum)
			{
				PopWithoutPush(startNum, index-1);
			}

		}
	}
}

void PopWithoutPush(unsigned int startNum, unsigned int endNum)
{
	// Pop every remain numbers if there is no item to push.
	for (unsigned int index = endNum; startNum <= index; --index)
	{
		std::cout << index;
	}
}
*/

void pop(unsigned int lastPushedItem, unsigned int endNum, const StackForQuiz & stack);

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

