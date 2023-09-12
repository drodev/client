/******************************************************************************
* File			: ScouterGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 9. 13S
* Abstract		: 
*****************************************************************************
* Desc			: Ŀ�´�Ƽ ���� ���̾�α� ��Ʋ
*				  ������ ������ ������ PageType�� ���� ���õǰ�
*				  �޼����� �̺�Ʈ�� Ȱ��ȭ�� Page�� ���޵ȴ�.
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// shared
#include "NtlParty.h"

// gui

#include "gui_panel.h"

// simulation
#include "NtlSLParty.h"

// dbo
#include "CommunityBase.h"
#include "SlotGui.h"
#include "Windowby3.h"

class CCommunityParty : public CCommunityBase
{
public:
	enum eZennyDivType
	{
		ZDT_PICKUP_PERSON,		///< ���� ����� ����
		ZDT_EQUAL,				///< ���� �й�

		NUM_ZDT
	};

	enum eItemDivType
	{
		IDT_PICKUP_PERSON,		///< ���� ����� ����
		IDT_ORDER,				///< �����Ƿ�
		IDT_GRADE_ITEM,			///< ������ ��޿� ���� �⿩�� �й�
		IDT_CONTIBUTION,		///< �⿩�� �й�

		NUM_IDT
	};

	struct PartyMemberUI
	{
		SERIAL_HANDLE		hSerial;	///< �ɹ��� �ø���
		gui::CStaticBox*	pName;		///< ��Ƽ�� �̸�
		gui::CStaticBox*	pScore;		///< ��Ƽ�� �⿩����
		gui::CPanel*		pTributarySimbol;///< ������ ���� �׸�

		PartyMemberUI()
		:pName(NULL)
		,pScore(NULL)
		{
		}
	};

	///< ��/��/��� �и��Ǿ� ���� Ȯ��Ǵ� 3��� ������
	struct Windowby3						
	{
		CSurfaceGui			Left;
		CSurfaceGui			Center;
		CSurfaceGui			Right;

		VOID	Render()
		{
			Left.Render();
			Center.Render();
			Right.Render();
		}
	};

	CCommunityParty();
	virtual ~CCommunityParty();

	virtual RwBool		Create(CNtlPLGui* pParent);
	virtual VOID		Update(RwReal fElapsed);
	virtual VOID		Destroy();

	virtual VOID		SwitchDialog(bool bOpen);

	virtual VOID		Clear();
	virtual VOID		ActiveTab(bool bActive);

	virtual VOID		HandleEvents( RWS::CMsg &msg );	
	
	virtual VOID		OnMouseDown(const CKey& key);
	virtual VOID		OnMouseUp(const CKey& key);
	virtual VOID		OnMove(RwInt32 iOldX, RwInt32 iOldY);
	virtual VOID		OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	virtual VOID		OnMouseLeave(gui::CComponent* pComponent);

	virtual VOID		OnPaint();

protected:	
	VOID		PartyLeave();

	VOID		SetZennyDivision(RwUInt8 byIndex);
	VOID		SetItemDivision(RwUInt8 byIndex);

	VOID		LockZennyButton(bool bLock);
	VOID		LockItemButton(bool bLock);

	VOID		SetMember(sPartyMember* pMember, RwUInt8 byIndex);
	VOID		DelMember(RwUInt8 byIndex);

	VOID		CheckInfoWindow();

	VOID		OnGotFocus();
	VOID		OnLostFocus();	

	VOID		OnReturn_PartyNameInput();

	VOID		ClickedPartyCreateButton(gui::CComponent* pComponent);
	VOID		ClickedSelectDivButton(gui::CComponent* pComponent);
	VOID		ClickedLockButton(gui::CComponent* pComponent);

	VOID		OnClicked_InvenButton(gui::CComponent* pComponent);
	VOID		OnClicked_CharmButton(gui::CComponent* pComponent);
	VOID		OnClicked_CPButton(gui::CComponent* pComponent);
	VOID		OnClicked_ItemtoCPButton(gui::CComponent* pComponent);

	VOID		LocateLeaderMark(RwInt32 iIndex);	///< ������ ��ġ�� ��ũ�� ǥ���Ѵ�. iIndex <= 0 �̸� ǥ������ �ʴ´�.

	VOID		CalcSurfacePosition();

	VOID		AdjustSurface(gui::CSurface& surface);	///< ��ư���� �� ��ǥ�� surface�� �̵���Ų��

protected:	
	gui::CSlot			m_slotReturnInput;
	gui::CSlot			m_slotSelectZennyDivButton;
	gui::CSlot			m_slotSelectItemDivButton;
	gui::CSlot			m_slotZennyLockButton;
	gui::CSlot			m_slotItemLockButton;
	gui::CSlot			m_slotPartyCreateButton;
	gui::CSlot			m_slotInvenButton;
	gui::CSlot			m_slotCharmButton;
	gui::CSlot			m_slotCPButton;
	gui::CSlot			m_slotItemtoCPButton;
	gui::CSlot			m_slotGotFocus;
	gui::CSlot			m_slotLostFocus;

	CNtlPLGui*			m_pParent;					///< Owner class	

	gui::CStaticBox*	m_pPartyName;				///< '��Ƽ�̸�'
	CSurfaceGui			m_PartyNameBack;			///< ��Ƽ �̸� �麸��

	gui::CStaticBox*	m_pMyPartyNameStatic;		///< ���� ��Ƽ �̸�
	gui::CInputBox*		m_pPartNameInput;			///< ��Ƽ �̸� �Է¶�
	gui::CButton*		m_pPartyButtonCreate;		///< ��Ƽ ����



	CSurfaceGui			m_ZennySurface;				///< 'Zenny' �����̽�
	CSurfaceGui			m_ZennyDivSurface[NUM_ZDT];	///< ���� �й� ���
	gui::CButton*		m_pSelectZennyDivButton;	///< ���� �й� ��� ���� ��ư
	CSurfaceGui			m_ZennyExplainPanel;		///< ���� �й� ���� ���
	gui::CStaticBox*	m_pZennyDivExplain;			///< ���� �й� ����
	gui::CButton*		m_pZennyLockButton;			///< ���� �й� ��� ��ư

	CSurfaceGui			m_ItemSurface;				///< 'Item' �����̽�
	CSurfaceGui			m_ItemDivSurface[NUM_IDT];	///< ������ �й� ���
	gui::CButton*		m_pSelectItemDivButton;		///< ������ �й� ��� ���� ��ư
	CSurfaceGui			m_ItemExplainPanel;			///< ������ �й� ���� ���
	gui::CStaticBox*	m_pItemDivExplain;			///< ������ �й� ����
	gui::CButton*		m_pItemLockButton;			///< ������ �й� ��� ��ư


	CSurfaceGui			m_MemberHeadLine;			///< ��Ƽ �ɹ� �ص����
	gui::CStaticBox*	m_MemberStatic;				///< '��Ƽ �ɹ�'
	gui::CStaticBox*	m_ScoreStatic;				///< '�⿩����'
	CSurfaceGui			m_LeaderMark;				///< ��Ƽ�� ��ũ
	CSurfaceGui			m_srfMemberboard;			///< �ɹ� ����Ʈ ���
	PartyMemberUI		m_PartyMemberInfo[NTL_MAX_MEMBER_IN_PARTY];	///< ��Ƽ�� ����	


	gui::CButton*		m_PartyInvenButton;			///< ��Ƽ �κ� ��ư		
	gui::CButton*		m_pCharmButton;				///< ���� ��ư
	CSlotGui			m_PartyCharmSlot[NTL_PARTY_CHARM_INVENTORY_COUNT];	///< ��Ƽ ���� ����
	CSurfaceGui			m_CharmBackpanel;			///< ���� �г�
	
	CSurfaceGui			m_CPHeadLine;				///< CP �ص����
	gui::CStaticBox*	m_CPStatic;					///< 'CP ��ȯ'
	gui::CStaticBox*	m_CPPoint;					///< ���� ���� CP
	gui::CStaticBox*	m_CPExplain;				///< CP ����
	gui::CButton*		m_pCPButton;				///< CP ��ư
	gui::CButton*		m_pItemtoCPButton;			///< �������� CP�� ��ȯ ��ư
	
	RwInt32				m_iLeaderIndex;				///< ��Ƽ�� �ε���
	RwInt8				m_byInfoWindowIndex;

	RwUInt8				m_byItemDivisionType;		///< ���� �׷����� �ִ� ������ �й� ���
	RwUInt8				m_byZennyDivisionType;		///< ���� �׷����� �ִ� ���� �й� ���

	RwUInt8				m_bySelectedItemDivisionType;	///< ���� ������ �й� ���
	RwUInt8				m_bySelectedZennyDivisionType;	///< ���� ���� �й� ���
};