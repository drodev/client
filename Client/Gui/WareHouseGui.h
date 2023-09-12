/******************************************************************************
* File			: CWarehouseGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 11. 20
* Abstract		: 
*****************************************************************************
* Desc			: CWarehouseGui
*				  �� ĳ���Ͱ� ������ 16ĭ�� �Ϲ�â�� 3��
*				  �� ������ ��� ĳ���Ͱ� �����ϴ� 16ĭ�� ����â�� ����
*				  ���ϴ� ����â���� ����Ǵ� �����ν� �� ������ ��� ĳ����
*				  �� �����Ѵ�
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// share
#include "NtlItem.h"

// presetation
#include "NtlPLGui.h"

// simulation
#include "NtlSLDef.h"

// dbo
#include "SlotGui.h"


//////////////////////////////////////////////////////////////////////////
//	CWarehouseGui
//////////////////////////////////////////////////////////////////////////

class CWarehouseGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CWarehouseGui(const RwChar* pName);
	virtual ~CWarehouseGui();

	RwBool		Create();
	VOID		Destroy();

	RwInt32		SwitchDialog(bool bOpen);		///< DialogManager������ Open/Close

	VOID		RegisterWarehouseIndex(RwUInt8 byIndex);
	VOID		ShowDisableSlot(RwBool bShow, RwUInt8 bySlot);

protected:
	CWarehouseGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			Init();

	VOID			UpdateItems();

	RwInt8			PtinSlot(RwInt32 iX, RwInt32 iY);				///< ���콺�� �������� ���� ������ ã�´�.
	VOID			FocusEffect( RwBool bPush, RwInt32 iSlotIdx = -1);
	VOID			SelectEffect( RwBool bPush, RwInt32 iSlotIdx = -1);	
	VOID			CheckInfoWindow();

	VOID			ClickedCloseButton(gui::CComponent* pComponent);

	VOID			OnMouseDown(const CKey& key);
	VOID			OnMouseUp(const CKey& key);
	VOID			OnMove( RwInt32 iOldX, RwInt32 iOldY );
	VOID			OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID			OnMouseLeave(gui::CComponent* pComponent);

	VOID			OnPaint();
	VOID			OnCaptureMouseDown(const CKey& key);

protected:
	gui::CSlot			m_slotMouseDown;
	gui::CSlot			m_slotMouseUp;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotMouseMove;
	gui::CSlot			m_slotMouseLeave;
	gui::CSlot			m_slotPaint;
	gui::CSlot			m_slotCloseButton;
	gui::CSlot			m_slotCaptureMouseDown;

	gui::CButton*		m_pExitButton;		///< â�ݱ� ��ư

	RwInt8				m_byInfoWindowIndex;
	RwInt32				m_iMouseDownSlot;	///< ���콺�� ���� ������ �ε���
	RwInt32				m_iSelectedSlot;	///< ����Ʈ ����Ʈ ����
	RwInt32				m_iClickEffectedSlot;///< ���� Ŭ�� ����Ʈ�� ���� ����

	gui::CStaticBox*	m_pDialogName;		///< ���̾�α��� �̸� ����ƽ

	CSurfaceGui			m_FocusEffect;		///< ���� ��Ŀ�� ����Ʈ
	CSurfaceGui			m_SelectEffect;		///< ���� ����Ʈ ����Ʈ

	RwUInt8				m_byWarehouseIndex;	///< �� ��° â������

	RwBool				m_bFocus;			///< ��Ŀ���� �����.

	CRegularSlotGui			m_Slot[NTL_MAX_BANK_ITEM_SLOT];	///< ������ ����
};


//////////////////////////////////////////////////////////////////////////
//	CWarehouseCommon
//////////////////////////////////////////////////////////////////////////

class CWarehouseCommonGui : public CWarehouseGui
{
public:
	CWarehouseCommonGui(const RwChar* pName);
	virtual ~CWarehouseCommonGui();

	RwBool		Create();
	VOID		Destroy();

	VOID		SetNPCHandle(SERIAL_HANDLE hHandle);
	SERIAL_HANDLE GetNPCHandle();

protected:
	CWarehouseCommonGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			ClickedZennyButton(gui::CComponent* pComponent);

	VOID			OnPostPaint();

protected:
	gui::CSlot			m_slotZennyButton;
	gui::CSlot			m_slotPostPaint;

	gui::CButton*		m_pZennyButton;
	gui::CStaticBox*	m_pZenny;
	gui::CTexture*		m_pMoneyIconTexture;

	CSurfaceGui			m_srfZennySlotDestination;	///< ���� ���� Destination �̹���

	RwBool				m_bZennySlotDestination;
	RwUInt32			m_uiZenny;
	SERIAL_HANDLE		m_hNPCSerial;		///< â������ NPC Serial
};


//////////////////////////////////////////////////////////////////////////
//	CWarehouseBar
//////////////////////////////////////////////////////////////////////////

class CWarehouseBarGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CWarehouseBarGui(const RwChar* pName);
	virtual ~CWarehouseBarGui();

	RwBool		Create();
	VOID		Destroy();

	RwInt32		SwitchDialog(bool bOpen);		///< DialogManager������ Open/Close

	VOID		RegisterWarehouse(RwUInt8 byIndex, CWarehouseGui* pWarehouseGui);
	SERIAL_HANDLE	GetNPCSerial();

protected:
	CWarehouseBarGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			CloseWarehouse();

	VOID			Clicked_1_Button(gui::CComponent* pComponent);
	VOID			Clicked_2_Button(gui::CComponent* pComponent);
	VOID			Clicked_3_Button(gui::CComponent* pComponent);
	VOID			Clicked_Common_Button(gui::CComponent* pComponent);
	VOID			ClickedAllButton(gui::CComponent* pComponent);
	VOID			ClickedCloseButton(gui::CComponent* pComponent);

	VOID			OnMove(RwInt32 iOldX, RwInt32 iOldY);
	VOID			OnCaptureMouseDown(const CKey& key);

protected:
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotWarehouseBtn[NTL_MAX_BANKSLOT_COUNT];
	gui::CSlot			m_slot_All_Button;
	gui::CSlot			m_slotCloseButton;
	gui::CSlot			m_slotCaptureMouseDown;

	gui::CButton*		m_pWarehouseBtn[NTL_MAX_BANKSLOT_COUNT];///< â�� ��ư
	gui::CButton*		m_p_All_Button;		///< ��� â�� ��ư
	gui::CButton*		m_pExitButton;		///< â�ݱ� ��ư
	
	SERIAL_HANDLE		m_hNPCSerial;		///< â������ NPC Serial

	CWarehouseGui*		m_pWareHouseGui[NTL_MAX_BANKSLOT_COUNT];
};