
#include <windows.h>
#include <stdio.h>

#include "CppUTest/CommandLineTestRunner.h"

extern bool app_started;

int main(int ac, char** av)
{
	app_started = true;
	CommandLineTestRunner::RunAllTests(ac, av);
	return 0;
}
