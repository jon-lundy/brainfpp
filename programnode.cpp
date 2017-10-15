// Implementation of the ProgramNode class, which is the root of the AST.

#include <string>
#include "programnode.h"
#include "programstate.h"

ProgramNode::ProgramNode() : AbstractNode(nullptr)
{
}

const AbstractNode* ProgramNode::Execute(ProgramState& state) const
{
	const AbstractNode* next_step = first_child_;
	while (next_step != nullptr) {
		next_step = next_step->Execute(state);
	}
	return nullptr;
}

const std::string ProgramNode::ToString() const
{
	return "(ProgramNode)";
}

void ProgramNode::DumpTree() const
{
	TreeDumpVisitor(0);
}

ProgramNode::~ProgramNode()
{
}
