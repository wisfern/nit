#include <Date.h>
#include <stdio.h>

__USING_NIT_NS

int main(void)
{
	Date time;
	printf("julian=%ld\n", time.getJulian());
	printf("��ǰ���ڣ�%s\n", time.toString().c_str());
	printf("��ǰ���ڣ�%d-%d-%d\n", time.getYear(), time.getMonth(), time.getDay());
	printf("Ϊһ���еĵ�%d��\n", time.getDayOfWeek());
	return 0;
}
