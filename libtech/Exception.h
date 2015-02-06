
#ifndef NIT_BASE_EXCEPTION_H
#define NIT_BASE_EXCEPTION_H

#include <exception>
#include <libdefs.h>

__NIT_NAMESPACE_BEGIN

class NIT_API BaseException : public std::exception
{
public:
	explicit BaseException(const char* what);
	explicit BaseException(const string& what);
	virtual ~BaseException() throw();
	virtual const char* what() const throw();
	const char* stack() const throw();

private:
	void fillStack();

	std::string message_;
	std::string stack_;
};

__NIT_NAMESPACE_END

#endif  // NIT_BASE_EXCEPTION_H
