#include "precomp_dboclient.h"
#include "RankBoardGui.h"

// core
#include "NtlDebug.h"
#include "NtlPLDef.h"

// shared
#include "NtlResultCode.h"
#include "NtlTimeQuest.h "
#include "NtlRankBattle.h"
#include "NtlSharedType.h"

// simulation
#include "InputActionMap.h"
#include "GUISoundDefine.h"
#include "NtlSoundManager.h"

// presentation
#include "NtlPLGuiManager.h"
#include "NtlPLEvent.h"

// Dbo
#include "DboEvent.h"
#include "DboEventGenerator.h"
#include "DboGlobal.h"
#include "DboLogic.h"
#include "DialogManager.h"
#include "DisplayStringManager.h"
#include "AlarmManager.h"

// RankBoard
#include "RankBattleBoard.h"
#include "TMQBoard.h"

/**
* \brief ������
*/
CRankBoardGui::CRankBoardGui( const RwChar* pName ) 
: CNtlPLGui( pName )
{
	for(int i=0; i< eBOARD_NUMS; ++i )
	{
		m_pBoard[i] = NULL;
	}
	m_eCurrentBoard = eBOARD_RANKBATTLE;

	m_pBtnClose = NULL;
	m_pCbbTitle = NULL;
	m_pStbDataLoading = NULL;

	m_slotClickedBtnClose = NULL;
	m_slotToggledTitle = NULL;

	m_fElapsedTime = 0.0f;
	m_bEnableButton = TRUE;
}

/**
* \brief �Ҹ���
*/
CRankBoardGui::~CRankBoardGui() 
{
	
}

/**
* \brief Create
*/
RwBool CRankBoardGui::Create() 
{
	NTL_FUNCTION("CRankBoardGui::Create");

	if( !CNtlPLGui::Create("", "gui\\RankingGui.srf" , "gui\\RankingGui.frm" ) )
		NTL_RETURN( FALSE );

	CNtlPLGui::CreateComponents(CNtlPLGuiManager::GetInstance()->GetGuiManager());

	// Get Component
	m_pThis = (gui::CDialog*)GetComponent( "dlgMain" );
	m_pstbTitle = (gui::CStaticBox*)GetComponent("sttTitle");
	m_pstbTitle->SetText(GetDisplayStringManager()->GetString("DST_RANKBOARD_TITLE"));
	m_pBtnClose = (gui::CButton*)GetComponent( "btnClose" );
	m_pCbbTitle = (gui::CComboBox*)GetComponent( "cbbTitle" );
	m_pStbDataLoading = (gui::CStaticBox*)GetComponent( "stbDataLoading" );
	m_pStbDataLoading->SetText( GetDisplayStringManager()->GetString( "DST_RANKBOARD_BOARD_DATALOADING" ) );
		
	// Signal
	m_slotClickedBtnClose = m_pBtnClose->SigClicked().Connect( this, &CRankBoardGui::OnClickedBtnClose );
	m_slotToggledTitle = m_pCbbTitle->SigListToggled().Connect( this, &CRankBoardGui::OnListToggledCbbTitle );
	m_slotClickedBtnTitle = m_pCbbTitle->GetButton()->SigClicked().Connect( this, &CRankBoardGui::OnClickedBtnTitle );
	m_slotSelectBoard = m_pCbbTitle->SigSelected().Connect( this, &CRankBoardGui::OnSelectBoard );

	// ComboBox
	m_pCbbTitle->ClearAllItems();
	m_pCbbTitle->AddItem( GetDisplayStringManager()->GetString( "DST_RANKBOARD_BOARD_TITLE_PVP" ) );
	m_pCbbTitle->SelectItem( 0 );

	// Show
	Show( FALSE );

	// �Խ��� ����
	m_pBoard[eBOARD_RANKBATTLE] = NTL_NEW CRankBattleBoard;
	m_pBoard[eBOARD_RANKBATTLE]->Create( eBOARD_RANKBATTLE, this );

	/*m_pBoard[eBOARD_TMQ] = NTL_NEW CTMQBoard;
	m_pBoard[eBOARD_TMQ]->Create( eBOARD_TMQ, this );*/

	// Link
	LinkMsg( g_EventRankBattleRankListRes, 0 );
	LinkMsg( g_EventRankBattleRankFindCharacterRes, 0 );
	LinkMsg( g_EventRankBattleRankCompareDayRes, 0 );
	LinkMsg( g_EventRankBoardDisable, 0 );

	LinkMsg( g_EventTMQRecordListRes, 0 );
	LinkMsg( g_EventTMQMemberListRes, 0 );
	

	NTL_RETURN(TRUE);
}

/**
* \brief Destroy
*/
VOID CRankBoardGui::Destroy() 
{
	NTL_FUNCTION("CRankBoardGui::Destroy");

	if( m_pBoard[eBOARD_RANKBATTLE] )
	{
		m_pBoard[eBOARD_RANKBATTLE]->Destroy();
		NTL_DELETE( m_pBoard[eBOARD_RANKBATTLE] );
	}

	/*if( m_pBoard[eBOARD_TMQ] )
	{
		m_pBoard[eBOARD_TMQ]->Destroy();
		NTL_DELETE( m_pBoard[eBOARD_TMQ] );
	}*/

	// UnLink
	UnLinkMsg( g_EventRankBattleRankListRes );
	UnLinkMsg( g_EventRankBattleRankFindCharacterRes );
	UnLinkMsg( g_EventRankBattleRankCompareDayRes );
	UnLinkMsg( g_EventRankBoardDisable );

	UnLinkMsg( g_EventTMQRecordListRes );
	UnLinkMsg( g_EventTMQMemberListRes );

	CNtlPLGui::DestroyComponents();
	CNtlPLGui::Destroy(); 

	NTL_RETURNVOID();
}

/**
* \brief HandleEvents
*/
VOID CRankBoardGui::HandleEvents( RWS::CMsg &msg ) 
{
	NTL_FUNCTION("CRankBoardGui::HandleEvents");

	// RankBattle Board
	if( msg.Id == g_EventRankBattleRankListRes ||
		msg.Id == g_EventRankBattleRankFindCharacterRes ||
		msg.Id == g_EventRankBattleRankCompareDayRes )
	{
		m_pBoard[eBOARD_RANKBATTLE]->MessageProc( msg );
	}
	if( msg.Id == g_EventTMQRecordListRes ||
		msg.Id == g_EventTMQMemberListRes )
	{
		//m_pBoard[eBOARD_TMQ]->MessageProc( msg );
	}
	// ��ũ���带 Disable���·� ��ȯ�Ѵ�.
	else if( msg.Id == g_EventRankBoardDisable )
	{
		DisableAllButton();
	}

	NTL_RETURNVOID();
}

/**
* \brief SwitchDialog
*/
RwInt32 CRankBoardGui::SwitchDialog( bool bOpen ) 
{
	if( bOpen == TRUE )
	{
		// ��ư�� Ȱ��ȭ�� ���¶�� ���� �������� ��û�Ѵ�. (�ƴ϶�� ��û���� �ʴ´�)
		if( m_bEnableButton )
		{
			m_pBoard[m_eCurrentBoard]->CurrentPage();
			DisableAllButton();
		}

		m_pThis->Show( TRUE );

		for(int i=0; i < eBOARD_NUMS; ++i )
		{
			if( i == m_eCurrentBoard )
				m_pBoard[i]->Show( TRUE );
			else
				m_pBoard[i]->Show( FALSE );
		}
		
		// Data Loading
		m_pStbDataLoading->Show( !m_bEnableButton );
	}
	else
	{
		m_pThis->Show( FALSE );
		
	}

	return 1;
}

/**
* \brief Button�� enable �������� Ȯ��
*/
RwBool CRankBoardGui::IsEnableButton()
{
	return m_bEnableButton;
}

/**
* \brief ��� Board�� Enable ��Ų��.
*/
VOID CRankBoardGui::EnableAllButton() 
{
	// ��� Board�� Enable TRUE
	//for( int i=0; i<eBOARD_NUMS; ++i)
	//	m_pBoard[i]->Enable( TRUE );

	m_pBoard[m_eCurrentBoard]->Enable( TRUE );

	m_pCbbTitle->Enable( TRUE );
	m_pCbbTitle->GetButton()->ClickEnable( TRUE );

	m_pStbDataLoading->Show( FALSE );
	
	m_bEnableButton = TRUE;

	GetNtlGuiManager()->RemoveUpdateFunc( this );
	
}

/**
* \brief ��� Board�� Diable ��Ų��.
*/
VOID CRankBoardGui::DisableAllButton() 
{
	// ��� Board�� Enable TRUE
	/*for( int i=0; i<eBOARD_NUMS; ++i)
		m_pBoard[i]->Enable( FALSE );*/

	m_pBoard[m_eCurrentBoard]->Enable( FALSE );

	m_pCbbTitle->Enable( FALSE );
	m_pCbbTitle->GetButton()->ClickEnable( FALSE );
	
	m_fElapsedTime = dRANKBOARD_COMMON_ENABLE_IDLE;		// 3��
	m_bEnableButton = FALSE;	// ��ư ��Ȱ��ȭ ���

	m_pStbDataLoading->Show( TRUE );

	//GetAlarmManager()->AlarmMessage( DST_RANKBOARD_BOARD_DATALOADING );

	GetNtlGuiManager()->AddUpdateFunc( this );
}

VOID CRankBoardGui::Update( RwReal fElapsed ) 
{
	// ��ư�� ��Ȱ��ȭ �����
	if( m_bEnableButton == FALSE )
	{
		// ��� �ð��� ���ְ�
		m_fElapsedTime -= fElapsed;

		if( m_fElapsedTime < 0.0f )
		{
			// Ȱ��ȭ
			EnableAllButton();
		}
	}
}


/**
* \brief �ݱ� ��ư�� Ŭ��
*/
VOID CRankBoardGui::OnClickedBtnClose( gui::CComponent* pComponent ) 
{
	if( !Logic_CanMouseInput_in_Tutorial( ETL_MOUSE_INPUT_TYPE_RANKBOARD_WND_CLOSE_BTN ) )
		return;

	GetDialogManager()->CloseDialog( DIALOG_RANKBOARD );
}

/**
* \brief �޺��ڽ��� ������ ����Ʈ�ڽ��� ������ ���� ��
*/
VOID CRankBoardGui::OnListToggledCbbTitle( RwBool bToggled, gui::CComponent* pComponent ) 
{
	if ( bToggled )
	{
		pComponent->Raise();
	}
}

/**
* \brief Ÿ��Ʋ ��ư�� Ŭ���Ͽ��� ��� ( �޺��ڽ��� Button )
*/
VOID CRankBoardGui::OnClickedBtnTitle( gui::CComponent* pComponent ) 
{
	
}

/**
* \brief �޺��ڽ��� �����Ͽ��� �� ������� �ݹ�
* \param nIndex	(RwInt32) �������� �ε���
*/
VOID CRankBoardGui::OnSelectBoard( RwInt32 nIndex )
{
	for( RwInt32 i=0; i<eBOARD_NUMS; ++i )
	{
		if( nIndex == i )
		{
			m_eCurrentBoard = (eBoardType)nIndex;
			m_pBoard[i]->Show(TRUE);

			if( m_bEnableButton )
			{
				m_pBoard[i]->CurrentPage();

				if( m_eCurrentBoard == eBOARD_RANKBATTLE )
					DisableAllButton();
			}
		}
		else
		{
			m_pBoard[i]->Show(FALSE);
		}
	}
}
