#include <iostream>
#include <vector>
#include "abstractnode.h"
#include "datanode.h"
#include "inputnode.h"
#include "loopnode.h"
#include "outputnode.h"
#include "parser.h"
#include "pointernode.h"
#include "programnode.h"
#include "tokenstream.h"

Parser::Parser(const char* file_name) : 
			file_name_(file_name),
			token_stream_(new TokenStream(file_name))
{}

const int Parser::SumAdjacentOperators(const char start_op, const char increment_op, const char decrement_op)
{
	int total_diff;
	if (start_op == increment_op) {
		total_diff = 1;
	} else if (start_op == decrement_op) {
		total_diff = -1;
	} else {
		return 0;
	}
	
	// only peek, b/c if it's not a character we care about it should be left
	// to the main parsing routine
	char next = token_stream_->Peek();
	while (next == increment_op || next == decrement_op) {
		total_diff += (next == increment_op ? 1 : -1);
		token_stream_->Get();
		next = token_stream_->Peek();
	}
	return total_diff;
}

// Parses the program.  Note this allocates the tree, so you'll need to delete this pointer.
const ProgramNode* Parser::Parse(bool& program_requires_input)
{
	program_requires_input = false;

	// check that file opened OK
	if (!token_stream_->IsOpen()) {
		std::cout << "Failed to open " << file_name_ << ". Make sure the file exists and that the path is correct." << std::endl;
		return nullptr;
	}

	// create root node
	ProgramNode* root = new ProgramNode();

	// create node stack, for loops
	std::vector<AbstractNode*> parentStack;
	parentStack.push_back(root);

	// begin reading program
	char c = token_stream_->Get();

	// loop until the read fails
	while (token_stream_->Good()) {
		// switch on input character
		switch (c) {
		case '>':
		case '<':
			new PointerNode(parentStack.back(), SumAdjacentOperators(c, '>', '<'));
			break;
		case '+':
		case '-':
			new DataNode(parentStack.back(), SumAdjacentOperators(c, '+', '-'), false);
			break;
		case '.':
			new OutputNode(parentStack.back());
			break;
		case ',':
			new InputNode(parentStack.back());
			program_requires_input = true;
			break;
		case '[':
			{ 
				LoopNode* loop = new LoopNode(parentStack.back());
				parentStack.push_back(loop);
			}
			break;
		case ']':
			parentStack.pop_back();
			// make sure we didn't pop root, since that indicates a mismatched bracket
			// if we did, bail out
			if (parentStack.size() == 0) {
				std::cout << "Unexpected ] encountered!  No matching [ to close." << std::endl;
				delete root;
				return nullptr;
			}
			break;
		default:
			// do nothing on unknown character
			break;
		}

		c = token_stream_->Get();
	}

	return root;
}

Parser::~Parser(void)
{
	delete token_stream_;
}
