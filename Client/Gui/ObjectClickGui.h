/******************************************************************************
* File			: ObjectClickGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2007. 11. 14
* Abstract		: 
*****************************************************************************
* Desc			: Ʈ���� ������Ʈ�� Ŭ������ ���� �̺�Ʈ�� �����ش�
*****************************************************************************/

#pragma once

#include <list>

// core
#include "ceventhandler.h"

// share
#include "NtlTimeQuest.h"

// sound
#include "GUISoundDefine.h"

// presentation
#include "NtlPLGui.h"

// simulation
#include "NtlSLDef.h"

// dbo
#include "SurfaceGui.h"

class CObjectClickGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CObjectClickGui(const RwChar* pName);
	virtual ~CObjectClickGui();

	RwBool		Create();
	VOID		Update(RwReal fElapsed);
	VOID		Destroy();

	RwInt32		SwitchDialog(bool bOpen);			///< DialogManager������ Open/Close

protected:
	CObjectClickGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			OnPaint();

protected:		
	gui::CSlot			m_slotPaint;

	SOUND_HANDLE		m_hSound;

	gui::CRadarEffect	m_TimeEffect;

	CSurfaceGui			m_srfNeedle;				///< �ٴ� �׸�
	CSurfaceGui			m_srfReflectedLight;		///< �ݻ籤	

	RwReal				m_fLastTime;
	RwReal				m_fRemainTime;

	RwBool				m_bActive;
	RwBool				m_bVisible;
};