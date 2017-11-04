#include "stdafx.h"
#include "Helper.h"
#include <sstream>

StackForQuiz::StackForQuiz(unsigned int startNum, unsigned int endNum)
{
	if (startNum > endNum)
	{
		//exception
		std::stringstream ss;
		ss << "StackForQuiz::StackForQuiz End Num[" << endNum << "] must be equal or bigger than startNum[" << startNum << "]";
		throw std::invalid_argument(ss.str());
	}

	m_list.push_back(PAIR_LIST::value_type(startNum, endNum));
}

unsigned int StackForQuiz::size() const
{
	if (m_list.empty())
		return 0;
	else
	{
		unsigned int count = 0;
		for (const PAIR_LIST::value_type & pair : m_list)
		{
			count += (pair.second - pair.first + 1);
		}

		return count;
	}
}

void StackForQuiz::push(unsigned int startNum, unsigned int endNum)
{
	if (startNum > endNum)
	{
		//exception
		std::stringstream ss;
		ss << "StackForQuiz::push End Num[" << endNum << "] must be equal or bigger than startNum[" << startNum << "]";
		throw std::invalid_argument(ss.str());
	}
	else
	{
		if (m_list.empty())
		{
			m_list.push_back(PAIR_LIST::value_type(startNum, endNum));
			for (unsigned int index = startNum; index <= endNum; ++index)
			{
#if defined(PRINT_BOTH) || defined(PRINT_PUSH)
				s_os << "[" << index << "]";
#endif
			}
		}
		else
		{

			//Do not allow to push smaller value than the value that m_list has
			//So, compare starNum and the largest value that m_list has
			const PAIR_LIST::value_type & pair = m_list.back();
			if (startNum <= pair.second)
			{
				//exception
				std::stringstream ss;
				ss << "StackForQuiz::push Start Num[" << startNum << "] must be bigger than the list's largest value[" << pair.second << "]";
				throw std::invalid_argument(ss.str());
			}
			else
			{
				m_list.push_back(PAIR_LIST::value_type(startNum, endNum));
				for (unsigned int index = startNum; index <= endNum; ++index)
				{
#if defined(PRINT_BOTH) || defined(PRINT_PUSH)
					s_os << "[" << index << "]";
#endif
				}
			}
		}
	}
}

bool StackForQuiz::peek(unsigned int * num) const
{
	if (m_list.empty())
		return false;
	else
	{
		const PAIR_LIST::value_type & pair = m_list.back();
		*num = pair.second;
		return true;
	}
}

bool StackForQuiz::pop(unsigned int * num)
{
	if (m_list.empty())
		return false;
	else
	{
		PAIR_LIST::value_type & pair = m_list.back();
		*num = pair.second;
		
		if (pair.first == pair.second)	// Remove ths block if this block has only one number.
		{
			m_list.pop_back();
		}
		else
		{
			--pair.second;	// Decrease one;
		}
#if defined(PRINT_BOTH) || defined(PRINT_POP)
		s_os << (*num);
#endif
		return true;
	}

}

bool StackForQuiz::pop(unsigned int count)
{
	if (m_list.empty() || count > size())
		return false;
	else
	{
		while (count > 0)
		{
			PAIR_LIST::value_type & pair = m_list.back();
			if (count >= (pair.second - pair.first + 1))	// Remove the black if count is bigger than black size
			{
				count -= (pair.second - pair.first + 1);
				for (unsigned int index = pair.second; index >= pair.first; --index)
				{
#if defined(PRINT_BOTH) || defined(PRINT_POP)
					s_os << index;
#endif
				}

				m_list.pop_back();
				
			}
			else
			{
				unsigned int newLargestNum = pair.second - count;
				for (unsigned int index = pair.second; index > newLargestNum; --index)
				{
#if defined(PRINT_BOTH) || defined(PRINT_POP)
					s_os << index;
#endif
				}

				pair.second = newLargestNum;
				break;
			}
		}
		return true;
	}
}