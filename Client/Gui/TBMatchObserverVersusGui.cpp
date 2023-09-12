#include "precomp_dboclient.h"
#include "TBMatchObserverVersusGui.h"

// Core
#include "NtlDebug.h"

// Presentation
#include "NtlPLGuiManager.h"

// Simulation
#include "NtlWorldConcept.h"
#include "NtlWorldConceptTB.h"
#include "NtlSLEvent.h"
#include "NtlSLLogic.h"

// Dbo
#include "DboGlobal.h"

/**
* \brief Construction
* \param pName	(const RwChar*) GUI �̸�
*/
CTBMatchObserverVersusGui::CTBMatchObserverVersusGui( const RwChar* pName )
: CNtlPLGui( pName )
{
	m_byType = TYPE_INDI;
	m_bTimeOn = FALSE;
}

/**
* \brief Destruction
*/
CTBMatchObserverVersusGui::~CTBMatchObserverVersusGui()
{

}


/**
* \brief Create
* õ������ ����ȸ ������ �Ǵ� ������ ������ Versus�� �����Ѵ�.
*/
RwBool CTBMatchObserverVersusGui::Create()
{
	NTL_FUNCTION("CTBMatchObserverVersusGui::Create");

	if( !CNtlPLGui::Create("gui\\Observer.rsr", "gui\\TBMatchObserverVersusGui.srf", "gui\\TBMatchObserverVersusGui.frm") )
		NTL_RETURN( FALSE );

	CNtlPLGui::CreateComponents(CNtlPLGuiManager::GetInstance()->GetGuiManager());

	m_pThis				= (gui::CDialog*)GetComponent("dlgMain");
	m_pPnlRedPanel		= (gui::CPanel*)GetComponent("pnlRedPanel");
	m_pPnlBluePanel		= (gui::CPanel*)GetComponent("pnlBluePanel");
	m_pStbRedTeam		= (gui::CStaticBox*)GetComponent("stbRedTeam");
	m_pStbBlueTeam		= (gui::CStaticBox*)GetComponent("stbBlueTeam");
	m_pPnlScore			= (gui::CPanel*)GetComponent("pnlScore");

	// Create Number
	CreateRedScoreNumber();
	CreateBlueScoreNumber();
	CreateLeftTimeNumber();

	m_slotMove			= m_pThis->SigMove().Connect( this, &CTBMatchObserverVersusGui::OnMove );
	m_slotPaint			= m_pPnlScore->SigPaint().Connect( this, &CTBMatchObserverVersusGui::OnPaint );

	LinkMsg( g_EventMajorMatchStateUpdate, 0 );
	LinkMsg( g_EventFinalMatchStateUpdate, 0 );
	LinkMsg( g_EventMajorMatchStageFinish, 0 );
	LinkMsg( g_EventFinalMatchStageFinish, 0 );

	// Add Update
	GetNtlGuiManager()->AddUpdateFunc( this );

	Show( false );

	NTL_RETURN(TRUE);
}

/**
* \brief �������� ������ ���� ���ڸ� �����Ѵ�.
*/
VOID CTBMatchObserverVersusGui::CreateRedScoreNumber()
{
	m_numRedScore.Create( ND_CENTER, NVD_CENTER, 0 );
	m_numRedScore.SetSurface( 0, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_0" ) );
	m_numRedScore.SetSurface( 1, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_1" ) );
	m_numRedScore.SetSurface( 2, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_2" ) );
	m_numRedScore.SetSurface( 3, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_3" ) );
	m_numRedScore.SetSurface( 4, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_4" ) );
	m_numRedScore.SetSurface( 5, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_5" ) );
	m_numRedScore.SetSurface( 6, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_6" ) );
	m_numRedScore.SetSurface( 7, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_7" ) );
	m_numRedScore.SetSurface( 8, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_8" ) );
	m_numRedScore.SetSurface( 9, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_9" ) );	
	
	CRectangle rect = m_pThis->GetScreenRect();
	m_numRedScore.SetParentPos( rect.left, rect.top );
	m_numRedScore.SetPosition( 187, 29 );
}

/**
* \brief ������� ������ ���� ���ڸ� �����Ѵ�.
*/
VOID CTBMatchObserverVersusGui::CreateBlueScoreNumber()
{
	m_numBlueScore.Create( ND_CENTER, NVD_CENTER, 0 );
	m_numBlueScore.SetSurface( 0, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_0" ) );
	m_numBlueScore.SetSurface( 1, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_1" ) );
	m_numBlueScore.SetSurface( 2, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_2" ) );
	m_numBlueScore.SetSurface( 3, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_3" ) );
	m_numBlueScore.SetSurface( 4, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_4" ) );
	m_numBlueScore.SetSurface( 5, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_5" ) );
	m_numBlueScore.SetSurface( 6, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_6" ) );
	m_numBlueScore.SetSurface( 7, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_7" ) );
	m_numBlueScore.SetSurface( 8, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_8" ) );
	m_numBlueScore.SetSurface( 9, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN9_9" ) );	

	CRectangle rect = m_pThis->GetScreenRect();
	m_numBlueScore.SetParentPos( rect.left, rect.top );
	m_numBlueScore.SetPosition( 326, 29 );
}

/**
* \brief TIME�� ���� ���ڸ� �����Ѵ�.
*/
VOID CTBMatchObserverVersusGui::CreateLeftTimeNumber()
{
	m_numLeftTime.Create( ND_CENTER, NVD_CENTER, 0 );
	m_numLeftTime.SetSurface( 0, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN8_0" ) );
	m_numLeftTime.SetSurface( 1, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN8_1" ) );
	m_numLeftTime.SetSurface( 2, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN8_2" ) );
	m_numLeftTime.SetSurface( 3, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN8_3" ) );
	m_numLeftTime.SetSurface( 4, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN8_4" ) );
	m_numLeftTime.SetSurface( 5, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN8_5" ) );
	m_numLeftTime.SetSurface( 6, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN8_6" ) );
	m_numLeftTime.SetSurface( 7, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN8_7" ) );
	m_numLeftTime.SetSurface( 8, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN8_8" ) );
	m_numLeftTime.SetSurface( 9, GetNtlGuiManager()->GetSurfaceManager()->GetSurface( "CommonNumber2.srf", "srfN8_9" ) );	
	m_numLeftTime.SetColorOnly( 255, 64, 2 );

	CRectangle rect = m_pThis->GetScreenRect();
	m_numLeftTime.SetParentPos( rect.left, rect.top );
	m_numLeftTime.SetPosition( 253, 80 );
}

/**
* \brief Destroy
*/
VOID CTBMatchObserverVersusGui::Destroy()
{
	NTL_FUNCTION("CTBMatchObserverVersusGui::Destroy");

	// Remove Update
	GetNtlGuiManager()->RemoveUpdateFunc( this );

	UnLinkMsg( g_EventMajorMatchStateUpdate );
	UnLinkMsg( g_EventFinalMatchStateUpdate );
	UnLinkMsg( g_EventMajorMatchStageFinish );
	UnLinkMsg( g_EventFinalMatchStageFinish );

	CNtlPLGui::DestroyComponents();
	CNtlPLGui::Destroy();

	NTL_RETURNVOID();
}

/**
* \brief Update
* \param fElapsed	(RwReal) ���� �����ӿ��� ����� �ð�
*/
VOID CTBMatchObserverVersusGui::Update( RwReal fElapsed )
{
	if( m_bTimeOn )
	{
		m_fTime -= fElapsed;
		if( m_fTime < -1.0f )
		{
			m_fTime = 0.0f;
			m_bTimeOn = FALSE;
		}

		if( m_numLeftTime.GetNumber() != (RwInt64)m_fTime )
		{
			m_numLeftTime.SetNumber( (RwInt64)m_fTime );
		}
	}
}

/**
* \brief HandleEvents
* \param msg		(RWS::CMsg&) Event �޽��� ����ü
*/
VOID CTBMatchObserverVersusGui::HandleEvents( RWS::CMsg& msg )
{
	if( msg.Id == g_EventMajorMatchStateUpdate )
	{
		SNtlEventMajorMatchStateUpdate* pData = reinterpret_cast<SNtlEventMajorMatchStateUpdate*>( msg.pData );

		if( pData->bEnterState )
		{
			// Match Ready ���¶�� ������ �ʱ�ȭ�����ش�.
			if( pData->byMatchState == BUDOKAI_MAJORMATCH_STATE_MATCH_READY )
			{
				SetScore( 0, 0 );
				return;
			}

			// READY, RUN, FINISH ���°� �ƴ϶�� �����Ѵ�.
			if( pData->byMatchState == BUDOKAI_MAJORMATCH_STATE_STAGE_READY ||
				pData->byMatchState == BUDOKAI_MAJORMATCH_STATE_STAGE_RUN	||
				pData->byMatchState == BUDOKAI_MAJORMATCH_STATE_STAGE_FINISH )
			{
				if( !IsShow() )
				{
					// �����ڶ�� ����
					CNtlWorldConceptTB*	pTBWorldConcept = reinterpret_cast<CNtlWorldConceptTB*>( GetNtlWorldConcept()->GetWorldConceptController( WORLD_PLAY_T_BUDOKAI ) );
					stTBudokaiMember* pMember = pTBWorldConcept->FindMember( Logic_GetAvatarHandle() );
					if( pMember )
						return;

					Show( true );

					SetVersusType();
					SetInterfaceByType( m_byType );
					SetAdjustPosition();
					/*SetCurrentScore();*/
				}

				if( pData->byMatchState == BUDOKAI_MAJORMATCH_STATE_STAGE_RUN )
				{
					SetTimer( TRUE, (RwReal)pData->dwRemainTime );
				}
			}
			else
			{
				if( IsShow() )
					Show( false );
			}
		}		
	}
	else if( msg.Id == g_EventFinalMatchStateUpdate )
	{
		SNtlEventFinalMatchStateUpdate* pData = reinterpret_cast<SNtlEventFinalMatchStateUpdate*>( msg.pData );

		if( pData->bEnterState )
		{
			// Match Ready ���¶�� ������ �ʱ�ȭ�����ش�.
			if( pData->byMatchState == BUDOKAI_MAJORMATCH_STATE_MATCH_READY )
			{
				SetScore( 0, 0 );
				return;
			}

			if( pData->byMatchState == BUDOKAI_FINALMATCH_STATE_STAGE_READY ||
				pData->byMatchState == BUDOKAI_FINALMATCH_STATE_STAGE_RUN	||
				pData->byMatchState == BUDOKAI_FINALMATCH_STATE_STAGE_FINISH )
			{
				if( !IsShow() )
				{
					// �����ڶ�� ����
					CNtlWorldConceptTB*	pTBWorldConcept = reinterpret_cast<CNtlWorldConceptTB*>( GetNtlWorldConcept()->GetWorldConceptController( WORLD_PLAY_T_BUDOKAI ) );
					stTBudokaiMember* pMember = pTBWorldConcept->FindMember( Logic_GetAvatarHandle() );
					if( pMember )
						return;

					Show( true );

					SetVersusType();
					SetInterfaceByType( m_byType );
					SetAdjustPosition();
					/*SetCurrentScore();*/

				}

				if( pData->byMatchState == BUDOKAI_MAJORMATCH_STATE_STAGE_RUN )
				{
					SetTimer( TRUE, (RwReal)pData->dwRemainTime );
				}
			}
			else
			{
				if( IsShow() )
					Show( false );
			}
		}		
	}
	else if( msg.Id == g_EventMajorMatchUpdateScore ||
		msg.Id == g_EventFinalMatchUpdateScore )
	{
		/*SetCurrentScore();*/
	}
	else if( msg.Id == g_EventMajorMatchStageFinish )
	{
		SNtlEventMajorMatchStageFinish* pData = reinterpret_cast< SNtlEventMajorMatchStageFinish* >(msg.pData);

		SetScore( pData->pStageScore->byTeam2, pData->pStageScore->byTeam1 );
	}
	else if( msg.Id == g_EventFinalMatchStageFinish )
	{
		SNtlEventMajorMatchStageFinish* pData = reinterpret_cast< SNtlEventMajorMatchStageFinish* >(msg.pData);

		SetScore( pData->pStageScore->byTeam2, pData->pStageScore->byTeam1 );
	}
}

/**
* \brief ���� VS GUI�� Ÿ���� �����Ѵ�.
*/
VOID CTBMatchObserverVersusGui::SetVersusType()
{
	CNtlWorldConceptTB* pTBWorldConcept = reinterpret_cast<CNtlWorldConceptTB*>( GetNtlWorldConcept()->GetWorldConceptController( WORLD_PLAY_T_BUDOKAI ) );
	DBO_ASSERT( pTBWorldConcept, "CTBMatchObserverVersusGui : must World concept is valid" );

	// ������
	if( !pTBWorldConcept->IsPartyBattle() )
	{
		m_byType = TYPE_INDI;
	}
	// ����
	else
	{
		m_byType = TYPE_TEAM;
	}
}

/**
* \brief Ÿ�Կ� ���� Interface�� �����Ѵ�.
* \param byType		(RwUInt8) Interface Type
*/
VOID CTBMatchObserverVersusGui::SetInterfaceByType( RwUInt8 byType )
{
	switch( byType )
	{
	case TYPE_INDI:
		{
			m_pPnlRedPanel->Show( false );
			m_pStbRedTeam->Show( false );
			m_pPnlBluePanel->Show( false );
			m_pStbBlueTeam->Show( false );
		}
		break;
	case TYPE_TEAM:
		{
			// Red �� �̸� ����
			// Blue �� �̸� ����
			CNtlWorldConceptTB* pTBWorldConcept = reinterpret_cast<CNtlWorldConceptTB*>( GetNtlWorldConcept()->GetWorldConceptController( WORLD_PLAY_T_BUDOKAI ) );
			DBO_ASSERT( pTBWorldConcept, "CTBMatchObserverVersusGui : must World concept is valid" );		

			// ������ Red
			stTBudokaiTeam* pRedTeam = pTBWorldConcept->GetRedTeam();
			DBO_ASSERT( pRedTeam, "CTBMatchObserverVersusGui : must Budokai red team is valid" );

			m_pStbRedTeam->SetText( pRedTeam->wstrTeamName.c_str() );

			stTBudokaiTeam* pBlueTeam = pTBWorldConcept->GetBlueTeam();
			DBO_ASSERT( pBlueTeam, "CTBMatchObserverVersusGui : must Budokai Blue team is valid" );

			m_pStbBlueTeam->SetText( pBlueTeam->wstrTeamName.c_str() );
		}
		break;
	default:
		{
			DBO_FAIL( "CTBMatchObserverVersusGui : Interface type is exist" );
		break;
		}
	}
}

VOID CTBMatchObserverVersusGui::SetAdjustPosition()
{
	CRectangle rect = m_pThis->GetScreenRect();
	RwInt32 nNewPosX = (GetDboGlobal()->GetScreenWidth()/2) - (rect.GetWidth()/2);
	SetPosition( nNewPosX, 0 );
}

VOID CTBMatchObserverVersusGui::SetCurrentScore()
{
	CNtlWorldConceptTB* pTBWorldConcept = reinterpret_cast<CNtlWorldConceptTB*>( GetNtlWorldConcept()->GetWorldConceptController( WORLD_PLAY_T_BUDOKAI ) );
	DBO_ASSERT( pTBWorldConcept, "CTBMatchObserverVersusGui : must World concept is valid" );	

	SetScore( pTBWorldConcept->GetRedTeam()->byTeamScore, pTBWorldConcept->GetBlueTeam()->byTeamScore );
}

/**
* \brief ������ �����Ѵ�.
*/
VOID CTBMatchObserverVersusGui::SetScore( RwUInt8 byRedScore, RwUInt8 byBlueScore )
{
	m_numRedScore.SetNumber( byRedScore );
	m_numBlueScore.SetNumber( byBlueScore );
}
/**
* \brief �ð��� �����Ѵ�.
*/
VOID CTBMatchObserverVersusGui::SetTime( RwUInt32 nTime )
{
	m_numLeftTime.SetNumber( nTime );
}

VOID CTBMatchObserverVersusGui::SetTimer( RwBool bPlay, RwReal fTime )
{
	if( bPlay )
	{
		m_bTimeOn = TRUE;
		m_fTime = fTime / 1000.0f;
	}
	else
	{
		m_bTimeOn = FALSE;
		m_fTime = 0.0f;
	}
}

VOID CTBMatchObserverVersusGui::OnPaint()
{
	m_numRedScore.Render();
	m_numBlueScore.Render();

	if( m_bTimeOn )
		m_numLeftTime.Render();
}

VOID CTBMatchObserverVersusGui::OnMove( RwInt32 nOldX, RwInt32 nOldY )
{
	CRectangle rtScreen = m_pThis->GetScreenRect();

	m_numRedScore.SetParentPos( rtScreen.left, rtScreen.top );
	m_numBlueScore.SetParentPos( rtScreen.left, rtScreen.top );
	m_numLeftTime.SetParentPos( rtScreen.left, rtScreen.top );
}

