
#include "precompiledHeaders.h"
#include "Notepad_plus_Window.h"

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Notepad_plus.h"

class Notepad_plus_for_test : public Notepad_plus
{
	virtual HWND getMainWindowHandle() {
		return NULL;
	}
};

class MockedFileManager : public FileManager
{
	virtual BufferID loadFile(const TCHAR * filename, Document doc = NULL, int encoding = -1)
	{
		mock().actualCall("FileManager::loadFile").withParameter("filename", filename).withParameter("Document", &doc).withParameter("encoding", encoding);
		return BUFFER_INVALID;
	}
};

TEST_GROUP(NPPIO)
{
};

TEST(NPPIO, fileToBeOpenedIsASessionFile)
{
	MockedFileManager mockedFileManager;
	FileManager* originalFileManager = FileManager::setInstance(&mockedFileManager);

	mock().setData("GetFullPathNameA_filename", "c:\\sessions\\file.session");
	mock().setData("GetLongPathNameA_filename", "c:\\sessions\\file.session");
	mock().expectOneCall("GetFullPathNameA").withParameter("lpFileName", "file.session").ignoreOtherParameters();
	mock().expectOneCall("GetLongPathNameA").withParameter("lpszShortPath", "c:\\sessions\\file.session").ignoreOtherParameters();
	mock().expectOneCall("GetFullPathNameA").withParameter("lpFileName", "c:\\sessions\\file.session").ignoreOtherParameters();
	mock().expectOneCall("GetLongPathNameA").withParameter("lpszShortPath", "c:\\sessions\\file.session").ignoreOtherParameters();
	mock().expectOneCall("PathFileExistsA").withParameter("filename", "c:\\sessions\\file.session").andReturnValue((int) true);
	mock().expectOneCall("PathFileExistsA").withParameter("filename", "c:\\sessions\\file.session").andReturnValue((int) true);
	Notepad_plus_for_test notepad;
	notepad.doOpen("file.session", false, 10);

	FileManager::setInstance(originalFileManager);
}
