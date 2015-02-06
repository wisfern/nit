#include <StringUtils.h>
#include <stdio.h>
#include <string>
#include <iostream>

__USING_NIT_NS
__USING_STD_NS

int main(void)
{
	string demo = "|My|name||is||xzf|xzf!||";
	cout << "Before deal : |" << demo <<  "|" << endl;
	cout << "toupper : |" << StringUtils::toUpper(demo) <<  "|" << endl;
	cout << "tolower : |" << StringUtils::toLower(demo) <<  "|" << endl;
	cout << "ltrim : |" << StringUtils::ltrim(demo) <<  "|" << endl;
	cout << "rtrim : |" << StringUtils::rtrim(demo) <<  "|" << endl;
	cout << "trim : |" << StringUtils::trim(demo) <<  "|" << endl;
	cout << "replace : |" << StringUtils::replace(demo, 13, 3, "demo") <<  "|" << endl;
	cout << "replace : |" << StringUtils::replace(demo, 16, "xzf", "demo") <<  "|" << endl;
	cout << "equalNoCase : |" << StringUtils::equalNoCase(demo, "  My name is xzf!  ") <<  "|" << endl;
	cout << "compareNoCase : |" << StringUtils::compareNoCase(demo, "  My name is xzf!  ") <<  "|" << endl;
	string temp = StringUtils::format("%s", "  My name is xzf!  ");
	cout << "format : |" << temp <<  "|" << endl;
	cout << "left : |" << StringUtils::left(demo, 5) <<  "|" << endl;
	cout << "mid : |" << StringUtils::mid(demo, 5, 5) <<  "|" << endl;
	cout << "right : |" << StringUtils::right(demo, 5) <<  "|" << endl;
		
	vector<string> value = StringUtils::parseTokens(demo, "|");
	cout << "after pasre : " << endl;
	for(vector<string>::iterator it=value.begin();
		it != value.end(); ++it)
	{
		cout << *it << endl;
	}
	return 0;
}
