// Definition of the OutputNode class, which represents
// an instruction to write the current character to stdout.

#ifndef OUTPUTNODE_H
#define OUTPUTNODE_H
#include <string>
#include "abstractnode.h"
#include "programstate.h"

class OutputNode :
	public AbstractNode
{
private:
	const OutputNode& operator=(const OutputNode&);		// no assignment allowed
protected:
	const std::string ToString() const;
public:
	OutputNode(AbstractNode* parent);
	const AbstractNode* Execute(ProgramState& state) const;
	~OutputNode();
};

#endif
