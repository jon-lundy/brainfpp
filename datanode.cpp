// Implementation of the DataNode class, which represents
// an instruction modify the data on tape where the pointer is.

#include <string>
#include <sstream>
#include "datanode.h"
#include "programstate.h"

DataNode::DataNode(AbstractNode* parent, const char data_step, const bool overwrites) : 
		AbstractNode(parent), 
		step_(data_step), 
		overwrite_(overwrites)
{
}

const AbstractNode* DataNode::Execute(ProgramState& state) const
{
	if (overwrite_) {
		state.Set(step_);
	} else {
		state.Change(step_);
	}
	return next_sib_;
}

const std::string DataNode::ToString() const
{
	std::stringstream ss;
	ss << "(DataNode step=" << static_cast<int>(step_) << " overwrite=" << overwrite_ << ")";
	return ss.str();
}

DataNode::~DataNode()
{
}
