// Definition of the ProgramNode class, which is the root of the AST.

#ifndef PROGRAMNODE_H
#define PROGRAMNODE_H
#include <string>
#include "abstractnode.h"
#include "programstate.h"

class ProgramNode :
	public AbstractNode
{
private:
	const ProgramNode& operator=(const ProgramNode&);		// no assignment allowed
protected:
	const std::string ToString() const;
public:
	ProgramNode(AbstractNode* parent);
	const AbstractNode* Execute(ProgramState& state) const;
	void DumpTree() const;
	~ProgramNode();
};

#endif
