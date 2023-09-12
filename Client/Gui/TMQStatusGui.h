/******************************************************************************
* File			: TMQStatusGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2007. 10. 29
* Abstract		: 
*****************************************************************************
* Desc			: TMQ ���� ����â
*****************************************************************************/

#pragma once

#include <list>

// core
#include "ceventhandler.h"

// share
#include "NtlTimeQuest.h"

// presentation
#include "NtlPLGui.h"

// simulation
#include "NtlSLDef.h"
#include "NtlSLEvent.h"

// dbo
#include "SurfaceGui.h"
#include "SlotGui.h"
#include "NumberGui.h"

class CLittleQuestContainer;

class CTMQStatusGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	struct sTimeBonus
	{
		RwReal		fElapsed;
		RwBool		bShow;
		CSurfaceGui	srfTimeBonus;
		CNumberGui	TimeBonusNum;
	};

	CTMQStatusGui(const RwChar* pName);
	virtual ~CTMQStatusGui();

	static VOID		CreateInstance();
	static VOID		DestroyInstance();

	RwBool		Create();
	VOID		Update(RwReal fElapsed);
	VOID		Destroy();

	RwInt32		SwitchDialog(bool bOpen);

protected:
	CTMQStatusGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			SetTMQPoint(RwInt32 iPoint);
	VOID			ShowBonusTime(RwReal fBonusTime);
	VOID			CheckInfoWindow();

	VOID			OnClicked_MinimizeButton(gui::CComponent* pComponent);
	VOID			OnClicked_SenarioButton(gui::CComponent* pComponent);
	VOID			OnClicked_InfoButton(gui::CComponent* pComponent);
	VOID			OnClicked_NextButton(gui::CComponent* pComponent);

	VOID			OnMove(RwInt32 iOldX, RwInt32 iOldY);
	VOID			OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID			OnMouseLeave(gui::CComponent* pComponent);
	VOID			OnPaint();
	VOID			OnPostPaint();

protected:		
	static CTMQStatusGui*	m_pInstance;

	gui::CSlot			m_slotMinimizeButton;
	gui::CSlot			m_slotSenarioButton;
	gui::CSlot			m_slotStageButton;
	gui::CSlot			m_slotNextButton;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotMouseMove;
	gui::CSlot			m_slotMouseLeave;
	gui::CSlot			m_slotPaint;
	gui::CSlot			m_slotPostPaint;

	gui::CStaticBox*	m_pDialogName;					///< ���̾�α��� �̸� ����ƽ
	gui::CStaticBox*	m_pInfo;						///< '����'
	gui::CStaticBox*	m_pPoint;						///< '����Ʈ'
	gui::CStaticBox*	m_pCurPoint;					///< ���� ����Ʈ
	gui::CStaticBox*	m_pQuest;						///< '����Ʈ'
	gui::CStaticBox*	m_pQuestTitle;					///< ����Ʈ ����
	gui::CStaticBox*	m_pQuestAim_1;					///< ����Ʈ ��ǥ 1
	gui::CStaticBox*	m_pQuestAim_2;					///< ����Ʈ ��ǥ 2
	gui::CStaticBox*	m_pQuestAim_3;					///< ����Ʈ ��ǥ 3
	gui::CStaticBox*	m_pQuestAim_4;					///< ����Ʈ ��ǥ 4
	
	gui::CButton*		m_pMinimizeButton;				///< �ּ�ȭ ��ư
	gui::CButton*		m_pStageButton;					///< �������� ����
	gui::CButton*		m_pSenarioButton;				///< �ó����� ��ư
	gui::CButton*		m_pNextButton;					///< ���� ����Ʈ ��ư

	gui::CFlickerEffect	m_SenarioButtonFlicker;
	gui::CFlickerEffect	m_StageButtonFlicker;

	CSurfaceGui			m_srfGaugeBack;					///< TMQ ����Ʈ �鼭���̽�
	CSurfaceGui			m_srfTMQContourLine_1;			///< ���м�
	CSurfaceGui			m_srfTMQContourLine_2;			///< ���м�
	CSurfaceGui			m_srfTMQContourLine_3;			///< ���м�
	CSurfaceGui			m_srfCouponSlot;				///< ���� ����

	gui::CProgressBar*	m_pTMQGauge;					///< TMQ ������

	CLittleQuestContainer* m_pTMQQuestContainer;
	CRegularSlotGui			m_CouponSlot;					///< ���� ����
};