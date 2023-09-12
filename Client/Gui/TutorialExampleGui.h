/******************************************************************************
* File			: TutorialExampleGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2008. 4. 23
* Abstract		: 
*****************************************************************************
* Desc			: Ʃ�丮�� �������� �޼����� ǥ���Ѵ�
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// presetation
#include "NtlPLGui.h"

// simulation
#include "NtlSLDef.h"


class CTutorialExampleGui : public CNtlPLGui, public RWS::CEventHandler
{
public:	
	struct sShowHide
	{
		RwReal				fRemainTime;
		RwReal				fElapsedTime;
		RwBool				bShow;
	};

	CTutorialExampleGui(const RwChar* pName);
	virtual ~CTutorialExampleGui();

	RwBool		Create();
	VOID		Update(RwReal fElapsed);
	VOID		Destroy();

	RwInt32		SwitchDialog(bool bOpen);

protected:
	CTutorialExampleGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	RwBool			LoadFlash(const char* acFileName);
	VOID			LocateComponent();
	VOID			FinishFlash();

	VOID			OnMovieEnd(gui::CComponent* pComponent);
	VOID			OnMove(RwInt32 iOldX, RwInt32 iOldY);
	
protected:
	gui::CSlot			m_slotMovieEnd;
	gui::CSlot			m_slotMove;

	gui::CFlash*		m_pflashExample;

	sShowHide			m_ShowHide;
	RwReal				m_fSizeRate;
	RwInt32				m_iOffsetX, m_iOffsetY;
};