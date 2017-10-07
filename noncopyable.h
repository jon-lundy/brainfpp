// Mixin class for making classes non-copyable.
// I know there's a boost version, but requiring boost for just this seems... overkill.

#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

template <class T>
class NonCopyable
{
protected:
	NonCopyable() {}
	~NonCopyable() {}
private:
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator =(const NonCopyable&) = delete;
};

#endif