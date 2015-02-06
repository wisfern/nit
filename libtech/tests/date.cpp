#include <Date.h>
#include <stdio.h>

__USING_NIT_NS

int main(void)
{
	Date time;
	printf("julian=%ld\n", time.getJulian());
	printf("当前日期：%s\n", time.toString().c_str());
	printf("当前日期：%d-%d-%d\n", time.getYear(), time.getMonth(), time.getDay());
	printf("为一周中的第%d天\n", time.getDayOfWeek());
	return 0;
}
