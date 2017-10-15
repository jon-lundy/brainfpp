// Implementation of the LoopNode class, which represents
// a full loop in the source code.

#include <string>
#include "loopnode.h"
#include "programstate.h"

LoopNode::LoopNode(AbstractNode* parent) : AbstractNode(parent)
{
}

const AbstractNode* LoopNode::Execute(ProgramState& state) const
{
	while (state.Read() != 0) {
		const AbstractNode* next_loop_step = first_child_;
		while (next_loop_step != nullptr) {
			next_loop_step = next_loop_step->Execute(state);
		}
	}
	return next_sib_;
}

const std::string LoopNode::ToString() const
{
	return "(LoopNode)";
}

LoopNode::~LoopNode(void)
{
}
