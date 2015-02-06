#include <Digest.h>
#include <iostream>

__USING_NIT_NS
__USING_STD_NS

void strncpyTest()
{
	char buff1[8];
	for(int i=0; i<8; i++) buff1[i] = '#';
	buff1[7] = '\0';
	char buff2[18];
	for(int i=0; i<18; i++) buff2[i] = '-';
	buff2[17] = '\0';
	cout << "buff1 = " << buff1 << endl;
	cout << "buff2 = " << buff2 << endl;
	strncpy(buff2, buff1, 7);
	cout << "after strcpy" << endl;
	cout << "buff1 = " << buff1 << endl;
	cout << "buff2 = " << buff2 << endl;
}

int main(void)
{
	cout << "MD5(\"\") = " << getMD5("") << endl;
	cout << "MD5(\"a\") = " << getMD5("a") << endl;
	cout << "MD5(\"abc\") = " << getMD5("abc") << endl;
	cout << "MD5(\"message digest\") = " << getMD5("message digest") << endl;
	cout << "MD5(\"abcdefghijklmnopqrstuvwxyz\") = " << getMD5("abcdefghijklmnopqrstuvwxyz") << endl;
	cout << "MD5(\"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\") = " << getMD5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") << endl;
	cout << "MD5(\"12345678901234567890123456789012345678901234567890123456789012345678901234567890\") = " << getMD5("12345678901234567890123456789012345678901234567890123456789012345678901234567890") << endl;
	
	strncpyTest();

	return 0;
}
