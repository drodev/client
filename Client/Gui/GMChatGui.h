/******************************************************************************
* File			: GMChatGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2008. 10. 21
* Abstract		: 
*****************************************************************************
* Desc			: GM���� ä�� ���̾�α�
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// presetation
#include "NtlPLGui.h"

// cleint
#include "Windowby3.h"
#include "SurfaceGui.h"

class CGMChatGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CGMChatGui(const RwChar* pName);
	virtual ~CGMChatGui();

	RwBool		Create();
	VOID		Destroy();

	RwInt32		SwitchDialog(bool bOpen);

	// avooo's comment : GM ä���� ������ ������ �ƴϸ� �̹� �ٸ� ���̾�αװ�
	//					 �� ����� ���¿��� ���������� GM ä���� ���� �ڸ��� ���� ���� ����.
	//					 GM ä���� ������ ������ ��ġ�� ������ �� �ֵ��� �Ѵ�.
	virtual void	SetMovable(RwBool bMovable) {}

	VOID		SetGMText(const WCHAR* pwcText);

protected:
	CGMChatGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			OnGotFocus();
	VOID			OnLostFocus();
	VOID			OnInputReturn();
	VOID			OnIMEChange( RwInt32 uiIMEState );
	VOID			OnCaptureWheelMove(RwInt32 iFlag, RwInt16 sDelta, CPos& pos);

	VOID			OnMove( RwInt32 iOldX, RwInt32 iOldY );
	VOID			OnPaint();

protected:
	gui::CSlot			m_slotGotFocus;
	gui::CSlot			m_slotLostFocus;
	gui::CSlot			m_slotReturn;
	gui::CSlot			m_slotIMEChange;
	gui::CSlot			m_slotCaptureWheelMove;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotPaint;

	gui::COutputBox*	m_pOutDisplay;			// ��ȭ����
	gui::CStaticBox*	m_pDialogName;			// ���̾�α� ����
	gui::CStaticBox*	m_pIME;					// IME ����
	gui::CInputBox*		m_pInput;				// ���� ��ǲâ

	CWindowby3			m_BackPanel;			// ���
	CSurfaceGui			m_InputBack;			// ��ǲ ���
};