#ifndef _NTL_ANIM_EVENT_DATA_H_
#define _NTL_ANIM_EVENT_DATA_H_

#include "GraphicDataTable.h"
#include "NtlInstanceEffect.h"
#include "NtlSoundDefines.h"
#include "NtlSerializer.h"



// Projectile Type�� ���� �߰� �Ķ���͵��� �����ϱ� ���� Union
struct SHissidanData        /// Hissidan Ÿ���� ���� �߰� ������
{
	RwBool      bApplyAngle;                              ///< ���� ����/������ ���� (�������� �ϸ� Hand Type�� ���� ������ �ش�)
	RwV2d       v2dAngle;                                   ///< �߻� ���� (X��, Y��)
};

struct SMultiHissidanData   /// Multi Hissidan Ÿ���� ���� �߰� ������
{
	RwInt32     nCount;                                   ///< Hissidan ����
	RwV2d*      pArrayAngle;                              ///< �߻� �������� �迭 (���� �Ҵ��Ѵ�)
};

struct SHellZoneData        /// ���� ����ź�� Ÿ���� ���� �߰� ������
{
	RwV3d				vTargetEffectOffset;						///< Target������ Offset �Ÿ�
	RwReal				fTargetEffectStartWaitTime;					///< Target�� ���ư��� ���� ��ٸ��� �ð�
	RwReal				fTargetEffectSpeed;							///< Target�� ���ư��� �ӵ�
};

union UEffectTypeExtraData
{
	SHissidanData       hissidanData;
	SMultiHissidanData  multiHissidanData;
	SHellZoneData       hellZoneData;
};

struct SEventAnimHit : public SEventAnim
{
	RwUInt32			uiDamage;
	RwBool				bPowerEffect;
	EAttackType			eAttackType;								///< Attack Type
	ETargetBehavior		eTargetBehavior;
	RwBool              bKB2Push;                                   ///< �˴ٿ��� ���� ������ Push�� ó������ ���� �÷���
	EHandType			eHandType;									///< HandType
	EProjectileEffectType uiProjectileEffectType;					///< Ball, Beam, Hissidan, hell zone, Multi Hissidan

	EBoneType			eProjectileShotType;						///< ��� Bone���� Projectile�� ���󰡴��� ����
	RwInt32             nSubWeaponFlag;                             ///< SubWeapon�� ��� Bone���� ������ üũ�� �÷���

	RwChar				chBoneName[MAX_DEFAULT_NAME];				///< Character Bone Name	
	RwChar              chProjectileEffectName[MAX_DEFAULT_NAME];	///< ���󰡴� Effect Name
	RwReal				fProjectileSpeed;							///< projectile speed
	RwBool              bTargetAttach;								///< Effect�� Target�� Attach�� ������ ����
	RwReal              fTargetHeight;								///< Target Effect�� ���� ��ġ (1�� �⺻ 100%)

	RwChar              chTargetEffectName[MAX_DEFAULT_NAME];		///< Target�� ǥ�õ� Effect Name
	ETargetEffectType	eTargetEffectType;							///< Target Effct�� ���� ���� Ÿ��
	RwChar              chSubTargetEffect[MAX_DEFAULT_NAME];        ///< ���� ���ݽ� ���� Ÿ�ٿ��� ǥ�õ� ����Ʈ
	RwChar              chTargetSoundName[MAX_DEFAULT_NAME];		///< Target�� �¾��� ��� ������ Sound File Name
	eChannelGroupType	eSoundType;									///< Sound type(CHANNEL_GROUP_VOICE_SOUND or CHANNEL_GROUP_EFFECT_SOUND)    
	RwBool              bHitSoundEcho;                              ///< Hit�� ���尡 Echo ������� ����
	RwBool              bCameraShake;                               ///< Target Hit�� Camera Shake����
	RwReal              fCameraShakeFactor;                         ///< ī�޶� ����ũ ����
	RwReal              fCameraShakeMaxHeight;                      ///< ī�޶� ����ũ �ִ밪 ����
	RwChar              chWordEffect[MAX_DEFAULT_NAME];             ///< Target Hit�� ��Ÿ�� Word Effect (ex. ����)

	UEffectTypeExtraData uEffectTypeExtraData;                      ///< Effect Type�� ���� �߰� ������ Union


	SEventAnimHit() : eAttackType(ATTACK_TYPE_PHYSICAL),
		eTargetBehavior(TARGET_BEHAVIOR_NONE),
		bKB2Push(FALSE),
		uiDamage(0),
		bPowerEffect(FALSE),
		eHandType(HAND_TYPE_LEFT),
		uiProjectileEffectType(BEID_PROJ_BALL),
		fProjectileSpeed(10.0f),
		eProjectileShotType(BONE_CHARACTER),
		nSubWeaponFlag(0),
		bTargetAttach(FALSE),
		fTargetHeight(1.0f),
		eSoundType(CHANNEL_GROUP_EFFECT_SOUND),
		bCameraShake(FALSE),
		eTargetEffectType(TARGET_EFFECT_TYPE_NONE),
		bHitSoundEcho(FALSE),
		fCameraShakeFactor(CAMERA_SHAKE_FACTOR),
		fCameraShakeMaxHeight(CAMERA_SHAKE_MAX_HEIGHT_FACTOR)
	{
		eEventID = EVENT_ANIM_HIT;
		memset(chBoneName, 0, sizeof(chBoneName));
		ZeroMemory(chProjectileEffectName, sizeof(chProjectileEffectName));
		ZeroMemory(chTargetEffectName, sizeof(chTargetEffectName));
		ZeroMemory(chTargetSoundName, sizeof(chTargetSoundName));
		ZeroMemory(chWordEffect, sizeof(chWordEffect));
		ZeroMemory(&uEffectTypeExtraData, sizeof(UEffectTypeExtraData));
		ZeroMemory(chSubTargetEffect, sizeof(chSubTargetEffect));
	}

	~SEventAnimHit()
	{
		if (uiProjectileEffectType == BEID_PROJ_MULTI_HISSIDAN)
		{
			NTL_ARRAY_DELETE(uEffectTypeExtraData.multiHissidanData.pArrayAngle); // �������� �Ҵ��Ѱ��̶� Delete����� �Ѵ�.
		}
	}

	void SaveSerialize(CNtlSerializer& sOut);
	void LoadSerialize(CNtlSerializer& sIn);

};

struct SEventAnimEnd : public SEventAnim
{
	RwUInt32	uiAnimKey;
	SEventAnimEnd() : uiAnimKey(0) { eEventID = EVENT_ANIM_END; }

};

struct SEventVisualEffect : public SEventAnim
{
	RwChar  chEffectName[MAX_DEFAULT_NAME];     ///< Effect Name;
	EBoneType eBoneType;                        ///< Effect�� ���� Bone Type
	RwChar  chBoneName[MAX_DEFAULT_NAME];       ///< Attach�� �� Bone Name
	RwV3d   vOffSetPos;                         //<  Offset;    
	RwBool  bAttach;                            ///< �𵨿� Attach ���� ����
	RwBool  bAttachBone;                        ///< Bone�� Attach ���� ���� (TRUE = Bone Attach, FALSE = Pos Attach)
	RwBool  bApplyScale;                        ///< �θ� Entity�� Scale�� �������� ����
	RwBool  bProjectileType;                    ///< �߻�üŸ������ ����

	unsigned int uiUnknown;

	SEventVisualEffect() : eBoneType(BONE_CHARACTER)
	{
		ZeroMemory(chBoneName, sizeof(chBoneName));
		ZeroMemory(chEffectName, sizeof(chEffectName));
		ZeroMemory(&vOffSetPos, sizeof(vOffSetPos));
		bAttach = TRUE;
		bAttachBone = FALSE;
		bApplyScale = TRUE;
		bProjectileType = FALSE;

		uiUnknown = 0;

		eEventID = EVENT_ANIM_VISUAL_EFFECT;
	}

};

struct SEventSound : public SEventAnim
{
	RwChar	chSoundName[MAX_DEFAULT_NAME * 2]; ///< Sound ���ϸ� (Sound ������ ��θ� ����)
	RwChar	chSoundName2[MAX_DEFAULT_NAME * 2]; ///< Sound ���ϸ� (Sound ������ ��θ� ����)
	RwChar	chSoundName3[MAX_DEFAULT_NAME * 2]; ///< Sound ���ϸ� (Sound ������ ��θ� ����)
	RwChar	chSoundName4[MAX_DEFAULT_NAME * 2]; ///< Sound ���ϸ� (Sound ������ ��θ� ����)
	eChannelGroupType eSoundType;				///< Sound Type (CHANNEL_GROUP_VOICE_SOUND or CHANNEL_GROUP_EFFECT_SOUND)    
	RwBool  bLoop;                              ///< Sound Loop ����
	RwReal  fSoundVolume;                       ///< Sound Volume
	RwReal  fSoundDist;                         ///< ��ȿ �Ÿ�
	RwReal  fSoundDecayDist;                    ///< ���� ���� �Ÿ�
	RwReal  fSoundPitchMin;                     ///< ���� ��ġ �ּҰ�
	RwReal  fSoundPitchMax;                     ///< ���� ��ġ �ִ밪

	SEventSound()
	{
		eEventID = EVENT_ANIM_VISUAL_SOUND;
		ZeroMemory(chSoundName, sizeof(chSoundName));
		ZeroMemory(chSoundName2, sizeof(chSoundName2));
		ZeroMemory(chSoundName3, sizeof(chSoundName3));
		ZeroMemory(chSoundName4, sizeof(chSoundName4));
		eSoundType = CHANNEL_GROUP_EFFECT_SOUND;
		bLoop = FALSE;
		fSoundVolume = 100.0f;
		fSoundDist = 15.0f;
		fSoundDecayDist = 30.0f;
		fSoundPitchMin = fSoundPitchMax = dNTLSOUND_PITCH_DEFAULT;
	}
};

struct SEventFootStep : public SEventAnim
{
	EFootStepType eFootStepType;
	EFootStepMobType eFootStepMobType;

	SEventFootStep()
	{
		eEventID = EVENT_ANIM_FOOT_STEP;
		eFootStepType = FOOT_LEFT;
		eFootStepMobType = FOOT_TYPE_NORMAL;
	}
};

struct SEventLinkEffect : public SEventAnim
{
	RwChar  chEffectName[MAX_DEFAULT_NAME];
	RwChar  chBoneName[MAX_DEFAULT_NAME];
	RwV3d   vOffsetPos;
	RwBool  bAttachBone;

	SEventLinkEffect()
	{
		eEventID = EVENT_ANIM_LINK_EFFECT;
		ZeroMemory(chEffectName, sizeof(chEffectName));
		ZeroMemory(chBoneName, sizeof(chBoneName));
		ZeroMemory(&vOffsetPos, sizeof(vOffsetPos));
		bAttachBone = FALSE;
	}

};

///////////////////////////////////////////////////////////////////////////
// Slow Time Event
//////////////////////////////////////////////////////////////////////////
struct SEventWeightTime : public SEventAnim
{
	RwReal fLifeTime;       ///< Slow ȿ���� ���ֵ� �ð�
	RwReal fWeightValue;    ///< �󸶳� ���������� ���� Weight��

	SEventWeightTime()
	{
		eEventID = EVENT_ANIM_WEIGHT_TIME;
		fLifeTime = 0.0f;
		fWeightValue = 1.0f;
	}

};

struct SEventTrace : public SEventAnim
{
	/// Trace�� ��� �������� Ÿ��
	enum EAttachType
	{
		CHARACTER_BONE,     ///< ĳ���� ���� �ٴ´�.
		WEAPONE_BONE,       ///< ���� ���� �ٴ´�.
		SUB_WEAPON_BONE,    ///< �������� ���� �ٴ´�.
	};

	/// ���� ������ �̺�Ʈ �������� ������, Weapon �������� ������ ���
	enum ETraceKind
	{
		EVENT_TRACE,        ///< Event�� �������� ������.
		ITEM_TRACE,         ///< Item�� �������� ������.
	};

	RwReal  fLifeTime;           ///< ������ ǥ�� �ð�
	RwReal  fEdgeLifeTime;       ///< Edge�� Life Time    
	EAttachType eAttachType;     ///< ������ ��� ������ 
	ETraceKind  eTraceKind;      ///< ������ Item ������ ������
	RwChar  strStartBoneName[MAX_DEFAULT_NAME];    ///< ù��° Bone�� �̸�
	RwChar  strEndBoneName[MAX_DEFAULT_NAME];      ///< �ι�° Bone�� �̸�
	RwChar  strTexture[MAX_DEFAULT_NAME];          ///< Texture File Name
	RwV3d   v3dStartBoneOffset;  ///< ù��° Bone�� Offset
	RwV3d   v3dEndBoneOffset;    ///< �ι�° Bone�� Offset
	RwReal  fEdgeGap;             ///< ���ʸ��� Edge�� ���������� ��
	RwInt32 nSplinePointCount;   ///< Spline���� �����ϴ� ���ؽ��� ���� (�ΰ��� Edge���̿� �����Ǵ� ���ؽ��� �����̴�)
	RwInt32 nMaxEdgeCount;       ///< �ִ� Edge Count
	RwReal  fMaxLength;          ///< ������ �ִ� ����
	RwBlendFunction eSrcBlend;  ///< Src Blend State
	RwBlendFunction eDestBlend; ///< Dest Blend State
	RwRGBA  colStartColor;       ///< ���� Color��
	RwRGBA  colEndColor;         ///< �� Color��   

	SEventTrace() : fLifeTime(1.0f),
		fEdgeLifeTime(0.3f),
		fEdgeGap(0.03f),
		nSplinePointCount(10),
		nMaxEdgeCount(500),
		fMaxLength(1.0f)
	{
		eEventID = EVENT_ANIM_TRACE_EFFECT;
		eSrcBlend = rwBLENDSRCALPHA;
		eDestBlend = rwBLENDONE;
		eAttachType = CHARACTER_BONE;
		eTraceKind = EVENT_TRACE;
		ZeroMemory(strStartBoneName, sizeof(strStartBoneName));
		ZeroMemory(strEndBoneName, sizeof(strEndBoneName));
		ZeroMemory(strTexture, sizeof(strTexture));
		ZeroMemory(&v3dStartBoneOffset, sizeof(RwV3d));
		ZeroMemory(&v3dEndBoneOffset, sizeof(RwV3d));
		colStartColor.red = colStartColor.green = colStartColor.blue = 255;
		colEndColor.red = colEndColor.green = colEndColor.blue = 255;
		colStartColor.alpha = 255;
		colEndColor.alpha = 0;
	}

};

/// Sub Weapon Ȱ��ȭ �̺�Ʈ
struct SEventSubWeapon : SEventAnim
{
	ESubWeaponActiveFlag    eSubWeaponActiveFlag;

	SEventSubWeapon() : eSubWeaponActiveFlag(SUB_WEAPON_DEACTIVE)
	{
		eEventID = EVENT_ANIM_SUB_WEAPON;
	}

};

/// Post Effect �̺�Ʈ (ȭ������ �߽ɼ� ǥ�� �̺�Ʈ)
struct SEventPostEffect : SEventAnim
{
	RwChar                   szPostEffectName[MAX_DEFAULT_NAME];          ///< ���� PostEffect�� �̸�
	EPostEffectTypeFlag      eTarget;                                     ///< PostEffect�� Target ����
	RwV3d                    v3dOffset;                                   ///< PostEffect�� ���� ��ġ�� Offset��
	RwBool                   bCenterFixEnable;                            ///< �߽��� ���� ���
	RwReal                   fTargetHeight;                               ///< ����� Ÿ������ �����Ѱ�� ���̰�(�ٿ���ڽ� ��밪)
	RwChar                   szPCBoneName[MAX_DEFAULT_NAME];              ///< ����� PC�� �����Ѱ�� Attach�� Bone�� �̸�

	SEventPostEffect()
	{
		eEventID = EVENT_ANIM_POST_EFFECT;

		ZeroMemory(szPostEffectName, sizeof(szPostEffectName));
		ZeroMemory(&v3dOffset, sizeof(v3dOffset));
		ZeroMemory(szPCBoneName, sizeof(szPCBoneName));
		eTarget = POST_EFFECT_TARGET_TYPE_SELF;
		bCenterFixEnable = TRUE;
		fTargetHeight = 1.0f;
	}

};

// Summon Pet Event
struct SEventSummonPet : SEventAnim
{
	SEventSummonPet()
	{
		eEventID = EVENT_ANIM_SUMMON_PET;
	}
};

struct SEventAnimCinematic : public SEventAnim
{
	EAnimCinematicEventType eAnimCinematicEventType;

	SEventAnimCinematic()
	{
		eEventID = EVENT_ANIM_TMQ;
		eAnimCinematicEventType = E_ANIM_CINEMATIC_TMQ_IN;
	}
};

// Alpha Event 
struct SEventAlpha : SEventAnim
{
	// Alpha Event Apply Type
	enum EAlphaEventType
	{
		E_ALPHA_EVENT_CLUMP,
		E_ALPHA_EVENT_ATOMIC,
	};
	//////////////////////////////////////////////////////////////////////////

	RwInt32       nStartAlpha;              ///< Fade ���� ���İ� (0~255)
	RwInt32       nDestAlpha;               ///< Fade Dest ���İ� (0~255)    
	RwReal        fFadeTime;                ///< Fade �Ǵ� �ð�
	RwReal        fLifeTime;                ///< �̺�Ʈ�� �����Ǵ� Life Time
	EAlphaEventType eAlphaEventType;        ///< ���� �̺�Ʈ ���� Ÿ��
	BITFLAG       bfAtomicList;             ///< ���İ� ����� ����͵��� Index �÷���


	SEventAlpha()
	{
		eEventID = EVENT_ANIM_ALPHA;
		nStartAlpha = 255;
		nDestAlpha = 0;
		fFadeTime = 1.0f;
		fLifeTime = 1.0f;
		eAlphaEventType = E_ALPHA_EVENT_CLUMP;
		bfAtomicList = 0;
	}
};

// ���� �̺�Ʈ
struct SEventExplosion : SEventAnim
{
	ENtlPLExplosionEventType  eType;

	SEventExplosion()
	{
		eEventID = EVENT_ANIM_EXPLOSION;
		eType = EXPLOSION_EVENT_TYPE_NORMAL;
	}
};

// ���� �̺�Ʈ
struct SEventDirect : SEventAnim
{
	ENtlPLDirectEventType eType;

	SEventDirect()
	{
		eEventID = EVENT_ANIM_DIRECT;
		eType = DIRECT_EVENT_TYPE_CAMERA_SHAKE;
	}
};

// Į�� ü���� �̺�Ʈ
struct SEventColorChange : SEventAnim
{
	EColorChangeType eType;
	RwRGBA           colorEdge;
	RwRGBA           colorBody;
	RwRGBA           colorAdd;

	SEventColorChange()
	{
		eEventID = EVENT_ANIM_COLOR_CHANGE;
		eType = COLOR_CHANGE_TYPE_START;
		colorEdge.red = colorEdge.green = colorEdge.blue = 0;
		colorBody.red = colorBody.green = colorBody.blue = 255;
		colorAdd.red = colorAdd.green = colorAdd.blue = 0;
		colorEdge.alpha = colorBody.alpha = colorAdd.alpha = 255;
	}
};

/// �þ BONE�� ���� ����
struct StretchBoneInfo
{
	RwChar szBoneName[MAX_DEFAULT_NAME];
	RwReal fStretchSpeed;
	RwReal fWidth;

	StretchBoneInfo()
	{
		ZeroMemory(szBoneName, sizeof(szBoneName));
		fStretchSpeed = 100.0f;
		fWidth = 1.0f;
	}
};

/// BONE�� �ø��� �̺�Ʈ
struct SEventStretch : SEventAnim
{
	EStretchEventType eType;
	RwChar          szBoneName[2][MAX_DEFAULT_NAME];
	RwReal          fStretchSpeed;
	RwReal          fWidth;
	RwReal          fAccel;
	RwChar          szScaleBone[MAX_DEFAULT_NAME];
	RwReal          fScaleSize;
	RwChar          szAxisBone[MAX_DEFAULT_NAME];
	RwChar          szTargetEffect[MAX_DEFAULT_NAME];

	SEventStretch()
	{
		eEventID = EVENT_ANIM_STRETCH;
		fScaleSize = 1.0f;
		fStretchSpeed = 10.0f;
		fWidth = 1.0f;
		fAccel = 25.0f;
		sprintf_s(szBoneName[0], "Bip01 L UpperArm");
		sprintf_s(szBoneName[1], "Bip01 L Forearm");
		sprintf_s(szScaleBone, "Bip01 L Hand");
		sprintf_s(szAxisBone, "Bip01 L Clavicle");
		ZeroMemory(szTargetEffect, sizeof(szTargetEffect));
		eType = E_STRETCH_PULLING;
	}
};

/// ��ų��� ���Ǵ� Ʈ���� �̺�Ʈ
struct SEventTrigger : SEventAnim
{
	SEventTrigger()
	{
		eEventID = EVENT_ANIM_TRIGGER;
	}
};

/// ��ų ĵ���� ���Ǵ� �̺�Ʈ
struct SEventSkillCancel : SEventAnim
{
	SEventSkillCancel()
	{
		eEventID = EVENT_ANIM_SKILL_CANCEL;
	}
};

/// �� �̺�Ʈ ����ü�� ����� ��ȯ���ϴ� �Լ�
static RwUInt32 GetAnimEventSize(EAnimEventType eType)
{
    switch(eType)
    {
    case EVENT_ANIM_HIT:
        return sizeof(SEventAnimHit);
    case EVENT_ANIM_VISUAL_EFFECT:
        return sizeof(SEventVisualEffect);
    case EVENT_ANIM_VISUAL_SOUND:
        return sizeof(SEventSound);
    case EVENT_ANIM_FOOT_STEP:
        return sizeof(SEventFootStep);
    case EVENT_ANIM_LINK_EFFECT:
        return sizeof(SEventLinkEffect);
    case EVENT_ANIM_WEIGHT_TIME:
        return sizeof(SEventWeightTime);
    case EVENT_ANIM_TRACE_EFFECT:
        return sizeof(SEventTrace);
    case EVENT_ANIM_SUB_WEAPON:
        return sizeof(SEventSubWeapon);
    case EVENT_ANIM_POST_EFFECT:
        return sizeof(SEventPostEffect);
    case EVENT_ANIM_SUMMON_PET:
        return sizeof(SEventSummonPet);
    case EVENT_ANIM_TMQ:
        return sizeof(SEventAnimCinematic);
    case EVENT_ANIM_ALPHA:
        return sizeof(SEventAlpha);
    case EVENT_ANIM_EXPLOSION:
        return sizeof(SEventExplosion);
    case EVENT_ANIM_DIRECT:
        return sizeof(SEventDirect);
    case EVENT_ANIM_COLOR_CHANGE:
        return sizeof(SEventColorChange);
    case EVENT_ANIM_STRETCH:
        return sizeof(SEventStretch);
    case EVENT_ANIM_TRIGGER:
        return sizeof(SEventTrigger);
    case EVENT_ANIM_SKILL_CANCEL:
        return sizeof(SEventSkillCancel);        
    }

    return 0;
}


#endif
