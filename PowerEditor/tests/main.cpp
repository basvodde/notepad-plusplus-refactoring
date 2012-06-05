
#include <windows.h>
#include <stdio.h>

#include "CppUTest/TestRegistry.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTestExt/MockSupportPlugin.h"

extern bool app_started;

int main(int ac, char** av)
{
	MockSupportPlugin mockPlugin;
	TestRegistry::getCurrentRegistry()->installPlugin(&mockPlugin);
	app_started = true;
	CommandLineTestRunner::RunAllTests(ac, av);
	return 0;
}
