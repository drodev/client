/*****************************************************************************
 *
 * File			: NTLAnimSet.h
 * Author		: HongHoDong
 * Copyright	: (��)NTL
 * Date			: 2005. 8. 20	
 * Abstract		: NTL PLAnimSet
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/
#ifndef _CNTL_PL_ANIM_SET_
#define _CNTL_PL_ANIM_SET_

/*
#include <rwcore.h>
#include <rtanim.h>
#include <rpworld.h> 
#include <rtquat.h> 
#include <rtanim.h>
#include <rphanim.h>
#include <vector>
*/

#include "NtlDebug.h"
#include "NtlPLCharacterAnimTable.h"

/**
 * \ingroup Client
 * Animation ���� ó���ϴ� Class �̴�.
 * 
 */

enum EAnimChannel
{
	ANIM_CHANNEL_CURRENT = 0,
	ANIM_CHANNEL_NEXT,
	ANIM_CHANNEL_END,
};

enum EBlendType
{
	BLEND_MIX,		//������ Animation�� Play�� �ϰ�, ������ Animation�� Play�� �ϸ鼭 ������ �Ѵ�.
	BLEND_TWEEN		//������ Animation�� ���߰�, ������ Animation�� Start���� ������ �Ѵ�.
};


struct SAnimChannel
{
	RpHAnimHierarchy	*pHierarchy;
	RwBool				bLoop;				//loop�� �۵��� �ؾ� �ϴ� Animation ����
	RwBool				bNotLoopEnd;		//loop�� �ƴ� Animation�� ��������
	RwReal				fAnimSpeed;         //Animation Speed
	unsigned int		uiAnimKey;

	SAnimData			*pAnimData;

	SAnimChannel() 
	{ 
		pHierarchy      = NULL;
		bLoop			= FALSE;
		pAnimData		= NULL;
		bNotLoopEnd     = FALSE;
		fAnimSpeed      = 1.f;
	};
};

class CNtlPLCharacter;
class CNtlPLAnimSet
{
public:
	CNtlPLAnimSet();
	~CNtlPLAnimSet();
private:
	RpClump	*m_pTargetClump;						 //Target Clump
	CNtlPLCharacter *m_pOwner;                       //���� Class�� �����ϴ� Class

	RpHAnimHierarchy *m_pMainHierarchy;				 //Character Main Hierarchy
	
	
	SAnimChannel		m_Channel[ANIM_CHANNEL_END]; //AnimChannel
	EBlendType			m_eBlendType;

	RwReal	m_fBlendAlpha;							 // Blend �� (0.. 1)
	RwReal	m_fBlendTargetAlpha;					 // Target Blend
	RwReal	m_fBlendTargetInterval;					 // Blend �� �ð�(��)

	RwBool	m_bAnimChanging;
	
	RwReal	m_fDefaultBlendAlpha;
	RwReal  m_fDefaultBlendTargetAlpha;
	RwReal	m_fDefaultBlendTargetInterval;
	
	RwBool	m_bActiveFlag;
	
	RwReal	m_fOldAnimTime;
private:
	void SendAnimEnd();
	void SendAnimHit();
	void SendFootStep();

public:
	void Create(RpClump *pClump, RtAnimAnimation *pDefaultAnim, CNtlPLCharacter *pOwner);
	void CreateAnimation(RtAnimAnimation *pDefaultAnim);


	void Destroy();
	void Update(float fElapsed);
	
	void	SetChangeAnimation(SAnimData *pAnimData, RwBool bLoop, unsigned int uiAnimKey);
	void	SetChangeChannelAnimation(EAnimChannel eChannel, RtAnimAnimation *pAnim);

	RwBool	SetChangeBlend(EBlendType blendType, RwReal fBlendTargetAlpha = 1.f, RwReal fBlendTargetInterval = 0.1f);
	RwBool	SetChangeAnimSpeed(RwReal fSpeed = 1.f);

	RpHAnimHierarchy *GetHierarchy() { NTL_ASSERTE(m_pMainHierarchy != NULL); return m_pMainHierarchy; }
};

#endif
