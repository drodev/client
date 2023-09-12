////////////////////////////////////////////////////////////////////////////////
// Name: class gui:CTabButton
// Desc: Tab������ ��ư ����. ������ ���� Button�� ����, ������.
//
//
// 2006.03.28 Peessi@hitel.net   
// 2007.04.04 Peessi@hitel.net 
//		- ���� ũ�⺯ȯ ���� ��ȯ ����.
// 2008.03.03 Peessi@hitel.net
//		- �ǹ�ư �ִ��� �̻� �þ�� ����. ���û����� * ������ �ǹ�ư ��ü�� �ʰ��� Assert
//      - �ǹ�ư ������ �������� ��ǥ���� ��� �ڵ����� ������ ����. 
//
// Use : 1. SetTabSurface�� ���, Surface�� ����ϱ� ���� Add�� ��� �� Refresh�� ��.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GUI_TABBUTTON_H__
#define __GUI_TABBUTTON_H__

START_GUI

class CTabButton_Generic;

class CTabButton : public CComponent
{
public:
//! Constructors:
	CTabButton( CComponent* pParent, CSurfaceManager* pSurfaceManager );
	CTabButton( const CRectangle& rtRect, CComponent* pParent, CSurfaceManager* pSurfaceManager );
//! Destructor:
	virtual ~CTabButton(VOID);

public:
//! Attributes:
	INT		GetButtonCount(VOID) const;
	INT		GetSelectedButtonIndex(VOID) const;

	VOID	SetTabSurface( CSurface& left, CSurface& center, CSurface& right, 
						   CSurface& selectedleft, CSurface& selectedcenter, CSurface& selectedright,
						   CSurface& focusleft, CSurface& focuscenter, CSurface& focusright, CSurface& line );
						   
	////////////////////////////////////////////////////////////////////////////
	// �� �ܶ��� �Ӽ��� Tab�� Add�ϱ� ���� �����Ѵ�. Tab�� ������ Clear��.
	// �� �̿��� ���� ���� �� ApplyAttribute()�Լ��� ȣ���Ѵ�. 
	VOID	SetTextColor( BYTE ucRed, BYTE ucGreen, BYTE ucBlue );
	VOID	SetTextSelectedColor( BYTE ucRed, BYTE ucGreen, BYTE ucBlue );
	VOID	SetTextFocusedColor( BYTE ucRed, BYTE ucGreen, BYTE ucBlue );
	VOID	SetTextDisabledColor( BYTE ucRed, BYTE ucGreen, BYTE ucBlue );
	VOID	SetTextAlpha( BYTE ucAlpha );
	VOID	SetTextSelectedAlpha( BYTE ucAlpha );
	VOID	SetTextFocusedAlpha( BYTE ucAlpha );
	VOID	SetTextDisabledAlpha( BYTE ucAlpha );
	VOID	SetFont( CHAR* pFaceName, INT nHeight, INT nAttributes );
	VOID	SetTextAlign( DWORD dwAlign );
	VOID	SetTabTextMargin( INT nMarginX, INT nMarginY );
	////////////////////////////////////////////////////////////////////////////
	// ApplyAttribute ȣ��� ������ �Ǽ����� �����ȴ�.
	VOID	ApplyAttribute(VOID);

	VOID	SetUnselTabWidth( INT nWidth, BOOL bRedraw = TRUE );
	VOID	SetOrient( BOOL bLeft, BOOL bRedraw = TRUE );
		
	INT		AddTab( std::string& strTabText, BOOL bRedraw = TRUE );
	INT		AddTab( std::wstring& wstrTabText, BOOL bRedraw = TRUE );
	VOID	ClearTab(VOID);

	VOID	SetClickSound( const CHAR* szClickSoundFilename );
	VOID	SetFocusSound( const CHAR* szFocusSoundFIlename );
		
//! Operations:
	VOID	SelectTab( INT nIndex, BOOL bDoCallBack = FALSE );		
	
	VOID	EnableTab( INT nIndex, BOOL bEnable = TRUE );
	VOID	ChangeTabText( INT nIndex, std::string& strText );
	VOID	ChangeTabText( INT nIndex, std::wstring& wstrText );
		
//! Signals:
	CSignal_v1<INT>& SigSelected(VOID);
	CSignal_v2<INT,INT>& SigSelectChanged(VOID);

private:
				
protected:
//! Variables:
	CTabButton_Generic* m_pImpl;

private:
//! Etc:
	CTabButton( const CTabButton& copy ); // prevent construction by copy construction
	friend class CTabButton_Generic;
};

END_GUI

#endif//__GUI_TABBUTTON_H__
