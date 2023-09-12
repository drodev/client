/******************************************************************************
* File			: PartyMemberGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Abstract		: 2006. 10. 13
*****************************************************************************
* Desc			: CPartyMemberBuffGui : ��Ƽ���� ������ �����ش�.
*
*				  CPartyMemberGui : ��Ƽ���� ������ �����ش�.
*									CPartyMemberBuffGui��ü�� �ΰ���
*									������ ���Ʒ� 2������ ������ ������
*									�����ش�.
*****************************************************************************/

#pragma once

#include <list>

// core
#include "ceventhandler.h"

// shared
#include "NtlParty.h"

// presetation
#include "NtlPLGui.h"

// simulation
#include "NtlSLDef.h"

// dbo
#include "SurfaceGui.h"

class CBuffDispGui;

class CPartyMemberBuffGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CPartyMemberBuffGui();
	virtual ~CPartyMemberBuffGui();

	RwBool		Create(SERIAL_HANDLE hHandle);
	VOID		Update(RwReal fElapsed);
	VOID		Destroy();

	VOID		Show(bool bShow);
	VOID		SetPosition(RwInt32 iXPos, RwInt32 iYPos);

protected:
	VOID		HandleEvents(RWS::CMsg &pMsg);	

	VOID		OnPaint();

	VOID		OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID		OnMouseLeave(gui::CComponent* pComponent);

protected:
	gui::CSlot			m_slotMouseMove;
	gui::CSlot			m_slotMouseLeave;
	gui::CSlot			m_slotPaint;

	SERIAL_HANDLE		m_hOwnerHandle;

	CBuffDispGui*		m_pBuff;
};

class CPartyMemberGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CPartyMemberGui();
	virtual ~CPartyMemberGui();

	RwBool		Create(SERIAL_HANDLE hSerial, WCHAR* pcText, RwUInt8 byClass);
	VOID		Update(RwReal fElapsed);
	VOID		Destroy();

	SERIAL_HANDLE GetHandle();						///< �ɹ��� �ڵ� ��ȯ

	VOID		SetLP(RwInt32 iValue, RwInt32 iMaxValue);	///< LP ����
	VOID		SetEP(RwInt32 iValue, RwInt32 iMaxValue);	///< EP ����
	VOID		SetLevel(RwInt8 byLevel);			///< Level ����
	VOID		SetClass(RwUInt8 byClass);			///< Class ����
	VOID		SetLeader(RwBool bLeader);			///< ��Ƽ ������� ����
	VOID		SetOtherWorld(RwBool bOtherWorld);
	VOID		SetCurEmergencyPulse(RwReal fPulse);
	VOID		SetEmergencyState(RwBool bState);

	RwReal		GetCurEmergencyPulse();
	RwBool		GetEmergencyState();

	VOID		ShowBuff(bool bShow);

protected:
	virtual VOID HandleEvents( RWS::CMsg &msg );

	VOID		OnPostPaint();
	
	VOID		OnMouseDown(const CKey& key);
	VOID		OnMouseUp(const CKey& key);
	VOID		OnMove(RwInt32 nX, RwInt32 nY);
	VOID		OnMouseEnter(gui::CComponent* pComponent);
	VOID		OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID		OnMouseLeave(gui::CComponent* pComponent);

protected:
	gui::CSlot			m_slotMouseDown;
	gui::CSlot			m_slotMouseUp;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotMouseEnter;
	gui::CSlot			m_slotMouseMove;
	gui::CSlot			m_slotMouseLeave;
	gui::CSlot			m_slotPaint;
	gui::CSlot			m_slotPostPaint;

	gui::CPanel*		m_pTributarySimbol;			///< ������ ���� �׸�

	gui::CStaticBox*	m_pNameStatic;				///<  �ɹ� �̸�

	gui::CProgressBar*	m_pLPGauge;					///< LP ������
	/*
	gui::CStaticBox*	m_pLPStatic;				///< LP ����ƽ
	gui::CStaticBox*	m_pLPSlachStatic;			///< ������ ����ƽ
	gui::CStaticBox*	m_pMaxLPStatic;				///< MaxLP ����ƽ
*/
	gui::CProgressBar*	m_pEPGauge;					///< EP ������
	/*
	gui::CStaticBox*	m_pEPStatic;				///< EP ����ƽ
	gui::CStaticBox*	m_pEPSlachStatic;			///< ������ ����ƽ
	gui::CStaticBox*	m_pMaxEPStatic;				///< MAxEP ����ƽ
*/
	gui::CStaticBox*	m_pLevel;					///< Level

	CSurfaceGui			m_srfOtherWorldPanel;		///< �ٸ� ���忡 �ִ� ��Ƽ���� �г�
	CSurfaceGui			m_srfDeathPanel;			///< ����� �г�

	CSurfaceGui			m_srfLeaderMark;			///< ���� ��ũ
	CSurfaceGui			m_srfDeathMark;				///< ��� ��ũ
	CSurfaceGui			m_srfTooFarMark;			///< �ָ� ������ ��Ƽ��

	gui::CFlickerEffect	m_feEmergency;				///< LP ��� ǥ�õ�

	SERIAL_HANDLE		m_hSerial;					///< �ɹ��� �ø���
	RwUInt8				m_byClass;					///< Ŭ����
	RwInt8				m_byMouse;					///< �ɹ�â�� ���ȴ��� ����

	RwUInt8				m_byDisplayFlag;

	CPartyMemberBuffGui*	m_pBuff;				///< ����������
};