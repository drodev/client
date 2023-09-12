/******************************************************************************
* File			: CounterGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2008. 11. 8
* Abstract		: 
* Update		: 
*****************************************************************************
* Desc			: ������ ī���͸� ���� GUI
*				  1. ī��Ʈ�� �پ��⸸ �ϰ� �þ�� �ʴ´�
*				  2. �� �ʸ��� �ð�Ҹ��� �� �� �ִ�
*				  3. ī��Ʈ�� �Ͻ������� ���� �� �ִ�
*				  4. ������ Pibot�� �������� 4���� ������� ��ġ�� �� �ִ�
*****************************************************************************/

#pragma once

// util
#include "NtlBitFlag.h"

// presentation
#include "NtlPLGui.h"

// dbo
#include "SurfaceGui.h"
#include "NumberGui.h"


enum eCounterDisplayType
{
	COUNTER_DISPLAY_1,		// 2D backgrounds can have different image sizes per hour
	COUNTER_DISPLAY_2,		// Flash background
};

enum eCounterQuadrant		// SetPosition The space to be sorted from the assignment specified by the function
{							//						||
	COUNTER_QUADRANT_1,		//			2��и�		||		1��и�
	COUNTER_QUADRANT_2,		//	================== Pibot ==================
	COUNTER_QUADRANT_3,		//			3��и�		||		4��и�
	COUNTER_QUADRANT_4		//						||
};

#define dCOUNTER_DISPLAY_FLAG_BIGGER	0x01		///< The GUI grows at certain times (COUNTER_DISPLAY_2 does not apply)


class CCounterGui : public CNtlPLGui
{
public:
	CCounterGui(const RwChar* pName);
	virtual ~CCounterGui();

	RwBool			Create(eCounterDisplayType eDisplayType, RwReal fSecond, eCounterQuadrant eQuadrant = COUNTER_QUADRANT_4);
	virtual VOID	Update(RwReal fElapsed);
	virtual VOID	Destroy();

	VOID			SetTime(RwReal fSecond);				///< CCounterGui�� ���� �ð��� ������
	RwReal			GetTime();

	VOID			SetQuadrant(eCounterQuadrant eQuadrantType);

	///< fUsableSecond ���� ���� �ð��� �� �� "°��" �Ÿ��� �Ҹ��� ����
	VOID			AlarmSound(RwBool bActive, RwReal fUsableSecond = 10.f);

	VOID			SetDisplayFlag(RwUInt8 byFlag);
	VOID			UnsetDisplayFlag(RwUInt8 byFlag);

	VOID			Pause(RwBool bPause);
	RwBool			IsPause();

protected:
	CCounterGui() {}

	VOID			SetSizeRate(RwReal fRate);

	VOID			RelocatePosition_1();
	VOID			RelocatePosition_2();

	VOID			LoadSurface_1();
	VOID			LoadSurface_2();

	VOID			LoadNumberSurface();

	VOID			OnMove( RwInt32 iOldX, RwInt32 iOldY );
	VOID			OnPaintDisplay_1();
	VOID			OnPaintDisplay_2();

	VOID			OnFrameCallback_Display2(const char* pcParam, const char* pcParam2);

protected:
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotPaintDisplay_1;
	gui::CSlot			m_slotPaintDisplay_2;
	gui::CSlot			m_slotFrameCallbackDisplay2;

	gui::CFlash*		m_pflashBackground;

	CNumberGui			m_MinuteNumberGui;		///< �� ���� ǥ��
	CNumberGui			m_SecondNumberGui;		///< �� ���� ǥ��

	CSurfaceGui			m_srfNumberBack;

	eCounterDisplayType	m_eDisplayType;
	eCounterQuadrant	m_eQuadrant;

	RwReal				m_fElapsed;				///< ī��Ʈ ���� �ð�
	RwReal				m_fUsableAlarmTime;		///< �� �ð����� m_fElapsed�� �۾����� °�� �Ҹ��� ����
	RwReal				m_fSizeRate;			///< Number�� ������ ����

	RwInt32				m_iAlarmElapsed;		///< °�� �Ҹ��� ������ �ð�

	RwUInt8				m_byDisplayFlag;
	
	CPos				m_OriginalNumberBackGuiSize;

	RwBool				m_bPause;
	RwBool				m_bAlarmSound;
	RwBool				m_bRender;
};


inline VOID CCounterGui::SetTime(RwReal fSecond)
{
	m_fElapsed		= fSecond;
	m_iAlarmElapsed	= (RwInt32)fSecond;
}

inline RwReal CCounterGui::GetTime()
{
	return m_fElapsed;
}

inline VOID CCounterGui::AlarmSound(RwBool bActive, RwReal fUsableSecond /* = 10.f */)
{
	m_bAlarmSound		= bActive;
	m_fUsableAlarmTime	= fUsableSecond;
	m_iAlarmElapsed		= (RwInt32)fUsableSecond;
}

inline VOID CCounterGui::SetDisplayFlag(RwUInt8 byFlag)
{
	BIT_FLAG_SET(m_byDisplayFlag, byFlag);
}

inline VOID CCounterGui::UnsetDisplayFlag(RwUInt8 byFlag)
{
	BIT_FLAG_UNSET(m_byDisplayFlag, byFlag);
}

inline VOID CCounterGui::Pause(RwBool bPause)
{
	m_bPause = bPause;
}

inline RwBool CCounterGui::IsPause()
{
	return m_bPause;
}