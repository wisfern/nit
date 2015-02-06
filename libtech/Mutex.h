/*
 *@author wisfern
 */
#ifndef NIT_BASE_MUTEX_H
#define NIT_BASE_MUTEX_H

#include <noncopyable.h>
#include <assert.h>

__NIT_NAMESPACE_BEGIN

class NIT_API Mutex : public noncopyable
{
public:
	/* @param name ����������֣�����
	 */
	Mutex(const char* name = NULL);
	virtual ~Mutex();
	
	void enterMutex();
	void leaveMutex();
	
	/*@return ���Ի�ȡ���ɹ�����true������false
	 *@see enterMutex
	 *@see leaveMutex
	 */
	bool tryEnterMutex();
	
	inline void lock()
	{ enterMutex(); }
	
	inline void unlock()
	{ leaveMutex(); }
	
	/*@see #tryEnterMutex
	 */
	inline bool trylock()
	{ return tryEnterMutex(); }
	
	/* @param name ����������� 
	 */
	inline void setMutexName(const char* name)
	{ _name = (char *)name; }
	
	/*��ȡ��ʵ�Ļ�����
	 *@return pthread_mutex_t���͵�ָ��
	 */
	inline MUTEX* getMutex()
	{ return &_mutex; }
	
private:
	MUTEX _mutex;
	char* _name;
};

class NIT_API MutexGuard : public noncopyable
{
public:
	explicit MutexGuard(Mutex &mutex) : _mutex(mutex)	
	{ _mutex.enterMutex(); }
	
	virtual ~MutexGuard()
	{
		_mutex.leaveMutex();
	}
	
private:
	Mutex& _mutex;
};

__NIT_NAMESPACE_END

// Prevent misuse like:
// MutexLockGuard(mutex_);
// A tempory object doesn't hold the lock for long!
#define MutexLockGuard(x) error "Missing guard object name"

#endif /* #ifndef NIT_BASE_MUTEX_H */
