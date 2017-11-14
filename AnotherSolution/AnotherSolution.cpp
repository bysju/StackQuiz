// AnotherSolution.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <sstream>


struct PUSHED_NUMBERS
{
	PUSHED_NUMBERS() : m_previous(nullptr), m_startNum(0), m_endNum(0) {}
	PUSHED_NUMBERS(PUSHED_NUMBERS * pPrevious) : m_previous(pPrevious), m_startNum(0), m_endNum(0) {}
	PUSHED_NUMBERS * m_previous;
	unsigned int	 m_startNum;
	unsigned int	 m_endNum;
};

void Print(unsigned int startNum, unsigned int endNum)
{
	for (unsigned int index = endNum; index >= startNum; ++index)
	{
		std::cout << index;
	}
}

void SaveHistory(unsigned __int64 & history, unsigned int startNum, unsigned int endNum)
{
}

void Push(const unsigned __int64 &  history, PUSHED_NUMBERS * pPushedNumbers, unsigned int startNum, unsigned int endNum, unsigned int lastNum)
{
	// Check the error

	if (lastNum == endNum) // There is not any number to put
	{
		// Print previous poped numbers
		std::cout << history;

		// Print numbers from stack
		Print(startNum, endNum); //current
		while (nullptr != pPushedNumbers)
		{
			Print(pPushedNumbers->m_startNum, pPushedNumbers->m_endNum);
			pPushedNumbers = pPushedNumbers->m_previous;
		}
		std::cout << std::endl;


	}
	else
	{
		PUSHED_NUMBERS pushedNumbers(pPushedNumbers);

		// We have to calculate previous pushed numbers
		for (unsigned int index = startNum; index <= endNum; ++index)
		{
			unsigned __int64 newHistory(history);
			SaveHistory(newHistory, index, endNum);
			
			if (index != startNum)
			{
			}
			
			//Push remain numbers
			for (unsigned int indexEndNum = endNum + 1; indexEndNum <= lastNum; ++indexEndNum)
			{
				

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

			for (unsigned int index = 1; index <= number; ++index)
			{
				DisplayNum(1, index, number);
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
