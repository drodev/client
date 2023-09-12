/******************************************************************************
* File			: TutorialSideIconGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2008. 1. 22
* Abstract		: 
*****************************************************************************
* Desc			: Ʃ�丮�� ���̵� �������� ������ ���̵� �並 �����ִ� ����
*				  �ƴ϶� Ʃ�丮���� ������ ������ ���� �޼��� �ڽ��� ����
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// presentation
#include "NtlPLGui.h"

// dbo
#include "SideIconGui.h"

class CTutorialSideIconGui : public CSideIconBase
{
public:
	CTutorialSideIconGui(const RwChar* pName);
	virtual ~CTutorialSideIconGui();

	RwBool		Create();
	VOID		Destroy();

	virtual VOID	OnSideViewClosed();
	virtual VOID	OnIconButtonClicked(gui::CComponent* pComponent);	

protected:		
	gui::CSlot			m_slotIconButton;

	gui::CButton*		m_pIconButton;
};


class CTutorialSideViewGui : public CSideViewBase
{
public:
	CTutorialSideViewGui(const RwChar* pName);
	virtual ~CTutorialSideViewGui();

	RwBool		Create();
	VOID		Destroy();

	virtual VOID	OnPressESC();
	virtual VOID	OnSideViewOpen(const void* pData);
	virtual VOID	OnSideViewClose();
	virtual VOID	OnSideViewLocate(const CRectangle& rectSideIcon);	
};