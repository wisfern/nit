#include <StringUtils.h>
#include <cctype>				// need tolower() toupper()
#include <stdarg.h>				// need va_arg
#include <stdio.h>
//#include <strings.h>			// need strcasecmp()
#include <algorithm>

__USING_NIT_NS
__USING_STD_NS

/* 因为toupper、tolower命名有多个实现，所以特别指定形式 */
string StringUtils::toUpper(const string& __s)
{
	string dest;
	transform(__s.begin(), __s.end(), 
		insert_iterator<string>(dest, dest.begin()), (int(*)(int))toupper);
	return dest;
}

string StringUtils::toLower(const string& __s)
{
	string dest;
	transform(__s.begin(), __s.end(), 
		insert_iterator<string>(dest, dest.begin()), (int(*)(int))tolower);
	return dest;
}

string StringUtils::ltrim(const string& __s)
{
	string::size_type pos = __s.find_first_not_of(' ');
	if (pos == string::npos)
	{
		return string();		
	}
	return __s.substr(pos);
}

string StringUtils::rtrim(const string& __s)
{
	string::size_type pos = __s.find_last_not_of(' ');
	if (pos == string::npos)
	{
		return string();
	}
	return __s.substr(0, pos+1);
}

string StringUtils::trim(const string& __s)
{
	string::size_type pos = __s.find_first_not_of(' ');
	if (pos == string::npos)
	{
		return string();
	}
	
	string::size_type len = __s.find_last_not_of(' ') - pos +1;
	return __s.substr(pos, len);
}

string StringUtils::replace(const string& __s, size_t _pos, size_t _len, const string& _goal)
{
	string dest = __s;
	dest.replace(_pos, _len, _goal);
	return dest;
}

string StringUtils::replace(const string& __s, size_t _pos, const string& _src, const string& _goal)
{
	string dest = __s;
	string::size_type idx = _pos;
	while( (idx=dest.find(_src, idx)) != string::npos)
	{
		dest.replace(idx, _src.length(), _goal);
	}
	
	return dest;
}

bool StringUtils::equalNoCase(const string& __s1, const string& __s2)
{
	return toLower(__s1) == toLower(__s2);
}

int StringUtils::compareNoCase(const string& __s1, const string& __s2)
{
	return stricmp(__s1.c_str(), __s2.c_str());
}

string StringUtils::format(const char* fmt, ...)
{
	va_list ap;
	char* szBuf = NULL;
	int n = 0;
	int size = 1024;
	
	if ( (szBuf=(char *)malloc(size)) == NULL)
	{
		return string();
	}
	
	while(true)
	{
		va_start(ap, fmt);
		n = vsnprintf(szBuf, size, fmt, ap);
		va_end(ap);
		
		if(n > -1 && n < size)
	    {
	      return string(szBuf, n);
	    }
	    
	    /* vsnprintf调用失败(n<0)或者p的空间不足够容纳size大小的字符串(n>=size)，尝试申请更大的空间*/ 
	    size *= 2;
	    if( (szBuf=(char *)realloc(szBuf, size)) == NULL)
	    {
	    	return string();
	    }
	}
	
	return string();
}

string StringUtils::left(const string& __s,int len)
{
	return __s.substr(0, len);
}

string StringUtils::mid(const string& __s,int from,int len/*=-1*/)
{
	return __s.substr(from, len);
}

string StringUtils::right(const string& __s,int len)
{
	return __s.substr(__s.length() - len);
}

int StringUtils::parseTokens(vector<string>& _dest, const string& _str, const string& delim/*=" \t\n\r\f"*/)
{
	string::size_type head = 0;
	string::size_type end = 0;
	string::size_type len = 0;
	while(head < _str.length())
	{
		if( (end=_str.find_first_of(delim, end)) != string::npos)
		{
			len = end - head;
			_dest.push_back(_str.substr(head, len));
			head = ++end;
		}
		else
		{
			_dest.push_back(_str.substr(head));
			head = _str.length();
		}
	}
	
	return _dest.size();
}

int StringUtils::parseTokens(vector<string>& _dest, const string& _str, const char delim)
{
    char *st1 = NULL;
    char *st2 = NULL;
    char tempbuf_[1024];
    
    strcpy( tempbuf_, _str.c_str() );
    if( tempbuf_[strlen(tempbuf_)-1] == '\n' )
        tempbuf_[strlen(tempbuf_)-1] = 0;
      
    _dest.clear();
    st1 = tempbuf_;
    while( ( st2 = strchr(st1,delim) ) != NULL )
    {
      *st2 = 0;
      _dest.push_back( string(st1) );
      *st2 = delim;
      st1 = st2 + 1;
    }
    if( *st1 != 0 )  _dest.push_back( string(st1) );
    
    return _dest.size();
}

vector<string> StringUtils::parseTokens(const string& _str, const string& delim/*=" \t\n\r\f"*/)
{
	vector<string> values;
	parseTokens(values,_str,delim);
	return values;
}
