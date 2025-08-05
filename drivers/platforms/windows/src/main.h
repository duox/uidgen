/*main.h*/
#pragma once

#include "resource.h"

#define UIDGEN_VERSION		"0.3.0"

void	ProcessCmdLineArgs( INT ArgCount, LPCSTR * Args );

extern STARTUPINFO gStartupInfo;
extern uidgen::context	* g_uidgen_context;
extern HWND g_hwndMain;				//< handle to the main dialog window
extern HACCEL g_haccMain;			//< handle to accelerator table
extern HINSTANCE g_hInstance;		//< handle to the application module instance
extern HWND g_hwndLastActive;		//< handle to the popup that was active before the UidGen window popped up
extern HWND g_hwndHelp;				//< handle to the modeless Help dialog window

extern RECT g_rcMainWindow;			//< current coordinates of the main dialog window
extern RECT g_rcSettingsWindow;		//< current coordinates of the settings dialog window
extern RECT g_rcHelpWindow;			//< current coordinates of the help dialog window


#define SF_REQUEST_EXIT			0x0001	//< application is requested to exit as fast as possible
#define SF_HELP_PRINTED			0x0002	//< command line help has already been displayed
#define SF_FORCE_CONSOLE		0x0004	//< ignore mode auto-detection; use console mode
#define SF_FORCE_GUI			0x0008	//< ignore mode auto-detection; use GUI mode
#define SF_MINIMIZE_TO_TRAY		0x0010	//< minimize application to the tray
#define SF_ESC_MINIMIZES_APP	0x0020	//< pressing Esc makes application minimize
#define SF_ESC_CLOSES_APP		0x0040	//< pressing Esc makes application close
#define SF_WINDOW_HOOK			0x0080	//< window key hook installed
#define SF_GENERATOR_HOOK		0x0100	//< generation key hook installed
extern DWORD	gSystemFlags;		//< general application state flags
extern UINT		gWindowHotKey;		//< hot key used for popping up the application window (in format returned by the HotKeyCtrl control)
extern UINT		gGeneratorHotKey;	//< hot key used for generating GUID(s) in background (in format returned by the HotKeyCtrl control)

void	PxCmdlineParse( LPCSTR SrcCmdLine, INT * OutArgCount, LPCSTR ** OutArgs );

PVOID UIDGEN_API MmHeapAlloc( SIZE_T Size );
PVOID UIDGEN_API MmHeapRealloc( PVOID Block, SIZE_T Size );
BOOL UIDGEN_API MmHeapReallocPtr( PVOID* Block, SIZE_T Size );
VOID UIDGEN_API MmHeapFree( PVOID Block );

DWORD ConsoleMain( void );

void StoreConfig( HWND hwnd );
BOOL LoadConfig( HWND hwnd );
void DeleteConfig( HWND hwnd );

BOOL UpdateHookKey();

BOOL UpdateTrayIcon( BOOL Destroy );
#define WM_NOTIFYICON		(WM_APP + 1)	//< message used for receiving data from the tray icon

BOOL CenterWindow( HWND hwndWindow );

void OnUpdateGuidFormat( HWND hwnd,HWND hwndChild );

void LoadPlugins();

BOOL UIDGEN_API IsConsoleApp( void );
SIZE_T UIDGEN_API ConsolePrintf( PCSTR Format, ... );
SIZE_T UIDGEN_API ConsoleVPrintf( PCSTR Format, va_list ap );
SIZE_T UIDGEN_API ConsolePrint( PCSTR String, SIZE_T Count );
#define ConsolePrintString( String )	ConsolePrint( String, (SIZE_T) -1 )

// GUI operations
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

INT_PTR CALLBACK MainDialogProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
INT_PTR CALLBACK HelpDialogProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
INT_PTR CALLBACK SettingsDialogProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
INT_PTR CALLBACK AboutDialogProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

void ComboBox_GatherAllStrings( HWND hwndCombo, uidgen::string & result );
int ComboBox_FindItemByData( HWND hwndCombo, int iStartIndex, DWORD_PTR Data );

/**
 * @brief Flags specifying behavior of child windows.
 */
//{
static const unsigned CTRL_ANCHOR_TOP	= 0x0001;	//< keep window top border at the same offset to the parent top border
static const unsigned CTRL_ANCHOR_LEFT	= 0x0002;	//< keep window left border at the same offset to the parent left border
static const unsigned CTRL_ANCHOR_BOTTOM= 0x0004;	//< keep window bottom border at the same offset to the parent bottom border
static const unsigned CTRL_ANCHOR_RIGHT = 0x0008;	//< keep window right border at the same offset to the parent right border
static const unsigned CTRL_MOVE_TOP		= 0x0010;	//< keep window top/bottom borders at the same offset to the parent top border
static const unsigned CTRL_MOVE_LEFT	= 0x0020;	//< keep window left/right border at the same offset to the parent left border
//}
/**
 * @brief Structure that defines all information types required to keep child window size and position synchronized.
 *
 */
struct control_info
{
	unsigned	m_id;			//< control identifier
	unsigned	m_flags;		//< behavior flags (see CTRL_* flags)
	RECT		m_margins;		//< control initial distances to parent sides for all four sides
	SIZE		m_initial_size;	//< initial size of control
};

void InitPositions( HWND hwnd, control_info * ctrl_list, size_t count, RECT * rcInitialClient, RECT * prcInitialWindow );
void UpdatePositions( HWND hwnd, control_info * ctrl_list, size_t count );

/*END OF main.h*/
