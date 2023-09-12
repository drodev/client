/*****************************************************************************
*
* File			: NtlSLCommunityGroup.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 
* Abstract		: 
*****************************************************************************
* Desc          : �������� ������ �ִ� �׷��� �����͸� �����ϱ� ���� ���� Ŭ����
*
*				  map�� list�� �ߺ��Ǿ� �ɹ��� �����ϴµ� �̴� �Ը� ū �׷���
*				  �ɹ��� ����, Ż�� ������� �ʰ� �Ը� ���� �׷���
*				  �ɹ��� ����, Ż���� ���ϰ� ũ�� �ʴٰ� �ǴܵǱ� �����̴�.
*****************************************************************************/

#ifndef __NTL_COMMUNITY_GROUP_H__
#define __NTL_COMMUNITY_GROUP_H__

#include <algorithm>

// shared
#include "NtlSharedDef.h"


struct sCommunityMember
{
	RwUInt32		uiKey;
	WCHAR			wszMemberName[NTL_MAX_SIZE_CHAR_NAME + 1];	///< �ɹ� �̸�
};

typedef std::map<RwUInt32, sCommunityMember*>			COMMUNITY_MAP;
typedef std::map<RwUInt32, sCommunityMember*>::iterator	COMMUNITY_MAP_ITER;

typedef std::list<sCommunityMember*>					COMMUNITY_LIST;
typedef std::list<sCommunityMember*>::iterator			COMMUNITY_ITER;



// Sort�Լ��� ��ũ��
#define dCOMMUNITY_GROUP_SORT(bAscentValue, function_Ascent, function_Decent) \
{	\
	if( bAscentValue )	\
	std::stable_sort(m_listMember.begin(), m_listMember.end(), function_Ascent);	\
	else	\
	std::stable_sort(m_listMember.begin(), m_listMember.end(), function_Decent);	\
	break;	\
}

// Sort�� �� ������ �ε����� eCommunityDataType�� �̾ �����Ѵ�.
// �� Ŀ�´�Ƽ�� Sort�� ���� ������ ��ġ�� �ʱ⿡ �ε����� �Ʒ� ���ǵ� �� ���ķ�
// �ߺ��Ǿ �����ϴ�.
enum eCommunityDataType
{
	COMMUNITY_DATA_NAME,

	COMMUNITY_DATA_NEXT_INDEX,

    // ģ�� ����Ʈ Sort�� ���
    COMMUNITY_DATA_LEVEL,
    COMMUNITY_DATA_LOC,
    COMMUNITY_DATA_CHANNEL,
};



class CNtlSLCommunityGroup
{
public:
	CNtlSLCommunityGroup() {}
	virtual ~CNtlSLCommunityGroup() {}

	virtual	RwBool	Create() = 0;
	virtual VOID	Destroy() = 0;

	// Ŀ�´�Ƽ�� ���� �������� ������ �ִ� �����Ͱ� ���� �� �ִ�.
	// �װ͵��� �Լ��� �������̵�����.
	virtual VOID	ClearMember();
	virtual VOID	Leave()	= 0;

	sCommunityMember* GetMemberbyIndex(RwInt32 iIndex);
	sCommunityMember* GetMemberbyKey(RwUInt32 uiKey);
	sCommunityMember* GetMemberbyName(WCHAR* pwcName);
	RwInt32			GetMemberCount();

	COMMUNITY_ITER	Begin();
	COMMUNITY_ITER	End();

	// Sort�� �����ϰ� ������ ������ GetMemberbyIndex()�� ���� �ɹ� ����ü�� �ٸ� �� �ִ�
	virtual VOID	Sort(RwUInt8 byDataType, RwBool bAscent);

	// member list�� ��� �ް� �Ѳ��� GUI���� ������Ʈ �ϱ� ����
	// �ڽ��� �׷쿡 ���� �ִ����� �����ϴ� ���� member�� �ִ��� �������� �˻����� ����
	// ������ �������� �����϶�. ��) ����� �̸��� �����ϴ°�?
	virtual RwBool	IsHaveGroup() = 0;
	RwBool			IsMember(RwUInt32 uiKey);

protected:
	RwBool			AddMember(RwUInt32 uiKey, sCommunityMember* pNewMember);
	VOID			DelMember(RwUInt32 uiKey);

	static RwBool	CompareAscentName(sCommunityMember* pMember, sCommunityMember* pMember2)
	{
		if( !pMember || !pMember2 )
			return FALSE;

		return (wcscmp(pMember->wszMemberName, pMember2->wszMemberName) < 0 );
	}
	static RwBool	CompareDecentName(sCommunityMember* pMember, sCommunityMember* pMember2)
	{
		if( !pMember || !pMember2 )
			return FALSE;

		return (wcscmp(pMember->wszMemberName, pMember2->wszMemberName) > 0 );
	}

protected:
	COMMUNITY_MAP			m_mapMember;			///< Container for search
	COMMUNITY_LIST			m_listMember;			///< Aligned container for GUI
};

#endif