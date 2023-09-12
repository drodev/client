/******************************************************************************
* File			: SideDialogControlGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2008. 1. 24
* Abstract		: 
*****************************************************************************
* Desc			: ���̵� ���̾�α׸� �����ϴ� ��Ʈ�� GUI
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// presetation
#include "NtlPLGui.h"

class CSideDialogMiniGui;

class CSideDialogControlGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	enum eButtonType
	{
		BUTTONTYPE_TMQ,
		BUTTONTYPE_PCVIEW,
		BUTTONTYPE_RANKBATTLE,
		BUTTONTYPE_QUESTINDICATE,
		BUTTONTYPE_BUDOKAI_MINOR,
		BUTTONTYPE_BUDOKAI_MAJOR,
		BUTTONTYPE_BUDOKAI_FINAL,
		BUTTONTYPE_CCBD,

		NUM_BUTTONTYPE
	};

	struct sButtonType
	{
		gui::CButton*		pButton;		
		gui::CSlot			slotButton;
		RwUInt32			uiSideDialogType;
	};
	
	typedef std::list<sButtonType*>					LIST_BUTTON;
	typedef std::list<sButtonType*>::iterator		LIST_BUTTON_ITER;


public:
	CSideDialogControlGui(const RwChar* pName);
	virtual ~CSideDialogControlGui();		

	RwBool		Create();
	VOID		Destroy();

	RwInt32		SwitchDialog(bool bOpen);			///< DialogManager������ Open/Close

	RwBool		SelectButtonType(RwUInt32 uiDialogType);

protected:
	CSideDialogControlGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );	

	VOID			ArrangeButtons(RwBool bOpenStartIndex = FALSE);

	VOID			AddButton(RwUInt32 uiSideDialogType);
	VOID			DelButton(RwUInt32 uiSideDialogType);

	VOID			OnClick_LeftButton(gui::CComponent* pComponent);
	VOID			OnClick_RightButton(gui::CComponent* pComponent);
	VOID			OnClick_ButtonType(gui::CComponent* pComponent);
	VOID			OnMove(RwInt32 iOldX, RwInt32 iOldY);

protected:
	gui::CSlot			m_slotLeftButton;
	gui::CSlot			m_slotRightButton;
	gui::CSlot			m_slotMove;

	gui::CButton*		m_pLeftButton;				///< ���� ��ư
	gui::CButton*		m_pRightButton;				///< ������ ��ư

	CSideDialogMiniGui*	m_pSideDialogMiniGui;		///< ���̵� ���̾�α��� �ּ�ȭ�� ���� ���̾�α�

	sButtonType			m_aButtonType[NUM_BUTTONTYPE];

	RwInt8				m_byVisibleStart;

	LIST_BUTTON			m_listEnableButton;
};