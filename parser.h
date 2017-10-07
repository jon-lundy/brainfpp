// The Parser class encapsulates all BF parsing logic.

#ifndef PARSER_H
#define PARSER_H
#include "noncopyable.h"
#include "programnode.h"
#include "tokenstream.h"

class Parser : private NonCopyable<Parser>
{
private:
	const char* file_name_;
	TokenStream* token_stream_;
	const int SumAdjacentOperators(const char start_op, const char increment_op, const char decrement_op);

public:
	Parser(const char* file_name);
	const ProgramNode* Parse(bool& program_requires_input);
	~Parser();
};

#endif
