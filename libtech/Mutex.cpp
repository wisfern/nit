
#include <Mutex.h>

__USING_NIT_NS

Mutex::Mutex(const char* name /*=NULL*/)
{
	MUTEXINIT(&_mutex);
	_name = (char *)name;
}

Mutex::~Mutex()
{
	MUTEXDESTROY(&_mutex);
}

void Mutex::enterMutex()
{
	MUTEXLOCK(&_mutex);
}

void Mutex::leaveMutex()
{
	MUTEXUNLOCK(&_mutex);
}

bool Mutex::tryEnterMutex()
{
	return (MUTEXTRYLOCK(&_mutex) == 0) ? true : false;
}
