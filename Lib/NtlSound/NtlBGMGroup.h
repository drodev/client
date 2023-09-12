/*****************************************************************************
*
* File			: NtlBGMGroup.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2009. 1. 28
* Abstract		: Background Music Channel Group
*****************************************************************************
* Desc			: �ٸ� ����������� ��ȯ�ɽ� ���� �������(PostMusic)��
*				  Fade Out �� �Ǹ� �������
*
*				  ��������� �켱������ �־ �켱���� ��������� ���ְ�
*				  ������ ������� ��������� Play�ȴ�.
*****************************************************************************/

#pragma once

#include <string>
#include "ceventhandler.h"
#include "NtlChannelGroup.h"

class CNtlBGMPlayList;


class CNtlBGMGroup : public CNtlChannelGroup, public RWS::CEventHandler
{
protected:
	struct sPLAY_BGM_INFO
	{
		SOUND_HANDLE	hHandle;
		eBGMType		eType;
	};

public:
	CNtlBGMGroup(eChannelGroupType eGroup);
	virtual ~CNtlBGMGroup();

	virtual bool			Create(FMOD::ChannelGroup* pChannelGroup, unsigned int uiSoundDuplicatoin = 0);
	virtual void			Update(float fElapsed);
	virtual void			Destory();

	virtual eStoreResult	StoreSound(CNtlSound* pSound, sNtlSoundPlayParameta* pParameta);
	virtual bool			Stop(SOUND_HANDLE hHandle);
	void					StopImmediately(SOUND_HANDLE hHandle);

public:
	virtual VOID	HandleEvents( RWS::CMsg &msg );	

protected:
	void			Update_Replay(float fElapsed);
	void			ClearBGMList(SOUND_HANDLE hHandle);

	virtual void	ReleaseFinishedSound(float fElapsed);

protected:
	float			m_fReplayElapsed;						///< ���� ������ ���� ������� ���� �ð�

	sPLAY_BGM_INFO	m_tPlaySound;							///< ���� Play �ǰ� �ִ� ����
	sPLAY_BGM_INFO	m_tPostSound;							///< Fade out �� ������ ����

	CNtlBGMPlayList*	m_pBGMPlayList;
};