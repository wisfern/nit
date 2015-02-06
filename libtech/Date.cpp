#include <stdio.h>  // snprintf
#include <string.h> // memcpy
#include <stdlib.h> // atoi
#include <Date.h>

__USING_NIT_NS

Date::Date()
{
	time_t now = time(NULL);
	struct tm local;
	memcpy(&local, localtime(&now), sizeof(struct tm));
	_julian= toJulian(local.tm_year+1900, local.tm_mon+1, local.tm_mday);
}

Date::Date(int y, int m, int d)
  : _julian(toJulian(y, m, d))
{
}

Date::Date(const struct tm& t)
  : _julian(toJulian(t.tm_year+1900, t.tm_mon+1, t.tm_mday))
{
}

Date::Date(const time_t& t)
{
	struct tm local;
	memcpy(&local, localtime(&t), sizeof(struct tm));
	_julian= toJulian(local.tm_year+1900, local.tm_mon+1, local.tm_mday);
}

unsigned Date::getYear(void) const
{
	char buffer[11];
	fromJulian(buffer);
	return atoi(buffer);
}

unsigned Date::getMonth(void) const
{
	char buffer[11];
	fromJulian(buffer);
	return atoi(buffer+5);
}

unsigned Date::getDay(void) const
{
	char buffer[11];
	fromJulian(buffer);
	return atoi(buffer+8);
}

unsigned Date::getDayOfWeek(void) const
{
	return (unsigned)((_julian + 1l) % 7l);
}

string Date::toString() const
{
	return fromJulian();
}

// algorithm and explanation see:
// http://www.faqs.org/faqs/calendars/faq/part2/
// http://blog.csdn.net/Solstice
int Date::toJulian(int year, int month, int day)
{
	int a = (14 - month) / 12;
	int y = year + 4800 - a;
	int m = month + 12 * a - 3;
	return day + (153*m + 2) / 5 + y*365 + y/4 - y/100 + y/400 - 32045;
}

string Date::fromJulian() const
{
	return fromJulian(_julian);
}

void Date::fromJulian(char *buffer) const
{
	fromJulian(_julian, buffer);
}

string Date::fromJulian(const int julian)
{
	char buffer[11];
	fromJulian(julian, buffer);
	
	return buffer;
}

void Date::fromJulian(const int julian, char *buffer)
{
	int a = julian + 32044;
	int b = (4 * a + 3) / 146097;
	int c = a - ((b * 146097) / 4);
	int d = (4 * c + 3) / 1461;
	int e = c - ((1461 * d) / 4);
	int m = (5 * e + 2) / 153;
	
	int day = e - ((153 * m + 2) / 5) + 1;
	int month = m + 3 - 12 * (m / 10);
	int year = b * 100 + d - 4800 + (m / 10);
	
	if (buffer)
		snprintf(buffer, 11, "%04d-%02d-%02d", year, month, day);
}
