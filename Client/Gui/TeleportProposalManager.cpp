#include "precomp_dboclient.h"
#include "TeleportProposalManager.h"

// Core
#include "NtlDebug.h"

// Shared
#include "NtlResultCode.h"
#include "NtlTeleport.h"
#include "NtlBudokai.h"
#include "WorldMapTable.h"


// Framework
#include "NtlStage.h"

// Simulation
#include "NtlSobAvatar.h"
#include "NtlSLGLobal.h"

// Sound
#include "GUISoundDefine.h"

// DBO ( Client )
#include "DboDef.h"
#include "DboEvent.h"
#include "AlarmManager.h"
#include "StageManager.h"
#include "DboPacketGenerator.h"
#include "DboGlobal.h"

CTeleportProposalManager* CTeleportProposalManager::m_pInstance = NULL;

CTeleportProposalManager::CTeleportProposalManager()
: m_fElapsedTime(0.0f)
{

}

CTeleportProposalManager::~CTeleportProposalManager()
{

}

/**
* \brief Create
* TeleportProposalManager�� Event�� �����Ѵ�.
*/
RwBool CTeleportProposalManager::Create()
{
	// LinkEvent
	LinkMsg( g_EventTeleportProposalNfy, 0 );
	LinkMsg( g_EventTeleportConfirmRes, 0 );
	LinkMsg( g_EventMsgBoxResult, 0 );
	LinkMsg( g_EventUpdateTick, 0 );

	m_mapEventFunc[g_EventTeleportProposalNfy.Get_pEventId()]	= &CTeleportProposalManager::HandleTeleportProposalNfy;
	m_mapEventFunc[g_EventTeleportConfirmRes.Get_pEventId()]	= &CTeleportProposalManager::HandleTeleportConfirmRes;
	m_mapEventFunc[g_EventMsgBoxResult.Get_pEventId()]			= &CTeleportProposalManager::HandleMsgBoxResult;
	m_mapEventFunc[g_EventUpdateTick.Get_pEventId()]			= &CTeleportProposalManager::HandleUpdateTick;

	return TRUE;
}

/**
* \brief Destroy
* Link�� event���� �����Ѵ�.
*/
VOID CTeleportProposalManager::Destroy()
{
	for each( std::pair< BYTE, STeleportProposal* > proposal in m_mapTeleportProposal )
	{
		STeleportProposal* pProposal = (proposal.second);
		NTL_DELETE( pProposal );
		
	}
	m_mapTeleportProposal.clear();
	m_mapEventFunc.clear();

	// UnLinkEvent
	UnLinkMsg( g_EventTeleportProposalNfy );
	UnLinkMsg( g_EventTeleportConfirmRes );
	UnLinkMsg( g_EventMsgBoxResult );
	UnLinkMsg( g_EventUpdateTick );
}

/**
* \brief HandleEvents
* \param msg			(RWS::CMsg&) Event message class
* Link�Ǿ� �ִ� Events �� �˸��� �Լ��� �������ش�.
*/
void CTeleportProposalManager::HandleEvents( RWS::CMsg& msg )
{
	MapFuncEventHandler::iterator it = m_mapEventFunc.find( msg.Id );
	if( it != m_mapEventFunc.end() )
	{
		(this->*(*it).second)(msg);
	}
}

/**
* \brief Update
* \param fElapsed		(RwReal) ���� �����ӿ��� ����� �ð�
*/
void CTeleportProposalManager::Update( RwReal fElapsed )
{
	m_fElapsedTime += fElapsed;

	// �ʴ� �ѹ� ������Ʈ �Ѵ�.
	if( m_fElapsedTime > 1.0f )
	{
		m_fElapsedTime -= 1.0f;

		for each( std::pair< BYTE, STeleportProposal* > proposal in m_mapTeleportProposal )
		{
			STeleportProposal* pProposal = (proposal.second);

			if( pProposal->dataNotify.wWaitTime > 0 )
				pProposal->dataNotify.wWaitTime--;

			// Proposal ���� �ʾҾ��ٸ� Proposal �� ����ش�.
			if( !pProposal->bProposal )
			{
				if( IsGameStage() && IsAvatar() )
				{
					DBO_WARNING_MESSAGE("pProposal->dataNotify.wWaitTime: " << pProposal->dataNotify.wWaitTime);
					SendTeleportProposal( pProposal );
				}
			}
		}
	}
}

/**
* \brief TeleportProposalNfy�� �����Ѵ�.
* �������� ������ ��û�� �ڷ���Ʈ Proposal�� ���� ���� ���� �ٰ����� �����ϰ� ���� ������ ó���Ѵ�.
*/
void CTeleportProposalManager::HandleTeleportProposalNfy( RWS::CMsg& msg )
{
	SDboEventTeleportProposalNfy* pNotify = reinterpret_cast<SDboEventTeleportProposalNfy*>(msg.pData);

	// Proposal �� �������� �ʴ´ٸ� �߰��ϰ� ���� ���¸� �˻��Ͽ� Proposal�� ������.
	MapTeleportProposal::iterator it = m_mapTeleportProposal.find( pNotify->byInfoIndex );
	if( it == m_mapTeleportProposal.end() )
	{
		STeleportProposal* pProposal = NTL_NEW STeleportProposal();
		memcpy( &pProposal->dataNotify, pNotify, sizeof( SDboEventTeleportProposalNfy ) );
		m_mapTeleportProposal.insert( std::make_pair( pNotify->byInfoIndex, pProposal ) );

		// ���� �����̰� �ƹ�Ÿ�� �����Ѵٸ� Proposal �Ѵ�.
		if( IsGameStage() && IsAvatar() )
			SendTeleportProposal( pProposal );
	}
	else
	{
		// �ִٸ� ����Ǿ� �ִ� �ε����� ����� ���ο� �����ͷ� ä���ִ´�.
		STeleportProposal* pProposal = (*it).second;
		NTL_DELETE( pProposal );
		m_mapTeleportProposal.erase( it );

		pProposal = NTL_NEW STeleportProposal();
		memcpy( &pProposal->dataNotify, pNotify, sizeof( SDboEventTeleportProposalNfy ) );
		m_mapTeleportProposal.insert( std::make_pair( pNotify->byInfoIndex, pProposal ) );

		// ���� �����̰� �ƹ�Ÿ�� �����Ѵٸ� Proposal �Ѵ�.
		if( IsGameStage() && IsAvatar() )
			SendTeleportProposal( pProposal );
	}
}

/**
* \brief TeleportConfirmRes�� �����Ѵ�.
* ����ڰ� ������ TeleportConfirmReq�� ������ �޾Ƽ� �ڷ���Ʈ �޽����� �ٽ� ����شٰų� �����ϴ� ó���� �Ѵ�.
*/
void CTeleportProposalManager::HandleTeleportConfirmRes( RWS::CMsg& msg )
{
	SDboEventTeleportConfirmRes* pResult = reinterpret_cast<SDboEventTeleportConfirmRes*>(msg.pData);

	// ������ �ƴ϶�� ResultCode ��� ��
	if( pResult->wResultCode != GAME_SUCCESS )
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, ""), TRUE );

	// ���� �ִ� Index�� ã�´�.
	MapTeleportProposal::iterator it = m_mapTeleportProposal.find( pResult->byTeleportIndex );
	if( it != m_mapTeleportProposal.end() )
	{
		STeleportProposal* pProposal = (*it).second;

		// ������ �� Interface�� ã�´�.
		if( pProposal->bProposal )
		{
			// ResultCode���� bClearInterface�� ������ �ٽ� �� ������ �ƴ����� �����Ѵ�.
			if( pResult->bClearInterface )
			{
				// �����ش�.
				NTL_DELETE( pProposal );
				m_mapTeleportProposal.erase( it );
			}
			else
			{
				if( pProposal->dataNotify.wWaitTime != 0 )
				{
					SendTeleportProposal( pProposal );
				}
			}
		}
	}
}

/**
* \brief MsgBoxResult�� ó���Ѵ�.
* MessageBox���� ���� WorkID�� ������� ó���Ѵ�.
*/
void CTeleportProposalManager::HandleMsgBoxResult( RWS::CMsg& msg )
{
	// MessageBox result
	SDboEventMsgBoxResult* pResult = reinterpret_cast< SDboEventMsgBoxResult* >( msg.pData );

	if (pResult->strID == "DST_TELEPORT_COMMON_CONFIRM_MSG")
	{
		if (_wcsicmp(pResult->pData->pwcText, L"DST_TELEPORT_COMMON_CONFIRM_YES_BTN") == 0)
		{
			GetDboGlobal()->GetGamePacketGenerator()->SendTeleportConfirmReq(true, pResult->pData->byIndex);
		}
		else
		{
			STeleportProposal* pProposal = GetTeleportProposal(pResult->pData->byIndex);
			if( pProposal )
				SendTeleportProposal( pProposal, TRUE );
		}
	}
	else if (pResult->strID == "DST_TELEPORT_FINAL_CONFIRM_MSG")
	{
		if (_wcsicmp(pResult->pData->pwcText, L"DST_TELEPORT_FINAL_CONFIRM_YES_BTN") == 0)
		{
			GetDboGlobal()->GetGamePacketGenerator()->SendTeleportConfirmReq(false, pResult->pData->byIndex);
		}
		else
		{
			STeleportProposal* pProposal = GetTeleportProposal(pResult->pData->byIndex);
			if (pProposal)
				SendTeleportProposal(pProposal, FALSE);
		}
	}
}

void CTeleportProposalManager::HandleUpdateTick( RWS::CMsg& msg )
{
	float fElapsed = *reinterpret_cast<float*>(msg.pData);

	Update( fElapsed );
}

void CTeleportProposalManager::SendTeleportProposal( STeleportProposal* pProposal, RwBool bFinalConfirm /*= FALSE */ )
{
	if( pProposal->dataNotify.byTeleportType == TELEPORT_TYPE_DOJO)
	{
		CNtlSLEventGenerator::DojoEvent(DOJO_EVENT_SCRAMBLE_TELEPORT_PROPOSAL, pProposal->dataNotify.byInfoIndex);
		return;
	}

	if( !pProposal->bProposal )
	{
		sNtlSoundPlayParameta tSoundParam;
		tSoundParam.iChannelGroup	= CHANNEL_GROUP_JINGLE_MUSIC_WITHOUT_FADE;
		tSoundParam.pcFileName		= GSD_TB_TOURNAMENT_START;

		GetSoundManager()->Play(&tSoundParam);

		pProposal->bProposal = true;
	}
	

	// �������� Proposal �Ѵ�
	
	std::string nMsgBoxID = "DST_TELEPORT_COMMON_CONFIRM_MSG";
	if( bFinalConfirm )
		nMsgBoxID = "DST_TELEPORT_FINAL_CONFIRM_MSG";

	switch( pProposal->dataNotify.byTeleportType )
	{
		case TELEPORT_TYPE_RANKBATTLE:
		{
			WCHAR awcBuffer[128];

			swprintf_s(awcBuffer, 128, L"%s %s",
				GetDisplayStringManager()->GetString("DST_MOVE_POSITION"),
				GetDisplayStringManager()->GetString("DST_TELEPORT_TYPE_RANKBATTLE"));


			sMsgBoxData data;
			data.byIndex = pProposal->dataNotify.byInfoIndex;
			GetAlarmManager()->FormattedAlarmMessage(nMsgBoxID,
				FALSE,
				(RwReal)pProposal->dataNotify.wWaitTime,
				&data,
				awcBuffer);
		}
		break;
		case TELEPORT_TYPE_BUDOKAI:		// õ������ ����ȸ ������ �̵��Ͻðڽ��ϱ�?
		{
			sMsgBoxData data;
			data.byIndex = pProposal->dataNotify.byInfoIndex;
			GetAlarmManager()->FormattedAlarmMessage( nMsgBoxID, 
				FALSE, 
				(RwReal)pProposal->dataNotify.wWaitTime,
				&data,
				GetDisplayStringManager()->GetString( "DST_BUDOKAI_TELEPORT_MSG_TBSERVER" ) );
		}
		break;
		case TELEPORT_TYPE_MINORMATCH:	// õ������ ����ȸ ������ �ڷ���Ʈ
		{
			// make string '���� �����'
			WCHAR awcBuffer[128];
			swprintf_s( awcBuffer, 128, GetDisplayStringManager()->GetString( "DST_BUDOKAI_TELEPORT_MSG_MATCH" ),
				GetDisplayStringManager()->GetString( "DST_BUDOKAI_REQUEST_MINOR" ) );

			sMsgBoxData data;
			data.byIndex = pProposal->dataNotify.byInfoIndex;
			GetAlarmManager()->FormattedAlarmMessage( nMsgBoxID,
				FALSE,
				(RwReal)pProposal->dataNotify.wWaitTime,
				&data,
				awcBuffer );
		}
		break;
		case TELEPORT_TYPE_MAJORMATCH:	// õ������ ����ȸ ���� �ڷ���Ʈ
		{
			RwUInt8 nDepth = pProposal->dataNotify.byBudokaiMatchDepth;
			std::string nStringID = "DST_BUDOKAI_MAJORMATCH_INFO_TITLE_32";
			switch( nDepth )
			{
			case BUDOKAI_MATCH_DEPTH_2:
				nStringID = "DST_BUDOKAI_MAJORMATCH_INFO_TITLE_FINAL";
				break;
			case BUDOKAI_MATCH_DEPTH_4:
				nStringID = "DST_BUDOKAI_MAJORMATCH_INFO_TITLE_SEMIFINAL";
				break;
			case BUDOKAI_MATCH_DEPTH_8:
				nStringID = "DST_BUDOKAI_MAJORMATCH_INFO_TITLE_8";
				break;
			case BUDOKAI_MATCH_DEPTH_16:
				nStringID = "DST_BUDOKAI_MAJORMATCH_INFO_TITLE_16";
				break;
			case BUDOKAI_MATCH_DEPTH_32:
				nStringID = "DST_BUDOKAI_MAJORMATCH_INFO_TITLE_32";
				break;
			default:
				nStringID = "DST_BUDOKAI_MAJORMATCH_INFO_TITLE_32";
				break;
			}

			// make string '���� ?? �� �����'
			WCHAR awcBuffer1[32];
			swprintf_s( awcBuffer1, 32, L"%s %s", 
				GetDisplayStringManager()->GetString( "DST_BUDOKAI_REQUEST_MAJOR" ),
				GetDisplayStringManager()->GetString( nStringID ) );

			WCHAR awcBuffer2[128];
			swprintf_s( awcBuffer2, 128, GetDisplayStringManager()->GetString( "DST_BUDOKAI_TELEPORT_MSG_MATCH" ),
				awcBuffer1 );

			sMsgBoxData data;
			data.byIndex = pProposal->dataNotify.byInfoIndex;
			GetAlarmManager()->FormattedAlarmMessage( nMsgBoxID,
				FALSE,
				(RwReal)pProposal->dataNotify.wWaitTime,
				&data,
				awcBuffer2 );
		}
		break;
		case TELEPORT_TYPE_FINALMATCH:	// õ������ ����ȸ �ἱ �ڷ���Ʈ
		{
			// make string '�ἱ �����'
			WCHAR awcBuffer[64];
			swprintf_s( awcBuffer, 64, GetDisplayStringManager()->GetString( "DST_BUDOKAI_TELEPORT_MSG_MATCH" ),
				GetDisplayStringManager()->GetString( "DST_BUDOKAI_REQUEST_FINAL" ) );

			sMsgBoxData data;
			data.byIndex = pProposal->dataNotify.byInfoIndex;
			GetAlarmManager()->FormattedAlarmMessage( nMsgBoxID,
				FALSE,
				(RwReal)pProposal->dataNotify.wWaitTime,
				&data,
				awcBuffer );
		}
		break;
		case TELEPORT_TYPE_PARTY_POPO:
		{
			sMsgBoxData data;
			data.byIndex = pProposal->dataNotify.byInfoIndex;
			GetAlarmManager()->FormattedAlarmMessage(nMsgBoxID,
				FALSE,
				(RwReal)pProposal->dataNotify.wWaitTime,
				&data,
				GetDisplayStringManager()->GetString("DST_PARTYPOPO_RECALL_FROM_PERTY"));
		}
		break;
		case TELEPORT_TYPE_PARTY_SUMMON:
		{
			WCHAR awcBuffer[64];
			swprintf_s(awcBuffer, 64, GetDisplayStringManager()->GetString("DST_MASCOTEX_SKILL_PARTY_SUMMON"),
				pProposal->dataNotify.wszSummonnerName);

			sMsgBoxData data;
			data.byIndex = pProposal->dataNotify.byInfoIndex;
			GetAlarmManager()->FormattedAlarmMessage(nMsgBoxID,
				FALSE,
				(RwReal)pProposal->dataNotify.wWaitTime,
				&data,
				awcBuffer);
		}
		break;
		case TELEPORT_TYPE_GUILD_SUMMON:
		{
			WCHAR awcBuffer[64];
			swprintf_s(awcBuffer, 64, GetDisplayStringManager()->GetString("DST_MASCOTEX_SKILL_GUILD_SUMMON"),
				pProposal->dataNotify.wszSummonnerName);

			sMsgBoxData data;
			data.byIndex = pProposal->dataNotify.byInfoIndex;
			GetAlarmManager()->FormattedAlarmMessage(nMsgBoxID,
				FALSE,
				(RwReal)pProposal->dataNotify.wWaitTime,
				&data,
				awcBuffer);
		}
		break;
		default:
		{
			WCHAR awcBuffer[64];
			swprintf_s(awcBuffer, 64, L"MOVE TO TYPE: %d",
				(int)pProposal->dataNotify.byTeleportType);

			sMsgBoxData data;
			data.byIndex = pProposal->dataNotify.byInfoIndex;
			GetAlarmManager()->FormattedAlarmMessage( nMsgBoxID,
				FALSE,
				(RwReal)pProposal->dataNotify.wWaitTime,
				&data,
				awcBuffer );
		}
		break;
	}
}

STeleportProposal* CTeleportProposalManager::GetTeleportProposal( RwUInt8 byIndex )
{
	MapTeleportProposal::iterator it = m_mapTeleportProposal.find( byIndex );
	if( it != m_mapTeleportProposal.end() )
	{
		return (*it).second;
	}

	return NULL;
}

RwBool CTeleportProposalManager::IsAvatar()
{
	CNtlSobAvatar* pSobAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( pSobAvatar )
		return TRUE;
	else
		return FALSE;
}

RwBool CTeleportProposalManager::IsGameStage()
{
	CNtlStage *pStage = CStageManager::GetInstance()->GetActiveStage();
	std::string strStageName = pStage->GetName();

	if( strStageName == GAME_STAGE_NAME )
	{
		return TRUE;
	}	

	return FALSE;
}

RwBool CTeleportProposalManager::CreateInstance( VOID )
{
	if( !m_pInstance )
	{
		m_pInstance = NTL_NEW CTeleportProposalManager();
		NTL_ASSERT( m_pInstance, "CTeleportProposalManager::CreateInstance : Instance Allocate Fail" );
		m_pInstance->Create();
	}

	return TRUE;
}

VOID CTeleportProposalManager::DeleteInstance( VOID )
{
	if( m_pInstance )
	{
		m_pInstance->Destroy();
		NTL_DELETE( m_pInstance );
	}
}

CTeleportProposalManager* CTeleportProposalManager::GetInstance( VOID )
{
	return m_pInstance;
}