// Declaration of the AbstractNode class, which represents 
// any node in the AST.

#ifndef ABSTRACTNODE_H
#define ABSTRACTNODE_H
#include <string>
#include <iostream>
#include "programstate.h"

class AbstractNode
{
private:
	void AdoptChild(AbstractNode* adoptee);
	const AbstractNode& operator=(const AbstractNode&);		// no assignment allowed
protected:
	AbstractNode* next_sib_;
	AbstractNode* first_child_;
	AbstractNode* last_child_;
	virtual const std::string ToString() const = 0;
	void TreeDumpVisitor(const int current_num_indents) const;
public:
	AbstractNode(AbstractNode* parent);
	virtual const AbstractNode* Execute(ProgramState& state) const = 0;
	virtual ~AbstractNode();
};

#endif
