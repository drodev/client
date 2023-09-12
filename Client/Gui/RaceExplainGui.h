/******************************************************************************
* File			: RaceExplainGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 12. 8
* Abstract		: 
*****************************************************************************
* Desc			: �κ񿡼� ������ ���� ������ �����ش�
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// gui
#include "gui_button.h"

// presentation
#include "NtlPLGui.h"

// simulation
#include "Inputhandler.h"

// dbo
#include "Windowby3.h"


class CRaceExplainGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CRaceExplainGui(const RwChar* pName);
	virtual ~CRaceExplainGui();

	RwBool		Create();
	VOID		Destroy();

	VOID		SetRace(RwUInt8 byRace);
	VOID		SetPosition(RwInt32 iXPos, RwInt32 iYPos);

protected:
	CRaceExplainGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			OnPaint();

protected:
	gui::CSlot			m_slotPaint;

	CWindowby3			m_Background;		///< ���

	CSurfaceGui			m_srtRaceNameBack;	///< ���� �̸� ���

	gui::CStaticBox*	m_pTitleStatic;

	gui::CStaticBox*	m_pRaceName;		///< ���� �̸�
	gui::CHtmlBox*		m_pExplainHtml;		///< ���� ����
};