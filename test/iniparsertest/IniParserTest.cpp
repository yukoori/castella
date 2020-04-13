#include <stdio.h>

#include "SCIniParser.h"

int main(int argc, char* argv[])
{
	SCIniParser ini;
	int ret = ini.load(SCTEXT("./test.ini"));
	if (ret != 0)
	{
		return -1;
	}

	ini.print();

	SCString data1 = SCTEXT("TEST VALUE1");
	ini.setString(SCTEXT("NEW SESSION"), SCTEXT("TEST KEY1"), data1);
	SCString data2 = SCTEXT("TEST VALUE2");
	ini.setString(SCTEXT("NEW SESSION"), SCTEXT("TEST KEY2"), data2);
	ini.setString(SCTEXT("NEW SESSION"), SCTEXT("TEST KEY1"), data2);

	ini.save(SCTEXT("./test1.ini"));

	return 0;
}
