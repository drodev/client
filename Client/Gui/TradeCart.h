/******************************************************************************
* File			: TradeCart.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 8. 1
* Abstract		: 
*****************************************************************************
* Desc			: Trade �� �̿��� ���� īƮ
*				  BuySlot�� Serial�� ���������̺� ���� ����
*				  SellSlot�� Serial�� Sob�� ���� ����
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

struct sSHOP_BUY_CART;
struct sSHOP_SELL_CART;
struct SDboEventShop;

class CTradeCart : public CNtlPLGui, public RWS::CEventHandler
{
public:	
	CTradeCart(const RwChar* pName);
	virtual ~CTradeCart();

	enum eTradeCartDefinedValue
	{		
		MAX_SLOT				= 12,	///< Buy, Sell�� ���� �����Ǵ� ������ �ִ� ���� ����		
	};

	enum
	{
		BUY_SLOT,
		SELL_SLOT,

		SLOTKIND_NUM
	};

	enum eTradeCartTextureType
	{
		TRADECART_TEXTURE_NORMAL,
		TRADECART_TEXTURE_TENKAICHI
	};

	struct MouseDownSlot
	{
		RwInt32		iSlotKind;
		RwInt32		iSlotIndex;

		MouseDownSlot()
		{
			iSlotKind = -1;
			iSlotIndex = -1;
		}
	};

	struct BuySlotInfo
	{
		sSHOP_BUY_CART		NPCShopBuyInfo;		///< ������ �ѱ�� ���� ����		
		CRegularSlotGui			slot;
		sITEM_DATA			TakeItem;			///< ������ �ŷ��� ���� ������
		SERIAL_HANDLE		hGiveHandle;		///< ������ �ŷ��� ���� �������� �ڵ�(������ ����, ���� �ڽ��� ������ ������ �ʴ�.)

		BuySlotInfo()
		:hGiveHandle(INVALID_SERIAL_ID)
		{
			memset((void*)&TakeItem, 0, sizeof(TakeItem) );
			TakeItem.itemNo = INVALID_SERIAL_ID;
		}
	};

	struct  SellSlotInfo 
	{		
		sSHOP_SELL_CART		NPCShopSellInfo;	///< ������ �ѱ�� ���� ����
		CRegularSlotGui			slot;
	};

	RwBool			Create();
	VOID			Destroy();

	VOID			OpenCart(eDialogType eType, RwUInt32 uiSerial);		///< īƮ UI�� ����
	VOID			CloseCart(eDialogType eType);						///< īƮ�� �ݴ´�.

	RwInt32			SwitchDialog(bool bOpen);			///< DialogManager������ Open/Close

	RwUInt32		GetTargetSerial();

	///< �ڽ��� ��� �� �������� ���ϰų� ����.
	///< iSlotKind : BUY_SLOT, SELL_SLOT
	///< iSlotY : Trade Slot Index
	///< iCount : ����
	VOID			AddItem(RwInt32 iSlotKind, RwInt32 iSlotY, RwInt32 iCount, RwUInt32 itemTblidx);
	VOID			SubItem(RwInt32 iSlotKind, RwInt32 iSlotY, RwInt32 iCount, RwUInt32 itemTblidx);

protected:
	CTradeCart() {}
	virtual VOID	HandleEvents( RWS::CMsg &pMsg );

	VOID			ResetCartTexture(eTradeCartTextureType eType);

	VOID			Clear();									///< Ʈ���̵� īƮ�� ������ �����.
	VOID			ClearSlot(RwInt32 iSlotKind, RwInt32 iSlot);///< �ش� ������ ������ �����.

	VOID			AddItemCount(RwInt32 iSlotKind, RwInt32 iSlot, RwInt32 iCount, RwUInt32 itemSerial);	///< ������ ������ ������ ���ϰų� ����.
	VOID			UpdateCount(RwUInt8 bySlotKind, RwUInt8 bySlot, RwUInt8 byCount);

	VOID			CalcTotalBuyPrice();						///< �� ���Ծ� ���
	VOID			CalcTotalSellPrice();						///< �� �Ǹž� ���

	///< NPCShop �Ǵ� �κ����� �������� �ø��� ����� ���� �з�
	VOID			RegBuyItemByDrag(RwInt32 iSlot);
	VOID			RegSellItemByDrag(RwInt32 iSlot);

	VOID			RegBuyItemByEvent(RwInt32 iSlot, SDboEventShop& TradeInfo);	
	VOID			RegSellItemByEvent(RwInt32 iSlot, SDboEventShop& TradeInfo);

	// ���� Ʈ���̵忡�� �������� ����� ��
	VOID			RegTakeItemByPacket(RwInt32 iSlot, SERIAL_HANDLE hTakeHandle, sITEM_DATA* pITEM_DATA, RwUInt8 byCount);
	VOID			RegGiveItemByPacket(RwInt32 iSlot, RwUInt32 uiSerial, RwUInt8 byCount);

	RwInt32			FindEmptySlot(RwInt32 iSlotType);			///< Slot ������ ����ִ� ���� ���� ������ ������ ã�´�.
	RwUInt8			FindSlot(RwUInt8 bySlotType, RwUInt32 uiSerial);
	RwInt32			PtinSlot(RwInt32 iSlotKind, RwInt32 iX, RwInt32 iY);

	VOID			CheckInfoWindow();							///< ��Ȳ�� ���� ���������츦 �ݴ´�
	
	VOID			FocusEffect( RwBool bPush, RwInt32 iSlotKind = 0, RwInt32 iSlotIdx = -1 );		///< ���� ��Ŀ�� ����Ʈ

	VOID			OnPaint();
	VOID			OnPostPaint();

	VOID			ClickedCloseButton(gui::CComponent* pComponent);

	VOID			ClickedZennyButton(gui::CComponent* pComponent);

	VOID			ClickedBuyButton(gui::CComponent* pComponent);		///< ������ ��ǰ���� ���.
	VOID			ClickedSellButton(gui::CComponent* pComponent);		///< ������ ��ǰ���� �Ǵ�.

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
	gui::CSlot			m_slotPostPaint;
	gui::CSlot			m_slotCaptureMouseDown;
	gui::CSlot			m_slotCloseButton;
	gui::CSlot			m_slotRightLockButton;
	gui::CSlot			m_slotRightUnlockButton;
	gui::CSlot			m_slotBtnZenny;
	gui::CSlot			m_slotClickedBuy;
	gui::CSlot			m_slotClickedSell;
	gui::CSlot			m_slotUpButton[SLOTKIND_NUM][MAX_SLOT];
	gui::CSlot			m_slotDownButton[SLOTKIND_NUM][MAX_SLOT];

	RwInt8				m_byInfoWindowIndex;
	MouseDownSlot		m_MouseDownSlot;			///< ���콺�� ���� ����

	gui::CTexture*		m_pMoneyIconTexture;
	
	gui::CButton*		m_pExitButton;				///< â�ݱ� ��ư
	gui::CButton*		m_pZennyButton;				///< ���� ��ư(���� Ʈ���̵�� ������ ���� ��ư)
	gui::CButton*		m_pBuyButton;				///< ���� ��ư
	gui::CButton*		m_pSellButton;				///< �Ǹ� ��ư

	gui::CButton*		m_pUpButton[SLOTKIND_NUM][MAX_SLOT];	///< ������ ���� ���ϱ� ��ư
	gui::CButton*		m_pDownButton[SLOTKIND_NUM][MAX_SLOT];	///< ������ ���� ���� ��ư

	gui::CStaticBox*	m_pDialogName;				///< ���̾�α��� �̸� ����ƽ
	gui::CStaticBox*	m_pTotalBuyMoney;			///< �� ���� �ݾ�
	gui::CStaticBox*	m_pTotalSellMoney;			///< �� �Ǹ� �ݾ�

	CSurfaceGui			m_FocusEffect;				///< ���� ��Ŀ�� ����Ʈ
	CSurfaceGui			m_BuyBar;					///< ��� �����̽�
	CSurfaceGui			m_SellBar;					///< �ȱ� �����̽�
	CSurfaceGui			m_GiveBar;					///< �ޱ� �����̽�
	CSurfaceGui			m_TakeBar;					///< �ֱ� �����̽�
	CSurfaceGui			m_srfZennySlotDestination;	///< ���� ���� Destination �̹���

	CWindowby3			m_LeftLockSurface;			///< ���� ��� �����̽�
	CWindowby3			m_RightLockSurface;			///< ������ ��� �����̽�

	RwBool				m_bFocus;					///< ��Ŀ���� �����.
	bool				m_bLeftLock;				///< ���� ��ǰ ��� ���
	bool				m_bRightLock;				///< ������ ��ǰ ��� ���
	RwBool				m_bZennySlotDestination;

	eTradeCartTextureType m_eTextureType;			///< īƮ �ؽ�ó Ÿ��
	RwUInt32			m_uiSubjectSerial;			///< TradeCart�� ��� Serial
	eDialogType			m_eDialogType;				///< � �ŷ��� ���� īƮ�ΰ�
	RwInt32				m_iCurTabIndex;				///< ������ �� �ε���

	BuySlotInfo			m_BuySlotInfo[MAX_SLOT];	///< ���� ���� ����
	SellSlotInfo		m_SellSlotInfo[MAX_SLOT];	///< ������ ���� ����

	RwUInt32			m_uiTotalSellPrice;			///< �� �Ǹ� �ݾ�

	RwUInt8				m_byOthersEmptySlot;		///< ������ �ŷ��� ������ �ŷ� ������ �� ���Լ�
	RwUInt32			m_uiUserTradePacketCount;	///< ������ �ŷ��� ������Ʈ �� ������ ��Ŷ�� ����
};
