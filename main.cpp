#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "abstractnode.h"
#include "datanode.h"
#include "inputnode.h"
#include "loopnode.h"
#include "outputnode.h"
#include "pointernode.h"
#include "programnode.h"
#include "programstate.h"

const int TAPE_SIZE = 30000;

void Usage(const char* executable_name)
{
	std::cout << "BrainFPP Interpreter" << std::endl;
	std::cout << "Usage: " << executable_name << " <source file>" << std::endl;
}

// Parses the program.  Note this allocates the tree, so you'll need to delete this pointer.
const ProgramNode* Parse(char* file_name, bool& needs_input)
{
	needs_input = false;

	// attempt to open source file
	std::ifstream src;
	src.open(file_name);
	if (!src.is_open()) {
		std::cout << "Failed to open " << file_name << ". Make sure the file exists and that the path is correct." << std::endl;
		return NULL;
	}

	// create root node
	ProgramNode* root = new ProgramNode(NULL);

	// create node stack, for loops
	std::vector<AbstractNode*> parentStack;
	parentStack.push_back(root);

	// begin reading program
	char c;
	src.get(c);

	// loop until the read fails
	while (src.good()) {
		// switch on input character
		switch (c) {
		case '>':
			new PointerNode(parentStack.back(), 1);
			break;
		case '<':
			new PointerNode(parentStack.back(), -1);
			break;
		case '+':
		case '-': {
				char increment = (c == '+' ? 1 : -1);
				int next = src.peek();
				while (next == '+' || next == '-') {
					src.get(c);
					increment += (c == '+' ? 1 : -1);
					next = src.peek();
				}
				new DataNode(parentStack.back(), increment, false);
				break;
		}
		case '.':
			new OutputNode(parentStack.back());
			break;
		case ',':
			new InputNode(parentStack.back());
			needs_input = true;
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

		src.get(c);
	}

	// cleanup
	src.close();

	return root;
}

int main(int argc, char* argv[])
{
	// ensure source file is specified
	if (argc < 2) {
		Usage(argc > 0 ? argv[0] : "brainfpp");
		return -1;
	}

	// parse the source file
	// this returns a pointer to a node created by NEW, so we better delete it later
	bool needs_input = false;
	const ProgramNode* program_root = Parse(argv[1], needs_input);

	// if parse was bad, bail out
	if (program_root == NULL) {
		std::cout << "Terminating due to parsing failure." << std::endl;
		return -2;
	}

	// dump ast
	program_root->DumpTree();

	// if we need input, grab it here:
	std::istringstream input_stream;
	if (needs_input) {
		std::cout << "Program " << argv[1] << " requires input." << std::endl;
		std::cout << "Type input below and press ENTER." << std::endl;

		std::string input;
		std::getline(std::cin, input);
		input_stream.str(input);
	}
	
	//execute
	ProgramState program_state(TAPE_SIZE, input_stream, std::cout);
	program_root->Execute(program_state);

	// cleanup AST
	delete program_root;

	// done!
	std::cout << std::endl;
	return 0;
}

