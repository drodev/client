/******************************************************************************
* File			: OptionChattingTab.h
* Author		: Hae sung, Cho
* Copyright		: (��)NTL
* Date			: 2008. 9. 11 
* Abstract		: 
*****************************************************************************
* Desc			: Tab of Chatting
*****************************************************************************/

#ifndef _OPTIONCHATTINGTAB_H_
#define _OPTIONCHATTINGTAB_H_

#pragma once

#include "GuiLineTree.h"

// Option Chatting List�� Size
#define dOPTIONCHATTING_LIST_X			0
#define dOPTIONCHATTING_LIST_Y			0
#define dOPTIONCHATTING_LIST_WIDTH		288
#define dOPTIONCHATTING_LIST_HEIGHT		304

// OptionChattingList ScrollBar�� Size
#define dOPTIONCHATTING_LIST_SCROLL_WIDTH			12
#define dOPTIONCHATTING_LIST_SCROLL_HEIGHT			19
#define dOPTIONCHATTING_LIST_SLIDER_WIDTH			12
#define dOPTIONCHATTING_LIST_SLIDER_HEIGHT			39

// CGuiLineTree�� �����ϴ� Item���� Size
#define dOPTIONCHATTING_LINE_HEIGHT				20
#define dOPTIONCHATTING_LINE_MARGIN				4	
#define dOPTIONCHATTING_CHILD_MARGIN_WIDTH		20

// ä��â�� �ɼ��� �׷����� ID
#define dOPTIONCHATTING_CATEGORY_COMMON			-2
#define dOPTIONCHATTING_CATEGORY_BASIC			-3
#define dOPTIONCHATTING_CATEGORY_ADDED			-4
#define dOPTIONCHATTING_CATEGORY_ADDED2			-5

enum eCHATOPTIONID
{
	// Common
	eCHAT_INPUTMODE	= 0,
	eCHAT_WINDOWLOCK,
	eCHAT_WINDOWMSCROLL,
	eCHAT_ADDEDWINDOW,
	eCHAT_ADDEDWINDOW2,
	eCHAT_WINDOWOPACITY,

	// Basic
	eCHAT_BASIC_NORMAL,
	eCHAT_BASIC_WISPHER,
	eCHAT_BASIC_PARTY,
	eCHAT_BASIC_FIND_PARTY,
	eCHAT_BASIC_GUILD,
	eCHAT_BASIC_TRADE,
	eCHAT_BASIC_SHOUT,
	eCHAT_BASIC_SYSTEM,

	// Added
	eCHAT_ADDED_NORMAL,
	eCHAT_ADDED_WISPHER,
	eCHAT_ADDED_PARTY,
	eCHAT_ADDED_FIND_PARTY,
	eCHAT_ADDED_GUILD,
	eCHAT_ADDED_TRADE,
	eCHAT_ADDED_SHOUT,
	eCHAT_ADDED_SYSTEM,

	// Added2
	eCHAT_ADDED2_NORMAL,
	eCHAT_ADDED2_WISPHER,
	eCHAT_ADDED2_PARTY,
	eCHAT_ADDED2_FIND_PARTY,
	eCHAT_ADDED2_GUILD,
	eCHAT_ADDED2_TRADE,
	eCHAT_ADDED2_SHOUT,
	eCHAT_ADDED2_SYSTEM,

	eCHATOPTIONID_NUMS = eCHAT_ADDED_SYSTEM,
	INVALID_CHATOPTIONID = 0xFF
};

/**
* \ingroup client
*/
class COptionChattingCategoryNode : public CGuiLineTreeNode
{
public:
	COptionChattingCategoryNode(CGuiLineTree* pMgr, std::wstring strTitle, RwInt32 nID);
	virtual ~COptionChattingCategoryNode();

	virtual void ShowProc();				///< CGuiLineTreeNode������ Override
	virtual void HideProc();				///< CGuiLineTreeNode������ Override

	void OnClickBtnExpand(gui::CComponent* pComponent);		///< + ��ư�� Ŭ���Ҷ� ����Ǵ� �Լ�
	void OnClickBtnReduce(gui::CComponent* pComponent);		///< - ��ư�� Ŭ���Ҷ� ����Ǵ� �Լ�

protected:
	gui::CButton* m_pBtnExpand;				// + Button
	gui::CButton* m_pBtnReduce;				// - Button

	gui::CSlot m_slotClickedBtnExpand;		// + Button's signal
	gui::CSlot m_slotClickedBtnReduce;		// - Button's signal
};

/**
* \ingroup client
* üũ�ڽ��� ����ϴ� �ɼ�
*/
class CCheckBoxNode : public CGuiLineTreeNode
{
public:
	CCheckBoxNode(CGuiLineTree* pMgr, RwInt32 nID, std::wstring strTitle, std::wstring strToolTip);
	virtual ~CCheckBoxNode();

	virtual void ShowProc();
	virtual void HideProc();

	void SetDown( RwBool bDown ) { m_pBtnCheck->SetDown( B2b(bDown) ); }
	void SetDown( bool bDown ) { m_pBtnCheck->SetDown( bDown ); }
	bool GetDown() { return m_pBtnCheck->IsDown(); }

	void OnToggledCheckBox(gui::CComponent* pComponent, bool bDown);
protected:
	gui::CButton*		m_pBtnCheck;
	gui::CStaticBox*	m_pStbTitle;

	gui::CSlot		m_slotToggledBtnCheck;
};

/**
* \ingroup client
* �����̴��� ����ϴ� �ɼ�
*/
class CSliderNode : public CGuiLineTreeNode
{
public:
	CSliderNode(CGuiLineTree* pMgr, RwInt32 nID, std::wstring strTitle, std::wstring strToolTip);
	virtual ~CSliderNode();

	void OnChangeSlider(RwInt32 nValue);

	RwInt32 GetValue()					{ return m_pScrSlider->GetValue(); }
	void	SetValue(RwInt32 nValue)	{ m_pScrSlider->SetValue( nValue ); }

	virtual void ShowProc();
	virtual void HideProc();

protected:
	gui::CStaticBox*	m_pStbTitle;
	gui::CScrollBar*	m_pScrSlider;

	gui::CSlot			m_slotChangedScrSlider;
	gui::CSlot			m_slotValueChanged;
};

/**
* \ingroup client
*/
class COptionChattingList : public CGuiLineTree
{
public:
	COptionChattingList();
	virtual ~COptionChattingList();

	RwBool	Create(CRectangle& rect, gui::CComponent* pParent, RwInt32 nLineHeight, RwInt32 nLineMargin, RwInt32 nChildXMargin, RwInt32 nScrollBarWidth, COptionChatting* pOptionChatting = NULL);

	void CreateTree();									///< Ʈ���� �����Ѵ�.

	///< ��ũ�� �ٸ� �ٸ��콺 ������ �ϱ� ����
	void OnCaptureWheelMove( RwInt32 nFlag, RwInt16 sDelta, CPos& pos );

	
protected:
	COptionChatting*	m_pOptionChatting;

	gui::CSlot m_slotCaptureWheelMove;
};

/**
* \ingroup client
* COptionBase �� ��� �޾Ƽ� �ɼ� �������� �� ���� �ϳ��� ä��â ���� ���� ����
* CGuiLineTree�� ����Ͽ� ä��â�� ���õ� ���� �ɼ��� ������ �� �ְ� �ϴ� Ŭ����
*/
class COptionChatting : public COptionBase
{
public:
	COptionChatting();
	virtual ~COptionChatting();

	virtual RwBool		Create(COptionWindowGui* pOptionWindow);
	virtual void		Destroy();

	virtual void		Show();
	virtual void		Hide();

	virtual void		OnInit();
	virtual void		OnReset();
	virtual void		OnOk();
	virtual void		OnCancel();
	virtual void		OnHandleEvents(RWS::CMsg &pMsg);

	// ����
	VOID				LoadSerializer();
	VOID				SaveSerializer();
	VOID				DefaultOption();

protected:
	COptionChattingList* m_pOptionChattingList;		///< ����Ʈ���� �Ŵ���
	gui::CDialog*		m_pDlgChattingList;			///< ����Ʈ���� �θ� �� Dialog
};

#endif