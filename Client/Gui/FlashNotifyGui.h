/******************************************************************************
* File			: FlashNotifyGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2007. 11. 21
* Abstract		: 
*****************************************************************************
* Desc			: �˸� �޼����� ���� ������ �÷��� ������ �о�鿩 ǥ���Ѵ�
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// presentation
#include "NtlPLGui.h"

class CFlashNotifyGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CFlashNotifyGui(const RwChar* pName);
	virtual ~CFlashNotifyGui();

	RwBool		Create();
	VOID		Update(RwReal fElapsed);
	VOID		Destroy();

	RwInt32		SwitchDialog(bool bOpen);

protected:
	CFlashNotifyGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );	

	RwBool			LoadFlash(const char* acFileName, RwBool bFrameCallback = FALSE);
	VOID			LocateComponent();
	VOID			FinishFlash();

	VOID			OnMovieEnd(gui::CComponent* pComponent);

protected:	
	gui::CSlot			m_slotMovieEnd;

	gui::CFlash*		m_pFlashBackground;

	std::string			m_strSecondFile;		///< �� ��°�� �÷��� �� ������ �̸�
	RwBool				m_bFinishNotify;
};