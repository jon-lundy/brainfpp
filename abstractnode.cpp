// Implementation of the AbstractNode class, which represents 
// any node in the AST.

#include <iostream>
#include "abstractnode.h"

AbstractNode::AbstractNode(AbstractNode* parent)
{
	first_child_ = last_child_ = next_sib_ = NULL;
	if (parent != NULL) {
		parent->AdoptChild(this);
	}
}

void AbstractNode::TreeDumpVisitor(const int current_num_indents) const
{
	for (int i = 0; i < current_num_indents; ++i) {
		std::cout << '\t';
	}
	std::cout << ToString() << std::endl;
	AbstractNode* child_visitor = first_child_;
	while (child_visitor != NULL) {
		child_visitor->TreeDumpVisitor(current_num_indents + 1);
		child_visitor = child_visitor->next_sib_;
	}
}

void AbstractNode::AdoptChild(AbstractNode* adoptee)
{
	if (first_child_ == NULL) {
		first_child_ = adoptee;
		last_child_ = adoptee;
	} else {
		last_child_->next_sib_ = adoptee;
		last_child_ = adoptee;
	}
}

AbstractNode::~AbstractNode()
{
	// each node deletes its first child, and then its next sibling
	// in this way, the entire tree is cleaned up
	if (first_child_ != NULL) {
		delete first_child_;
	}
	if (next_sib_ != NULL) {
		delete next_sib_;
	}
}
