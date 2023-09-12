////////////////////////////////////////////////////////////////////////////////
// Name: class gui:CMDStaticBox
// Desc: �ϳ��� �ؽ��� �̹����� ��� ���� ���� 
//       �پ��� ������ ��Ʈ, ������ �ؽ�Ʈ�� ���� �� �ִ�.
//		 
//
// 2006.04.12 Peessi@hitel.net   
//			 
////////////////////////////////////////////////////////////////////////////////

#ifndef __GUI_MDSTATICBOX_H__
#define __GUI_MDSTATICBOX_H__

#include "gui_component.h"
#include "gui_surface.h"

START_GUI

class CMDStaticBox_Generic;

class CMDStaticBox : public CComponent
{
public:
//! Construction & Destruction:
	CMDStaticBox( CComponent* pParent, CSurfaceManager* pSurfaceManager );
	CMDStaticBox( const CRectangle& rtRect, CComponent* pParent, CSurfaceManager* pSurfaceManager );
	virtual ~CMDStaticBox(VOID);

//! Operations:	
	VOID SetDefaultTextStyle( DWORD dwStyle );
	VOID SetDefaultTextColor( COLORREF color );
	VOID SetDefaultEffectColor( COLORREF color );
	VOID SetDefaultEffectMode( INT nMode );
	VOID SetDefaultEffectValue( INT nValue );
	VOID SetDefaultFont( DWORD dwFontIndex );

	VOID SetBkColor( COLORREF color, BOOL bRedraw = TRUE );
	VOID SetBkMode( INT nMode, BOOL bRedraw = TRUE );	

	VOID SetMinSize( INT nCX, INT nCY );			// �ּһ�����
	VOID SetMarginX( INT nMarginX );				// ���ο���
	VOID SetMarginY( INT nMarginY );				// ���ο���
	VOID SetInterval( INT nInterval );				// �ٰ�
	
	VOID SetBlankLine( INT nCY = -1 );				// Default�� ��� Default���� ������.
		
	INT  AddFont( const CHAR* pFontName, INT nHeight, INT nAttributes = 0 );

	// Cursor�� ��ġ�� ���� ���������� �Ʒ������� ��´�.
	VOID SetItem( const CHAR* szText, const CHAR* szName, DWORD dwFontIndex, DWORD dwStyle, COLORREF colorText, INT nX = 0, BOOL bAttachPrevLine = FALSE );
	VOID SetItem( const CHAR* szText, const CHAR* szName, DWORD dwFontIndex, DWORD dwStyle, COLORREF colorText, COLORREF colorEffect, INT nEffectMode, INT nEffectValue, INT nX = 0, BOOL bAttachPrevLine = FALSE );

	VOID SetItem( const WCHAR* szText, const CHAR* szName, DWORD dwFontIndex, DWORD dwStyle, COLORREF colorText, INT nX = 0, BOOL bAttachPrevLine = FALSE );
	VOID SetItem( const WCHAR* szText, const CHAR* szName, DWORD dwFontIndex, DWORD dwStyle, COLORREF colorText, COLORREF colorEffect, INT nEffectMode, INT nEffectValue,  INT nX = 0, BOOL bAttachPrevLine = FALSE );
	
	VOID SetItem( const INT nNumber, const CHAR* szName, DWORD dwFontIndex, DWORD dwStyle, COLORREF colorText, INT nX = 0, BOOL bAttachPrevLine = FALSE );
	VOID SetItem( const INT nNumber, const CHAR* szName, DWORD dwFontIndex, DWORD dwStyle, COLORREF colorText, COLORREF colorEffect, INT nEffectMode, INT nEffectValue,  INT nX = 0, BOOL bAttachPrevLine = FALSE );
	
	VOID Format( const CHAR* szName, DWORD dwFontIndex, DWORD dwStyle, COLORREF colorText, INT nX, BOOL bAttachPrevLine, const CHAR* format, ... );
	VOID Format( const CHAR* szName, DWORD dwFontIndex, DWORD dwStyle, COLORREF colorText, COLORREF colorEffect, INT nEffectMode, INT nEffectValue,  INT nX, BOOL bAttachPrevLine, const CHAR* format, ... );

	VOID Format( const CHAR* szName, DWORD dwFontIndex, DWORD dwStyle, COLORREF colorText, INT nX, BOOL bAttachPrevLine, const WCHAR* format, ... );
	VOID Format( const CHAR* szName, DWORD dwFontIndex, DWORD dwStyle, COLORREF colorText, COLORREF colorEffect, INT nEffectMode, INT nEffectValue,  INT nX, BOOL bAttachPrevLine, const WCHAR* format, ... );

	// X,Y��ǥ�� �����Ͽ� ��� �Լ�. 
	VOID SetItemXY( const CHAR* szText, const CHAR* szName, DWORD dwFontIndex, INT nX, INT nY, DWORD dwStyle, COLORREF colorText );
	VOID SetItemXY( const CHAR* szText, const CHAR* szName, DWORD dwFontIndex, INT nX, INT nY, DWORD dwStyle, COLORREF colorText, COLORREF colorEffect, INT nEffectMode, INT nEffectValue );

	VOID SetItemXY( const WCHAR* szText, const CHAR* szName, DWORD dwFontIndex, INT nX, INT nY, DWORD dwStyle, COLORREF colorText );
	VOID SetItemXY( const WCHAR* szText, const CHAR* szName, DWORD dwFontIndex, INT nX, INT nY, DWORD dwStyle, COLORREF colorText, COLORREF colorEffect, INT nEffectMode, INT nEffectValue );

	VOID SetItemXY( const INT nNumber, const CHAR* szName, DWORD dwFontIndex, INT nX, INT nY, DWORD dwStyle, COLORREF colorText );
	VOID SetItemXY( const INT nNumber, const CHAR* szName, DWORD dwFontIndex, INT nX, INT nY, DWORD dwStyle, COLORREF colorText, COLORREF colorEffect, INT nEffectMode, INT nEffectValue );

	VOID FormatXY( const CHAR* szName, DWORD dwFontIndex, INT nX, INT nY, DWORD dwStyle, COLORREF colorText, const CHAR* format, ... );
	VOID FormatXY( const CHAR* szName, DWORD dwFontIndex, INT nX, INT nY, DWORD dwStyle, COLORREF colorText, COLORREF colorEffect, INT nEffectMode, INT nEffectValue, const CHAR* format, ... );

	VOID FormatXY( const CHAR* szName, DWORD dwFontIndex, INT nX, INT nY, DWORD dwStyle, COLORREF colorText, const WCHAR* format, ... );
	VOID FormatXY( const CHAR* szName, DWORD dwFontIndex, INT nX, INT nY, DWORD dwStyle, COLORREF colorText, COLORREF colorEffect, INT nEffectMode, INT nEffectValue,  const WCHAR* format, ... );

	VOID DeleteItem( const CHAR* szName );

	VOID Clear(VOID);

	VOID DrawItem(VOID);	// Trigger

	//: Sets the surface.
	VOID AddSurface( CSurface Surface );
	
protected:
//! Variables:
	CMDStaticBox_Generic* m_pImpl;

private:
//! Etc
	CMDStaticBox( const CMDStaticBox& copy ) : CComponent( NULL, NULL ) { return; } // disallow copy construction.
	
	friend class CMDStaticBox_Generic;	
};

END_GUI

#endif
