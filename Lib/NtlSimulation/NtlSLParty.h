/*****************************************************************************
*
* File			: NtlParty.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 10. 20	
* Abstract		: Simulation party info class
*****************************************************************************
* Desc         : 
*
*****************************************************************************/

#ifndef __NTL_PARTY_INFO_H__
#define __NTL_PARTY_INFO_H__

// core
#include "ceventhandler.h"

// share
#include "NtlParty.h"
#include "NtlPartyDungeon.h"

// simulation
#include "NtlSharedDef.h"
#include "NtlSLDef.h"
#include "NtlSLCommunityGroup.h"

#define dINVALID_CHARM_BUFF_INDEX	NTL_PARTY_CHARM_INVENTORY_COUNT

class CNtlFakeBuffContainer;
struct sITEM_TBLDAT;
struct sCHARM_TBLDAT;

struct sPartyMember : public sCommunityMember
{
	SERIAL_HANDLE	hSerial;		///< �ɹ� �ڵ�
	RwUInt8			byRace;			///< ����
	RwUInt8			byClass;		///< ����
	RwUInt8			byLevel;		///< ����
	RwUInt16		wCurLP;			///< ���� LP
	RwUInt16		wMaxLP;			///< �ִ� LP
	RwUInt16		wCurEP;			///< ���� EP
	RwUInt16		wMaxEP;			///< �ִ� EP
	RwUInt32		uiWorldID;		///< ���� ID
	RwUInt32		uiWorldTbl;		///< ���� ���̺� Index
	RwV3d			vPos;			///< ��ġ(���ðŸ� �ۿ� ���� ���� ��Ŷ�� �޴´�)
	SERIAL_HANDLE	hBusSerial;		///< Ÿ�� �ִ� ������ �ڵ�

	CNtlFakeBuffContainer*	pFakeBuffContainer;		///< Save buff information of members except yourself
};

enum ePartyMemberDataType
{
	PARTY_MEMBER_DATA_RACE,

	NUM_PARTY_MEMBER_DATA
};

class CNtlParty : public CNtlSLCommunityGroup, public RWS::CEventHandler
{
public:
	CNtlParty();
	virtual ~CNtlParty();

	virtual	RwBool	Create(void);
	VOID			Update(RwReal fElapsed);
	virtual VOID	Destroy(void);

	virtual VOID	ClearMember();
	virtual VOID	Leave();

	virtual	void	HandleEvents(RWS::CMsg &pMsg);

	VOID			SetPartyName(WCHAR* pcName);			///< ��Ƽ �̸� ����

	const WCHAR*	GetPartyName();							///< ��Ƽ �̸��� ��ȯ�Ѵ�
	SERIAL_HANDLE	GetLeaderHandle();						///< ���� �ڵ��� ��ȯ�Ѵ�
	RwInt32			GetAvatarIndex();

	// �й� ��� ��ȯ
	RwUInt8				 GetZennyLootingMethod();
	RwUInt8				 GetItemLootingMethod();

	ePARTY_DUNGEON_STATE GetPartyDungeonState();

	// After executing Sort, it may be different from the member structure previously received with GetMemberbyIndex ()
	virtual VOID	Sort(RwUInt8 byDataType, RwBool bAscent);

	virtual RwBool	IsHaveGroup();

    sSHARETARGET_INFO*  GetShareTargetInfos() {return m_aShareTargetInfo;}      ///< ��Ƽ ����Ÿ�� ������ ��ȯ�Ѵ�

protected:
    void            PartyShareTargetResHandler(RWS::CMsg& pMsg);         ///< ��Ƽ ���� Ÿ�� ���� ó��
    void            PartyShareTargetNfyHandler(RWS::CMsg& pMsg);         ///< ��Ƽ ���� Ÿ�� �˸� ó�� 

protected:
	WCHAR					m_pwPartyName[NTL_MAX_SIZE_PARTY_NAME+1];	///< ��Ƽ �̸�

	SERIAL_HANDLE			m_hLeaderHandle;			///< ��Ƽ ���� �ڵ�

	sSHARETARGET_INFO       m_aShareTargetInfo[NTL_MAX_SHARETARGET_COUNT];        // ��Ƽ ���� Ÿ�� ����, �迭�� �ε����� ���� Ÿ�� ��ȣ�̴�

	RwUInt8					m_byZennyLootingMethod;		///< ���� �й� ���
	RwUInt8					m_byItemLootingMethod;		///< ������ �й� ���

	ePARTY_DUNGEON_STATE	m_eDungeonState;			///< ��Ƽ �ν��Ͻ� ������ ����
};

inline RwUInt8 CNtlParty::GetZennyLootingMethod()
{
	return m_byZennyLootingMethod;
}

inline RwUInt8 CNtlParty::GetItemLootingMethod()
{
	return m_byItemLootingMethod;
}

inline ePARTY_DUNGEON_STATE CNtlParty::GetPartyDungeonState()
{
	return m_eDungeonState;
}

#endif