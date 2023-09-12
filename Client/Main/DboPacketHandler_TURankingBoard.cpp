/*****************************************************************************
* File			: DboPackethandler_TURankingBoard.cpp
* Author		: Cho Haesung
* Copyright		: (��)NTL
* Date			: 2008. 4. 8
* Abstract		: 
*****************************************************************************
* Desc         : ��ŷ���忡 ���õ� ��Ŷ
*****************************************************************************/

#include "precomp_dboclient.h"
#include "DboPacketHandler.h"

// simulation
#include "NtlNetSender.h"
#include "NtlSLEventFunc.h"
#include "NtlSLPacketGenerator.h"
#include "NtlWorldConceptNPCCommu.h"
#include "NtlCameraController.h"

/**
* \brief ��ŷ���� : ��ũ��Ʋ�� �������� ��û�� �������� ����Ʈ�� �޴´�.
*/
void PacketHandler_TURankBattle_Rank_List_Res(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock( TU_RANKBATTLE_RANK_LIST_RES );

	sTU_RANKBATTLE_RANK_LIST_RES* pResult = (sTU_RANKBATTLE_RANK_LIST_RES*)pPacket;

	if( pResult->wResultCode != CHAT_SUCCESS )
	{
		/*GetAlarmManager()->AlarmMessage( pResult->wResultCode, TRUE );*/
		return;
	}

	CDboEventGenerator::RankBattleRankListRes( pResult->wResultCode,
		pResult->dwPage, pResult->byCompareDay, pResult->byRankInfoCount, pResult->wRankInfo,
		reinterpret_cast<void*>(&pResult->sData) );
}

/**
* \brief Ranking Board: You will receive a list of pages with the character you searched for in Rank Battle Rank.
*/
void PacketHandler_TURankBattle_Rank_Find_Character_Res(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock( TU_RANKBATTLE_RANK_FIND_CHARACTER_RES );

	sTU_RANKBATTLE_RANK_FIND_CHARACTER_RES* pResult = (sTU_RANKBATTLE_RANK_FIND_CHARACTER_RES*)pPacket;

	if( pResult->wResultCode != CHAT_SUCCESS && pResult->wResultCode != COMMUNITY_RANK_BATTLE_LIST_NOT_FOUND)
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "sTU_RANKBATTLE_RANK_FIND_CHARACTER_RES"), TRUE );
		return;
	}

	CDboEventGenerator::RankBattleRankFindCharacterRes( pResult->wResultCode,
		pResult->dwPage, pResult->byCompareDay, pResult->wszCharName, pResult->byRankInfoCount,
		pResult->wRankInfo, reinterpret_cast<void*>(&pResult->sData));

}

/**
* \brief ��ŷ���� : ��ũ��Ʋ�� �������� ��û�� �񱳳�¥�� ������ ����Ʈ�� �޴´�.
*/
void PacketHandler_TURankBattle_Rank_Compare_Day_Res(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock( TU_RANKBATTLE_RANK_COMPARE_DAY_RES );

	sTU_RANKBATTLE_RANK_COMPARE_DAY_RES* pResult = (sTU_RANKBATTLE_RANK_COMPARE_DAY_RES*)pPacket;

	if( pResult->wResultCode != CHAT_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "TU_RANKBATTLE_RANK_COMPARE_DAY_RES"), TRUE );
		return;
	}

	CDboEventGenerator::RankBattleRankCompareDayRes(pResult->wResultCode, pResult->dwPage,
		pResult->byCompareDay, pResult->bIsFullList, pResult->byInfoCount, pResult->wRankInfo, pResult->wCompareInfo,
		reinterpret_cast<void*>(&pResult->sData));
}

void PacketHandler_TUTMQ_Record_List_Res(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock( TU_TMQ_RECORD_LIST_RES );

	sTU_TMQ_RECORD_LIST_RES* pResult = (sTU_TMQ_RECORD_LIST_RES*)pPacket;

	if( pResult->wResultCode != CHAT_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "TU_TMQ_RECORD_LIST_RES"), TRUE );
		return;
	}

	CDboEventGenerator::TMQRecordListRes( pResult->wResultCode, pResult->tmqTblidx, pResult->byDifficult, pResult->byTeamCount, (void*)pResult->asTeam );
}

void PacketHandler_TUTMQ_Member_List_Res(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock( TU_TMQ_MEMBER_LIST_RES );

	sTU_TMQ_MEMBER_LIST_RES* pResult = (sTU_TMQ_MEMBER_LIST_RES*)pPacket;

	if( pResult->wResultCode != CHAT_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "TU_TMQ_MEMBER_LIST_RES"), TRUE );
		return;
	}

	CDboEventGenerator::TMQMemberListRes( pResult->wResultCode, pResult->tmqTblidx, pResult->byDifficult, pResult->byRank, (void*)&pResult->sTeam );
}