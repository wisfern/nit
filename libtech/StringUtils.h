/*
 *@author wisfern
 */
#ifndef NIT_BASE_STRINGUTILS_H
#define NIT_BASE_STRINGUTILS_H

#include <copyable.h>
#include <libdefs.h>
#include <assert.h>
#include <vector>

__NIT_NAMESPACE_BEGIN

class NIT_API StringUtils : public copyable
{
public:
	static string toUpper(const string& __s);
	static string toLower(const string& __s);
	
	static string ltrim(const string& __s);
	static string rtrim(const string& __s);
	static string trim(const string& __s);
	
	static string replace(const string& __s, size_t _pos, size_t _len, const string& _goal);
	static string replace(const string& __s, size_t _pos, const string& _src, const string& _goal);
	
	static bool equalNoCase(const string& __s1, const string& __s2);
	static int compareNoCase(const string& __s1, const string& __s2);
	
	static string format(const char* fmt, ...);
	
	static string left(const string& __s,int len);
	static string mid(const string& __s,int from,int len=-1);
	static string right(const string& __s,int len);
	
	static int parseTokens(std::vector<string>& _dest, const string& _str, const string& delim=" \t\n\r\f");
	static int parseTokens(std::vector<string>& _dest, const string& _str, const char delim);
	static std::vector<string> parseTokens(const string& _str, const string& delim=" \t\n\r\f");
};

__NIT_NAMESPACE_END

#endif /* #ifndef NIT_BASE_STRINGUTILS_H */
