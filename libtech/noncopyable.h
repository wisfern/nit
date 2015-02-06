#ifndef NIT_BASE_NONCOPYABLE_H
#define NIT_BASE_NONCOPYABLE_H

#include <libdefs.h>

__NIT_NAMESPACE_BEGIN

class NIT_API noncopyable
{
public:
	noncopyable() {}
	virtual ~noncopyable() {}
	
private:
	noncopyable(const noncopyable&);
	noncopyable operator=(const noncopyable&);		
};

__NIT_NAMESPACE_END

#endif /* #ifndef NIT_BASE_NONCOPYABLE_H */
