/*****************************************************************************
* File			: PrivateShopGui.h
* Author		: Jinsung, Kim -> Haesung, Cho
* Copyright		: (��)NTL
* Date			: 2007. 7. 4 -> 2007. 12. 19
* Abstract		: DBO ���λ���
*****************************************************************************
* Desc         : 
*****************************************************************************/

#ifndef __PRIVATE_SHOP_GUI_H__
#define __PRIVATE_SHOP_GUI_H__

#pragma once

#include "Windowby3.h"
#include "SlotGui.h"
#include "NtlItem.h"

// ���λ��� �������� ��ġ
#define dPRIVATESHOP_UI_ITEM_TOP				42
#define dPRIVATESHOP_UI_ITEM_LEFT				20
#define dPRIVATESHOP_UI_ITEM_GAP				55

#define dPRIVATESHOP_UI_BGLINE_LEFT				9
#define dPRIVATESHOP_UI_BGLINE_TOP				30
#define dPRIVATESHOP_UI_SHOP_BGLINE_WIDTH		303
#define dPRIVATESHOP_UI_SHOP_BGLINE_HEIGHT		347
#define dPRIVATESHOP_UI_NOTE_BGLINE_WIDTH		303
#define dPRIVATESHOP_UI_NOTE_BGLINE_HEIGHT		375
#define dPRIVATESHOP_UI_BUY_AWAY_LEFT			30
#define dPRIVATESHOP_UI_SELL_AWAY_LEFT			115

#define dPRIVATESHOP_UI_ITEM_HEIGHT				DBOGUI_ICON_SIZE
#define dPRIVATESHOP_UI_ITEM_WIDTH				DBOGUI_ICON_SIZE

#define dPRIVATESHOP_UI_CALC_OFFSET				104


class CPrivateShopItemGui;
class CPrivateShopGui;

/**
* \ingroup client
* \brief ���λ��� ������ ����
*/
class CPrivateShopItemGui
{
public:
	CPrivateShopItemGui();
	virtual ~CPrivateShopItemGui();

	// Create & Destroy
	RwBool			Create(const CRectangle& rectArea, CSurfaceGui* pEffectSelect, CSurfaceGui* pEffectFocus, gui::CComponent* pParent, CPrivateShopGui* pPrivateShopGui);
	void			Destroy();

	// Callback
	void			OnPaint();	
	void			OnBgPaint();
	void			OnMove(RwInt32 iOldX, RwInt32 iOldY);
	void			OnMouseDown(const CKey& key);
	void			OnMouseUp(const CKey& key);
	void			OnMouseLeave(gui::CComponent* pComponent);
	void			OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	void			OnClickedBtnPrice(gui::CComponent* pComponent);

	// Interface
	void			Clear();
	void			Show(bool bShow = true)					{ m_pShopItem->Show(bShow); }

	RwUInt8			GetPos()								{ return m_uiPos; }
	void			SetPos(RwUInt8 uiPos)					{ m_uiPos = uiPos; }

	CRegularSlotGui*		GetIcon()								{ return m_pShopItemIcon; }
	void			SetIcon(RwUInt8 uiPos, RwUInt32 uiSerial, 
							RwUInt32 uiCount, RwUInt32 uiPrice, 
							RwUInt8 uiItemState, eREGULAR_SLOT_TYPE eSerialType);

	SERIAL_HANDLE	GetSerial()								{ return m_pShopItemIcon->GetSerial(); }
	RwUInt32		GetCount()								{ return m_pShopItemIcon->GetCount(); }
	RwUInt32		GetPrice()								{ return m_pShopItemIcon->GetPrice(); }
	sITEM_TBLDAT*	GetItemTable()							{ return m_pShopItemIcon->GetItemTable(); }

	void			SetItemState(RwUInt8 uiItemState)		{ m_uiItemState = uiItemState; }
	RwUInt8			GetItemState()							{ return m_uiItemState; }

	CRectangle		GetShopItemRect();
	void			EnablePrice(bool bEnable = true)				{ m_pShopItemPrice->ClickEnable(bEnable); }


protected:
	// Components
	gui::CDialog*		m_pShopItem;				///< Item�� Dialog
	gui::CPanel*		m_pShopItemBg;				///< Item Slot�� ���
	gui::CStaticBox*	m_pShopItemName;			///< Item �̸�
	gui::CButton*		m_pShopItemPrice;			///< Item ����
	CRegularSlotGui*			m_pShopItemIcon;			///< Item Icon�� Slot

	// Signals
	gui::CSlot			m_slotMove;	
	gui::CSlot			m_slotPaint;
	gui::CSlot			m_slotBgPaint;
	gui::CSlot			m_slotMouseDown;
	gui::CSlot			m_slotMouseUp;
	gui::CSlot			m_slotMouseMove;
	gui::CSlot			m_slotMouseLeave;
	gui::CSlot			m_slotClickedBtnPrice;			

	// Effects
	CSurfaceGui			m_EffectPick;				///< �ȵ� ������ �׸�
	CSurfaceGui*		m_pEffectSelect;			///< ���õ� ������ �׸�
	CSurfaceGui*		m_pEffectFocus;				///< ��Ŀ�� ������ �׸�

	CPrivateShopGui*	m_pPrivateShopGui;			///< �� ������ ������ �θ��� Class
	RwBool				m_bClick;					///< Ŭ���Ǿ���?
	
	RwUInt8				m_uiItemState;				///< ������ ����
	CRectangle			m_rectItem;
	RwUInt8				m_uiPos;
};

/**
* \ingroup client
* \brief ���λ��� GUI
*/
class CPrivateShopGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	
	///< ���λ��� UI�� Tab Type
	enum eTAB_TYPE
	{
		TAB_SHOP,	///< ����
		TAB_NOTE,	///< ����
		TAB_NUM,	///< TAB�� ����
	};

	///< ���λ��� UI�� Item Slot
	enum eITEM_SLOT
	{
		SLOT_NUM = 6,	///< ���� ����
	};

	///< ���λ��� UI�� Type
	enum ePrivateShopType
	{
		PRIVATESHOP_BUY,	///< �մ�
		PRIVATESHOP_SELL,	///< ����
		PRIVATESHOP_NONE,
	};

	// ������ & �Ҹ���
	CPrivateShopGui(const RwChar* pName);
	virtual ~CPrivateShopGui();

	// Create & Destroy
	RwBool	Create();
	RwBool	CreateTabShop(gui::CDialog* pParent);
	RwBool	CreateTabNote(gui::CDialog* pParent);
	void	Destroy();

	// SwitchDialog & HandleEvents
	RwInt32	SwitchDialog(bool bOpen);
	void	HandleEvents(RWS::CMsg& msg);								///< �̺�Ʈ
	void	HandleMsgboxResult(void* pData);							///< �޽��� �ڽ� ���

	void	HandleCalcPopupResult(void* pData);							///< ������ �Է� ���
	void	HandleSobPrivateShopCommunity(void *pData);					///< ������ ���°� ����Ǿ��� ���
	void	HandleRegPrivateShopItem(void* pData);						///< ���λ��� Item Reg
	void	HandleSobInfoUpdate(void* pData);							///< Sob ��ä�� ���� Update
	void	HandlePickedUpHide(void* pData);							///< ���λ��� �������� �Ⱦ� �Ǿ Hide �Ǿ��� �� 

	// HandleEvents : ���λ��� ����
	void	HandlePrivateShopState(void* pData);						///< ���λ��� State
	void	HandlePrivateShopStateVisitor(void *pData);					///< �湮�ڰ� ������ ��
	void	HandlePrivateShopItem(void* pData);							///< ���λ��� Item
	void	HandlePrivateShopItemDataInfo(void* pData);					///< ���λ��� Item Update
	void	HandlePrivateShopItemSelect(void* pData);					///< ���λ��� Item Select
	void	HandlePrivateShopSelectNfy(void* pData);
	void	HandlePrivateShopItemBuying(void* pData);					///< ���λ��� Item Buying
	void	HandlePrivateShopItemState(void* pData);					///< ���λ��� Item State
	void	HandlePrivateShopNameTag(void* pData);						///< ���λ��� NameTag Update

	// Event
	void	OnPaintEffect();
	void	OnMove(RwInt32 iOldX, RwInt32 iOldY);
	void	OnTabChanged(RwInt32 nIndex, RwInt32 nOldIndex);
	void	OnTabShopMouseLeave(gui::CComponent* pComponent);
	void	OnClickedBtnClose(gui::CComponent* pComponent);
	void	OnCaptureMouseDown(const CKey& key);

	void	OnGotFocus();
	void	OnLostFocus();

	void	OnClickedBtnNext(gui::CComponent* pComponent);
	void	OnClickedBtnPrev(gui::CComponent* pComponent);
	void	OnClickedBtnMail(gui::CComponent* pComponent);
	void	OnClickedBtnAway(gui::CComponent* pComponent);
	void	OnPaintBtnAway();
	void	OnMovedBtnAway(RwInt32 iOldX, RwInt32 iOldY);
	void	OnKeyUp(gui::CComponent* pComponenet, CInputDevice* pDevice, const CKey& key);
	void	OnNoticeCharChanged(int iLength);
	void	OnClickedBtnSale(gui::CComponent* pComponent);

	// ShopItemGui Event
	void	OnShopItemEnter(CPrivateShopItemGui* pShopItem);
	void	OnShopItemLeave(CPrivateShopItemGui* pShopItem);
	void	OnShopItemClicked(CPrivateShopItemGui* pShopItem, const CKey& Key);
	void	OnShopItemPriceClicked(CPrivateShopItemGui* pShopItem, gui::CComponent* pComponent);
	
	// Gui Setting
	void	SetSale(bool bSale);		// �ǸŰ���
	void	SetAway(bool bAway);		// �ڸ����
	void	SetNotice(const WCHAR* pText);
	void	SetPage(RwUInt32 iPage, bool bCheckMax = true);

	void	SetUserInterface(ePrivateShopType eType, sPRIVATESHOP_SHOP_DATA* pShopData, bool bIsSale);
	void	SetShopItemSelect(CPrivateShopItemGui* pShopItem);
	void	SetShopItemFocus(CPrivateShopItemGui* pShopItem);

	// Get
	RwUInt8	GetShopState() { return m_ShopData.sSummaryPrivateShopData.byShopState; }

	void	Clear();
	void	ClearShopItem();

	void	UpdateShopItem();
	void	UpdateShopItemData();

	void	SetShopItemData(RwUInt8 uiPrivateShopPos, sPRIVATESHOP_ITEM_DATA* pShopItemData, bool bEvent = true);
	void	ShowInfoWindow(RwBool bIsShow, CPrivateShopItemGui* pShopItem = NULL);

	void	CalcNoticeMaxNum();
	void	CheckSoldOut();

protected:
	// Gui Common Components
	gui::CStaticBox*			m_pTitle;
	gui::CButton*				m_pCloseButton;
	gui::CTabButton*			m_pTabButton;
	gui::CDialog*				m_apDialogTab[TAB_NUM];

	// Gui Common Signals
	gui::CSlot					m_slotMove;
	gui::CSlot					m_slotTabChanged;
	gui::CSlot					m_slotCloseButtonClicked;
	gui::CSlot					m_slotTabShopMouseLeave;
	gui::CSlot					m_slotCaptureMouseDown;

	// TAB_SHOP ( ���� ) Components
	gui::CButton*				m_pNextButton;
	gui::CButton*				m_pPrevButton;
	gui::CButton*				m_pSaleButton;
	gui::CStaticBox*			m_pZenny;
	gui::CStaticBox*			m_pZennyTitle;
	gui::CStaticBox*			m_pCurrentPage;
	gui::CPanel*				m_pSoldOut;
	gui::CStaticBox*			m_pStbSoldOut;

	gui::CSlot					m_slotNextClicked;
	gui::CSlot					m_slotPrevClicked;
	gui::CSlot					m_slotSaleClicked;
	gui::CSlot					m_slotEffectPaint;

	// TAB_SHOP ( ���� ) Signals
	CPrivateShopItemGui			m_aShopItem[SLOT_NUM];		///< ���λ��� ������
	CSurfaceGui					m_EffectSelect;				///< ���õ� ������ �׸�
	CSurfaceGui					m_EffectFocus;				///< ��Ŀ�� ������ �׸�

	// TAB_SHOP ( ���� ) State & Effect
	ePrivateShopType			m_eShopType;				///< ������ ����
	sPRIVATESHOP_ITEM_DATA		m_aShopItemData[NTL_MAX_PRIVATESHOP_INVENTORY];
	sPRIVATESHOP_SHOP_DATA		m_ShopData;

	CPrivateShopItemGui*		m_pItemSelect;		///< ���õ� ������
	CPrivateShopItemGui*		m_pItemFocus;		///< ��Ŀ�� �� ������

	RwUInt32					m_uiItemCount;		///< ������ ����
	RwUInt32					m_uiPageMax;		///< �ִ� ������ 
	RwUInt32					m_uiPageCur;		///< ���� ������
	bool						m_bAway;			///< �ڸ����
	bool						m_bSale;			///< �Ǹ���

	// TAB_NOTE ( ���� ) Components
	gui::CStaticBox*			m_pShopNameTitle;
	gui::CInputBox*				m_pShopNameInput;
	gui::CStaticBox*			m_pShopNoticeTitle;
	gui::CInputBox*				m_pShopNoticeInput;
	gui::CDialog*				m_pShopNoticeDialog;
	gui::CButton*				m_pAwayButton;
	gui::CButton*				m_pMailButton;
	gui::CStaticBox*			m_pNoticeMaxNum;

	// TAB_NOTE ( ���� ) Signals
	gui::CSlot					m_slotNameGotFocus;
	gui::CSlot					m_slotNameLostFocus;
	gui::CSlot					m_slotNoticeGotFocus;
	gui::CSlot					m_slotNoticeLostFocus;
	gui::CSlot					m_slotMailClicked;
	gui::CSlot					m_slotAwayClicked;
	gui::CSlot					m_slotAwayPaint;
	gui::CSlot					m_slotAwayMove;
	gui::CSlot					m_slotNameKeyUp;
	gui::CSlot					m_slotNoticeKeyUp;
	gui::CSlot					m_slotNoticeCharChanged;

	CSurfaceGui					m_surAwayCheck;
	CSurfaceGui					m_surAwayUnCheck;
	
};

#endif//__PRIVATE_SHOP_GUI_H__