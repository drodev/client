/******************************************************************************
* File			: NPCShop.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 8. 1
* Abstract		:
*****************************************************************************
* Desc			: NPC ����
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

#include "NtlItem.h"

// gui
#include "eventtimer.h"

// presentation
#include "NtlPLGui.h"

// simulation
#include "NtlSLDef.h"

// dbo
#include "SurfaceGui.h"
#include "SlotGui.h"
#include "Windowby3.h"

struct sNPC_TBLDAT;
class CNtlSobActor;

class CItemSwapGui : public CNtlPLGui, public RWS::CEventHandler
{
#define dMAX_ITEM_PANEL		6			///< Shop�� ������ �г� ����

public:
	CItemSwapGui(const RwChar* pName);
	virtual ~CItemSwapGui();

	enum eShopType
	{
		SHOP_TYPE_NORMAL,
		SHOP_TYPE_TENKAICHI,
	};

	struct ItemPanel
	{
		CRegularSlotGui		slot;			///< slot
		gui::CPanel*		pItemPanel;		///< Item panel
		gui::CStaticBox*	pItemName;		///< �̸�
		gui::CStaticBox*	pPoint;			///< �ʿ��� ����Ʈ(����, õ������ ����ȸ ����Ʈ ��...)

		gui::CStaticBox*	pstbNeedItemCount;
		CRegularSlotGui		slotNeedItem;
	};

	struct ShopItem
	{
		SERIAL_HANDLE	hItem;
		std::wstring	wstrItemName;
		RwInt32			iCount;
		RwUInt32		uiPrice;

		std::wstring	wstrNeedItemName;

		sITEM_TBLDAT*	pITEM_DATA;
		sITEM_TBLDAT*	pNeedITEM_DATA;
	};

	VOID			Init();
	RwBool			Create();
	VOID			Destroy();

	RwInt32			SwitchDialog(bool bOpen);		///< DialogManager������ Open/Close

	SERIAL_HANDLE	GetNPCSerial();

protected:

	virtual VOID	HandleEvents(RWS::CMsg &msg);

	VOID			ResetCartTexture();

	VOID			OpenShop(SERIAL_HANDLE hNPC, sNPC_TBLDAT* pNPC_TBLDAT);	///< NPC ������ ����
	VOID			CloseShop();						///< NPC ������ �ݴ´�.	

	VOID			ClearShop();						///< Shop�� ������ �ʱ�ȭ �Ѵ�.
	VOID			ClearPanels();						///< �г� ���� ���� �ʱ�ȭ �Ѵ�.

	VOID			UpdateTabContent(RwUInt8 byIndex);	///< �ǿ� �´� ������ �����Ѵ�
	RwBool			SetPage(RwInt32 iPage);				///< ���� ������ ����
	VOID			SetPanel(RwInt32 iPage);			///< ���� �������� �´� ������ ����Ʈ�� �����ش�.
	VOID			SetPageButton();

	VOID			SetZenny();							///< �ڽ��� ������ ������ ������Ʈ �Ѵ�.

	VOID			SetRepairAllTooltip();				///< ���� ��ü ��������� ����Ͽ� ������ ǥ���Ѵ�

	RwUInt8			GetPageCount_of_CurTab();			///< ���� �ǿ� ���� �������� ������ ��ȯ�Ѵ�

	RwBool			IsFirstPage();
	RwBool			IsLastPage();

	RwInt8			PtinSlot(RwInt32 iX, RwInt32 iY);
	RwInt8			PtinSlot_of_SmallIcon_in_panel(RwInt32 iX, RwInt32 iY);
	VOID			FocusEffect(RwBool bPush, RwInt32 iSlotIdx = -1);
	VOID			SelectEffect(RwBool bPush, RwInt32 iSlotIdx = -1);
	VOID			CheckInfoWindow();

	VOID			OnPaint();
	VOID			OnPostPaint();

	VOID			OnSelectChangeTabButton(INT nCurIndex, INT nPrevIndex);	///< �� ��ư�� ������

	VOID			ClickedPrePageButton(gui::CComponent* pComponent);	///< ���� ��ư�� ������.
	VOID			ClickedNextPageButton(gui::CComponent* pComponent);	///< ���� ��ư�� ������.
	VOID			ClickedCloseButton(gui::CComponent* pComponent);	///< �ݱ� ��ư�� ������.
	VOID			ClickedRepairButton(gui::CComponent* pComponent);	///< ���� ��ư�� ������.
	VOID			ClickedRepairAllButton(gui::CComponent* pComponent);///< ��ü ���� ��ư�� ������.
	VOID			ClickedIdentifyButton(gui::CComponent* pComponent);	///< ������ ���� ��ư�� ������.

	VOID			OnMouseDown(const CKey& key);
	VOID			OnMouseUp(const CKey& key);
	VOID			OnMove(RwInt32 iOldX, RwInt32 iOldY);
	VOID			OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID			OnMouseLeave(gui::CComponent* pComponent);
	VOID			OnCaptureMouseDown(const CKey& key);


protected:
	gui::CSlot			m_slotMouseDown;
	gui::CSlot			m_slotMouseUp;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotMouseMove;
	gui::CSlot			m_slotMouseLeave;
	gui::CSlot			m_slotTab;
	gui::CSlot			m_slotPrePageButton;
	gui::CSlot			m_slotNextPageButton;
	gui::CSlot			m_slotCloseButton;
	gui::CSlot			m_slotRepairButton;
	gui::CSlot			m_slotRepairAllButton;
	gui::CSlot			m_slotIdentifyButton;
	gui::CSlot			m_slotPaint;
	gui::CSlot			m_slotPostPaint;
	gui::CSlot			m_slotCaptureMouseDown;

	RwInt8				m_byInfoWindowIndex;
	RwInt32				m_iMouseDownSlot;	///< ���콺�� ���� ������ �ε���
	RwInt32				m_iSelectedSlot;	///< ����Ʈ ����Ʈ ����
	RwInt32				m_iClickEffectedSlot;

	gui::CTabButton*	m_pTabButton;		//< �� ��ư

	ItemPanel			m_ItemPanel[dMAX_ITEM_PANEL];	///< ItemPanel

	CWindowby3			m_BackLineSurface;	///< �����

	CSurfaceGui			m_FocusEffect;		///< ���� ��Ŀ�� ����Ʈ
	CSurfaceGui			m_SelectEffect;		///< ���� ����Ʈ ����Ʈ
	CSurfaceGui			m_MoneyBackPanel;	///< ������ ���
	CSurfaceGui			m_PageBackPanel;	///< ������ ���

	gui::CButton*		m_pExitButton;		///< â�ݱ� ��ư
	gui::CButton*		m_pRepairButton;	///< ���� ��ư
	gui::CButton*		m_pRepairAllButton;	///< ��ü ���� ��ư
	gui::CButton*		m_pIdentifyButton;	///< ������ ���� ��ư	
	gui::CButton*		m_pPrePageButton;	///< ���� ������ �Ѿ�� ��ư
	gui::CButton*		m_pNextPageButton;	///< ���� ������ �Ѿ�� ��ư

	gui::CStaticBox*	m_pShopTitle;		///< ���� �̸�	

	gui::CStaticBox*	m_pPocketMoneytitle;///< ������ ����
	gui::CStaticBox*	m_pPocketMoney;		///< ������	
	gui::CStaticBox*	m_pCurrentPage;		///< ���� ������ ǥ��

	ShopItem			m_aShopItem[NTL_MAX_MERCHANT_TAB_COUNT][NTL_MAX_MERCHANT_COUNT];	/// �� �Ǻ��� �� �� �ִ� ������ ����

	SERIAL_HANDLE		m_hNPCSerial;		///< NPC ��ȣ

	RwInt32				m_iCurTab;			///< ���� �� �ε���
	RwInt32				m_iCurPage;			///< ���� ������

	RwBool				m_bFocus;			///< ��Ŀ���� �����.
};