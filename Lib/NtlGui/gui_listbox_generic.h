#ifndef __GUI_LISTBOX_GENERIC_H__
#define __GUI_LISTBOX_GENERIC_H__

#include "gui_define.h"
#include "gui_signals.h"
#include "gui_listbox_item.h"
#include "key.h"
#include "rectangle.h"

START_GUI

#define LISTBOX_DEFAULT_VISIBLEITEM	1

class CListBox;
class CScrollBar;
class CComponent;
class CComponentOptions;

class CListBox_Generic
{
//! Constructor & Destructor:
public:
	CListBox_Generic( CListBox* pSelf, BOOL bDynamicScrollBar, INT nMaxVisibleItems = LISTBOX_DEFAULT_VISIBLEITEM );
	~CListBox_Generic();

// Attributes:
	INT GetItemCount(VOID);
	const std::vector<CListBox_Item*>& GetAllItems(VOID) const;

	std::vector<CListBox_Item*> GetSelectedItems(VOID);
	std::vector<std::wstring>  GetSelectedItemsText(VOID);
	std::vector<INT>		   GetSelectedItemsIndex(VOID);

	CListBox_Item*	GetSelectedItem(VOID);
	std::wstring	GetSelectedItemText(VOID);
	INT				GetSelectedItemIndex(VOID);

	CListBox_Item*	GetItem( INT nIndex ); 
	std::wstring	GetItemText( INT nIndex );

	bool			IsSelected( INT nIndex );
	
// Operations:
	INT	 AddItem( const CHAR* szText, DWORD dwData );
	INT	 AddItem( const WCHAR* szText, DWORD dwData );
	INT	 InsertItem( const CHAR* szText, INT nIndex, DWORD dwData );
	INT	 InsertItem( const WCHAR* szText, INT nIndex, DWORD dwData );
	VOID ChangeItem( const CHAR* szText, INT nIndex, DWORD dwData );
	VOID ChangeItem( const WCHAR* szText, INT nIndex, DWORD dwData );
	
	VOID RemoveItem( INT nIndex );
	VOID RemoveSelectedItems(VOID);
	VOID ClearAll(VOID);
	VOID ClearSelection(VOID);
	
	VOID SelectItem( INT nIndex, bool bSelect );
	VOID SelectAll( bool bSelect);
	VOID InvertSelection(VOID);

	BOOL IsVisibleIndex( INT nIndex );

	VOID SetMultiSelection( bool bEnable );
	VOID SetItemHeight( INT nHeight );
	VOID SetMaxVisibleItems( INT nCount );
	VOID SetTopItem( INT nIndex );
	VOID SetSelectedMaskColor( BYTE uRed, BYTE uGreen, BYTE uBlue, BYTE uAlpha);
	VOID SetSelectedTextColor( COLORREF color );
	VOID SetTextColor( COLORREF color );
	VOID SetBkColor( COLORREF color );
	VOID SetBkMode( INT nBkMode );

	VOID Sort( bool bAscending );

	VOID ReviseItem();						// �������� Item�� �߸���, ���� ����.
	VOID DrawItem(VOID);						// �������� Item�� Texture�� �׸���.

	//-------------------------------------------------------------------------
	//: font Create
	VOID CreateFont( CHAR* pFaceName, INT nHeight, INT nAttributes = 0 );
	VOID CreateFont(VOID);

	VOID AddSurface( CSurface surface );
	VOID AddMaskSurface( CSurface& surface );
	
//! Signals:

	CSignal_v1<INT> m_SigHighlighted;
	CSignal_v1<INT> m_SigSelected;
	CSignal_v0		m_SigSelectionChanged;

private:
//! Implementation:
	VOID UpdateScrollbar(VOID);					// ScrollBar ���� �Ǵ�.
	VOID CalcRowWidth(VOID);
	VOID CalcRowHeight(VOID);
	INT  GetStartX( CUniBuffer* pBuffer );		// Draw�Ǵ� Row�� Client���� ��ġ ��ȯ.
	INT  GetStartY( INT nIndex );
	INT  MousePosToIndex( INT nYPos );

	VOID ClearItems(VOID);
	VOID ClearDrawItems(VOID);
	VOID ClearSelectionMasks(VOID);

// Callbacks:
	VOID OnPaint(VOID);
	VOID OnSetOptions( const CComponentOptions& options );
	VOID OnMouseDown( const CKey& key );
	VOID OnMouseMove( INT nkey, INT xPos, INT yPos );
	VOID OnMouseLeave( CComponent* pComponent );
	VOID OnScrollChange( INT nNewOffset );
	VOID OnWheelMove( RwInt32 nFlag, RwInt16 sDelta, CPos& pos );
	VOID OnMove( INT nOldX, INT nOldY );
	VOID OnResize(int nOldWidth, int nOldHeight);

	CSlot m_SlotPaint;
	CSlot m_SlotSetOptions;
	CSlot m_SlotMouseDown;
	CSlot m_SlotMouseMove;
	CSlot m_SlotMouseLeave;
	CSlot m_SlotScrollChange;
	CSlot m_SlotWheelMove;
	CSlot m_SlotSliderMove;
	CSlot m_SlotMove;
	
public:
// Variables:
	CSurface				  m_TextSurface;	
	CSurface				  m_MaskSurface;
	std::list<CRectangle*>	  m_listMaskRect;
	std::list<CSurface>		  m_listSurface;	// ListBox�ڽ��� Surface
	
	CGuiFont*			m_pFont;				// Font
	DWORD				m_dwScrollStyle;		// scroll bar is vertival ro horizen
	DWORD				m_dwWidthSortStyle;		// ���� ����.

	INT					m_nMaxRowCount;			// max text line count
	INT					m_nVisibleRowCount;		// ȭ�鿡 ���̴� �� ����
	
	INT					m_nMarginX;				// ����, ���� ����.		
	INT					m_nMarginY;

	INT					m_nTextMarginX;			// new 11/3/2018
	INT					m_nScrollbarMarginX;	// new 11/3/2018
		
	INT					m_nOffsetRow;			// Begin to take a string line. (Change when scrolling.)
	INT					m_nHighlightRow;		// DrawItem Index����.
	
	std::string			m_strFont;				// font �̸�.
	INT					m_nFontH;				// font ����.
	INT					m_nFontAttributes;		// font attribute
	
	COLORREF			m_SelTextColor;			// ���õ� item�� text color ����...
	COLORREF			m_TextColor;			// �⺻ TextColor;
	COLORREF			m_BkColor;
	INT					m_nBkMode;				
	COLORREF			m_EffectColor;			// �ؽ�Ʈ ����ƮĮ��.
	INT					m_nEffectMode;	
	INT					m_nEffectValue;			
		
	INT					m_nRowHeight;			// ���� ��, ����
	INT					m_nRowWidth;			
	
	BOOL				m_bDynamicScrollBar;
	bool				m_bMultiSelection;

	std::vector<CListBox_Item*>	m_vecItems;
	std::list<CListBox_Item*>	m_listDrawItems;

	CListBox*			m_pListBox;
};

END_GUI

#endif
