// Definition of the InputNode class, which represents
// an instruction to read a character from stdin.

#ifndef INPUTNODE_H
#define INPUTNODE_H
#include <string>
#include "abstractnode.h"
#include "programstate.h"

class InputNode :
	public AbstractNode
{
private:
	const InputNode& operator=(const InputNode&);		// no assignment allowed
protected:
	const std::string ToString() const;
public:
	InputNode(AbstractNode* parent);
	const AbstractNode* Execute(ProgramState& state) const;
	~InputNode();
};

#endif
