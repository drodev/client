/*****************************************************************************
 *
 * File			: NTLAnimLayer.h
 * Author		: HongHoDong
 * Copyright	: (��)NTL
 * Date			: 2006. 4. 11	
 * Abstract		: NTL NtlAnimLayer
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __NTL_PL_ANIM_LAYER_H__
#define __NTL_PL_ANIM_LAYER_H__

#include "NtlInstanceAnimData.h"
#include "NtlAnimChannel.h"
#include "NtlCallbackWidget.h"

enum EAnimChannel
{
	ANIM_CHANNEL_CURRENT = 0,
	ANIM_CHANNEL_NEXT,
	ANIM_CHANNEL_END,
};

enum EBlendType
{
	BLEND_MIX,							///< Current�� Play�� �ϰ� Next�� Play�� �ϸ鼭 ������ �Ѵ�.
	BLEND_TWEEN							///< Current�� Stop�ϰ� Next�� Start���� ������ �Ѵ�.
};

struct SBlendData
{
	RwReal		fBlendAlpha;			///< Current Blend��(0.f - 1.f)
	RwReal		fBlendTargetAlpha;		///< Target Blend��
	RwReal		fBlendTargetInterval;	///< ��ȭ��
	EBlendType	eBlendType;				///< BlendType

	SBlendData() : fBlendAlpha(0.f), fBlendTargetAlpha(1.f), fBlendTargetInterval(0.1f),
	               eBlendType(BLEND_TWEEN) {}
};

/*!
 * \Animation
 * Animation�� Blending�� ó���ϱ� ���� Class	
 * 
 */
class CNtlAnimLayer
{
public:
	CNtlAnimLayer();
	virtual ~CNtlAnimLayer() {};

protected:
	RpHAnimHierarchy	*m_pBaseHierarchy;					///< Base Hierarchy Reference
	CNtlAnimChannel		m_AnimChannel[ANIM_CHANNEL_END];	///< Blending�� �ִ� 2��
	
	SBlendData			m_CurBlendData;						///< ���� Blend ��
	SBlendData			m_DefaultBlendData;					///< Default Blend ��
	RwBool				m_bBlendChange; 					///< Blending ������

	RwInt32				m_iLastSendEventIndex;				///< ���������� ���� Event Index
	RwReal				m_fLastSendEventTime;				///< ���������� ���� Event�� ���� �ð�

	CNtlCallbackVPParam1	*m_pCallBack;

public:
	RwBool	Create(RpHAnimHierarchy *pBaseHierarchy);
	RwBool	Update(float fElapsed);
	void	Destroy();
	
	RwBool	SetAllAnimation(SInstanceAnimData *pInstanceAnimData, RwReal fStartTime = 1.f, RwBool bLoop = TRUE);
	RwBool	SetAnimation(SInstanceAnimData *pInstanceAnimData, RwReal fStartTime = 1.f, RwBool bLoop = TRUE, RwBool bBlending = TRUE);
	RwBool	SetBlend(EBlendType eBlendType, RwReal fBlendAlpha = 0.f, RwReal fBlendInterval = 0.1f);
	
	RwReal	GetCurrentAnimTime();
    void    SetCurrentAnimTime(RwReal fCurrTime);				///< �ִϸ��̼��� ���� �÷��� Ÿ���� �����Ѵ�. (By agebreak 2006.05.01)
	RwReal	GetDurationAnimTime();								///< �̸ֹ��̼��� ��ü �ð�

	RwBool	GetCurrentAnimEnd();

	RwBool	IsBlendEnable(void);

    void    OnAfterAnimEventRun();                              ///< ���� �ð� ���� Anim Event�� ��� �����Ų��.
	
	template <class Callbackclass>
	void SetCallBack(Callbackclass *cbclass,int (Callbackclass::*callback)(void* EventData))
	{
		m_pCallBack = NTL_NEW CNtlCallbackVPWidget1<Callbackclass> (cbclass,callback);
	}

};

#endif
