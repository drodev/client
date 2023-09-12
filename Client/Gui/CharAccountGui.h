/******************************************************************************
* File			: CharAccountGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2007. 10. 15
* Abstract		:
*****************************************************************************
* Desc			: ���������� ǥ���Ѵ�
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// presentation
#include "NtlPLGui.h"

// simulation
#include "Inputhandler.h"

// dbo
#include "Windowby3.h"

class CAccountGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CAccountGui(const RwChar* pName);
	virtual ~CAccountGui();

	RwBool		Create();
	VOID		Destroy();

	VOID		SetPosition(RwInt32 iXPos, RwInt32 iYPos);

protected:
	CAccountGui() {}
	virtual VOID	HandleEvents(RWS::CMsg &msg);

	VOID			SetServerInfo();
	VOID			SetServerState(RwUInt8 byState, RwUInt8 byRate);

	VOID			EnableButtons(bool bEnable);

	VOID			OnClicked_ServerSelectButton(gui::CComponent* pComponent);
	VOID			OnPaint();

protected:
	gui::CSlot			m_slotSelectServer;
	gui::CSlot			m_slotPaint;

	CWindowby3			m_Background;		///< ���

	CSurfaceGui			m_srtAccountBack;	///< ���� ���� ���

	gui::CStaticBox*	m_pTitleStatic;

	gui::CStaticBox*	m_pServerNameStatic;///< '���� �̸�'
	gui::CStaticBox*	m_pServerStateStatic;///< '���� ����'	
	gui::CStaticBox*	m_pServerName;		///< ���� �̸�
	gui::CStaticBox*	m_pServerState;		///< ���� ����

	gui::CButton*		m_pServerSelectButton;///< ���� ���� ��ư
};