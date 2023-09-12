/******************************************************************************
* File			: NameNotifyGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2008. 11. 5
* Abstract		: 
*****************************************************************************
* Desc			: ��� ��ȭ�߿� �ƹ�Ÿ�� �̸��� ���ԵǾ� ������ �˷��ش�
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// presentation
#include "NtlPLGui.h"

// trigger
#include "DboTSCoreDefine.h"

// dbo
#include "NumberGui.h"


class CNameNotifyGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CNameNotifyGui(const RwChar* pName);
	virtual ~CNameNotifyGui();

	RwBool		Create();
	VOID		Update(RwReal fElapsed);
	VOID		Destroy();

protected:
	CNameNotifyGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			Update_FadeIn();
	VOID			Update_Idle();
	VOID			Update_FadeOut();

	VOID			PositionAlign(RwInt32 iScreenWidth, RwInt32 iScreenHeight);

protected:
	gui::CStaticBox*	m_pMessageStatic;

	RwReal				m_fElapsedTime;
	VOID				(CNameNotifyGui::*m_pStateUpdate)();
};