/*****************************************************************************
*
* File			: NtlSLGuild.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2007. 4. 11	
* Abstract		: Simulation guild info class
*****************************************************************************
* Desc         : 
*
*****************************************************************************/

#ifndef __NTL_GUILD_INFO_H__
#define __NTL_GUILD_INFO_H__

// core
#include "ceventhandler.h"

// Share
#include "NtlGuild.h"

// simulation
#include "NtlSLCommunityGroup.h"

struct sGuildMember : public sCommunityMember
{
	CHARACTERID		charID;			///< DB character id	
	RwUInt32		uiWorldNameTable;	///< ���� �̸� ���̺� �ε���
	RwUInt8			byRace;			///< ����
	RwUInt8			byLevel;		///< ����
	RwUInt8			byClass;		///< Ŭ����	
	RwBool			bOnline;		///< ���� ���� ����
	RwUInt32        uiSerialID;     ///< �ø���ID (�ڵ�)
	RwUInt32		uiReputation;	///< ���� ����
	std::wstring	wstrArea;		///< ���� ��ġ �̸�
};

struct sGuildNotice
{
	WCHAR awcCharName[NTL_MAX_SIZE_CHAR_NAME + 1];
	WCHAR awcNotice[NTL_MAX_LENGTH_OF_GUILD_NOTICE + 1];
};

enum eGuildDataType
{
	COMMUNITY_GUILD_LEVEL	= COMMUNITY_DATA_NEXT_INDEX,
	COMMUNITY_GUILD_AREA,
};

enum eDOJO_TEAM_STATE
{
	DOJO_TEAM_NONE,
	DOJO_TEAM_SCRAMBLE_RESERV_OFFENCE,
	DOJO_TEAM_SCRAMBLE_RESERV_DEFENCE,
};

class CNtlGuild : public CNtlSLCommunityGroup, public RWS::CEventHandler
{
public:
	CNtlGuild();
	virtual ~CNtlGuild();	

	virtual	RwBool	Create(void);
	VOID			Destroy(void);
	VOID			Leave();

	virtual	void	HandleEvents(RWS::CMsg &pMsg);

	const WCHAR*	GetGuildName();							///< ��� �̸��� ��ȯ�Ѵ�

	GUILDID			GetGuildID();
	CHARACTERID		GetMasterID();							///< ��� ������ ID�� ��ȯ�Ѵ�
	CHARACTERID		GetSecondMasterID(RwInt32 iIndex);		///< ��� �θ����� ID�� ��ȯ�Ѵ�

	RwInt32			GetCountSecondMaster();					///< ��� �θ����� �ο����� ��ȯ�Ѵ�
	RwUInt32		GetReputation();						///< ��� �� ����Ʈ�� ��ȯ�Ѵ�
	RwUInt32		GetReputationEver();					///< ��� ���� ���� ����Ʈ�� ��ȯ�Ѵ�
	time_t			GetTimeToDisband();						///< ��尡 �ػ�Ǳ���� ���� �ð��� ��ȯ�Ѵ�	
	sGuildNotice*	GetNotice();							///< ���� �������� ��ȯ
	RwInt32			GetOnlineMemberCount();
	RwUInt8			GetGuildDogiColorIndex();
	RwUInt8			GetDojoDogiColorIndex();

	// Sort�� �����ϰ� ������ ������ GetMemberbyIndex()�� ���� �ɹ� ����ü�� �ٸ� �� �ִ�
	virtual VOID	Sort(RwUInt8 byDataType, RwBool bAscent);

	virtual RwBool	IsHaveGroup();
	RwBool			IsBeingDisband();						///< ��尡 �ػ�Ǳ����� ����
	RwBool			IsGuildMaster(CHARACTERID charID);		///< ��������� ����
	RwBool			IsSecondGuildMaster(CHARACTERID charID);///< �α�������� ����
	RwBool			IsHaveEmblem();							///< ��� ������ �ִ��� ����
	RwBool			IsChangedGuildDogiColor();
	RwBool			IsChangedDojoDogiColor();
	RwBool			IsExistFunction(eDBO_GUILD_FUNCTION eFunctionIndex);///< ��� ����� �����ϴ��� ����

	RwBool			CanGetGuildFunction(eDBO_GUILD_FUNCTION eFunctionIndex);	///< ��� ����� ���� �� �ִ��� ����
	RwBool			CanGetDojoFunction(eDBO_GUILD_FUNCTION eFunctionIndex);		///< ���� ����� ���� �� �ִ��� ����

	RwBool			EnableUIGuildFunction(eDBO_GUILD_FUNCTION eFunctionIndex);	///< ��� ��� �޴��� �� �� �ִ��� ����
	RwBool			EnableUIDojoFunction(eDBO_GUILD_FUNCTION eFunctionIndex);	///< ���� ��� �޴��� �� �� �ִ��� ����

protected:
	VOID			AppointSecondMaster(CHARACTERID charID);	///< �α�������� �Ӹ��Ѵ�
	VOID			DismissSecondMaster(CHARACTERID charID);	///< �α������ ������ �����Ѵ�

	VOID			ChangeAllMemberDogiColor(RwUInt8 byGuildDogiColor, RwUInt8 byDojoDogiColor);
	VOID			ChangeMemberDogiColor(CHARACTERID charID, RwUInt8 byGuildDogiColor, RwUInt8 byDojoDogiColor);

	static RwBool	CompareAscentLevel(sCommunityMember* pMember, sCommunityMember* pMember2)
	{
		if( !pMember || !pMember2 )
			return FALSE;

		return reinterpret_cast<sGuildMember*>( pMember )->byLevel < reinterpret_cast<sGuildMember*>( pMember2 )->byLevel;
	}
	static RwBool	CompareDecentLevel(sCommunityMember* pMember, sCommunityMember* pMember2)
	{
		if( !pMember || !pMember2 )
			return FALSE;

		return reinterpret_cast<sGuildMember*>( pMember )->byLevel > reinterpret_cast<sGuildMember*>( pMember2 )->byLevel;
	}
	static RwBool	CompareAscentArea(sCommunityMember* pMember, sCommunityMember* pMember2)
	{
		if( !pMember || !pMember2 )
			return FALSE;

		return (wcscmp(reinterpret_cast<sGuildMember*>( pMember )->wstrArea.c_str(),
					   reinterpret_cast<sGuildMember*>( pMember2 )->wstrArea.c_str()) < 0 );
	}
	static RwBool	CompareDecentArea(sCommunityMember* pMember, sCommunityMember* pMember2)
	{
		if( !pMember || !pMember2 )
			return FALSE;

		return (wcscmp(reinterpret_cast<sGuildMember*>( pMember )->wstrArea.c_str(),
					   reinterpret_cast<sGuildMember*>( pMember2 )->wstrArea.c_str()) > 0 );
	}

protected:
	WCHAR					m_wszGuildName[NTL_MAX_SIZE_GUILD_NAME+1];	///< ��� �̸�

	GUILDID					m_guildID;
	
	CHARACTERID				m_masterID;					///< ������ ID
	CHARACTERID				m_secondMasterID[DBO_MAX_SECOND_MASTER_IN_GUILD];///< �θ����� ID

	RwUInt32				m_uiReputation;				///< ��� ��
	RwUInt32				m_uiMaxReputationEver;		///< ��� �ִ� ���� �� ����Ʈ	
	time_t					m_timeToDisband;			///< ��尡 �ػ�Ǳ���� ���� �ð�

	RwInt32					m_iOnlineMember;

	RwUInt64				m_ui64Function;				///< ��� ���
	sGuildNotice			m_GuildNotice;				///< ��� ����

	RwUInt8					m_byGuildDogiColorIndex;	///< ���� ���� ����
	RwUInt8					m_byDojoDogiColorIndex;		///< ���� ���� ����
};

#endif