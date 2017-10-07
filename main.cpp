#include <iostream>
#include <sstream>
#include <cstring>
#include "parser.h"
#include "programnode.h"
#include "programstate.h"

const int TAPE_SIZE = 30000;

void Usage(const char* executable_name)
{
	std::cout << "BrainFPP Interpreter" << std::endl;
	std::cout << "Usage: " << executable_name << " <options> <source file>" << std::endl << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "\t--tree-only\tPrint program tree instead of executing" << std::endl << std::endl;
}

int main(int argc, char* argv[])
{
	// ensure at least one argument is provided (at least the source file must be present)
	if (argc < 2) {
		Usage(argc > 0 ? argv[0] : "brainfpp");
		return -1;
	}
	
	// source file should be the last argument
	const char* source_file = argv[argc-1];
	
	// parse the flags, if present
	bool tree_only = false;
	for (int i = 1; i < argc-1; i++) {
		if (strcmp(argv[i], "--tree-only") == 0) {
			tree_only = true;
		} else {
			// unknown parameter
			Usage(argv[0]);
			std::cout << "Unknown option: " << argv[i] << std::endl;
			return -1;
		}
	}
	
	// parse the source file
	// this returns a pointer to a node created by NEW, so we better delete it later
	Parser parser(source_file);
	bool needs_input = false;
	const ProgramNode* program_root = parser.Parse(needs_input);

	// if parse was bad, bail out
	if (program_root == NULL) {
		std::cout << "Terminating due to parsing failure." << std::endl;
		return -2;
	}

	// dump ast, if requested
	if (tree_only) {
		program_root->DumpTree();
		return 0;
	}

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

