// Definition of the LoopNode class, which represents
// a full loop in the source code.

#ifndef LOOPNODE_H
#define LOOPNODE_H
#include <string>
#include "abstractnode.h"
#include "programstate.h"

class LoopNode :
	public AbstractNode
{
protected:
	const std::string ToString() const;
public:
	LoopNode(AbstractNode* parent);
	const AbstractNode* Execute(ProgramState& state) const;
	~LoopNode();
};

#endif
