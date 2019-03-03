// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here
#ifdef QAQNETWORK_EXPORT
#define QAQNETWORK_LIB _declspec(dllexport)
#else
#define QAQNETWORK_LIB _declspec(dllimport)
#endif