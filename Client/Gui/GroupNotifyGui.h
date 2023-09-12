/******************************************************************************
* File			: GroupNotifyGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2008. 11. 5
* Abstract		: 
*****************************************************************************
* Desc			: ��� Ŀ�´�Ƽ �׷� �ȿ��� ���� ���� �̻��� ���� �����
*				  �ٸ� �׷������ �˸� �޼����� ���� �� ���
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// presentation
#include "NtlPLGui.h"

class CGroupNotifyGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CGroupNotifyGui(const RwChar* pName);
	virtual ~CGroupNotifyGui();

	RwBool		Create();
	VOID		Update(RwReal fElapsed);
	VOID		Destroy();

protected:
	CGroupNotifyGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			Update_FadeIn();
	VOID			Update_Idle();
	VOID			Update_FadeOut();

	VOID			PositionAlign(RwInt32 iScreenWidth, RwInt32 iScreenHeight);

protected:
	gui::CStaticBox*	m_pMessageStatic;

	RwReal				m_fElapsedTime;
	VOID				(CGroupNotifyGui::*m_pStateUpdate)();
};