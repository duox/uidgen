/*config.cpp*/
/** @file
 *
 * @brief Configuration management.
 * SPDX-License-Identifier: MIT
 *
 */

#include "pch.h"
#include "main.h"

static BOOL ConfigLoaded = FALSE;	//< guards configuration data by ordering load and then store access
static BOOL	ConfigDeleted = FALSE;	//< TRUE if user invoked Help/Uninstall command


/**
 * @brief More convenient registry value query call.
 *
 * @param[in] hKey (HKEY) handle to key.
 * @param[in] Name (LPSTR) value name.
 * @param[in] lpData (LPVOID) pointer to data buffer.
 * @param[in] cbData (SIZE_T) size of the data buffer, in bytes.
 * @param[out] lpcbData (SIZE_T *) pointer to variable receiving number of bytes read.
 *
 * @return (LRESULT) operation status.
 */
static LRESULT	RegQueryTypedValueA( HKEY hKey, LPCSTR Name, DWORD dwType, LPVOID lpData, SIZE_T cbData, SIZE_T * lpcbData )
{
	DWORD dwThisType = dwType;
	DWORD nRead = (DWORD) cbData;
	LRESULT lResult = RegQueryValueExA( hKey, Name, NULL, &dwType, (LPBYTE) lpData, &nRead );
	if( NULL != lpcbData )
		*lpcbData = nRead;
	if( ERROR_SUCCESS != lResult )
		return lResult;
	if( dwThisType != dwType )
		return ERROR_INVALID_DATATYPE;

	return lResult;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Store configuration.
 *
 * @param[in] hwnd (HWND) pointer to the parent window.
 */
void StoreConfig( HWND hwnd )
{
	HKEY hKey;
	LONG lResult;
	DWORD dwValue;
	char buffer[256];

	// Check current state
	if( !ConfigLoaded )
		return;
	if( ConfigDeleted )
		return;

	// Open path to the registry
	lResult = RegOpenKey( HKEY_CURRENT_USER, TEXT("Software\\duox\\UIDgen"), &hKey );
	if( ERROR_SUCCESS != lResult )
	{
		lResult = RegCreateKey( HKEY_CURRENT_USER, TEXT("Software\\duox\\UIDgen"), &hKey );
		if( ERROR_SUCCESS != lResult )
			return;
	}

	// Store data
	dwValue = ComboBox_GetCurSel( GetDlgItem( hwnd, IDC_GUID_TYPE ) );
	RegSetValueExA( hKey, "GenType", 0, REG_DWORD, (BYTE *) &dwValue, sizeof(dwValue) );
	dwValue = ComboBox_GetCurSel( GetDlgItem( hwnd, IDC_FORMAT_LIST ) );
	RegSetValueExA( hKey, "Format", 0, REG_DWORD, (BYTE *) &dwValue, sizeof(dwValue) );

	GetDlgItemTextA( hwnd, IDC_MANUAL_GUID, buffer, countof(buffer) );
	RegSetValueExA( hKey, "ManualGuid", 0, REG_SZ, (BYTE *) buffer, DWORD( sizeof(*buffer)*lstrlen(buffer) ) );
	GetDlgItemTextA( hwnd, IDC_USER_FORMAT_STRING, buffer, countof(buffer) );
	RegSetValueExA( hKey, "FormatString", 0, REG_SZ, (BYTE *) buffer, DWORD( sizeof(*buffer)*lstrlen(buffer) ) );

	dwValue = g_uidgen_context->get_flags();
	RegSetValueExA( hKey, "UidGenContextFlags", 0, REG_DWORD, (BYTE *) &dwValue, sizeof(dwValue) );
	dwValue = gSystemFlags;
	RegSetValueExA( hKey, "WorkFlags", 0, REG_DWORD, (BYTE *) &dwValue, sizeof(dwValue) );
	dwValue = gWindowHotKey;
	RegSetValueExA( hKey, "WindowHotKey", 0, REG_DWORD, (BYTE *) &dwValue, sizeof(dwValue) );
	dwValue = gGeneratorHotKey;
	RegSetValueExA( hKey, "GeneratorHotKey", 0, REG_DWORD, (BYTE *) &dwValue, sizeof(dwValue) );

	dwValue = !IsWindowVisible( g_hwndMain );
	RegSetValueExA( hKey, "Minimized", 0, REG_DWORD, (BYTE *) &dwValue, sizeof(dwValue) );

	if( 0 <= g_rcMainWindow.left )
		RegSetValueExA( hKey, "Window.X", 0, REG_DWORD, (BYTE *) &g_rcMainWindow.left, sizeof(g_rcMainWindow.left) );
	if( 0 <= g_rcMainWindow.top )
		RegSetValueExA( hKey, "Window.Y", 0, REG_DWORD, (BYTE *) &g_rcMainWindow.top, sizeof(g_rcMainWindow.top) );
	dwValue = g_rcMainWindow.right - g_rcMainWindow.left;
	RegSetValueExA( hKey, "Window.Width", 0, REG_DWORD, (BYTE *) &dwValue, sizeof(dwValue) );
	dwValue = g_rcMainWindow.bottom - g_rcMainWindow.top;
	RegSetValueExA( hKey, "Window.Height", 0, REG_DWORD, (BYTE *) &dwValue, sizeof(dwValue) );

	if( 0 <= g_rcSettingsWindow.left )
		RegSetValueExA( hKey, "Settings.X", 0, REG_DWORD, (BYTE *) &g_rcSettingsWindow.left, sizeof(g_rcSettingsWindow.left) );
	if( 0 <= g_rcSettingsWindow.top )
		RegSetValueExA( hKey, "Settings.Y", 0, REG_DWORD, (BYTE *) &g_rcSettingsWindow.top, sizeof(g_rcSettingsWindow.top) );
	dwValue = g_rcSettingsWindow.right - g_rcSettingsWindow.left;
	RegSetValueExA( hKey, "Settings.Width", 0, REG_DWORD, (BYTE *) &dwValue, sizeof(dwValue) );
	dwValue = g_rcSettingsWindow.bottom - g_rcSettingsWindow.top;
	RegSetValueExA( hKey, "Settings.Height", 0, REG_DWORD, (BYTE *) &dwValue, sizeof(dwValue) );

	if( 0 <= g_rcHelpWindow.left )
		RegSetValueExA( hKey, "Help.X", 0, REG_DWORD, (BYTE *) &g_rcHelpWindow.left, sizeof(g_rcHelpWindow.left) );
	if( 0 <= g_rcHelpWindow.top )
		RegSetValueExA( hKey, "Help.Y", 0, REG_DWORD, (BYTE *) &g_rcHelpWindow.top, sizeof(g_rcHelpWindow.top) );
	dwValue = g_rcHelpWindow.right - g_rcHelpWindow.left;
	RegSetValueExA( hKey, "Help.Width", 0, REG_DWORD, (BYTE *) &dwValue, sizeof(dwValue) );
	dwValue = g_rcHelpWindow.bottom - g_rcHelpWindow.top;
	RegSetValueExA( hKey, "Help.Height", 0, REG_DWORD, (BYTE *) &dwValue, sizeof(dwValue) );

	// Done, exit
	RegCloseKey( hKey );
}

/**
 * @brief Load configuration.
 *
 * @param[in] hwnd (HWND) pointer to the parent window.
 */
BOOL LoadConfig( HWND hwnd )
{
	HKEY hKey;
	LONG lResult;
	DWORD dwGenType = 0, dwFormat = 0;
	char ManualGuid[256];
	char FormatString[256];
	DWORD Minimized = 0;
	DWORD WindowX = 0, WindowY = 0, WindowWidth = 0, WindowHeight = 0;
	DWORD SettingsX = 0, SettingsY = 0, SettingsWidth = 0, SettingsHeight = 0;
	DWORD HelpX = 0, HelpY = 0, HelpWidth = 0, HelpHeight = 0;
	DWORD UidGenContextFlags = 0, WorkFlags = 0, WindowHotKey = 0, GeneratorHotKey = 0;

	*ManualGuid = *FormatString = '\0';

	// Open path to the registry
	lResult = RegOpenKeyA( HKEY_CURRENT_USER, "Software\\duox\\UIDgen", &hKey );
	if( ERROR_SUCCESS != lResult )
	{
		ConfigLoaded = TRUE;	// enable functioning StoreConfig
		return FALSE;
	}

	// Load data
	BOOL bResult =
		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "GenType", REG_DWORD, &dwGenType, sizeof(dwGenType), NULL ) &&
		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "Format", REG_DWORD, &dwFormat, sizeof(dwFormat), NULL ) &&
		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "ManualGuid", REG_SZ, ManualGuid, sizeof(ManualGuid), NULL ) &&
		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "FormatString", REG_SZ, FormatString, sizeof(FormatString), NULL ) &&

		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "UidGenContextFlags", REG_DWORD, &UidGenContextFlags, sizeof(UidGenContextFlags), NULL ) &&
		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "WorkFlags", REG_DWORD, &WorkFlags, sizeof(WorkFlags), NULL ) &&
		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "WindowHotKey", REG_DWORD, &WindowHotKey, sizeof(WindowHotKey), NULL ) &&
		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "GeneratorHotKey", REG_DWORD, &GeneratorHotKey, sizeof(GeneratorHotKey), NULL ) &&

		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "Minimized", REG_DWORD, &Minimized, sizeof(Minimized), NULL ) &&

		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "Window.X", REG_DWORD, &WindowX, sizeof(WindowX), NULL ) &&
		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "Window.Y", REG_DWORD, &WindowY, sizeof(WindowY), NULL ) &&
		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "Window.Width", REG_DWORD, &WindowWidth, sizeof(WindowWidth), NULL ) &&
		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "Window.Height", REG_DWORD, &WindowHeight, sizeof(WindowHeight), NULL ) &&

		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "Settings.X", REG_DWORD, &SettingsX, sizeof(SettingsX), NULL ) &&
		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "Settings.Y", REG_DWORD, &SettingsY, sizeof(SettingsY), NULL ) &&
		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "Settings.Width", REG_DWORD, &SettingsWidth, sizeof(SettingsWidth), NULL ) &&
		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "Settings.Height", REG_DWORD, &SettingsHeight, sizeof(SettingsHeight), NULL ) &&

		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "Help.X", REG_DWORD, &HelpX, sizeof(HelpX), NULL ) &&
		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "Help.Y", REG_DWORD, &HelpY, sizeof(HelpY), NULL ) &&
		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "Help.Width", REG_DWORD, &HelpWidth, sizeof(HelpWidth), NULL ) &&
		ERROR_SUCCESS == RegQueryTypedValueA( hKey, "Help.Height", REG_DWORD, &HelpHeight, sizeof(HelpHeight), NULL ) &&
		TRUE;
	if( bResult &&
		dwGenType < ComboBox_GetCount( GetDlgItem( hwnd, IDC_GUID_TYPE ) ) &&
		dwFormat < ComboBox_GetCount( GetDlgItem( hwnd, IDC_FORMAT_LIST ) ) &&
		0 != WindowWidth && 0 != WindowHeight
	){
		// Modify GUI
		SetRect( &g_rcMainWindow, WindowX, WindowY, WindowX + WindowWidth, WindowY + WindowHeight );
		SetRect( &g_rcSettingsWindow, SettingsX, SettingsY, SettingsX + SettingsWidth, SettingsY + SettingsHeight );
		SetRect( &g_rcHelpWindow, HelpX, HelpY, HelpX + HelpWidth, HelpY + HelpHeight );

#if 1
		if( 0 <= (int) WindowX && 0 <= (int) WindowY )
			MoveWindow( hwnd, WindowX, WindowY, WindowWidth, WindowHeight, FALSE );

		if( Minimized )
		{
			gSystemFlags |= SF_MINIMIZE_TO_TRAY;
			ShowWindow( g_hwndMain, SW_HIDE );
			UpdateTrayIcon( FALSE );
		}
		else
			ShowWindow( g_hwndMain, SW_SHOWDEFAULT );
#else
		if( Minimized )	// TODO: set window size without showing/flashing it if window is minimized/hidden
		{
			ShowWindow( g_hwndMain, SW_HIDE );
			SetRect( &g_rcMainWindow, WindowX, WindowY, WindowWidth, WindowHeight );

			//SetWindowPos( hwnd, NULL, WindowX, WindowY, WindowWidth, WindowHeight, Minimized ? SWP_NOREDRAW | SWP_HIDEWINDOW : 0 );

			WINDOWPLACEMENT wp = { sizeof( WINDOWPLACEMENT ) };
			wp.showCmd = SW_HIDE;
			SetRect( &wp.rcNormalPosition, WindowX, WindowY, WindowWidth, WindowHeight );
			SetWindowPlacement( g_hwndMain, &wp );
		}
		else
			MoveWindow( hwnd, WindowX, WindowY, WindowWidth, WindowHeight, FALSE );
#endif

		ComboBox_SetCurSel( GetDlgItem( hwnd, IDC_GUID_TYPE ), dwGenType );
		ComboBox_SetCurSel( GetDlgItem( hwnd, IDC_FORMAT_LIST ), dwFormat );
		SetDlgItemTextA( hwnd, IDC_MANUAL_GUID, ManualGuid );
		SetDlgItemTextA( hwnd, IDC_USER_FORMAT_STRING, FormatString );
//		CheckDlgButton( hwnd, IDC_REMOVE_LEADING_ZEROES, dwRemoveLeadingZeroes ? BST_CHECKED : BST_UNCHECKED );
//		CheckDlgButton( hwnd, IDC_USE_ANGLE_BRACKETS, dwAngleBrackets ? BST_CHECKED : BST_UNCHECKED );

/*		EnableWindow(
			GetDlgItem( hwnd, IDC_MANUAL_GUID ),
			uidgen::manual_uuid_generator::m_uuid == dwGenType
			);
		EnableWindow(
			GetDlgItem( hwnd, IDC_USER_FORMAT_STRING ),
			&g_user_format_guid_generator == g_guid_generators[dwFormat]
			);
*/
		g_uidgen_context->set_flags( UidGenContextFlags );
		gSystemFlags = WorkFlags;
		gWindowHotKey = WindowHotKey;
		gGeneratorHotKey = GeneratorHotKey;
	}

	// Done, exit
	RegCloseKey( hKey );
	ConfigLoaded = TRUE;	// enable functioning StoreConfig
	return bResult;
}

/**
 * @brief Delete configuration.
 *
 * @param[in] hwnd (HWND) pointer to the parent window.
 */
void DeleteConfig( HWND hwnd )
{
	if( IDYES == MessageBoxA( hwnd, "Delete configuration from the registry?", "Please confirm operation", MB_YESNO|MB_ICONQUESTION ) )
	{
		RegDeleteKeyA( HKEY_CURRENT_USER, "Software\\duox\\UIDgen" );
		RegDeleteKeyA( HKEY_CURRENT_USER, "Software\\duox" );	// may fail if other products are installed
		ConfigDeleted = TRUE;
	}
}

/*END OF config.cpp*/
