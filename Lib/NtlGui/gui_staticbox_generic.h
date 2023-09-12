#ifndef __GUI_STATICBOX_GENERIC_H__
#define __GUI_STATICBOX_GENERIC_H__

#include "gui_staticbox.h"
#include "gui_outputbox_item.h"
#include "gui_staticbox_item.h"

START_GUI

class CFont;

class CStaticBox_Generic
{
public:

	typedef std::list<CSurface>						LIST_SURFACE;
	typedef std::list<CSurface>::iterator			LIST_SURFACE_IT;
	typedef std::list<CStaticBox_Item*>				LIST_ITEM;
	typedef std::list<CStaticBox_Item*>::iterator	LIST_ITEM_IT;


	CStaticBox_Generic(CStaticBox *pSelf, DWORD dwStyle, BOOL bDynamic);
	~CStaticBox_Generic(VOID);

	CStaticBox*		m_pStaticBox;

	LIST_SURFACE	m_stlSurface;
	CSurface		m_TextSurface;

	CGuiFont*		m_pFont;
	DWORD			m_dwStyle;
	COLORREF		m_Color;
	INT				m_nBkMode;
	COLORREF		m_BkColor;	
	INT				m_nEffectMode;
	COLORREF		m_effectColor;
	INT				m_nEffectValue;
	std::string		m_strFont;
	INT				m_nFontH;
	INT				m_nFontAttribute;
	BOOL			m_bDynamic;			// Dynamically adjust window size.
	INT				m_nMaxCX;			// Dynamic�� �ִ� ��
	INT				m_nMaxCY;			// Dynamic�� �ִ� ����.
	INT				m_nMinCX;			// Dynamic�� �ּ� ��.
	INT				m_nMinCY;			// Dynamic�� �ּ� ����.
	INT				m_nTextureWidth;
	INT				m_nTextureHeight;
	INT				m_nMarginX;
	INT				m_nMarginY;
	INT				m_nLineSpace;		// Line.
	
	BYTE			m_ucAlpha;				// Alpha���尪.
	BYTE			m_ucTexturePosOffset;	// Shadow, Outline������ ���� �߻��Ǵ� �ý��� ������ ������. 
	BYTE			m_ucTextureSizeOffset;

	LIST_ITEM		m_listItem;
	CUniBuffer		*m_pBuffer;

private:

	VOID AdjustRectToString(VOID);			
	VOID StringDetect(VOID);
	INT	 GetStartPosX( CUniBuffer* pBuffer );
	INT	 GetStartPosY( INT nTotLine, INT nCurrLine );
	VOID ItemClear(VOID);
	
	INT	 CalcCurrentHeight( INT nTotalLine );
	INT	 GetTextRegionWidth(VOID);
	INT	 GetTextRegionHeight(VOID);	

	inline VOID SetTextTexturePos( CRectangle& rect );

public:

	//-------------------------------------------------------------------------
	//: font Create
	VOID CreateFont( CHAR* pFaceName, INT nHeight, INT nAttributes = 0 );
	VOID CreateFont(VOID);

	VOID Clear(VOID);

	VOID SetText( const CHAR* text );		
	VOID SetText( const WCHAR* text );
	VOID AddText( const CHAR* text );		
	VOID AddText( const WCHAR* text );

	VOID SetMargin( INT nMarginX, INT nMarginY );	// Font������ Margin������. ���������� �ڵ����� �Էµȴ�.
	VOID SetEffectMode( INT nEffectMode, BOOL bSurfaceChange = TRUE );
	VOID SetEffectValue( INT nEffectValue, BOOL bSurfaceChange = TRUE );

	VOID DrawItem(VOID);

	VOID Render(VOID);

	VOID SetTextSurface( CRectangle rcScreen );

	INT  GetFitWidthToString(VOID);					// �ؽ�Ʈ ��ü�� ���� + Margin�� ������ ��������.
	INT  GetFitHeightToString(VOID);

	VOID Redraw(VOID);

// callback function
private:

	VOID OnSetOptions( const CComponentOptions& options );
	VOID OnScrollChange( INT nValue );
	VOID OnMove( INT nOldX, INT nOldY );
	VOID OnResize( INT nOldCX, INT nOldCY );
	VOID OnSetAlpha( BYTE ucAlpha );
	VOID OnSetColor( BYTE ucRed, BYTE ucGreen, BYTE ucBlue );

	CSlot m_SlotSetOptions;
	CSlot m_SlotMove;
	CSlot m_SlotResize;
	CSlot m_SlotSetAlpha;
	CSlot m_SlotSetColor;
};

END_GUI

#endif
