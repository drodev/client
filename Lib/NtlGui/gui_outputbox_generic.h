#ifndef __GUI_OUTPUTBOX_GENERIC_H__
#define __GUI_OUTPUTBOX_GENERIC_H__

#include "gui_outputbox.h"
#include "gui_outputbox_item.h"

START_GUI

class CFont;
class COutputBox_Item;

class COutputBox_Generic
{
public:
//! Construction & Desstruction
	COutputBox_Generic( COutputBox *pSelf, INT nMaxLine, INT nMarginX, INT nMarginY, 
						bool bDynamicScrollBar, bool bScrollBarLeft, DWORD dwStyle );
	~COutputBox_Generic(VOID);

//! Opreations
	VOID Clear(VOID);
	
	VOID CreateFont( CHAR* pFaceName, INT nHeight, INT nAttributes = 0 );
	VOID CreateFont(VOID);

	VOID AddText( const CHAR* text, DWORD dwTextColor, INT nEffectMode, DWORD dwEffectColor, INT nEffectValue );
	VOID AddText( const WCHAR* text, DWORD dwTextColor, INT nEffectMode, DWORD dwEffectColor, INT nEffectValue );

	VOID AddSurface( CSurface surface );

	VOID PrevLine(VOID);
	VOID NextLine(VOID);
	VOID FirstLine(VOID);
	VOID LastLine(VOID);

	void SetLine(int nLine);

	VOID SetScrollBarLeft( bool bScrollBarLeft );

//! Implementation
	VOID StringDetect(VOID);

	VOID AddOriginalItem( const WCHAR* text, DWORD dwTextColor, INT nEffectMode, DWORD dwEffectColor, INT nEffectValue );
	VOID AddCrudeItem( COutputBox_Item* pItem );
	VOID AddDrawItem( COutputBox_Item* pItem );

	VOID VisibleLineCount(VOID);
	
	VOID PopItem(VOID);
	
	VOID DrawItem(VOID);

//! callback function
	VOID OnSetOptions( const CComponentOptions& options );
	VOID OnScrollChange( INT nValue );
	VOID OnMove( INT nOldX,INT nOldY );
	VOID OnResize( INT nOldX, INT nOldY );
	VOID OnPaint(VOID);

	CSlot m_SlotSetOptions;
	CSlot m_SlotScrollMove;
	CSlot m_SlotScrollChange;
	CSlot m_SlotMove;
	CSlot m_SlotPaint;
	CSlot m_SlotResize;

public:
//! Variables
	std::list<CSurface> m_stlSurface;
	CSurface m_TextSurface;

	CGuiFont*		m_pFont;				// font 
	DWORD			m_dwStyle;				// scroll bar is vertival ro horizen
	COLORREF		m_dwTextColor;			// Default Text color
	COLORREF		m_dwBkColor;			// Default Text back ground color
	INT				m_nBkMode;				// Default Text back ground mode
	COLORREF		m_dwTextEffectColor;	// Default Text Effect color
	INT				m_nTextEffectMode;		// Default Text Effect mode;
	INT				m_nTextEffectValue;		// Default Text Effect Value;
	INT				m_nMaxLine;				// max text line count
	INT				m_nMarginX,m_nMarginY;	// X,Y ����.
	INT				m_nInterval;
	INT				m_nScrollLine;			// ���ڿ��� ���� ���� line.
	INT				m_nRowLimit;			// ȭ�鿡 ����� ������ ����.
	std::string		m_strFont;				// font �̸�.
	INT				m_nFontH;				// font ����.
	INT				m_nFontAttribute;		// font attribute

	bool			m_bScrollbarLeftLine;	// scrollbar left in line
	INT				m_nScrollBarWidth;		// Scrollbar Width
	INT				m_nScrollBarMarginTop;	// Scrollbar MarginTop
	INT				m_nScrollBarMarginBottom;	// Scrollbar MarginBottom
	bool			m_bDynamicScrollBar;		
	bool			m_bNeedDrawItem;		// Texture�� DrawItem()�� �ٽ� �ؾ� �ȴٴ� ���� �˸�

	INT				m_nDrawItemNum;
	INT				m_nDrawOffset;			// �̸� ����� ���� �κп��� �󸶳� offset�Ǿ�� �ϴ����� ���� �κ�

	std::list<COutputBox_Item*> m_listDrawItem;
	std::list<COutputBox_Item*> m_listCrudeItem;	// LineFeed�� ���� �ʴ� Item

	std::list<COutputBox_Item*> m_listOriginalItem;	// ��������� �ڷ�

	std::list<COutputBox_Item*>::iterator m_itDrawItem;	// DrawItem�� �ε��� �ݺ���
private:	
	COutputBox *m_pOutputBox;
};

END_GUI

#endif
