/*****************************************************************************
* File			: DboPackethandler_GUParty.cpp
* Author		: Hong sungbock
* Copyright		: (��)NTL
* Date			: 2007. 1. 16
* Abstract		: ��Ƽ ���� ��Ŷ �ڵ�
*****************************************************************************
* Desc         : 
*****************************************************************************/

#include "precomp_dboclient.h"
#include "DboPacketHandler.h"

// shared
#include "ItemTable.h"

// sound
#include "GUISoundDefine.h"

// simulation
#include "NtlNetSender.h"
#include "NtlSLEventFunc.h"
#include "NtlSLPacketGenerator.h"

// dbo
#include "IconMoveManager.h"
#include "DiceManager.h"

void PacketHandler_GSPartyCreateRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_CREATE_RES );

	// �ڽ��� ��û�� ��Ƽ ���� ����� �˷��ش�.
	sGU_PARTY_CREATE_RES* pResult = (sGU_PARTY_CREATE_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_PARTY_CREATE_RES"), TRUE );
		return;
	}

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
	{
		DBO_FAIL("Not exist avatar instance");
		return;
	}

	CNtlSobAvatarAttr* pAvatarAttr = reinterpret_cast<CNtlSobAvatarAttr*>(pAvatar->GetSobAttr());

	// Create Party
	CNtlSLEventGenerator::PartyCreate(pResult->wszPartyName);

	// Add yourself to the party list
	CNtlSLEventGenerator::PartyMemberAdd(pAvatar->GetSerialID(), (WCHAR*)pAvatarAttr->GetName());

	// You are the party leader.
	CNtlSLEventGenerator::PartyLeaderChange(pAvatar->GetSerialID());

	// Zeni distribution system
	CNtlSLEventGenerator::PartyUpdate(PMT_ZENNY_DIVISION, INVALID_SERIAL_ID, NTL_PARTY_ZENNY_LOOTING_GREEDILY);

	// Item distribution method
	CNtlSLEventGenerator::PartyUpdate(PMT_ITEM_DIVISION, INVALID_SERIAL_ID, NTL_PARTY_ITEM_LOOTING_GREEDILY);

	// Party Quest
	CNtlSLEventGenerator::TSParty();
}

void PacketHandler_GSPartyDisbandRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_DISBAND_RES );

	// �ڽ��� ��Ƽ�� �ػ��� ����� �˷��ش�.
	sGU_PARTY_DISBAND_RES* pResult = (sGU_PARTY_DISBAND_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_PARTY_DISBAND_RES"), TRUE );
		return;
	}

	CNtlSLEventGenerator::PartyDisband();
}

void PacketHandler_GSPartyDisbandNfy(void *pPacket)
{
	// ��Ƽ�� �ػ�Ǿ����� ��Ƽ���� �ƴ� �ɹ��鿡�� �˷��ش�.
	//sGU_PARTY_DISBANDED_NFY* pResult = (sGU_PARTY_DISBANDED_NFY*)pPacket;

	CNtlSLEventGenerator::PartyDisband();
}

void PacketHandler_GSPartyInviteRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_INVITE_RES );

	// ��Ƽ �������� ��Ƽ �ʴ� ����� �˷��ش�.	
	sGU_PARTY_INVITE_RES* pResult = (sGU_PARTY_INVITE_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_PARTY_INVITE_RES"), TRUE );
		return;
	}	

	// %s���� ��Ƽ�� �ʴ��Ͽ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_PARTY_INVITE_SUCCESS", FALSE, NULL, pResult->wszTargetName);
}

void PacketHandler_GSPartyInviteNfy(void *pPacket)
{
	// �ʴ� ��󿡰� �޼����� ������.
	sGU_PARTY_INVITE_NFY* pResult = (sGU_PARTY_INVITE_NFY*)pPacket;

	if( wcslen(pResult->wszInvitorPcName) > 0)
	{
		GetAlarmManager()->FormattedAlarmMessage( "DST_PARTY_PARTY_INVITE", FALSE, NULL, pResult->wszInvitorPcName);
	}
}

void PacketHandler_GSPartyResponseInvitationRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_RESPONSE_INVITATION_RES );

	// ��Ƽ �ʴ��� ���信 ���� ����� �������� ������.
	sGU_PARTY_RESPONSE_INVITATION_RES* pResult = (sGU_PARTY_RESPONSE_INVITATION_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_PARTY_RESPONSE_INVITATION_RES"), TRUE );
		return;
	}	
}

void PacketHandler_GSPartyMemberJoinedNfy(void *pPacket)
{
	// ���ο� ��Ƽ���� ���������� �˷��ش�.
	sGU_PARTY_MEMBER_JOINED_NFY* pResult = (sGU_PARTY_MEMBER_JOINED_NFY*)pPacket;

	CNtlSLEventGenerator::PartyMemberAdd(pResult->memberInfo.hHandle, pResult->memberInfo.awchMemberName,
		pResult->memberInfo.byRace, pResult->memberInfo.byClass, pResult->memberInfo.byLevel,
		pResult->memberInfo.curLp, pResult->memberInfo.maxLp, pResult->memberInfo.wCurEP,
		pResult->memberInfo.wMaxEP, pResult->memberInfo.worldTblidx, pResult->memberInfo.worldId,
		pResult->memberInfo.vCurLoc.x, pResult->memberInfo.vCurLoc.y, pResult->memberInfo.vCurLoc.z);

	// %s���� ��Ƽ�� �����̽��ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_PARTY_NEW_MEMBER", FALSE, NULL, pResult->memberInfo.awchMemberName);
}

void PacketHandler_GSPartyInfo(void *pPacket)
{
	// ���� ������ ��Ƽ���� ��Ƽ������ �޴´�.
	sGU_PARTY_INFO* pResult = (sGU_PARTY_INFO*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
	{
		DBO_FAIL("Not exist avatar instance");
		return;
	}

	// ��Ƽ�� �����Ѵ�
	CNtlSLEventGenerator::PartyCreate(pResult->awchPartyName);

	for(RwInt32 i = 0 ; i < pResult->byMemberInfoCount ; ++i )
	{		
		CNtlSLEventGenerator::PartyMemberAdd(pResult->memberInfo[i].hHandle, pResult->memberInfo[i].awchMemberName,
			pResult->memberInfo[i].byRace, pResult->memberInfo[i].byClass,
			pResult->memberInfo[i].byLevel, pResult->memberInfo[i].curLp,
			pResult->memberInfo[i].maxLp, pResult->memberInfo[i].wCurEP,
			pResult->memberInfo[i].wMaxEP,
			pResult->memberInfo[i].worldTblidx, pResult->memberInfo[i].worldId,
			pResult->memberInfo[i].vCurLoc.x, pResult->memberInfo[i].vCurLoc.y, pResult->memberInfo[i].vCurLoc.z);
	}	

	// ��Ƽ ����Ʈ�� �ڽ��� �߰���Ų��	
	CNtlSobAvatarAttr* pAvatarAttr = reinterpret_cast<CNtlSobAvatarAttr*>(pAvatar->GetSobAttr());
	CNtlSLEventGenerator::PartyMemberAdd(pAvatar->GetSerialID(), (WCHAR*)pAvatarAttr->GetName());

	// ��Ƽ���� �����Ѵ�
	CNtlSLEventGenerator::PartyLeaderChange(pResult->hLeader);

	// ������ �й� ���
	CNtlSLEventGenerator::PartyUpdate(PMT_ITEM_DIVISION, INVALID_SERIAL_ID, pResult->byItemLootingMethod);

	// ���� �й� ���
	CNtlSLEventGenerator::PartyUpdate(PMT_ZENNY_DIVISION, INVALID_SERIAL_ID, pResult->byZennyLootingMethod);

    // ���� Ÿ�� ������    
    CNtlSLEventGenerator::PartyShareTargetNfy(pResult->sharetargetInfo);

	// ��Ƽ ���� ����
	CNtlSLEventGenerator::PartyUpdate(PMT_PARTY_DUNGEON_STATE, INVALID_SERIAL_ID, pResult->eDiff);	
}

void PacketHandler_GSPartyInviteDeclinedNfy(void *pPacket)
{
	// �ʴ��� ����� �����ߴ�.
	sGU_PARTY_INVITATION_DECLINED_NFY* pResult = (sGU_PARTY_INVITATION_DECLINED_NFY*)pPacket;	

	// %s���� �ʴ븦 �����Ͽ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_PARTY_INVITE_DECLINE", FALSE, NULL, pResult->wszPlayerName);
}

void PacketHandler_GSPartyInviteExpiredNfy(void *pPacket)
{
	// ��Ƽ �ʴ븦 ������ ���� �ð����� ������ ������.
	sGU_PARTY_INVITATION_EXPIRED_NFY* pResult = (sGU_PARTY_INVITATION_EXPIRED_NFY*)pPacket;

	// %s���� �ʴ븦 �����Ͽ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_PARTY_INVITE_DECLINE", FALSE, NULL, pResult->wszPlayerName);
}

void PacketHandler_GSPartyLeaveRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_LEAVE_RES );

	// �ڽ��� ��û�� ��Ƽ Ż���� ����� �˷��ش�.
	sGU_PARTY_LEAVE_RES* pResult = (sGU_PARTY_LEAVE_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_PARTY_LEAVE_RES"), TRUE );
		return;
	}

	CNtlSLEventGenerator::PartyLeaderChange(INVALID_HOBJECT); // required to turn char name color back to normal

	CNtlSLEventGenerator::PartyDisband();
}

void PacketHandler_GSPartyMemberLeftNfy(void *pPacket)
{
	// �ڽ��� ��Ƽ���� ������.
	sGU_PARTY_MEMBER_LEFT_NFY* pResult = (sGU_PARTY_MEMBER_LEFT_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
	{
		DBO_FAIL("Not exist avatar instance");
		return;
	}

	CNtlParty*		pParty	= pAvatar->GetParty();
	sPartyMember*	pMember = reinterpret_cast<sPartyMember*>( pParty->GetMemberbyKey(pResult->hMember) );
	if( !pMember )
	{
		DBO_FAIL("Not exist party member of handle : " << pResult->hMember);
		return;
	}

	WCHAR* pwcText	= pMember->wszMemberName;

	// %s���� ��Ƽ���� Ż���Ͽ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_PARTY_LEAVE", FALSE, NULL, pwcText);
	CNtlSLEventGenerator::PartyMemberDel(pResult->hMember);
}

void PacketHandler_GSPartyKickOutRes(void* pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_KICK_OUT_RES );

	// ��Ƽ �ɹ� ���� ���
	sGU_PARTY_KICK_OUT_RES* pResult = (sGU_PARTY_KICK_OUT_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_PARTY_KICK_OUT_RES"), TRUE );
		return;
	}

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
	{
		DBO_FAIL("Not exist avatar instance");
		return;
	}

	CNtlParty*		pParty	= pAvatar->GetParty();
	sPartyMember*	pMember = reinterpret_cast<sPartyMember*>( pParty->GetMemberbyKey(pResult->hTargetMember) );
	if( !pMember )
	{
		DBO_FAIL("Not exist party member of handle : " << pResult->hTargetMember);
		return;
	}

	WCHAR* pwcText = pMember->wszMemberName;

	// %s���� ��Ƽ���� Ż���Ͽ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_PARTY_LEAVE", FALSE, NULL, pwcText);
	CNtlSLEventGenerator::PartyMemberDel(pResult->hTargetMember);
}

void PacketHandler_GSPartyMemberKickedOutNfy(void *pPacket)
{
	// ��Ƽ �ɹ��� ����� ���� �����ִ� ��Ƽ������ �˷��ش�.
	sGU_PARTY_MEMBER_KICKED_OUT_NFY* pResult = (sGU_PARTY_MEMBER_KICKED_OUT_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
	{
		DBO_FAIL("Not exist avatar instance");
		return;
	}

	CNtlParty*		pParty	= pAvatar->GetParty();
	sPartyMember*	pMember = reinterpret_cast<sPartyMember*>( pParty->GetMemberbyKey(pResult->hMember) );
	if( !pMember )
	{
		DBO_FAIL("Not exist party member of handle : " << pResult->hMember);
		return;
	}

	WCHAR* pwcText = pMember->wszMemberName;

	// %s���� ��Ƽ���� Ż���Ͽ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_PARTY_LEAVE", FALSE, NULL, pwcText);
	CNtlSLEventGenerator::PartyMemberDel(pResult->hMember);
}

void PacketHandler_GSPartyChangeLeaderRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_CHANGE_LEADER_RES );

	// ��Ƽ �������� ���� ���� ��û�� ����� �˷��ش�.
	sGU_PARTY_CHANGE_LEADER_RES* pResult = (sGU_PARTY_CHANGE_LEADER_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_PARTY_CHANGE_LEADER_RES"), TRUE );
		return;
	}

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
	{
		DBO_FAIL("Not exist avatar instance");
		return;
	}

	CNtlParty*		pParty	= pAvatar->GetParty();
	sPartyMember*	pMember = reinterpret_cast<sPartyMember*>( pParty->GetMemberbyKey(pResult->hNewLeader) );
	if( !pMember )
	{
		DBO_FAIL("Not exist party member of handle : " << pResult->hNewLeader);
		return;
	}

	WCHAR* pwcText = pMember->wszMemberName;

	// %s���� ��Ƽ���� �Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_PARTY_CHANGE_LEADER", FALSE, NULL, pwcText);
	CNtlSLEventGenerator::PartyLeaderChange(pResult->hNewLeader);
}

void PacketHandler_GSPartyChangedLeaderNfy(void *pPacket)
{
	// ��Ƽ ������ ����Ǿ����� ��Ƽ �ɹ����� �˷��ش�
	sGU_PARTY_LEADER_CHANGED_NFY* pResult = (sGU_PARTY_LEADER_CHANGED_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
	{
		DBO_FAIL("Not exist avatar instance");
		return;
	}

	CNtlParty*		pParty	= pAvatar->GetParty();
	sPartyMember*	pMember = reinterpret_cast<sPartyMember*>( pParty->GetMemberbyKey(pResult->hNewLeader) );
	if( !pMember )
	{
		DBO_FAIL("Not exist party member of handle : " << pResult->hNewLeader);
		return;
	}	

	WCHAR* pwcText = pMember->wszMemberName;

	// %s���� ��Ƽ���� �Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_PARTY_CHANGE_LEADER", FALSE, NULL, pwcText);
	CNtlSLEventGenerator::PartyLeaderChange(pResult->hNewLeader);
}

void PacketHandler_GSPartyLevelUp(void* pPacket)
{
	// ��Ƽ���� �������� �Ͽ���
	sGU_PARTY_MEMBER_LEVELED_UP_NFY* pResult = (sGU_PARTY_MEMBER_LEVELED_UP_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
		return;

	CNtlParty*		pParty	= pAvatar->GetParty();
	sPartyMember*	pMember = reinterpret_cast<sPartyMember*>( pParty->GetMemberbyKey(pResult->hMember) );
	if( !pMember )
	{
		DBO_FAIL("Not exist party member of handle : " << pResult->hMember);
		return;
	}

	CNtlSLEventGenerator::PartyUpdate(PMT_LEVEL, pResult->hMember, pResult->byLevel);
	CNtlSLEventGenerator::PartyUpdate(PMT_LP, pResult->hMember, pMember->wCurLP, pResult->maxLp);
	CNtlSLEventGenerator::PartyUpdate(PMT_EP, pResult->hMember, pMember->wCurEP, pResult->wMaxEP);	
}

void PacketHandler_GSPartyChangeClass(void* pPacket)
{
	// ��Ƽ���� Ŭ������ �ٲ����
	sGU_PARTY_MEMBER_CLASS_CHANGED_NFY* pResult = (sGU_PARTY_MEMBER_CLASS_CHANGED_NFY*)pPacket;
	CNtlSLEventGenerator::PartyUpdate(PMT_CLASS, pResult->hMember, pResult->byNewClass);
}

void PacketHandler_GSPartyMember_LocationNfy(void* pPacket)
{
	// ��Ƽ �ɹ��� ��ġ�� ������Ʈ �Ѵ�
	sGU_PARTY_MEMBER_LOCATION_NFY* pResult = (sGU_PARTY_MEMBER_LOCATION_NFY*)pPacket;

	RwV3d vPos;
	NtlLocationDecompress(&pResult->vCompressLoc, &vPos.x, &vPos.y, &vPos.z);

	CNtlSLEventGenerator::PartyMemberLocation(pResult->hMember, pResult->worldId, pResult->worldTblidx, vPos);
}

void PacketHandler_GSPartyMemberGainedItemNfy(void *pPacket)
{
	// ��Ƽ �ɹ��� �������� ���� ���� �˷��ش�
	sGU_PARTY_MEMBER_GAINED_ITEM_NFY* pResult = (sGU_PARTY_MEMBER_GAINED_ITEM_NFY*)pPacket;

	CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
	if( !pAvatar )
	{
		DBO_FAIL("Not exist avatar instance");
		return;
	}

	CNtlParty*		pParty	= pAvatar->GetParty();
	sPartyMember*	pMember = reinterpret_cast<sPartyMember*>( pParty->GetMemberbyKey(pResult->hMember) );
	if( !pMember )
	{
		DBO_FAIL("Not exist party member of handle : " << pResult->hMember);
		return;
	}

	WCHAR* pwcText = pMember->wszMemberName;

	if(pResult->itemTblidx == INVALID_SERIAL_ID)
	{
		// %s���� ��Ȯ�� �������� ȹ���Ͽ����ϴ�
		GetAlarmManager()->FormattedAlarmMessage("DST_PARTY_INVEN_ADD_UNDEFINED_ITEM_OTHER", FALSE, NULL, pwcText);
	}
	else
	{
		// %s���� ȹ�� ������ %s
		sITEM_TBLDAT* pITEM_TBLDAT = Logic_GetItemDataFromTable(pResult->itemTblidx);
		if( !pITEM_TBLDAT )
		{
			DBO_FAIL("Not exist item table of index : " << pResult->itemTblidx);
			return;
		}

		memset((char*)awcPacketMessageBuffer, 0, sizeof(WCHAR) * dPACKET_MEESAGE_LENGTH);

		CTextTable* pItemTextTable = API_GetTableContainer()->GetTextAllTable()->GetItemTbl();
		std::wstring& strItemName = pItemTextTable->GetText(pITEM_TBLDAT->Name);		

		GetAlarmManager()->FormattedAlarmMessage("DST_PARTY_GET_ITEM", FALSE, NULL, pwcText, strItemName.c_str());
	}
}

void PacketHandler_GSPartyMemberGainedZennyNfy(void *pPacket)
{
	// ���ϸ� �й�޾Ҵٴ� �޼���
	sGU_PARTY_MEMBER_GAINED_ZENNY_NFY* pResult = (sGU_PARTY_MEMBER_GAINED_ZENNY_NFY*)pPacket;

	if( pResult->bIsShared )
	{
		// �ٸ� ��Ƽ���� ���ϸ� �־ �й�޾Ҵ�
		// %d�� %d ���ϸ� �й�޾ҽ��ϴ�
        if(pResult->dwBonusZenny == 0)
        {
		    GetAlarmManager()->FormattedAlarmMessage("DST_PARTY_GET_ZENNY", FALSE, NULL, Logic_FormatZeni(pResult->dwOriginalZenny), Logic_FormatZeni(pResult->dwZenny));
        }
        else    // PC�� �߰� ȹ��
        {
            GetAlarmManager()->FormattedAlarmMessage("DST_PARTY_GET_ZENNY_AND_BONUS", FALSE, NULL, Logic_FormatZeni(pResult->dwOriginalZenny), Logic_FormatZeni(pResult->dwAcquisitionZenny), Logic_FormatZeni(pResult->dwBonusZenny));
        }
	}
	else
	{
		// �ٸ� ��Ƽ���� ���ϸ� �־���
		CNtlSobAvatar* pAvatar = GetNtlSLGlobal()->GetSobAvatar();
		if( !pAvatar )
		{
			DBO_FAIL("Not exist avatar instance");
			return;
		}

		CNtlParty*		pParty	= pAvatar->GetParty();
		sPartyMember*	pMember = reinterpret_cast<sPartyMember*>( pParty->GetMemberbyKey(pResult->hMember) );
		if( !pMember )
		{
			DBO_FAIL("Not exist party member of handle : " << pResult->hMember);
			return;
		}

		// %s���� %d ���ϸ� ȹ���Ͽ����ϴ�
        if(pResult->dwBonusZenny == 0)
        {
		    GetAlarmManager()->FormattedAlarmMessage("DST_PARTY_GET_ZENNY_OTHER", FALSE, NULL, pMember->wszMemberName, Logic_FormatZeni(pResult->dwZenny));
        }
        else    // PC�� �߰� ȹ��
        {
            GetAlarmManager()->FormattedAlarmMessage("DST_PARTY_GET_ZENNY_OTHER_AND_BONUS", FALSE, NULL, pMember->wszMemberName, Logic_FormatZeni(pResult->dwAcquisitionZenny), Logic_FormatZeni(pResult->dwBonusZenny));
        }
	}
}

void PacketHandler_GSPartyChangeZennyLootinMethodRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_CHANGE_ZENNY_LOOTING_METHOD_RES );

	// ���� �й� ��� ���� ����� ��Ƽ�忡�� �˷��ش�
	sGU_PARTY_CHANGE_ZENNY_LOOTING_METHOD_RES* pResult = (sGU_PARTY_CHANGE_ZENNY_LOOTING_METHOD_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )	
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_PARTY_CHANGE_ZENNY_LOOTING_METHOD_RES"), TRUE );
		return;
	}

	CNtlSLEventGenerator::PartyUpdate(PMT_ZENNY_DIVISION, INVALID_SERIAL_ID, pResult->byNewLootingMethod);	

	// ���� �й����� %s�� ����Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_PARTY_CHANGE_ZENNY_DIVISION", FALSE, NULL, Logic_GetPartyZeniLootingMethod(pResult->byNewLootingMethod));
}

void PacketHandler_GSPartyZennyLootingMethodChangedNfy(void *pPacket)
{
	// ��Ƽ���� ������ �ɹ��鿡�� ���� �й� ��� ���� �˸���
	sGU_PARTY_ZENNY_LOOTING_METHOD_CHANGED_NFY* pResult = (sGU_PARTY_ZENNY_LOOTING_METHOD_CHANGED_NFY*)pPacket;

	CNtlSLEventGenerator::PartyUpdate(PMT_ZENNY_DIVISION, INVALID_SERIAL_ID, pResult->byNewLootingMethod);

	// ���� �й����� %s�� ����Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_PARTY_CHANGE_ZENNY_DIVISION", FALSE, NULL, Logic_GetPartyZeniLootingMethod(pResult->byNewLootingMethod));
}

void PacketHandler_GSPartyChangeItemLootinMethodRes(void *pPacket)
{
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_CHANGE_ITEM_LOOTING_METHOD_RES );

	// ������ �й� ��� ���� ����� ��Ƽ�忡�� �˷��ش�
	sGU_PARTY_CHANGE_ITEM_LOOTING_METHOD_RES* pResult = (sGU_PARTY_CHANGE_ITEM_LOOTING_METHOD_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_PARTY_CHANGE_ITEM_LOOTING_METHOD_RES"), TRUE );
		return;
	}

	CNtlSLEventGenerator::PartyUpdate(PMT_ITEM_DIVISION, INVALID_SERIAL_ID, pResult->byNewLootingMethod);

	// ������ �й����� %s�� ����Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_PARTY_CHANGE_ITEM_DIVISION", FALSE, NULL, Logic_GetPartyItemLootingMethod(pResult->byNewLootingMethod));
}

void PacketHandler_GSPartyItemLootingMethodChangedNfy(void *pPacket)
{
	// ��Ƽ���� ������ �ɹ��鿡�� ���� ������ �й� ��� ���� �˸���
	sGU_PARTY_ITEM_LOOTING_METHOD_CHANGED_NFY* pResult = (sGU_PARTY_ITEM_LOOTING_METHOD_CHANGED_NFY*)pPacket;

	CNtlSLEventGenerator::PartyUpdate(PMT_ITEM_DIVISION, INVALID_SERIAL_ID, pResult->byNewLootingMethod);

	// ������ �й����� %s�� ����Ǿ����ϴ�
	GetAlarmManager()->FormattedAlarmMessage("DST_PARTY_CHANGE_ITEM_DIVISION", FALSE, NULL, Logic_GetPartyItemLootingMethod(pResult->byNewLootingMethod));
}

// ��Ƽ ���� Ÿ�� ��û�� ���� ��� ��Ŷ
void PacketHandler_GSPartyShareTargetRes( void* pPacket ) 
{
    sGU_PARTY_SHARETARGET_RES* pData = (sGU_PARTY_SHARETARGET_RES*)pPacket;
    if( pData->wResultCode != GAME_SUCCESS )
    {
        GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pData->wResultCode, "GU_PARTY_SHARETARGET_RES"), TRUE );
        return;
    }

    CNtlSLEventGenerator::PartyShareTargetRes(pData->wResultCode);
}

// ��Ƽ ���� Ÿ�� ���ÿ� ���� �˸� ��Ŷ
void PacketHandler_GSPartyShareTargetNfy( void* pPacket ) 
{
    sGU_PARTY_SHARETARGET_NFY* pData = (sGU_PARTY_SHARETARGET_NFY*)pPacket;

    CNtlSLEventGenerator::PartyShareTargetNfy(pData->sharetargetInfo);
}

void PacketHandler_GSPartyDungeonDiffRes(void *pPacket)
{
	// ��Ƽ�忡�� ��Ƽ ������ ���̵� ���� ����� �˸���
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_DUNGEON_DIFF_RES );

	sGU_PARTY_DUNGEON_DIFF_RES* pResult = (sGU_PARTY_DUNGEON_DIFF_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_PARTY_DUNGEON_DIFF_RES"), TRUE );
		return;
	}

	CNtlSLEventGenerator::PartyUpdate(PMT_PARTY_DUNGEON_STATE, INVALID_SERIAL_ID, pResult->eDiff);	

	if (pResult->eDiff == PARTY_DUNGEON_STATE_NORMAL)
		GetAlarmManager()->AlarmMessage("DST_PARTY_DUNGEON_CHANGE_NORMAL");
	else if (pResult->eDiff == PARTY_DUNGEON_STATE_HARD)
		GetAlarmManager()->AlarmMessage("DST_PARTY_DUNGEON_CHANGE_HARD");
	else if (pResult->eDiff == PARTY_DUNGEON_STATE_LEGENDARY)
		GetAlarmManager()->AlarmMessage("DST_PARTY_DUNGEON_CHANGE_LEGENDARY");
	else if (pResult->eDiff == PARTY_DUNGEON_STATE_HERO)
		GetAlarmManager()->AlarmMessage("DST_PARTY_DUNGEON_CHANGE_HERO");
}

void PacketHandler_GSPartyDungeonDiffNfy(void *pPacket)
{
	// ��Ƽ���鿡�� ��Ƽ ���� ���̵� ������ �˸���
	sGU_PARTY_DUNGEON_DIFF_NFY* pResult = (sGU_PARTY_DUNGEON_DIFF_NFY*)pPacket;

	CNtlSLEventGenerator::PartyUpdate(PMT_PARTY_DUNGEON_STATE, INVALID_SERIAL_ID, pResult->eDiff);	
	
	if(pResult->eDiff == PARTY_DUNGEON_STATE_NORMAL)
		GetAlarmManager()->AlarmMessage("DST_PARTY_DUNGEON_CHANGE_NORMAL");
	else if (pResult->eDiff == PARTY_DUNGEON_STATE_HARD)
		GetAlarmManager()->AlarmMessage("DST_PARTY_DUNGEON_CHANGE_HARD");
	else if (pResult->eDiff == PARTY_DUNGEON_STATE_LEGENDARY)
		GetAlarmManager()->AlarmMessage("DST_PARTY_DUNGEON_CHANGE_LEGENDARY");
	else if (pResult->eDiff == PARTY_DUNGEON_STATE_HERO)
		GetAlarmManager()->AlarmMessage("DST_PARTY_DUNGEON_CHANGE_HERO");
}

void PacketHandler_GSPartyDungeonInitRes(void *pPacket)
{
	// ��Ƽ�忡�� ��Ƽ ���� �ʱ�ȭ ����� �˸���
	API_GetSLPacketLockManager()->Unlock( GU_PARTY_DUNGEON_INIT_RES );

	sGU_PARTY_DUNGEON_INIT_RES* pResult = (sGU_PARTY_DUNGEON_INIT_RES*)pPacket;

	if( pResult->wResultCode != GAME_SUCCESS )
	{
		GetAlarmManager()->AlarmMessage(Logic_GetResultCodeString(pResult->wResultCode, "GU_PARTY_DUNGEON_INIT_RES"), TRUE );
		return;
	}

	CNtlSLEventGenerator::PartyUpdate(PMT_PARTY_DUNGEON_INITIALIZE);

	GetAlarmManager()->AlarmMessage("DST_PARTY_DUNGEON_INITIALIZE");
}

void PacketHandler_GSPartyDungeonInitNfy(void *pPacket)
{
	// ��Ƽ������ ��Ƽ ���� �ʱ�ȭ�� �˸���
	//sGU_PARTY_DUNGEON_INIT_NFY* pResult = (sGU_PARTY_DUNGEON_INIT_NFY*)pPacket;

	GetAlarmManager()->AlarmMessage("DST_PARTY_DUNGEON_INITIALIZE");
}