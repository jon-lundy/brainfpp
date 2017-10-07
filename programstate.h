// Declaration of the ProgramState class, which represents 
// the data tape and data pointer.

#ifndef PROGRAMSTATE_H
#define PROGRAMSTATE_H
#include <iostream>
#include "noncopyable.h"

class ProgramState : NonCopyable<ProgramState>
{
private:
	const unsigned int length_;	//number of cells on tape
	const char* start_;		//first cell in tape
	const char* end_;		//just past last cell in tape
	char* current_;			//current cell
	std::istream& istream_;		//read data to here
	std::ostream& ostream_;		//write data to here
public:
	ProgramState(const unsigned int tape_length, std::istream& in, std::ostream& out);
	void Move(const int displacement);
	char Read() const;
	void Set(const char in);
	void Change(const char diff);
	inline std::istream& istream() { return istream_; }
	inline std::ostream& ostream() { return ostream_; }
	~ProgramState();
};

#endif
