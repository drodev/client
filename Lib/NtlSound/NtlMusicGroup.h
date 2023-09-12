/*****************************************************************************
*
* File			: NtlMusicGroup.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 7. 11	
* Abstract		: Background Music Channel Group
*****************************************************************************
* Desc			: �ٸ� �������� ��ȯ�ɽ� ���� ����(PostMusic)��
*				  Fade Out �� �Ǹ� map�� ó���� ��ġ�ϰ� ���ο� ������
*				  map�� �ι�°�� ��ġ�Ѵ�
*
*				  �ϴ� Fade Out�� ���۵� PostMusic�� ������߸� �Ѵ�
*****************************************************************************/

#pragma once

#include <string>
#include "ceventhandler.h"
#include "NtlChannelGroup.h"


class CNtlMusicGroup : public CNtlChannelGroup, public RWS::CEventHandler
{
public:
	CNtlMusicGroup(eChannelGroupType eGroup);
	virtual ~CNtlMusicGroup();

	virtual void			Update(float fElapsed);

	virtual eStoreResult	StoreSound(CNtlSound* pSound, sNtlSoundPlayParameta* pParameta);
	virtual bool			Stop(SOUND_HANDLE hHandle);

public:
	virtual VOID	HandleEvents( RWS::CMsg &msg );

protected:
	virtual void	ReleaseFinishedSound(float fElapsed);

protected:
	float			m_fDelayReplayTime;						///< �ݺ��Ǵ� ������ ���� ������� �޽� �ð�(���� : ��)
	float			m_fReplayElapsed;						///< ���� ������ ���� ������� ���� �ð�

	SOUND_HANDLE	m_hPostSound;							///< Fade out �� ������ ���� �ڵ�
};