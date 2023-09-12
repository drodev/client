/******************************************************************************
* File			: GroupChatGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2008. 10. 17
* Abstract		: 
*****************************************************************************
* Desc			: ä�ù��� �����Ͽ� �� ����� ������ �̾߱⸦ �Ѵ�
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// presetation
#include "NtlPLGui.h"

class CGroupChatGui : public CNtlPLGui
{
public:
	CGroupChatGui(const RwChar* pName);
	virtual ~CGroupChatGui();

	RwBool		Create();
	VOID		Destroy();

	RwInt32		SwitchDialog(bool bOpen);
	virtual VOID	HandleEvents( RWS::CMsg &msg );

protected:
	CGroupChatGui() {}
};