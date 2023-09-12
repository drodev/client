/*****************************************************************************
*
* File			: NTLPLCharacter.h
* Author		: HongHoDong
* Copyright	: (��)NTL
* Date			: 2005. 8. 20.
* Abstract		: NTL PLCharacter
*****************************************************************************
* Desc         : 
*
*****************************************************************************/
#ifndef __NTL_PL_CHARACTER_H__
#define __NTL_PL_CHARACTER_H__

#include "NtlDebug.h"
#include "NtlPLAttach.h"
#include "NtlPLResource.h"
#include "NtlPLCharacterProperty.h"
#include "NtlPLItem.h"
#include "ceventhandler.h"
#include "NtlPLEntityRenderHelpers.h"
#include "NtlDefaultItemData.h"
#include "NtlPLLinkEffect.h"
#include "NtlAnimLayer.h"
#include "NtlInstanceAnimData.h"
#include "NtlPLEquipItem.h"
#include "OccluderProxy.h"


#define dCOSTUME_BITSET_INVALID		(0xffffffff)


struct SPLCharacterCreateParam : public SPLEntityCreateParam
{
	RwUInt32 uiSerialId;

	RwBool   bPcFlag;
	RwUInt32 uiClass;
	RwUInt32 uiRace;
	RwUInt32 uiGender;
	RwUInt32 uiHeadType;
	RwUInt32 uiFaceType;
	RwUInt32 uiHeadColorType;
	RwUInt32 uiSkinColorType;
	RwBool	bNotShadingFlag;
    RwBool  bIsAdult;
	SPLCharacterCreateParam() : bNotShadingFlag(FALSE), bIsAdult(FALSE) {}
};

enum ECharacterAnimLayer
{
	CHARACTER_ANIM_LAYER_BASE = 0,
	CHARACTER_ANIM_LAYER_UPPER,
	CHARACTER_ANIM_LAYER_END,
};

/*
* Play�� �ǰ� �ִ� Animation�� ����
*/
struct SAnimPlayInfo
{
	RwUInt32	m_uiAnimKey;
	std::vector<SEventAnimHit *> vecAnimHit;

	SAnimPlayInfo() : m_uiAnimKey(0) {}
};


/**
* \ingroup NtlPresentation
* \brief Character ���� Ŭ����
* \date 2006-08-21
* \author Hodong
*/

class CNtlPLCharacter : public CNtlPLAttach, public COccluderProxy
{
public:
	CNtlPLCharacter();
	virtual ~CNtlPLCharacter();

protected:
//	RwSphere				m_BSphere;								///< Position�� ������� ���� BoundSphere
	RwSphere				m_BSphereCur;							///< Position�� ����� BoundingSphere : GetBoundingSphere�� ȣ���ϰ� �Ǹ� ������Ʈ �ȴ�.
	CNtlPLCharacterProperty	*m_pProperty;							///< Character Property
	CNtlPLResource			*m_pResourceClump;						///< Target Clump Resource Reference
	ENTITY_ATOMIC_VEC	    m_vecAtomicList;                        ///< ���� Clump�� �����ϰ� �ִ� Atomic���� ����Ʈ

	SCharScheduleResInfo	m_sScheduleResInfo;
	RwBool					m_bRunTimeAlpha;

	RpHAnimHierarchy		*m_pBaseHierarchy;						///< Base Hierarchy
    
	CNtlAnimLayer			m_AnimLayer[CHARACTER_ANIM_LAYER_END];	///< AnimationLayer(��, ��ü)
	CNtlInstanceAnimTable	m_InstanceAnimTable;					///< Animation Resource InstanceData

	SAnimPlayInfo			m_sBaseAnimPlayInfo;					///< ���� Play���� Animation�� ������
	FRAME_MAP				m_mapFrame;								///< Bone Info
	SToonData				m_ToonData;								///< Toon Ink, Toon Paint, Toon Resource
	
    STypeBoneData			*m_pTypeBoneData;						///< Bone Data Reference
	RwInt32				    m_nBoneCount;							///< Bone�� ����
    RwV3d                   m_vBoneStretchTargetPos;                ///< Bone Stretch Target ��ġ
    RwChar                  m_szBoneStretchAxisBone[MAX_DEFAULT_NAME];                ///< Bone Stretch �̺�Ʈ���� ȸ������ �Ǵ� ��


	RwV3d					m_vCurPos;								///< Character�� ���� ��ġ
	RwV3d					m_vScale;								///< Character�� Scale�� �����ϰ��� �Ҷ�(Instance)
	RwV3d					m_vAngle;								///< Angle					

	RwBool					m_bAnimUpdate;							///< Animation�� Update�� �ϴ���
	RwReal					m_fAnimSpeed;							///< Anim Speed
	RwReal					m_fFastMaxExtent;						///< fast max extent

	CNtlPLEquipItem			*m_pEquipItem;							///< Equip Item

	RwRGBA					m_sHeadColor;							///< Head Color
	RwRGBA					m_sSkinColor;							///< Skin Color

	RwRGBA					m_sColor;								///< Base Color
	RwRGBA					m_sAddColor;							///< Add Color

	RwRGBA					m_sInkColor;							///< Ink Color;

	CNtlPLLinkEffect        m_LinkEffectInstance;                   ///< LinkEffect Instance���� �����ϴ� ��ü
	ListLoopEffect          m_listLoopEffect;                       ///< LoopEffect�� list
	ListSoundHandle         m_listLoopSound;                        ///< LoopSound���� HANDLE List

	RwBool					m_ToonEdgeVisibility;

	// NPC�� MOB�� ��� m_pResourceClump�� ���µ� �̰�� PLItem���� �ش��ϴ� SimpleMaterial�� ������ ����.
	RwBool m_SimpleMaterial;

	// Character�� �ָ� ������ performance ������ ���� animation update�� skip�Ѵ�.
	RwReal m_SkipAnimUpdateTime;
	RwReal m_SkipAnimUpdateElapsedTime;

	static RwBool m_SkipAnimUpdate;
	static RwBool m_SkipSimpleMaterial;
	static RwBool m_SkipAdge;

	// For NPC, MOB, VEHICLE spherical enviroment mapping texture
	RwTexture* m_pSEMTex;

	RwBool m_PetrifySkillActivated;

protected:
	void	CreateToonData(const RwChar *szTexName, const RwChar *szTexPath);
	RwBool	CreateAnim(RwUInt32 uiAnimKey, RwReal fStartTime = 0.f, RwBool	bLoop = TRUE);

	RwBool	SetThreadSafeProperty(const CNtlPLProperty *pData);
	RwBool	CreateScheduling(const SPLEntityCreateParam * pParam);
	RwBool	CreateThreadSafe(void);

	void	SetApplyRunTimeAlpha(RwBool bFlag);

 	virtual RwSphere*	GetBoundingSphere();
// 	virtual void		CalcBoundingSphere();

	void	UpdatePreBoneScale();
	void	UpdatePostBoneScale();

	// Loop Effect ����
	void    AddLoopEffect(SLoopEffect* pLoopEffect) {m_listLoopEffect.push_back(pLoopEffect);} ///< LoopEffect List�� LoopEffect�� �߰��Ѵ�.
	void    ClearLoopEffect();                                                                 ///< LoopEffect List�� ����ִ� EffectInstance���� �Ҹ��Ų��.
	RwBool  IsExistLoopEffect(const RwChar* szEffectName, const RwChar* szBoneName);           ///< LoopEffect List�ȿ� �̸�-Bone ���� LoopEffect�� �ִ��� Ȯ���Ѵ�.

	// Loop Sound ����
	void    AddLoopSound(SOUND_HANDLE hSound) {m_listLoopSound.push_back(hSound);}             ///< LoopSound List�� SoundHandle�� �߰��Ѵ�.
	void    ClearLoopSound();                                                                  ///< LoopSound List�� ����ִ� LoopSound���� �Ҹ��Ѵ�.
	RwBool  IsExistLoopSound(RwChar* szSoundName);                                             ///< LoopSound List�� ������ SoundHandle�� �ִ��� Ȯ���Ѵ�.

	// Animation Event ����    
	virtual void   OnEventAnimEnd(SEventAnimEnd* pEventAnimEnd);                               ///< Anim End Event�� ó���Ѵ�.
	virtual void   OnEventHit(SEventAnimHit* pEventHit);    
	virtual void   OnEventWeightTime(SEventWeightTime* pEventTime);
	virtual void   OnEventVisualSound(SEventSound* pEventSound);
	virtual void   OnEventTraceEffect(SEventTrace* pEventTrace);                                ///< Trace Effect�� �����Ѵ�.
	virtual void   OnEventVisualEffect(SEventVisualEffect* pEventVisualEffect);                 ///< Visual Effect Event�� ó���ϰ�, Visual Effect�� �����Ѵ�.
	virtual void   OnEventSubWeapon(SEventSubWeapon* pEventSubWeapon);                          ///< SubWeapon Event�� ó���Ѵ�.
	virtual void   OnEventPostEffect(SEventPostEffect* pEventPostEffect);						///< Post Effect Event�� ó���Ѵ�.
	virtual void   OnEventSummonPet(SEventSummonPet* pEventSummonPet);							///< Summon Pet Event�� ó���Ѵ�.
	virtual void   OnEventAlphaFade(SEventAlpha* pEventAlpha);                                  ///< Alpha Fade Event�� ó���Ѵ�.
	virtual void   OnEventFootStep(SEventFootStep* pEventFootStep);
	virtual void   OnEventDirect(SEventDirect* pEventDirect);                                   ///< ����� �̺�Ʈ
    virtual void   OnEventColorChange(SEventColorChange* pEventColorChange);                    ///< ���� ���� �̺�Ʈ ó��
    virtual void   OnEventStretch(SEventStretch* pEventStretch);                                ///< �� �ø��� �̺�Ʈ
    virtual void   OnEventTrigger(SEventTrigger* pEventTrigger);                                ///< Ʈ���� �̺�Ʈ
    virtual void   OnEventSkillCancel(SEventSkillCancel* pEventSkillCancel);                    ///< ��ų ĵ�� �̺�Ʈ

public:
	void* operator new(size_t size);
	void operator delete(void *pObj);

	virtual RwBool	Create(const SPLEntityCreateParam *pParam = NULL);
	virtual RwBool	Update(RwReal fElapsed);
	virtual RwBool	Render();
	virtual RwBool	RenderToTexture();
	

	// Occluder Proxy ���� ����.
	virtual RwBool CreateOccluderProxy();

#ifdef dNTL_WORLD_CULLING_NEW
	virtual RwBool	CullingTest(RwCamera* pRwCamera, RwUInt16 uiRenderFrame);
#else
	virtual RwBool	CullingTest(RwCamera* pRwCamera);
#endif
    virtual RwBool  IsCullingTestAllAtomic();                                       ///< ���� ������ �ִϸ��̼��� Culling Atomic üũ���� ��ȯ�Ѵ�.

	virtual RwBool	SetProperty(const CNtlPLProperty *pData);
	virtual void	Destroy();

	virtual void CallSchedulingResource(CNtlPLResource *pResource);
	SCharScheduleResInfo *GetCharScheduleResInfo() { return &m_sScheduleResInfo; }
	virtual RwBool IsSchedulingLoadingComplete() {return m_sScheduleResInfo.bLoadComplete;}

	virtual void AddWorld(void);
	virtual void RemoveWorld(void);
	RwBool	IsExistWorld();

	virtual void SetVisible(RwBool bVisible);    
	virtual void SetPicking(RwBool bPicking);

	virtual void SetCullFlags(RwUInt32 uiFlag, RwBool bCulled);
	virtual void SetCullFlags(RwUInt32 uiFlag);

	virtual RwFrame*    GetFrame();
	virtual RwMatrix&   GetMatrix();
	virtual void        SetMatrix(RwMatrix& matWorld);    
    RpClump*            GetClump();
    RpAtomic*           GetAtomic(const std::string& strName);
    RpHAnimHierarchy*   GetBaseHierarchy();
    void                UpdateMaterialSkinInfo();                                               ///< Atomic�� Material ������ �����Ѵ�. (�������ν� ���)

    // �� ����
    RwMatrix*       GetBoneMatrix(const RwChar *pBoneName);
    RwFrame *       GetBoneByName(const RwChar *pBoneName);
    RwUInt32        GetBoneIndex(const RwChar* pBoneName);
    STypeBoneData*  GetBoneData() {return m_pTypeBoneData;}
    RwChar*         GetBoneName(int nBoneIndex);                                                ///< Bone�� �̸��� ��ȯ�Ѵ�.
    void            SetSBoneStretchTargetPos(const RwV3d& vTargetPos, const RwChar* szAxisBone);///< Bone Stretch�̺�Ʈ�� Ÿ���� �����Ѵ�

	virtual void SetPosition(const RwV3d *pPos);
	RwV3d	GetPosition();

	virtual void SetDirection(const RwV3d *pDir);
	RwV3d	GetDirection();
	RwV3d	GetRight();    
	RwV3d   GetUp();

	void	SetAngleDelta(const RwReal fAngleDeltaY);

	void	SetAngleY(const RwReal fAngleY);
	RwReal	GetAngleY() { return m_vAngle.y; }

	void    SetAngleX(const RwReal fAngleX);
	RwReal	GetAngleX() { return m_vAngle.x; }

	virtual void   SetScale(RwReal fScale);														///< ���Ƿ� Scale�� ����(Instance)
	virtual RwReal GetScale();                                                                  ///< ���Ƿ� ������ Scale�� ��ȯ

	void	SetBaseScale(RwReal fBaseScale);													///< BaseScale ����
	RwReal  GetBaseScale();                                                                     ///< ������ BaseScale�� ��ȯ�Ѵ�.
	void	SetPosOffset(RwV3d *pPos);															///< Bone Scale ������� ���� �������� �����ϴ� �Լ�

	RwBool	SetAllAnimation(RwUInt32 uiAnimKey, RwReal fStartTime = 0.f, RwBool	bLoop = TRUE);  ///< Set All Animation
	RwBool	SetBaseAnimation(RwUInt32 uiAnimKey, RwReal fStartTime = 0.f, RwBool bLoop = TRUE); ///< Set Base Animation(Client ����)
	RwUInt32 GetCurBaseAnimKey() {return m_sBaseAnimPlayInfo.m_uiAnimKey;};                     ///< ���� �÷��̵ǰ� �ִ� Anim Key�� ��ȯ�Ѵ�.    
	RwBool	IsExistAnim(RwUInt32 uiAnimKey);													///< uiAnimKey�� Animation�� �ִ���
	RwBool	SetBlend(EBlendType eBlendType, RwReal fBlendAllpha = 0.f, RwReal fBlendInterval = 0.1f);///< Animation Blend (fBlendAlpha = 1.f �̸� Blend�� �ȵȴ�.)
	void	SetAnimSpeed(RwReal fSpeed);														///< Animation�� Speed Default(1.f)
	RwReal  GetAnimSpeed();                                                                     ///< Animation�� Speed�� ��ȯ�Ѵ�.
	void	SetAnimUpdate(RwBool bAnimUpdate);													///< Animation�� Update�� ���� ����
	RwBool	GetAnimUpdate();																	///< Animation�� Update�� �ϴ��� �˻��ϴ� �Լ�
	RwReal	GetBaseCurrentAnimTime();															///< ���� Base Layer Animation�� �ð��� ��� �Լ�
	RwReal	GetBaseDurationAnimTime();															///< ���� Base Layer Animation�� ��ü �ð��� ��� �Լ�
	void    SetBaseCurrentAnimTime(RwReal fCurrTime);								    		///< �ð��� ������ �ִ� �Լ��� �ʿ�
	RwBool	GetBaseCurrentAnimEnd();
	SAnimPlayInfo	*GetBaseAnimPlayInfo();														///< ���� Animation�� ���� ������ ��´�.
	RwReal  GetDurationAnimTime(RwUInt32 uiAnimKey);											///< uiAnimKey�� �ش��Ѵ� Animation�� �ð��� ��´�.
    void    OnAfterAnimEventRun();                                                              ///< ���� �ð� ������ ��� Anim Event�� �����Ų��.

	RwReal	GetWidth();																			///< Character Width (x)
	RwReal	GetHeight();																		///< Character Height (y)
	RwReal	GetDepth();																			///< Character Depth (z)	
	RwReal	GetMaxExtent();
	RwReal	GetFastMaxExtent();

	RwBool SetChangeEquipCItem(CNtlPLItem* _pItem, RwBool _bAttach, RwUInt32 _CBitSet);
	RwBool SetRemoveEquipCItem(CNtlPLItem* _pItem, RwUInt32 _CBitSet);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 1. pItem		: Change �Ǵ� Remove �Ϸ��� Item �̴�.
	// 2. bAttach	: Subweapon ���� Flag, Subweapon �� ��� �� Flag�� FALSE���� �����δ� Attach ���� �ʴ´ٴ� ���� �ǹ��Ѵ�.
	// 3. _CBitSet	: Costume ���� BitFlag Set �̸� �ݵ�� Costume �� ��쿡�� �Է��Ѵ�.
	//				  ���� BitFlag Set ���� 0xFFFFFFFF �� ���� ������ ����� ������ 0xFFFFFFFF�� �ƴ� ���� ���� Attach �Ǵ� Detach �ȴٴ� �ǹ��̴�.
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// < ���� >
	// ���� Interface�� ����Ҷ� �����ؾ� �� ������ ������ ����.
	// BitSet�� �ش��ϴ� ���޽��� �ܼ��� Lib���������� attach, detach�ȴ�. ������ �� �Լ��� �׻� �������� ������Ѿ� �Ѵ�.
	// �� �Լ��� ���� ������ �� ����������� item�� �԰ų� ���ԵǸ� �ٽ� �� item������ default item�κ��� �������ų� �������� �����̴�.
	// �׻� Costume���õ� �Ա� interface�� �������� �����Ѵ�. �ݴ�� �������� �׻� ���� �����Ѵ�. ������ �����̴�.
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual RwBool	SetChangeEquipItem(CNtlPLItem *pItem, RwBool bAttach = TRUE, RwUInt32 _CBitSet = dCOSTUME_BITSET_INVALID);
	virtual RwBool	SetRemoveEquipItem(CNtlPLItem *pItem, RwUInt32 _CBitSet = dCOSTUME_BITSET_INVALID);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Toon edge visibiltity�� �����ϴ� �Լ�
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ȣ���ϸ� Toon edge rendering�� ���ų� �Ӽ� �ִ�.
	// �� �Լ��� ȣ���ϰ� �Ǹ� ���������� Atomic�� Flag�� ���� �ǹǷ� ���������� �����Ͽ��� �Ѵ�.
	// Edge�� �� ���¿��� ������ ���� �κ� mesh�� �Դ°��, ���°���� ĳ������ �ܰ����º�ȭ�� ���� �� �Լ��� ȣ��Ǿ�� �Ұ��̴�.
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	VOID SetToonEdgeVisibility4CurEquipItem(RwBool _Visibility);

	void UpdateCharacterAtomicList();

	CNtlPLEquipItem* GetEquipItem() {return m_pEquipItem;}
	RwBool  SetItemGradeEffect(ENtlPLItemGrade eGrade);                                         ///< ���� �����ϰ� �ִ� ���⿡ Grade Effect�� �����Ѵ�.

	SToonData	*GetToonData() { return &m_ToonData; }											///< Toon Data�� ��´�.							

	void SetColor(RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue);								///< Base Color
	RwRGBA	*GetColor() { return &m_sColor; }

	void SetAddColor(RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue);
	RwRGBA *GetAddColor() { return &m_sAddColor; }

	virtual void SetAlpha(RwUInt8 byValue);																///< Base Alpha
	virtual void SetWeightAlpha(RwReal fWeightValue);													///< Weight Alpha
	virtual void SetAtomicWeightAlpha(const RwChar *pAtomicName, RwReal fWeightValue);                  ///< Atomic Weight Alpha Value�� �����Ѵ�.

	virtual void SetSkinColor(RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue);					///< Skin Color
	RwRGBA	*GetSkinColor() { return &m_sSkinColor; }		

	virtual void SetHeadColor(RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue);					///< Head Color
	RwRGBA *GetHeadColor() { return &m_sHeadColor; }

	virtual void SetInkColor(RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue);					///< Ink Color
	virtual void SetInkThickness(RwReal fThickness = DEFAULT_INK_THICKNESS);					///< Ink Thickness

	virtual int	CallBackBaseAnim(void* pAnimEvent);											///< Animation Event�� �޴� Callback �Լ�
	static RpAtomic *RenderCallBack(RpAtomic *pAtomic);

	// Link Effect ����
	VecLinkEffect*      GetVecLinkEffect() {return &(m_LinkEffectInstance.m_vecLinkEffect);}	///< LinkEffect Vector�� ��ȯ�Ѵ�.
    CNtlInstanceEffect* AttachLinkEffect(SEventLinkEffect* pEventLinkEffect);					///< Link Effect�� Attach ��Ų��.
	RwBool              DetachLinkEffect(CNtlInstanceEffect* pLinkEffect);                      ///< Link Effect�� Detach ��Ų��.

	RwV3d  GetFaceCameraPos() { return m_pProperty->GetFaceCameraPos();}							///< Get Face Camera Position
	RwV3d  GetFaceCameraLookAt() { return m_pProperty->GetFaceCameraLookAt();}					///< Set Face Camera LookAt Height 
    RwReal GetAlphaDistance();                              

	RwBool IsApplyGroundPitchAngle(void);

	static void fpRenderCB(void* _pParam);

	// Animation update�� skip�Ҷ� ������ �߻��� ������ �ִ�. ex) Ʃ�丮�󿡼� ���� Ʈ�������� �̷������ ���ϰ� char animation���θ� ó���Ҷ����
	// ���� ���� ������ ����� �κп� �����ϰ� �����Ѵ�; Renderstate������ ������ ���� �������� ����ϸ� �ȴ�.
	static void SetSkipAnimUpdate(RwBool _Skip = TRUE);

	// Simple material�κ��� game option check�� ���� ������ �Ǵ��ϱ� ���� �Լ��̴�.
	static void SetSkipSimpleMaterial(RwBool _Skip = TRUE);
	static RwBool GetSkipSimpleMaterial(void);

	// edge�� skip ��Ų��.(����)
	static void SetSkipEdge(RwBool _Skip = FALSE);
	static RwBool GetSkipEdge(void);

	void	SetDXT1AlphaCheck(RwBool _DXT1AlphaCheck);

	// simple material; simplify textures
	RwBool	GetSimpleMaterial() { return m_SimpleMaterial; }
	VOID	SetSimpleMaterial(RwBool _SimpleMaterial);

	// Petrify
	RwBool	GetPetrifyMaterial() { return m_PetrifySkillActivated; }
	VOID	SetPetrifyMaterial(RwBool _PetrifyFlag);

	// Spherical Enviroment Map
	RwTexture* GetSEM() { return m_pSEMTex; }

	// enviroment map uv ani toggling
	static VOID ToggleEMUVAni(RwBool _Visibility);
};

#endif
