/******************************************************************************
* File			: PetitionSatisFactionGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2008. 10. 23
* Abstract		: 
*****************************************************************************
* Desc			: GM���� ��� ���� ������ �������� GUI
*****************************************************************************/

#pragma once

// presetation
#include "NtlPLGui.h"

// share
#include "NtlSharedType.h"
#include "NtlPetition.h"

#define dTEMP_GG	5

class CPetitionSatisfaction : public CNtlPLGui
{
public:
	CPetitionSatisfaction(const RwChar* pName);
	virtual ~CPetitionSatisfaction();

	RwBool		Create();
	VOID		Destroy();

	RwInt32		SwitchDialog(bool bOpen);

protected:
	CPetitionSatisfaction() {}

	VOID			OnClicked_CloseButton(gui::CComponent* pComponent);
	VOID			OnClicked_RadioToggleButton(gui::CComponent* pComponent, bool bToggled);
	VOID			OnClicked_SendButton(gui::CComponent* pComponent);

protected:
	gui::CSlot			m_slotCloseButton;
	gui::CSlot			m_slotRadioButton[dTEMP_GG];
	gui::CSlot			m_slotSendButton;

	gui::CStaticBox*	m_pDialogName;					///< ���̾�α� ����
	gui::CStaticBox*	m_pMessage;						///< �ȳ� �޼���
	gui::CStaticBox*	m_pToggleText[dTEMP_GG];		///< ������ �ؽ�Ʈ

	gui::CButton*		m_pCloseButton;					///< �ݱ� ��ư
	gui::CButton*		m_pRadioButton[dTEMP_GG];		///< ������ ���� ���� ��ư
	gui::CButton*		m_pSendButton;					///< ������ ������ ��ư

	RwInt32				m_iSelectedIndex;				///< ������ ������ �ε���

	PETITIONID			m_petitionID;
	ACCOUNTID			m_GMID;
};