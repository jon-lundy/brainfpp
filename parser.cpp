#include <fstream>
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

Parser::Parser(const char* file_name) : 
			file_name_(file_name),
			source_stream_()
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
	int next = source_stream_.peek();
	while (next == increment_op || next == decrement_op) {
		source_stream_.get();
		total_diff += (next == increment_op ? 1 : -1);
		next = source_stream_.peek();
	}
	return total_diff;
}

// Parses the program.  Note this allocates the tree, so you'll need to delete this pointer.
const ProgramNode* Parser::Parse(bool& program_requires_input)
{
	program_requires_input = false;

	// attempt to open source file
	source_stream_.open(file_name_);
	if (!source_stream_.is_open()) {
		std::cout << "Failed to open " << file_name_ << ". Make sure the file exists and that the path is correct." << std::endl;
		return NULL;
	}

	// create root node
	ProgramNode* root = new ProgramNode(NULL);

	// create node stack, for loops
	std::vector<AbstractNode*> parentStack;
	parentStack.push_back(root);

	// begin reading program
	char c;
	source_stream_.get(c);

	// loop until the read fails
	while (source_stream_.good()) {
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
				return NULL;
			}
			break;
		default:
			// do nothing on unknown character
			break;
		}

		source_stream_.get(c);
	}

	// cleanup
	source_stream_.close();

	return root;
}

Parser::~Parser(void)
{
}
