/*guimain.cpp*/
/** @file
 *
 * @brief GUI entry.
 * SPDX-License-Identifier: MIT
 *
 */
#include "pch.h"
#include "main.h"

HWND g_hwndMain;
HACCEL g_haccMain;
HINSTANCE g_hInstance;

/**
 * @brief Split key modifiers, returned by the HotKeyCtrl, into VKey and modifiers.
 * @param[in] uHotKey (UINT) hot key value.
 * @param[out] KeyModifiers (UINT *) key modifiers.
 * @param[out] Key (UINT *) key virtual code.
 */
void SplitKeyModifiers( UINT uHotKey, UINT * KeyModifiers, UINT * Key )
{
	UINT HKCtrlKey = LOBYTE( LOWORD( uHotKey ) );
	UINT HKCtrlMod = HIBYTE( LOWORD( uHotKey ) );

	*Key = HKCtrlKey;
	*KeyModifiers = 0;
	if( HKCtrlMod & HOTKEYF_ALT )
		*KeyModifiers |= MOD_ALT;
	if( HKCtrlMod & HOTKEYF_CONTROL )
		*KeyModifiers |= MOD_CONTROL;
	if( HKCtrlMod & HOTKEYF_SHIFT )
		*KeyModifiers |= MOD_SHIFT;

	return;
}

/**
 * @brief Update hot keys, reading them from the corresponding HotKeyCtrls.
 */
BOOL UpdateHookKey()
{
	BOOL Result = TRUE;
	UINT KeyModifiers, Key;

	if( 0 != gWindowHotKey && 0 != (gSystemFlags & SF_WINDOW_HOOK) )
	{
		SplitKeyModifiers( gWindowHotKey, &KeyModifiers, &Key );
		SetLastError( NO_ERROR );
		UnregisterHotKey( g_hwndMain, IDC_GLOBAL_HOOK_KEY );
		RegisterHotKey( g_hwndMain, IDC_GLOBAL_HOOK_KEY, KeyModifiers, Key );
		switch( GetLastError() )
		{
		case NO_ERROR:
		case ERROR_HOTKEY_NOT_REGISTERED:
			break;
		case ERROR_ALREADY_ASSIGNED:
			MessageBox( g_hwndMain, "Another window has already this hot key assigned", "Error", MB_OK | MB_ICONSTOP );
			break;
		case ERROR_INVALID_PARAMETER:
			MessageBox( g_hwndMain, "Hot key is invalid", "Error", MB_OK | MB_ICONSTOP );
			Result = FALSE;
			break;
		default:
			MessageBox( g_hwndMain, "Hot key assignment failure", "Error", MB_OK | MB_ICONSTOP );
			break;
		}
	}

	if( 0 != gGeneratorHotKey && 0 != (gSystemFlags & SF_GENERATOR_HOOK) )
	{
		SplitKeyModifiers( gGeneratorHotKey, &KeyModifiers, &Key );
		SetLastError( NO_ERROR );
		UnregisterHotKey( g_hwndMain, IDC_GENERATOR_HOOK_KEY );
		RegisterHotKey( g_hwndMain, IDC_GENERATOR_HOOK_KEY, KeyModifiers, Key );
		switch( GetLastError() )
		{
		case NO_ERROR:
		case ERROR_HOTKEY_NOT_REGISTERED:
			break;
		case ERROR_ALREADY_ASSIGNED:
			MessageBox( g_hwndMain, "Another window has already this hot key assigned", "Error", MB_OK | MB_ICONSTOP );
			break;
		case ERROR_INVALID_PARAMETER:
			MessageBox( g_hwndMain, "Hot key is invalid", "Error", MB_OK | MB_ICONSTOP );
			Result = FALSE;
			break;
		default:
			MessageBox( g_hwndMain, "Hot key assignment failure", "Error", MB_OK | MB_ICONSTOP );
			break;
		}
	}
	return Result;
}

NOTIFYICONDATA gNotifyIconData;

/**
 * @brief Update shell notification icon.
 */
BOOL UpdateTrayIcon( BOOL Destroy )
{
	if( !Destroy )
	{
		if( 0 == gNotifyIconData.cbSize && (gSystemFlags & SF_MINIMIZE_TO_TRAY) )
		{
			gNotifyIconData.cbSize = sizeof( gNotifyIconData );
			if( NULL == gNotifyIconData.hWnd )
			{
				gNotifyIconData.hWnd = g_hwndMain;
				gNotifyIconData.uCallbackMessage = WM_NOTIFYICON;
				gNotifyIconData.uID = 1;
				gNotifyIconData.uFlags = NIF_ICON | NIF_MESSAGE
#if (_WIN32_IE >= 0x600)
					| NIF_GUID
#endif // (_WIN32_IE >= 0x600)
#if (NTDDI_VERSION >= NTDDI_VISTA)
					| NIF_SHOWTIP
#endif // (NTDDI_VERSION >= NTDDI_VISTA)
					;
				gNotifyIconData.hIcon = LoadIcon( g_hInstance, MAKEINTRESOURCE( IDI_MAIN_SMALL ) );
				lstrcpy( gNotifyIconData.szTip, "UigGen" );
			}
			Shell_NotifyIcon( NIM_ADD, &gNotifyIconData );
		}
	}
	else
	{
		if( 0 != gNotifyIconData.cbSize )
		{
			Shell_NotifyIcon( NIM_DELETE, &gNotifyIconData );
			gNotifyIconData.cbSize = 0;
		}
	}
	return TRUE;
}

/**
 * @brief Window hook callback.
 * @param[int] hWinEventHook (HWINEVENTHOOK) The handle to the hook.
 * @param[int] event (DWORD) The event hat has triggered this callback.
 * @param[int] hwnd (HWND) The window that generated the event (in our case for foreground activation,this is a handle to the window that has received foreground).
 * @param[int] idObject (LONG) The object ID that is associated with this event.
 * @param[int] idChild (LONG) Identifies whether the event was triggered by the object itself,or a child of the object.
 * @param[int] dwEventThread (DWORD) The thread ID that generated the event,or the thread ID that owns the window.
 * @param[int] dwmsEventTime (DWORD) Specifies the time in milliseconds that the event was generated.
 */
VOID CALLBACK WinEventProcCallback(
	HWINEVENTHOOK	hWinEventHook,
	DWORD			event,
	HWND			hwnd,
	LONG			idObject,
	LONG			idChild,
	DWORD			dwEventThread,
	DWORD			dwmsEventTime
	)
{
	/* Test for a window foreground event */
	if ( event == EVENT_SYSTEM_FOREGROUND )
	{
		if ( hwnd && IsWindow( hwnd ) ) /* is this handle still valid? */
		{
			/* Store the window handle in our global variable */
			g_hwndLastActive = hwnd;

			//char Caption[512];
			//GetWindowText( hwnd, Caption, sizeof( Caption ) );
			//OutputDebugString( "Window foreground: " );
			//OutputDebugString( Caption );
			//OutputDebugString( "\r\n" );
		}
	}
	UNREFERENCED_PARAMETER( hWinEventHook );
	UNREFERENCED_PARAMETER( idObject );
	UNREFERENCED_PARAMETER( idChild );
	UNREFERENCED_PARAMETER( dwEventThread );
	UNREFERENCED_PARAMETER( dwmsEventTime );
}

/**
 * @brief GUI entry point function.
 * @param[in] hInstance (HINSTANCE) handle to the module.
 * @param[in] hPrevInstance (HINSTANCE) unused.
 * @param[in] lpCmdLine (LPSTR) pointer to command line.
 * @param[in] nShowCmd (int) one of the SW_* constants, used by the ShowWindow function.
 * @return (int) process exit code.
 */
int WINAPI WinMain( IN HINSTANCE hInstance,IN HINSTANCE hPrevInstance,IN LPSTR lpCmdLine,IN int nShowCmd )
{
	HWINEVENTHOOK g_hWinEventHook;

	g_hInstance = hInstance;

	LoadLibrary( TEXT("Riched20.dll") );
//	INITCOMMONCONTROLSEX icce = { sizeof(INITCOMMONCONTROLSEX), ICC_UPDOWN_CLASS };
//	InitCommonControlsEx( &icce );

	g_hwndMain = CreateDialog( hInstance,MAKEINTRESOURCE( IDD_MAIN ),HWND_DESKTOP,MainDialogProc );
	if( NULL == g_hwndMain )
	{
		MessageBoxA( HWND_DESKTOP,"Cannot create main dialog.","Fatal error",MB_OK | MB_ICONERROR | MB_TOPMOST );
		return -1;
	}

	HMENU hmnuSystem = GetSystemMenu( g_hwndMain, FALSE );
	InsertMenu( hmnuSystem, 0, MF_BYPOSITION | MF_STRING, ID_ABOUT, "About..." );
	InsertMenu( hmnuSystem, 1, MF_BYPOSITION | MF_SEPARATOR, 0, "");

	g_haccMain = LoadAccelerators( hInstance,MAKEINTRESOURCE( IDA_MAIN ) );

	if( !LoadConfig( g_hwndMain ) )
		ShowWindow( g_hwndMain,nShowCmd );
	OnUpdateGuidFormat( g_hwndMain,GetDlgItem( g_hwndMain,IDC_FORMAT_LIST ) );
	UpdateHookKey();

	g_hWinEventHook = SetWinEventHook( EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, NULL, WinEventProcCallback, 0, 0,
		WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS );

	MSG Msg;
	int bRet;
	while( 0 != (bRet = GetMessage( &Msg,NULL,0,0 )) )
	{
		if( bRet == -1 || !IsWindow( g_hwndMain ) )
		{
			Msg.wParam = (WPARAM) -2;
			break;
		}

		if( TranslateAccelerator( g_hwndMain, g_haccMain, &Msg ) )
			continue;

		if( IsDialogMessage( g_hwndMain, &Msg ) )
			continue;
		if( IsDialogMessage( g_hwndHelp, &Msg ) )
			continue;

		TranslateMessage( &Msg );
		DispatchMessage( &Msg );
	}

	if( 0 != g_hWinEventHook )
		UnhookWinEvent( g_hWinEventHook ); 
	UpdateTrayIcon( TRUE );

	DestroyAcceleratorTable( g_haccMain );

	//	_CrtDumpMemoryLeaks();
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );
	return (int) Msg.wParam;
}

/*END OF guimain.cpp*/
