/******************************************************************************
* File			: ClassExplainGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2007. 10. 17
* Abstract		: 
*****************************************************************************
* Desc			: �κ񿡼� Ŭ������ ���� ������ �����ش�
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


class CClassExplainGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CClassExplainGui(const RwChar* pName);
	virtual ~CClassExplainGui();

	RwBool		Create();
	VOID		Destroy();

	VOID		SetClass(RwUInt8 byRace);
	VOID		SetPosition(RwInt32 iXPos, RwInt32 iYPos);

protected:
	CClassExplainGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			OnPaint();

protected:
	gui::CSlot			m_slotPaint;

	CWindowby3			m_Background;		///< ���

	CSurfaceGui			m_srtClassNameBack;	///< Ŭ���� �̸� ���

	gui::CStaticBox*	m_pTitleStatic;
	gui::CStaticBox*	m_pClassName;		///< Ŭ���� �̸�
	gui::CHtmlBox*		m_pExplainHtml;		///< Ŭ���� ����
};