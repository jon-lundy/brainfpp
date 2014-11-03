// The Parser class encapsulates all BF parsing logic.

#ifndef PARSER_H
#define PARSER_H
#include <fstream>
#include "programnode.h"

class Parser
{
private:
	const char* file_name_;
	std::ifstream source_stream_;
	const int SumAdjacentOperators(const char start_op, const char increment_op, const char decrement_op);	
	const Parser& operator=(const Parser&); // no assignment allowed (there should only be one)
public:
	Parser(const char* file_name);
	const ProgramNode* Parse(bool& program_requires_input);
	~Parser();
};

#endif
