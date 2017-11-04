#pragma once
#include <iostream>
#include <utility>
#include <list>

#define PRINT_BOTH
// PRINT_BOTH - Prints both push and pop
// PRINT_PUSH - Prints push only
// PRINT_POP  - Prints pop only
//

class StackForQuiz
{
	typedef std::list<std::pair<unsigned int, unsigned int> > PAIR_LIST;
public:
	StackForQuiz() {}
	StackForQuiz(unsigned int startNum, unsigned int endNum);
	
	bool pop(unsigned int count);
	bool pop(unsigned int * num);
	bool peek(unsigned int * num) const;
	
	void push(unsigned int startNum, unsigned int endNum);
	unsigned int size() const;
private:
	PAIR_LIST m_list;
	static std::ostream& s_os;
};
