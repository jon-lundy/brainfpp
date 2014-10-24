// Implementation of the PointerNode class, which represents
// an instruction to move the tape pointer.

#include <string>
#include <sstream>
#include "pointernode.h"
#include "programstate.h"

PointerNode::PointerNode(AbstractNode* parent, const int pointer_step) : AbstractNode(parent), step_(pointer_step)
{
}

const AbstractNode* PointerNode::Execute(ProgramState& state) const
{
	state.Move(step_);
	return next_sib_;
}

const std::string PointerNode::ToString() const
{
	std::stringstream ss;
	ss << "(PointerNode step=" << step_ << ")";
	return ss.str();
}

PointerNode::~PointerNode()
{
}
