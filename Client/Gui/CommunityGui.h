/******************************************************************************
* File			: CCommunityGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 9. 13
* Abstract		: 
*****************************************************************************
* Desc			: Ŀ�´�Ƽ ���� ���̾�α� ��Ʋ
*				  ������ ������ ������ PageType�� ���� ���õǰ�
*				  �޼����� �̺�Ʈ�� Ȱ��ȭ�� Page�� ���޵ȴ�.
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// gui
#include "gui_staticbox.h"
#include "gui_inputbox.h"

// presentation
#include "NtlPLGui.h"

// simulation
#include "NtlSLDef.h"

// client
#include "SlotGui.h"
#include "Windowby3.h"

class CCommunityBase;

class CCommunityGui : public CNtlPLGui, public RWS::CEventHandler
{
public:

	enum eCommunityPageType
	{
		PAGETYPE_GUILD,
		//PAGETYPE_RAID,

		NUM_PAGE,

		INVALID_PAGE
	};
	
	CCommunityGui(const RwChar* pName);
	virtual ~CCommunityGui();

	RwBool		Create();
	VOID		Destroy();

	RwInt32		SwitchDialog(bool bOpen);			///< DialogManager������ Open/Close

	VOID		SetPageType(RwInt32 iPageType);			///< �ش� �������� Ȱ��ȭ ��Ų��.
	RwInt32		GetPageType();							///< Ȱ��ȭ�� ������ �ε��� ��ȯ

	CHARACTERID	GetGuildSelectedID();

protected:
	CCommunityGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			SetupPage(RwInt32 iPage);

	VOID			CloseButtonClicked(gui::CComponent* pComponent);	///< �ݱ� ��ư�� ������.
	VOID			OnTabChanged(RwInt32 nIndex, RwInt32 nOldIndex);	///< �� ��ư�� ������.

	VOID			OnPaint();

	VOID			OnMouseDown(const CKey& key);
	VOID			OnMouseUp(const CKey& key);
	VOID			OnMove( RwInt32 iOldX, RwInt32 iOldY );
	VOID			OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID			OnMouseLeave(gui::CComponent* pComponent);
	VOID			OnCaptureMouseDown(const CKey& key);
	VOID			OnClickedBtnHelp( gui::CComponent* pComponent );

protected:	
	gui::CSlot			m_slotTabChanged;
	gui::CSlot			m_slotMouseDown;
	gui::CSlot			m_slotMouseUp;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotMouseMove;
	gui::CSlot			m_slotMouseLeave;
	gui::CSlot			m_slotPaint;	
	gui::CSlot			m_slotCaptureMouseDown;
	gui::CSlot			m_slotCloseButton;

	gui::CStaticBox*	m_pDialogName;				///< ���̾�α��� �̸� ����ƽ
	gui::CButton*		m_pExitButton;				///< â�ݱ� ��ư
	CWindowby3			m_BackLineSurface;			///< �����

	gui::CPanel*		m_pDumyPanel;				///< ����

	gui::CTabButton*	m_pTabButton;				///< �� ��ư

	gui::CButton*		m_pBtnHelp;
	gui::CSlot			m_slotClickedBtnHelp;

	RwInt32				m_iPageType;				///< ������ ������ Ÿ��

	///< �� �Ǻ� ������
	CCommunityBase*		m_pTabPage[NUM_PAGE];		///< �� ���� GUI
};