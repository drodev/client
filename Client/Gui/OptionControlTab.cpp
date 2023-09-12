#include "precomp_dboclient.h"
// core
#include "NtlDebug.h"
#include "CEventHandler.h"

// presentation
#include "NtlPLGui.h"
#include "NtlPLGuiManager.h"

// framework
#include "NtlApplication.h"

// simulation
#include "InputActionMap.h"
#include "NtlSLEvent.h"

// dbo
#include "DialogManager.h"
#include "DisplayStringManager.h"

// Option
#include "OptionWindowGui.h"
#include "OptionBase.h"
#include "OptionControlTab.h"

// logic
#include "DboLogic.h"


/////////////////////////////////////////////////////////////////////////////
// class : COptionControlCategoryNode

/**
* \brief COptionControlCategoryNode�� ������
*
* �����ڿ� ǥ�õ� �ؽ�Ʈ�� Action�� Group�� ����� ID�� �����Ѵ�.
*/
COptionControlCategoryNode::COptionControlCategoryNode(CGuiLineTree* pMgr, std::wstring strTitle, RwInt32 nID)
: CGuiLineTreeNode( pMgr, nID )
, m_pStbTitle( NULL )
, m_pBtnExpand( NULL )
, m_pBtnReduce( NULL )
{
	// CategoryNode StaticBox�� Size�� Text, Color�� �����Ѵ�.
	CRectangle rect;
	rect.SetRectWH( dOPTIONCONTROL_CATEGORY_TITLE_X, dOPTIONCONTROL_CATEGORY_TITLE_Y, 
		dOPTIONCONTROL_CATEGORY_TITLE_WIDTH, dOPTIONCONTROL_CATEGORY_TITLE_HEIGHT );
	m_pStbTitle = NTL_NEW gui::CStaticBox( rect, pMgr->GetParentGui(), GetNtlGuiManager()->GetSurfaceManager() );
	m_pStbTitle->SetText( strTitle.c_str() );
	m_pStbTitle->SetTextColor( dOPTIONCONTROL_CATEGORY_TITLE_COLOR );
	m_pStbTitle->Enable( false );

	// +��ư
	rect.SetRectWH(dOPTIONCONTROL_CATEGORY_BUTTON_X, dOPTIONCONTROL_CATEGORY_BUTTON_Y, dOPTIONCONTROL_CATEGORY_BUTTON_WIDTH, dOPTIONCONTROL_CATEGORY_BUTTON_HEIGHT);
	m_pBtnExpand = NTL_NEW gui::CButton( rect, std::string(),pMgr->GetParentGui(), GetNtlGuiManager()->GetSurfaceManager());
	m_pBtnExpand->AddSurfaceUp(GetNtlGuiManager()->GetSurfaceManager()->GetSurface("QuestList.srf", "srfExpandBtnUp"));
	m_pBtnExpand->AddSurfaceFocus(GetNtlGuiManager()->GetSurfaceManager()->GetSurface("QuestList.srf", "srfExpandBtnFoc"));
	m_pBtnExpand->AddSurfaceDown(GetNtlGuiManager()->GetSurfaceManager()->GetSurface("QuestList.srf", "srfExpandBtnDown"));

	// -��ư
	m_pBtnReduce = NTL_NEW gui::CButton(rect, std::string(),pMgr->GetParentGui(), GetNtlGuiManager()->GetSurfaceManager());
	m_pBtnReduce->AddSurfaceUp(GetNtlGuiManager()->GetSurfaceManager()->GetSurface("QuestList.srf", "srfReduceBtnUp"));
	m_pBtnReduce->AddSurfaceFocus(GetNtlGuiManager()->GetSurfaceManager()->GetSurface("QuestList.srf", "srfReduceBtnFoc"));
	m_pBtnReduce->AddSurfaceDown(GetNtlGuiManager()->GetSurfaceManager()->GetSurface("QuestList.srf", "srfReduceBtnDown"));

	// Button�� Signal ����
	m_slotClickedBtnExpand = m_pBtnExpand->SigClicked().Connect(this, &COptionControlCategoryNode::OnClickBtnExpand);
	m_slotClickedBtnReduce = m_pBtnReduce->SigClicked().Connect(this, &COptionControlCategoryNode::OnClickBtnReduce);
}

/**
* \biref COptionControlCategoryNode�� �Ҹ���
*/
COptionControlCategoryNode::~COptionControlCategoryNode()
{
	NTL_DELETE( m_pStbTitle );
	NTL_DELETE( m_pBtnReduce );
	NTL_DELETE( m_pBtnExpand );
}

/**
* \brief CategoryNode�� ǥ��
*
* CGuiLineTreeNode�� ShowProc()�� �������̵� �Ͽ� ������ Ȯ��ʿ� ���� �ڽ� ������� ���踦 �� ����Ͽ�
* ��ġ���ְ� ���� ��ư�� ���°� + ���� - ���� �����ؼ� ������ش�.
*/
void COptionControlCategoryNode::ShowProc()
{
	CGuiLineTreeNode::ShowProc();

	m_pStbTitle->Show(true);
	if (IsExpand())
	{
		m_pBtnReduce->Show(true);		
		m_pBtnExpand->Show(false);
		m_pStbTitle->SetTextColor( dOPTIONCONTROL_CATEGORY_TITLE_COLOR_DOWN, TRUE );
	}
	else
	{
		m_pBtnExpand->Show(true);
		m_pBtnReduce->Show(false);
		m_pStbTitle->SetTextColor( dOPTIONCONTROL_CATEGORY_TITLE_COLOR, TRUE );
	}

	// ī�װ� ������ ��ġ�� �� ���
	m_pBtnExpand->SetPosition(m_nPosX + dOPTIONCONTROL_CATEGORY_BUTTON_X, m_nPosY + dOPTIONCONTROL_CATEGORY_BUTTON_Y);
	m_pBtnReduce->SetPosition(m_nPosX + dOPTIONCONTROL_CATEGORY_BUTTON_X, m_nPosY + dOPTIONCONTROL_CATEGORY_BUTTON_Y);
	m_pStbTitle->SetPosition(m_nPosX + dOPTIONCONTROL_CATEGORY_TITLE_X, m_nPosY + dOPTIONCONTROL_CATEGORY_TITLE_Y);
}

/**
* \brief CategoryNode�� ����
*/
void COptionControlCategoryNode::HideProc()
{
	CGuiLineTreeNode::HideProc();

	m_pStbTitle->Show(false);
	m_pBtnExpand->Show(false);
	m_pBtnReduce->Show(false);
}

/**
* \brief +��ư�� ������ ���� �ൿ
*/
void COptionControlCategoryNode::OnClickBtnExpand(gui::CComponent* pComponent)
{
	Expand(TRUE);
}

/**
* \brief -��ư�� ������ ���� �ൿ
*/
void COptionControlCategoryNode::OnClickBtnReduce(gui::CComponent* pComponent)
{
	Expand(FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// class : COptionControlActionNode

/**
* \brief COptionControlActionNode�� ������
*
* COptionControlCategoryNode�� �ڽĵ�� ���� �� Node, �ൿ�� str�� Action�� ID�� �޾Ƽ� �����Ѵ�.
*/
COptionControlActionNode::COptionControlActionNode(CGuiLineTree* pMgr, std::wstring wstrTitle, RwUInt32 nAction, RwBool bFixed)
: CGuiLineTreeNode( pMgr, nAction )
, m_pStbTitle( NULL )
, m_pBtnSetKey( NULL )
{
	// �ʱ�ȭ�� ����
	m_nAction = nAction;
	m_bFixed = bFixed;

	// ActionNode StaticBox�� Size�� Text, Color�� �����Ѵ�.
	CRectangle rect;
	rect.SetRectWH( dOPTIONCONTROL_ACTIONNODE_TITLE_X, dOPTIONCONTROL_ACTIONNODE_TITLE_Y, 
		dOPTIONCONTROL_ACTIONNODE_TITLE_WIDTH, dOPTIONCONTROL_CATEGORY_TITLE_HEIGHT );

	m_pStbTitle = NTL_NEW gui::CStaticBox( rect, pMgr->GetParentGui(), GetNtlGuiManager()->GetSurfaceManager());
	m_pStbTitle->AddSurface(GetNtlGuiManager()->GetSurfaceManager()->GetSurface("OptionWnd.srf", "srfStaticBGLarge"));
	m_pStbTitle->CreateFontStd( DETAIL_FONT, DEFAULT_FONT_SIZE, DEFAULT_FONT_ATTR );
	m_pStbTitle->SetTextColor( dOPTIONCONTROL_ACTIONNODE_TITLE_COLOR );
	m_pStbTitle->SetTextStyle(COMP_TEXT_CENTER);
	m_pStbTitle->SetText( wstrTitle.c_str() );
	
	// Ű ���� ��ư(Action Id�� ���� ǥ�⸦ ����� �Ѵ�.)
	// �ӽ÷� ũ�Ⱑ �Ȱ��� ���ҽ� ���
	rect.SetRectWH( dOPTIONCONTROL_ACTIONNODE_BUTTON_X, dOPTIONCONTROL_ACTIONNODE_BUTTON_Y,
		dOPTIONCONTROL_ACTIONNODE_BUTTON_WIDTH, dOPTIONCONTROL_ACTIONNODE_BUTTON_HEIGHT );
	m_pBtnSetKey = NTL_NEW gui::CButton(rect, std::string(),pMgr->GetParentGui(), GetNtlGuiManager()->GetSurfaceManager());
	m_pBtnSetKey->AddSurfaceUp(GetNtlGuiManager()->GetSurfaceManager()->GetSurface("OptionWnd.srf", "srfStaticBGSmall"));
	m_pBtnSetKey->AddSurfaceFocus(GetNtlGuiManager()->GetSurfaceManager()->GetSurface("OptionWnd.srf", "srfButtonBGSmallFocus"));
	m_pBtnSetKey->AddSurfaceDown(GetNtlGuiManager()->GetSurfaceManager()->GetSurface("OptionWnd.srf", "srfButtonBGSmallDown"));
	m_pBtnSetKey->AddSurfaceDisabled(GetNtlGuiManager()->GetSurfaceManager()->GetSurface("OptionWnd.srf", "srfButtonBGSmallDisable"));
	m_pBtnSetKey->SetTextStyle(COMP_TEXT_CENTER);
	m_pBtnSetKey->SetTextFont( DETAIL_FONT, DEFAULT_FONT_SIZE, DEFAULT_FONT_ATTR );

	// �׼� ID�� ���� ���ڿ��� ������ش�.
	std::wstring wstrKeyName = GetInputActionMap()->GetKeyName( nAction );

	// ��� �ִٸ� "�����ȵ�" ���, �ƴ϶�� Ű�� �̸��� �״�� ����Ѵ�.
	if( wstrKeyName.empty() )
		m_pBtnSetKey->SetText( GetDisplayStringManager()->GetString( "DST_OPTION_CONTROL_TEXT_EMPTYKEY" ) );
	else
		m_pBtnSetKey->SetText( wstrKeyName.c_str() );

	// Button�� Signal ����
	m_slotClickedBtnSetKey = m_pBtnSetKey->SigClicked().Connect(this, &COptionControlActionNode::OnClickBtnSetKey);
}

/**
* \biref COptionControlActionNode�� �Ҹ���
*/
COptionControlActionNode::~COptionControlActionNode()
{
	NTL_DELETE( m_pStbTitle );
	NTL_DELETE( m_pBtnSetKey );
}

/**
* \brief COptionControlActionNode�� ǥ��
*/
void COptionControlActionNode::ShowProc()
{
	CGuiLineTreeNode::ShowProc();

	m_pStbTitle->Show(true);
	m_pBtnSetKey->Show(true);
	
	m_pBtnSetKey->SetPosition(m_nPosX + dOPTIONCONTROL_ACTIONNODE_BUTTON_X, m_nPosY + dOPTIONCONTROL_ACTIONNODE_BUTTON_Y);
	m_pStbTitle->SetPosition(m_nPosX + dOPTIONCONTROL_ACTIONNODE_TITLE_X, m_nPosY + dOPTIONCONTROL_ACTIONNODE_TITLE_Y);
}

/**
* \brief COptionControlActionNode�� ����
*/
void COptionControlActionNode::HideProc()
{
	CGuiLineTreeNode::HideProc();

	m_pStbTitle->Show(false);
	m_pBtnSetKey->Show(false);

	if( GetInputActionMap()->GetInputMode() == (RwUInt32)m_nID )
	{
		GetInputActionMap()->InitInputMode();
		m_pBtnSetKey->Enable( true );
		COptionControlList* pMgr = static_cast<COptionControlList *>(m_pMgr);

		pMgr->GetParentTab()->SetGuideDefault();
	}
}

/**
* \brief Ű ���� ��ư�� ������ �� �߻��Ǵ� ��
*/
void COptionControlActionNode::OnClickBtnSetKey(gui::CComponent* pComponent)
{
	COptionControlList* pMgr = static_cast<COptionControlList *>(m_pMgr);

	// InputActionMap �� ���� �Ұ����� mdoe�� ��
	if( GetInputActionMap()->GetActionMapMode() == ACTIONMAP_MODE_DEFAULT )
	{
		pMgr->GetParentTab()->SetGuideNegativeMode();
		return;
	}

	// ���� �Ұ��� ����Ұ���� �˷������.
	if( m_bFixed )
	{
		pMgr->GetParentTab()->SetGuideFixed( m_nID );
	}
	else
	{
		pMgr->GetParentTab()->SetGuideText(dOPTIONCONTROL_STATICBOX_COLOR, L"DST_OPTION_CONTROL_TEXT_READYGUIDE" );
		pMgr->UpdateNode();
		GetInputActionMap()->SetInputMode( m_nAction );
	
		// ��ư�� ��Ȱ��ȭ�Ѵ�.
		m_pBtnSetKey->Enable(false);
	}
}

void COptionControlActionNode::SetText( std::wstring& strTitle ) 
{
	m_pBtnSetKey->SetText( strTitle );
}

void COptionControlActionNode::Update() 
{
	m_pBtnSetKey->Enable( true );

	// �׼� ID�� ���� ���ڿ��� ������ش�.
	std::wstring wstrKeyName = GetInputActionMap()->GetKeyName( m_nID );

	// ��� �ִٸ� "�����ȵ�" ���, �ƴ϶�� Ű�� �̸��� �״�� ����Ѵ�.
	if( wstrKeyName.empty() )
		m_pBtnSetKey->SetText( GetDisplayStringManager()->GetString( "DST_OPTION_CONTROL_TEXT_EMPTYKEY" ) );
	else
		m_pBtnSetKey->SetText( wstrKeyName.c_str() );
}


/////////////////////////////////////////////////////////////////////////////
// class : COptionControlCategoryNode

/**
* \brief COptionControlList�� ������
*/
COptionControlList::COptionControlList()
{
}

/**
* \brief COptionControlList�� �Ҹ���
*/
COptionControlList::~COptionControlList()
{
}

/**
* \brief COptionControlList�� CGuiLineTree�� ����� �Լ�
*
* LineTree�� ����� ��ũ�ѹ��� �Ӽ��� �����Ѵ�.
*
* \param rect (CRectangle&)
*/
RwBool COptionControlList::Create(CRectangle& rect, gui::CComponent* pParent, RwInt32 nLineHeight, RwInt32 nLineMargin, RwInt32 nChildXMargin, RwInt32 nScrollBarWidth, COptionControl* pOptionControl)
{
	if (!CGuiLineTree::Create(rect, pParent, nLineHeight, nLineMargin, nChildXMargin, nScrollBarWidth))
		return FALSE;

	m_pScroll->AddSurfaceLayout( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "GameCommon.srf", "srfScrollLayout" ) );
	m_pScroll->AddSurfaceSlider( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "GameCommon.srf", "srfScrollMedium" ) );
	m_pScroll->GetDecreaseButton()->AddSurfaceUp( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "GameCommon.srf", "srfScrollPrevBtnUp" ) );
	m_pScroll->GetDecreaseButton()->AddSurfaceDown( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "GameCommon.srf", "srfScrollPrevBtnDown" ) );
	m_pScroll->GetDecreaseButton()->AddSurfaceFocus( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "GameCommon.srf", "srfScrollPrevBtnFoc" ) );
	m_pScroll->GetIncreaseButton()->AddSurfaceUp( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "GameCommon.srf", "srfScrollNextBtnUp" ) );
	m_pScroll->GetIncreaseButton()->AddSurfaceDown( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "GameCommon.srf", "srfScrollNextBtnDown" ) );
	m_pScroll->GetIncreaseButton()->AddSurfaceFocus( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "GameCommon.srf", "srfScrollNextBtnUp" ) );
	m_pScroll->SetButtonSize(dOPTIONCONTROL_LIST_SCROLL_WIDTH, dOPTIONCONTROL_LIST_SCROLL_HEIGHT);
	m_pScroll->SetSliderSize(dOPTIONCONTROL_LIST_SLIDER_WIDTH, dOPTIONCONTROL_LIST_SLIDER_HEIGHT);

	m_slotCaptureWheelMove = GetNtlGuiManager()->GetGuiManager()->SigCaptureWheelMove().Connect( this, &COptionControlList::OnCaptureWheelMove );

	m_pOptionControl = pOptionControl;

	return TRUE;
}

/**
* \brief OptionControl�� �׸���� ����
*/
void COptionControlList::CreateTree() 
{
	//////////////////////////////////////////////////////////////////////////////
	// �ƹ�Ÿ ���� ī�װ�
	CGuiLineTreeNode* pNode = NTL_NEW COptionControlCategoryNode(this, 
		GetDisplayStringManager()->GetString( "DST_OPTION_CONTROL_CATEGORY_AVATAR" ) ,	// ī�װ� ����
		dOPTIONCONTROL_CATEGORY_AVATAR );												// ī�װ� ID
	CGuiLineTree::AddNode( pNode, GUILINETREE_ROOTNODE_ID );							// CGuiLineTree ��Ʈ�� �θ�� ������
	pNode->Expand( true );

	// ���������� ������ Ȯ���� ������� �Ѵ�. ������� ���� ������ ���̰� �ȴ�.
	for(RwUInt32 nActionID = ACTION_AVATAR_FORWARD; nActionID <= ACTION_AVATAR_RIGHTSIDE; ++nActionID)
	{
		pNode = NTL_NEW COptionControlActionNode(this,
			GetActionDisplayStringNum(nActionID),								// Action ����
			nActionID );															// Action ID
		CGuiLineTree::AddNode( pNode, dOPTIONCONTROL_CATEGORY_AVATAR );							// ī�װ��� �θ�� ������.
	}
	
	//////////////////////////////////////////////////////////////////////////////
	// Ÿ�� ���� ī�װ�
	pNode = NTL_NEW COptionControlCategoryNode(this, 
		GetDisplayStringManager()->GetString( "DST_OPTION_CONTROL_CATEGORY_TARGET") , 
		dOPTIONCONTROL_CATEGORY_TARGET );
	CGuiLineTree::AddNode( pNode, GUILINETREE_ROOTNODE_ID );
	pNode->Expand( true );

	for(RwUInt32 nActionID = ACTION_TARGET_SELF; nActionID <= ACTION_TARGET_4THPARTY; ++nActionID)
	{
		pNode = NTL_NEW COptionControlActionNode(this,
			GetActionDisplayStringNum(nActionID),
			nActionID );
		CGuiLineTree::AddNode( pNode, dOPTIONCONTROL_CATEGORY_TARGET );
	}

	pNode = NTL_NEW COptionControlActionNode(this, 
		GetDisplayStringManager()->GetString( "DST_OPTION_CONTROL_ACTION_TARGET_AUTOPARTY" ),
		ACTION_TARGET_AUTOTARGET_PARTY );
	CGuiLineTree::AddNode( pNode, dOPTIONCONTROL_CATEGORY_TARGET );

	for( RwUInt32 nActionID = ACTION_TARGET_AUTO; nActionID <= ACTION_TARGET_SELECTING_5; ++nActionID )
	{
		pNode = NTL_NEW COptionControlActionNode(this,
			GetActionDisplayStringNum(nActionID),
			nActionID );
		CGuiLineTree::AddNode( pNode, dOPTIONCONTROL_CATEGORY_TARGET );
	}

	//////////////////////////////////////////////////////////////////////////////
	// ������ ���� ī�װ�
	pNode = NTL_NEW COptionControlCategoryNode(this, 
		GetDisplayStringManager()->GetString( "DST_OPTION_CONTROL_CATEGORY_QUICKSLOT") , 
		dOPTIONCONTROL_CATEGORY_QUICKSLOT );
	CGuiLineTree::AddNode( pNode, GUILINETREE_ROOTNODE_ID );
	pNode->Expand( true );

	for(RwUInt32 nActionID = ACTION_QUICK_1; nActionID <= ACTION_QUICK_PLUS; ++nActionID)
	{
		pNode = NTL_NEW COptionControlActionNode(this,
			GetActionDisplayStringNum(nActionID),
			nActionID );
		CGuiLineTree::AddNode( pNode, dOPTIONCONTROL_CATEGORY_QUICKSLOT );
	}

	//////////////////////////////////////////////////////////////////////////
	// Ȯ��
	// 80 ~ 159 ���� ���ڸ� ����
	for(RwUInt32 nActionID = ACTION_QUICK_1_EX; nActionID <= ACTION_QUICK_PLUS_EX2; ++nActionID )
	{
		pNode = NTL_NEW COptionControlActionNode(this,
			GetActionDisplayStringNum(nActionID),
			nActionID );
		CGuiLineTree::AddNode( pNode, dOPTIONCONTROL_CATEGORY_QUICKSLOT );
	}

	// ������ ���� ����
	for(RwUInt32 nActionID = ACTION_QUICK_PREV; nActionID <= ACTION_QUICK_5THCAP; ++nActionID )
	{
		pNode = NTL_NEW COptionControlActionNode(this,
			GetActionDisplayStringNum(nActionID),
			nActionID );
		CGuiLineTree::AddNode( pNode, dOPTIONCONTROL_CATEGORY_QUICKSLOT );
	}

	//////////////////////////////////////////////////////////////////////////////
	// ������ ���� ī�װ�
	pNode = NTL_NEW COptionControlCategoryNode(this, 
		GetDisplayStringManager()->GetString( "DST_OPTION_CONTROL_CATEGORY_WINDOW") , 
		dOPTIONCONTROL_CATEGORY_WINDOW );
	CGuiLineTree::AddNode( pNode, GUILINETREE_ROOTNODE_ID );
	pNode->Expand( true );

	for(RwUInt32 nActionID = ACTION_WINDOW_PROFILE; nActionID <= ACTION_WINDOW_RANKBOARD; ++nActionID)
	{
		pNode = NTL_NEW COptionControlActionNode(this,
			GetActionDisplayStringNum( nActionID ),
			nActionID );
		CGuiLineTree::AddNode( pNode, dOPTIONCONTROL_CATEGORY_WINDOW );
	}

	//////////////////////////////////////////////////////////////////////////////
	// ���� ī�װ�
	pNode = NTL_NEW COptionControlCategoryNode(this, 
		GetDisplayStringManager()->GetString( "DST_OPTION_CONTROL_CATEGORY_FIXED") , 
		dOPTIONCONTROL_CATEGORY_FIXED );
	CGuiLineTree::AddNode( pNode, GUILINETREE_ROOTNODE_ID );
	pNode->Expand( true );

	// �̴ϸ� ���
	pNode = NTL_NEW COptionControlActionNode(this,
		GetDisplayStringManager()->GetString( "DST_OPTION_CONTROL_ACTION_MINIMAP_ZOOMOUT" ),
		ACTION_MINIMAP_ZOOMOUT , true);
	CGuiLineTree::AddNode( pNode, dOPTIONCONTROL_CATEGORY_FIXED );

	// �̴ϸ� Ȯ��
	pNode = NTL_NEW COptionControlActionNode(this,
		GetDisplayStringManager()->GetString( "DST_OPTION_CONTROL_ACTION_MINIMAP_ZOOMIN" ),
		ACTION_MINIMAP_ZOOMIN , true);
	CGuiLineTree::AddNode( pNode, dOPTIONCONTROL_CATEGORY_FIXED );

	// ä��â ���� ������
	pNode = NTL_NEW COptionControlActionNode(this,
		GetDisplayStringManager()->GetString( "DST_OPTION_CONTROL_ACTION_CHAT_PGUP" ),
		ACTION_CHAT_PGUP , true);
	CGuiLineTree::AddNode( pNode, dOPTIONCONTROL_CATEGORY_FIXED );

	// ä��â ���� ������
	pNode = NTL_NEW COptionControlActionNode(this,
		GetDisplayStringManager()->GetString( "DST_OPTION_CONTROL_ACTION_CHAT_PGDN" ),
		ACTION_CHAT_PGDN , true);
	CGuiLineTree::AddNode( pNode, dOPTIONCONTROL_CATEGORY_FIXED );

	// ���
	pNode = NTL_NEW COptionControlActionNode(this,
		GetDisplayStringManager()->GetString( "DST_OPTION_CONTROL_ACTION_GLOBAL_CANCLE" ),
		ACTION_GLOBAL_CANCLE , true);
	CGuiLineTree::AddNode( pNode, dOPTIONCONTROL_CATEGORY_FIXED );

	// ��ũ����
	pNode = NTL_NEW COptionControlActionNode(this,
		GetDisplayStringManager()->GetString( "DST_OPTION_CONTROL_ACTION_GLOBAL_SNAPSHOT" ),
		ACTION_GLOBAL_SNAPSHOT , true);
	CGuiLineTree::AddNode( pNode, dOPTIONCONTROL_CATEGORY_FIXED );

	// ä���Է�
	pNode = NTL_NEW COptionControlActionNode(this,
		GetDisplayStringManager()->GetString( "DST_OPTION_CONTROL_ACTION_GLOBAL_CHAT" ),
		ACTION_GLOBAL_CHAT , true);
	CGuiLineTree::AddNode( pNode, dOPTIONCONTROL_CATEGORY_FIXED );


//		ACTION_DEVUSER_ONLYRENDERGUI = 200,	///< ���߿��� (GUI�� �׸���. �ӽ�)
}

/**
* \brief ������ ��带 ������Ʈ ���ش�.
*
* COptionControlActionNode���� Update() �Լ��� ȣ���Ѵ�.
*/
void COptionControlList::UpdateNode() 
{
	for(int i=ACTION_AVATAR_FORWARD; i != ACTION_NUMS; ++i)
	{
		COptionControlActionNode* pActionNode = 
			static_cast<COptionControlActionNode*>(FindNode( i ));

		if( pActionNode )
			pActionNode->Update();
	}
	
}

void COptionControlList::OnCaptureWheelMove( RwInt32 nFlag, RwInt16 sDelta, CPos& pos ) 
{
	if( !GetParentGui()->IsVisible() )
		return;
	
	if( GetParentGui()->PosInRect( pos.x, pos.y ) != gui::CComponent::INRECT )
		return;

	RwInt32 nValue = static_cast<gui::CScrollBar*>(CGuiLineTree::GetScrollBar())->GetValue();
	RwInt32 nMaxValue = static_cast<gui::CScrollBar*>(CGuiLineTree::GetScrollBar())->GetMaxValue();
	RwInt32 nDelta = nValue - sDelta / GUI_MOUSE_WHEEL_DELTA;

	if( nDelta < 0 )
		nDelta = 0;
	else if( nDelta > nMaxValue )
		nDelta = nMaxValue;

	static_cast<gui::CScrollBar*>(CGuiLineTree::GetScrollBar())->SetValue( nDelta );	
}

COptionControl* COptionControlList::GetParentTab() 
{
	if( m_pOptionControl ) 
		return m_pOptionControl; 
	else 
		return NULL;
}
//////////////////////////////////////////////////////////////////////////////////
// class : COptionControl

COptionControl::COptionControl()
{
	m_pOptionControlList = NULL;	
	m_pDlgControlList = NULL;	
	m_pStbControlTitle = NULL;
	m_pStbControlBack = NULL;
	m_pStbControlText = NULL;	
}

COptionControl::~COptionControl()
{
}

RwBool COptionControl::Create(COptionWindowGui* pOptionWindow)
{
	NTL_FUNCTION("COptionControl::Create");
	COptionBase::Create(pOptionWindow);

	// ������Ʈ�� Ÿ��Ʋ
	m_pStbControlTitle = (gui::CStaticBox*)GetComponent("stbControlTitle");
	m_pStbControlTitle->SetText( GetDisplayStringManager()->GetString( "DST_OPTION_CONTROL_TEXT_TITLE" ) );

	// GUI LineTree�� ����ϱ� ���� ���� Dialog
	m_pDlgControlList = (gui::CDialog*)GetComponent("dlgControlList");

	// Gui Line Tree�� ũ�⸦ rect�� �����Ѵ�.
	CRectangle rect;
	rect.SetRectWH(dOPTIONCONTROL_LIST_X, dOPTIONCONTROL_LIST_Y, 
		dOPTIONCONTROL_LIST_WIDTH, dOPTIONCONTROL_LIST_HEIGHT);

	// GuiLineTree�� �����Ѵ�.
	m_pOptionControlList = NTL_NEW COptionControlList;
	if (!m_pOptionControlList->Create(rect, m_pDlgControlList, 
		dOPTIONCONTROL_LINE_HEIGHT,			// �� ������ ����
		dOPTIONCONTROL_LINE_MARGIN,			// �� ������ ����
		dOPTIONCONTROL_CHILD_MARGIN_WIDTH,	// �ڽĵ��� ����
		dOPTIONCONTROL_LIST_SLIDER_WIDTH, this))	// �����̴��� ����
		return FALSE;

	// ����Ű�� ������ �� �ִ� �����۵��� ����
	m_pOptionControlList->CreateTree();

	// TextBox�� ����
	m_pStbControlBack = (gui::CStaticBox*)GetComponent("stbControlBack");
	m_pStbControlText = (gui::CStaticBox*)GetComponent("stbControlText");

	NTL_RETURN(TRUE);
}

void COptionControl::Destroy()
{
	NTL_FUNCTION("COptionControl::Destroy");

	if (m_pOptionControlList)
	{
		m_pOptionControlList->Destroy();
		NTL_DELETE(m_pOptionControlList);
	}

	NTL_RETURNVOID();
}

void COptionControl::Show()
{
	// COptionBase�� ScrollBar�� ������� �ʴ´�.
	m_pScrollBar->Show(false);

	m_pStbControlTitle->Show(true);
	m_pDlgControlList->Show(true);
	m_pStbControlBack->Show(true);
	
	// �⺻ �ȳ� �޽��� ����
	SetGuideDefault(); 
	m_pStbControlText->Show(true);

	COptionBase::Show();
}

void COptionControl::Hide()
{	
	// COptionBase�� ScrollBar ���
	m_pScrollBar->Show(true);

	m_pDlgControlList->Show(false);
	m_pStbControlTitle->Show(false);
	m_pStbControlBack->Show(false);
	m_pStbControlText->Show(false);

	GetInputActionMap()->InitInputMode();	   ///< �׼Ǹ� �Է� ����� ����
	//GetInputActionMap()->CancleActionMap();	   ///< �׼Ǹ��� �ӽ� ����Ȱ��� �ε�
	
	// ����� ������Ʈ
	m_pOptionControlList->UpdateNode();
		
	COptionBase::Hide();
}

void COptionControl::OnInit()
{
}

void COptionControl::OnReset()
{
	// ������ ����Ǿ��� �׼��� ���������ش�.
	GetInputActionMap()->InitInputMode();
	GetInputActionMap()->InitDefaultActionMap();

	m_pOptionControlList->UpdateNode();
	SetGuideDefault();
}

void COptionControl::OnOk()
{
	GetInputActionMap()->InitInputMode();
	
	// ���� �������� �ְ� ������ �Ǿ��ٸ� Node�� ������Ʈ�Ѵ�.
	if( GetInputActionMap()->ApplyActionMap() )
	{
		m_pOptionControlList->UpdateNode();
		SetGuideDefault();
	}
	else
		SetGuideText(dOPTIONCONTROL_STATICBOX_WARNING_COLOR, L"DST_OPTION_CONTROL_TEXT_WAITGUIDE" );
}

void COptionControl::OnCancel()
{
	GetInputActionMap()->CancleActionMap();
}

/**
* \breif OnHandleEvents
*/
void COptionControl::OnHandleEvents( RWS::CMsg &pMsg ) 
{
	// �׼Ǹʿ��� ������ ���� ���� ó���Ѵ�.
	if( pMsg.Id == g_EventActionMapClientNotify )
	{
		SNtlEventActionMapClientNotify* pData = reinterpret_cast<SNtlEventActionMapClientNotify*>( pMsg.pData );

		m_pOptionControlList->UpdateNode();

		switch( pData->byType )
		{
		case SNtlEventActionMapClientNotify::ACTIONMAP_OK:							// ������ ����ƴٰ� �˸�
			SetGuideDefault();
			break;
		case SNtlEventActionMapClientNotify::ACTIONMAP_RELEASE:							// Ű�� ����ƴٰ� �˸�
			SetGuideChange( pData->wParam1 );
			break;
		case SNtlEventActionMapClientNotify::ACTIONMAP_FIXEDKEY:						// Ű�� ������ Ű��� �˸�
			SetGuideText( dOPTIONCONTROL_STATICBOX_GUIDE_COLOR, L"DST_OPTION_CONTROL_TEXT_FIXEDKEYGUIDE" );
			break;
		case SNtlEventActionMapClientNotify::ACTIONMAP_NOTCOMBINE:						// ����Ű�δ� �������Ѵٰ� �˸�
			SetGuideText( dOPTIONCONTROL_STATICBOX_GUIDE_COLOR, L"DST_OPTION_CONTROL_TEXT_NOTCOMBINEGUIDE" );
			break;
		case SNtlEventActionMapClientNotify::ACTIONMAP_SAMEKEY:
			SetGuideText( dOPTIONCONTROL_STATICBOX_GUIDE_COLOR, L"DST_OPTION_CONTROL_TEXT_SAMEKEYGUIDE" );
			break;
		default:
			break;
		}
	}
}

void COptionControl::SetGuideText( RwUInt32 uiColor, const WCHAR* pString ) 
{
	m_pStbControlText->SetTextColor( uiColor );
	m_pStbControlText->SetText( pString );
}

/**
* \brief �⺻���� ����Ű ������ �ȳ�
*/
void COptionControl::SetGuideDefault() 
{
	WCHAR awcTemp[512];
	swprintf_s(awcTemp, 512, GetDisplayStringManager()->GetString("DST_OPTION_CONTROL_TEXT_GUIDE"),
		GetDisplayStringManager()->GetString("DST_OPTION_CONTROL_TEXT_EMPTYKEY"));
	
	SetGuideText( dOPTIONCONTROL_STATICBOX_COLOR, awcTemp );
}

/**
* \brief Ű�� �ߺ��Ǿ� �����ȵ����� ������ Ű�� �ȳ�
*/
void COptionControl::SetGuideChange(RwUInt32 nAction) 
{
	WCHAR awcTemp[512];
	swprintf_s(awcTemp, 512, 
		GetDisplayStringManager()->GetString("DST_OPTION_CONTROL_TEXT_CHANGEGUIDE"),
		GetActionDisplayStringNum(nAction),
		GetActionDisplayStringNum(nAction),
		GetDisplayStringManager()->GetString("DST_OPTION_CONTROL_TEXT_EMPTYKEY"));

	SetGuideText( dOPTIONCONTROL_STATICBOX_WARNING_COLOR, awcTemp );
}

/**
* \brief ���� �Ұ����� Ű��� ���� �ȳ�
*/
void COptionControl::SetGuideFixed( RwUInt32 nAction ) 
{
	WCHAR awcTemp[512];
	swprintf_s( awcTemp, 512, GetDisplayStringManager()->GetString("DST_OPTION_CONTROL_TEXT_NOTCHANGEGUIDE"),
		GetActionDisplayStringNum( nAction ) );
	
	SetGuideText( dOPTIONCONTROL_STATICBOX_GUIDE_COLOR, awcTemp );
}

/**
* \brief ���� ��忡���� ������ �Ұ����մϴ� ��� ���� �ȳ�
*/
void COptionControl::SetGuideNegativeMode()
{
	SetGuideText( dOPTIONCONTROL_STATICBOX_GUIDE_COLOR, 
		GetDisplayStringManager()->GetString("DST_OPTION_CONTROL_TEXT_NEGATIVEMODEGUIDE") );
}

