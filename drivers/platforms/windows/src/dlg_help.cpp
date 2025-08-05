/*dlg_help.cpp*/
/** @file
 *
 * @brief `Help' dialog box.
 * SPDX-License-Identifier: MIT
 *
 */
#include "pch.h"
#include "main.h"

static RECT g_InitialClientRect;
static RECT g_InitialWindowRect;
RECT g_rcHelpWindow;

/**
 * @brief List of all controls that can change size and/or position during resize of the parent window.
 *
 */
static control_info g_ctrl_list[] =
{
	{ IDC_HELP_DOC,				CTRL_ANCHOR_TOP | CTRL_ANCHOR_LEFT | CTRL_ANCHOR_BOTTOM | CTRL_ANCHOR_RIGHT },
	{ IDOK,						CTRL_MOVE_TOP | CTRL_ANCHOR_LEFT | CTRL_ANCHOR_BOTTOM },
};

/**
 * @brief Load RTF data to the reach edit control.
 * @param[in] hwndRichEdit (HWND) handle to the Rich Edit control.
 * @param[in] uRcId (UINT) the resource where the RTF data are stored.
 */
void LoadRtfToRichEdit( HWND hwndRichEdit, UINT uRcId )
{
	// Load resource
	HRSRC hRsrc = FindResource( g_hInstance, MAKEINTRESOURCE( uRcId ), "RTF" );
	if( NULL == hRsrc )
		return;
	HGLOBAL hglbRsrc = LoadResource( g_hInstance, hRsrc );
	if( NULL == hglbRsrc )
		return;
	LPVOID lpData = LockResource( hglbRsrc );
	if( NULL == lpData )
		return;

	// Load file
	SetWindowText( hwndRichEdit, (LPCSTR) lpData );

	// Exit
	return;
}

/**
 * @brief Help dialog procedure.
 *
 * @param[in] hwnd (HWND) dialog window handle.
 * @param[in] uMsg (UINT) message identifier.
 * @param[in] wParam (WPARAM) 1st message parameter.
 * @param[in] lParam (WPARAM) 2nd message parameter.
 *
 * @return (INT_PTR) return value depends on the message sent.
 */
INT_PTR CALLBACK HelpDialogProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
	case WM_INITDIALOG:
		g_hwndHelp = hwnd;
		InitPositions( hwnd, g_ctrl_list, countof( g_ctrl_list ), &g_InitialClientRect, &g_InitialWindowRect );
		if( 0 != g_rcHelpWindow.right )
			MoveWindow( hwnd, g_rcHelpWindow.left, g_rcHelpWindow.top, g_rcHelpWindow.right - g_rcHelpWindow.left, g_rcHelpWindow.bottom - g_rcHelpWindow.top, TRUE );
		SendDlgItemMessage( hwnd, IDC_HELP_DOC, EM_SETWORDWRAPMODE, WBF_WORDWRAP | WBF_WORDBREAK, 0 );
		LoadRtfToRichEdit( GetDlgItem( hwnd, IDC_HELP_DOC ), IDR_RTF_HELP_TEXT );
		ShowWindow( hwnd, SW_SHOWDEFAULT );

		// Remove selection by placing caret in the start of the document
		SendDlgItemMessage( hwnd, IDC_HELP_DOC, EM_SETSEL, (WPARAM) 0, (LPARAM) 0);

		// Set fialog icon
		HICON hico;
		hico = LoadIcon( g_hInstance, MAKEINTRESOURCE( IDI_MAIN_SMALL ) );
		SendMessage( hwnd, WM_SETICON, ICON_BIG, LPARAM( hico ) );
		SendMessage( hwnd, WM_SETICON, ICON_SMALL, LPARAM( hico ) );
		DestroyIcon( hico );

		//return TRUE;	// let Windows set the focus
		return FALSE;
	case WM_CLOSE:
		//EndDialog( hwnd, 0 );
		DestroyWindow( hwnd );
		g_hwndHelp = NULL;
		break;
	case WM_NCHITTEST:{
		int lResult = (int) DefWindowProc( hwnd, uMsg, wParam, lParam );
		::SetWindowLongPtr( hwnd, DWLP_MSGRESULT, HTCLIENT == lResult ? HTCAPTION : lResult );
		}break;
	case WM_GETMINMAXINFO:{
		MINMAXINFO* mmi = (MINMAXINFO*) lParam;
		mmi->ptMinTrackSize.x = 200;
		mmi->ptMinTrackSize.y = 200;
		}return TRUE;
	case WM_SIZE:
		UpdatePositions( hwnd, g_ctrl_list, countof( g_ctrl_list ) );
		// fall through
	case WM_MOVE:
		GetWindowRect( hwnd, &g_rcHelpWindow );
		return FALSE;
	case WM_COMMAND:
		switch( LOWORD( wParam ) )
		{
		case IDOK:
		case IDCANCEL:
		case IDCLOSE:
			SendMessage( hwnd, WM_CLOSE, 0, 0 );
			break;
		default:
			return FALSE;
		}
		break;
	default:
		return FALSE;
	}
	UNREFERENCED_PARAMETER( wParam );
	UNREFERENCED_PARAMETER( lParam );
	return TRUE;
}

/*END OF dlg_help.cpp*/
