/******************************************************************************
* File			: PetitionGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2008. 10. 23
* Abstract		: 
*****************************************************************************
* Desc			: GM ��� ��ûâ
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// presetation
#include "NtlPLGui.h"

// simulation
#include "NtlSLDef.h"

// cleint
#include "Windowby3.h"
#include "SurfaceGui.h"

class CPetitionGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CPetitionGui(const RwChar* pName);
	virtual ~CPetitionGui();

	RwBool		Create();
	VOID		Destroy();

	RwInt32		SwitchDialog(bool bOpen);

	// avooo's comment : GM ��� ��ûâ�� ������ ������ �ƴϸ� �̹� �ٸ� ���̾�αװ�
	//					 �� ����� ���¿��� ���������� �ڸ��� ���� ���� ����.
	//					 ������ ������ ��ġ�� ������ �� �ֵ��� �Ѵ�.
	virtual void	SetMovable(RwBool bMovable) {}

protected:
	CPetitionGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			EnableControll(bool bEnable);

	VOID			SetTextCategory(RwInt32 iSelect = INVALID_INDEX);
	VOID			SetTextCategory2(RwInt32 iSelect = INVALID_INDEX);

	const WCHAR*	GetCategory1Text(RwInt32 iSelect);
	const WCHAR*	GetCategory2Text(RwInt32 iSelect);

	VOID			OnClicked_CloseButton(gui::CComponent* pComponent);
	VOID			OnClicked_SendButton(gui::CComponent* pComponent);

	VOID			OnItemSelect( INT nIndex );
	VOID			OnItemSelect2( INT nIndex );
	
	VOID			OnGotFocus();
	VOID			OnLostFocus();
	VOID			OnMove( RwInt32 iOldX, RwInt32 iOldY );
	VOID			OnPaint();

protected:
	gui::CSlot			m_slotItemSelect;
	gui::CSlot			m_slotItemSelect2;
	gui::CSlot			m_slotCloseButton;
	gui::CSlot			m_slotSendButton;
	gui::CSlot			m_slotGotFocus;
	gui::CSlot			m_slotLostFocus;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotPaint;

	gui::CButton*		m_pCloseButton;			///< �ݱ� ��ư

	gui::CComboBox*		m_pCategory;			///< ��з� ī�װ�
	gui::CComboBox*		m_pCategory2;			///< �Һз� ī�װ�
	
	gui::CInputBox*		m_pInput;				///< ��������
	
	gui::CStaticBox*	m_pDialogName;			///< ���̾�α� ����
	gui::CStaticBox*	m_pCategoryStatic;		///< ��з� ī�װ�
	gui::CStaticBox*	m_pCategoryStatic2;		///< �Һз� ī�װ�
	gui::CStaticBox*	m_pCategoryMessage;		///< ��з� ī�װ� ���� �޼���
	gui::CStaticBox*	m_pCategoryMessage2;	///< �Һз� ī�װ� ���� �޼���
	
	gui::CButton*		m_pSendButton;			///< ���۹�ư

	CWindowby3			m_BackPanel;			///< ���
	CSurfaceGui			m_srfCaregoryBack;		///< ī�װ� 1 ���
	CSurfaceGui			m_srfCaregoryBack2;		///< ī�װ� 2 ���
};