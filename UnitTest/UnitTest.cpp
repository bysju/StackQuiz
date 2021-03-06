// UnitTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Stack/Helper.h"


std::ostream& StackForQuiz::s_os = std::cout;

TEST_CASE("Test for StackForQuiz class with consecutive numbers")
{

	const unsigned int START_NUM_1 = 1;
	const unsigned int START_NUM_2 = 5;
	const unsigned int END_NUM_1 = 12;
	const unsigned int END_NUM_2 = 14;

	const unsigned int START_ADD_NUM = 21;
	const unsigned int END_ADD_NUM = 25;
	StackForQuiz stack1(START_NUM_1, END_NUM_1);
	StackForQuiz stack2;
	stack2.push(START_NUM_2, END_NUM_2);
	SECTION("Check to get correct size.")
	{
		REQUIRE((END_NUM_1 - START_NUM_1 + 1) == stack1.size());
		REQUIRE((END_NUM_2 - START_NUM_2 + 1) == stack2.size());
	}

	SECTION("Check the pop function works correctly.")
	{
		unsigned int number = 0;
		for (unsigned int index = END_NUM_1; index >= START_NUM_1; --index)
		{
			REQUIRE(true == stack1.pop(&number));
			REQUIRE(number == index);
		}

		REQUIRE(false == stack1.pop(&number));

		for (unsigned int index = END_NUM_2; index >= START_NUM_2; --index)
		{
			REQUIRE(true == stack2.pop(&number));
			REQUIRE(number == index);
		}

		REQUIRE(false == stack2.pop(&number));
	}

	SECTION("Check the pop function with count works correctly.")
	{
		
		REQUIRE(true == stack1.pop(END_NUM_1 - START_NUM_1 + 1));
		REQUIRE(0 == stack1.size());
		REQUIRE(false == stack1.pop(1));

		REQUIRE(true == stack2.pop(END_NUM_2 - START_NUM_2 + 1));
		REQUIRE(0 == stack2.size());
		REQUIRE(false == stack2.pop(1));

	}

	SECTION("Check the peek function works correctly.")
	{
		unsigned int number = 0;
		REQUIRE(true == stack1.peek(&number));
		REQUIRE(END_NUM_1 == number);

		REQUIRE(true == stack2.peek(&number));
		REQUIRE(END_NUM_2 == number);

	}

	SECTION("Chceck the push funcion works correctly.")
	{
		unsigned int number = 0;
		stack1.push(START_ADD_NUM, END_ADD_NUM);
		REQUIRE(((END_NUM_1 - START_NUM_1 + 1) + (END_ADD_NUM - START_ADD_NUM + 1)) == stack1.size());

		for (unsigned int index = END_ADD_NUM; index >= START_ADD_NUM; --index)
		{
			REQUIRE(true == stack1.pop(&number));
			REQUIRE(index == number);
		}

		for (unsigned int index = END_NUM_1; index >= START_NUM_1; --index)
		{
			REQUIRE(true == stack1.pop(&number));
			REQUIRE(index == number);
		}

		stack2.push(START_ADD_NUM, END_ADD_NUM);
		REQUIRE(((END_NUM_2 - START_NUM_2 + 1) + (END_ADD_NUM - START_ADD_NUM + 1)) == stack2.size());

		for (unsigned int index = END_ADD_NUM; index >= START_ADD_NUM; --index)
		{
			REQUIRE(true == stack2.pop(&number));
			REQUIRE(index == number);
		}

		for (unsigned int index = END_NUM_2; index >= START_NUM_2; --index)
		{
			REQUIRE(true == stack2.pop(&number));
			REQUIRE(index == number);
		}
	}

}