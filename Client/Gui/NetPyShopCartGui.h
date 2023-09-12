/******************************************************************************
* File			: NetPyShopCartGui.h
* Author		: Cho Haesung
* Copyright		: (��)NTL
* Date			: 2009. 6. 25
* Abstract		: 
*****************************************************************************
* Desc			: Commercial ��� �� NetPyShop�� Cart GUI �� ����� �����ϴ� Class
*****************************************************************************/

#ifndef __NETPYSHOP_CART_GUI_H__
#define __NETPYSHOP_CART_GUI_H__

#pragma once

// Core
#include "ceventhandler.h"

// Shared
#include "NtlPacketUG.h"

// Gui
#include "eventtimer.h"
#include "gui_slot.h"
#include "gui_button.h"
#include "gui_staticbox.h"

// Presentation
#include "NtlPLGui.h"

// Simulation
#include "NtlSLDef.h"

// Dbo
#include "SlotGui.h"
#include "Windowby3.h"

struct sSHOP_BUY_CART;
struct SDboEventNetPyShopEvent;

#define dNETPYSHOP_CART_INVALID_INDEX		(-1)

class CNetPyShopCartGui : public CNtlPLGui, public RWS::CEventHandler
{
public:	
	CNetPyShopCartGui(const RwChar* pName);
	virtual ~CNetPyShopCartGui();

	enum eNetPyShopCartDefinedValue
	{		
		MAX_SLOT				= 12,	///< Buy, Sell�� ���� �����Ǵ� ������ �ִ� ���� ����		
	};

	struct MouseDownSlot
	{
		RwInt32		iSlotKind;
		RwInt32		iSlotIndex;

		MouseDownSlot()
		{
			iSlotKind = dNETPYSHOP_CART_INVALID_INDEX;
			iSlotIndex = dNETPYSHOP_CART_INVALID_INDEX;
		}
	};

	enum
	{
		BUY_SLOT,

		SLOTKIND_NUM
	};

	struct BuySlotInfo
	{
		sSHOP_BUY_CART		NPCShopBuyInfo;		///< ������ �ѱ�� ���� ����		
		CRegularSlotGui			slot;
	};

	RwBool			Create();
	VOID			Destroy();

	VOID			OpenCart();		///< īƮ UI�� ����
	VOID			CloseCart();						///< īƮ�� �ݴ´�.

	RwInt32			SwitchDialog(bool bOpen);			///< DialogManager������ Open/Close

	///< �ڽ��� ��� �� �������� ���ϰų� ����.
	///< iSlotKind : BUY_SLOT
	///< iSlotY : Trade Slot Index
	///< iCount : ����
	VOID			AddItem(RwInt32 iSlotKind, RwInt32 iSlotY, RwInt32 iCount);
	VOID			SubItem(RwInt32 iSlotKind, RwInt32 iSlotY, RwInt32 iCount);

protected:
	CNetPyShopCartGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &pMsg );

	VOID			Clear();									///< Ʈ���̵� īƮ�� ������ �����.
	VOID			ClearSlot(RwInt32 iSlotKind, RwInt32 iSlot);///< �ش� ������ ������ �����.

	VOID			AddItemCount(RwInt32 iSlotKind, RwInt32 iSlot, RwInt32 iCount);	///< ������ ������ ������ ���ϰų� ����.
	VOID			UpdateCount(RwUInt8 bySlotKind, RwUInt8 bySlot, RwUInt8 byCount);

	VOID			CalcTotalBuyPrice();						///< �� ���Ծ� ���

	///< NPCShop �Ǵ� �κ����� �������� �ø��� ����� ���� �з�
	VOID			RegBuyItemByDrag(RwInt32 iSlot);	
	VOID			RegBuyItemByEvent(RwInt32 iSlot, SDboEventNetPyShopEvent& TradeInfo);	

	RwInt32			FindEmptySlot(RwInt32 iSlotType);			///< Slot ������ ����ִ� ���� ���� ������ ������ ã�´�.
	RwInt32			FindSlot(RwUInt8 bySlotType, RwUInt32 uiSerial);
	RwInt32			PtinSlot(RwInt32 iSlotKind, RwInt32 iX, RwInt32 iY);

	VOID			CheckInfoWindow();							///< ��Ȳ�� ���� ���������츦 �ݴ´�

	VOID			FocusEffect( RwBool bPush, RwInt32 iSlotKind = 0, RwInt32 iSlotIdx = -1 );		///< ���� ��Ŀ�� ����Ʈ

	VOID			OnPaint();

	VOID			ClickedCloseButton(gui::CComponent* pComponent);
	VOID			ClickedBuyButton(gui::CComponent* pComponent);		///< ������ ��ǰ���� ���.
	
	VOID			ClickUpButton(gui::CComponent* pComponent);	///< ������ ���� ���ϱ� ��ư�� ������
	VOID			ClickDownButton(gui::CComponent* pComponent);	///< ������ ���� ���� ��ư�� ������

	VOID			OnMouseDown(const CKey& key);
	VOID			OnMouseUp(const CKey& key);
	VOID			OnMove( RwInt32 iOldX, RwInt32 iOldY );
	VOID			OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID			OnMouseLeave(gui::CComponent* pComponent);
	VOID			OnCaptureWheelMove(RwInt32 iFlag, RwInt16 sDelta, CPos& pos);
	VOID			OnCaptureMouseDown(const CKey& key);

protected:
	gui::CSlot			m_slotMouseDown;
	gui::CSlot			m_slotMouseUp;
	gui::CSlot			m_slotMouse;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotMouseMove;
	gui::CSlot			m_slotMouseLeave;
	gui::CSlot			m_slotCaptureWheelMove;
	gui::CSlot			m_slotPaint;
	gui::CSlot			m_slotCaptureMouseDown;
	gui::CSlot			m_slotCloseButton;
	gui::CSlot			m_slotBtnZenny;
	gui::CSlot			m_slotClickedBuy;
	gui::CSlot			m_slotUpButton[SLOTKIND_NUM][MAX_SLOT];
	gui::CSlot			m_slotDownButton[SLOTKIND_NUM][MAX_SLOT];

	RwInt8				m_byInfoWindowIndex;
	MouseDownSlot		m_MouseDownSlot;			///< ���콺�� ���� ����

	gui::CTexture*		m_pMoneyIconTexture;

	gui::CButton*		m_pExitButton;				///< â�ݱ� ��ư
	gui::CButton*		m_pBuyButton;				///< ���� ��ư

	gui::CButton*		m_pUpButton[SLOTKIND_NUM][MAX_SLOT];	///< ������ ���� ���ϱ� ��ư
	gui::CButton*		m_pDownButton[SLOTKIND_NUM][MAX_SLOT];	///< ������ ���� ���� ��ư

	gui::CStaticBox*	m_pDialogName;				///< ���̾�α��� �̸� ����ƽ
	gui::CStaticBox*	m_pTotalBuyMoney;			///< �� ���� �ݾ�
	gui::CStaticBox*	m_pTotalSellMoney;			///< �� �Ǹ� �ݾ�

	CSurfaceGui			m_FocusEffect;				///< ���� ��Ŀ�� ����Ʈ
	CSurfaceGui			m_BuyBar;					///< ��� �����̽�

	RwBool				m_bFocus;					///< ��Ŀ���� �����.	

	RwInt32				m_iCurTabIndex;				///< ������ �� �ε���

	BuySlotInfo			m_BuySlotInfo[MAX_SLOT];	///< ���� ���� ����
	
	RwUInt32			m_uiTotalBuyPrice;			///< �� ���� �ݾ�
};


#endif