// The TokenStream class is a flimsy wrapper around an ifstream
// that ignores all characters that aren't valid BF.

#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H

#include <fstream>
#include "noncopyable.h"

class TokenStream : NonCopyable<TokenStream>
{
private:
	void AdvanceStream();
	char next_token_;
	bool finished_;
	std::ifstream source_stream_;
public:
	TokenStream(const char* file_name);
	char Peek() const;
	char Get();
	bool Good() const;
	bool IsOpen() const;
	~TokenStream();
};

#endif
