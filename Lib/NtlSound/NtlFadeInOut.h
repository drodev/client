/*****************************************************************************
*
* File			: NtlFadeInOut.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 7. 12	
* Abstract		: Fade In/Out Effect
*****************************************************************************
* Desc			: Channel, ChannelGroup�� Effect�� ������ �� �ִ�
*
*				  FMOD System���� Fade In/Out Effect�� �������� �ʾƼ�
*				  ���� �����Ͽ���.
*****************************************************************************/

#pragma once

#include <list>
#include "ceventhandler.h"
#include "fmod/fmod.hpp"

class CNtlSound;
class CNtlChannelGroup;

#define dFADE_STOP_FLAG_NOT_NOTIFY						0x01

struct sFadeInOut
{
	eFadeInOutType		eFadeType;					///< Fade In/Out Type
	eSoundResourceType	eResourceType;				///< ���� ����
	bool				bFinish;	
	float				fDestVolume;				///< ���� ��ȯ�� ����
	float				fAdjustVolume;				///< �Ź� ��ȭ�Ǵ� ������
	unsigned long		ulApplyTime;				///< ������ Fade In/Out ȿ���� ����� �ð�

	union
	{
		struct
		{
			SOUND_HANDLE	u1_hHandle;
			CNtlSound*		u1_pSound;
		};

		struct 
		{
			CNtlChannelGroup*	u2_pChannelGroup;
		};		
	};
};


class CNtlFadeInOut : public RWS::CEventHandler
{
public:
	typedef std::list<sFadeInOut>::iterator	FADE_ITER;

public:
	static bool		CreateInstance();
	static void		DestroyInstance();
	static CNtlFadeInOut* GetInstance() { return m_pInstance; }


	CNtlFadeInOut();
	virtual ~CNtlFadeInOut();

	void		Update();

	void		FadeIn(CNtlSound* pSound, float fDestVolume, unsigned long ulTime);
	void		FadeIn(CNtlChannelGroup* pChannelGroup, float fDestVolume, unsigned long ulTime);

	void		FadeOut(CNtlSound* pSound, float fDestVolume, unsigned long ulTime);
	void		FadeOut(CNtlChannelGroup* pChannelGroup, float fDestVolume, unsigned long ulTime);

	void		StopImmdiately(FMOD::Channel* m_pFMODChannel, RwUInt8 byFlag = 0);
	void		StopImmdiately(CNtlChannelGroup* pChannelGroup, RwUInt8 byFlag = 0);

	bool		IsFadeIn(FMOD::Channel* pChannel);
	bool		IsFadeOut(FMOD::Channel* pChannel);

	bool		IsFadeIn(CNtlChannelGroup* pChannelGroup);
	bool		IsFadeOut(CNtlChannelGroup* pChannelGroup);

protected:
	virtual VOID	HandleEvents( RWS::CMsg &msg );

public:
	static CNtlFadeInOut* m_pInstance;

	std::list<sFadeInOut>		m_listFade;
};

static CNtlFadeInOut* GetFadeInOut()
{
	return CNtlFadeInOut::GetInstance();
}