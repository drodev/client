/******************************************************************************
* File			: NetPyShopGui.h
* Author		: Cho Haesung
* Copyright		: (��)NTL
* Date			: 2009. 6. 25
* Abstract		: 
*****************************************************************************
* Desc			: Commercial ��� �� NetPyShop�� GUI �� ����� �����ϴ� Class
*****************************************************************************/

#ifndef __NETPYSHOP_GUI_H__
#define __NETPYSHOP_GUI_H__

#pragma once

// Core
#include "ceventhandler.h"


// Shared
#include "NtlItem.h"

// Gui
#include "eventtimer.h"

// Presentation
#include "NtlPLGui.h"

// Simulation
#include "NtlSLDef.h"

// Client
#include "SurfaceGui.h"
#include "SlotGui.h"
#include "Windowby3.h"

struct sNPC_TBLDAT;
class CNtlSobActor;

#define dNETPYSHOP_INVALID_INDEX		(-1)

class CNetPyShopGui : public CNtlPLGui, public RWS::CEventHandler
{
#define dFIRST_PAGE			0
#define dMAX_PAGE			4			///< �� �� �� ��� �� �ִ� �ִ� ������
#define dMAX_ITEM_PANEL		6			///< Shop�� ������ �г� ����
#define dNETPYSHOP_TAB_NUMS 4

public:
	CNetPyShopGui(const RwChar* pName);
	virtual ~CNetPyShopGui();

	enum eShopType
	{
		SHOP_TYPE_NETPY,

		SHOP_TYPE_NUMS,
		SHOP_TYPE_INVALID = 0xFF
	};

	struct ItemPanel
	{
		CRegularSlotGui			slot;			///< slot
		gui::CPanel*		pItemPanel;		///< Item panel
		CSurfaceGui			srfNeedItem;	///< Need Item
		gui::CStaticBox*	pItemName;		///< �̸�
		gui::CStaticBox*	pPoint;			///< �ʿ��� ����Ʈ(����, õ������ ����ȸ ����Ʈ ��...)
		std::wstring		wstrNeedItemName;

		RwBool				bNeedItem;
	};

	struct ShopItem
	{
		SERIAL_HANDLE	hItem;
		std::wstring	wstrItemName;
		RwInt32			iCount;
		RwUInt32		uiPrice;
		RwUInt32		uiPoint;
		sITEM_TBLDAT*	pITEM_DATA;
		sITEM_TBLDAT*	pNeedITEM_DATA;
	};

	VOID			Init();
	RwBool			Create();
	VOID			Destroy();

	RwInt32			SwitchDialog(bool bOpen);		///< DialogManager������ Open/Close
	eShopType		GetShopType();

protected:
	CNetPyShopGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			ResetCartTexture(eShopType eType);

	VOID			OpenShop();
	VOID			CloseShop();						///< NPC ������ �ݴ´�.	

	VOID			ClearShop();						///< Shop�� ������ �ʱ�ȭ �Ѵ�.
	VOID			ClearPanels();						///< �г� ���� ���� �ʱ�ȭ �Ѵ�.

	VOID			UpdateTabContent(RwUInt8 byIndex);	///< �ǿ� �´� ������ �����Ѵ�
	bool			SetPage(RwInt32 iPage);				///< ���� ������ ����
	VOID			SetPanel(RwInt32 iPage);			///< ���� �������� �´� ������ ����Ʈ�� �����ش�.
	VOID			SetPageButton();

	VOID			SelectItem(RwInt32 iPanelIndex);	///< �������� ��� ���� ������ �Ͽ���.

	VOID			SetZenny();							///< �ڽ��� ������ ������ ������Ʈ �Ѵ�.
	
	RwUInt8			GetPageCount_of_CurTab();			///< ���� �ǿ� ���� �������� ������ ��ȯ�Ѵ�

	RwBool			IsFirstPage();
	RwBool			IsLastPage();

	RwInt32			PtinSlot(RwInt32 iX, RwInt32 iY);
	RwInt32			PtinSlot_of_SmallIcon_in_panel(RwInt32 iX, RwInt32 iY);
	VOID			FocusEffect( RwBool bPush, RwInt32 iSlotIdx = -1);
	VOID			SelectEffect( RwBool bPush, RwInt32 iSlotIdx = -1 );
	VOID			CheckInfoWindow();

	VOID			OnPaint();
	VOID			OnPostPaint();	

	VOID			OnSelectChangeTabButton( INT nCurIndex, INT nPrevIndex );	///< �� ��ư�� ������

	VOID			ClickedPrePageButton(gui::CComponent* pComponent);	///< ���� ��ư�� ������.
	VOID			ClickedNextPageButton(gui::CComponent* pComponent);	///< ���� ��ư�� ������.
	VOID			ClickedCloseButton(gui::CComponent* pComponent);	///< �ݱ� ��ư�� ������.
	VOID			ClickedNetStoreButton(gui::CComponent* pComponent);
	
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
	gui::CSlot			m_slotPaint;
	gui::CSlot			m_slotPostPaint;
	gui::CSlot			m_slotCaptureMouseDown;
	gui::CSlot			m_slotClickedNetStore;

	RwInt32				m_iInfoWindowIndex;
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
	gui::CButton*		m_pPrePageButton;	///< ���� ������ �Ѿ�� ��ư
	gui::CButton*		m_pNextPageButton;	///< ���� ������ �Ѿ�� ��ư
	gui::CButton*		m_pNetStoreButton;

	gui::CStaticBox*	m_pShopTitle;		///< ���� �̸�	
	gui::CStaticBox*	m_pLargeBuyExplan;	///< �뷮 ���� ����
	gui::CStaticBox*	m_pPocketMoneytitle;///< ������ ����
	gui::CStaticBox*	m_pPocketMoney;		///< ������	
	gui::CStaticBox*	m_pCurrentPage;		///< ���� ������ ǥ��

	ShopItem			m_aShopItem[NTL_MAX_MERCHANT_TAB_COUNT][NTL_MAX_MERCHANT_COUNT];	/// �� �Ǻ��� �� �� �ִ� ������ ����

	eShopType			m_eShopType;

	RwInt32				m_iCurTab;			///< ���� �� �ε���
	RwInt32				m_iCurPage;			///< ���� ������

	RwBool				m_bFocus;			///< ��Ŀ���� �����.

	unsigned int		m_adwNETPYSHOP_MERCHANT_TBLIDX[dNETPYSHOP_TAB_NUMS];
};

#endif