// AnotherSolution.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <sstream>





struct PUSHED_NUMBERS
{
	PUSHED_NUMBERS() : m_previous(nullptr), m_startNum(0), m_endNum(0) {}
	PUSHED_NUMBERS(PUSHED_NUMBERS * pPrevious, unsigned int startNum, unsigned int endNum) : m_previous(pPrevious), m_startNum(startNum), m_endNum(endNum) {}
	PUSHED_NUMBERS * m_previous;
	unsigned int	 m_startNum;
	unsigned int	 m_endNum;
};

unsigned int CountNumbers(unsigned int num);
void SaveHistory(unsigned __int64 & history, unsigned int startNum, unsigned int endNum);
unsigned int GetPushedNumbersCount(const PUSHED_NUMBERS & pushedNumbers);
void PrintAndUpdatePushedNumbers(unsigned __int64 & history, PUSHED_NUMBERS & pushedNumbers, unsigned int count);
void SaveHistory(unsigned __int64 & history, unsigned int startNum, unsigned int endNum);
void Push(const unsigned __int64 &  history, PUSHED_NUMBERS * pPushedNumbers, unsigned int startNum, unsigned int endNum, unsigned int lastNum);

unsigned int CountNumbers(unsigned int num)
{
	unsigned int count = 0;
	while (0 != num)
	{
		++count;
		num /= 10;
	}
	return count;
}

unsigned int GetPushedNumbersCount(const PUSHED_NUMBERS & pushedNumbers)
{

	const PUSHED_NUMBERS * pPushedNumbers = &pushedNumbers;
	unsigned count = 0;
	while (nullptr != pPushedNumbers)
	{
		if (pPushedNumbers->m_startNum > pPushedNumbers->m_endNum)
		{
			//exception
			std::stringstream ss;
			ss << "GetPushedNumbersCount End Num[" << pPushedNumbers->m_endNum << "] must be equal or bigger than startNum[" << pPushedNumbers->m_startNum << "]";
			throw std::invalid_argument(ss.str());
		}
		else if (pPushedNumbers->m_startNum == 0 && pPushedNumbers->m_endNum == 0)
		{
			// count += 0
		}
		else if ((pPushedNumbers->m_startNum == 0 && pPushedNumbers->m_endNum != 0)
			|| (pPushedNumbers->m_startNum != 0 && pPushedNumbers->m_endNum == 0))
		{
			//exception
			std::stringstream ss;
			ss << "GetPushedNumbersCount End Num[" << pPushedNumbers->m_endNum << "]  or Start Num[" << pPushedNumbers->m_startNum << "] should not be zero";
			throw std::invalid_argument(ss.str());
		}
		else
		{
			count += (pPushedNumbers->m_endNum - pPushedNumbers->m_startNum + 1);
		}

		pPushedNumbers = pPushedNumbers->m_previous;
	}

	return count;
}

void PrintAndUpdatePushedNumbers(unsigned __int64 & history, PUSHED_NUMBERS & pushedNumbers, unsigned int count)
{
	if (0 >= count)
	{
		std::stringstream ss;
		ss << "PrintAndUpdatePushedNumbers count must be bigger thant zero count[" << count << "]";
		throw std::invalid_argument(ss.str());
	}
	PUSHED_NUMBERS * pPushNumbers = &pushedNumbers;
	while (0 != count && nullptr != pPushNumbers)
	{
		unsigned int currentBlockCount = (pPushNumbers->m_endNum - pPushNumbers->m_startNum + 1);
		if (currentBlockCount <= count)
		{
			SaveHistory(history, pPushNumbers->m_startNum, pPushNumbers->m_endNum);		//Pop all numbers in the block.
			count -= currentBlockCount;
			pPushNumbers = pPushNumbers->m_previous;

			if (nullptr == pPushNumbers)
			{
				pushedNumbers.m_previous = nullptr;
				pushedNumbers.m_startNum = 0;
				pushedNumbers.m_endNum = 0;
			}
			else
				pushedNumbers = *pPushNumbers;		// Remove current block in the chain of block;
		}
		else
		{
			SaveHistory(history, pPushNumbers->m_startNum + ( currentBlockCount - count), pPushNumbers->m_endNum);
			pushedNumbers.m_endNum -= count;
			return;
		}
	}

	if (0 != count)
	{
		//exception
		std::stringstream ss;
		ss << "PrintAndUpdatePushedNumbers count should be zero in the end of function count[" << count << "] PUSHED_NUMBER startNum[" << pushedNumbers.m_startNum << "] PUSHED_NUMBER endNum[" << pushedNumbers.m_endNum << "]";
		throw std::logic_error(ss.str());
	}
}

void Print(unsigned int startNum, unsigned int endNum)
{
	if (startNum <= 0 || endNum <= 0)
	{
		std::stringstream ss;
		ss << "Print Start Num[" << startNum << "]  and End Num[" << endNum << "] should not be zero";
		throw std::invalid_argument(ss.str());
	}
	for (unsigned int index = endNum; index >= startNum; --index)
	{
		std::cout << index;
	}
}

void SaveHistory(unsigned __int64 & history, unsigned int startNum, unsigned int endNum)
{
	for (unsigned int index = endNum; index >= startNum; --index)
	{
		if (0 == history)
			history = index;
		else
		{
			unsigned digitCount = CountNumbers(index);
			history = history * static_cast<unsigned int>(std::pow(10, digitCount));
			history += index;
		}
	}
}

void Push(const unsigned __int64 &  history, PUSHED_NUMBERS * pPushedNumbers, unsigned int startNum, unsigned int endNum, unsigned int lastNum)
{
	// Check the error
	if (0 == startNum || 0 == endNum)
	{
		std::stringstream ss;
		ss << "Push Start Num[" << startNum << "]  and End Num[" << endNum << "] should not be zero";
		throw std::invalid_argument(ss.str());
	}
	else if (startNum > endNum)
	{
		std::stringstream ss;
		ss << "Push End Num[" << startNum << "]  or Start Num[" << endNum << "] should not be zero";
		throw std::invalid_argument(ss.str());
	}

	if (lastNum == endNum) // There is not any number to put
	{
		// Print previous poped numbers
		if( 0 != history)
			std::cout << history;

		// Print numbers from stack
		Print(startNum, endNum); //current
		while (nullptr != pPushedNumbers && 0 != pPushedNumbers->m_startNum && 0 != pPushedNumbers->m_endNum)
		{
			Print(pPushedNumbers->m_startNum, pPushedNumbers->m_endNum);
			pPushedNumbers = pPushedNumbers->m_previous;
		}
		std::cout << std::endl;


	}
	else
	{
		
		PUSHED_NUMBERS pushedNumbers(pPushedNumbers, startNum, endNum);
		// We have to calculate previous pushed numbers

		unsigned int count = GetPushedNumbersCount(pushedNumbers);
		if (0 == count)
		{
			//exception
			std::stringstream ss;
			ss << "Push End Num[" << endNum << "] must be equal or bigger than startNum[" << startNum << "]";
			throw std::invalid_argument(ss.str());
		}
	
		for ( ; count >= 1; --count)
		{
			PUSHED_NUMBERS newPushedNumbers(pushedNumbers);
			unsigned __int64 newHistory(history);

			PrintAndUpdatePushedNumbers(newHistory, newPushedNumbers, count);
			for (unsigned int endIndex = endNum + 1; endIndex <= lastNum; ++endIndex)
			{
				Push(newHistory, &newPushedNumbers, endNum + 1, endIndex, lastNum);
			}
		}
	}
}




int main()
{
	try
	{
		while (true)
		{
#if defined PRINT_TIME
			typedef std::chrono::high_resolution_clock Clock;
			typedef std::chrono::seconds Seconds;
			Clock::time_point pt1 = Clock::now();
#endif
			std::string input;
			std::getline(std::cin, input);

			int number = std::stoi(input);
			if (0 == number)
				break;
			else if (17 <= number || 0 > number )
			{
				std::cout << "Please enter only numbers between 0 and 16!" << std::endl;
				break;
			}

			unsigned __int64 histroy = 0;
			for (unsigned int index = 1; index <= static_cast<unsigned int>(number); ++index)
			{
				Push(histroy, nullptr, 1, index, number);
			}

#if defined PRINT_TIME
			Clock::time_point pt2 = Clock::now();
			Seconds seconds = std::chrono::duration_cast<Seconds>(pt2 - pt1);

			std::cout << "Complete: " << seconds.count() << std::endl;
#endif
			std::cout << std::endl;
		}

	}
	catch (const std::exception & e)
	{
		std::cerr << e.what();
	}
	catch (...)
	{
		std::cerr << "Unknown exception";
	}

	return 0;
}
