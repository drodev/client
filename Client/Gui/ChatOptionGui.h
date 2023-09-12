/******************************************************************************
* File			: ChatOptionGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2008. 7. 1
* Abstract		: 
*****************************************************************************
* Desc			: ä�ÿ� ���õ� �ɼ��� �����ϴ� GUI
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// presetation
#include "NtlPLGui.h"

// simulation
#include "NtlSLDef.h"

// dbo
#include "ChatDefine.h"
#include "ChatGui.h"

class CChatOptionGui : public CNtlPLGui, public RWS::CEventHandler
{
public:	
	CChatOptionGui(const RwChar* pName);
	virtual ~CChatOptionGui();

	RwBool		Create(CChatGui* pChatGui);
	VOID		Destroy();

	VOID		EnableCatting(eChatType eType, BOOL bEnable);

	VOID		SwitchDialog(bool bOpen);

protected:
	CChatOptionGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );	

	VOID			OnClicked_CloseButton(gui::CComponent* pComponent);
	VOID			OnClicked_ChatTypeButton(gui::CComponent* pComponent);
	VOID			OnClicked_ToggleQuickButton(gui::CComponent* pComponent, bool bToggled);
	VOID			OnClicked_CommandButton(gui::CComponent* pComponent);

protected:
	gui::CSlot			m_slotCloseButton;
	gui::CSlot			m_slotChatTypeButton[NUM_NET_CHAT_TYPE];
	gui::CSlot			m_slotToggleQuickButton[NUM_NET_CHAT_TYPE];
	gui::CSlot			m_slotCommand;

	gui::CButton*		m_pCloseButton;
	gui::CButton*		m_pChatTypeButton[NUM_NET_CHAT_TYPE];		///< ä�� Ÿ�� ���� ��ư
	gui::CButton*		m_pToggleQuickButton[NUM_NET_CHAT_TYPE];	///< ����ư ��� ��ư
	gui::CButton*		m_pCommandButton;							///< ��ɾ� ��ư

	gui::CStaticBox*	m_pTitle;									///< ���̾�α� ����
	gui::CStaticBox*	m_pShoutcut[NUM_NET_CHAT_TYPE];				///< ����Ű ǥ��
	gui::CStaticBox*	m_pShoutcutExplain[NUM_NET_CHAT_TYPE];		///< ����Ű ����
	gui::CStaticBox*	m_pstbCommandShortcutExplain;
	gui::CStaticBox*	m_pCommand;			///< ��ɾ� ����

	CChatGui*			m_pChatGui;
};