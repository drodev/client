/*****************************************************************************
*
* File			: NtlObjectGroup.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 7. 13
* Abstract		: Object music channel group
*****************************************************************************
* Desc			: ������Ʈ ä�� �׷��� �ٸ� ä�� �׷��� �켱 ������ �з��� ��
*				  ������ ������Ʈ ä�� �ϳ��� �������� ��Ű�� �� �̸��� �����Ѵ�
*				  ���� �� ä���� ����� ��������� ������� ���带 �÷����Ѵ�
*
*****************************************************************************/

#pragma once

#include <list>

// core
#include "ceventhandler.h"

// sound
#include "NtlSoundDefines.h"
#include "NtlChannelGroup.h"

class CNtlObjectGroup : public CNtlChannelGroup, public RWS::CEventHandler
{
public:
	CNtlObjectGroup(eChannelGroupType eGroup);
	virtual ~CNtlObjectGroup();

	virtual void			Destory();

	virtual bool			Stop(SOUND_HANDLE hHandle);
	virtual CNtlSound*		GetSound(SOUND_HANDLE hHandle);

	virtual bool			ReleaseLowRankChannel();
	virtual bool			IsExistSound(SOUND_HANDLE handle);

public:
	virtual void			PostUpdate(float fXPos, float fYPos, float fZPos);

	virtual void			StoreReleasedSound(CNtlSound* pSound);
	virtual void			StoreSleepingSound(CNtlSound* pSound);

	virtual void			DelSleepingSound(SOUND_HANDLE hHandle);
	virtual void			DelReleasedSound(SOUND_HANDLE hHandle);	

	virtual CNtlSound*		GetReleasedSoundbyPriority();	///< ���� �������� ���� ����� ������ �̸��� ��ȯ�Ѵ�.
	virtual void			SuccessRelay();					///< ������ ���带 �ٽ� �÷����ϴµ� �������� �� ȣ���ؾ� �Ѵ�.

protected:
	virtual VOID			HandleEvents( RWS::CMsg &msg );


public:
	SOUND_MAP			m_mapReleasedSound;			///< ���� �׷쿡 ���� ���������� ���� �̸�
	///< �ٸ� ä���� release�Ǹ� ���ʴ�� �÷����Ѵ�.

	SOUND_MAP			m_mapSleepingSound;			///< ���� �ݰ���� ����� �÷��̵��� �ʰ� ����Ʈ�� �����Ѵ�
};