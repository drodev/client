#ifndef __GUI_TABBUTTON_GENERIC_H__
#define __GUI_TABBUTTON_GENERIC_H__

START_GUI

class CTabButton_Item;

class CTabButton_Generic
{
public:
//! Enum
	enum SURFACETYPE { LEFT, CENTER, RIGHT, SEL_LEFT, SEL_CENTER, SEL_RIGHT, FOC_LEFT, FOC_CENTER, FOC_RIGHT, LINE, NUM_TYPE };

//! Constructor & Destructor
	CTabButton_Generic( CTabButton* pSelf );
	~CTabButton_Generic(VOID);

//! Attributes
	inline BOOL	AvailableIndexRange( INT nIndex );

	INT		GetSelectedTabIndex(VOID);
	INT		GetTabCount(VOID);

//! Operations
	VOID	SelectTab( INT nIndex, BOOL bDoCallBack );	
	VOID	EnableTab( INT nIndex, BOOL bEnable );
	VOID	ChangeTabText( INT nIndex, std::string& strText );
	VOID	ChangeTabText( INT nIndex, std::wstring& wstrText );

	INT		AddTab( std::string& strTabText );
	INT		AddTab( std::wstring& wstrTabText );
	VOID	ClearTab(VOID);

	VOID	CalcTabRect(VOID);							// �� Component�� ũ�⸦ ����.

	VOID	InitLine(VOID);								// Line�� Component Size�� ����.

	VOID	ApplyAttribute(VOID);						// �����Ǿ� �ִ� Tab�� �Ӽ����� �ٽ� ������.
	
public:
//! Implements
	VOID	AvailableWidthCheck(VOID);					// ���� UI�� ǥ���� ���� ����� �������.

//! Signals
	CSignal_v1<INT>	m_SigSelected;
	CSignal_v2<INT,INT> m_SigSelectChanged;

public:
//! Callbacks
	VOID	OnSetOptions( const CComponentOptions& options );
	VOID	OnPaint(VOID);
	VOID	OnMove( INT nX, INT nY );
	
	CSlot	m_slotSetOptions;
	CSlot	m_slotMove;
	CSlot	m_slotPaint;
	
//! variables
	std::vector<CTabButton_Item*>	m_vecTabItem;

	COLORREF	m_TextColor;
	COLORREF	m_SelTextColor;
	COLORREF	m_FocTextColor;
	COLORREF	m_DisableTextColor;
	BYTE		m_ucTextAlpha;
	BYTE		m_ucSelTextAlpha;
	BYTE		m_ucFocTextAlpha;
	BYTE		m_ucDisableTextAlpha;
	
	std::string m_strFontname;
	DWORD		m_dwFontHeight;
	DWORD		m_dwFontAttr;
	DWORD		m_dwTextStyle;

	CSurface	m_Surface[NUM_TYPE];

	BOOL		m_bLeftOriented;

	INT			m_nTextMarginX;
	INT			m_nTextMarginY;
	INT			m_nUnselWidth;						// ���õ��� ���� ��ư�� ��
	INT			m_nMarginWidth;						// ���� ��.
		
	INT			m_nSelectedIndex;	

	std::string	m_strFocusSound;					
	std::string m_strClickSound;				

	CTabButton* m_pTabButton;
};

BOOL CTabButton_Generic::AvailableIndexRange( INT nIndex )
{
	if( nIndex >= 0 && nIndex < (INT)m_vecTabItem.size() )
		return TRUE;

	return FALSE;
}

END_GUI

#endif//__GUI_TABBUTTON_GENERIC_H__
