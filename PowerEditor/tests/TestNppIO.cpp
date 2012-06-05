
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

	virtual void loadBufferIntoView(BufferID id, int whichOne, bool dontClose = false) {
		mock().actualCall("Notepad_plus::loadBufferIntoView").withParameter("id", id).withParameter("whichOne", whichOne).withParameter("dontClose", dontClose);
	}
};

class MockedFileManager : public FileManager
{
	virtual BufferID loadFile(const TCHAR * filename, Document doc = NULL, int encoding = -1)
	{
		mock().actualCall("FileManager::loadFile").withParameter("filename", filename).withParameter("Document", &doc).withParameter("encoding", encoding);
		return (Buffer*) 0xcdcdcdcd;
	}
};

TEST_GROUP(NPPIO)
{
	void setup()
	{
//		if (NppParameters::getInstance())
//			NppParameters::getInstance()->destroyInstance();
//
//		mock().expectOneCall("PathRemoveFileSpecA").ignoreOtherParameters();
//		mock().expectOneCall("PathFileExistsA").ignoreOtherParameters();
//		NppParameters::setInstance(new NppParameters());

	}

	void teardown()
	{
//		NppParameters::getInstance()->destroyInstance();
//		NppParameters::setInstance(NULL);
	}
};

TEST(NPPIO, NormalFileToBeOpened)
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
	mock().expectOneCall("FileManager::loadFile").withParameter("filename", "c:\\sessions\\file.session").ignoreOtherParameters();
	mock().expectOneCall("Notepad_plus::loadBufferIntoView").ignoreOtherParameters();
	mock().expectOneCall("PathRemoveFileSpecA").ignoreOtherParameters();

	Notepad_plus_for_test notepad;
	notepad.doOpen("file.session", false, 10);

	FileManager::setInstance(originalFileManager);
	mock().expectNCalls(DOCKCONT_MAX, "DeleteObject").ignoreOtherParameters();
	mock().expectNCalls(2, "DeleteObject").ignoreOtherParameters();
}

TEST(NPPIO, fileToBeOpenedIsASessionFile)
{
	MockedFileManager mockedFileManager;

	FileManager* originalFileManager = FileManager::setInstance(&mockedFileManager);

	string oldSessionExtension = NppParameters::getInstance()->getNppGUI()._definedSessionExt;
	((NppGUI &)NppParameters::getInstance()->getNppGUI())._definedSessionExt = ".session";

	mock().setData("GetFullPathNameA_filename", "c:\\sessions\\file.session");
	mock().setData("GetLongPathNameA_filename", "c:\\sessions\\file.session");
	mock().expectOneCall("GetFullPathNameA").withParameter("lpFileName", "file.session").ignoreOtherParameters();
	mock().expectOneCall("GetLongPathNameA").withParameter("lpszShortPath", "c:\\sessions\\file.session").ignoreOtherParameters();
	mock().expectOneCall("GetFullPathNameA").withParameter("lpFileName", "c:\\sessions\\file.session").ignoreOtherParameters();
	mock().expectOneCall("GetLongPathNameA").withParameter("lpszShortPath", "c:\\sessions\\file.session").ignoreOtherParameters();
	mock().expectOneCall("PathFileExistsA").withParameter("filename", "c:\\sessions\\file.session").andReturnValue((int) true);
	mock().expectOneCall("PathFileExistsA").withParameter("filename", "c:\\sessions\\file.session").andReturnValue((int) true);
	mock().expectOneCall("PathFindExtension").withParameter("filename", "c:\\sessions\\file.session").andReturnValue(".session");

	Notepad_plus_for_test notepad;
	notepad.doOpen("file.session", false, 10);

	FileManager::setInstance(originalFileManager);
	mock().expectNCalls(DOCKCONT_MAX, "DeleteObject").ignoreOtherParameters();
	((NppGUI &)NppParameters::getInstance()->getNppGUI())._definedSessionExt = oldSessionExtension;
}


TEST(NPPIO, fileCreateNewFile)
{
}


TEST(NPPIO, fileOpenADirectory)
{
}
