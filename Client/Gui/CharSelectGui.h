/******************************************************************************
* File			: CharCreateGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 12. 8
* Update		: 2007. 10. 11
* Abstract		:
*****************************************************************************
* Desc			: CCharSelectGui
*****************************************************************************/

#pragma once

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

class CCharSelecterGui;
class CChannelSelectGui;
class CCharacterInfoGui;
class CAccountGui;


class CCharSelectGui : public CNtlPLGui, public RWS::CEventHandler
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
	CCharSelectGui(const RwChar* pName);
	virtual ~CCharSelectGui();

	RwBool		Create();
	VOID		Destroy();

	RwUInt8		GetSelectedChannelIndex();

	// ĳ���� ��������(�κ�)������ GUI�� ��Ʈ���� ���� �Լ�
	VOID		SwitchDialog(bool bShow);
	VOID		EnableButtons(bool bEnable);

protected:
	CCharSelectGui() {}
	virtual VOID	HandleEvents(RWS::CMsg &msg);

	VOID			LocateComponent(RwInt32 IWidth, RwInt32 IHeight);

	VOID			OnPress_LeftTurnButton(gui::CComponent* pComponent);
	VOID			OnPress_RightTurnButton(gui::CComponent* pComponent);
	VOID			OnRelease_TurnButton(gui::CComponent* pComponent);
	VOID			OnClickedGameStartButton(gui::CComponent* pComponent);
	VOID			OnClickedExitButton(gui::CComponent* pComponent);
	VOID			OnMouseDown(const CKey& key);
	VOID			OnMouseUp(const CKey& key);
	VOID			OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID			OnCaptureWheelMove(RwInt32 nFlag, RwInt16 sDelta, CPos& pos);
	VOID			OnCaptureMouseUp(const CKey& key);

protected:
	gui::CSlot			m_slotPressLeftButton;
	gui::CSlot			m_slotReleaseLeftButton;
	gui::CSlot			m_slotPressRightButton;
	gui::CSlot			m_slotReleaseRightButton;
	gui::CSlot			m_slotGameStartButton;
	gui::CSlot			m_slotExitButton;
	gui::CSlot			m_slotMouseDown;
	gui::CSlot			m_slotMouseUp;
	gui::CSlot			m_slotMouseMove;
	gui::CSlot			m_slotCaptureWheelMove;
	gui::CSlot			m_slotCaptureMouseUp;

	gui::CButton*		m_pLeftRotButton;	///< ���� ȸ�� ��ư
	gui::CButton*		m_pRightRotButton;	///< ������ ȸ�� ��ư
	gui::CButton*		m_pGameStartButton;	///< ���� ���� ��ư
	gui::CButton*		m_pExitButton;		///< ������ ��ư

	CAccountGui*		m_pAccountGui;		///< ���� ���� GUI
	CCharacterInfoGui*	m_pCharacterInfoGui;///< ĳ���� ���� GUI
	CCharSelecterGui*	m_pCharSelecterGui;	///< ĳ���� ���ñ� GUI
	CChannelSelectGui*	m_pChannelSelectGui;///< ä�� ����Ʈ GUI

	RwUInt8				m_byRotationState;	///< ĳ���� ȸ������

	sMOUSE_ROL			m_tMouseRol;		///< ���콺�� �̿��� ĳ���� ȸ��
};