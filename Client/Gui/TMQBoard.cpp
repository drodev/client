#include "precomp_dboclient.h"
#include "TMQBoard.h"

// core
#include "NtlDebug.h"
#include "NtlPLDef.h"

// shared
#include "Table.h"
#include "TimeQuestTable.h"
#include "NtlRankBattle.h"
#include "QuestTextDataTable.h"

// simulation
#include "DboEvent.h"
#include "NtlSoundManager.h"
#include "GUISoundDefine.h"

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

/**
* \brief Construction
*/
CTMQPartyListItem::CTMQPartyListItem()
: m_pTMQBoard(NULL)
, m_pDlgPartyListItem(NULL)
, m_pStbPartyName(NULL)
, m_pStbClearTime(NULL)
{
	
}

/**
* \brief Destruction
*/
CTMQPartyListItem::~CTMQPartyListItem()
{

}

/**
* \brief Create
* \param pBoard		(CTMQBoard*) ������ GUI�� �θ�� ������ CBoard*
* \param pParentGui	(gui::CComponent*) CTMQPartyListItem�� ������ �ִ� Dialog�� �θ� Component
* \param byIndex	(RwUInt8) ��Ƽ ����Ʈ�� �ε��� ( ���� �Ǵ� ���� )
* \param nTop		(RwInt32) ��Ƽ ����Ʈ�� ������ Dialog�� Y ��ǥ
*/
VOID CTMQPartyListItem::Create( CTMQBoard* pBoard, gui::CComponent* pParentGui, RwUInt8 byIndex, RwInt32 nTop )
{
	// TMQ Board�� �����Ϳ� �ε����� �����ϰ� �ִ´�.
	m_pTMQBoard = pBoard;
	m_byIndex = byIndex;

	CRectangle rect;

	// Dialog
	rect.SetRectWH( 13, nTop, 316, dRANKBOARD_TMQ_PARTYTIEM_HEIGHT );
	m_pDlgPartyListItem = NTL_NEW gui::CDialog( &rect, pParentGui, GetNtlGuiManager()->GetSurfaceManager() );

	// ��Ƽ �̸�
	rect.SetRectWH( 57, 6, 125, 20 );
	m_pStbPartyName = NTL_NEW gui::CStaticBox( &rect, m_pDlgPartyListItem, GetNtlGuiManager()->GetSurfaceManager(),
		COMP_TEXT_VERTICAL_CENTER | COMP_TEXT_CENTER );
	m_pStbPartyName->CreateFontStd( DETAIL_FONT, dRANKBOARD_TMQ_PARTYITEM_FONT_HEIGHT, 0 );

	// Ŭ���� �ð�
	rect.SetRectWH( 184, 6, 107, 20 );
	m_pStbClearTime = NTL_NEW gui::CStaticBox( &rect, m_pDlgPartyListItem, GetNtlGuiManager()->GetSurfaceManager(),
		COMP_TEXT_VERTICAL_CENTER | COMP_TEXT_CENTER );
	m_pStbClearTime->CreateFontStd( DETAIL_FONT, dRANKBOARD_TMQ_PARTYITEM_FONT_HEIGHT, 0 );

	// ����
	rect.SetRectWH( 0, 33, 316, 1 );
	m_pPanUnderLine = NTL_NEW gui::CPanel( &rect, m_pDlgPartyListItem, GetNtlGuiManager()->GetSurfaceManager() );

	if( dRANKBOARD_TMQ_PARTYITEM_NUMS-1 != byIndex )
		m_pPanUnderLine->AddSurface( GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "RankingGui.srf", "srfTMQUnderLine" ) );

	// 
	m_slotMouseUp = m_pDlgPartyListItem->SigMouseUp().Connect( this, &CTMQPartyListItem::OnMouseUp );

	Enable( TRUE );
}

/**
* \brief Destroy
*/
VOID CTMQPartyListItem::Destroy()
{
	NTL_DELETE( m_pPanUnderLine );
	NTL_DELETE( m_pStbPartyName );
	NTL_DELETE( m_pStbClearTime );
	NTL_DELETE( m_pDlgPartyListItem );
}

/**
* \brief ��Ƽ ����Ʈ �׸��� �����Ѵ�.
* \param nRank			(RwInt32) ����
* \param pwcPartyName	(const WCHAR*) ��Ƽ �̸�
* \param uiClearTime	(RwUInt32) Ŭ���� ���
*/
VOID CTMQPartyListItem::SetItem( RwInt32 nRank, const WCHAR* pwcPartyName, RwUInt32 uiClearTime )
{
	m_pStbPartyName->SetText( pwcPartyName );

	// ClearTime�� ms ����
	RwReal fSec = (RwReal)uiClearTime / 1000.f;

	// �Ϸ簡 �Ѿ�� ������ String�� ����Ѵ�.
	RwUInt32 uiDay = (RwUInt32)(fSec / 86400.f);
	if( uiDay > 0 )
		m_pStbClearTime->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_TMQ_OVER_TIME" ) );
	else
		m_pStbClearTime->SetText( Logic_GetTimeString( fSec ) );
}

/**
* \brief �������� �ʱ�ȭ�Ѵ�.
*/
VOID CTMQPartyListItem::ClearItem()
{
	m_pStbPartyName->SetText(L"---");
	m_pStbClearTime->SetText(L"---");
}

/**
* \brief bEnable �������� ��Ȱ/Ȱ��ȭ ��Ų��. �������� ��Ȱ��ȭ�� �Ǹ� ���콺 UP�� ó������ �ʴ´�.
* \param bEnable	(RwBool) ����
*/
VOID CTMQPartyListItem::Enable( RwBool bEnable )
{
	m_bEnable = bEnable;
	m_pDlgPartyListItem->Enable( B2b(bEnable) );
	m_pStbPartyName->Enable( false );
	m_pStbClearTime->Enable( false );
}

/**
* \brief ���콺�� UP�� �޴´�.
* \param key	(CKey&) ���콺 ������ ����ü
*/
VOID CTMQPartyListItem::OnMouseUp( const CKey& key )
{
	// ������ ���ٸ� Mouse Up�� ó������ �ʴ´�.
	if( !m_pStbPartyName->GetText().compare( L"---" ) )
		return;

	if( m_bEnable )
		m_pTMQBoard->SelectMemberList( m_byIndex );
}

/**
* \brief Construction
*/
CTMQPartyMemberItem::CTMQPartyMemberItem()
: m_pDlgPartyMemberItem(NULL)
, m_pStbPartyMemberName(NULL)
, m_pStbLevel(NULL)
, m_pPanClass(NULL)
, m_byClass(255)
{
	
}

/**
* \brief Destruction
*/
CTMQPartyMemberItem::~CTMQPartyMemberItem()
{

}

/**
* \brief ��Ƽ ��� ����Ʈ�� ������Ʈ���� �������� �����Ѵ�.
* \param pParentGui	(gui::CComponent*) �θ��� GUI
* \param nTop		(RwInt32) ���� �������� Y ���� ��ġ
*/
VOID CTMQPartyMemberItem::Create( gui::CComponent* pParentGui, RwInt32 nTop )
{
	CRectangle rect;

	rect.SetRectWH( 362, nTop, 240, 17 );
	m_pDlgPartyMemberItem = NTL_NEW gui::CDialog( &rect, pParentGui, GetNtlGuiManager()->GetSurfaceManager() );

	rect.SetRectWH( 12, 0, 126, 17 );
	m_pStbPartyMemberName = NTL_NEW gui::CStaticBox( &rect, m_pDlgPartyMemberItem, GetNtlGuiManager()->GetSurfaceManager(),
		COMP_TEXT_VERTICAL_CENTER | COMP_TEXT_CENTER );
	m_pStbPartyMemberName->CreateFontStd( DETAIL_FONT, dRANKBOARD_TMQ_PARTYMEMBERITEM_FONT_HEIGHT, 0 );

	rect.SetRectWH( 142, 0, 28, 17 );
	m_pStbLevel = NTL_NEW gui::CStaticBox( &rect, m_pDlgPartyMemberItem, GetNtlGuiManager()->GetSurfaceManager(),
		COMP_TEXT_VERTICAL_CENTER | COMP_TEXT_CENTER );
	m_pStbLevel->CreateFontStd( DETAIL_FONT, dRANKBOARD_TMQ_PARTYMEMBERITEM_FONT_HEIGHT, 0 );

	rect.SetRectWH( 203, 0, 19, 17 );
	m_pPanClass = NTL_NEW gui::CPanel( &rect, m_pDlgPartyMemberItem, GetNtlGuiManager()->GetSurfaceManager() );
}

/**
* \brief Destroy
*/
VOID CTMQPartyMemberItem::Destroy()
{
	NTL_DELETE( m_pStbPartyMemberName );
	NTL_DELETE( m_pStbLevel );
	NTL_DELETE( m_pPanClass );
	NTL_DELETE( m_pDlgPartyMemberItem );
}

/**
* \brief ��� �������� ����Ÿ�� �����Ѵ�.
* \param pwcMemberName	(const WCHAR*) ��Ƽ ����� �̸�
* \param nLevel			(RwInt32) ����
* \param byClass		(RwUInt8) Ŭ����
*/
VOID CTMQPartyMemberItem::SetItem( const WCHAR* pwcMemberName, RwInt32 nLevel, RwUInt8 byClass )
{
	m_pStbPartyMemberName->SetText( pwcMemberName );
	m_pStbLevel->SetText( nLevel );
	
	// ToolTip �� Class�� Icon�� �޾��ش�.
	m_pPanClass->DeleteToolTip();
	m_pPanClass->GetSurface()->clear();
	m_pPanClass->AddSurface( Logic_GetPCClassIconSurface( byClass, FALSE ) );
	m_pPanClass->SetToolTip( Logic_GetClassName(byClass) );

	m_byClass = byClass;
}

/**
* \brief �������� �ʱ�ȭ�Ѵ�.
*/
VOID CTMQPartyMemberItem::ClearItem()
{
	m_pStbPartyMemberName->SetText( L"---" );
	m_pStbLevel->SetText( L"---" );
	m_pPanClass->GetSurface()->clear();
}

/**
* \brief Construction
*/
CTMQBoard::CTMQBoard()
: m_pTMQBoardDlg(NULL)
, m_pParentGui(NULL)
{
	m_nCurrentDifficulty = TIMEQUEST_DIFFICULTY_EASY;
	m_nCurrentScenario = 0;

	m_byDataResult = eDATA_NONE;
	m_byTeamCount = 0;
	m_byMemberCount = 0;

	ZeroMemory( m_sTeamRankData, sizeof(sTIMEQUEST_TEAM_RANK_DATA) * dRANKBOARD_TMQ_PARTYITEM_NUMS );
	ZeroMemory( m_sMemberData, sizeof(sTIMEQUEST_PARTY_MEMBER_DATA) * dRANKBOARD_TMQ_PARTYMEMBERITEM_NUMS );
}

/**
* \brief Destruction
*/
CTMQBoard::~CTMQBoard()
{

}

/**
* \brief TMQ Board�� �����Ѵ�.
* \param eType		(eBoardType) ������ Ÿ��
* \param pParentGui	(CRankBoardGui*) ��ŷ ������ ������
*/
void CTMQBoard::Create( eBoardType eType, CRankBoardGui* pParentGui )
{
	m_pParentGui = pParentGui;

	// UI
	m_pTMQBoardDlg = (gui::CDialog*)pParentGui->GetComponent( "dlgTMQ" );
	m_pBtnPrev = (gui::CButton*)pParentGui->GetComponent( "btnTMQPrev" );
	m_pBtnNext = (gui::CButton*)pParentGui->GetComponent( "btnTMQNext" );
	/*m_pStbTMQTitle = (gui::CStaticBox*)pParentGui->GetComponent( "stbTMQTitle" );*/
	m_pCbbTitle = (gui::CComboBox*)pParentGui->GetComponent( "cbbTMQScenarioList" );
	m_pStbTMQRank = (gui::CStaticBox*)pParentGui->GetComponent( "stbTMQRank" );
	m_pStbTMQPartyName = (gui::CStaticBox*)pParentGui->GetComponent( "stbTMQPartyName" );
	m_pStbTMQClearTime = (gui::CStaticBox*)pParentGui->GetComponent( "stbTMQClearTime" );
	m_pStbPartyMemberInfo = (gui::CStaticBox*)pParentGui->GetComponent( "stbPartyMemberInfo" );
	m_pStbPartyMember = (gui::CStaticBox*)pParentGui->GetComponent( "stbPartyMember" );
	m_pStbPartyLevel = (gui::CStaticBox*)pParentGui->GetComponent( "stbPartyLevel" );
	m_pStbPartyClass = (gui::CStaticBox*)pParentGui->GetComponent( "stbPartyClass" );
	/*m_pCbbTMQScenarioList = (gui::CComboBox*)pParentGui->GetComponent( "cbbTMQScenarioList" );*/
	m_pPanTMQHighLight = (gui::CPanel*)pParentGui->GetComponent( "panTMQHighLight" );
	m_pBtnNormal = (gui::CButton*)pParentGui->GetComponent("btnTMQNormal");
	m_pBtnHard = (gui::CButton*)pParentGui->GetComponent("btnTMQHard");
	
	m_pBtnPrev->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_BOARD_PREV" ) );
	m_pBtnNext->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_BOARD_NEXT" ) );
	m_pStbTMQRank->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_TMQ_SUBJECT_RANK" ) );
	m_pStbTMQPartyName->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_TMQ_SUBJECT_PARTYNAME" ) );
	m_pStbTMQClearTime->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_TMQ_SUBJECT_CLEARTIME" ) );
	m_pStbPartyMemberInfo->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_TMQ_SUBJECT_PARTYMEMBERINFO" ) );
	m_pStbPartyMember->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_TMQ_SUBJECT_PARTYMEMBER" ) );
	m_pStbPartyLevel->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_TMQ_SUBJECT_LEVEL" ) );
	m_pStbPartyClass->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_TMQ_SUBJECT_CLASS" ) );
	
	// Data
	m_pCbbTitle->ClearAllItems();
	m_slotClickedBtnPrev = m_pBtnPrev->SigClicked().Connect( this, &CTMQBoard::OnClickedBtnPrev );
	m_slotClickedBtnNext = m_pBtnNext->SigClicked().Connect( this, &CTMQBoard::OnClickedBtnNext );
	m_slotClickedBtnNormal = m_pBtnNormal->SigClicked().Connect( this, &CTMQBoard::OnClickedBtnNormal);
	m_slotClickedBtnHard = m_pBtnHard->SigClicked().Connect( this, &CTMQBoard::OnClickedBtnHard );
	m_slotOnItemSelect = m_pCbbTitle->SigSelected().Connect( this, &CTMQBoard::OnItemSelect );
	m_slotListToggled = m_pCbbTitle->SigListToggled().Connect( this, &CTMQBoard::OnListToggled );

	// ��Ƽ ����Ʈ�� �����Ѵ�.
	for( RwUInt8 i = 0; i< dRANKBOARD_TMQ_PARTYITEM_NUMS; ++i )
		m_itemPartyList[i].Create( this, m_pTMQBoardDlg, i, (63) + (dRANKBOARD_TMQ_PARTYTIEM_HEIGHT*i));

	// ��� ����Ʈ�� �����Ѵ�.
	for( RwUInt8 i = 0; i< dRANKBOARD_TMQ_PARTYMEMBERITEM_NUMS; ++i )
		m_itemPartyMember[i].Create( m_pTMQBoardDlg, (106) + (30*i) );

	CTimeQuestTable* pTMQTable = API_GetTableContainer()->GetTimeQuestTable();	

	CTable::TABLEIT itTable = pTMQTable->Begin();
	RwUInt8 byCount = 1;
	
	while( itTable != pTMQTable->End() )
	{
		sTIMEQUEST_TBLDAT* pTIMEQUEST_TABLE = (sTIMEQUEST_TBLDAT*)((*itTable).second);	
		if( pTIMEQUEST_TABLE->byTimeQuestType == TIMEQUEST_TYPE_PARTY ||
			pTIMEQUEST_TABLE->byTimeQuestType == TIMEQUEST_TYPE_GROUP )
		{
			CQuestTextDataTable* pQuestTextTable = API_GetTableContainer()->GetQuestTextDataTable();
			sTIMEQUEST_DATASET* pTIMEQUEST_DATASET = &pTIMEQUEST_TABLE->sTimeQuestDataset[TIMEQUEST_DIFFICULTY_EASY];
			sQUEST_TEXT_DATA_TBLDAT* pQUEST_TEXT_DATA_TBLDAT = reinterpret_cast<sQUEST_TEXT_DATA_TBLDAT*>( pQuestTextTable->FindData( pTIMEQUEST_DATASET->nameTblidx ) );
			if( !pQUEST_TEXT_DATA_TBLDAT )
			{
				DBO_FAIL( "QuestTextDataTbl Data is null" );
				return;
			}

			std::wstring& wstrText = gui::GetHtmlFromMemoryString(pQUEST_TEXT_DATA_TBLDAT->wstrText.c_str(), pQUEST_TEXT_DATA_TBLDAT->wstrText.size());
			m_pCbbTitle->AddItem( wstrText.c_str() );
			m_vecTblIdx.push_back( (*itTable).first );
			++byCount;
		}
			
		++itTable;
	}

	m_pCbbTitle->SelectItem( 0 );
	SetDifficultButton( TIMEQUEST_DIFFICULTY_EASY );
}

/**
* \brief TMQ Board���� ������ �����۵��� �����Ѵ�.
*/
void CTMQBoard::Destroy()
{
	for( RwInt32 i = 0; i< dRANKBOARD_TMQ_PARTYITEM_NUMS; ++i )
		m_itemPartyList[i].Destroy();

	for( RwInt32 i = 0; i< dRANKBOARD_TMQ_PARTYMEMBERITEM_NUMS; ++i )
		m_itemPartyMember[i].Destroy();
}

/**
* \brief ���� ���尡 ������ �ִ� Dialog�� Show ���� ����
* \param bShow	(RwBool) TRUE : ����, FALSE : ������ ����
*/
void CTMQBoard::Show( RwBool bShow /*= TRUE */ )
{
	m_pTMQBoardDlg->Show( B2b(bShow) );
	if( bShow )
		m_pPanTMQHighLight->Show( false );
}

/**
* \brief ���� ������ Ȱ��ȭ ���� ����
* \param bEnable	(RwBool) TRUE : Ȱ��ȭ   FALSE : ��Ȱ��ȭ
*/
void CTMQBoard::Enable( RwBool bEnable /*= TRUE */ )
{
	m_pCbbTitle->Enable(B2b(bEnable) );
	m_pCbbTitle->GetButton()->ClickEnable( bEnable );

	
	m_pBtnPrev->ClickEnable( bEnable );
	m_pBtnNext->ClickEnable( bEnable );

	for(RwInt32 i = 0; i< dRANKBOARD_TMQ_PARTYITEM_NUMS; ++i )
		m_itemPartyList[i].Enable( bEnable );

	if( m_nCurrentScenario == 0 )
		m_pBtnPrev->ClickEnable( FALSE );
	else if( m_nCurrentScenario+1 == (RwInt32)m_vecTblIdx.size() )
		m_pBtnNext->ClickEnable( FALSE );
	
	if( bEnable )
		ApplyData();
}

/**
* \brief �̺�Ƽ ó�� �Լ�
* \param msg	(RWS::CMsg*) �̺�Ʈ ����ü
*/
void CTMQBoard::MessageProc( RWS::CMsg& msg )
{
	// TMQ ����� ����Ʈ�� �޴´�.
	if( msg.Id == g_EventTMQRecordListRes )
	{
		SDboEventTMQRecordListRes* pResult = reinterpret_cast<SDboEventTMQRecordListRes*>(msg.pData);

		// ���̵�
		SetDifficultButton( pResult->byDifficult );

		sTIMEQUEST_TEAM_RANK_DATA* pTeamData = reinterpret_cast<sTIMEQUEST_TEAM_RANK_DATA*>( pResult->paTeam );

		// ù��°(Best) ClearTime�� 0�̶�� ����Ÿ�� ����
		if( pTeamData[0].dwClearTime == 0 )
		{
			SetDataResult( eDATA_NONE );
			
			// Select �� 0���� ���ش�.
			CRectangle rect = m_itemPartyList[0].GetScreenRect();
			CRectangle DialogRect = m_pTMQBoardDlg->GetScreenRect();

			m_pPanTMQHighLight->SetPosition( rect-DialogRect );
			m_pPanTMQHighLight->Show( false );
			m_pParentGui->DisableAllButton();
			return;
		}

		// �����͸� GUI���� �����Ѵ�.
		m_byTeamCount = pResult->byTeamCount;
		for( RwInt32 i = 0; i< pResult->byTeamCount; ++i )
		{
			m_sTeamRankData[i].dwClearTime = pTeamData[i].dwClearTime;
			m_sTeamRankData[i].byMode = pTeamData[i].byMode;
			memcpy( m_sTeamRankData[i].wszPartyName,
				pTeamData[i].wszPartyName,
				sizeof(WCHAR) * NTL_MAX_SIZE_PARTY_NAME );
		}

		// ����� ���������� �޾����� 0 ��° ��� ����Ʈ�� ��û�Ѵ�.
		SelectMemberList( 0 );

		//// ���������� �����͸� �޾Ҵ�.
		//SetDataResult( eDATA_OK );
	}
	// MEMBER LIST�� �޴´�.
	else if( msg.Id == g_EventTMQMemberListRes )
	{
		SDboEventTMQMemberListRes* pResult = reinterpret_cast<SDboEventTMQMemberListRes*>(msg.pData);

		sTIMEQUEST_TEAM_MEMBER_DATA* pTeamData = reinterpret_cast<sTIMEQUEST_TEAM_MEMBER_DATA*>( pResult->pTeam );
		sTIMEQUEST_PARTY_MEMBER_DATA* pMemberData = pTeamData->asMember;
		
		if( pTeamData->byMemberCount <= 0 )
		{
			SetDataResult( eDATA_NOMEMBER );
			return;
		}

		m_byMemberCount = pTeamData->byMemberCount;
		for( RwInt32 i = 0; i< pTeamData->byMemberCount; ++i )
		{
			m_sMemberData[i].byLevel = pMemberData[i].byLevel;
			m_sMemberData[i].byClass = pMemberData[i].byClass;
			memcpy( m_sMemberData[i].wszName,
				pMemberData[i].wszName,
				sizeof(WCHAR) * NTL_MAX_SIZE_CHAR_NAME );
		}

		SetDataResult( eDATA_OK );
	}
}

/**
* \brief ���� �������� ��û�Ѵ�.
*/
void CTMQBoard::CurrentPage()
{
	if( m_nCurrentScenario >= (RwInt32)m_vecTblIdx.size() || m_nCurrentScenario < 0 )
		return;
	
	// ���� ������ ��û
	GetDboGlobal()->GetChatPacketGenerator()->SendTMQ_Record_List_Req( m_vecTblIdx[m_nCurrentScenario], m_nCurrentDifficulty );
	ClearPartyList();
	m_pCbbTitle->SelectItem( m_nCurrentScenario );
	
	// Best�� ��� ����Ʈ�� ��û
	/*SelectMemberList( 0 );*/
}

/**
* \brief ��Ƽ ����Ʈ�� �ʱ�ȭ�Ѵ�.
*/
VOID CTMQBoard::ClearPartyList()
{
	for(RwInt32 i = 0; i< dRANKBOARD_TMQ_PARTYITEM_NUMS; ++i)
		m_itemPartyList[i].ClearItem();
}

/**
* \brief ��� ����Ʈ�� �ʱ�ȭ�Ѵ�.
*/
VOID CTMQBoard::ClearMemberList()
{
	for(RwInt32 i = 0; i< dRANKBOARD_TMQ_PARTYMEMBERITEM_NUMS; ++i)
		m_itemPartyMember[i].ClearItem();
}

/**
* \brief ��� ����Ʈ�� ��û�Ѵ�.
* \param byPartyIndex	(RwUInt8) ���� ��Ƽ�� �ε��� ��ȣ ( ex : 0, 1, 2, ... , 6)
*/
VOID CTMQBoard::SelectMemberList( RwUInt8 byPartyIndex )
{
	// � �������� �����ߴ���
	CRectangle rect = m_itemPartyList[byPartyIndex].GetScreenRect();
	CRectangle DialogRect = m_pTMQBoardDlg->GetScreenRect();

	m_pPanTMQHighLight->SetPosition( rect-DialogRect );
	m_pPanTMQHighLight->Show( true );

	GetDboGlobal()->GetChatPacketGenerator()->SendTMQ_Member_List_Req( m_vecTblIdx[m_nCurrentScenario], m_nCurrentDifficulty, byPartyIndex );
	
	// Disable
	ClearMemberList();
	m_pParentGui->DisableAllButton();
}

/**
* \brief ���� TMQ �ó������� ���̵��� �����Ѵ�.
* \param byDifficult	(RwUInt8) ���̵� ���
*/
VOID CTMQBoard::SelectDifficult( RwUInt8 byDifficult )
{
	m_nCurrentDifficulty = byDifficult;
	CurrentPage();
}

/**
* \brief ������ ���̵��� ��ư�� ������ ���̵� ��ư�� Ȱ��ȭ ��Ų��.
* \param byDifficult	(RwUInt8) ���̵� ���
*/
VOID CTMQBoard::SetDifficultButton( RwUInt8 byDifficult )
{
	switch( byDifficult )
	{
	case TIMEQUEST_DIFFICULTY_EASY:
		m_pBtnNormal->ClickEnable( FALSE );
		m_pBtnHard->ClickEnable( TRUE );
		break;
	case TIMEQUEST_DIFFICULTY_NORMAL:
		m_pBtnNormal->ClickEnable( FALSE );
		m_pBtnHard->ClickEnable( TRUE );
		break;
	case TIMEQUEST_DIFFICULTY_HARD:
		m_pBtnNormal->ClickEnable( TRUE );
		m_pBtnHard->ClickEnable( FALSE );
		break;
	default:
		break;
	}
}

/**
* \brief �������� ������ �������� ��ȿ���� ����Ѵ�.
* \param byDataResult	(RwUInt8) eDataResult
*/
VOID CTMQBoard::SetDataResult( RwUInt8 byDataResult )
{
	m_byDataResult = byDataResult;
}

/**
* \brief ������ �ִ� �����͸� �����Ѵ�. ���� ��ȿ���� ���� ����Ÿ��� �ǴܵǸ� �˸��� �ȳ� �޽����� ����Ѵ�.
*/
VOID CTMQBoard::ApplyData()
{
	ClearPartyList();
	ClearMemberList();

	// Ȱ��ȭ �Ǿ��� ��� ó��
	switch( m_byDataResult )
	{
	case eDATA_OK:
		{
			for(int i=0; i< m_byTeamCount; ++i )
				m_itemPartyList[i].SetItem( i, m_sTeamRankData[i].wszPartyName, m_sTeamRankData[i].dwClearTime );

			for(int i=0; i< m_byMemberCount; ++i )
				m_itemPartyMember[i].SetItem( m_sMemberData[i].wszName, m_sMemberData[i].byLevel, m_sMemberData[i].byClass );
		}
		break;
	case eDATA_NONE:
		{
			if( m_pParentGui->IsShow() )
				GetAlarmManager()->AlarmMessage( "DST_RANKBOARD_BOARD_MSGBOX_NODATA" );
		}
		break;
	case eDATA_NOMEMBER:
		{
			if( m_pParentGui->IsShow() )
				GetAlarmManager()->AlarmMessage( "DST_RANKBOARD_BOARD_MSGBOX_NOTMEMBER" );
		}
		break;
	default:
		break;
	}
}

/**
* \brief ���� ��ư�� Ŭ���ϸ� �� �ܰ� ������ �ó������� �����Ѵ�.
* \param pComponent		(gui::CComponent*) Ŭ���� ������Ʈ
*/
VOID CTMQBoard::OnClickedBtnPrev( gui::CComponent* pComponent )
{
	// Prev
	if( m_nCurrentScenario <= 0 )
	{
		GetAlarmManager()->AlarmMessage( "DST_RANKBOARD_BOARD_MSGBOX_NONESCENARIO" );
		return;
	}

	--m_nCurrentScenario;
	CurrentPage();
}

/**
* \brief ���� ��ư�� Ŭ���ϸ� �� �ܰ� ������ �ó������� �����Ѵ�.
* \param pComponent		(gui::CCOmponent*) Ŭ���� ������Ʈ
*/
VOID CTMQBoard::OnClickedBtnNext( gui::CComponent* pComponent )
{
	// Next
	if( m_nCurrentScenario >= (RwInt32)m_vecTblIdx.size() )
	{
		// ���� �ó������Դϴ�.
		GetAlarmManager()->AlarmMessage( "DST_RANKBOARD_BOARD_MSGBOX_NONESCENARIO" );
		return;
	}
	
	++m_nCurrentScenario;
	CurrentPage();
}

/**
* \brief ����Ʈ �ڽ��� ����Ͽ��� ��
* \param bToggled	(RwBool) ����� ����
* \param pComponent	(gui::CComponent*) ��۵� ����Ʈ�ڽ��� ������Ʈ
*/
VOID CTMQBoard::OnListToggled( RwBool bToggled, gui::CComponent* pComponent )
{
	// �������� �ִٸ� �ٸ� gui�� �������� �ʰ� Raise() �����ش�.
	if( bToggled )
	{
		pComponent->Raise();
	}
}

/**
* \brief Easy ��ư�� Ŭ���Ͽ��� ��
*/
VOID CTMQBoard::OnClickedBtnEasy( gui::CComponent* pComponent )
{
	if( m_pParentGui->IsEnableButton() )
		SelectDifficult( TIMEQUEST_DIFFICULTY_EASY );
}

/**
* \brief Normal ��ư�� Ŭ���Ͽ��� ��
*/
VOID CTMQBoard::OnClickedBtnNormal( gui::CComponent* pComponent )
{
	if( m_pParentGui->IsEnableButton() )
		SelectDifficult( TIMEQUEST_DIFFICULTY_EASY );
}

/**
* \brief Hard ��ư�� Ŭ���Ͽ��� ���
*/
VOID CTMQBoard::OnClickedBtnHard( gui::CComponent* pComponent )
{
	if( m_pParentGui->IsEnableButton() )
		SelectDifficult( TIMEQUEST_DIFFICULTY_HARD );
}

/**
* \brief ����Ʈ���� �ó������� �������� ���
*/
VOID CTMQBoard::OnItemSelect( RwInt32 nIndex )
{
	// Next
	if( nIndex >= (RwInt32)m_vecTblIdx.size() )
	{
		// ���� �ó������Դϴ�.
		GetAlarmManager()->AlarmMessage( "DST_RANKBOARD_BOARD_MSGBOX_NONESCENARIO" );
		return;
	}

	m_nCurrentScenario = nIndex;
	CurrentPage();
}
