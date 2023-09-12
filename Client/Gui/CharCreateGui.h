			/******************************************************************************
* File			: CharCreateGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 12. 7
* Update		: 2007. 10. 11
* Abstract		: 
*****************************************************************************
* Desc			: CharCreateGui
*****************************************************************************/

#pragma once

#include <list>

// core
#include "ceventhandler.h"

// gui
#include "gui_button.h"

// presentation
#include "NtlPLGui.h"

// simulation
#include "Inputhandler.h"

// dbo
#include "Windowby3.h"
#include "SlotGui.h"

class CCharMakePartGui;
class CRaceExplainGui;
class CClassExplainGui;


class CCharCreateGuiGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	enum eRotation
	{
		ER_STOP,
		ER_TURN_LEFT,
		ER_TURN_RIGHT
	};

	struct sMOUSE_ROL
	{
		RwBool		bPressLeft;
		RwInt32		iOldX;
	};

public:
	CCharCreateGuiGui(const RwChar* pName);
	virtual ~CCharCreateGuiGui();

	RwBool		Create();
	VOID		Destroy();

	const WCHAR*	GetInputText();

	// ĳ���� ��������(�κ�)������ GUI�� ��Ʈ���� ���� �Լ�
	VOID		SwitchDialog(bool bShow);

protected:
	CCharCreateGuiGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			EnableButtons(bool bEnable);
	VOID			LocateComponent(RwInt32 IWidth, RwInt32 IHeight);

	VOID			OnPress_LeftTurnButton(gui::CComponent* pComponent);
	VOID			OnPress_RightTurnButton(gui::CComponent* pComponent);
	VOID			OnRelease_TurnButton(gui::CComponent* pComponent);

	VOID			OnClick_MakeButton(gui::CComponent* pComponent);
	VOID			OnClick_ReturnButton(gui::CComponent* pComponent);
	
	VOID			OnMouseDown(const CKey& key);
	VOID			OnMouseUp(const CKey& key);
	VOID			OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID			OnCaptureWheelMove( RwInt32 nFlag, RwInt16 sDelta, CPos& pos );
	VOID			OnCaptureMouseUp(const CKey& key);

	VOID			OnPaint();

public:
	gui::CSlot			m_slotPressLeftButton;
	gui::CSlot			m_slotReleaseLeftButton;
	gui::CSlot			m_slotPressRightButton;	
	gui::CSlot			m_slotReleaseRightButton;
	gui::CSlot			m_slotMakeButton;
	gui::CSlot			m_slotReturnButton;
	gui::CSlot			m_slotMouseDown;
	gui::CSlot			m_slotMouseUp;
	gui::CSlot			m_slotMouseMove;	
	gui::CSlot			m_slotCaptureWheelMove;
	gui::CSlot			m_slotCaptureMouseUp;
	gui::CSlot			m_slotPaint;

	gui::CButton*		m_pLeftRotButton;	///< ���� ȸ�� ��ư
	gui::CButton*		m_pRightRotButton;	///< ������ ȸ�� ��ư
	gui::CButton*		m_pReturnButton;	///< ���ư��� ��ư
	gui::CButton*		m_pMakeButton;		///< ����� ��ư

	CSurfaceGui			m_srfNameBack;		///< Name Back

	gui::CStaticBox*	m_pNameStatic;		///< '�̸�'

	gui::CInputBox*		m_pNameInput;		///< �̸� �Է¶�

	CRaceExplainGui*	m_pRaceExplainGui;	///< ���� ���� Gui
	CClassExplainGui*	m_pClassExplainGui;	///< Ŭ���� ���� Gui
	CCharMakePartGui*	m_pCharMakePartGui;	///< ĳ������ �� �κ��� �����ϴ� Ŭ����

	RwUInt8				m_byRotationState;	///< ĳ���� ȸ������

	sMOUSE_ROL			m_tMouseRol;
};