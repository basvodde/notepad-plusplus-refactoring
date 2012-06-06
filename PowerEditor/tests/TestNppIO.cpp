
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
		if (mock().hasReturnValue())
			return (BufferID) mock().returnValue().getPointerValue();

		return (BufferID) 0xcdcdcdcd;
	}

	virtual bool createEmptyFile(const TCHAR * filename)
	{
		mock().actualCall("FileManager::createEmptyFile").withParameter("filename", filename);
		return true;
	}
};

TEST_GROUP(NPPIO)
{
	MockedFileManager mockedFileManager;
	FileManager* originalFileManager;

	void setup()
	{
		originalFileManager = FileManager::setInstance(&mockedFileManager);
	}

	void teardown()
	{
		FileManager::setInstance(originalFileManager);
	}
};

void exceptShortAndLongFilenames(const char* shortFilename, const char* longFilename)
{
	mock().setData("GetFullPathNameA_filename", longFilename);
	mock().setData("GetLongPathNameA_filename", longFilename);
	mock().expectOneCall("GetFullPathNameA").withParameter("lpFileName", shortFilename).ignoreOtherParameters();
	mock().expectOneCall("GetLongPathNameA").withParameter("lpszShortPath", longFilename).ignoreOtherParameters();
}

TEST(NPPIO, NormalFileToBeOpened)
{
	Notepad_plus_for_test notepad;

	exceptShortAndLongFilenames("file.session", "c:\\sessions\\file.session");
	mock().expectOneCall("PathFileExistsA").withParameter("filename", "c:\\sessions\\file.session").andReturnValue((int) true);
	mock().expectOneCall("PathFileExistsA").withParameter("filename", "c:\\sessions\\file.session").andReturnValue((int) true);
	mock().expectOneCall("FileManager::loadFile").withParameter("filename", "c:\\sessions\\file.session").ignoreOtherParameters();
	mock().expectOneCall("Notepad_plus::loadBufferIntoView").ignoreOtherParameters();

	notepad.doOpen("file.session", false, 10);

	mock().expectNCalls(DOCKCONT_MAX, "DeleteObject").ignoreOtherParameters();
}

TEST(NPPIO, fileToBeOpenedIsASessionFile)
{
	string oldSessionExtension = NppParameters::getInstance()->getNppGUI()._definedSessionExt;
	((NppGUI &)NppParameters::getInstance()->getNppGUI())._definedSessionExt = ".session";

	exceptShortAndLongFilenames("file.session", "c:\\sessions\\file.session");

	mock().expectOneCall("PathFileExistsA").withParameter("filename", "c:\\sessions\\file.session").andReturnValue((int) true);
	mock().expectOneCall("PathFileExistsA").withParameter("filename", "c:\\sessions\\file.session").andReturnValue((int) true);
	mock().expectOneCall("PathFindExtension").withParameter("filename", "c:\\sessions\\file.session").andReturnValue(".session");

	Notepad_plus_for_test notepad;
	notepad.doOpen("file.session", false, 10);

	mock().expectNCalls(DOCKCONT_MAX, "DeleteObject").ignoreOtherParameters();
	((NppGUI &)NppParameters::getInstance()->getNppGUI())._definedSessionExt = oldSessionExtension;
}


TEST(NPPIO, fileCreateNewFile)
{
	Notepad_plus_for_test notepad;

	exceptShortAndLongFilenames("file.session", "c:\\sessions\\file.session");
	mock().expectOneCall("PathFileExistsA").withParameter("filename", "c:\\sessions\\file.session").andReturnValue((int) false);
	mock().expectOneCall("PathFileExistsA").withParameter("filename", "c:\\sessions\\file.session").andReturnValue((int) false);
	mock().expectOneCall("PathFileExistsA").withParameter("filename", "c:\\sessions").andReturnValue((int) true);
	mock().expectOneCall("MessageBoxA").ignoreOtherParameters().andReturnValue(IDYES);
	mock().expectOneCall("FileManager::createEmptyFile").withParameter("filename", "c:\\sessions\\file.session").ignoreOtherParameters();
	mock().expectOneCall("FileManager::loadFile").withParameter("filename", "c:\\sessions\\file.session").ignoreOtherParameters();
	mock().expectOneCall("Notepad_plus::loadBufferIntoView").ignoreOtherParameters();

	notepad.doOpen("file.session", false, 10);

	mock().expectNCalls(DOCKCONT_MAX, "DeleteObject").ignoreOtherParameters();
}

TEST(NPPIO, fileOpenADirectory)
{
	Notepad_plus_for_test notepad;

	exceptShortAndLongFilenames("dir", "c:\\dir");
	mock().expectOneCall("PathFileExistsA").withParameter("filename", "c:\\dir").andReturnValue((int) true);
	mock().expectOneCall("PathFileExistsA").withParameter("filename", "c:\\dir").andReturnValue((int) true);
	mock().expectOneCall("FileManager::loadFile").withParameter("filename", "c:\\dir").ignoreOtherParameters().andReturnValue(BUFFER_INVALID);
	mock().expectOneCall("PathIsDirectoryA").withParameter("path", "c:\\dir").ignoreOtherParameters().andReturnValue((int)true);
	mock().expectOneCall("FindFirstFileA").ignoreOtherParameters();

	notepad.doOpen("dir", false, 10);

	mock().expectNCalls(DOCKCONT_MAX, "DeleteObject").ignoreOtherParameters();

}
