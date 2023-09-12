/******************************************************************************
* File			: OptionControlTab.h
* Author		: Cho Hae sung
* Copyright		: (��)NTL
* Date			: 2007. 10. 15 
* Abstract		: 
*****************************************************************************
* Desc			: Tab of Options
*****************************************************************************/

#ifndef _OPTIONCONTROLTAB_H_
#define _OPTIONCONTROLTAB_H_

#pragma once

#include "GuiLineTree.h"

// OptionControlList�� Size
#define dOPTIONCONTROL_LIST_X			0
#define dOPTIONCONTROL_LIST_Y			0
#define dOPTIONCONTROL_LIST_WIDTH		288
#define dOPTIONCONTROL_LIST_HEIGHT		240

// OptionControlList ScrollBar�� Size
#define dOPTIONCONTROL_LIST_SCROLL_WIDTH			12
#define dOPTIONCONTROL_LIST_SCROLL_HEIGHT			19
#define dOPTIONCONTROL_LIST_SLIDER_WIDTH			12
#define dOPTIONCONTROL_LIST_SLIDER_HEIGHT			39

// OptionControl�� StaticBox(���� �κ�)
#define dOPTIONCONTROL_STATICBOX_X		0
#define dOPTIONCONTROL_STATICBOX_Y		0
#define dOPTIONCONTROL_STATICBOX_WIDTH	288
#define dOPTIONCONTROL_STATICBOX_HEIGHT 415
#define dOPTIONCONTROL_STATICBOX_COLOR			RGB(255, 219, 71)
#define dOPTIONCONTROL_STATICBOX_WARNING_COLOR	RGB(255, 219, 71)
#define dOPTIONCONTROL_STATICBOX_GUIDE_COLOR	RGB(255, 219, 71)

//#define dOPTIONCONTROL_STATICBOX_WARNING_COLOR	RGB(255, 0, 0)
//#define dOPTIONCONTROL_STATICBOX_GUIDE_COLOR	RGB(0, 255, 255)

// COptionControlCategoryNode [+] Button�� Size
#define dOPTIONCONTROL_CATEGORY_BUTTON_X		0
#define dOPTIONCONTROL_CATEGORY_BUTTON_Y		0
#define dOPTIONCONTROL_CATEGORY_BUTTON_WIDTH	140
#define dOPTIONCONTROL_CATEGORY_BUTTON_HEIGHT	20

// COptionControlCategoryNode Title�� Size
#define dOPTIONCONTROL_CATEGORY_TITLE_X 30
#define dOPTIONCONTROL_CATEGORY_TITLE_Y 0
#define dOPTIONCONTROL_CATEGORY_TITLE_WIDTH		140
#define dOPTIONCONTROL_CATEGORY_TITLE_HEIGHT	20
#define dOPTIONCONTROL_CATEGORY_TITLE_COLOR			RGB(255, 255, 255)
#define dOPTIONCONTROL_CATEGORY_TITLE_COLOR_DOWN	RGB( 255, 219, 71 )

// COptionControlActionNode StaticBox�� Size
#define dOPTIONCONTROL_ACTIONNODE_TITLE_X 0
#define dOPTIONCONTROL_ACTIONNODE_TITLE_Y 0
#define dOPTIONCONTROL_ACTIONNODE_TITLE_WIDTH 147
#define dOPTIONCONTROL_ACTIONNODE_TITLE_HEIGHT 19
#define dOPTIONCONTROL_ACTIONNODE_TITLE_COLOR RGB(255, 255, 255)

// Action Node Statib Box Text�� Coordinate
#define dOPTIONCONTROL_ACTIONNODE_TEXT_COORD_X 10
#define dOPTIONCONTROL_ACTIONNODE_TEXT_COORD_Y 3

// COptionControlActionNode Button�� Size
#define dOPTIONCONTROL_ACTIONNODE_BUTTON_X 150
#define dOPTIONCONTROL_ACTIONNODE_BUTTON_Y 0
#define dOPTIONCONTROL_ACTIONNODE_BUTTON_WIDTH 91
#define dOPTIONCONTROL_ACTIONNODE_BUTTON_HEIGHT 19
#define dOPTIONCONTROL_ACTIONNODE_BUTTON_COLOR RGB(255, 255, 255)

// CGuiLineTree�� �����ϴ� Item���� Size
#define dOPTIONCONTROL_LINE_HEIGHT				20
#define dOPTIONCONTROL_LINE_MARGIN				4	
#define dOPTIONCONTROL_CHILD_MARGIN_WIDTH		20

// Action���� �׷����� ����
#define dOPTIONCONTROL_CATEGORY_AVATAR			-2	// �ƹ�Ÿ ����
#define dOPTIONCONTROL_CATEGORY_TARGET			-3	// Ÿ�� �ൿ
#define dOPTIONCONTROL_CATEGORY_QUICKSLOT		-4	// ������ �ൿ
#define dOPTIONCONTROL_CATEGORY_WINDOW			-5	// ������ ���� �ൿ
#define dOPTIONCONTROL_CATEGORY_FIXED			-6	// ����(����Ű ���� �Ұ���)

////////////////////////////////////////////////////////////////////////////////////////////////////
// Class : COptionControlCategoryNode, COptionControlActionNode, COptionControlList, COptionControl
// Modified by Kell ( 2007. 10. 01 )
//
// COptionControlList(CGuiLineTree)�� ����
// (RootNode)
//     �� COptionControlCategoryNode(CGuiLineTreeNode) ( ��: [+] �ƹ�Ÿ �ൿ ���� )
//     �� �� COptionControlActionNode(CGuiLineTreeNode)  ( ��:  [�ƹ�Ÿ ����]  [ W ] )
//     �� �� COptionControlActionNode(CGuiLineTreeNode)
//     �� �� ...
//     �� COptionControlCategoryNode(CGuiLineTreeNode)
//     �� ...
///////////////////////////////////////////////////////////////////////////////////////////////////

/**
* \ingroup Client
* ����Ű �ɼ� �������� Action�� Group�� ǥ���ϴ� NODE
*/
class COptionControlCategoryNode : public CGuiLineTreeNode
{
public:
	COptionControlCategoryNode(CGuiLineTree* pMgr, std::wstring strTitle, RwInt32 nID);
	virtual ~COptionControlCategoryNode();

	virtual void ShowProc();				///< CGuiLineTreeNode������ Override
	virtual void HideProc();				///< CGuiLineTreeNode������ Override

	void OnClickBtnExpand(gui::CComponent* pComponent);		///< + ��ư�� Ŭ���Ҷ� ����Ǵ� �Լ�
	void OnClickBtnReduce(gui::CComponent* pComponent);		///< - ��ư�� Ŭ���Ҷ� ����Ǵ� �Լ�

protected:
	gui::CStaticBox* m_pStbTitle;			///< Action Group�� Title
	
	gui::CButton* m_pBtnExpand;				// + Button
	gui::CButton* m_pBtnReduce;				// - Button

	gui::CSlot m_slotClickedBtnExpand;		// + Button's signal
	gui::CSlot m_slotClickedBtnReduce;		// - Button's signal
};

/**
* \ingroup Client
* ����Ű �ɼ� ������ Action Group�� Item���� ǥ���ϴ� Node
*/
class COptionControlActionNode : public CGuiLineTreeNode
{
public:
	COptionControlActionNode(CGuiLineTree* pMgr, std::wstring strTitle, RwUInt32 nAction, RwBool bFixed = false);
	virtual ~COptionControlActionNode();

	virtual void ShowProc();
	virtual void HideProc();

	///< Ű �̸��� ��ư
	void OnClickBtnSetKey(gui::CComponent* pComponent);

	///< Ű ��ư�� �̸��� ����
	void SetText( std::wstring& strTitle );
	
	void Update();

	void RestoreBtnSetKey() { m_pBtnSetKey->Enable(); }

protected:
	gui::CStaticBox* m_pStbTitle;			///< �׼��� �̸�
	
	gui::CButton* m_pBtnSetKey;				///< Ű ���� ��ư
	
	gui::CSlot m_slotClickedBtnSetKey;		///< Ű ���� ��ư�� signal

	RwUInt32 m_nAction;						///< �׼ǰ��� ������ �ִ´�.
	RwBool m_bFixed;
};

/**
* \ingroup Client
* CGuiLineTreeNode�� ��ӹ޴� ������ ����Ű ���� Node���� �����ϱ� ����
* CGuiLineTree�� ��ӹ��� �Ŵ��� Ŭ����
*/
class COptionControlList : public CGuiLineTree
{
public:
	COptionControlList();
	virtual ~COptionControlList();

	RwBool	Create(CRectangle& rect, gui::CComponent* pParent, RwInt32 nLineHeight, RwInt32 nLineMargin, RwInt32 nChildXMargin, RwInt32 nScrollBarWidth, COptionControl* pOptionControl = NULL);

	void CreateTree();									///< Ʈ���� �����Ѵ�.

	///< Ʈ���� ������Ʈ �Ѵ�.
	void UpdateNode();

	///< ��ũ�� �ٸ� �ٸ��콺 ������ �ϱ� ����
	void OnCaptureWheelMove( RwInt32 nFlag, RwInt16 sDelta, CPos& pos );

	///< ������ COptionControlList�� �����ִ� ���� �θ���.
	COptionControl* GetParentTab(); 

protected:
	COptionControl*	m_pOptionControl;

	gui::CSlot m_slotCaptureWheelMove;
};

/**
* \ingroup Client
* COptionBase�� ��ӹ޾Ƽ� �ɼ� �������� �� �߿� �ϳ��� ����Ű ���� ���� ����
* CGuiLineTree�� �����Ͽ� ����Ű �Է� ������ ���� �� ����
*/
class COptionControl : public COptionBase
{
public:
	COptionControl();
	virtual ~COptionControl();

	virtual RwBool		Create(COptionWindowGui* pOptionWindow);
	virtual void		Destroy();

	virtual void		Show();
	virtual void		Hide();
		
	virtual void		OnInit();
	virtual void		OnReset();
	virtual void		OnOk();
	virtual void		OnCancel();
	virtual void		OnHandleEvents(RWS::CMsg &pMsg);

	// ��µ� �ȳ� �޽���
public:

	void SetGuideText( RwUInt32 uiColor, const WCHAR* pString );

	void SetGuideDefault();						///< �⺻ �ȳ�
	void SetGuideChange(RwUInt32 nAction);		///< nAction�� �ߺ��˴ϴ�. nAction�� �����ȵ�����...
	void SetGuideFixed(RwUInt32 nAction);		///< %s �� ���� �Ұ��� �մϴ�.
	void SetGuideNegativeMode();				///< ���� ��忡���� ������ �Ұ����մϴ�.
	

protected:
	COptionControlList* m_pOptionControlList;		///< ����Ʈ���� �Ŵ���
	gui::CDialog*		m_pDlgControlList;			///< ����Ʈ���� �θ� �� Dialog

	gui::CStaticBox*	m_pStbControlTitle;			///< ����Ű ���� â�� ����
	gui::CStaticBox*	m_pStbControlBack;			///< �ɼ�â�� �ؽ�Ʈ ���â ���
	gui::CStaticBox*	m_pStbControlText;			///< �ɼ�â�� �ؽ�Ʈ ���â
};

#endif//OPTIONREFACTOR