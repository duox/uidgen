/*pch.h*/
#pragma once

#ifdef FINAL
# define _CRT_SECURE_INVALID_PARAMETER(expr)
#endif // def FINAL

#define STRICT
#define _WIN32_WINNT	0x0501
#include <windows.h>
#include <strsafe.h>

#include "../include/uidgen-rtl.h"

/*END OF pch.h*/
