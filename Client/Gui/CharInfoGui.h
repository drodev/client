/******************************************************************************
* File			: CharInfoGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2007. 10. 17
* Abstract		:
*****************************************************************************
* Desc			: �κ񿡼� ���� ���õ� ĳ������ ������ �����ش�
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

class CCharacterInfoGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CCharacterInfoGui(const RwChar* pName);
	virtual ~CCharacterInfoGui();

	RwBool		Create();
	VOID		Destroy();

	VOID		SetChar(RwUInt8 byIndex);
	VOID		SetPosition(RwInt32 iXPos, RwInt32 iYPos);

protected:
	CCharacterInfoGui() {}
	virtual VOID	HandleEvents(RWS::CMsg &msg);

	VOID			SetReservatedDelInfo(RwUInt8 byCharIndex);

	VOID			OnPaint();

protected:
	gui::CSlot			m_slotPaint;

	CWindowby3			m_Background;		///< ���

	CSurfaceGui			m_srtInfoBack;		///< ĳ���� ���� ���

	gui::CStaticBox*	m_pTitleStatic;		///<
	gui::CStaticBox*	m_pNameStatic;		///< '�̸�'
	gui::CStaticBox*	m_pLevelStatic;		///< '����'
	gui::CStaticBox*	m_pClassStatic;		///< 'Ŭ����'
	gui::CStaticBox*	m_pZennyStatic;		///< '��������'
	gui::CStaticBox*	m_pLastLocationStatic;///< '������ġ'
	gui::CStaticBox*	m_pDeleteDayStatic;	///< '���� ������'
	gui::CStaticBox*	m_pName;			///< ĳ���� �̸�
	gui::CStaticBox*	m_pLevel;			///< ĳ���� ����
	gui::CStaticBox*	m_pClass;			///< ĳ���� Ŭ����
	gui::CStaticBox*	m_pZenny;			///< ĳ���� ���� ����
	gui::CStaticBox*	m_pLastLocation;	///< ĳ���� ���� ��ġ

	gui::CStaticBox*	m_pDeleteDay;		///< ĳ���� ���� ������
	gui::CStaticBox*	m_pDeleteDayExplain;///< ĳ���� ���� ������ �� ����
};