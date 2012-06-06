
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#define WINSHLWAPI extern
#include "precompiledHeaders.h"

bool app_started = false;

BOOL WINAPI PathFileExistsA(LPCSTR filename)
{
	if (!app_started) return TRUE;

	mock().actualCall("PathFileExistsA").withParameter("filename", filename);

	if (mock().hasReturnValue())
		return (bool) mock().returnValue().getIntValue();
	return TRUE;
}

BOOL WINAPI PathRemoveFileSpecA(LPSTR filename)
{
	if (!app_started) return TRUE;

	mock().actualCall("PathRemoveFileSpecA").withParameter("filename", filename);

	return TRUE;
}

LPSTR WINAPI PathFindFileNameA(LPCSTR)
{
	FAIL("PathFindFileNameA");
	return NULL;
}

void WINAPI PathRemoveExtensionA(LPSTR)
{
	FAIL("PathRemoveExtensionA");
}

LPSTR WINAPI PathFindExtensionA(LPCSTR filename)
{
	mock().actualCall("PathFindExtension").withParameter("filename", filename);

	if (mock().hasReturnValue())
		return (LPSTR) mock().returnValue().getStringValue();

	return NULL;
}

BOOL WINAPI PathAppendA(LPSTR,LPCSTR)
{
	if (app_started)
		FAIL("PathAppendA");
	return TRUE;
}

BOOL WINAPI PathMatchSpecA(LPCSTR,LPCSTR)
{
	FAIL("PathMatchSpecA");
	return FALSE;
}

BOOL WINAPI PathIsDirectoryA(LPCSTR path)
{
	mock().actualCall("PathIsDirectoryA").withParameter("path", path);

	if (mock().hasReturnValue())
		return (bool) mock().returnValue().getIntValue();

	return FALSE;
}

BOOL WINAPI PathIsRelativeA(LPCSTR)
{
	FAIL("PathIsRelativeA");
	return FALSE;
}

void WINAPI PathStripPathA(LPSTR)
{
	FAIL("PathStripPathA");
}

WINSHLWAPI BOOL WINAPI PathCompactPathExA(LPSTR,LPCSTR,UINT,DWORD)
{
	FAIL("PathCompactPathExA");
	return FALSE;
}

WINSHLWAPI BOOL WINAPI PathAddExtensionA(LPSTR,LPCSTR)
{
	FAIL("PathAddExtensionA");
	return FALSE;
}

/////// GDI

HGDIOBJ WINAPI GetStockObject(int)
{
	FAIL("GetStockObject");
	return NULL;
}

HBRUSH WINAPI CreateSolidBrush(COLORREF)
{
	FAIL("CreateSolidBrush");
	return NULL;
}

HDC WINAPI CreateCompatibleDC(HDC)
{
	FAIL("CreateCompatibleDC");
	return NULL;
}

HBITMAP WINAPI CreateCompatibleBitmap(HDC,int,int)
{
	FAIL("CreateCompatibleBitmap");
	return NULL;
}

HGDIOBJ WINAPI SelectObject(HDC,HGDIOBJ)
{
	FAIL("SelectObject");
	return NULL;
}

COLORREF WINAPI GetPixel(HDC,int,int)
{
	FAIL("GetPixel");
	return NULL;
}

BOOL WINAPI DeleteObject(HGDIOBJ obj)
{
	mock().actualCall("DeleteObject").withParameter("obj", obj);
	return FALSE;
}

BOOL WINAPI DeleteDC(HDC)
{
	FAIL("DeleteDC");
	return FALSE;
}

COLORREF WINAPI SetTextColor(HDC,COLORREF)
{
	FAIL("SetTextColor");
	return NULL;
}

COLORREF WINAPI SetBkColor(HDC,COLORREF)
{
	FAIL("SetBkColor");
	return NULL;
}

int WINAPI GetObjectA(HGDIOBJ,int,PVOID)
{
	FAIL("GetObjectA");
	return 0;
}

HFONT WINAPI CreateFontIndirectA(const LOGFONTA*)
{
	FAIL("CreateFontIndirectA");
	return NULL;
}

BOOL WINAPI Rectangle(HDC,int,int,int,int)
{
	FAIL("Rectangle");
	return NULL;
}

int WINAPI SetBkMode(HDC,int)
{
	FAIL("SetBkMode");
	return 0;
}

HBRUSH WINAPI CreateHatchBrush(int,COLORREF)
{
	FAIL("CreateHatchBrush");
	return NULL;
}

WINGDIAPI HPEN WINAPI CreatePen(int,int,COLORREF)
{
	FAIL("CreateHatchBrush");
	return NULL;
}

WINGDIAPI BOOL WINAPI MoveToEx(HDC,int,int,LPPOINT)
{
	FAIL("MoveToEx");
	return FALSE;
}

WINGDIAPI BOOL WINAPI LineTo(HDC,int,int)
{
	FAIL("LineTo");
	return FALSE;
}

WINGDIAPI int WINAPI EnumFontFamiliesExA(HDC,PLOGFONTA,FONTENUMPROCA,LPARAM,DWORD)
{
	FAIL("EnumFontFamiliesExA");
	return 0;
}

WINGDIAPI HBITMAP WINAPI CreateBitmap(int,int,UINT,UINT,PCVOID)
{
	FAIL("CreateBitmap");
	return NULL;
}

WINGDIAPI HBRUSH WINAPI CreatePatternBrush(HBITMAP)
{
	FAIL("CreatePatternBrush");
	return NULL;
}

WINGDIAPI BOOL WINAPI SetBrushOrgEx(HDC,int,int,LPPOINT)
{
	FAIL("SetBrushOrgEx");
	return FALSE;
}

WINGDIAPI BOOL WINAPI BitBlt(HDC,int,int,int,int,HDC,int,int,DWORD)
{
	FAIL("BitBlt");
	return FALSE;
}

WINGDIAPI BOOL WINAPI PatBlt(HDC,int,int,int,int,DWORD)
{
	FAIL("PatBlt");
	return FALSE;
}

BOOL GetTextExtentPoint32A(HDC,LPCSTR,int,LPSIZE)
{
	FAIL("GetTextExtentPoint32A");
	return FALSE;
}

WINGDIAPI HFONT WINAPI CreateFontA(int,int,int,int,int,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,LPCSTR)
{
	FAIL("CreateFontA");
	return NULL;
}

WINGDIAPI BOOL WINAPI RestoreDC(HDC,int)
{
	FAIL("RestoreDC");
	return FALSE;
}

WINGDIAPI int WINAPI SaveDC(HDC)
{
	FAIL("SaveDC");
	return 0;
}

WINGDIAPI BOOL WINAPI GetTextMetricsA(HDC,LPTEXTMETRICA)
{
	FAIL("GetTextMetricsA");
	return FALSE;
}

WINGDIAPI int WINAPI SetROP2(HDC,int)
{
	FAIL("SetROP2");
	return 0;
}

WINGDIAPI int WINAPI GetROP2(HDC)
{
	FAIL("GetROP2");
	return 0;
}

WINGDIAPI BOOL WINAPI GetTextExtentPointA(HDC,LPCSTR,int,LPSIZE)
{
	FAIL("GetTextExtentPointA");
	return FALSE;
}

WINGDIAPI int WINAPI GetDeviceCaps(HDC,int)
{
	FAIL("GetDeviceCaps");
	return 0;
}

WINGDIAPI BOOL WINAPI DPtoLP(HDC,LPPOINT,int)
{
	FAIL("DPtoLP");
	return FALSE;
}

WINGDIAPI int WINAPI StartDocA(HDC,const DOCINFOA*)
{
	FAIL("StartDocA");
	return 0;
}

WINGDIAPI int WINAPI StartPage(HDC)
{
	FAIL("StartPage");
	return 0;
}

WINGDIAPI UINT WINAPI SetTextAlign(HDC,UINT)
{
	FAIL("SetTextAlign");
	return 0;
}

WINGDIAPI BOOL WINAPI ExtTextOutA(HDC,int,int,UINT,LPCRECT,LPCSTR,UINT,const INT*)
{
	FAIL("ExtTextOutA");
	return FALSE;
}

WINGDIAPI int WINAPI EndDoc(HDC)
{
	FAIL("EndDoc");
	return 0;
}

WINGDIAPI BOOL WINAPI OffsetWindowOrgEx(HDC,int,int,LPPOINT)
{
	FAIL("OffsetWindowOrgEx");
	return FALSE;
}

WINGDIAPI int WINAPI EndPage(HDC)
{
	FAIL("EndPage");
	return 0;
}

WINGDIAPI BOOL WINAPI SetWindowOrgEx(HDC,int,int,LPPOINT)
{
	FAIL("SetWindowOrgEx");
	return FALSE;
}

// Commctrl

BOOL WINAPI PrintDlgA(LPPRINTDLGA)
{
	FAIL("PrintDlgA");
	return FALSE;
}

BOOL WINAPI InitCommonControlsEx(LPINITCOMMONCONTROLSEX)
{
	FAIL("InitCommonControlsExs");
	return FALSE;
}

BOOL WINAPI ChooseColorA(LPCHOOSECOLORA)
{
	FAIL("ChooseColorA");
	return FALSE;
}

BOOL WINAPI ImageList_Destroy(HIMAGELIST)
{
	FAIL("ImageList_Destroy");
	return FALSE;
}

HIMAGELIST WINAPI ImageList_Create(int,int,UINT,int,int)
{
	FAIL("ImageList_Create");
	return FALSE;
}

int WINAPI ImageList_ReplaceIcon(HIMAGELIST,int,HICON)
{
	FAIL("ImageList_ReplaceIcon");
	return 0;
}

BOOL WINAPI ImageList_GetImageInfo(HIMAGELIST,int,IMAGEINFO*)
{
	FAIL("ImageList_GetImageInfo");
	return FALSE;
}

BOOL WINAPI ImageList_Draw(HIMAGELIST,int,HDC,int,int,UINT)
{
	FAIL("ImageList_Draw");
	return FALSE;
}

void WINAPI InitCommonControls(void)
{
	FAIL("InitCommonControls");
}

int WINAPI ImageList_AddMasked(HIMAGELIST,HBITMAP,COLORREF)
{
	FAIL("ImageList_AddMasked");
	return 0;
}

BOOL WINAPI ImageList_SetIconSize(HIMAGELIST,int,int)
{
	FAIL("ImageList_SetIconSize");
	return FALSE;
}

BOOL WINAPI ImageList_BeginDrag(HIMAGELIST,int,int,int)
{
	FAIL("ImageList_BeginDrag");
	return FALSE;
}

BOOL WINAPI ImageList_DragEnter(HWND,int,int)
{
	FAIL("ImageList_DragEnter");
	return FALSE;
}

BOOL WINAPI ImageList_DragMove(int,int)
{
	FAIL("ImageList_DragMove");
	return FALSE;
}

BOOL WINAPI ImageList_DragShowNolock(BOOL)
{
	FAIL("ImageList_DragShowNolockv");
	return FALSE;
}

void WINAPI ImageList_EndDrag(VOID)
{
	FAIL("ImageList_EndDrag");
}

int WINAPI ImageList_Add(HIMAGELIST,HBITMAP,HBITMAP)
{
	FAIL("ImageList_Add");
	return 0;
}

int WINAPI ImageList_GetImageCount(HIMAGELIST)
{
	FAIL("ImageList_GetImageCount");
	return 0;
}

// Objbase

WINOLEAPI CoInitialize(PVOID)
{
	FAIL("CoInitialize");
	return NULL;
}

void CoUninitialize(void)
{
	FAIL("CoUninitialize");
}

// Winuser

WINUSERAPI BOOL WINAPI _TrackMouseEvent(LPTRACKMOUSEEVENT)
{
	FAIL("TrackMouseEvent");
	return FALSE;
}

// Commdlg

BOOL WINAPI GetOpenFileNameA(LPOPENFILENAMEA)
{
	FAIL("GetOpenFileNameA");
	return FALSE;
}

BOOL WINAPI GetSaveFileNameA(LPOPENFILENAMEA)
{
	FAIL("GetSaveFileNameA");
	return FALSE;
}

// winuser

WINUSERAPI int WINAPI MessageBoxA(HWND wnd,LPCSTR message,LPCSTR title,UINT type)
{
	mock().actualCall("MessageBoxA").withParameter("wnd", wnd).withParameter("message", message).withParameter("title", title).withParameter("type", (int)type);

	if (mock().hasReturnValue())
		return mock().returnValue().getIntValue();

	return 0;
}


// Winbase

DWORD WINAPI GetFullPathNameA(LPCSTR lpFileName,DWORD nBufferLength, LPSTR lpBuffer,LPSTR* lpFilePart)
{
	mock().actualCall("GetFullPathNameA").withParameter("lpFileName", lpFileName).withParameter("nBufferLength", (int) nBufferLength)
			.withParameter("lpBuffer", lpBuffer).withParameter("lpFilePart", lpFilePart);

	if (mock().hasData("GetFullPathNameA_filename")) {
		const char* output_filename = mock().getData("GetFullPathNameA_filename").getStringValue();
		strncpy(lpBuffer, output_filename , min(strlen(output_filename)+1, nBufferLength));
	}

	return 0;
}

DWORD WINAPI GetLongPathNameA(LPCSTR lpszShortPath,LPSTR lpszLongPath,DWORD cchBuffer)
{
	mock().actualCall("GetLongPathNameA").withParameter("lpszShortPath", lpszShortPath).withParameter("lpszLongPath", lpszLongPath)
			.withParameter("cchBuffer", (int) cchBuffer);
	if (mock().hasData("GetFullPathNameA_filename")) {
		const char* output_filename = mock().getData("GetLongPathNameA_filename").getStringValue();
		strncpy(lpszLongPath, output_filename , min(strlen(output_filename)+1, cchBuffer));
	}

	return 0;
}

HANDLE WINAPI FindFirstFileA(LPCTSTR lpFileName, LPWIN32_FIND_DATA lpFindFileData)
{
	mock().actualCall("FindFirstFileA").withParameter("lpFileName", lpFileName).withParameter("lpFindFileData", lpFindFileData);
	return INVALID_HANDLE_VALUE;
}
