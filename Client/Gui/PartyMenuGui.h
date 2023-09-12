/******************************************************************************
* File			: PartyMenu.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Abstract		: 2006. 10. 13
*****************************************************************************
*
*****************************************************************************/

#pragma once

#include <list>

// core
#include "ceventhandler.h"

// shared
#include "NtlParty.h"
#include "NtlSkill.h"

// presetation
#include "NtlPLGui.h"

// simulation
#include "NtlSLDef.h"
#include "NtlSLParty.h"

// Dbo
#include "SlotGui.h"


class CPartyMemberGui;


class CPartyMenu : public CNtlPLGui, public RWS::CEventHandler
{
public:	
	struct sMenuShape
	{
		bool				bShowBuff;
		bool				bShowMember;
	};

	CPartyMenu(const RwChar* pName);
	virtual ~CPartyMenu();

	typedef std::list<CPartyMemberGui*>				PARTYMEMBER_LIST;
	typedef std::list<CPartyMemberGui*>::iterator	PARTYMEMBER_ITER;
	
	RwBool		Create();
	VOID		Destroy();
	VOID		Update(RwReal fElapsed);

	RwInt32		SwitchDialog(bool bOpen);			///< DialogManager������ Open/Close

	VOID		ResetPartyMenu();					///< PartyMenu �� �ʱ�ȭ �Ѵ�

protected:
	CPartyMenu() {}
	virtual VOID HandleEvents( RWS::CMsg &msg );

	VOID		Clear();

	VOID		AddMember(sPartyMember* pMember);				///< �ɹ�â�� �ϳ� �ø���.
	VOID		DelMember(SERIAL_HANDLE hSerial);				///< �ɹ�â�� �ϳ� ���δ�.

	CPartyMemberGui* GetPartyMemberGui(SERIAL_HANDLE hSerial);	///< �ɹ�â�� ��ȯ�Ѵ�.
	
	VOID		SetOtherWorld(); // �ƹ�Ÿ�� �����ϴ� ������ ��� �ٸ� ���� ���忡 �����ϴ� �ɹ��� GUI�� ǥ���Ѵ�

	VOID		NoPartyButtons();
	VOID		SpreadButtons();
	VOID		FoldButtons();

	VOID		SwitchMemberGui(bool bOpen);
	VOID		SwitchMemberBuff(bool bOpen);

	VOID		CheckPopup();

	VOID		MemberButton_UpdateTooltip();

	VOID		OnClick_MemberMenuButton(gui::CComponent* pComponent);
	VOID		OnClick_DevideZennyButton(gui::CComponent* pComponent);
	VOID		OnClick_DevideItemButton(gui::CComponent* pComponent);
	VOID		OnClick_DungeonButton(gui::CComponent* pComponent);
	VOID		OnClick_SwitchButton(gui::CComponent* pComponent);

	VOID		OnClick_SpreadMenuButton(gui::CComponent* pComponent);
	VOID		OnClick_FoldMenuButton(gui::CComponent* pComponent);

	VOID		OnMove(RwInt32 iOldX, RwInt32 iOldY);
	VOID		OnPaint();

protected:
	gui::CSlot			m_slotSpreadMenuButton;
	gui::CSlot			m_slotFoldMenuButton;
	gui::CSlot			m_slotMemberMenuButton;
	gui::CSlot			m_slotSwitchButton;
	gui::CSlot			m_slotDivideZennyButton;
	gui::CSlot			m_slotDivideItemButton;
	gui::CSlot			m_slotDungeonButton;
	gui::CSlot			m_slotPartyCharmButton;
	gui::CSlot			m_slotChangeMouseMove;
	gui::CSlot			m_slotChangeMouseLeave;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotPaint;

	gui::CStaticBox*	m_pPartyName;

	gui::CButton*		m_pSpreadMenuButton;		///< �޴� ��ġ�� ��ư
	gui::CButton*		m_pFoldMenuButton;			///< �޴� ���� ��ư

	gui::CButton*		m_pMemberMenuButton;		///< ��Ƽ�� ���� ��ư	
	gui::CButton*		m_pDivideZennyButton;		///< ���� �й� ��� ��ư
	gui::CButton*		m_pDivideItemButton;		///< ������ �й� ��� ��ư
	gui::CButton*		m_pDungeonButton;			///< ���� ��ư
	gui::CButton*		m_pSwitchButton;			///< ��Ƽ �޴�/�ɹ� â�� switch ��ư

	CSurfaceGui			m_srfPartyNameBackground;

	sMenuShape			m_MenuShape;
	
	RwReal				m_fUpdateTimeAbsentee;

	PARTYMEMBER_LIST	m_listPartyMember;			///< ��Ƽ �ɹ�â ����Ʈ
};