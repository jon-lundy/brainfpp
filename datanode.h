// Definition of the DataNode class, which represents
// an instruction to modify the data on tape where the pointer is.

#ifndef DATANODE_H
#define DATANODE_H
#include <string>
#include "abstractnode.h"
#include "programstate.h"

class DataNode :
	public AbstractNode
{
private:
	const bool overwrite_;
	const char step_;
	const DataNode& operator=(const DataNode&);		// no assignment allowed
protected:
	const std::string ToString() const;
public:
	DataNode(AbstractNode* parent, const char data_step, const bool overwrites);
	const AbstractNode* Execute(ProgramState& state) const;
	~DataNode();
};

#endif
