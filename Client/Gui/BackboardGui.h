/******************************************************************************
* File			: CBackboardGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2007. 8. 8
* Abstract		: 
*****************************************************************************
* Desc			: ������ ����� ������ ���� ȭ�� ��ü�� ������ �簢���� �׸���
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// presentation
#include "NtlPLGui.h"

// dbo
#include "SurfaceGui.h"


class CBackboardGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CBackboardGui(const RwChar* pName);
	virtual ~CBackboardGui();

	RwBool		Create();
	VOID		Destroy();

	VOID		SetColor(RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue);
	VOID		SetAlpha(RwUInt8 byAlpha);

	RwInt32		SwitchDialog(bool bOpen);			///< DialogManager������ Open/Close

protected:
	CBackboardGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			OnPaint();

protected:	
	gui::CSlot			m_slotPaint;

	CSurfaceGui			m_srfBack;
};