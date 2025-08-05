/*args.cpp*/
/** @file
 *
 * @brief Miscelaneous GUI functions.
 * SPDX-License-Identifier: MIT
 *
 */
#include "pch.h"
#include "main.h"

/**
 * @brief Gather all lines in the ComboBox into a string, separating them with new-lines.
 * @param[in] hwndCombo (HWND) ComboBox window handle.
 * @param[in] result (uidgen::string &) buffer where a ll strings are stored to.
 */
void ComboBox_GatherAllStrings( HWND hwndCombo, uidgen::string & result )
{
	int iItem, nItems = ComboBox_GetCount( hwndCombo );
	for( iItem = 0; iItem < nItems; ++ iItem )
	{
		int nSize = ComboBox_GetLBTextLen( hwndCombo, iItem );

		uidgen::string buf;
		if( !buf.resize( nSize ) )
			return;

		ComboBox_GetLBText( hwndCombo, iItem, buf.data() );

		result.append( buf );
		result.append( '\r' );
		result.append( '\n' );
	}
}

/**
 * @brief Find item by the user data value.
 * @param[in] hwndCombo (HWND) ComboBox window handle.
 * @param[in] iStartIndex (int) index of the first item to perform search from.
 * @param[in] Data (DWORD_PTR) user data.
 * @return (int) zero-based index of the item or CB_ERR on error.
 */
int ComboBox_FindItemByData( HWND hwndCombo, int iStartIndex, DWORD_PTR Data )
{
	int nItems = ComboBox_GetCount( hwndCombo );
	for( ; iStartIndex < nItems; ++ iStartIndex )
	{
		if( Data == (DWORD_PTR) ComboBox_GetItemData( hwndCombo, iStartIndex ) )
			return iStartIndex;
	}
	return CB_ERR;
}

/**
 * @brief Initialize dialog controls positions.
 * @param[in] hwnd (HWND) handle to the dialog window.
 * @param[in] ctrl_list (control_info *) list of control descriptors.
 * @param[in] count (size_t) number of controls.
 * @param[out] prcInitialClient (RECT *) pointer to the variable receiving initial client coordinates.
 * @param[out] prcInitialWindow (RECT *) pointer to the variable receiving initial window coordinates.
 */
void InitPositions( HWND hwnd, control_info * ctrl_list, size_t count, RECT * prcInitialClient, RECT * prcInitialWindow )
{
	GetClientRect( hwnd, prcInitialClient );
	GetWindowRect( hwnd, prcInitialWindow );

	for( size_t i = 0; i < count; ++ i )
	{
		HWND hwndChild = GetDlgItem( hwnd, ctrl_list[i].m_id );
		if( NULL == hwndChild )
			continue;

		RECT rcChild;
		GetWindowRect( hwndChild, &rcChild );
		MapWindowPoints( HWND_DESKTOP, hwnd, (LPPOINT) &rcChild, sizeof( rcChild ) / sizeof( POINT ) );

		ctrl_list[i].m_initial_size.cx = rcChild.right - rcChild.left;
		ctrl_list[i].m_initial_size.cy = rcChild.bottom - rcChild.top;

		ctrl_list[i].m_margins.left = rcChild.left;
		ctrl_list[i].m_margins.top = rcChild.top;
		ctrl_list[i].m_margins.right = prcInitialClient->right - rcChild.right;
		ctrl_list[i].m_margins.bottom = prcInitialClient->bottom - rcChild.bottom;
	}
}
/**
 * @brief Initialize dialog controls positions.
 * @param[in] hwnd (HWND) handle to the dialog window.
 * @param[in] ctrl_list (control_info *) list of control descriptors.
 * @param[in] count (size_t) number of controls.
 */
void UpdatePositions( HWND hwnd, control_info * ctrl_list, size_t count )
{
	RECT rc;
	HDWP hdwp = BeginDeferWindowPos( (int) count );
	GetClientRect( hwnd, &rc );
	for( size_t i = 0; i < count; ++ i )
	{
		HWND hwndChild = GetDlgItem( hwnd, ctrl_list[i].m_id );
		if( NULL == hwndChild )
			continue;

		RECT rcChild;
		GetWindowRect( hwndChild, &rcChild );
		MapWindowPoints( HWND_DESKTOP, hwnd, (LPPOINT) &rcChild, sizeof( rcChild ) / sizeof( POINT ) );

		if( ctrl_list[i].m_flags & CTRL_ANCHOR_TOP )
			rcChild.top = rc.top + ctrl_list[i].m_margins.top;
		if( ctrl_list[i].m_flags & CTRL_ANCHOR_LEFT )
			rcChild.left = rc.left + ctrl_list[i].m_margins.left;
		if( ctrl_list[i].m_flags & CTRL_ANCHOR_BOTTOM )
			rcChild.bottom = rc.bottom - ctrl_list[i].m_margins.bottom;
		if( ctrl_list[i].m_flags & CTRL_ANCHOR_RIGHT )
			rcChild.right = rc.right - ctrl_list[i].m_margins.right;

		if( ctrl_list[i].m_flags & CTRL_MOVE_LEFT )
			rcChild.left = rcChild.right - ctrl_list[i].m_initial_size.cx;
		if( ctrl_list[i].m_flags & CTRL_MOVE_TOP )
			rcChild.top = rcChild.bottom - ctrl_list[i].m_initial_size.cy;

		DeferWindowPos( hdwp, hwndChild, NULL, rcChild.left, rcChild.top, rcChild.right - rcChild.left, rcChild.bottom - rcChild.top, SWP_NOZORDER );
	}
	InvalidateRect( hwnd, NULL, FALSE );
	EndDeferWindowPos( hdwp );
}

/**
 * @brief Place the window in the center of the parent window.
 * @param[in] hwndWindow (HWND) the window which position must be centered.
 */
BOOL CenterWindow( HWND hwndWindow )
{
	HWND hwndParent;
	RECT rectWindow, rectParent;

	// make the window relative to its parent
	if ((hwndParent = GetParent(hwndWindow)) != NULL)
	{
		GetWindowRect(hwndWindow, &rectWindow);
		GetWindowRect(hwndParent, &rectParent);

		int nWidth = rectWindow.right - rectWindow.left;
		int nHeight = rectWindow.bottom - rectWindow.top;

		int nX = ((rectParent.right - rectParent.left) - nWidth) / 2 + rectParent.left;
		int nY = ((rectParent.bottom - rectParent.top) - nHeight) / 2 + rectParent.top;

		int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

		// make sure that the dialog box never moves outside of the screen
		if (nX < 0) nX = 0;
		if (nY < 0) nY = 0;
		if (nX + nWidth > nScreenWidth) nX = nScreenWidth - nWidth;
		if (nY + nHeight > nScreenHeight) nY = nScreenHeight - nHeight;

		MoveWindow(hwndWindow, nX, nY, nWidth, nHeight, FALSE);

		return TRUE;
	}

	return FALSE;
}

/*END OF args.cpp*/
