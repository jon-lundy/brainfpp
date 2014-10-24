// Implementation of the ProgramState class, which represents 
// the data tape and data pointer.

#include <iostream>
#include "programstate.h"

ProgramState::ProgramState(const unsigned int tape_length, std::istream& in, std::ostream& out) : 
			length_(tape_length), 
			start_(new char[length_]()), 
			end_(start_ + length_), 
			current_(const_cast<char*>(start_)),
			istream_(in),
			ostream_(out)
{}

// Move the current pointer.  If goes beyond the start or end, wrap around.
void ProgramState::Move(const int displacement) 
{
	current_ += displacement;
	while (current_ < start_) {
		current_ += length_;
	}
	while (current_ >= end_) {
		current_ -= length_;
	}
}

// Return value at pointer.
char ProgramState::Read() const 
{
	return *current_;
}

// Overwrite the value at the pointer.
void ProgramState::Set(const char in)
{
	*current_ = in;
}

// Increment the value at the pointer by the provided value.
void ProgramState::Change(const char diff) 
{
	*current_ += diff;
}

ProgramState::~ProgramState()
{
	delete start_;
}
