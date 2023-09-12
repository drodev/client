/******************************************************************************
* File			: ScouterGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 9. 13S
* Abstract		: 
*****************************************************************************
* Desc: Community-related dialog form
* Each page content is set according to PageType
* Messages and events are also passed to the active Page.
*****************************************************************************/
/*
#pragma once

#include "NtlPLGui.h"
#include "ItemSlot.h"
#include "ceventhandler.h"

#include "CommunityBase.h"
#include "gui_panel.h"

class CCommunityGui : public CCommunityBase
{
public:

	enum eCommunityPageType
	{
		PAGETYPE_PARTY,
		PAGETYPE_GUILD,
		PAGETYPE_RAID
	};

	CCommunityGui();
	CCommunityGui(const RwChar* pName);
	virtual ~CCommunityGui();

	VOID		Init();
	RwBool		Create();
	VOID		Destroy();

	RwInt32		SwitchDialog(bool bOpen);			///< DialogManager������ Open/Close

protected:
	virtual VOID	HandleEvents( RWS::CMsg &msg );	

	VOID			OnPaint();

	VOID			OnMouseDown(const CKey& key);
	VOID			OnMouseUp(const CKey& key);
	VOID			OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID			OnMouseLeave(gui::CComponent* pComponent);

protected:	
	gui::CSlot			m_slotMouseDown;
	gui::CSlot			m_slotMouseUp;
	gui::CSlot			m_slotMouseMove;
	gui::CSlot			m_slotMouseLeave;
	gui::CSlot			m_slotPaint;

	RwInt32				m_iMouseDownSlot;			///< ���콺�� ���� ������ �ε���

	RwInt32				m_iPageType;				///< ������ ������ Ÿ��

	CItemSlot			m_slot;						///< ����

	gui::CPanel*		m_pSlotFocusEffect;			///< ���� ��Ŀ�� ����Ʈ
};*/