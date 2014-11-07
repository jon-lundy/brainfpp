#include <fstream>
#include "tokenstream.h"

TokenStream::TokenStream(const char* file_name) :
				next_token_(0),
				source_stream_(),
				finished_(false)
{
	source_stream_.open(file_name);
	AdvanceStream();
}

char TokenStream::Peek() const
{
	return next_token_;
}

char TokenStream::Get()
{
	char ret_val = next_token_;
	
	// if we haven't reached the end of the stream, then keep going
	if (source_stream_.good()) {
		AdvanceStream();
	} else {
	// if we have reached the end, then ret_val is bad, and Good should return false
		finished_ = true;
	}
	return ret_val;
}

bool TokenStream::Good() const
{
	return !finished_;
}

bool TokenStream::IsOpen() const
{
	return source_stream_.is_open();
}

void TokenStream::AdvanceStream()
{
	// advance one char
	char c;
	source_stream_.get(c);
	
	// get next token and store it, or reach EOF
	while (source_stream_.good()) {
		// 43-46 coorespond to + , - .
		if ((c >= 43 && c <= 46) || c == '>' || c == '<' || c == '[' || c == ']') {
			next_token_ = c;
			break;
		}
		source_stream_.get(c);
	}
	
	// if EOF reached, set next to 0
	if (!source_stream_.good()) {
		next_token_ = 0;
	}

	return;
}

TokenStream::~TokenStream()
{
	source_stream_.close();
}
