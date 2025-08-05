/*pch.h*/
/** @file
 *
 * @brief Pre-compiled header generation header file.
 * SPDX-License-Identifier: MIT
 *
 */
#pragma once

#ifdef FINAL
# define _CRT_SECURE_INVALID_PARAMETER(expr)
#endif // def FINAL

#define STRICT
#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <Richedit.h>
#include <strsafe.h>

#include "../../../../include/uidgen.h"
#include "../../../../drivers/formatters/basic/include/uidgen/basic_formatters.h"
#include "../../../../drivers/generators/basic/include/uidgen/basic_generators.h"

/*END OF pch.h*/
