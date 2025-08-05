/*dlg_main.cpp*/
/** @file
 *
 * @brief Main dialog box.
 * SPDX-License-Identifier: MIT
 *
 */
#include "pch.h"
#include "main.h"

HWND g_hwndLastActive;
HWND g_hwndHelp;
static RECT g_InitialClientRect;
static RECT g_InitialWindowRect;
RECT g_rcMainWindow;
uidgen::uuid	g_guid;

static inline void OnUpdateResult( HWND hwnd, HWND hwndChild );

/**
 * @brief Function called when GUID must be generated, formatted and displayed.
 *
 * @param[in] hwnd (HWND) handle to the main window.
 * @param[in] UseExisting (BOOL) flag that inhibits generation of new GUID so the function simply updates GUID representation string.
 *
 */
static inline void GenerateGuid( HWND hwnd, BOOL UseExisting )
{
	HWND hwndChild;
	BOOL bResult;

	// Get active generator and formatter
	hwndChild = GetDlgItem( hwnd, IDC_GUID_TYPE );
	uidgen::Igenerator* generator = (uidgen::Igenerator*) ComboBox_GetItemData( hwndChild, ComboBox_GetCurSel( hwndChild ) );
	if( nullptr == generator || (void *)CB_ERR == generator )
		return;

	hwndChild = GetDlgItem( hwnd, IDC_FORMAT_LIST );
	uidgen::Iformatter* formatter = (uidgen::Iformatter*) ComboBox_GetItemData( hwndChild, ComboBox_GetCurSel( hwndChild ) );
	if( nullptr == formatter || (void *)CB_ERR == formatter )
		return;

	g_uidgen_context->set_active_generator( generator );
	g_uidgen_context->set_active_formatter( formatter );

	// Prepare context
	char buffer[1024];

	GetDlgItemTextA( hwnd, IDC_USER_FORMAT_STRING, buffer, countof( buffer ) );
	g_uidgen_context->set_user_format_string( buffer );

	GetDlgItemTextA( hwnd, IDC_MANUAL_GUID, buffer, countof( buffer ) );
	g_uidgen_context->set_user_data( buffer );

	bResult = FALSE;
	unsigned UIntValue = (unsigned) GetDlgItemInt( hwnd, IDC_COUNT, &bResult, FALSE );
	if( bResult )
		g_uidgen_context->set_generation_count( UIntValue );

	// Generate string
	bool res;
	uidgen::string buf;
	uidgen::string msg_buf;
	HWND hwndCombo = GetDlgItem( hwnd, IDC_GUID );
	ComboBox_ResetContent( hwndCombo );
	g_uidgen_context->begin_generation();
	for( unsigned i = 0; g_uidgen_context->can_generate_more_uids(); ++ i )
	{
		buf.clear();
		if( UseExisting && 0 == i )		// if we need just ot reformat the GUID, do not generate the new one
			res = g_uidgen_context->reformat_last_uid( buf, msg_buf );
		else
			res = g_uidgen_context->generation_uid( buf, msg_buf );


		if( !res )
		{
			if( nullptr != g_uidgen_context->get_active_formatter() && g_uidgen_context->get_active_formatter()->get_uuid() != uidgen::user_string_formatter::m_uuid )
				MessageBoxA( NULL, "Error generating GUID with the specified generator", "Error", MB_OK | MB_ICONERROR );
			else
				SetDlgItemTextA( hwnd, IDC_RESULT, "Error: invalid format string" );
			SetDlgItemTextA( hwnd, IDC_RESULT, "" );
			break;
		}

		ComboBox_AddString( hwndCombo, buf.c_str() );
	}
	g_uidgen_context->end_generation();
	ComboBox_SetCurSel( hwndCombo, 0 );
	OnUpdateResult( hwnd, hwndCombo );

//	buf.clear();
//	formatter = g_uidgen_context->find_formatter( uidgen::registry_format_formatter::m_uuid );
//	formatter->format( buf, *g_uidgen_context, g_guid );
//	SetDlgItemTextA( hwnd, IDC_GUID, buf.c_str() );
}

/**
 * @brief Update GUID values.
 * @param[in] hwnd (HWND) the main dialog window handle.
 */
static inline void UpdateGuid( HWND hwnd )
{
	StoreConfig( hwnd );
	GenerateGuid( hwnd, TRUE );
}

/**
 * @brief Copy all strings from the GUID combo box.
 * @param[in] hwnd (HWND) the main dialog window handle.
 */
static inline void CopyString( HWND hwnd )
{
//	SendDlgItemMessage( hwnd, IDC_RESULT, EM_SETSEL, 0, -1 );
//	SendDlgItemMessage( hwnd, IDC_RESULT, WM_COPY, 0, 0 );
	uidgen::string result;
	HWND hwndCombo = GetDlgItem( hwnd, IDC_GUID );
	ComboBox_GatherAllStrings( hwndCombo, result );

	HGLOBAL hglbText = GlobalAlloc( GMEM_MOVEABLE | GMEM_DDESHARE, (result.length() + 1) * sizeof(TCHAR) );
	if( NULL == hglbText )
		return;
	LPVOID lptstrCopy = GlobalLock( hglbText ); 
	uidgen::memory::copy( lptstrCopy, result.c_str(), (result.length() + 1) * sizeof(TCHAR) );
	GlobalUnlock( hglbText );

	if( OpenClipboard( hwnd ) )
	{
		EmptyClipboard();
		HGLOBAL hPrevBlock = SetClipboardData( CF_TEXT, hglbText );
		if( NULL == hPrevBlock )
		{
			DWORD dwError = GetLastError();
			dwError = dwError;
		}
		CloseClipboard();
	}
}

/**
 * @brief List of all controls that can change size and/or position during resize of the parent window.
 *
 */
static control_info g_ctrl_list[] =
{
	{ IDC_GUID_TYPE,			CTRL_ANCHOR_TOP | CTRL_ANCHOR_LEFT | CTRL_ANCHOR_RIGHT },
	{ IDC_MANUAL_GUID,			CTRL_ANCHOR_TOP | CTRL_ANCHOR_LEFT | CTRL_ANCHOR_RIGHT },
	{ IDC_FORMAT_LIST,			CTRL_ANCHOR_TOP | CTRL_ANCHOR_LEFT | CTRL_ANCHOR_RIGHT },
	{ IDC_USER_FORMAT_STRING,	CTRL_ANCHOR_TOP | CTRL_ANCHOR_LEFT | CTRL_ANCHOR_BOTTOM | CTRL_ANCHOR_RIGHT },

	{ IDC_COUNT_TEXT,			CTRL_MOVE_TOP | CTRL_ANCHOR_BOTTOM | CTRL_ANCHOR_LEFT },
	{ IDC_COUNT,				CTRL_MOVE_TOP | CTRL_ANCHOR_BOTTOM | CTRL_ANCHOR_LEFT },
	{ IDC_SAVE,					CTRL_MOVE_LEFT | CTRL_MOVE_TOP | CTRL_ANCHOR_BOTTOM | CTRL_ANCHOR_RIGHT },

	{ IDC_GUID,					CTRL_MOVE_TOP | CTRL_ANCHOR_BOTTOM | CTRL_ANCHOR_LEFT | CTRL_ANCHOR_RIGHT },
	{ IDC_RESULT,				CTRL_MOVE_TOP | CTRL_ANCHOR_BOTTOM | CTRL_ANCHOR_LEFT | CTRL_ANCHOR_RIGHT },

	{ IDC_SETTINGS,				CTRL_MOVE_TOP | CTRL_ANCHOR_LEFT | CTRL_ANCHOR_BOTTOM },
	{ ID_GENERATE,				CTRL_MOVE_TOP | CTRL_ANCHOR_LEFT | CTRL_ANCHOR_BOTTOM },
	{ ID_COPY,					CTRL_MOVE_TOP | CTRL_ANCHOR_LEFT | CTRL_ANCHOR_BOTTOM },
	{ IDHELP,					CTRL_MOVE_LEFT | CTRL_MOVE_TOP | CTRL_ANCHOR_RIGHT | CTRL_ANCHOR_BOTTOM },
};


/**
 * @brief Callback called after the main dialog window size has changed.
 *
 * @param[in] hwnd (HWND) dialog window handle.
 */
static inline void OnSize( HWND hwnd )
{
	UpdatePositions( hwnd, g_ctrl_list, countof( g_ctrl_list ) );
}

/**
 * @brief Function called by those who wishes to update status of the GUID type.
 *
 * @param[in] hwnd (HWND) dialog window handle.
 * @param[in] hwndChild (HWND) handle to the format GUID type drop down.
 */
static inline void OnUpdateGuidType( HWND hwnd, HWND hwndChild )
{
	HWND hwndManualGuidEdit;

	int iCurSel = ComboBox_GetCurSel( hwndChild );
	if( -1 == iCurSel )
		return;
	hwndManualGuidEdit = GetDlgItem( hwnd, IDC_MANUAL_GUID );

	uidgen::Igenerator* generator = (uidgen::Igenerator*) ComboBox_GetItemData( hwndChild, iCurSel );
	EnableWindow(
		hwndManualGuidEdit,
		nullptr != generator && generator->get_uuid() == uidgen::manual_uuid_generator::m_uuid
	);

	if( GetWindowTextLength( hwndManualGuidEdit ) == 0 )
		SetWindowText( hwndManualGuidEdit, "00000000-0000-0000-0000-000000000000" );

	StoreConfig( hwnd );
}

/**
 * @brief Function called by those who wishes to update status of the GUID format.
 *
 * @param[in] hwnd (HWND) dialog window handle.
 * @param[in] hwndChild (HWND) handle to the format edit control.
 */
void OnUpdateGuidFormat( HWND hwnd, HWND hwndChild )
{
	int iCurSel = ComboBox_GetCurSel( hwndChild );
	if( -1 == iCurSel )
		return;

	uidgen::Iformatter* formatter = (uidgen::Iformatter*) ComboBox_GetItemData( hwndChild, iCurSel );
	EnableWindow(
		GetDlgItem( hwnd, IDC_USER_FORMAT_STRING ),
		nullptr != formatter && formatter->get_uuid() == uidgen::user_string_formatter::m_uuid
	);
	UpdateGuid( hwnd );
}

/**
 * @brief Function called when the selection in changed in the GUID list combo box.
 *
 * @param[in] hwnd (HWND) dialog window handle.
 * @param[in] hwndChild (HWND) handle to the format edit control.
 */
static inline void OnUpdateResult( HWND hwnd, HWND hwndChild )
{
	size_t nSize;
	int iCurSel = ComboBox_GetCurSel( hwndChild );
	if( -1 == iCurSel )
		return;

	nSize = ComboBox_GetLBTextLen( hwndChild, iCurSel );

	uidgen::string buf;
	if( !buf.resize( nSize ) )
		return;

	ComboBox_GetLBText( hwndChild, iCurSel, buf.data() );

	SetDlgItemTextA( hwnd, IDC_RESULT, buf.c_str() );
}

/**
* @brief Save data to file.
*
* @param[in] hwnd (HWND) dialog window handle.
*/
void OnSave( HWND hwnd )
{
	// Get the file name
	static TCHAR Buffer[_MAX_PATH + 1];
	static OPENFILENAME ofn;
	ofn.lStructSize = sizeof( ofn );
	ofn.hwndOwner = hwnd;
	ofn.hInstance = g_hInstance;
	ofn.lpstrFilter = "All Files\0*.*\0\0";
	ofn.lpstrFile = Buffer;
	ofn.nMaxFile = countof( Buffer ) - 1;
	ofn.Flags = OFN_ENABLESIZING | OFN_EXPLORER | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;
#ifdef OFN_DONTADDTORECENT
	ofn.Flags |= OFN_DONTADDTORECENT;
#endif // def OFN_DONTADDTORECENT
	if( FALSE == GetSaveFileName( &ofn ) )
		return;
	if( ofn.nMaxFile < countof( Buffer ) )
		Buffer[ofn.nMaxFile] = TEXT('\0');

	// Gather file data
	uidgen::string buf;
	ComboBox_GatherAllStrings( GetDlgItem( hwnd, IDC_GUID ), buf );

	// Write file data
	HANDLE hFile = CreateFile( Buffer, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
	if( INVALID_HANDLE_VALUE == hFile )
	{
		MessageBox( hwnd, "Cannot create file.", "Error", MB_OK | MB_ICONERROR );
		return;
	}
	DWORD nWritten;
	WriteFile( hFile, buf.data(), (DWORD) buf.size(), &nWritten, NULL );
	CloseHandle( hFile );

	// Exit
	return;
}

/**
 * @brief Dialog initialization handler procedure.
 *
 * @param[in] hwnd (HWND) dialog window handle.
 */
static inline void OnInitDialog( HWND hwnd )
{
	HWND hwndChild;
	int iCurSel;

	// Set icon
	HICON hico;
	hico = LoadIcon( g_hInstance, MAKEINTRESOURCE( IDI_MAIN_BIG ) );
	SendMessage( hwnd, WM_SETICON, ICON_BIG, LPARAM( hico ) );
	DestroyIcon( hico );
	hico = LoadIcon( g_hInstance, MAKEINTRESOURCE( IDI_MAIN_SMALL ) );
	SendMessage( hwnd, WM_SETICON, ICON_SMALL, LPARAM( hico ) );
	DestroyIcon( hico );

	// Initialize list of auto-resizeable controls
	InitPositions( hwnd, g_ctrl_list, countof( g_ctrl_list ), &g_InitialClientRect, &g_InitialWindowRect );
	if( 0 != g_rcMainWindow.right )
		MoveWindow( hwnd, g_rcMainWindow.left, g_rcMainWindow.top, g_rcMainWindow.right - g_rcMainWindow.left, g_rcMainWindow.bottom - g_rcMainWindow.top, TRUE );
	else
		GetWindowRect( hwnd, &g_rcMainWindow );

	// Initialize type list
	uidgen::Igenerator * generator = nullptr;
	hwndChild = GetDlgItem( hwnd, IDC_GUID_TYPE );
	if( NULL != hwndChild )
	{
		for( uidgen::generator_list_t::const_iterator it = g_uidgen_context->get_generator_list().begin(), st = g_uidgen_context->get_generator_list().end(); it != st; ++ it )
		{
			uidgen::string buf;
			(*it)->get_string( buf, uidgen::Igenerator::sid_description );
			ComboBox_SetItemData( hwndChild, ComboBox_AddString( hwndChild, buf.c_str() ), *it );
			if( (*it)->get_uuid() == uidgen::random_uuid_generator::m_uuid )
				generator = *it;
		}
		iCurSel = ComboBox_FindItemByData( hwndChild, 0, DWORD_PTR( generator ) );
		ComboBox_SetCurSel( hwndChild, -1 != iCurSel ? iCurSel : 0 );
		OnUpdateGuidType( hwnd, hwndChild );
	}

	// Initialize format list
	uidgen::Iformatter * formatter = nullptr;
	hwndChild = GetDlgItem( hwnd, IDC_FORMAT_LIST );
	if( NULL != hwndChild )
	{
		for( uidgen::formatter_list_t::const_iterator it = g_uidgen_context->get_formatter_list().begin(), st = g_uidgen_context->get_formatter_list().end(); it != st; ++ it )
		{
			uidgen::string buf;
			(*it)->get_string( buf, uidgen::Iformatter::sid_description );
			ComboBox_SetItemData( hwndChild, ComboBox_AddString( hwndChild, buf.c_str() ), *it );
			if( (*it)->get_uuid() == uidgen::registry_format_formatter::m_uuid )
				formatter = *it;
		}
		iCurSel = ComboBox_FindItemByData( hwndChild, 0, DWORD_PTR( formatter ) );
		ComboBox_SetCurSel( hwndChild, -1 != iCurSel ? iCurSel : 0 );
		OnUpdateGuidFormat( hwnd, hwndChild );
	}

	// Initialize other controls
	SetDlgItemInt( hwnd, IDC_COUNT, g_uidgen_context->get_generation_count(), FALSE );

	// Automatically generate new GUID
	GenerateGuid( hwnd, FALSE );
}

/**
 * @brief Measure simensions of an owner-draw item.
 * @param[in] hwnd (HWND) the main dialog window handle.
 * @param[in] hwndCombo (HWND) the ComboBox window handle.
 * @param[in] lpmis (LPMEASUREITEMSTRUCT) pointer to the MEASUREITEMSTRUCT.
 */
static inline void OnMeasureItem( HWND hwnd, HWND hwndCombo, LPMEASUREITEMSTRUCT lpmis )
{
	int nSize;
	uidgen::string buf;
	int iItem = lpmis->itemID;

	if( -1 == iItem )
	{
		//	iItem = ComboBox_GetCurSel( hwndCombo );
		/*nSize = GetWindowTextLengthA( hwndCombo );
		if( !buf.resize( nSize ) )
			return;
		GetWindowTextA( hwndCombo, buf.data(), buf.size() );*/
		//RECT rcCtrl;
		//GetClientRect( hwndCombo, &rcCtrl );
		//lpmis->itemWidth = rcCtrl.right - rcCtrl.left;
		//lpmis->itemHeight = 12;// rcCtrl.bottom - rcCtrl.top;
		//return;
		buf = "1";
	}
	else
	{
		nSize = ComboBox_GetLBTextLen( hwndCombo, lpmis->itemID );
		if( !buf.resize( nSize ) )
			return;
		ComboBox_GetLBText( hwndCombo, lpmis->itemID, buf.data() );
	}

	HDC hdc = GetDC( hwndCombo );
//	HFONT hFont = (HFONT) SendMessage( hwnd, WM_GETFONT, 0, 0 );
//	HFONT hOldFont = (HFONT) SelectObject( hdc, hFont );

	SIZE size = { 0, 0 };
	RECT rc = { 0, 0, 0, 0 };
	DrawText( hdc, buf.c_str() , (int) buf.length(), &rc, DT_CALCRECT | DT_EDITCONTROL);
	size.cx = rc.right - rc.left;
	size.cy = rc.bottom - rc.top;
	//GetTextExtentPoint32A( hdc, buf.c_str(), (int) buf.length(), &size ); 

//	SelectObject( hdc, hOldFont );
	ReleaseDC( hwndCombo, hdc );

	lpmis->itemWidth = size.cx;
	lpmis->itemHeight = max( lpmis->itemHeight, (DWORD) size.cy );

	UNREFERENCED_PARAMETER( hwnd );
	return;
}

/// Colors of the odd and even lines in the GUIDs combo box.
static DWORD rgbLineColor[2] =
{
	0x00000000,
	0x00CFCFCF
};
/**
 * @brief Draw an owner-draw item.
 * @param[in] hwnd (HWND) the main dialog window handle.
 * @param[in] hwndCombo (HWND) the ComboBox window handle.
 * @param[in] lpdis (LPDRAWITEMSTRUCT) pointer to the DRAWITEMSTRUCT.
 */
static inline void OnDrawItem( HWND hwnd, HWND hwndCombo, LPDRAWITEMSTRUCT lpdis )
{
	int nSize;
	uidgen::string buf;
	int iItem = lpdis->itemID;
	COLORREF clrBackground;
	COLORREF clrForeground;

	// The colors depend on whether the item is selected.
	clrForeground = SetTextColor(lpdis->hDC, 
		GetSysColor(lpdis->itemState & ODS_SELECTED ?
			COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT));

	clrBackground = SetBkColor(lpdis->hDC, 
		GetSysColor(lpdis->itemState & ODS_SELECTED ?
			COLOR_HIGHLIGHT : COLOR_WINDOW));

	// Set font
//	HFONT hFont = (HFONT) SendMessage( hwnd, WM_GETFONT, 0, 0 );
//	HFONT hOldFont = (HFONT) SelectObject( lpdis->hDC, hFont );

	// Get text
	if( -1 == iItem )
	{
		nSize = GetWindowTextLengthA( hwndCombo );
		if( !buf.resize( nSize ) )
			return;
		GetWindowTextA( hwndCombo, buf.data(), (int) buf.size() );

		char * s;
		for( s = buf.c_str(); '\0' != *s; ++ s )
		{
			if( '\n' == *s || '\r' == *s )
				break;
		}
		buf.resize( s - buf.c_str() );
	}
	else
	{
		nSize = ComboBox_GetLBTextLen( lpdis->hwndItem, iItem );
		if( !buf.resize( nSize ) )
			return;
		ComboBox_GetLBText( lpdis->hwndItem, iItem, buf.data() );
	}

	RECT rcDrop;
	GetClientRect( hwnd, &rcDrop );

	if( 0 == rgbLineColor[0] )
		rgbLineColor[0] = GetSysColor( COLOR_WINDOW );

	DWORD dwColor = lpdis->itemState & ODS_SELECTED ?
		GetSysColor( COLOR_HIGHLIGHT ) :
		rgbLineColor[iItem & 1];
	HBRUSH hbr = CreateSolidBrush( dwColor );
	FillRect( lpdis->hDC, &lpdis->rcItem, hbr );
	DeleteObject( hbr );

	RECT rcItem = lpdis->rcItem;
	if( -1 != iItem )	// center text vertically; DT_VCENTER works only for DT_SINGLELINE
	{
		DrawText( lpdis->hDC, buf.c_str(), (int) buf.length(), &rcItem, DT_NOPREFIX | DT_CALCRECT );
		int y = (lpdis->rcItem.bottom - rcItem.bottom) / 2;
		if( y < 0 )
			y = 0;
		OffsetRect( &rcItem, 5, y );
	}

	int OldBkMode = SetBkMode( lpdis->hDC, TRANSPARENT );
	DrawText( lpdis->hDC, buf.c_str(), (int) buf.length(), &rcItem, DT_NOPREFIX  );
//	ExtTextOut(lpdis->hDC, x, y,
//		ETO_CLIPPED | ETO_OPAQUE, &lpdis->rcItem,
//		buf.c_str(), (int) buf.length(), NULL );

	if( lpdis->itemState & ODS_FOCUS )
		DrawFocusRect( lpdis->hDC, &lpdis->rcItem );

	// Restore the previous colors.
	SetBkMode( lpdis->hDC, OldBkMode );

	SetTextColor( lpdis->hDC, clrForeground );
	SetBkColor( lpdis->hDC, clrBackground );

//	SelectObject( lpdis->hDC, hOldFont );
}

/**
 * @brief Main dialog procedure.
 *
 * @param[in] hwnd (HWND) dialog window handle.
 * @param[in] uMsg (UINT) message identifier.
 * @param[in] wParam (WPARAM) 1st message parameter.
 * @param[in] lParam (WPARAM) 2nd message parameter.
 *
 * @return (INT_PTR) return value depends on the message sent.
 */
INT_PTR CALLBACK MainDialogProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
	case WM_INITDIALOG:
		OnInitDialog( hwnd );
		break;
	case WM_DESTROY:
		g_hwndMain = NULL;
		PostQuitMessage( 0 );
		return FALSE;
	case WM_CLOSE:
		StoreConfig( hwnd );
		DestroyWindow( hwnd );
		break;
	case WM_GETMINMAXINFO:{
		MINMAXINFO* mmi = (MINMAXINFO*) lParam;
		mmi->ptMinTrackSize.x = g_InitialWindowRect.right - g_InitialWindowRect.left;
		mmi->ptMinTrackSize.y = g_InitialWindowRect.bottom - g_InitialWindowRect.top;
		}return FALSE;
	case WM_NCHITTEST:{
		int lResult = (int) DefWindowProc( hwnd, uMsg, wParam, lParam );
		::SetWindowLongPtr( hwnd, DWLP_MSGRESULT, HTCLIENT == lResult ? HTCAPTION : lResult );
		}break;
	case WM_SIZE:
		switch( wParam )
		{
		case SIZE_MINIMIZED:
			if( gSystemFlags & SF_MINIMIZE_TO_TRAY )
			{
				UpdateTrayIcon( FALSE );
				ShowWindow( hwnd, SW_HIDE );
			}
			return FALSE;
		case SIZE_MAXIMIZED:
		case SIZE_RESTORED:
		default:
			ShowWindow( hwnd, SW_SHOW );
			break;
		}
		OnSize( hwnd );
		GetWindowRect( hwnd, &g_rcMainWindow );
		break;
	case WM_MOVE:
		if( 0 <= (short) HIWORD(lParam) && 0 <= (short) LOWORD(lParam) )
			GetWindowRect( hwnd, &g_rcMainWindow );
		return FALSE;
	case WM_ACTIVATE:
		if( WA_INACTIVE == LOWORD( wParam ) && NULL != lParam )
			g_hwndLastActive = (HWND) lParam;
		if( WA_INACTIVE != LOWORD( wParam ) && NULL != lParam )
			g_hwndLastActive = (HWND) lParam;
		break;
	case WM_SYSCOMMAND:
		switch( wParam )
		{
		case ID_ABOUT:
			DialogBox( g_hInstance, MAKEINTRESOURCE( IDD_ABOUT ), hwnd, AboutDialogProc );
			return TRUE;
		}
		return FALSE;
	case WM_COMMAND:
		switch( LOWORD( wParam ) )
		{
		case IDCANCEL:
			if( gSystemFlags & SF_ESC_CLOSES_APP )
				SendMessage( hwnd, WM_CLOSE, 0, 0 );
			else
				CloseWindow( hwnd );
			SetForegroundWindow( g_hwndLastActive );
			SetActiveWindow( g_hwndLastActive );
			SetFocus( g_hwndLastActive );
			break;
		case IDOK:
		case IDCLOSE:
			SendMessage( hwnd, WM_CLOSE, 0, 0 );
			break;
		case ID_GENERATE:
			GenerateGuid( hwnd, FALSE );
			CopyString( hwnd );
			break;
		case ID_COPY:
			CopyString( hwnd );
			break;
		case IDHELP:
			//DialogBox( g_hInstance, MAKEINTRESOURCE( IDD_HELP ), hwnd, HelpDialogProc );
			if( NULL == g_hwndHelp )
				CreateDialog( g_hInstance, MAKEINTRESOURCE( IDD_HELP ), hwnd, HelpDialogProc );
			else
				SetForegroundWindow( g_hwndHelp );
			break;
		case IDC_GUID_TYPE:
			if( CBN_SELCHANGE == HIWORD( wParam ) )
			{
				GenerateGuid( hwnd, FALSE );
				OnUpdateGuidType( hwnd, (HWND) lParam );
			}
			break;
		case IDC_FORMAT_LIST:
			if( CBN_SELCHANGE == HIWORD( wParam ) )
				OnUpdateGuidFormat( hwnd, (HWND) lParam );
			break;
		case IDC_GUID:
			if( CBN_SELCHANGE == HIWORD( wParam ) )
				OnUpdateResult( hwnd, (HWND) lParam );
			break;
		case IDC_REMOVE_LEADING_ZEROES:
			if( BN_CLICKED == HIWORD( wParam ) )
				UpdateGuid( hwnd );
			break;
		case IDC_USE_ANGLE_BRACKETS:
			if( BN_CLICKED == HIWORD( wParam ) )
				UpdateGuid( hwnd );
			break;
		case IDC_USER_FORMAT_STRING:
			if( EN_CHANGE == HIWORD( wParam ) )
				UpdateGuid( hwnd );
			break;
		case IDC_MANUAL_GUID:
			if( EN_CHANGE == HIWORD( wParam ) )
				UpdateGuid( hwnd );
			break;
		case IDC_SETTINGS:
			DialogBox( g_hInstance, MAKEINTRESOURCE( IDD_OPTIONS ), hwnd, SettingsDialogProc );
			break;
		case IDC_SAVE:
			OnSave( hwnd );
			break;
		case ID_SHOW_WINDOW:
			ShowWindow( g_hwndMain, SW_RESTORE );
			OpenIcon( g_hwndMain );
			SetForegroundWindow( g_hwndMain );
			break;
		default:
			return FALSE;
		}
		break;
	case WM_MEASUREITEM:
		OnMeasureItem( hwnd, GetDlgItem( hwnd, ((LPMEASUREITEMSTRUCT) lParam)->CtlID ), (LPMEASUREITEMSTRUCT) lParam );
		break;
	case WM_DRAWITEM:
		OnDrawItem( hwnd, (HWND) wParam, (LPDRAWITEMSTRUCT) lParam );
		break;
	case WM_NOTIFYICON:
		switch( lParam )
		{
		case WM_LBUTTONDBLCLK:
			ShowWindow( g_hwndMain, SW_RESTORE );
			OpenIcon( g_hwndMain );
			SetForegroundWindow( g_hwndMain );
			return 0;
		case WM_RBUTTONUP:
		case WM_CONTEXTMENU:
			POINT pt;
			HMENU hMenu, hSubMenu;
			GetCursorPos( &pt );
			hMenu = LoadMenu( g_hInstance, MAKEINTRESOURCE(IDM_NOTIFYICON_MENU) );
			hSubMenu = GetSubMenu( hMenu, 0 );
			SetForegroundWindow( hwnd );
			TrackPopupMenu( hSubMenu, TPM_LEFTBUTTON | TPM_LEFTALIGN | TPM_BOTTOMALIGN, pt.x, pt.y, 0, hwnd, NULL );
			DestroyMenu( hMenu);
			PostMessage( hwnd, WM_NULL, 0, 0 );
			return 0;
		}
		break;
	case WM_HOTKEY:
		switch( wParam )
		{
		case IDC_GLOBAL_HOOK_KEY:
			ShowWindow( g_hwndMain, SW_RESTORE );
			OpenIcon( g_hwndMain );
			SetForegroundWindow( g_hwndMain );
			break;
		case IDC_GENERATOR_HOOK_KEY:
			GenerateGuid( hwnd, FALSE );
			CopyString( hwnd );
			break;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

/*END OF dlg_main.cpp*/
