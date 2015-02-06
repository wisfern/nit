#ifndef NIT_BASE_DATE_H
#define NIT_BASE_DATE_H

#include <copyable.h>
#include <time.h>
#include <string>

__NIT_NAMESPACE_BEGIN

/*
 *@detail Julian Calendar Class
 */
class NIT_API Date : public copyable
{
public:
	/*
	 *以系统当前的日期初始化
	 */
	Date();
	Date(int year, int month, int day);
	explicit Date(int julian)
		: _julian(julian) {}
	explicit Date(const struct tm& t);
	explicit Date(const time_t& t);
	virtual ~Date() {}
	
	unsigned getYear(void) const;
	unsigned getMonth(void) const;
	unsigned getDay(void) const;
	unsigned getDayOfWeek(void) const;
	
	time_t getDate(tm& dt) const;
	/*
	 *以format格式输出日期，格式说明见strftime
	 */
	string getDate(const string& format) const;
	/*
	 *以YYYY-MON-DD格式输出日期
	 */
	string toString() const;
	
	inline long getJulian() const
	{	return _julian;	}
	
	string fromJulian() const;
	void fromJulian(char *buffer) const;
	
	static int toJulian(int year, int month, int day);
	static string fromJulian(const int julian);
	static void fromJulian(const int julian, char *buffer);
	
	inline int getJulianNum()
	{ return _julian; }
	inline void setJulianNum(long julian)
	{ _julian = julian; }
	
protected:
	long _julian;
};

inline bool operator>(Date x, Date y)
{
  return x.getJulianNum() > y.getJulianNum();
}

inline bool operator<(Date x, Date y)
{
  return x.getJulianNum() < y.getJulianNum();
}

inline bool operator==(Date x, Date y)
{
  return x.getJulianNum() == y.getJulianNum();
}

__NIT_NAMESPACE_END

#endif  // NIT_BASE_DATE_H
