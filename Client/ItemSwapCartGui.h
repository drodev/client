/******************************************************************************
* File			: ItemSwapCartGui.h
* Author		: Daneos
* Copyright		: Daneos
* Date			: 14-sep-2018
* Abstract		:
*****************************************************************************
* Desc			: Item exchange cart
*				  SellSlot's Serial writes Sob's
*****************************************************************************/

#pragma once

#include "SlotGui.h"
#include "gui_slot.h"
#include "NtlPLGui.h"
#include "NtlSLDef.h"
#include "ceventhandler.h"
#include "eventtimer.h"
#include "gui_button.h"
#include "gui_staticbox.h"
#include "NtlPacketUG.h"
#include "Windowby3.h"

struct sSHOP_SELL_CART;
struct SDboEventShop;

class CItemSwapCartGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CItemSwapCartGui(const RwChar* pName);
	virtual ~CItemSwapCartGui();

	enum eItemSwapCartDefinedValue
	{
		MAX_SLOT = 12,	///< Max sell slots	
	};

	struct  SellSlotInfo
	{
		sSHOP_SELL_CART		NPCShopSellInfo;	///< Information for passing to the server
		CRegularSlotGui		slot;
	};

	RwBool			Create();
	VOID			Destroy();

	VOID			OpenCart(RwUInt32 uiSerial);		///< Open the cart UI
	VOID			CloseCart();						///< Close cart

	RwInt32			SwitchDialog(bool bOpen);			///< DialogManager������ Open/Close

	RwUInt32		GetTargetSerial();

	///< Add or subtract items you sell
	///< iSlotY : Trade Slot Index
	///< iCount : amount
	VOID			AddItem(RwInt32 iSlotY, RwInt32 iCount, RwUInt32 itemTblidx);
	VOID			SubItem(RwInt32 iSlotY, RwInt32 iCount, RwUInt32 itemTblidx);

protected:
	CItemSwapCartGui() {}
	virtual VOID	HandleEvents(RWS::CMsg &pMsg);

	VOID			ResetCartTexture();

	VOID			Clear();									///< Ʈ���̵� īƮ�� ������ �����.
	VOID			ClearSlot(RwInt32 iSlot);///< �ش� ������ ������ �����.

	VOID			AddItemCount(RwInt32 iSlot, RwInt32 iCount, RwUInt32 itemSerial);	///< ������ ������ ������ ���ϰų� ����.
	VOID			UpdateCount(RwUInt8 bySlot, RwUInt8 byCount);

	VOID			CalcTotalSellPrice();						///< Calculate total sale price

	VOID			RegSellItemByDrag(RwInt32 iSlot);

	VOID			RegBuyItemByEvent(SDboEventShop& TradeInfo);
	VOID			RegSellItemByEvent(RwInt32 iSlot, SDboEventShop& TradeInfo);

	RwInt32			FindEmptySlot();			///< Slot ������ ����ִ� ���� ���� ������ ������ ã�´�.
	RwUInt8			FindSlot(RwUInt32 uiSerial);
	RwInt32			PtinSlot(RwInt32 iX, RwInt32 iY);

	VOID			CheckInfoWindow();							///< ��Ȳ�� ���� ���������츦 �ݴ´�

	VOID			FocusEffect(RwBool bPush, RwInt32 iSlotIdx = -1);		///< ���� ��Ŀ�� ����Ʈ

	VOID			OnPaint();

	VOID			ClickedSellButton(gui::CComponent* pComponent);		///< ������ ��ǰ���� �Ǵ�.

	VOID			ClickUpButton(gui::CComponent* pComponent);	///< ������ ���� ���ϱ� ��ư�� ������
	VOID			ClickDownButton(gui::CComponent* pComponent);	///< ������ ���� ���� ��ư�� ������

	VOID			OnMouseDown(const CKey& key);
	VOID			OnMouseUp(const CKey& key);
	VOID			OnMove(RwInt32 iOldX, RwInt32 iOldY);
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

	gui::CSlot			m_slotRightLockButton;
	gui::CSlot			m_slotRightUnlockButton;

	gui::CSlot			m_slotClickedSell;
	gui::CSlot			m_slotUpButton[MAX_SLOT];
	gui::CSlot			m_slotDownButton[MAX_SLOT];

	RwInt8				m_byInfoWindowIndex;

	gui::CTexture*		m_pMoneyIconTexture;

	gui::CButton*		m_pExitButton;				///< â�ݱ� ��ư

	gui::CButton*		m_pSellButton;				///< �Ǹ� ��ư

	gui::CButton*		m_pUpButton[MAX_SLOT];		///< Item number plus button
	gui::CButton*		m_pDownButton[MAX_SLOT];	///< Item number minus button

	gui::CStaticBox*	m_pTotalSellMoney;			///< �� �Ǹ� �ݾ�

	CSurfaceGui			m_FocusEffect;				///< ���� ��Ŀ�� ����Ʈ

	CSurfaceGui			m_SellBar;					///< �ȱ� �����̽�

	CWindowby3			m_LeftLockSurface;			///< ���� ��� �����̽�
	CWindowby3			m_RightLockSurface;			///< ������ ��� �����̽�

	RwBool				m_bFocus;					///< ��Ŀ���� �����.
	bool				m_bLeftLock;				///< ���� ��ǰ ��� ���
	bool				m_bRightLock;				///< ������ ��ǰ ��� ���

	RwUInt32			m_hNPCSerial;				///<

	RwInt32				m_iCurTabIndex;				///< ������ �� �ε���

	SellSlotInfo		m_SellSlotInfo[MAX_SLOT];	///< ������ ���� ����

	RwUInt32			m_uiTotalSellPrice;			///< �� �Ǹ� �ݾ�

	RwUInt8				m_byOthersEmptySlot;		///< ������ �ŷ��� ������ �ŷ� ������ �� ���Լ�
	RwUInt32			m_uiUserTradePacketCount;	///< ������ �ŷ��� ������Ʈ �� ������ ��Ŷ�� ����

	RwInt32				iMouseDownSlotIndex;
};
