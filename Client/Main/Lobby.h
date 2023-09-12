/******************************************************************************
* File			: Lobby.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2009. 8. 6
* Abstract		: 
* Update		: 
*****************************************************************************
* Desc			: ���� �� ������������ �κ� �����͸� �����Ѵ�
*****************************************************************************/

#pragma once

// share
#include "NtlCharacter.h"
#include "NtlCSArchitecture.h"


struct sDBO_GAME_SERVER_FARM_INFO;
struct sDBO_GAME_SERVER_CHANNEL_INFO;
struct sDELETE_WAIT_CHARACTER_INFO;

typedef BYTE		SERVER_HANDLE;


struct sLOBBY_CHARACTER
{
	sPC_SUMMARY					tSummary;				///< ĳ���� ����
	RwBool						bReservatedDelete;		///< ���� ��� ����
	RwReal						fTime_util_Deletion;	///< �������� ���� �ð�

	sLOBBY_CHARACTER()
	:bReservatedDelete(FALSE)
	,fTime_util_Deletion(0.f)
	{
		tSummary.charId = INVALID_CHARACTERID;
	}
};


class CLobby
{
public:
	CLobby();
	virtual ~CLobby();

	RwBool				Create();
	VOID				Destroy();	


	// ����
	VOID				SetServerInfo(sDBO_GAME_SERVER_FARM_INFO* pServerInfo);
	VOID				RefreshServerInfo(eDBO_SERVER_STATUS eStatus, RwUInt32 uiUseRate);

	SERVER_HANDLE		GetServerHandle();
	WCHAR*				GetServerName();
	eDBO_SERVER_STATUS	GetServerStatus();
	RwUInt32			GetServerUseRate();

	// ä��
	VOID				SetChannelInfo(RwUInt8 byCount, sDBO_GAME_SERVER_CHANNEL_INFO* pChannelInfo);	
	VOID				SetSelectedChannelIndex(RwUInt8 byIndex);

	RwUInt8				GetSelectedChannelIndex();
	RwUInt8				GetChannelCount();
	sDBO_GAME_SERVER_CHANNEL_INFO*	GetChannel(RwUInt8 byIndex);

	// ������ ĳ����
	VOID				SetCharacterInfo(RwUInt8 byCount, sPC_SUMMARY* pPC_SUMMARY);
	VOID				SetDeletingCharcterInfo(sDELETE_WAIT_CHARACTER_INFO* pDELETE_WAIT_CHARACTER_INFO);

	RwBool				AddCharacter(sPC_SUMMARY* pSummary);
	RwUInt8				RemoveCharacter(CHARACTERID charID);		///< ���� ĳ������ ���� �ε����� ��ȯ, ������ �ʾҴٸ� INVALID_BYTE ��ȯ

	VOID				SetSelectedCharacterIndex(RwUInt8 byIndex);
	VOID				SetLoadedLastCharacter(RwBool bLoaded);
	VOID				SetReserveDeleteCharacter(CHARACTERID charID, RwReal fTime_util_Deletion);
	VOID				CancelDeleteCharacter(CHARACTERID charID);
	VOID				Rename(CHARACTERID charID, const WCHAR* pwcName);

	RwUInt8				GetSelectedCharacterIndex();
	RwUInt8				GetPostSelectedServerHandle();
	RwUInt8				GetCharacterCount();
	sLOBBY_CHARACTER*	GetCharacter(RwUInt8 byIndex);
	sLOBBY_CHARACTER*	GetCharacter(CHARACTERID charID);

	RwBool				IsLoadedLastCharacter();

protected:
	// server

	SERVER_HANDLE				hServer;
	WCHAR						awcServerName[NTL_MAX_SIZE_SERVER_FARM_NAME_UNICODE + 1];
	eDBO_SERVER_STATUS			eServerState;
	RwUInt32					uiUseRate;

	//channel

	RwUInt8						bySelectedChannelIndex;
	RwUInt8						byChannelCount;
	sDBO_GAME_SERVER_CHANNEL_INFO	atChannel[NTL_MAX_SERVER_CHANNEL_COUNT_IN_SERVER_FARM];

	// Character
	RwUInt8						m_bySelectedCharacterIndex;
	RwUInt8						byCharacterCount;
	sLOBBY_CHARACTER			atLobbyCharacter[NTL_MAX_COUNT_USER_CHAR_SLOT];
	RwBool						bSuccess_Loaded_Last_Used_Character;
	RwBool						bLoadedLastCharacter;				///< Whether or not you chose the last character you were previously connected to
};


inline SERVER_HANDLE CLobby::GetServerHandle()
{
	return hServer;
}

inline WCHAR* CLobby::GetServerName()
{
	return awcServerName;
}

inline eDBO_SERVER_STATUS CLobby::GetServerStatus()
{
	return eServerState;
}

inline RwUInt32 CLobby::GetServerUseRate()
{
	return uiUseRate;
}

inline VOID CLobby::SetSelectedChannelIndex(RwUInt8 byIndex)
{
	if( NTL_MAX_SERVER_CHANNEL_COUNT_IN_SERVER_FARM <= byIndex )
		return;

	bySelectedChannelIndex = byIndex;
}

inline RwUInt8 CLobby::GetSelectedChannelIndex()
{
	return bySelectedChannelIndex;
}

inline RwUInt8 CLobby::GetChannelCount()
{
	return byChannelCount;
}

inline sDBO_GAME_SERVER_CHANNEL_INFO* CLobby::GetChannel(RwUInt8 byIndex)
{
	if( NTL_MAX_SERVER_CHANNEL_COUNT_IN_SERVER_FARM <= byIndex )
		return NULL;

	return &(atChannel[byIndex]);
}

inline VOID CLobby::SetSelectedCharacterIndex(RwUInt8 byIndex)
{
	if( NTL_MAX_COUNT_USER_CHAR_SLOT <= byIndex )
		return;

	m_bySelectedCharacterIndex = byIndex;
}

inline VOID CLobby::SetLoadedLastCharacter(RwBool bLoaded)
{
	bLoadedLastCharacter = bLoaded;
}

inline RwUInt8 CLobby::GetSelectedCharacterIndex()
{
	return m_bySelectedCharacterIndex;
}

inline RwUInt8 CLobby::GetCharacterCount()
{
	return byCharacterCount;
}

inline sLOBBY_CHARACTER* CLobby::GetCharacter(RwUInt8 byIndex)
{
	if( NTL_MAX_COUNT_USER_CHAR_SLOT <= byIndex )
		return NULL;

	if( INVALID_CHARACTERID == atLobbyCharacter[byIndex].tSummary.charId )
		return NULL;

	return &(atLobbyCharacter[byIndex]);
}

inline RwBool CLobby::IsLoadedLastCharacter()
{
	return bLoadedLastCharacter;
}