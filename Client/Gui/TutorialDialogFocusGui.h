/******************************************************************************
* File			: TutorialDialogFocus.h
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


class CTutorialDialogFocus : public CNtlPLGui, public RWS::CEventHandler
{
public:	
	CTutorialDialogFocus(const RwChar* pName);
	virtual ~CTutorialDialogFocus();

	RwBool		Create();
	VOID		Update(RwReal fElapsed);
	VOID		Destroy();

	RwInt32		SwitchDialog(bool bOpen);

protected:
	CTutorialDialogFocus() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	RwBool			LoadFlash(const char* acFileName, gui::CFlash* pFlash);
	VOID			LocateComponent();
	VOID			FinishFlash();

	RwUInt32		ConvertIdicateTypetoDialog(RwUInt32 uiIndicateType);

	VOID			Display(RwUInt8 byType, RwChar* pcFlashName, const RwV2d* pFocusOffset);

	VOID			OnResize(RwInt32 iOldW, RwInt32 iOldH );

protected:
	gui::CSlot			m_slotResize;

	gui::CFlash*		m_pflashFocus;

	RwUInt32			m_uiFocusDialog;
	RwV2d				m_v2FocusOffset;
};