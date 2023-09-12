/*****************************************************************************
* File			: DboPackethandler_TU.cpp
* Author		: Hong sungbock
* Copyright		: (��)NTL
* Date			: 2008. 2. 25
* Abstract		: 
*****************************************************************************
* Desc         : ���� ���� & Ŀ�´�Ƽ ���� ��� ��Ŷ �ڵ�
*****************************************************************************/

#include "precomp_dboclient.h"
#include "DboPacketHandler.h"

// Shared
#include "NtlGuild.h"
#include "DojoTable.h"
#include "ObjectTable.h"

// presentation
#include "NtlPLVisualManager.h"
#include "NtlPLDojoContainer.h"

// simulation
#include "NtlNetSender.h"
#include "NtlSLEventFunc.h"
#include "NtlSLPacketGenerator.h"
#include "NtlWorldConceptNPCCommu.h"
#include "NtlCameraController.h"
#include "NtlSobPlayer.h"
#include "NtlSobGroup.h"

// dbo
#include "IconMoveManager.h"
#include "LobbyManager.h"


void PacketHandler_GSGuild_Create_Res(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_GUILD_CREATE_RES );

	// ��� ���� ���
	sGU_GUILD_CREATE_RES* pResult = (sGU_GUILD_CREATE_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_GUILD_CREATE_RES"), TRUE );
		return;
	}

	// ��带 ��������ϴ�
	GetAlarmManager()->AlarmMessage("DST_GUILD_CREATE");
}

void PacketHandler_GSGuild_Invite_Res(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_GUILD_INVITE_RES );

	// ��� �ʴ� ���
	sGU_GUILD_INVITE_RES* pResult = (sGU_GUILD_INVITE_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_GUILD_INVITE_RES"), TRUE );
		return;
	}

	// %s���� ��忡 �ʴ��Ͽ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_INVITE", FALSE, NULL, pResult->wszTargetName);
}

void PacketHandler_TUGuild_CreateNfy(void *pPacket)
{
	// ��尡 �����Ǿ����� ��Ÿ �ɹ����� �˸���
	sTU_GUILD_CREATED_NFY *pResult = (sTU_GUILD_CREATED_NFY*)pPacket;

	// %s ��尡 �����Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_CREATE_NFY", FALSE, NULL, pResult->wszGuildName);
}

void PacketHandler_TUGuild_Info(void *pPacket)
{
	// ��� ������ �޴´�
	sTU_GUILD_INFO* pResult = (sTU_GUILD_INFO*)pPacket;

	CNtlSLEventGenerator::SLGuildEvent(SLGE_NOTICE, wcslen(pResult->guildInfo.awchNotice),
													pResult->guildInfo.awchName,
													pResult->guildInfo.awchNotice);

	CNtlSLEventGenerator::SLGuildEvent(SLGE_GUILD_INFO, INVALID_SERIAL_ID, (void*)&pResult->guildInfo);
}

void PacketHandler_TUGuild_MemberInfo(void *pPacket)
{
	// ��� �ɹ� ������ �޴´�
	sTU_GUILD_MEMBER_INFO *pResult = (sTU_GUILD_MEMBER_INFO*)pPacket;

	CNtlSLEventGenerator::SLGuildEvent(SLGE_ADD_MEMBER, INVALID_SERIAL_ID, (void*)&pResult->guildMemberInfo);

	CNtlSobAvatar *pSobAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( pSobAvatar && pResult->guildMemberInfo.charId == pSobAvatar->GetCharID() )
	{
		SERVER_HANDLE	hServer	= GetLobbyManager()->GetSelectedServerHandle();
		CLobby*			pLobby	= GetLobbyManager()->GetLobby(hServer);
		if( !pLobby )
		{
			DBO_FAIL("Not exist lobby infomation of server handle : " << hServer);
			return;
		}

		RwUInt8 bySelectedCharIndex = pLobby->GetSelectedCharacterIndex();

		sLOBBY_CHARACTER* pLOBBY_CHARACTER = pLobby->GetCharacter( bySelectedCharIndex );
		if( !pLOBBY_CHARACTER )
		{
			DBO_FAIL("Not exist character of index : " << pLobby->GetSelectedCharacterIndex());
			return;
		}

		RwUInt32 uiMapNameIndex = pLOBBY_CHARACTER->tSummary.dwMapInfoIndex;
		CNtlSLEventGenerator::SLGuildEvent(SLGE_MEM_POS, pResult->guildMemberInfo.charId, (void*)&uiMapNameIndex);
	}
}

void PacketHandler_TUGuild_DisbandRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock(TU_GUILD_DISBAND_RES);

	// ��尡 �ػ� ��Ⱑ �Ǿ����� ����忡�� �˸���
	sTU_GUILD_DISBAND_RES *pResult = (sTU_GUILD_DISBAND_RES*)pPacket;

	if( pResult->wResultCode != CHAT_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "TU_GUILD_DISBAND_RES"), TRUE);
		return;
	}

	CNtlSLEventGenerator::SLGuildEvent(SLGE_BEING_DISBAND, INVALID_SERIAL_ID, (void*)&pResult->timeToDisband);
}

void PacketHandler_TUGuild_BeingDisbanded_Nfy(void *pPacket)
{
	// ��尡 �ػ� ��������� ��� �ɹ����� �˸���
	sTU_GUILD_BEING_DISBANDED_NFY *pResult = (sTU_GUILD_BEING_DISBANDED_NFY*)pPacket;

	CNtlSLEventGenerator::SLGuildEvent(SLGE_BEING_DISBAND, INVALID_SERIAL_ID, (void*)&pResult->timeToDisband);
}

void PacketHandler_TUGuild_Disband_Cancel_Res(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock(TU_GUILD_DISBAND_CANCEL_RES);

	// ��尡 �ػ� ����߿��� ��ҵǾ����� ����忡�� �˸���
	sTU_GUILD_DISBAND_CANCEL_RES *pResult = (sTU_GUILD_DISBAND_CANCEL_RES*)pPacket;

	if( pResult->wResultCode != CHAT_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "TU_GUILD_DISBAND_CANCEL_RES"), TRUE);
		return;
	}

	CNtlSLEventGenerator::SLGuildEvent(SLGE_CANCLE_DISBAND);
}

void PacketHandler_TUGuild_Disband_Canceled_Nfy(void *pPacket)
{
	// ��尡 �ػ� ����߿��� ��ҵǾ����� �α����� �������� �˸���
	CNtlSLEventGenerator::SLGuildEvent(SLGE_CANCLE_DISBAND);
}

void PacketHandler_TUGuild_Disband_Nfy(void *pPacket)
{
	// ��尡 �ػ�Ǿ����� �α����� �������� �˸���
	CNtlSLEventGenerator::SLGuildEvent(SLGE_DISBAND);

	// ��尡 �ػ�Ǿ����ϴ�
	GetAlarmManager()->AlarmMessage("DST_GUILD_DISBAND");
}

void PacketHandler_TUGuild_Invited_Nfy(void *pPacket)
{
	// ��� ���� ������ �޴´�
	sTU_GUILD_INVITED_NFY *pResult = (sTU_GUILD_INVITED_NFY*)pPacket;

	// %s ��忡 �����Ͻðڽ��ϱ�?
	GetAlarmManager()->FormattedAlarmMessage( "DST_GUILD_INVITE_REQ", FALSE, NULL, pResult->wszGuildName );
}

void PacketHandler_TUGuild_Response_Invitation_Res(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock(TU_GUILD_RESPONSE_INVITATION_RES);

	// �ڽ��� ��� ���� ����� �˷��ش�
	sTU_GUILD_RESPONSE_INVITATION_RES *pResult = (sTU_GUILD_RESPONSE_INVITATION_RES*)pPacket;

	if( pResult->wResultCode != CHAT_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "TU_GUILD_RESPONSE_INVITATION_RES"), TRUE);
		return;
	}
}

void PacketHandler_TUGuild_Member_Joined_Nfy(void *pPacket)
{
	// ���� ��� �ɹ����� ���ο� ������ ���������� �˸���
	sTU_GUILD_MEMBER_JOINED_NFY *pResult = (sTU_GUILD_MEMBER_JOINED_NFY*)pPacket;

	CNtlSLEventGenerator::SLGuildEvent(SLGE_ADD_MEMBER, INVALID_SERIAL_ID, (void*)&pResult->memberInfo);

	// %s���� ��忡 �����Ͽ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_NEW_MEMBER", FALSE, NULL, pResult->memberInfo.wszMemberName);
}

void PacketHandler_TUGuild_Invitation_Declined_Nfy(void *pPacket)
{
	// ��� �ʴ뿡 �����Ͽ���
	sTU_GUILD_INVITATION_DECLINED_NFY *pResult = (sTU_GUILD_INVITATION_DECLINED_NFY*)pPacket;

	// %s���� ��� ������ �����Ͽ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_DECLINE", FALSE, NULL, pResult->wszTargetName);
}

void PacketHandler_TUGuild_Invitation_Expired_Nfy(void *pPacket)
{
	// ��� �ʴ뿡 �������� �ʾҴ�
	sTU_GUILD_INVITATION_EXPIRED_NFY *pResult = (sTU_GUILD_INVITATION_EXPIRED_NFY*)pPacket;

	// %s�� ��� ���Կ� �������� �ʾҽ��ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_EXPIRED", FALSE, NULL, pResult->wszTargetName);
}

void PacketHandler_TUGuild_Leave_Res(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock(TU_GUILD_LEAVE_RES);

	// �ڽ��� ��带 Ż���Ͽ���
	sTU_GUILD_LEAVE_RES *pResult = (sTU_GUILD_LEAVE_RES*)pPacket;

	if( pResult->wResultCode != CHAT_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "TU_GUILD_LEAVE_RES"), TRUE);
		return;
	}

	CNtlSLEventGenerator::SLGuildEvent(SLGE_DISBAND);
}

void PacketHandler_TUGuild_Member_Left_Nfy(void *pPacket)
{
	// ������ Ż���Ͽ����� �α����� ���ɹ����� �˸���
	sTU_GUILD_MEMBER_LEFT_NFY *pResult = (sTU_GUILD_MEMBER_LEFT_NFY*)pPacket;	

	CNtlGuild* pGuild = GetNtlSLGlobal()->GetSobAvatar()->GetGuild();
	sGuildMember* pMember = reinterpret_cast<sGuildMember*>( pGuild->GetMemberbyKey(pResult->memberCharId) );

	if( !pMember )
	{
		DBO_FAIL("Not exist guild member of charID : " << pResult->memberCharId);
		return;
	}

	// %s���� ��带 Ż���Ͽ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_LEAVE_MEMBER", FALSE, NULL, pMember->wszMemberName);
	CNtlSLEventGenerator::SLGuildEvent(SLGE_DEL_MEMBER, pResult->memberCharId);
}

void PacketHandler_TUGuild_Kick_Out_Res(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock(TU_GUILD_KICK_OUT_RES);

	// ������ �߹���״�
	sTU_GUILD_KICK_OUT_RES *pResult = (sTU_GUILD_KICK_OUT_RES*)pPacket;

	if( pResult->wResultCode != CHAT_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "TU_GUILD_KICK_OUT_RES"), TRUE);
		return;
	}

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;

	CNtlGuild*		pGuild	= pAvatar->GetGuild();
	sGuildMember* pMember = reinterpret_cast<sGuildMember*>( pGuild->GetMemberbyKey(pResult->kickedOutMemberCharId) );

	if( !pMember )
	{
		DBO_FAIL("Not exist guild member of charID : " << pResult->kickedOutMemberCharId);
		return;
	}
}

void PacketHandler_TUGuild_Member_Kicked_Out_Nfy(void *pPacket)
{
	// ������ �߹�Ǿ����� ��� �ɹ����� �˸���
	sTU_GUILD_MEMBER_KICKED_OUT_NFY* pResult = (sTU_GUILD_MEMBER_KICKED_OUT_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;

	CNtlGuild*		pGuild	= pAvatar->GetGuild();
	sGuildMember* pMember = reinterpret_cast<sGuildMember*>( pGuild->GetMemberbyKey(pResult->memberCharId) );

	if( !pMember )
	{
		DBO_FAIL("Not exist guild member of charID : " << pResult->memberCharId);
		return;
	}

	// %s���� ��忡�� �߹�Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_KICKOUT_MEMBER", FALSE, NULL, pMember->wszMemberName);
	CNtlSLEventGenerator::SLGuildEvent(SLGE_DEL_MEMBER, pResult->memberCharId);
}


void PacketHandler_TUGuild_Appoint_Second_Master_Res(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock(TU_GUILD_APPOINT_SECOND_MASTER_RES);

	// �α������ �Ӹ�Ǿ����� ����忡�� �˸���
	sTU_GUILD_APPOINT_SECOND_MASTER_RES* pResult = (sTU_GUILD_APPOINT_SECOND_MASTER_RES*)pPacket;

	if( pResult->wResultCode != CHAT_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "TU_GUILD_APPOINT_SECOND_MASTER_RES"), TRUE);
		return;
	}

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;

	CNtlGuild*		pGuild	= pAvatar->GetGuild();
	sGuildMember* pMember = reinterpret_cast<sGuildMember*>( pGuild->GetMemberbyKey(pResult->secondMasterCharId) );

	if( !pMember )
	{
		DBO_FAIL("Not exist guild member of charID : " << pResult->secondMasterCharId);
		return;
	}

	// %s���� �α������ �Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_SECOND_MASTER_APPOINTED", FALSE, NULL, pMember->wszMemberName);
	CNtlSLEventGenerator::SLGuildEvent(SLGE_APPOINT_SECOND_MASTER, pResult->secondMasterCharId);
}

void PacketHandler_TUGuild_Second_Master_Appointed_Nfy(void *pPacket)
{
	// �α������ �Ӹ�Ǿ����� �α����� �������� �˸���
	sTU_GUILD_SECOND_MASTER_APPOINTED_NFY* pResult = (sTU_GUILD_SECOND_MASTER_APPOINTED_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;

	CNtlGuild*		pGuild	= pAvatar->GetGuild();
	sGuildMember* pMember = reinterpret_cast<sGuildMember*>( pGuild->GetMemberbyKey(pResult->memberCharId) );

	if( !pMember )
	{
		DBO_FAIL("Not exist guild member of charID : " << pResult->memberCharId);
		return;
	}

	// %s���� �α������ �Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_SECOND_MASTER_APPOINTED", FALSE, NULL, pMember->wszMemberName);
	CNtlSLEventGenerator::SLGuildEvent(SLGE_APPOINT_SECOND_MASTER, pResult->memberCharId);
}

void PacketHandler_TUGuild_DismissSecondMasterRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock(TU_GUILD_DISMISS_SECOND_MASTER_RES);

	// �α������ ���� ���� ���
	sTU_GUILD_DISMISS_SECOND_MASTER_RES* pResult = (sTU_GUILD_DISMISS_SECOND_MASTER_RES*)pPacket;

	if( pResult->wResultCode != CHAT_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "TU_GUILD_DISMISS_SECOND_MASTER_RES"), TRUE);
		return;
	}

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;

	CNtlGuild*		pGuild	= pAvatar->GetGuild();
	sGuildMember* pMember = reinterpret_cast<sGuildMember*>( pGuild->GetMemberbyKey(pResult->secondMasterCharId) );

	if( !pMember )
	{
		DBO_FAIL("Not exist guild member of charID : " << pResult->secondMasterCharId);
		return;
	}

	// %s���� �α�� �����Ϳ��� �Ϲ� ���ɹ��� �Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_DISMISS_SECOND_MASTER", FALSE, NULL, pMember->wszMemberName);
	CNtlSLEventGenerator::SLGuildEvent(SLGE_DISMISS_SECOND_MASTER, pResult->secondMasterCharId);
}

void PacketHandler_TUGuild_SecondMasterDismissedNfy(void *pPacket)
{
	// �α������ ���� ���� �Ǿ����� ��� �ɹ����� �˸���
	sTU_GUILD_SECOND_MASTER_DISMISSED_NFY* pResult = (sTU_GUILD_SECOND_MASTER_DISMISSED_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;

	CNtlGuild*		pGuild	= pAvatar->GetGuild();
	sGuildMember* pMember = reinterpret_cast<sGuildMember*>( pGuild->GetMemberbyKey(pResult->memberCharId) );

	if( !pMember )
	{
		DBO_FAIL("Not exist guild member of charID : " << pResult->memberCharId);
		return;
	}

	// %s���� �α�� �����Ϳ��� �Ϲ� ���ɹ��� �Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_DISMISS_SECOND_MASTER", FALSE, NULL, pMember->wszMemberName);
	CNtlSLEventGenerator::SLGuildEvent(SLGE_DISMISS_SECOND_MASTER, pResult->memberCharId);
}

void PacketHandler_TUGuild_Change_Guild_Master_Res(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock(TU_GUILD_CHANGE_GUILD_MASTER_RES);

	// ������� �ٲ������ ���� ����忡�� �˸���
	sTU_GUILD_CHANGE_GUILD_MASTER_RES* pResult = (sTU_GUILD_CHANGE_GUILD_MASTER_RES*)pPacket;

	if( pResult->wResultCode != CHAT_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "TU_GUILD_CHANGE_GUILD_MASTER_RES"), TRUE);
		return;
	}

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;

	CNtlGuild*		pGuild	= pAvatar->GetGuild();
	sGuildMember* pMember = reinterpret_cast<sGuildMember*>( pGuild->GetMemberbyKey(pResult->newMasterCharId) );

	if( !pMember )
	{
		DBO_FAIL("Not exist guild member of charID : " << pResult->newMasterCharId);
		return;
	}

	// %s���� ������� �Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_CHANGE_MASTER", FALSE, NULL, pMember->wszMemberName);
	CNtlSLEventGenerator::SLGuildEvent(SLGE_APPOINT_MASTER, pResult->newMasterCharId);
}

void PacketHandler_TUGuild_Guild_Master_Changed_Nfy(void *pPacket)
{
	// ������� �ٲ������ ��� �ɹ����� �˸���
	sTU_GUILD_GUILD_MASTER_CHANGED_NFY* pResult = (sTU_GUILD_GUILD_MASTER_CHANGED_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;

	CNtlGuild*		pGuild	= pAvatar->GetGuild();
	sGuildMember* pMember = reinterpret_cast<sGuildMember*>( pGuild->GetMemberbyKey(pResult->memberCharId) );

	if( !pMember )
	{
		DBO_FAIL("Not exist guild member of charID : " << pResult->memberCharId);
		return;
	}

	// %s���� ������� �Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_CHANGE_MASTER", FALSE, NULL, pMember->wszMemberName);
	CNtlSLEventGenerator::SLGuildEvent(SLGE_APPOINT_MASTER, pResult->memberCharId);
}

void PacketHandler_TUGuild_MemberPositionChangedNfy(void* pPacket)
{
	// ��� �ɹ��� ���� ����
	sTU_GUILD_MEMBER_POSITION_CHANGED_NFY* pResult = (sTU_GUILD_MEMBER_POSITION_CHANGED_NFY*)pPacket;

	CNtlSLEventGenerator::SLGuildEvent(SLGE_MEM_POS, pResult->memberCharId, (void*)&pResult->newMapNameTblidx);
}

void PacketHandler_TUGuild_MemberClassChangedNfy(void* pPacket)
{
	// ��� �ɹ��� Ŭ���� ����
	sTU_GUILD_MEMBER_CLASS_CHANGED_NFY* pResult = (sTU_GUILD_MEMBER_CLASS_CHANGED_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;

	CNtlGuild*		pGuild	= pAvatar->GetGuild();
	sGuildMember* pMember = reinterpret_cast<sGuildMember*>( pGuild->GetMemberbyKey(pResult->memberCharId) );

	if( !pMember )
	{
		DBO_FAIL("Not exist guild member of charID : " << pResult->memberCharId);
		return;
	}

	// %s���� %s Ŭ������ �Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_CLASS_CHANGE_MEMBER", FALSE, NULL, pMember->wszMemberName, Logic_GetClassName(pResult->byNewClass));
	CNtlSLEventGenerator::SLGuildEvent(SLGE_MEM_CLASS, pResult->memberCharId, (void*)&pResult->byNewClass);
}

void PacketHandler_TUGuild_MemberLevelChangedNfy(void* pPacket)
{
	// ��� �ɹ��� ���� ����
	sTU_GUILD_MEMBER_LEVEL_CHANGED_NFY* pResult = (sTU_GUILD_MEMBER_LEVEL_CHANGED_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;

	CNtlGuild*		pGuild	= pAvatar->GetGuild();
	sGuildMember* pMember = reinterpret_cast<sGuildMember*>( pGuild->GetMemberbyKey(pResult->memberCharId) );

	if( !pMember )
	{
		DBO_FAIL("Not exist guild member of charID : " << pResult->memberCharId);
		return;
	}

	// %s���� %d ������ �Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_LEVEL_CHANGE_MEMBER", FALSE, NULL, pMember->wszMemberName, pResult->byNewLevel);
	CNtlSLEventGenerator::SLGuildEvent(SLGE_MEM_LEVEL, pResult->memberCharId, (void*)&pResult->byNewLevel);
}

void PacketHandler_TUGuild_ReputationChangedNfy(void* pPacket)
{
	// ��� �ɹ��� ���� ����
	sTU_GUILD_MEMBER_REPUTATION_CHANGED_NFY* pResult = (sTU_GUILD_MEMBER_REPUTATION_CHANGED_NFY*)pPacket;

	CNtlSLEventGenerator::SLGuildEvent(SLGE_MEM_REPUTATION, pResult->memberCharId, (void*)&pResult->dwNewReputation);
}

void PacketHandler_TUGuild_MemberOnlineNfy(void* pPacket)
{
	// ��� �ɹ��� ���ӿ� �����Ͽ���
	sTU_GUILD_MEMBER_ONLINE_NFY* pResult = (sTU_GUILD_MEMBER_ONLINE_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;

	CNtlGuild*		pGuild	= pAvatar->GetGuild();
	sGuildMember* pMember = reinterpret_cast<sGuildMember*>( pGuild->GetMemberbyKey(pResult->memberCharId) );

	if( !pMember )
	{
		DBO_FAIL("Not exist guild member of charID : " << pResult->memberCharId);
		return;
	}

	// %s���� �����߽��ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_ONLINE_MEMBER", FALSE, NULL, pMember->wszMemberName);
	CNtlSLEventGenerator::SLGuildEvent(SLGE_MEM_ONLINE, pResult->memberCharId, (void*)&pResult->newMapNameTblidx);
}

void PacketHandler_TUGuild_MemberOfflineNfy(void* pPacket)
{
	// ��� �ɹ��� ������ ������
	sTU_GUILD_MEMBER_OFFLINE_NFY *pResult = (sTU_GUILD_MEMBER_OFFLINE_NFY*)pPacket;

	CNtlSLEventGenerator::SLGuildEvent(SLGE_MEM_OFFLINE, pResult->memberCharId);
}

void PacketHandler_GSGuild_NameChanged_Res(void* pPacket)
{
	// ����� �̸��� ����Ǿ����� ����忡�� �˸���
	API_GetSLPacketLockManager()->Unlock(GU_GUILD_CHANGE_NAME_RES);

	Logic_CancelNpcFacing();

	sGU_GUILD_CHANGE_NAME_RES* pResult = (sGU_GUILD_CHANGE_NAME_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_GUILD_CHANGE_NAME_RES"), TRUE );
		return;
	}

	// ��� �̸��� ����Ǿ����ϴ�
	GetAlarmManager()->AlarmMessage("DST_GUILD_CHANGED_GUILD_NAME");
}

void PacketHandler_GSGuild_NameChanged_Nfy(void* pPacket)
{
	sGU_GUILD_NAME_CHANGED_NFY* pResult = (sGU_GUILD_NAME_CHANGED_NFY*)pPacket;

	CNtlSLEventGenerator::ChangeGuildName(pResult->hSubject, pResult->wszGuildName);

	CNtlGuild* pGuild = GetNtlSLGlobal()->GetSobAvatar()->GetGuild();
	if( pGuild->IsHaveGroup() )
	{
		// ������ ��Ŷ ������ �� ������ ���´�
		/*
		// ��� �̸��� ����Ǿ����ϴ�
		GetAlarmManager()->AlarmMessage(DST_GUILD_CHANGED_GUILD_NAME);
		*/
	}
}

void PacketHandler_GSGuild_FunctionAdd_Res(void* pPacket)
{
	// ����� ����� ����Ǿ����� �˸���
	API_GetSLPacketLockManager()->Unlock(GU_GUILD_FUNCTION_ADD_RES);

	Logic_CancelNpcFacing();

	sGU_GUILD_FUNCTION_ADD_RES* pResult = (sGU_GUILD_FUNCTION_ADD_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_GUILD_FUNCTION_ADD_RES"), TRUE );
		return;
	}	

	// ���� ��� ����� �޼����� �����ִ� ��Ŷ : PacketHandler_TUGuild_FunctionChange_Nfy
}

void PacketHandler_TUGuild_FunctionChange_Nfy(void* pPacket)
{
	// Guild or Dojo functions have changed
	sTU_GUILD_FUNCTION_CHANGE_NFY* pResult = (sTU_GUILD_FUNCTION_CHANGE_NFY*)pPacket;

	CNtlSLEventGenerator::SLGuildEvent(SLGE_CHANGE_FUNCTION, INVALID_DWORD, (VOID*)&pResult->qwGuildFunctionFlag, (void*)&pResult->byNewFunc);

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if (!pAvatar)
		return;

	// The function has changed in the guild
	if(  INVALID_BYTE == pResult->byNewFunc )
	{
		// Existing function removed
	}
	else if( IsGuildFunction((eDBO_GUILD_FUNCTION)pResult->byNewFunc) )
	{
		if (pAvatar->GetGuild()->IsGuildMaster(pAvatar->GetCharID()))
			GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_ADD_FUNCTION_NOTIFY_TO_MASTER", FALSE, NULL, Logic_GetGuildFunctionString(pResult->byNewFunc));
		else
			GetAlarmManager()->AlarmMessage("DST_GUILD_ADD_FUNCTION_NOTIFY_TO_MEMBER");
	}
	else if( IsDojoFunction((eDBO_GUILD_FUNCTION)pResult->byNewFunc) )
	{
		if (pAvatar->GetGuild()->IsGuildMaster(pAvatar->GetCharID()))
			GetAlarmManager()->FormattedAlarmMessage("DST_DOJO_ADD_FUNCTION_NOTIFY_TO_MASTER", FALSE, NULL, Logic_GetGuildFunctionString(pResult->byNewFunc));
		else
			GetAlarmManager()->AlarmMessage("DST_DOJO_ADD_FUNCTION_NOTIFY_TO_MEMBER");
	}
	else
	{
		DBO_FAIL("Invalid guild function: " << pResult->byNewFunc);
	}
}

void PacketHandler_GSGuild_GiveZenny_Res(void* pPacket)
{
	// ���ϸ� ��忡 �����Ͽ���
	API_GetSLPacketLockManager()->Unlock(GU_GUILD_GIVE_ZENNY_RES);

	Logic_CancelNpcFacing();

	sGU_GUILD_GIVE_ZENNY_RES* pResult = (sGU_GUILD_GIVE_ZENNY_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_GUILD_GIVE_ZENNY_RES"), TRUE );
		return;
	}

	// ���� �̱���
	CNtlSLEventGenerator::SLGuildEvent(SLGE_CHANGE_INVEST_ZENNY);

	// ���ϸ� ����Ͽ����ϴ�
	GetAlarmManager()->AlarmMessage("DST_GUILD_CONTRIBUTION_ZENNY_NOTIFY");
}

void PacketHandler_TUGuild_GiveZenny_Nfy(void* pPacket)
{
	// ������ ���ϸ� ���������� �˸���
	sTU_GUILD_GIVE_ZENNY_NFY* pResult = (sTU_GUILD_GIVE_ZENNY_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;

	CNtlGuild*		pGuild	= pAvatar->GetGuild();
	sGuildMember* pMember = reinterpret_cast<sGuildMember*>( pGuild->GetMemberbyKey(pResult->charId) );

	if( !pMember )
	{
		DBO_FAIL("Not exist guild member of charID : " << pResult->charId);
		return;
	}

	// %s���� %d ���ϸ� ����Ͽ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_CONTRIBUTION_ZENNY_OTHERS", FALSE, NULL, pMember->wszMemberName, Logic_FormatZeni(pResult->dwZenny));
}

void PacketHandler_GSGuild_WarehouseStart_Res(void* pPacket)
{
	// ��� â�� ����
	API_GetSLPacketLockManager()->Unlock(GU_GUILD_BANK_START_RES);

	sGU_GUILD_BANK_START_RES* pResult = (sGU_GUILD_BANK_START_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		Logic_CancelNpcFacing();

		// ������ �Ʒ��� �̺�Ʈ�� �޾Ƽ� ó���ϴ� ���� ������ �� �������� ���â��GUIŬ���� ��ü��
		// �����Ǿ� ���� �ʾƼ� �̺�Ʈ�� �޾��� ���� ó���� ���⿡�� ���ش�.
		// �̺�Ʈ�� �߻���Ű�� ���� DIALOGEVENT_OPEN_FAIL_NPC_DIALOG�� �߻���Ű�� �ٸ� ��������� ���ϼ� �����̴�
		CDboEventGenerator::DialogEvent(DIALOGEVENT_OPEN_FAIL_NPC_DIALOG, PLACE_NONE, DIALOG_GUILD_WAREHOUSEBAR);
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_GUILD_BANK_START_RES"), TRUE );
		return;
	}

	CNtlWorldConceptNPCCOMMU* pWorldConceptController = reinterpret_cast<CNtlWorldConceptNPCCOMMU*>( GetNtlWorldConcept()->GetWorldConceptController(WORLD_PLAY_NPC_COMMU) );
	pWorldConceptController->ChangeState(WORLD_NPC_GUILD_WAREHOUSE);

	CNtlSLEventGenerator::GuildWarehouseEvent(GUILD_WAREHOUSE_EVENT_START, pResult->handle);
}

void PacketHandler_GSGuild_WarehouseMove_Res(void* pPacket)
{
	// ��� â���� �������� �ű��
	API_GetSLPacketLockManager()->Unlock(GU_GUILD_BANK_MOVE_RES);

	sGU_GUILD_BANK_MOVE_RES* pResult = (sGU_GUILD_BANK_MOVE_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_GUILD_BANK_MOVE_RES"), TRUE );
		return;
	}

	GetIconMoveManager()->IconMoveEnd();

	CNtlSLEventGenerator::GuildWarehouseItemMove(pResult->hSrcItem, pResult->hDstItem,
		pResult->bySrcPlace, pResult->bySrcPos, pResult->byDestPlace, pResult->byDestPos);
}

void PacketHandler_GSGuild_WarehouseMoveStack_Res(void* pPacket)
{
	// ��� â���� ���� �������� �ű��
	API_GetSLPacketLockManager()->Unlock(GU_GUILD_BANK_MOVE_STACK_RES);

	sGU_GUILD_BANK_MOVE_STACK_RES* pResult = (sGU_GUILD_BANK_MOVE_STACK_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_GUILD_BANK_MOVE_STACK_RES"), TRUE );
		return;
	}

	GetIconMoveManager()->IconMoveEnd();

	CNtlSLEventGenerator::GuildWarehouseItemStackMove(pResult->hSrcItem, pResult->hDestItem,
		pResult->bySrcPlace, pResult->bySrcPos, pResult->byDestPlace, pResult->byDestPos,
		pResult->byStackCount1, pResult->byStackCount2);
}

void PacketHandler_GSGuild_WarehouseZenny_Res(void* pPacket)
{
	// ��� â���� ���ϸ� �����Ѵ�
	API_GetSLPacketLockManager()->Unlock(GU_GUILD_BANK_ZENNY_RES);

	sGU_GUILD_BANK_ZENNY_RES* pResult = (sGU_GUILD_BANK_ZENNY_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_GUILD_BANK_ZENNY_RES"), TRUE );
		return;
	}

	GetIconMoveManager()->IconMoveEnd();

	if( pResult->bIsSave )
	{
		// %d ���ϸ� �����Ͽ����ϴ�
		GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_WAREHOUSE_SAVE_ZENNY", FALSE, NULL, Logic_FormatZeni(pResult->dwZenny));

		CNtlSLEventGenerator::GuildWarehouseEvent(GUILD_WAREHOUSE_EVENT_ADD_ZENNY, pResult->dwZenny);
	}
	else
	{
		// %d ���ϸ� ����Ͽ����ϴ�
		GetAlarmManager()->FormattedAlarmMessage("DST_GUILD_WAREHOUSE_ZENNY_DRAW_OUT", FALSE, NULL, Logic_FormatZeni(pResult->dwZenny));

		CNtlSLEventGenerator::GuildWarehouseEvent(GUILD_WAREHOUSE_EVENT_SUB_ZENNY, pResult->dwZenny);
	}
}

void PacketHandler_GSGuild_WarehouseZennyInfo(void* pPacket)
{
	// ��� â���� ���� ������ �޾Ҵ�
	sGU_GUILD_BANK_ZENNY_INFO* pResult = (sGU_GUILD_BANK_ZENNY_INFO*)pPacket;

	CNtlSLEventGenerator::GuildWarehouseEvent(GUILD_WAREHOUSE_EVENT_SET_ZENNY, pResult->dwZenny);
}

void PacketHandler_GSGuild_WarehouseItemInfo(void* pPacket)
{
	// ��� â���� ������ ������ �޾Ҵ�
	sGU_GUILD_BANK_ITEM_INFO* pResult = (sGU_GUILD_BANK_ITEM_INFO*)pPacket;

	CNtlSLEventGenerator::GuildWarehouseItemInfo(pResult->byPlace, pResult->byItemCount, (VOID*)&pResult->aItemProfile);
}

void PacketHandler_GSGuild_WarehouseEnd_Res(void* pPacket)
{
	// ��� â�� �ݾҴ�
	API_GetSLPacketLockManager()->Unlock(GU_GUILD_BANK_END_RES);

	sGU_GUILD_BANK_END_RES* pResult = (sGU_GUILD_BANK_END_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_GUILD_BANK_END_RES"), TRUE );
		return;
	}

	CNtlSLEventGenerator::GuildWarehouseEvent(GUILD_WAREHOUSE_EVENT_END);
}

void PacketHandler_TUGuild_Reputation_Change_Nfy(void* pPacket)
{
	// ����� ���� ����Ǿ���
	sTU_GUILD_REPUTATION_CHANGE_NFY* pResult = (sTU_GUILD_REPUTATION_CHANGE_NFY*)pPacket;

	CNtlSLEventGenerator::SLGuildEvent(SLGE_CHANGE_REPUTATION, INVALID_DWORD, (VOID*)&pResult->dwReputation, (VOID*)&pResult->dwMaxGuildPointEver);
}

void PacketHandler_TUGuild_ChangeNotice_Res(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock(TU_GUILD_CHANGE_NOTICE_RES);

	// ��� ������ ����Ǿ����� ������ ������ ������� �˸���
	sTU_GUILD_CHANGE_NOTICE_RES* pResult = (sTU_GUILD_CHANGE_NOTICE_RES*)pPacket;

	if( pResult->wResultCode != CHAT_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "TU_GUILD_CHANGE_NOTICE_RES"), TRUE );
		CDboEventGenerator::DialogPostEvent(DIALOGEVENT_FAIL_CLOSE_GUILD_NOTICE);
		return;
	}

	CDboEventGenerator::DialogPostEvent(DIALOGEVENT_CLOSE_GUILD_NOTICE);

	// ��� ������ �߼��Ͽ����ϴ�
	GetAlarmManager()->AlarmMessage("DST_GUILD_CHANGED_GUILD_NOTICE_SUCCESS");
}

void PacketHandler_TUGuild_changeNotice_Nfy(void* pPacket)
{
	// ��� ������ ����Ǿ����� �������� �˸���
	sTU_GUILD_CHANGE_NOTICE_NFY* pResult = (sTU_GUILD_CHANGE_NOTICE_NFY*)pPacket;

	CNtlSLEventGenerator::SLGuildEvent(SLGE_NOTICE, pResult->wNoticeLengthInUnicode, 
										pResult->awchCharName,
										pResult->awchNotice);

	CNtlGuild* pGuild = GetNtlSLGlobal()->GetSobAvatar()->GetGuild();
	if( pGuild->IsHaveGroup() )
	{
		// ���ο� ��� ������ �ֽ��ϴ�
		GetAlarmManager()->AlarmMessage("DST_GUILD_CHANGED_GUILD_NOTICE");
	}	
}

void PacketHandler_GSGuild_Create_Emblem_Res(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock(GU_GUILD_CREATE_MARK_RES);

	// ��� ������ �����Ͽ���
	sGU_GUILD_CREATE_MARK_RES* pResult = (sGU_GUILD_CREATE_MARK_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_GUILD_CREATE_MARK_RES"), TRUE );
		CDboEventGenerator::DialogPostEvent(DIALOGEVENT_FAIL_CLOSE_EMBLEM_MAKER);
		return;
	}

	CDboEventGenerator::DialogPostEvent(DIALOGEVENT_CLOSE_EMBLEM_MAKER);

	// ��� ������ �����Ǿ����ϴ�
	GetAlarmManager()->AlarmMessage("DST_GUILD_CREATE_GUILD_EMBLEM");	
}

void PacketHandler_GSGuild_Change_Emblem_Res(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock(GU_GUILD_CHANGE_MARK_RES);

	// ��� ������ �����Ͽ���
	sGU_GUILD_CHANGE_MARK_RES* pResult = (sGU_GUILD_CHANGE_MARK_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_GUILD_CHANGE_MARK_RES"), TRUE );
		CDboEventGenerator::DialogPostEvent(DIALOGEVENT_FAIL_CLOSE_EMBLEM_MAKER);
		return;
	}

	CDboEventGenerator::DialogPostEvent(DIALOGEVENT_CLOSE_EMBLEM_MAKER);

	// ��� ������ ����Ǿ����ϴ�
	GetAlarmManager()->AlarmMessage("DST_GUILD_CHANGE_GUILD_EMBLEM");	
}

void PacketHandler_GSGuild_Change_Emblem_Nfy(void* pPacket)
{
	sGU_GUILD_MARK_CHANGED_NFY* pResult = (sGU_GUILD_MARK_CHANGED_NFY*)pPacket;

	CNtlSLEventGenerator::ChangeGuildEmblem(pResult->hSubject,
											pResult->sMark.byMarkMain, pResult->sMark.byMarkMainColor,
											pResult->sMark.byMarkInLine, pResult->sMark.byMarkInColor,
											pResult->sMark.byMarkOutLine, pResult->sMark.byMarkOutColor);

	CNtlGuild* pGuild = GetNtlSLGlobal()->GetSobAvatar()->GetGuild();
	if( pGuild->IsHaveGroup() )
	{
		// ������ ��Ŷ ������ �� ������ ���´�
		/*
		if( pGuild->IsHaveEmblem() )
			// ��� ������ ����Ǿ����ϴ�
			GetAlarmManager()->AlarmMessage(DST_GUILD_CHANGE_GUILD_EMBLEM);	
		else
			// ��� ������ �����Ǿ����ϴ�
			GetAlarmManager()->AlarmMessage(DST_GUILD_CREATE_GUILD_EMBLEM);	
			*/

		CNtlSLEventGenerator::NotifyGuildEvent(SLGE_CHANGE_GUILD_EMBLEM);
	}
}


//////////////////////////////////////////////////////////////////////////
//								�� ��									//
//////////////////////////////////////////////////////////////////////////

void PacketHandler_GSDojo_CreateRes(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock(GU_DOJO_CREATE_RES);

	Logic_CancelNpcFacing();

	// ������ �����Ͽ����� �����忡�� �˸���
	sGU_DOJO_CREATE_RES* pResult = (sGU_DOJO_CREATE_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_DOJO_CREATE_RES"), TRUE );
		return;
	}
}

void PacketHandler_TUDojo_CreateNfy(void* pPacket)
{
	// ������ ���������� ��� ���Ŀ����� �˸���
	//sTU_DOJO_CREATED_NFY* pResult = (sTU_DOJO_CREATED_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;

	CNtlGuild* pGuild = pAvatar->GetGuild();
	GetAlarmManager()->FormattedAlarmMessage("DST_DOJO_SUCCESS_ESTABLISHMENT", FALSE, NULL, pGuild->GetGuildName() );


	// ������ ������ ���� ���� ������ �ִٸ� �����Ѵ�
	RwUInt8 byColorIndex = pGuild->GetDojoDogiColorIndex();
	if( INVALID_BYTE == byColorIndex )
		return;

	Logic_SetDogiItemColor(pAvatar, byColorIndex);

	CNtlSobGroup* pSobGroup = GetNtlSobManager()->GetSobGroup( SLCLASS_PLAYER );
	if( pSobGroup )
	{					
		COMMUNITY_ITER	it_Begin	= pGuild->Begin();
		COMMUNITY_ITER	it_End		= pGuild->End();

		for( ; it_Begin != it_End ; ++it_Begin )
		{
			sGuildMember* pGuildMember = reinterpret_cast<sGuildMember*>( *it_Begin );
			CNtlSobGroup::MapObject::iterator it;

			for( it = pSobGroup->GetObjects().begin() ; it != pSobGroup->GetObjects().end() ; ++it )
			{
				CNtlSobPlayer* pSobPlayer = reinterpret_cast<CNtlSobPlayer*>( it->second );

				if( pSobPlayer->GetCharID() == pGuildMember->charID )
				{
					// ���� ����
					Logic_SetDogiItemColor(pSobPlayer, byColorIndex);
					break;
				}
			}
		}
	}
}

void PacketHandler_TUDojo_DestoryNfy(void* pPacket)
{
	// ���ĸ� ��ü�Ͽ� ������ �������� �Ҿ�������� ��� ���Ŀ����� �˸���
	sTU_DOJO_DESTROYED_NFY* pResult = (sTU_DOJO_DESTROYED_NFY*)pPacket;

	sDOJO_TBLDAT* pDOJO_TBLDAT = reinterpret_cast<sDOJO_TBLDAT*>( API_GetTableContainer()->GetDojoTable()->FindData(pResult->dojoTblidx) );
	if(!pDOJO_TBLDAT)
	{
		DBO_FAIL("Not exist dojo table of index : " << pResult->dojoTblidx);
		return;
	}

	GetAlarmManager()->AlarmMessage("DST_DOJO_LOST_DOJO");

	CNtlSLEventGenerator::DojoEvent(DOJO_EVENT_LOST_DOJO, pResult->dojoTblidx);

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;

	CNtlGuild* pGuild = pAvatar->GetGuild();

	// ������ ������ ���� ���� ������ �ִٸ� �����Ѵ�
	RwUInt8 byColorIndex = pGuild->GetGuildDogiColorIndex();
	if( INVALID_BYTE == byColorIndex )
		return;

	Logic_SetDogiItemColor(pAvatar, byColorIndex);

	CNtlSobGroup* pSobGroup = GetNtlSobManager()->GetSobGroup( SLCLASS_PLAYER );
	if( pSobGroup )
	{					
		COMMUNITY_ITER	it_Begin	= pGuild->Begin();
		COMMUNITY_ITER	it_End		= pGuild->End();

		for( ; it_Begin != it_End ; ++it_Begin )
		{
			sGuildMember* pGuildMember = reinterpret_cast<sGuildMember*>( *it_Begin );
			CNtlSobGroup::MapObject::iterator it;

			for( it = pSobGroup->GetObjects().begin() ; it != pSobGroup->GetObjects().end() ; ++it )
			{
				CNtlSobPlayer* pSobPlayer = reinterpret_cast<CNtlSobPlayer*>( it->second );

				if( pSobPlayer->GetCharID() == pGuildMember->charID )
				{
					// ���� ����
					Logic_SetDogiItemColor(pSobPlayer, byColorIndex);
					break;
				}
			}
		}
	}
}

void PacketHandler_GSDojo_FunctionAddRes(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock(GU_DOJO_FUNCTION_ADD_RES);

	// ���� ����� �߰��Ͽ����� �����忡�� �˸���
	sGU_DOJO_FUNCTION_ADD_RES* pResult = (sGU_DOJO_FUNCTION_ADD_RES*)pPacket;

	switch( pResult->byFunction )
	{
//	case DBO_GUILD_FUNCTION_DOJO_UPGRADE_1:
	case DBO_GUILD_FUNCTION_DOJO_UPGRADE_2:
	case DBO_GUILD_FUNCTION_DOJO_UPGRADE_3:
	case DBO_GUILD_FUNCTION_DOJO_UPGRADE_4:
	case DBO_GUILD_FUNCTION_DOJO_UPGRADE_5:
	case DBO_GUILD_FUNCTION_DOJO_UPGRADE_6:
	case DBO_GUILD_FUNCTION_DOJO_UPGRADE_7:
		{
			break;
		}
	default:
		{
		Logic_CancelNpcFacing();
			break;
		}
	}

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_DOJO_FUNCTION_ADD_RES"), TRUE );
		return;
	}

	// ���� ��� ����� �޼����� �����ִ� ��Ŷ : PacketHandler_TUGuild_FunctionChange_Nfy
}

void PacketHandler_GSDojo_LevelChangedNfy(void* pPacket)
{
	// �������� ���� ������ ����Ǿ����� �˸���
	sGU_DOJO_LEVEL_CHANGED_NFY* pResult = (sGU_DOJO_LEVEL_CHANGED_NFY*)pPacket;

	CNtlSLEventGenerator::DojoEvent(DOJO_EVENT_CHANGE_LEVEL, pResult->dojoTblidx, (VOID*)&pResult->byLevel);

	{
		CNtlPLVisualManager* pVisualMng = (CNtlPLVisualManager*)GetSceneManager();

		if ( GAMERULE_DOJO == Logic_GetActiveWorldRuleType() )
		{
			pVisualMng->GetDojoContainer()->SetDojoWorld_Level( pResult->byLevel );
			pVisualMng->GetDojoContainer()->RefreshDojo();
		}
		else
		{
			pVisualMng->GetDojoContainer()->SetDojo_Level( pResult->dojoTblidx, pResult->byLevel );
			pVisualMng->GetDojoContainer()->RefreshDojo();
		}
	}
}

void PacketHandler_GSDojo_MarkChangedNfy(void* pPacket)
{
	// �������� ���忡 �ٿ��ִ� ���� ������ ����Ǿ����� �˸���
	sGU_DOJO_MARK_CHANGED_NFY* pResult = (sGU_DOJO_MARK_CHANGED_NFY*)pPacket;

	{
		CNtlPLVisualManager* pVisualMng = (CNtlPLVisualManager*)GetSceneManager();

		sEmblemFactor sEmFactor;

		sEmFactor.byTypeA		= pResult->sMark.byMarkMain;
		sEmFactor.byTypeB		= pResult->sMark.byMarkInLine;
		sEmFactor.byTypeC		= pResult->sMark.byMarkOutLine;

		sEmFactor.byTypeAColor	= pResult->sMark.byMarkMainColor;
		sEmFactor.byTypeBColor	= pResult->sMark.byMarkInColor;
		sEmFactor.byTypeCColor	= pResult->sMark.byMarkOutColor;

		if ( GAMERULE_DOJO == Logic_GetActiveWorldRuleType() )
		{
			pVisualMng->GetDojoContainer()->SetDojoWorld_Emblem( &sEmFactor );
			pVisualMng->GetDojoContainer()->RefreshDojo();
		}
		else
		{
			pVisualMng->GetDojoContainer()->SetDojo_Emblem( pResult->dojoTblidx, &sEmFactor );
			pVisualMng->GetDojoContainer()->RefreshDojo();
		}
	}
}

void PacketHandler_GSDojo_ScrambleRes(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock(GU_DOJO_SCRAMBLE_RES);

	// ��Ż���� ��û�� ��� �����Ϳ��� ����
	sGU_DOJO_SCRAMBLE_RES* pResult = (sGU_DOJO_SCRAMBLE_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_DOJO_SCRAMBLE_RES"), TRUE );
		return;
	}

	GetAlarmManager()->AlarmMessage("DST_DOJO_ASK_SCRAMBLE");
}

void PacketHandler_TUDojo_ScrambleNfy(void* pPacket)
{
	// ��Ż���� ��û���� ��� �����Ϳ��� ��Ż�� ���� ���θ� �����
	sTU_DOJO_SCRAMBLE_NFY* pResult = (sTU_DOJO_SCRAMBLE_NFY*)pPacket;

	GetAlarmManager()->FormattedAlarmMessage("DST_DOJO_SCRAMBLE_ACCEPT_CHALLENGE", FALSE, NULL, pResult->wszName, DBO_DOJO_SCRAMBLE_REJECT_FARE);
}

void PacketHandler_TUDojo_ScrambleReceiveNfy(void* pPacket)
{
	// ��Ż���� ��û�� ��� �����Ϳ��� ��Ż�� ��û�� ���� ��� �������� ���� ����� �˸���
	sTU_DOJO_SCRAMBLE_RECEIVE_NFY* pResult = (sTU_DOJO_SCRAMBLE_RECEIVE_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;

	CNtlDojo* pDojo = pAvatar->GetDojo();
	sDOJO_INFO* pDOJO_INFO = pDojo->GetDojoInfo( pResult->dojoTblidx );

	if( !pDOJO_INFO )
	{
		DBO_FAIL("Invalid dojo info of dojo table index : " << pResult->dojoTblidx);
		return;
	}

	GetAlarmManager()->AlarmMessage("DST_DOJO_ACCEPTED_SCRAMBLE");

	CNtlSLEventGenerator::DojoEvent(DOJO_EVENT_SCRAMBLE_ACCEPT, pResult->dojoTblidx, (VOID*)&pResult->guildId);
}

void PacketHandler_TUDojo_ScrambleReceiveInfoNfy(void* pPacket)
{
	// ��Ż���� �����ϴ� ������ ��� ���Ŀ����� ��Ż�� �⺻ ������ �޾Ҵ�
	sTU_DOJO_SCRAMBLE_RECEIVE_INFO_NFY* pResult = (sTU_DOJO_SCRAMBLE_RECEIVE_INFO_NFY*)pPacket;

	CNtlSLEventGenerator::ScrambleDefaultInfo(pResult->dojoTblidx, pResult->defGuildId, pResult->attGuildId,
											  pResult->wszDefGuildName, pResult->wszAttGuildName,
											  (VOID*)&pResult->sDefMark, (VOID*)&pResult->sAttMark);
}

void PacketHandler_GSDojo_ScrambleResponseRes(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock(GU_DOJO_SCRAMBLE_RESPONSE_RES);

	// ��Ż���� ��û���� ��� �����Ͱ� ����� ���
	sGU_DOJO_SCRAMBLE_RESPONSE_RES* pResult = (sGU_DOJO_SCRAMBLE_RESPONSE_RES*)pPacket;

	if( pResult->bIsRetry )
	{
		GetAlarmManager()->FormattedAlarmMessage("DST_DOJO_SCRAMBLE_ACCEPT_CHALLENGE", FALSE, NULL, pResult->wszGuildName, DBO_DOJO_SCRAMBLE_REJECT_FARE);
	}

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_DOJO_SCRAMBLE_RESPONSE_RES"), TRUE );
		return;
	}
}

void PacketHandler_GSDojo_NPCInfoRes(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock(GU_DOJO_NPC_INFO_RES);

	// ���� ����â�� ������ �޾Ҵ�
	sGU_DOJO_NPC_INFO_RES* pResult = (sGU_DOJO_NPC_INFO_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_DOJO_NPC_INFO_RES"), TRUE );
		return;
	}

	CNtlSLEventGenerator::DojoEvent(DOJO_EVENT_NPC_GUI_INFO, pResult->sData.dojoTblidx, (VOID*)&pResult->sData);
}

void PacketHandler_GSDojo_SealCurrentStateNfy(void* pPacket)
{
	// ���� ��Ż�� ���Խ� �ʱ� ���� ������ �޴´�
	sGU_DOJO_SEAL_CURRENT_STATE_NFY* pResult = (sGU_DOJO_SEAL_CURRENT_STATE_NFY*)pPacket;

	if( GetNtlWorldConcept()->IsActivePlayConcept(WORLD_PLAY_DOJO_SCRAMBLE) )
	{
		CNtlSLEventGenerator::DojoEvent(DOJO_EVENT_SEAL_ATTACK_STATE, pResult->sealObjectTblidx,
									(VOID*)&pResult->byState, (VOID*)&pResult->vLoc);
}
}

void PacketHandler_GSDojo_SealAttackBeginNfy(void* pPacket)
{
	// ���� ��Ż���� ������ ���� ���� ĳ������ �����Ѵ�
	sGU_DOJO_SEAL_ATTACK_BEGIN_NFY* pResult = (sGU_DOJO_SEAL_ATTACK_BEGIN_NFY*)pPacket;

	if( GetNtlWorldConcept()->IsActivePlayConcept(WORLD_PLAY_DOJO_SCRAMBLE) )
	{
		CNtlSLEventGenerator::DojoEvent(DOJO_EVENT_SEAL_ATTACK_BEGIN, pResult->sealObjectTblidx,
										  (VOID*)&pResult->bIsBeingStolen, (VOID*)&pResult->vLoc);
}
}

void PacketHandler_GSDojo_SealAttackEndNfy(void* pPacket)
{
	// ���� ��Ż���� ������ ���� ���� ĳ������ �����Ѵ�.
	sGU_DOJO_SEAL_ATTACK_END_NFY* pResult = (sGU_DOJO_SEAL_ATTACK_END_NFY*)pPacket;

	if( GetNtlWorldConcept()->IsActivePlayConcept(WORLD_PLAY_DOJO_SCRAMBLE) )
	{
		CNtlSLEventGenerator::DojoEvent(DOJO_EVENT_SEAL_ATTACK_END, pResult->sealObjectTblidx);
	}
}

void PacketHandler_GSDojo_ScrambleShiftStateNfy(void* pPacket)
{
	// ���� ��Ż���� ������ ���°� ����Ǿ����� ��/�� ���Ŀ����� �˸���
	sGU_DOJO_SCRAMBLE_SHIFT_SEAL_STATE_NFY* pResult = (sGU_DOJO_SCRAMBLE_SHIFT_SEAL_STATE_NFY*)pPacket;

	if( FALSE == GetNtlWorldConcept()->IsActivePlayConcept(WORLD_PLAY_DOJO_SCRAMBLE) )
		return;


	CNtlSLEventGenerator::DojoEvent(DOJO_EVENT_SCRAMBLE_CHANGE_SEAL_OWNER, pResult->dojoTblidx, (VOID*)&pResult->objectTblidx, (VOID*)&pResult->guildId);


	CObjectTable* pObjectTable = API_GetTableContainer()->GetObjectTable( Logic_GetActiveWorldId() );
	if( pObjectTable == NULL )
	{
		DBO_FAIL("Not exist obejct table of world ID : " << Logic_GetActiveWorldId());
		return;
	}

	sOBJECT_TBLDAT* pOBJECT_TBLDAT		= reinterpret_cast<sOBJECT_TBLDAT*>( pObjectTable->FindData(pResult->objectTblidx) );
	if( pOBJECT_TBLDAT )
	{
		CTextTable* pObjectTextTable	= API_GetTableContainer()->GetTextAllTable()->GetObjectTbl();
		std::wstring wstrText			= pObjectTextTable->GetText(pOBJECT_TBLDAT->dwName);
		const WCHAR* pwcText			= GetDisplayStringManager()->GetString("DST_DOJO_SCRAMBLE_CHANGE_SEAL_OWNER");
		if( pwcText )
		{
			GetAlarmManager()->FormattedAlarmMessage("DST_DOJO_SCRAMBLE_CHANGE_SEAL_OWNER", FALSE, NULL, pResult->wszName, wstrText.c_str());
		}		
	}	
}

void PacketHandler_TUDojo_BriefNfy(void* pPacket)
{
	// (������ ��� ��������)���� ������ �޾Ҵ�
	sTU_DOJO_BRIEF_NFY* pResult = (sTU_DOJO_BRIEF_NFY*)pPacket;

	CNtlSLEventGenerator::DojoEvent(DOJO_EVENT_DOJO_INFO, 0xffffffff, (VOID*)&pResult->sDojoData);
}

void PacketHandler_TUDojo_ScrambleRejectNfy(void* pPacket)
{
	// ��Ż���� ��û�� ��� �����Ϳ��� ������������ �˸���
	//sTU_DOJO_SCRAMBLE_REJECT_NFY* pResult = (sTU_DOJO_SCRAMBLE_REJECT_NFY*)pPacket;

	GetAlarmManager()->AlarmMessage("DST_DOJO_REJECT_SCRAMBLE");
}

void PacketHandler_TUDojo_ScrambleInformNfy(void* pPacket)
{
	// ��Ż���� ��û�� ��� �����Ϳ� ��Ż���� ��û���� ��� �����Ϳ���
	// ������ ���¿� ������ ������
	sTU_DOJO_SCRAMBLE_INFORM_NFY* pResult = (sTU_DOJO_SCRAMBLE_INFORM_NFY*)pPacket;
	CNtlSLEventGenerator::DojoState(pResult->dojoTblidx, pResult->byState, pResult->tmNextStepTime);
}

void PacketHandler_TUDojo_AddBudokaiSeedAddRes(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock(TU_DOJO_BUDOKAI_SEED_ADD_RES);

	// �ε�ī�� �õ� �����ڸ� �߰��� ����� �����忡�� �˸���
	sTU_DOJO_BUDOKAI_SEED_ADD_RES* pResult = (sTU_DOJO_BUDOKAI_SEED_ADD_RES*)pPacket;

	if( pResult->wResultCode != CHAT_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "TU_DOJO_BUDOKAI_SEED_ADD_RES"), TRUE );
		return;
	}

	CNtlSLEventGenerator::DojoEvent(DOJO_EVENT_CHANGE_TENKAI_SEED_PLAYER, pResult->dojoTblidx, (VOID*)pResult->wszCharName);
}

void PacketHandler_TUDojo_ScramblePointNfy(void* pPacket)
{
	// ���� ��Ż�� ������ ���Ŀ����� �˸���
	sTU_DOJO_SCRAMBLE_POINT_NFY* pResult = (sTU_DOJO_SCRAMBLE_POINT_NFY*)pPacket;

	CNtlSLEventGenerator::DojoEvent(DOJO_EVENT_SCRAMBLE_SCORE, pResult->sData.dojoTblidx, (VOID*)&pResult->sData);
}

void PacketHandler_TUDojo_NoticeChangeRes(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock(TU_DOJO_NOTICE_CHANGE_RES);

	// ���� ������ ������ ����� �����忡�� �˷��ش�
	sTU_DOJO_NOTICE_CHANGE_RES* pResult = (sTU_DOJO_NOTICE_CHANGE_RES*)pPacket;

	if( pResult->wResultCode != CHAT_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "TU_DOJO_NOTICE_CHANGE_RES"), TRUE );
		CDboEventGenerator::DialogPostEvent(DIALOGEVENT_FAIL_CLOSE_GUILD_NOTICE);
		return;
	}

	CDboEventGenerator::DialogPostEvent(DIALOGEVENT_CLOSE_GUILD_NOTICE);
}

void PacketHandler_TUDojo_NoticeChangeNfy(void* pPacket)
{
	// ���� ������ ����Ǿ����� �����忡�� �˸���
	// ��ȹ�� ����Ǿ� �ٸ� ����� ���� ������ ����Ǿ����� �˰� �� ���� �ִ�. �� �� ���� �۾� ���ʿ�
	sTU_DOJO_NOTICE_CHANGE_NFY* pResult = (sTU_DOJO_NOTICE_CHANGE_NFY*)pPacket;

	if( NTL_MAX_LENGTH_OF_GUILD_NOTICE < pResult->wNoticeLengthInUnicode )
		pResult->wNoticeLengthInUnicode = NTL_MAX_LENGTH_OF_GUILD_NOTICE;

	WCHAR acNotice[NTL_MAX_LENGTH_OF_GUILD_NOTICE + 1];
	ZeroMemory(acNotice, sizeof(acNotice));
	memcpy(acNotice, pResult->awchNotice, sizeof(WCHAR)*pResult->wNoticeLengthInUnicode);
	
	CNtlSLEventGenerator::DojoEvent(DOJO_EVENT_CHANGE_DOJO_NOTICE, pResult->dojoTblidx,
									(VOID*)pResult->awchCharName, (VOID*)acNotice);
}

void PacketHandler_TUDojo_ScrambleResultNfy(void* pPacket)
{
	// ���� ��Ż�� ����� ���Ŀ��鿡�� �˸���
	sTU_DOJO_SCRAMBLE_RESULT_NFY* pResult = (sTU_DOJO_SCRAMBLE_RESULT_NFY*)pPacket;

	CNtlSLEventGenerator::DojoEvent(DOJO_EVENT_SCRAMBLE_RESULT, pResult->winGuildId);
}

void PacketHandler_TUDojo_ScrambleRewardNfy(void* pPacket)
{
	// ���� ��Ż���� �̱� ���Ŀ��鿡�� ������ �˸���
	sTU_DOJO_SCRAMBLE_REWARD_NFY* pResult = (sTU_DOJO_SCRAMBLE_REWARD_NFY*)pPacket;

	CNtlSLEventGenerator::DojoEvent(DOJO_EVENT_SCRAMBLE_REWARD, pResult->dwAddGuildReputation,
									(VOID*)&pResult->itemTblidx, (VOID*)&pResult->byCount);	
}

//////////////////////////////////////////////////////////////////////////
//								�� ��									//
//////////////////////////////////////////////////////////////////////////

void PacketHandler_GSDogi_CreateRes(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock(GU_DOGI_CREATE_RES);

	// ���� ������ ��������� �����忡�� �˸���
	sGU_DOGI_CREATE_RES* pResult = (sGU_DOGI_CREATE_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_DOGI_CREATE_RES"), TRUE );
		return;
	}

	GetAlarmManager()->AlarmMessage("DST_DOGI_CHANGED");
	CNtlSLEventGenerator::SLGuildEvent(SLGE_DOGI);
}

void PacketHandler_GSDogi_ChangeRes(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock(GU_DOGI_CHANGE_RES);

	// ���� ������ ���������� �����忡�� �˸���
	sGU_DOGI_CHANGE_RES* pResult = (sGU_DOGI_CHANGE_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_DOGI_CHANGE_RES"), TRUE );
		return;
	}

	CNtlSLEventGenerator::SLGuildEvent(SLGE_DOGI);
}

void PacketHandler_GSDogi_UpdateNfy(void* pPacket)
{
	// � ������ ������ ��ȭ�� ������ �ֺ� �������� �˸���
	sGU_DOGI_UPDATE_NFY* pResult = (sGU_DOGI_UPDATE_NFY*)pPacket;

	if( Logic_GetAvatarHandle() == pResult->handle )
	{
		CNtlSobAvatar*	pAvatar			= GetNtlSLGlobal()->GetSobAvatar();
		CNtlGuild*		pGuild			= pAvatar->GetGuild();
		sDBO_DOGI_DATA&	rDBO_DOGI_DATA	= pResult->sData;

		if( pGuild->GetGuildID() == rDBO_DOGI_DATA.guildId )
		{
			CNtlSLEventGenerator::SLGuildEvent(SLGE_DOGI_NFY, INVALID_SERIAL_ID, (void*)&rDBO_DOGI_DATA);
		}
	}

	CNtlSobPlayer* pSobPlayer = reinterpret_cast<CNtlSobPlayer*>( GetNtlSobManager()->GetSobObject(pResult->handle) );
	if( !pSobPlayer )
	{
		DBO_FAIL("Not exist sob player of handle : " << pResult->handle);
		return;
	}

	pSobPlayer->SetGuildDogiColorIndex(pResult->sData.byGuildColor);
	pSobPlayer->SetDojoDogiColorIndex(pResult->sData.byDojoColor);
	Logic_SetDogiItemColor(pSobPlayer, pResult->sData.byGuildColor);		
}

void PacketHandler_GSGuildDogi_CreateRes(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock(GU_GUILD_DOGI_CREATE_RES);

	// ���� ������ ��������� �����忡�� �˸���
	sGU_GUILD_DOGI_CREATE_RES* pResult = (sGU_GUILD_DOGI_CREATE_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_GUILD_DOGI_CREATE_RES"), TRUE );
		return;
	}

	CNtlSLEventGenerator::SLGuildEvent(SLGE_DOGI);
}

void PacketHandler_GSGuildDogi_ChangeRes(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock(GU_GUILD_DOGI_CHANGE_RES);

	// ���� ������ ���������� �����忡�� �˸���
	sGU_GUILD_DOGI_CHANGE_RES* pResult = (sGU_GUILD_DOGI_CHANGE_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_GUILD_DOGI_CHANGE_RES"), TRUE );
		return;
	}

	CNtlSLEventGenerator::SLGuildEvent(SLGE_DOGI);
}
