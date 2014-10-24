// Definition of the PointerNode class, which represents
// an instruction to move the tape pointer.

#ifndef POINTERNODE_H
#define POINTERNODE_H
#include <string>
#include "abstractnode.h"
#include "programstate.h"

class PointerNode :
	public AbstractNode
{
private:
	const int step_;
	const PointerNode& operator=(const PointerNode&);		// no assignment allowed
protected:
	const std::string ToString() const;
public:
	PointerNode(AbstractNode* parent, const int pointer_step);
	const AbstractNode* Execute(ProgramState& state) const;
	~PointerNode();
};

#endif
