// This file is part of Notepad++ project
// Copyright (C)2003 Don HO <don.h@free.fr>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// Note that the GPL places important restrictions on "derived works", yet
// it does not provide a detailed definition of that term.  To avoid      
// misunderstandings, we consider an application to constitute a          
// "derivative work" for the purpose of this license if it does any of the
// following:                                                             
// 1. Integrates source code from Notepad++.
// 2. Integrates/includes/aggregates Notepad++ into a proprietary executable
//    installer, such as those produced by InstallShield.
// 3. Links to a library or executes a program that does any of the above.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


#ifndef PRECOMPILEHEADER_H
#define PRECOMPILEHEADER_H

// w/o precompiled headers file : 1 minute 55 sec

#define _WIN32_WINNT 0x0501

#include "various.h"

// C RunTime Header Files
#define _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <ctype.h>
#include <functional>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

// STL Headers
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <memory>
#include <algorithm>
#include <exception>
#include <stdexcept>

// Windows Header Files
#include <windows.h>
#include <commctrl.h>
#include <Shlobj.h>
#include <shlwapi.h>
#include <uxtheme.h>
#include <Oleacc.h>
#ifndef CYGWIN_BUILD
#include <dbghelp.h>
#endif
#include <eh.h>

#ifdef UNICODE
#include <wchar.h>
#endif

// Notepad++
#include "Common.h"
#include "Window.h"
#include "StaticDialog.h"

#ifdef CYGWIN_BUILD
#define _stat stat
#define _fseeki64 fseek
#define _ftelli64 ftell

#undef generic_itoa

#define itoa generic_itoa
inline
char* generic_itoa(int value, char * str, int base)
{
	assert(base == 10);
	sprintf("%d", str, value);
	return str;
}
#endif

#endif // PRECOMPILEHEADER_H
