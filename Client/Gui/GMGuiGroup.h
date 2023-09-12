/******************************************************************************
* File			: GMGuiGroup.h
* Author		: Haesung, Cho
* Copyright		: (��)NTL
* Date			: 2008. 11. 18
* Abstract		: 
*****************************************************************************
* Desc			: GM Mode�� ���� �� ���Ǵ� Gui�� Group
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

/**
* \ingroup GM�� Gui Group
*/

class CGMQuickSlotGui;

class CGMGuiGroup : public RWS::CEventHandler
{
public:
	CGMGuiGroup();
	~CGMGuiGroup();

	RwBool	Create();
	VOID	Destroy();

	VOID	HandleEvents( RWS::CMsg& msg );	

protected:
	CGMQuickSlotGui*			m_pGMQuickSlot;
};