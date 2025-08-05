/*dlg_sett.cpp*/
/** @file
 *
 * @brief Settings dialog box.
 * SPDX-License-Identifier: MIT
 *
 */
#include "pch.h"
#include "main.h"

static RECT g_InitialClientRect;
static RECT g_InitialWindowRect;
RECT g_rcSettingsWindow;


/**
 * @brief Initialize state of the Settings dialog.
 * @param[in] hwnd (HWND) dialog window handle.
 */
static void OnReloadSettings( HWND hwnd )
{
	CheckDlgButton( hwnd, IDC_MINIMIZE_TO_TRAY, gSystemFlags & SF_MINIMIZE_TO_TRAY ? BST_CHECKED : BST_UNCHECKED );
	CheckDlgButton( hwnd, IDC_ESC_CLOSES_APP, gSystemFlags & SF_ESC_CLOSES_APP ? BST_CHECKED : BST_UNCHECKED );
	CheckDlgButton( hwnd, IDC_ESC_MINIMIZES_APP, gSystemFlags & SF_ESC_MINIMIZES_APP ? BST_CHECKED : BST_UNCHECKED );

	CheckDlgButton( hwnd, IDC_GLOBAL_HOOK, gSystemFlags & SF_WINDOW_HOOK ? BST_CHECKED : BST_UNCHECKED );
	EnableWindow( GetDlgItem( hwnd, IDC_GLOBAL_HOOK_KEY ), IsDlgButtonChecked( hwnd, IDC_GLOBAL_HOOK ) & BST_CHECKED );
	SendDlgItemMessage( hwnd, IDC_GLOBAL_HOOK_KEY, HKM_SETHOTKEY, gWindowHotKey, 0 );

	CheckDlgButton( hwnd, IDC_GENERATOR_HOOK, gSystemFlags & SF_GENERATOR_HOOK ? BST_CHECKED : BST_UNCHECKED );
	EnableWindow( GetDlgItem( hwnd, IDC_GENERATOR_HOOK_KEY ), IsDlgButtonChecked( hwnd, IDC_GENERATOR_HOOK ) & BST_CHECKED );
	SendDlgItemMessage( hwnd, IDC_GENERATOR_HOOK_KEY, HKM_SETHOTKEY, gGeneratorHotKey, 0 );

	CheckDlgButton( hwnd, IDC_REMOVE_LEADING_ZEROES, g_uidgen_context->get_flags( uidgen::context::fl_remove_leading_zeroes ) ? BST_CHECKED : BST_UNCHECKED );
	CheckDlgButton( hwnd, IDC_USE_ANGLE_BRACKETS, g_uidgen_context->get_flags( uidgen::context::fl_use_angle_brackets ) ? BST_CHECKED : BST_UNCHECKED );
	CheckDlgButton( hwnd, IDC_IGNORE_NEW_LINES_IN_USER_FORMAT, g_uidgen_context->get_flags( uidgen::context::fl_new_lines_in_user_format ) ? BST_CHECKED : BST_UNCHECKED );


	CheckDlgButton( hwnd, IDC_KEEP_CASE, 0 == g_uidgen_context->get_flags( uidgen::context::fl_format_upper_case|uidgen::context::fl_format_lower_case ) ? BST_CHECKED : BST_UNCHECKED );
	CheckDlgButton( hwnd, IDC_UPPERCASE, g_uidgen_context->get_flags( uidgen::context::fl_format_upper_case ) ? BST_CHECKED : BST_UNCHECKED );
	CheckDlgButton( hwnd, IDC_LOWERCASE, g_uidgen_context->get_flags( uidgen::context::fl_format_lower_case ) ? BST_CHECKED : BST_UNCHECKED );

	CheckDlgButton( hwnd, IDC_LITTLE_ENDIAN, !g_uidgen_context->get_flags( uidgen::context::fl_format_big_endian ) ? BST_CHECKED : BST_UNCHECKED );
	CheckDlgButton( hwnd, IDC_BIG_ENDIAN,	  g_uidgen_context->get_flags( uidgen::context::fl_format_big_endian ) ? BST_CHECKED : BST_UNCHECKED );
}

/**
 * @brief Apply changes made in the Settings dialog.
 * @param[in] hwnd (HWND) dialog window handle.
 */
static BOOL OnSettingsOK( HWND hwnd )
{
	BOOL Result = TRUE;

	IsDlgButtonChecked( hwnd, IDC_MINIMIZE_TO_TRAY ) == BST_CHECKED ?
		gSystemFlags |= SF_MINIMIZE_TO_TRAY:
		gSystemFlags &= ~SF_MINIMIZE_TO_TRAY;
	UpdateTrayIcon( FALSE );

	IsDlgButtonChecked( hwnd, IDC_ESC_CLOSES_APP ) == BST_CHECKED ?
		gSystemFlags |= SF_ESC_CLOSES_APP:
		gSystemFlags &= ~SF_ESC_CLOSES_APP;

	IsDlgButtonChecked( hwnd, IDC_ESC_MINIMIZES_APP ) == BST_CHECKED ?
		gSystemFlags |= SF_ESC_MINIMIZES_APP:
		gSystemFlags &= ~SF_ESC_MINIMIZES_APP;

	if( IsDlgButtonChecked( hwnd, IDC_GLOBAL_HOOK ) == BST_CHECKED )
	{
		gSystemFlags |= SF_WINDOW_HOOK;
		LRESULT lResult = SendDlgItemMessage( hwnd, IDC_GLOBAL_HOOK_KEY, HKM_GETHOTKEY, 0, 0 );
		
		gWindowHotKey = LOWORD( lResult );		// LOBYTE(LOWORD()) == VK_*, HIBYTE(LOWORD()) == HOTKEYF_ALT, HOTKEYF_CONTROL, HOTKEYF_SHIFT, HOTKEYF_EXT

		if( !UpdateHookKey() )
			SetFocus( GetDlgItem( hwnd, IDC_GLOBAL_HOOK_KEY ) );
	}
	else
	{
		gSystemFlags &= ~SF_WINDOW_HOOK;
		SendMessage( hwnd, WM_SETHOTKEY, 0, 0 );
		gWindowHotKey = 0;
	}

	if( IsDlgButtonChecked( hwnd, IDC_GENERATOR_HOOK ) == BST_CHECKED )
	{
		gSystemFlags |= SF_GENERATOR_HOOK;
		LRESULT lResult = SendDlgItemMessage( hwnd, IDC_GENERATOR_HOOK_KEY, HKM_GETHOTKEY, 0, 0 );

		gGeneratorHotKey = LOWORD( lResult );		// LOBYTE(LOWORD()) == VK_*, HIBYTE(LOWORD()) == HOTKEYF_ALT, HOTKEYF_CONTROL, HOTKEYF_SHIFT, HOTKEYF_EXT

		if( !UpdateHookKey() )
			SetFocus( GetDlgItem( hwnd, IDC_GENERATOR_HOOK_KEY ) );
	}
	else
	{
		gSystemFlags &= ~SF_GENERATOR_HOOK;
		SendMessage( hwnd, WM_SETHOTKEY, 0, 0 );
		gGeneratorHotKey = 0;
	}

	IsDlgButtonChecked( hwnd, IDC_REMOVE_LEADING_ZEROES ) == BST_CHECKED ?
		g_uidgen_context->modify_flags( uidgen::context::fl_remove_leading_zeroes ):
		g_uidgen_context->modify_flags( 0, uidgen::context::fl_remove_leading_zeroes );

	IsDlgButtonChecked( hwnd, IDC_USE_ANGLE_BRACKETS ) == BST_CHECKED ?
		g_uidgen_context->modify_flags( uidgen::context::fl_use_angle_brackets ):
		g_uidgen_context->modify_flags( 0, uidgen::context::fl_use_angle_brackets );

	IsDlgButtonChecked( hwnd, IDC_IGNORE_NEW_LINES_IN_USER_FORMAT ) == BST_CHECKED ?
		g_uidgen_context->modify_flags( uidgen::context::fl_new_lines_in_user_format ):
		g_uidgen_context->modify_flags( 0, uidgen::context::fl_new_lines_in_user_format );

	if( IsDlgButtonChecked( hwnd, IDC_KEEP_CASE ) == BST_CHECKED )
		g_uidgen_context->modify_flags( 0, uidgen::context::fl_format_upper_case | uidgen::context::fl_format_lower_case );
	if( IsDlgButtonChecked( hwnd, IDC_UPPERCASE ) == BST_CHECKED )
		g_uidgen_context->modify_flags( uidgen::context::fl_format_upper_case, uidgen::context::fl_format_lower_case );
	if( IsDlgButtonChecked( hwnd, IDC_LOWERCASE ) == BST_CHECKED )
		g_uidgen_context->modify_flags( uidgen::context::fl_format_lower_case, uidgen::context::fl_format_upper_case );

	if( IsDlgButtonChecked( hwnd, IDC_LITTLE_ENDIAN ) == BST_CHECKED )
		g_uidgen_context->modify_flags( 0, uidgen::context::fl_format_big_endian );
	if( IsDlgButtonChecked( hwnd, IDC_BIG_ENDIAN ) == BST_CHECKED )
		g_uidgen_context->modify_flags( uidgen::context::fl_format_big_endian, 0 );

	return Result;
}

/**
 * @brief Settings dialog procedure.
 *
 * @param[in] hwnd (HWND) dialog window handle.
 * @param[in] uMsg (UINT) message identifier.
 * @param[in] wParam (WPARAM) 1st message parameter.
 * @param[in] lParam (WPARAM) 2nd message parameter.
 *
 * @return (INT_PTR) return value depends on the message sent.
 */
INT_PTR CALLBACK SettingsDialogProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
	case WM_INITDIALOG:
		if( 0 != g_rcSettingsWindow.right )
			MoveWindow( hwnd, g_rcSettingsWindow.left, g_rcSettingsWindow.top, g_rcSettingsWindow.right - g_rcSettingsWindow.left, g_rcSettingsWindow.bottom - g_rcSettingsWindow.top, TRUE );
		OnReloadSettings( hwnd );
		break;
	case WM_CLOSE:
		EndDialog( hwnd, 0 );
		break;
	case WM_NCHITTEST:{
		int lResult = (int) DefWindowProc( hwnd, uMsg, wParam, lParam );
		::SetWindowLongPtr( hwnd, DWLP_MSGRESULT, HTCLIENT == lResult ? HTCAPTION : lResult );
		}break;
	case WM_MOVE:
	case WM_SIZE:
		GetWindowRect( hwnd, &g_rcSettingsWindow );
		break;
	case WM_COMMAND:
		switch( LOWORD( wParam ) )
		{
		case IDOK:
			if( !OnSettingsOK( hwnd ) )
				return FALSE;
		case IDCANCEL:
		case IDCLOSE:
			SendMessage( hwnd, WM_CLOSE, 0, 0 );
			break;

		case IDC_GLOBAL_HOOK:
			EnableWindow( GetDlgItem( hwnd, IDC_GLOBAL_HOOK_KEY ), SendMessage( (HWND) lParam, BM_GETCHECK, 0, 0 ) == BST_CHECKED );
			break;				
		case IDC_GENERATOR_HOOK:
			EnableWindow( GetDlgItem( hwnd, IDC_GENERATOR_HOOK_KEY ), SendMessage( (HWND) lParam, BM_GETCHECK, 0, 0 ) == BST_CHECKED );
			break;				
		case IDC_KEEP_CASE:
			CheckRadioButton( hwnd, IDC_KEEP_CASE, IDC_UPPERCASE, IDC_KEEP_CASE );
			break;
		case IDC_LOWERCASE:
			CheckRadioButton( hwnd, IDC_KEEP_CASE, IDC_UPPERCASE, IDC_LOWERCASE );
			break;
		case IDC_UPPERCASE:
			CheckRadioButton( hwnd, IDC_KEEP_CASE, IDC_UPPERCASE, IDC_UPPERCASE );
			break;
		case IDC_UNINSTALL:
			DeleteConfig( hwnd );
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

/*END OF dlg_sett.cpp*/
