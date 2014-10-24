// Implementation of the InputNode class, which represents
// an instruction to read a character from stdin.

#include <string>
#include <iostream>
#include "inputnode.h"
#include "programstate.h"

InputNode::InputNode(AbstractNode* parent) : AbstractNode(parent)
{
}

const AbstractNode* InputNode::Execute(ProgramState& state) const
{
	char c;
	state.istream().get(c);
	// on EOF or error, the value at the pointer is unchanged
	if (state.istream()) {
		state.Set(c);
	}
	return next_sib_;
}

const std::string InputNode::ToString() const
{
	return "(InputNode)";
}


InputNode::~InputNode()
{
}
