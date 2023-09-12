#pragma once

#include "NtlSLCommunityGroup.h"
#include "ceventhandler.h"
#include "NtlSLEvent.h"

struct sFriendMember : public sCommunityMember
{
	CHARACTERID		charID;			///< DB character id
	RwUInt32		mapTblIdx;		///< �� ���̺� �ε���
	RwUInt8			byLevel;		///< ����
	RwUInt8			byClass;		///< Ŭ����	
	RwBool			bOnline;		///< ���� ���� ����
	RwUInt32        uiSerialID;     ///< �ø���ID (�ڵ�)
	RwUInt8			byChannel;      ///< ä��
};

enum FriendDataType
{
	COMMUNITY_FRIEND_LEVEL	= COMMUNITY_DATA_NEXT_INDEX,
	COMMUNITY_FRIEND_ONLINE,
};

/// ģ������Ʈ�� �����͸� �����ϴ� Ŭ����
/// by agebreak 2007.12.14
class CNtlSLFriendList : public CNtlSLCommunityGroup, public RWS::CEventHandler
{
public:
    CNtlSLFriendList(void);
    virtual ~CNtlSLFriendList(void);

    virtual	RwBool	Create();
    virtual VOID	Destroy();
    virtual VOID	Leave();
    virtual	void	HandleEvents(RWS::CMsg &pMsg);

	// Sort�� �����ϰ� ������ ������ GetMemberbyIndex()�� ���� �ɹ� ����ü�� �ٸ� �� �ִ�
	virtual VOID	Sort(RwUInt8 byDataType, RwBool bAscent);
    virtual RwBool	IsHaveGroup() {return TRUE;}

protected:
	VOID    OnFriendAddRes(SNtlEventFriendAddRes* pData);
	VOID    OnFriendDelRes(SNtlEventFriendDelRes* pData);
	VOID    OnFriendMoveRes(SNtlEventFriendMoveRes* pData);
	VOID    OnFriendListInfo(SNtlEventFriendListInfo* pData);
	VOID    OnFriendInfo(SNtlEventFriendInfo* pData);
	VOID    OnFriendInfoChange(SNtlEventFriendInfoChange* pData);
	void    OnFriendNameChange(SNtlEventChangeCharName* pData);

    static RwBool CompareAscentLevel(sCommunityMember* pMember1, sCommunityMember* pMember2);
    static RwBool CompareDecentLevel(sCommunityMember* pMember1, sCommunityMember* pMember2);
    static RwBool CompareAscentLoc(sCommunityMember* pMember1, sCommunityMember* pMember2);
    static RwBool CompareDecentLoc(sCommunityMember* pMember1, sCommunityMember* pMember2);
    static RwBool CompareAscentChannel(sCommunityMember* pMember1, sCommunityMember* pMember2);
    static RwBool CompareDecentChannel(sCommunityMember* pMember1, sCommunityMember* pMember2);
protected:
};
