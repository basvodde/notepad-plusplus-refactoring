
#include "precompiledHeaders.h"
#include "Notepad_plus_Window.h"

#include "CppUTest/TestHarness.h"
#include "Notepad_plus.h"

TEST_GROUP(NPPIO)
{
};

TEST(NPPIO, fail)
{
	Notepad_plus notepad;
	notepad.doOpen("file.cpp", true, 0);
}
