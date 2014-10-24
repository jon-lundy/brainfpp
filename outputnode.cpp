// Implementation of the OutputNode class, which represents
// an instruction to write the current character to stdout.

#include <string>
#include <iostream>
#include "outputnode.h"
#include "programstate.h"

OutputNode::OutputNode(AbstractNode* parent) : AbstractNode(parent)
{
}

const AbstractNode* OutputNode::Execute(ProgramState& state) const
{
	state.ostream() << state.Read();
	return next_sib_;
}

const std::string OutputNode::ToString() const
{
	return "(OutputNode)";
}

OutputNode::~OutputNode()
{
}
