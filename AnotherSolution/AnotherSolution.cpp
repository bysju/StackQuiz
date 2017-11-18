// AnotherSolution.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <memory>

//#define DETAIL_LOG
#if defined(DETAIL_LOG)
unsigned int g_arrSize = 0;
#endif

void SwapArray(unsigned int arr[], unsigned int index, unsigned int depth);
void ReverseArray(unsigned int arr[], unsigned int arrSize, unsigned int depth);
void PrintArray(unsigned int arr[], unsigned int arrSize );
void InitArray(unsigned int arr[], unsigned int arrSize);

void InitArray(unsigned int arr[], unsigned int arrSize)
{
	for (unsigned int index = 0; index < arrSize; ++index)
		arr[index] = index + 1;
}

void SwapArray(unsigned int arr[], unsigned int index, unsigned int depth)
{

#if defined(DETAIL_LOG)
	std::cout << "=====" << std::endl;
	std::cout << "[SwapArray] index[" << index << "] depth[" << depth << "]" << std::endl;
	std::cout << "Before: ";
	PrintArray(arr, g_arrSize);
#endif

	
	if (depth != index)
	{
		unsigned int temp = arr[depth];
		arr[depth] = arr[index];
		arr[index] = temp;
	}

#if defined(DETAIL_LOG)
	std::cout << "After : ";
	PrintArray(arr, g_arrSize);
	std::cout << "-----" << std::endl;
#endif
	
}

void ReverseArray(unsigned int arr[], unsigned int arrSize, unsigned int depth)
{

#if defined(DETAIL_LOG)
	std::cout << "=====" << std::endl;
	std::cout << "[ReverseArray] arrSize[" << arrSize << "] depth[" << depth << "]" << std::endl;
	std::cout << "Before: ";
	PrintArray(arr, arrSize);
#endif

	unsigned int temp = arr[depth];
	for (unsigned int index = depth; index < (arrSize - 1); ++index)
	{
		arr[index] = arr[index + 1];
	}
	arr[arrSize - 1] = temp;

#if defined(DETAIL_LOG)
	std::cout << "After : ";
	PrintArray(arr, arrSize);
	std::cout << "-----" << std::endl;
#endif
}
void PrintArray(unsigned int arr[], unsigned int arrSize )
{
	for (unsigned int index = 0; index < arrSize; ++index)
	{
		std::cout << arr[index];
	}
	std::cout << std::endl;
}

void Permutation(unsigned int arr[],  unsigned int arrSize, unsigned int depth)
{

	if ((arrSize -1) == depth)	// Arrive at the end.
	{
		PrintArray(arr, arrSize);
		return;
	}

	for (unsigned int index = depth; index < arrSize; ++index)
	{
		SwapArray(arr, index, depth);
		Permutation(arr, arrSize, depth + 1);
	}

	ReverseArray(arr, arrSize, depth);
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

#if defined (DETAIL_LOG)
			g_arrSize = number;
#endif

			std::unique_ptr<unsigned int[]> numArray(new unsigned int[number]);
			InitArray(numArray.get(), number);


			Permutation(numArray.get(), number, 0);

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
