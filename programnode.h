// Definition of the ProgramNode class, which is the root of the AST.

#ifndef PROGRAMNODE_H
#define PROGRAMNODE_H
#include <string>
#include "abstractnode.h"
#include "programstate.h"

class ProgramNode :
	public AbstractNode
{
protected:
	const std::string ToString() const;
public:
	explicit ProgramNode(); // doesn't take a parent, because ProgramNode is always the root
	const AbstractNode* Execute(ProgramState& state) const;
	void DumpTree() const;
	~ProgramNode();
};

#endif
