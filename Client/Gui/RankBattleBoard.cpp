#include "precomp_dboclient.h"
#include "RankBattleBoard.h"

// core
#include "NtlDebug.h"
#include "NtlPLDef.h"

// shared
#include "NtlTimeQuest.h"
#include "NtlRankBattle.h"

// simulation
#include "DboEvent.h"

// presentation
#include "NtlPLGuiManager.h"
#include "NtlPLEvent.h"

// Dbo
#include "DboGlobal.h"
#include "DboLogic.h"
#include "DboEventGenerator.h"
#include "DisplayStringManager.h"
#include "AlarmManager.h"
#include "InfoWndManager.h"
#include "RankBoardGui.h"

////////////////////////////////////////////////////////////////////////////////////
// CRankBattleSubject
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// CRankBattleRowItem
////////////////////////////////////////////////////////////////////////////////////

/**
* \brief ������
*/
CRankBattleRowItem::CRankBattleRowItem() 
: m_pStbRank(NULL)
, m_pStbName(NULL)
, m_pStbLevel(NULL)
, m_pPanClass(NULL)
, m_pStbGuildName(NULL)
, m_pStbPoint(NULL)
, m_pStbStraightWin(NULL)
, m_pStbCompare(NULL)
, m_pPanCompareMark(NULL)
, m_nRank(0)
, m_pDlgItem(NULL)
, m_byClass(INVALID_BYTE)
{

}

/**
* \brief �Ҹ���
*/
CRankBattleRowItem::~CRankBattleRowItem() 
{

}

/**
* \brief Create
* \param pParentGui		(gui::CComponent*) �θ� GUI�� ������
* \param nTop			(RwInt32) ������ �������� ���۵� Y ��ǥ
*/
VOID CRankBattleRowItem::Create( gui::CComponent* pParentGui , RwInt32 nTop ) 
{
	// ������ ��ġ
	CRectangle rect;

	rect.SetRectWH( 0, nTop, 631, 25 );
	m_pDlgItem = NTL_NEW gui::CDialog( &rect, pParentGui, GetNtlGuiManager()->GetSurfaceManager() );
	
	// ����(����)
	rect.SetRectWH( 6, 0, 43, 25 );
	m_pStbRank = NTL_NEW gui::CStaticBox( &rect, m_pDlgItem, GetNtlGuiManager()->GetSurfaceManager(),
		COMP_TEXT_VERTICAL_CENTER | COMP_TEXT_CENTER );
	m_pStbRank->CreateFontStd( DETAIL_FONT , dRANKBOARD_RANKBATTLE_ROWITEM_FONT_HEIGHT, 0 );

	// �̸�(���ڿ�)
	rect.SetRectWH( 61, 0, 120, 25 );
	m_pStbName = NTL_NEW gui::CStaticBox( &rect, m_pDlgItem, GetNtlGuiManager()->GetSurfaceManager(),
		COMP_TEXT_VERTICAL_CENTER | COMP_TEXT_CENTER );
	m_pStbName->CreateFontStd( DETAIL_FONT, dRANKBOARD_RANKBATTLE_ROWITEM_FONT_HEIGHT, 0 );
	
	// ����(����)
	rect.SetRectWH( 199, 0, 30, 25 );
	m_pStbLevel = NTL_NEW gui::CStaticBox( &rect, m_pDlgItem, GetNtlGuiManager()->GetSurfaceManager(),
		COMP_TEXT_VERTICAL_CENTER | COMP_TEXT_CENTER );
	m_pStbLevel->CreateFontStd( DETAIL_FONT, dRANKBOARD_RANKBATTLE_ROWITEM_FONT_HEIGHT, 0 );

	// ����(�׸�)
	rect.SetRectWH( 252, 2, 19, 29 );
	m_pPanClass = NTL_NEW gui::CPanel( &rect, m_pDlgItem, GetNtlGuiManager()->GetSurfaceManager() );
	
	// ����̸�(���ڿ�)
	rect.SetRectWH( 293, 0, 136, 25 );
	m_pStbGuildName = NTL_NEW gui::CStaticBox( &rect, m_pDlgItem, GetNtlGuiManager()->GetSurfaceManager(),
		COMP_TEXT_VERTICAL_CENTER | COMP_TEXT_CENTER );
	m_pStbGuildName->CreateFontStd( DETAIL_FONT, dRANKBOARD_RANKBATTLE_ROWITEM_FONT_HEIGHT, 0 );

	// ����(����)
	rect.SetRectWH( 432, 0, 66, 25 );
	m_pStbPoint = NTL_NEW gui::CStaticBox( &rect, m_pDlgItem, GetNtlGuiManager()->GetSurfaceManager(),
		COMP_TEXT_VERTICAL_CENTER | COMP_TEXT_CENTER );
	m_pStbPoint->CreateFontStd( DETAIL_FONT, dRANKBOARD_RANKBATTLE_ROWITEM_FONT_HEIGHT, 0 );
	
	// ����(����)
	rect.SetRectWH( 514, 0, 24, 25 );
	m_pStbStraightWin = NTL_NEW gui::CStaticBox( &rect, m_pDlgItem, GetNtlGuiManager()->GetSurfaceManager(),
		COMP_TEXT_VERTICAL_CENTER | COMP_TEXT_CENTER );
	m_pStbStraightWin->CreateFontStd( DETAIL_FONT, dRANKBOARD_RANKBATTLE_ROWITEM_FONT_HEIGHT, 0 );

	// �񱳵��(����)
	rect.SetRectWH( 518, 0, 72, 25 );
	m_pStbCompare = NTL_NEW gui::CStaticBox( &rect, m_pDlgItem, GetNtlGuiManager()->GetSurfaceManager(),
		COMP_TEXT_VERTICAL_CENTER | COMP_TEXT_RIGHT );
	m_pStbCompare->CreateFontStd( DETAIL_FONT, dRANKBOARD_RANKBATTLE_ROWITEM_FONT_HEIGHT, 0 );

	// �񱳸�ũ(�׸�)
	rect.SetRectWH( 593, 8, 8, 7 );
	m_pPanCompareMark = NTL_NEW gui::CPanel( &rect, m_pDlgItem, GetNtlGuiManager()->GetSurfaceManager() );

	// Signals
	m_slotMouseEnterFromClass = m_pPanClass->SigMouseEnter().Connect( this, &CRankBattleRowItem::OnMouseEnterFromClass );
	m_slotMouseLeaveFromClass = m_pPanClass->SigMouseLeave().Connect( this, &CRankBattleRowItem::OnMouseLeaveFromClass );
}

/**
* \brief Destory
*/
VOID CRankBattleRowItem::Destroy() 
{
	NTL_DELETE( m_pPanCompareMark );
	NTL_DELETE( m_pStbCompare );
	NTL_DELETE( m_pStbStraightWin );
	NTL_DELETE( m_pStbPoint );
	NTL_DELETE( m_pStbGuildName );
	NTL_DELETE( m_pPanClass );
	NTL_DELETE( m_pStbLevel );
	NTL_DELETE( m_pStbName );
	NTL_DELETE( m_pStbRank );
	NTL_DELETE( m_pDlgItem );
}

/**
* \brief ������ �������� �������� �� �������� �����Ѵ�.
* \param bShow		(RwBool) �������� ����
* 
*/
VOID CRankBattleRowItem::Show( RwBool bShow /*= TRUE */ ) 
{
	m_pDlgItem->Show(B2b(bShow) );
}

/**
* \brief �׸��� �����͸� ����
* \param nRank			����	
* \param pwcName		�̸�
* \param nLevel			����
* \param byClass		����(NtlCharacter.h)
* \param pwcGuildName	����̸�
* \param nPoint			����
* \param nStraightWin	����
* \param nCompare		�񱳵��
* \param bHighLight		����( TRUE = ���� FALSE = �������� ���� )
*/
VOID CRankBattleRowItem::SetItem(  RwInt32 nRank, const WCHAR* pwcName, RwInt32 nLevel, 
									RwUInt8 byClass, const WCHAR* pwcGuildName, RwInt32 nPoint, 
									RwUInt16 nStraightWin, RwUInt32 nCompare , RwBool bHightLight/* FALSE  */) 
{	
	// �����̽��� �ʱ�ȭ
	m_pDlgItem->GetSurface()->clear();
	
	// �˻� �� ����� �����Ͽ� ǥ���Ѵ�.
	if( bHightLight )
	{
		m_pDlgItem->AddSurface( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "RankingGui.srf", "srfHighLightLeft" ) );
		m_pDlgItem->AddSurface( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "RankingGui.srf", "srfHighLightCenter" ) );
		m_pDlgItem->AddSurface( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "RankingGui.srf", "srfHighLightRight" ) );
	}
		
	m_nRank = nRank;

	m_pStbRank->SetText( nRank );
	m_pStbName->SetText( pwcName );
	m_pStbLevel->SetText( nLevel );
	m_pPanClass->GetSurface()->clear();
	m_pPanClass->AddSurface( Logic_GetPCClassIconSurface( byClass, FALSE ) );
	m_byClass = byClass;							// ���� ���� ����
	m_pStbGuildName->SetText( pwcGuildName );
	m_pStbPoint->SetText( nPoint );
	m_pStbStraightWin->SetText( nStraightWin );

	// nCompare�� DWORD_INVALID �� ��� ( ������ �� ��¥�� ��ϵ� ����� ���ٴ� �� )
	if( nCompare == -1 )
	{
		m_pStbCompare->SetText( L"-" );
		m_pPanCompareMark->GetSurface()->clear();
		Show( TRUE );
		return;
	}

	// �� ���( ���� �������� ���� ������ ���ش�. )
	RwInt32 nAbsComp = nCompare - nRank;

	m_pStbCompare->SetText( abs(nAbsComp) );

	m_pPanCompareMark->GetSurface()->clear();

	// �� ��ũ
	if( nAbsComp > 0 )
		m_pPanCompareMark->AddSurface( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "RankingGui.srf", "srfCompareUp" ) );
	else if( nAbsComp < 0 )
		m_pPanCompareMark->AddSurface( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "RankingGui.srf", "srfCompareDown" ) );
	
	Show( TRUE );
}

/**
* \brief �񱳵���� ����
* \param nCompare ������ ����
*/
VOID CRankBattleRowItem::SetCompareInfo( RwInt32 nCompare ) 
{
	if( nCompare == -1 )
	{
		m_pStbCompare->SetText( L"-" );
		m_pPanCompareMark->GetSurface()->clear();
		Show( TRUE );
		return;
	}

	// �� ���( ���� �������� ���� ������ ���ش�. )
	RwInt32 nAbsComp = nCompare - m_nRank;

	m_pStbCompare->SetText( abs(nAbsComp) );


	// �� ��ũ
	m_pPanCompareMark->GetSurface()->clear();

	if( nAbsComp > 0 )
		m_pPanCompareMark->AddSurface( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "RankingGui.srf", "srfCompareUp" ) );
	else if( nAbsComp < 0 )
		m_pPanCompareMark->AddSurface( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "RankingGui.srf", "srfCompareDown" ) );
}

/**
* \brief �������� �ʱ�ȭ�Ѵ�.
*/
VOID CRankBattleRowItem::ClearItem()
{
	m_pDlgItem->GetSurface()->clear();
	m_pStbRank->SetText( L"---" );
	m_pStbName->SetText( L"---" );
	m_pStbLevel->SetText( L"---" );
	m_pPanClass->GetSurface()->clear();
	m_pStbGuildName->SetText( L"---" );
	m_pStbPoint->SetText( L"---" );
	m_pStbStraightWin->SetText( L"---" );
	m_pStbCompare->SetText( L"---" );
	m_pPanCompareMark->GetSurface()->clear();
	m_nRank = INVALID_DWORD;
	m_byClass = INVALID_BYTE;
}

/**
* \brief ���� ��ũ�� ������ �ܴ�.
* \param pComponent	(gui::CComponent*) ���콺�� ���� ������Ʈ
*/
VOID CRankBattleRowItem::OnMouseEnterFromClass( gui::CComponent* pComponent ) 
{
	// InfoWindow�� ��ư�� �޾��ش�.
	if( m_byClass == INVALID_BYTE )
		return;

	if( m_pPanClass )
	{
		CRectangle rtScreen = m_pPanClass->GetScreenRect();
		// ToolTip�� infoWindow�� �����Ѵ�.
		
		GetInfoWndManager()->ShowInfoWindow( TRUE, CInfoWndManager::INFOWND_JUST_WTEXT,
				rtScreen.left, rtScreen.top, 
				(void*)Logic_GetClassName( m_byClass ), 
				DIALOG_RANKBOARD );
	}
}

/**
* \brief ���� ��ũ�� ������ �����Ѵ�.
* \param pComponent (gui::CComponent*) ���콺 �����Ͱ� ���� ������Ʈ
*/
VOID CRankBattleRowItem::OnMouseLeaveFromClass( gui::CComponent* pComponent ) 
{
	/*if( m_byClass == INVALID_BYTE )
		return;*/
	if( m_pPanClass )
	{
		if( DIALOG_RANKBOARD == GetInfoWndManager()->GetRequestGui() )
			GetInfoWndManager()->ShowInfoWindow( FALSE );
	}

}


////////////////////////////////////////////////////////////////////////////////////
// CRankBattleBoard
////////////////////////////////////////////////////////////////////////////////////

/**
* \brief ������
*/
CRankBattleBoard::CRankBattleBoard()
: m_pRankBattleBoardDlg(NULL)
, m_pParentGui(NULL)
, m_nCurrentCompareDay(1)
, m_nCurrentPage(0)
, m_nRankBattleItemCount(0)
{
	// Clear
	ZeroMemory( m_sRankBattleItem, sizeof(sRANKBATTLE_ITEM) * dRANKBOARD_RANKBATTLE_ROWITEM_NUMS );
	ZeroMemory( m_awcSearchName, sizeof(WCHAR) * (NTL_MAX_SIZE_CHAR_NAME+1) );
	m_byDataResult = eDATA_NONE;
	m_nSearchMode = eSEARCH_RANK;
	m_bSearchRank = FALSE;
}

/**
* \brief �Ҹ���
*/
CRankBattleBoard::~CRankBattleBoard() 
{
}

/**
* \brief Create
* \param eType		������ Ÿ��(CBoard*)
* \param pParentGui �θ� GUI�� ������
*/
void CRankBattleBoard::Create( eBoardType eType , CRankBoardGui* pParent ) 
{
	m_pParentGui = pParent;

	m_eBoardType = eType;

	// UI
	m_pRankBattleBoardDlg = (gui::CDialog*)pParent->GetComponent( "dlgRankBattle" );
	m_pBtnPrev = (gui::CButton*)pParent->GetComponent( "btnRankBattlePrev" );
	m_pBtnNext = (gui::CButton*)pParent->GetComponent( "btnRankBattleNext" );
	m_pCbbSearchTitle = (gui::CComboBox*)pParent->GetComponent( "cbbSearchTitle" );
	m_pCbbSearchTitle->AddItem( GetDisplayStringManager()->GetString( "DST_RANKBOARD_RANKBATTLE_SUBJECT_RANK" ) );
	m_pCbbSearchTitle->AddItem( GetDisplayStringManager()->GetString( "DST_RANKBOARD_RANKBATTLE_SUBJECT_NAME" ) );
	m_pCbbSearchTitle->SelectItem( m_nSearchMode );
	m_pIpbSearch = (gui::CInputBox*)pParent->GetComponent( "ipbRankBattleSearch" );
	m_pBtnSearch = (gui::CButton*)pParent->GetComponent( "btnRankBattleSearch" );

	m_slotClickedBtnPrev = m_pBtnPrev->SigClicked().Connect( this, &CRankBattleBoard::OnClickedBtnPrev );
	m_slotClickedBtnNext = m_pBtnNext->SigClicked().Connect( this, &CRankBattleBoard::OnClickedBtnNext );
	m_slotClickedBtnSearch = m_pBtnSearch->SigClicked().Connect( this, &CRankBattleBoard::OnClickedBtnSearch );
	m_slotReturnIptSearch = m_pIpbSearch->SigReturnPressed().Connect( this, &CRankBattleBoard::OnInputReturnSearch );

	m_slotIpbSearchGotFocus = m_pIpbSearch->SigGotFocus().Connect( this, &CRankBattleBoard::OnIpbSearchGotFocus );
	m_slotIpbSearchLostFocus = m_pIpbSearch->SigLostFocus().Connect( this, &CRankBattleBoard::OnIpbSearchLostFocus );

	m_slotSearchItemSelect = m_pCbbSearchTitle->SigSelected().Connect( this, &CRankBattleBoard::OnSearchItemSelect );
	m_slotSearchListToggled = m_pCbbSearchTitle->SigListToggled().Connect( this, &CRankBattleBoard::OnSearchListToggled );

	// String
	m_pBtnPrev->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_BOARD_PREV" ) );
	m_pBtnNext->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_BOARD_NEXT" ) );

	// Make Subject
	m_pStbRank = (gui::CStaticBox*)pParent->GetComponent( "stbRankBattleRank" );
	m_pStbRank->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_RANKBATTLE_SUBJECT_RANK" ) );
	m_pStbName = (gui::CStaticBox*)pParent->GetComponent( "stbRankBattleName" );
	m_pStbName->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_RANKBATTLE_SUBJECT_NAME" ) );
	m_pStbLevel = (gui::CStaticBox*)pParent->GetComponent( "stbRankBattleLevel" );
	m_pStbLevel->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_RANKBATTLE_SUBJECT_LEVEL" ) );
	m_pStbClass = (gui::CStaticBox*)pParent->GetComponent( "stbRankBattleClass" );
	m_pStbClass->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_RANKBATTLE_SUBJECT_CLASS" ) );
	m_pStbGuildName = (gui::CStaticBox*)pParent->GetComponent( "stbRankBattleGuildName" );
	m_pStbGuildName->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_RANKBATTLE_SUBJECT_GUILD" ) );
	m_pStbPoint = (gui::CStaticBox*)pParent->GetComponent( "stbRankBattlePoint" );
	m_pStbPoint->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_RANKBATTLE_SUBJECT_POINT" ) );
	m_pStbStraightWin = (gui::CStaticBox*)pParent->GetComponent( "stbRankBattleStraightWin" );
	m_pStbStraightWin->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_RANKBATTLE_SUBJECT_STRAIGHTWIN" ) );

	m_pStbRankBattleCompare = (gui::CStaticBox*)pParent->GetComponent( "stbRankBattleCompare" );
	m_pStbRankBattleCompare->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_RANKBATTLE_SUBJECT_COMPARE" ) );

	/*m_pCbbCompare = (gui::CComboBox*)pParent->GetComponent( "cbbRankBattleCompare" );*/

	// Data
	/*m_pCbbCompare->ClearAllItems();
	m_pCbbCompare->AddItem( GetDisplayStringManager()->GetString( DST_RANKBOARD_RANKBATTLE_SUBJECT_COMPARE_1 ) );
	m_pCbbCompare->AddItem( GetDisplayStringManager()->GetString( DST_RANKBOARD_RANKBATTLE_SUBJECT_COMPARE_2 ) );
	m_pCbbCompare->AddItem( GetDisplayStringManager()->GetString( DST_RANKBOARD_RANKBATTLE_SUBJECT_COMPARE_3 ) );
	m_pCbbCompare->AddItem( GetDisplayStringManager()->GetString( DST_RANKBOARD_RANKBATTLE_SUBJECT_COMPARE_4 ) );
	m_pCbbCompare->AddItem( GetDisplayStringManager()->GetString( DST_RANKBOARD_RANKBATTLE_SUBJECT_COMPARE_5 ) );
	m_pCbbCompare->AddItem( GetDisplayStringManager()->GetString( DST_RANKBOARD_RANKBATTLE_SUBJECT_COMPARE_6 ) );
	m_pCbbCompare->SelectItem( 0 );*/
	m_nCurrentCompareDay = 1;

	// Make Underline
	CRectangle rect;
	for(int i=0; i< dRANKBOARD_RANKBATTLE_UNDERLINE_NUMS; ++i)
	{
		rect.SetRectWH( 8, 13 + (24 * i), dRANKBOARD_RANKBATTLE_UNDERLINE_WIDTH, 1 );
		m_pPanUnderLine[i] = NTL_NEW gui::CPanel( &rect, m_pRankBattleBoardDlg, GetNtlGuiManager()->GetSurfaceManager() );
		m_pPanUnderLine[i]->AddSurface( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "RankingGui.srf", "srfUnderLine" ) );
	}

	// Make Items
	for(int i=0; i< dRANKBOARD_RANKBATTLE_ROWITEM_NUMS; ++i )
		m_RankBattleRowItem[i].Create( m_pRankBattleBoardDlg, 25 + ( 24 * i) );

	/*m_slotItemSelect = m_pCbbCompare->SigSelected().Connect( this, &CRankBattleBoard::OnItemSelect );
	m_slotListToggled = m_pCbbCompare->SigListToggled().Connect( this, &CRankBattleBoard::OnListToggled );
	m_slotClickedCompare = m_pCbbCompare->GetButton()->SigClicked().Connect( this, &CRankBattleBoard::OnClickedCompare );*/

	// Init
	OnSearchItemSelect( m_nSearchMode );
}

/**
* \brief Destroy
*/
void CRankBattleBoard::Destroy() 
{
	for(int i=0; i< dRANKBOARD_RANKBATTLE_ROWITEM_NUMS; ++i )
		m_RankBattleRowItem[i].Destroy();
	
	//m_RankBattleSubject.Destroy();

	for(int i=0; i< dRANKBOARD_RANKBATTLE_UNDERLINE_NUMS; ++i )
		NTL_DELETE( m_pPanUnderLine[i] );
}

/**
* \brief Show
*/
void CRankBattleBoard::Show( RwBool bShow /*= TRUE */ ) 
{
	if( !bShow )
		::ZeroMemory( m_awcSearchName, sizeof(WCHAR) * NTL_MAX_SIZE_CHAR_NAME+1 );

	if( bShow )
		RowItemClear();

	m_pRankBattleBoardDlg->Show( B2b(bShow) );
}

/**
* \brief Enable
*/
void CRankBattleBoard::Enable( RwBool bEnable /*= TRUE */ ) 
{
	//m_pRankBattleBoardDlg->Enable( bEnable );
	//m_RankBattleSubject.EnableComboBox( bEnable );
	/*m_pCbbCompare->GetButton()->ClickEnable( bEnable );*/
	
	m_pCbbSearchTitle->GetButton()->ClickEnable( bEnable );
	
	m_pBtnPrev->ClickEnable( bEnable );
	
	m_pBtnNext->ClickEnable( bEnable );
	m_pBtnSearch->ClickEnable( bEnable );
	m_pIpbSearch->Enable( B2b(bEnable) );

	// ���� �������� 0 �̶�� �׻� ClickEnable( FALSE ) ���°� �ǰ� �Ѵ�.
	if( m_nCurrentPage == 0 )
		m_pBtnPrev->ClickEnable( FALSE );

	if( bEnable )
		ApplyData();
}

/**
* \brief ���� ������ ��û
*/
void CRankBattleBoard::CurrentPage() 
{
	GetDboGlobal()->GetChatPacketGenerator()->SendRankBattle_Rank_List_Req( 
		m_nCurrentPage, 
		(RwInt8)m_nCurrentCompareDay );
}

/**
* \brief ��ũ��Ʋ�� �����Խ����� ���� Msg�� �޾Ƽ� ó���Ѵ�.
* CRankBoardGui���� ���� �� Board�� �ʿ��� �̺�Ʈ�� ��� �����ش�.
* \param msg	Event�� �޽���
*/
void CRankBattleBoard::MessageProc( RWS::CMsg& msg ) 
{
	// ������ ����Ʈ
	if( msg.Id == g_EventRankBattleRankListRes )
	{
		SDboEventRankBattleRankListRes* pRes = 
			reinterpret_cast<SDboEventRankBattleRankListRes*>(msg.pData);

		// ��ũ������ ī��Ʈ�� 0 �̶�� ���� �������� ��û�� ��.
		if( pRes->byRankInfoCount == 0 )
		{
			// ���� 0�������� ī��Ʈ�� �ϳ��� ���ٸ� ������ ��ũ��Ʋ �����Ͱ� ���� ��.
			if( pRes->dwPage == 0 )
			{
				/*GetAlarmManager()->AlarmMessage( DST_RANKBOARD_BOARD_MSGBOX_NODATA );*/
				SetDataResult( eDATA_NONE );
				return;
			}

			/*GetAlarmManager()->AlarmMessage( DST_RANKBOARD_BOARD_MSGBOX_NOTPAGE );*/
			SetDataResult( eDATA_NOTPAGE );
			return;
		}
	
		// get sVARIABLE_DATA
		sVARIABLE_DATA* pData = reinterpret_cast<sVARIABLE_DATA*>(pRes->sData);
		
		// get sRANKBATTLE_RANK_INFO
		sRANKBATTLE_RANK_INFO* apRank = 
			reinterpret_cast<sRANKBATTLE_RANK_INFO*>( pData->Read( pRes->wRankInfo ) );

		// ������ ���� ����
		m_nCurrentPage = pRes->dwPage;
		m_nCurrentCompareDay = pRes->byCompareDay;

		// ������ ����
		m_nRankBattleItemCount = pRes->byRankInfoCount;
		for( int i = 0; i< pRes->byRankInfoCount; ++i )
		{
			m_sRankBattleItem[i].nRank = (pRes->dwPage*10) + i + 1;
			
			// sVARIABLE_DATA���� ĳ���� �̸�
			int nSize = pData->GetSize( apRank[i].wCharName );
			::ZeroMemory( m_sRankBattleItem[i].awcName, sizeof(WCHAR) * NTL_MAX_SIZE_CHAR_NAME+1 );
			::CopyMemory( m_sRankBattleItem[i].awcName, pData->Read( apRank[i].wCharName ), nSize);
			m_sRankBattleItem[i].awcName[ nSize / sizeof(WCHAR) ] = L'\0';

			m_sRankBattleItem[i].nLevel = apRank[i].byLevel;
			m_sRankBattleItem[i].byClass = apRank[i].byClass;
		
			// sVARIABLE_DATA������ ��� �̸�
			nSize = pData->GetSize( apRank[i].wGuildName );
			::ZeroMemory( m_sRankBattleItem[i].awcGuildName, sizeof(WCHAR) * NTL_MAX_SIZE_GUILD_NAME+1 );
			::CopyMemory( m_sRankBattleItem[i].awcGuildName, pData->Read( apRank[i].wGuildName ), nSize );
			m_sRankBattleItem[i].awcGuildName[ nSize / sizeof(WCHAR) ] = L'\0';

			m_sRankBattleItem[i].nPoint = apRank[i].nPoint;
			m_sRankBattleItem[i].wStraightWin = apRank[i].wStraightWinCount;
			m_sRankBattleItem[i].nCompare = apRank[i].dwCompareRank;
		}

		SetDataResult( eDATA_OK );
	}
	// �˻� ��� ����Ʈ
	else if( msg.Id == g_EventRankBattleRankFindCharacterRes )
	{
		SDboEventRankBattleRankFindCharacterRes* pRes = reinterpret_cast<SDboEventRankBattleRankFindCharacterRes*>(msg.pData);
		
		m_nCurrentPage = pRes->dwPage;
		m_nCurrentCompareDay = pRes->byCompareDay;
				
		sVARIABLE_DATA* pData = reinterpret_cast<sVARIABLE_DATA*>(pRes->sData);
		sRANKBATTLE_RANK_INFO*  apRank = reinterpret_cast<sRANKBATTLE_RANK_INFO*>(pData->Read( pRes->wRankInfo ));

		if( apRank == NULL ||
			pRes->byRankInfoCount == 0 )
		{
			SetDataResult( eDATA_NOTFIND );
			return;
		}

		// Search Name
		::ZeroMemory( m_awcSearchName, sizeof(WCHAR) * NTL_MAX_SIZE_CHAR_NAME+1 );
		::CopyMemory( m_awcSearchName, pRes->pwsCharName, sizeof(WCHAR) * wcslen( pRes->pwsCharName ) );

		// Data Loading
		m_nRankBattleItemCount = pRes->byRankInfoCount;
		for( int i = 0; i < pRes->byRankInfoCount; ++i)
		{
			m_sRankBattleItem[i].nRank = (pRes->dwPage*10) + i + 1;

			// sVARIABLE_DATA���� ĳ���� �̸�
			int nSize = pData->GetSize( apRank[i].wCharName );
			::ZeroMemory( m_sRankBattleItem[i].awcName, sizeof(WCHAR) * NTL_MAX_SIZE_CHAR_NAME+1 );
			::CopyMemory( m_sRankBattleItem[i].awcName, pData->Read( apRank[i].wCharName ), nSize);
			m_sRankBattleItem[i].awcName[ nSize / sizeof(WCHAR) ] = L'\0';

			m_sRankBattleItem[i].nLevel = apRank[i].byLevel;
			m_sRankBattleItem[i].byClass = apRank[i].byClass;

			// sVARIABLE_DATA������ ��� �̸�
			nSize = pData->GetSize( apRank[i].wGuildName );
			::ZeroMemory( m_sRankBattleItem[i].awcGuildName, sizeof(WCHAR) * NTL_MAX_SIZE_GUILD_NAME+1 );
			::CopyMemory( m_sRankBattleItem[i].awcGuildName, pData->Read( apRank[i].wGuildName ), nSize );
			m_sRankBattleItem[i].awcGuildName[ nSize / sizeof(WCHAR) ] = L'\0';

			m_sRankBattleItem[i].nPoint = apRank[i].nPoint;
			m_sRankBattleItem[i].wStraightWin = apRank[i].wStraightWinCount;
			m_sRankBattleItem[i].nCompare = apRank[i].dwCompareRank;
		}

		SetDataResult( eDATA_OK );
	}
	// �񱳳�¥ ���� ����Ʈ
	else if( msg.Id == g_EventRankBattleRankCompareDayRes )
	{
		SDboEventRankBattleRankCompareDayRes* pRes = 
		reinterpret_cast<SDboEventRankBattleRankCompareDayRes*>(msg.pData);
		RwBool		bIsFullList = pRes->bIsFullList;		
		sVARIABLE_DATA* pData = reinterpret_cast<sVARIABLE_DATA*>(pRes->sData);

		m_nCurrentPage = pRes->dwPage;
		m_nCurrentCompareDay = pRes->byCompareDay;
	
		// bIsFullList == TRUE : ������ ĳ���� ����� ����Ÿ�� ��� �� �������� ��ü ����Ʈ�� �����´�
		// bIsFullList == FALSE : ������ ĳ���� ����� ����Ÿ�� �־ �񱳵� ��¥�� �����´�.
		if( bIsFullList )
		{
			sRANKBATTLE_RANK_INFO* apRank = reinterpret_cast<sRANKBATTLE_RANK_INFO*>( pData->Read(pRes->wRankInfo) );

			if( apRank == NULL )
			{
				SetDataResult( eDATA_NOTPAGE );
				return;
			}
	

			m_nRankBattleItemCount = pRes->byInfoCount;
			for( int i = 0; i < pRes->byInfoCount; ++i )
			{
				m_sRankBattleItem[i].nRank = (pRes->dwPage*10) + i + 1;

				// sVARIABLE_DATA���� ĳ���� �̸�
				int nSize = pData->GetSize( apRank[i].wCharName );
				::ZeroMemory( m_sRankBattleItem[i].awcName, sizeof(WCHAR) * NTL_MAX_SIZE_CHAR_NAME+1 );
				::CopyMemory( m_sRankBattleItem[i].awcName, pData->Read( apRank[i].wCharName ), nSize);
				m_sRankBattleItem[i].awcName[ nSize / sizeof(WCHAR) ] = L'\0';

				m_sRankBattleItem[i].nLevel = apRank[i].byLevel;
				m_sRankBattleItem[i].byClass = apRank[i].byClass;

				// sVARIABLE_DATA������ ��� �̸�
				nSize = pData->GetSize( apRank[i].wGuildName );
				::ZeroMemory( m_sRankBattleItem[i].awcGuildName, sizeof(WCHAR) * NTL_MAX_SIZE_GUILD_NAME+1 );
				::CopyMemory( m_sRankBattleItem[i].awcGuildName, pData->Read( apRank[i].wGuildName ), nSize );
				m_sRankBattleItem[i].awcGuildName[ nSize / sizeof(WCHAR) ] = L'\0';

				m_sRankBattleItem[i].nPoint = apRank[i].nPoint;
				m_sRankBattleItem[i].wStraightWin = apRank[i].wStraightWinCount;
				m_sRankBattleItem[i].nCompare = apRank[i].dwCompareRank;
			}

			SetDataResult( eDATA_OK );
		}
		else
		{
			DWORD* adwCompareRank = reinterpret_cast<DWORD*>( pData->Read(pRes->wCompareInfo) );

			if( adwCompareRank == NULL )
			{
				SetDataResult( eDATA_NOTPAGE );
				return;
			}
	
			for(int i=0; i<pRes->byInfoCount; ++i )
			{
				m_sRankBattleItem[i].nCompare = adwCompareRank[i];
			}

			SetDataResult( eDATA_ONLYCOMPARE );
		}
	}
}

/**
* \brief UI���� ������ �ִ� ������ �����ϰ� ����Ÿ�� ������� ���� �ȳ� �޽����� ����Ѵ�.
*/
VOID CRankBattleBoard::ApplyData()
{
	switch( m_byDataResult )
	{
		// ����Ÿ�� ���������� ó���Ǿ���.
	case eDATA_OK:
		{
			// ���� �˻� ��忴�� ���
			if( m_bSearchRank )
			{
				m_bSearchRank = FALSE;

				// UI�� ������ �ִ� ������ ���������� �����ۿ� �Է��Ѵ�.
				for( RwInt32 i = 0; i< m_nRankBattleItemCount; ++i )
				{
					RwBool bHighLight = FALSE;
					if( m_nSearchRankIndex == i )
						bHighLight = TRUE;

					m_RankBattleRowItem[i].SetItem( m_sRankBattleItem[i].nRank,
						m_sRankBattleItem[i].awcName,
						m_sRankBattleItem[i].nLevel,
						m_sRankBattleItem[i].byClass,
						m_sRankBattleItem[i].awcGuildName,
						m_sRankBattleItem[i].nPoint,
						m_sRankBattleItem[i].wStraightWin,
						m_sRankBattleItem[i].nCompare,
						bHighLight);

				}

				// ���� ���� ������ �������� �������� �ʴ´�.
				if( m_nRankBattleItemCount < dRANKBOARD_RANKBATTLE_ROWITEM_NUMS )
				{
					for(int i=m_nRankBattleItemCount; i< dRANKBOARD_RANKBATTLE_ROWITEM_NUMS; ++i )
					{
						m_RankBattleRowItem[i].Show( FALSE );
					}
				}
			}
			else
			{
				// UI�� ������ �ִ� ������ ���������� �����ۿ� �Է��Ѵ�.
				for( RwInt32 i = 0; i< m_nRankBattleItemCount; ++i )
				{
					RwBool bHighLight = FALSE;
					if( !wcscmp( m_awcSearchName, m_sRankBattleItem[i].awcName ) )
						bHighLight = TRUE;

					m_RankBattleRowItem[i].SetItem( m_sRankBattleItem[i].nRank,
						m_sRankBattleItem[i].awcName,
						m_sRankBattleItem[i].nLevel,
						m_sRankBattleItem[i].byClass,
						m_sRankBattleItem[i].awcGuildName,
						m_sRankBattleItem[i].nPoint,
						m_sRankBattleItem[i].wStraightWin,
						m_sRankBattleItem[i].nCompare,
						bHighLight);

				}

				// ���� ���� ������ �������� �������� �ʴ´�.
				if( m_nRankBattleItemCount < dRANKBOARD_RANKBATTLE_ROWITEM_NUMS )
				{
					for(int i=m_nRankBattleItemCount; i< dRANKBOARD_RANKBATTLE_ROWITEM_NUMS; ++i )
					{
						m_RankBattleRowItem[i].Show( FALSE );
					}
				}
			}
		}
		break;
		// �񱳳�¥�� �������� ���
	case eDATA_ONLYCOMPARE:
		{
			for( RwInt32 i = 0; i< m_nRankBattleItemCount; ++i )
			{
				m_RankBattleRowItem[i].SetCompareInfo( m_sRankBattleItem[i].nCompare );
			}
		}
		break;
		// ������ �ƹ��� ������ ����.
	case eDATA_NONE:
		{
			if( m_pParentGui->IsShow() )
				GetAlarmManager()->AlarmMessage( "DST_RANKBOARD_BOARD_MSGBOX_NODATA" );
		}
		break;
		// ���� �������Դϴ�.
	case eDATA_NOTPAGE:
		{
			if( m_bSearchRank )
			{
				if( m_pParentGui->IsShow() )
					GetAlarmManager()->AlarmMessage( "DST_RANKBOARD_BOARD_MSGBOX_NODATA" );
				
				m_bSearchRank = FALSE;
			}
			else
			{
				if( m_pParentGui->IsShow() )
					GetAlarmManager()->AlarmMessage( "DST_RANKBOARD_BOARD_MSGBOX_NOTPAGE" );
			}

		}
		break;
		// �˻� ����� �����ϴ�.
	case eDATA_NOTFIND:
		{
			if( m_pParentGui->IsShow() )
				GetAlarmManager()->AlarmMessage( "DST_RANKBOARD_BOARD_MSGBOX_NODATA" );
		}
		break;
	default:
		break;
	}

	
}

/**
* \brief ������ �ʱ�ȭ
*/
VOID CRankBattleBoard::RowItemClear()
{
	for(RwInt32 i = 0; i < dRANKBOARD_RANKBATTLE_ROWITEM_NUMS; ++i )
	{
		m_RankBattleRowItem[i].ClearItem();
	}
}

/**
* \brief �������� ���� ����Ÿ�� ��ȿ�� ����� �����Ѵ�.
* \param byDataResult	(RwUInt8) eDataResult
*/
VOID CRankBattleBoard::SetDataResult( RwUInt8 byDataResult )
{
	m_byDataResult = byDataResult;
}


/**
* \brief '����' ��ư�� Ŭ��
*/
VOID CRankBattleBoard::OnClickedBtnPrev( gui::CComponent* pComponent ) 
{
	if( m_nCurrentPage - 1 < 0 )
	{
		GetAlarmManager()->AlarmMessage( "DST_RANKBOARD_BOARD_MSGBOX_TOPPAGE" );
		return;
	}

	GetDboGlobal()->GetChatPacketGenerator()->SendRankBattle_Rank_List_Req(
		m_nCurrentPage - 1,
		(RwInt8)m_nCurrentCompareDay );
	
	// ��Ȱ��ȭ
	m_pParentGui->DisableAllButton();
}

/**
* \brief '����' ��ư�� Ŭ��
*/
VOID CRankBattleBoard::OnClickedBtnNext( gui::CComponent* pComponent ) 
{
	GetDboGlobal()->GetChatPacketGenerator()->SendRankBattle_Rank_List_Req( 
		m_nCurrentPage + 1, 
		(RwInt8)m_nCurrentCompareDay );

	// ��Ȱ��ȭ
	m_pParentGui->DisableAllButton();
}

/**
* \brief �˻� â���� ���͸� ���� ���
*/
VOID CRankBattleBoard::OnInputReturnSearch() 
{
	if( !m_pParentGui->IsEnableButton() )
		return;

	const WCHAR* pwcText = m_pIpbSearch->GetText();

	// �Է�â�� �� ���� �̻� �ԷµǾ��� ��� ó���Ѵ�.
	if( wcslen(pwcText) > 0 )
	{
		if( (eSearchMode)m_nSearchMode == eSEARCH_NAME )
		{
			GetDboGlobal()->GetChatPacketGenerator()->SendRankBattle_Rank_Find_Character_Req( 
				m_nCurrentPage, 
				(RwInt8)m_nCurrentCompareDay, 
				pwcText );

			m_pParentGui->DisableAllButton();
		}
		else
		{
			RwInt32 nSearchRank = _wtoi( pwcText );
			if( nSearchRank <= 0 )
				return;

			--nSearchRank;

			// �������� ���°������ ã�´�.
			m_nSearchRankPage = 0;
			m_nSearchRankIndex = nSearchRank % 10;
			if( nSearchRank > 10 )
				m_nSearchRankPage = (RwInt32)((RwReal)nSearchRank * 0.1f);

			// �������� ��û
			m_bSearchRank = TRUE;
			GetDboGlobal()->GetChatPacketGenerator()->SendRankBattle_Rank_List_Req( m_nSearchRankPage, (RwInt8)m_nCurrentCompareDay );

			m_pParentGui->DisableAllButton();
		}
	}
	else
	{
		GetAlarmManager()->AlarmMessage( "DST_RANKBOARD_BOARD_MSGBOX_INPUTSEARCH" );
	}
}

/**
* \brief �˻� ��ư�� Ŭ���Ͽ��� ���
*/
VOID CRankBattleBoard::OnClickedBtnSearch( gui::CComponent* pComponent ) 
{
	if( !m_pParentGui->IsEnableButton() )
		return;

	const WCHAR* pwcText = m_pIpbSearch->GetText();

	if( wcslen(pwcText) > 0 )
	{
		if( (eSearchMode)m_nSearchMode == eSEARCH_NAME )
		{
			GetDboGlobal()->GetChatPacketGenerator()->SendRankBattle_Rank_Find_Character_Req( 
				m_nCurrentPage, 
				(RwInt8)m_nCurrentCompareDay, 
				pwcText );

			m_pParentGui->DisableAllButton();
		}
		else
		{
			RwInt32 nSearchRank = _wtoi( pwcText );
			if( nSearchRank <= 0 )
				return;

			--nSearchRank;
			
			// �������� ���°������ ã�´�.
			m_nSearchRankPage = 0;
			m_nSearchRankIndex = nSearchRank % 10;
			if( nSearchRank > 10 )
				m_nSearchRankPage = (RwInt32)((RwReal)nSearchRank * 0.1f);

			// �������� ��û
			m_bSearchRank = TRUE;
			GetDboGlobal()->GetChatPacketGenerator()->SendRankBattle_Rank_List_Req( m_nSearchRankPage, (RwInt8)m_nCurrentCompareDay );
			
			m_pParentGui->DisableAllButton();
		}
	}
	else
	{
		GetAlarmManager()->AlarmMessage( "DST_RANKBOARD_BOARD_MSGBOX_INPUTSEARCH" );
	}
}


/**
* \brief �޺��ڽ��� �������� �����Ͽ��� ���
* \param nIndex		������ Index
*/
VOID CRankBattleBoard::OnItemSelect( INT nIndex ) 
{
	if( m_nCurrentCompareDay == nIndex+1 )
		return;

	GetDboGlobal()->GetChatPacketGenerator()->SendRankBattle_Rank_Compare_Day_Req( m_nCurrentPage, (RwInt8)(nIndex+1) );

	// ��ũ���带 Disable ���·� ��ȯ
	m_pParentGui->DisableAllButton();
}

/**
* \brief �޺��ڽ��� ����Ʈ�ڽ��� ������ ���
* \param bToggled	���¿���
* \param pComponent	���µ� ������Ʈ
*/
VOID CRankBattleBoard::OnListToggled( RwBool bToggled, gui::CComponent* pComponent ) 
{
	if( bToggled )
	{
		pComponent->Raise();
	}
}

VOID CRankBattleBoard::OnClickedCompare( gui::CComponent* pComponent ) 
{
}

VOID CRankBattleBoard::OnSearchItemSelect( INT nIndex )
{
	m_nSearchMode = nIndex;
	m_pIpbSearch->Clear();

	if( m_nSearchMode == eSEARCH_RANK )
	{
		
		m_pIpbSearch->SetNumberOnly( TRUE );
	}
	else
	{
		m_pIpbSearch->SetNumberOnly( FALSE );
	}
}

VOID CRankBattleBoard::OnSearchListToggled( RwBool bToggled, gui::CComponent* pComponent )
{
	if( bToggled )
	{
		pComponent->Raise();
	}
}

VOID CRankBattleBoard::OnIpbSearchGotFocus()
{
	GetDboGlobal()->GetGameData()->bChatMode = TRUE;
}

VOID CRankBattleBoard::OnIpbSearchLostFocus()
{
	GetDboGlobal()->GetGameData()->bChatMode = FALSE;
}