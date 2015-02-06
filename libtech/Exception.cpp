
#include <Exception.h>
#include <stdlib.h>

#ifdef OS_LINUX
# include <execinfo.h>	// backtrace类函数需要
#endif

__USING_NIT_NS

BaseException::BaseException(const char* msg)
  : message_(msg)
{
	fillStack();
}

BaseException::BaseException(const string& msg)
  : message_(msg)
{
	fillStack();
}

BaseException::~BaseException() throw ()
{
}

const char* BaseException::what() const throw()
{
  return message_.c_str();
}

const char* BaseException::stack() const throw()
{
  return stack_.c_str();
}

void BaseException::fillStack()
{
#ifdef OS_LINUX
  const int len = 200;
  void* buffer[len];
  int nptrs = ::backtrace(buffer, len);
  char** strings = ::backtrace_symbols(buffer, nptrs);
  if (strings)
  {
    for (int i = 0; i < nptrs; ++i)
    {
      stack_.append(strings[i]);
      stack_.push_back('\n');
    }
    //need to free the menory of backtrace_symbols
    free(strings);
  }
#endif
}
