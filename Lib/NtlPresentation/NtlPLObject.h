/*****************************************************************************
*
* File			: NtlPLObject.h
* Author		: HyungSuk Jang
* Copyright	: (��)NTL
* Date			: 2005. 8. 11	
* Abstract		: Presentation layer object entity class
*****************************************************************************
* Desc         : 
*
*****************************************************************************/

#ifndef __NTL_PLOBJECT_H__
#define __NTL_PLOBJECT_H__

// ���� ��� �ּ�ó��.
// #define FADE_OBJECT_TIME        2.0f                ///< Object�� Fade In/Out�� �ɸ��� �ð� 
#define FADE_EFFECT_GAP_TIME    1.0f                ///< Effect�� ǥ�õ��� ���Ŀ� Object�� ǥ�������� Gap

#include "NtlPLAttach.h"
#include "NtlPLGlobal.h"
#include "NtlAtomic.h"
#include "NtlPLResource.h"
#include "NtlPLObjectProperty.h"
#include "NtlPLUVAnim.h"
#include "NtlPLLinkEffect.h"
#include "NtlAnimLayer.h"
#include "NtlPLEntityRenderHelpers.h"
#include "OccluderProxy.h"
#include "NtlPLObjectType.h"

// #include <vector>
// using std::vector;

typedef union
{
	RwTexCoords uv;
	RwUInt32    intUV[2];
}
LtMapIntUV_;

struct sSCHEDULING_LM_ATOM_PROP
{
	sSCHEDULING_LM_ATOM_PROP()
	{
		_pTexCoords = NULL;
	}

	~sSCHEDULING_LM_ATOM_PROP()
	{
		NTL_ARRAY_DELETE(_pTexCoords);
	}

	RwChar			_szAtomName[64];
	RwChar			_szTexName[64];
	RwInt32			_UVCnt;
	RwTexCoords*	_pTexCoords;
};

struct sSCHEDULING_LM_PROP
{
	RwUInt32	_uiLtMapObjectFlags;
	RwUInt32	_uiLtMapMaterialFlags;

	vector<sSCHEDULING_LM_ATOM_PROP*> _vecSchedulingLMAtomProp;
};

/// �����층 �ε��� �ʿ��� ������ ��� ����ü
struct SObjectSchedulingInfo
{
    RwBool      bLoadComplete;
    RwUInt32    uiAnimKey;
    RwReal      fAnimStartTime;
    RwBool      bAnimLoop;

    SObjectSchedulingInfo()
    {
        bLoadComplete = FALSE;
        uiAnimKey = 0;
        fAnimStartTime = 0.0f;
        bAnimLoop = FALSE;
    }
};

class CNtlPLEntityAlphaWeightBlend;

struct SPLObjectCreateParam : public SPLEntityCreateParam
{
	RwBool bLoadMap;            // ���� �ε��Ҷ�(Fade�� ������� �ʾƾ� �Ҷ�)�� True, �ƴϸ� False
};

struct SCollisionInfo;
struct RpHAnimHierarchy;
struct RwFrame;
struct SPLLightObjectCreateParam;

class CNtlPLResource;
class CNtlWorldShadow;

//////////////////////////////////////////////////////////////////////////
// dNTL_WORLD_FILE : DEFINE
//////////////////////////////////////////////////////////////////////////
#ifdef dNTL_WORLD_FILE

class CNtlPLObject : public CNtlPLAttach, public COccluderProxy
{
public:
	/// Fade System�� ���� Flag��
	enum EObjectFadeState
	{
		FADE_VISIBLE,
		FADE_IN_OBJECT,
		FADE_IN_EFFECT,
		FADE_OUT_OBJECT,
		FADE_OUT_EFFECT,
		FADE_NOT_VISIBLE,
	};

public:
	void* operator new(size_t size);
	void operator delete(void *pObj);

	CNtlPLObject();
	virtual ~CNtlPLObject();

	virtual RwBool Create( const SPLEntityCreateParam * pParam = NULL );
	virtual void Destroy(void);
	virtual RwBool Update(RwReal fElapsed);

	virtual RwBool Render(void);
	virtual RwBool RenderToTexture();

	// Occluder Proxy ���� ����.
	virtual RwBool CreateOccluderProxy();

#ifdef dNTL_WORLD_CULLING_NEW
	virtual RwBool CullingTest(RwCamera* pRwCamera, RwUInt16 uiRenderFrame);
#else
	virtual RwBool CullingTest(RwCamera* pRwCamera);
#endif
	virtual RwBool  IsCullingTestAllAtomic();                                       ///< ���� ������ �ִϸ��̼��� Culling Atomic üũ���� ��ȯ�Ѵ�.

	virtual RwBool SetProperty(const CNtlPLProperty *pData);
	virtual CNtlPLObjectProperty* GetProperty() {return m_pProperty;}

	virtual void AddWorld(void);
	virtual void RemoveWorld(void);

	virtual void CallPreSchedulingResource(void);
	virtual void CallSchedulingResource(CNtlPLResource *pResource);
	virtual void CallSchedulingResourceOnly();

	virtual void SetPosition(const RwV3d *pPos);
	virtual RwV3d GetPosition(void);

	virtual void SetScale( const RwV3d * pScale );
	virtual const RwV3d * GetScale( void ) const;
	virtual void SetRotate(RwReal fXAngle, RwReal fYAngle, RwReal fZAngle);
	virtual const RwV3d* GetRotate(void) const;    
	virtual RwV3d GetDirection();

	virtual RwReal GetVisibleCullingDistance(void);

	virtual void  SetVisible(RwBool bVisible);													///< ������Ʈ�� ǥ�� ������ �����Ѵ�.
	void SetEffectVisible(RwBool bVisible);														///< ����Ʈ�� ǥ�� ������ �����Ѵ�.

	void SetAlpha(RwUInt8 byValue);																///< ������Ʈ�� Alpha�� �����Ѵ�.
	void SetColor(RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue);								///< ������Ʈ�� Color�� �����Ѵ�.
	RwRGBA	*GetColor() { return &m_sColor; }													///< ������Ʈ�� Color�� ��´�.

	void SetAddColor(RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue);
	RwRGBA	*GetAddColor() { return &m_sAddColor; }

	virtual RwFrame*	GetFrame(void);

	void				SetMatrix( RwMatrix & matWorld );
	RwMatrix&			GetMatrix(void);
	RwMatrix*			GetBoneMatrix(const RwChar *pBoneName);

	void				GetBoneName(std::vector<std::string>& vecBoneName);

	virtual RwSphere*	GetBoundingSphere();
	virtual void		CalcBoundingSphere();

	RwBool			IsActiveUpdate( void ) { return m_bActiveUpdate; }
	RwBool          IsSchedulingLoadingComplete() {return m_sScheduleInfo.bLoadComplete;}       ///< ������ �ε��� �Ϸ�

	RpClump *GetClump( void ) const;

	RwBool          SetUVAnim(const RwChar* szUVAnimFileName);									///< UVAnim�� �����Ѵ�.
	CNtlPLUVAnim*   GetUVAnim() {return m_pUVAnim;}												///< UVAnim ��ü�� ��ȯ�Ѵ�.

	RwBool          SetAnimation(const RwChar* szAnimFileName);									///< �ִϸ��̼��� �����Ѵ�.
	virtual RwBool	SetTriggerAnimation(RwUInt32 uiAnimKey, RwReal fStartTime = 0.0f, RwBool bLoop = TRUE);				///< Trigger Animation�� ����Ѵ�.
	virtual int		CallBackBaseAnim(void* pEventData);										///< Animation Event�� CallBack �Լ�    
	void            SetAnimUpdate(RwBool bPlay) {m_bAnimPlay = bPlay;}								///< �ִϸ��̼� �÷���/������ �����Ѵ�.
	RwBool			GetPlayAnim() { return m_bAnimPlay; }										///< �ִϸ��̼��� �÷��̰� �Ǵ���
	RwBool			SetPlayAnimTime(RwReal fStartAnimTime);										///< Animation Play ���� �ð� (0.f - 1.f)
	RwBool			SetPlayAnimSpeed(RwReal fAnimSpeed);										///< Animaiton Speed (1.f: Default )
	RwReal			GetBaseCurrentAnimTime();															///< ���� Base Layer Animation�� �ð��� ��� �Լ�
	RwReal			GetAnimPlayTime(RwUInt32 uiAnimKey);										///< Key�� �ش��ϴ� Anim�� Play Time�� ��ȯ�Ѵ�.
	RwReal			GetBaseDurationAnimTime();													///< Animation�� Play Time�� ��ȯ�Ѵ�.
	void			SetBaseCurrentAnimTime(RwReal fCurrTime);								    		///< �ð��� ������ �ִ� �Լ��� �ʿ�

	RwBool			GetEnableShadow();															///< Shadow�� ���������

	// Doodads PSM
	RwBool				GetEnableGenShadowMap();													///< ShadowMap�� ������ �ؾ� �ϴ���
	RwBool				AreThereObjPSMap();
	VOID				DeleteDoodadShadow();
	ENTITY_ATOMIC_VEC*	GetAtomicList();															///< Atomic List Return�� �Ѵ�.	
	VOID				SetAtomicPSMap();

	virtual const RwBBox* GetBoundingBox(void) {return &m_bbox;}								///< Bounding Box�� ��ȯ�Ѵ�.

	// Link Effect ����
	VecLinkEffect*      GetVecLinkEffect() {return &(m_LinkEffectInstance.m_vecLinkEffect);}	///< LinkEffect Vector�� ��ȯ�Ѵ�.
	CNtlInstanceEffect* AttachLinkEffect(SEventLinkEffect* pEventLinkEffect);					///< Link Effect�� Attach ��Ų��.
	RwBool              DetachLinkEffect(CNtlInstanceEffect* pLinkEffect);						///< Link Effect�� Detach ��Ų��.

	// World Editor�� ���� �Լ�
	virtual RwBBox  GetTriggerAABBInfo();														///< ���忡������ Ʈ���� ������ ����ϱ� ���� AABB�� ������ ��ȯ�Ѵ�.
	virtual RwBBox  GetTriggerAABBInfo( const RwV3d& vPos, 
		const RwV3d& vRotate, 
		const RwV3d& vScale);	

	// Fade System ����
	RwBool          UpdateFadeSystem();                                                         ///< ������ Culling Distance�� ���� Object�� Fade ��Ų��.
	void            SetFadeEnable(RwBool bEnable);                                              ///< Fade Enable ������ �����Ѵ�

	void    SetTransform(void);

	// Milepost ���� ������Ƽ
	RwUInt32        GetMilepostID() {return m_uiMilepostTextID;}                                ///< Milepost Text ID�� ��ȯ�Ѵ�.
	void            SetMilepostID(RwUInt32 uiMilepostTextID) {m_uiMilepostTextID = uiMilepostTextID;} ///< Milepost Text ID�� �����Ѵ�.

	// Toon ����
	void            CheckToonData();                                                            ///< Toon ������ �������� Ȯ���Ѵ�.
	SToonData*      GetToonData() {return m_pToonData;}

	void		ResetUV();
	RwBool		CheckUVsSetUpForLightMapping();
	RwUInt32	GetObjectSerialID()								{ return m_uiObjectSerialID; }
	void		SetObjectSerialID(RwUInt32 uiObjectSerialID) { m_uiObjectSerialID = uiObjectSerialID; }
	void		DeleteLightmapFile();
	void		CheckLightmapFlags();

	// attach light
	virtual void		AttachLightObject();	

	RwBBox				GetDefaultAABB();

	// object type
	RwUInt32			GetObjectType();
	void				SetObjectType(RwUInt32 uiObjectType);
	CNtlPLObjectType*	GetObjectTypePtr() { return m_pObjectType; }

protected:

	RwBool	SetThreadSafeProperty(const CNtlPLProperty *pData);
	RwBool	CreateScheduling(const SPLEntityCreateParam * pParam);
	RwBool	CreateThreadSafe(void);

	RwBool  CreateAnim();																		///< Anim ���� ������ ��ü�� �����Ѵ�.
	RwBBox  CreateDefaultAABB();																///< Property�� AABB������ ������ �⺻ AABB������ �����Ѵ�	
	RwBool  UpdateFading(RwReal fElapsedTime);                                                  ///< ���̵��Ѵ�.

	// Loop Effect ����
	void    AddLoopEffect(SLoopEffect* pLoopEffect) {m_listLoopEffect.push_back(pLoopEffect);} ///< LoopEffect List�� LoopEffect�� �߰��Ѵ�.
	void    ClearLoopEffect();                                                                 ///< LoopEffect List�� ����ִ� EffectInstance���� �Ҹ��Ų��.
	RwBool  IsExistLoopEffect(const RwChar* szEffectName, const RwChar* szBoneName);           ///< LoopEffect List�ȿ� �̸�-Bone ���� LoopEffect�� �ִ��� Ȯ���Ѵ�.

	// Loop Sound ����
	void    AddLoopSound(SOUND_HANDLE hSound) {m_listLoopSound.push_back(hSound);}             ///< LoopSound List�� SoundHandle�� �߰��Ѵ�.
	void    ClearLoopSound();                                                                  ///< LoopSound List�� ����ִ� LoopSound���� �Ҹ��Ѵ�.
	RwBool  IsExistLoopSound(RwChar* szSoundName);                                             ///< LoopSound List�� ������ SoundHandle�� �ִ��� Ȯ���Ѵ�.
	void    UpdateLoopSoundPos();                                                              ///< LoopSound ��ġ�� ������Ʈ �Ѵ�.

	// Animation Event ����
	virtual void OnEventAnimEnd(SEventAnimEnd* pEventAnimEnd);
	virtual void OnEventVisualSound(SEventSound* pEventSound);									
	virtual void OnEventVisualEffect(SEventVisualEffect* pEventVisualEffect);    
	virtual void OnEventAlphaFade(SEventAlpha* pEventAlpha);
	virtual void OnEventTMQ(SEventAnimCinematic* pEventTMQ);
	virtual void OnEventExplosion(SEventExplosion* pEventExplosion);

	void    SetAtomicWeightAlpha(const RwChar *pAtomicName, RwReal fWeightValue);               ///< Atomic Weight Alpha Value�� �����Ѵ�.

	void	AddSceneUpdate();
	void	RemoveSceneUpdate();

public:
	void			SetLightMapMaterialFlags(RwUInt32 uiFlags);
	void			SetLightMapObjectFlags(RwUInt32 uiFlags);
	RwUInt32		GetLightMapMaterialFlags();
	RwUInt32		GetLightMapObjectFlags();
	void			FreeSchedulingLTProp();
	void			AllocSchedulingLTProp();
	RwBool			IsRpWorldSectorList(RpWorldSector* pRpWorldSector);
	void			UpdateRpSectorOBBCheck();

	// attach dogi gym. emblem texture. careful for Destroy()
	RwBool			SetAtomicEmblemMap(RwTexture* _pEmblemMap);
	RwBool			GetEmblemMarkEnabled();
	void			DestroyEmblemMap();

	// dojo	
	CNtlPLEntity*	GetDojo()							{ return m_pDojoEntity; }
	void			SetDojo(CNtlPLEntity* pDojoEntity)	{ m_pDojoEntity = pDojoEntity; }

public:
	static RpAtomic *RenderCallBack(RpAtomic *pAtomic);

public:
	//static void					SetFarPlane(RwReal fFarDist);

protected:
	//static RwPlane				g_planeFar;

#ifdef dNTL_WORLD_TOOL_MODE
public:
	static void			SaveSwapFile(RwReal x, RwReal y, RwReal z);
	static void			LoadSwapFile(RwReal x, RwReal y, RwReal z);
#endif

protected:
	sSCHEDULING_LM_PROP*		m_pSchedulingLMProp;
	SObjectSchedulingInfo       m_sScheduleInfo;        ///< �����층 �ε� ���� ���� 
	RwUInt32					m_uiObjectSerialID;

	CNtlPLObjectType*			m_pObjectType;

	RwBool						m_bActiveUpdate;
	RwBool						m_bLoadMap;

	CNtlPLResource *			m_pClumpResource;
	ENTITY_ATOMIC_VEC	        m_vecAtomicList;         ///< ���� Clump�� �����ϰ� �ִ� Atomic���� ����Ʈ
	FRAME_MAP				    m_mapFrame;				 ///< Bone Info

	RwV3d						m_vModelAngle;
	RwV3d						m_vModelScale;
	RwV3d						m_vWorldPosition;

	CNtlPLObjectProperty*       m_pProperty;            ///< ������Ʈ ������Ƽ ��ü	

	CNtlPLUVAnim*               m_pUVAnim;              ///< UVAnim ���� ��ü                
	RpHAnimHierarchy*           m_pBaseHierarchy;		///< Base Hierarchy
	CNtlPLResource*             m_pAnimResource;        ///< Anim Resource
	RwBool                      m_bAnimPlay;            ///< Anim Play ����
	RwBool						m_bHaveAnim;			///< Anim ���� ����.

	RwReal						m_fAnimSpeed;			///< Anim Speed

	RwRGBA						m_sColor;				///< Color				
	RwRGBA						m_sAddColor;			///< AddColor

	RwSphere					m_BSphere;				///< Position�� ������� ���� BoundSphere
	RwSphere					m_BSphereCur;			///< Position�� ����� BoundingSphere : GetBoundingSphere�� ȣ���ϰ� �Ǹ� ������Ʈ �ȴ�.

	CNtlPLLinkEffect            m_LinkEffectInstance;   ///< LinkEffect Instance���� �����ϴ� ��ü

	RwBBox                      m_bbox;                 ///< Object�� Bounding Box

	// Fade System ����
	EObjectFadeState            m_eFadeState;           ///< ���� Object�� Fade State
	RwReal                      m_fPrevCameraDistance;  ///< ������ ī�޶���� �Ÿ�
	RwReal                      m_fFadeTime;            ///< Fade Time    
	CNtlPLEntityAlphaWeightBlend* m_pFadeBlend;         ///< Fade Blend ������ ���� ���� ��ü

	// Trigger Object�� Animation ����
	CNtlAnimLayer*				m_pAnimLayer;			///< �ִϸ��̼� ���̾�
	CNtlInstanceAnimTable*		m_pInstanceAnimTable;	///< Animation Resource Instance Table
	RwUInt32					m_uiCurAnimKey;			///< ���� ����ǰ� �ִ� AnimKey

	ListSoundHandle				m_listLoopSound;        ///< LoopSound���� HANDLE List
	ListLoopEffect				m_listLoopEffect;       ///< LoopEffect�� list

	// ���� ������Ʈ �׸��� ����
	vector<CNtlWorldShadow*>    m_vecNtlWorldShadow;

	RwUInt32                    m_uiMilepostTextID;      ///< ����ǥ�� ���ɶ� ����� �ؽ�Ʈ ���̺��� ID

	// ������
	SToonData*				    m_pToonData;			///< Toon Ink, Toon Paint, Toon Resource

	// �ε���
	CNtlOBB						m_OBB;					///< �ε���� ���Ǹ�, RpWorldSector�� �˻��ϱ� ���� ���.
	vector<RpWorldSector*>		m_vecRpWorldSector;		///< �ε���� ���Ǹ�, ���ԵǾ� �ִ� RpWorldSectorlist

	// Dojo
	CNtlPLEntity*				m_pDojoEntity;

	// attach light
	struct SLightObjectAttachData
	{
		RwV3d						vPos;
		RwChar						chBoneName[MAX_ATTR_BONE_NAME];
		SPLLightObjectCreateParam*	pPLLightObjectCreateParam;
	};
	std::vector<SLightObjectAttachData*> m_vecAttachLightParam;

public:
	virtual RwBool		LoadFromFile(FILE* pFile, EActiveWorldType eActiveWorldType);
	virtual RwBool		SaveIntoFile(FILE* pFile, EActiveWorldType eActiveWorldType);
	static	RwInt32		SkipToFile(FILE* pFile, EActiveWorldType eActiveWorldType, RwUInt32 uiObjectType);

	static	BYTE*		SaveIntoFileFromFileMem(FILE* pFile, BYTE* pFileMem, EActiveWorldType eActiveWorldType, RwUInt32 uiObjectType);
	static	BYTE*		SaveIntoFileFromFileMemVisibilityDistance(FILE* pFile, BYTE* pFileMem, EActiveWorldType eActiveWorldType, RwUInt32 uiObjectType, RwReal fVD, RwReal fMinVD, RwReal fMaxVD);
	static	BYTE*		SkipToFileMem(BYTE* pFileMem, EActiveWorldType eActiveWorldType, RwUInt32 uiObjectType);
	static	BYTE*		SkipToFileMemGetEnabledTrigger(BYTE* pFileMem, EActiveWorldType eActiveWorldType, RwUInt32 uiObjectType, RwBool* pResult);
	static	BYTE*		SkipToFileMemGetEnabledPEC(BYTE* pFileMem, EActiveWorldType eActiveWorldType, RwUInt32 uiObjectType, RwBool* pResult);

	// Projection Shadow
	virtual RwBool		SavePSMap(FILE* pFile);
	virtual RwBool		LoadPSMap(FILE* pFile);
	static RwInt32		SkipPSMap(FILE* pFile);

	static	BYTE*		SavePSMapFromFileMem(FILE* pFile, BYTE* pFileMem);
	static	BYTE*		SkipPSMapToFileMem(BYTE* pFileMem);

	// lightmap ����
	virtual RwBool		SaveLightmap(FILE* pFile);
	virtual RwBool		LoadLightmap(FILE* pFile);
	static  RwInt32		SkipLightmap(FILE* pFile);

	static  BYTE*		SaveLightmapFromFileMem(FILE* pFile, BYTE* pFileMem);
	static  BYTE*		SkipLightmapToFileMem(BYTE* pFileMem);

	virtual RwBool		LoadSchedulingLightmapProp(FILE* pFile);

	// Attach LightObject
	virtual RwBool		LoadLightObjectAttachData(FILE* pFile);	
	virtual RwBool		SaveLightObjectAttachData(FILE* pFile);
	static  RwInt32		SkipLightObjectAttachData(FILE* pFile);

	static  BYTE*		SaveLightObjectAttachDataFromFileMem(FILE* pFile, BYTE* pFileMem);
	static  BYTE*		SkipLightObjectAttachDataToFileMem(BYTE* pFileMem);
};

//////////////////////////////////////////////////////////////////////////
// dNTL_WORLD_FILE : DEFINE
//////////////////////////////////////////////////////////////////////////
#else

class CNtlPLObject : public CNtlPLAttach, public COccluderProxy
{
public:
	/// Fade System�� ���� Flag��
	enum EObjectFadeState
	{
		FADE_VISIBLE,
		FADE_IN_OBJECT,
		FADE_IN_EFFECT,
		FADE_OUT_OBJECT,
		FADE_OUT_EFFECT,
		FADE_NOT_VISIBLE,
	};

public:
	void* operator new(size_t size);
	void operator delete(void *pObj);

	CNtlPLObject();
	virtual ~CNtlPLObject();

	virtual RwBool Create( const SPLEntityCreateParam * pParam = NULL );
	virtual void Destroy(void);
	virtual RwBool Update(RwReal fElapsed);

	virtual RwBool Render(void);
	virtual RwBool RenderToTexture();

	// Occluder Proxy ���� ����.
	virtual RwBool CreateOccluderProxy();

#ifdef dNTL_WORLD_CULLING_NEW
	virtual RwBool CullingTest(RwCamera* pRwCamera, RwUInt16 uiRenderFrame);
#else
	virtual RwBool CullingTest(RwCamera* pRwCamera);
#endif
    virtual RwBool  IsCullingTestAllAtomic();                                       ///< ���� ������ �ִϸ��̼��� Culling Atomic üũ���� ��ȯ�Ѵ�.

	virtual RwBool SetProperty(const CNtlPLProperty *pData);
	virtual CNtlPLObjectProperty* GetProperty() {return m_pProperty;}

	virtual void AddWorld(void);
	virtual void RemoveWorld(void);

	virtual void CallPreSchedulingResource(void);
	virtual void CallSchedulingResource(CNtlPLResource *pResource);
	virtual void CallSchedulingResourceOnly();

	virtual void SetPosition(const RwV3d *pPos);
	virtual RwV3d GetPosition(void);

	virtual void SetScale( const RwV3d * pScale );
	virtual const RwV3d * GetScale( void ) const;
	virtual void SetRotate(RwReal fXAngle, RwReal fYAngle, RwReal fZAngle);
	virtual const RwV3d* GetRotate(void) const;    
	virtual RwV3d GetDirection();

	virtual RwReal GetVisibleCullingDistance(void);

	virtual void  SetVisible(RwBool bVisible);													///< ������Ʈ�� ǥ�� ������ �����Ѵ�.
	void SetEffectVisible(RwBool bVisible);														///< ����Ʈ�� ǥ�� ������ �����Ѵ�.

	void SetAlpha(RwUInt8 byValue);																///< ������Ʈ�� Alpha�� �����Ѵ�.
	void SetColor(RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue);								///< ������Ʈ�� Color�� �����Ѵ�.
	RwRGBA	*GetColor() { return &m_sColor; }													///< ������Ʈ�� Color�� ��´�.

	void SetAddColor(RwUInt8 byRed, RwUInt8 byGreen, RwUInt8 byBlue);
	RwRGBA	*GetAddColor() { return &m_sAddColor; }

	virtual RwFrame*	GetFrame(void);

	void				SetMatrix( RwMatrix & matWorld );
	RwMatrix&			GetMatrix(void);
	RwMatrix*			GetBoneMatrix(const RwChar *pBoneName);

	void				GetBoneName(std::vector<std::string>& vecBoneName);

	virtual RwSphere*	GetBoundingSphere();
	virtual void		CalcBoundingSphere();

	RwBool			IsActiveUpdate( void ) { return m_bActiveUpdate; }
    RwBool          IsSchedulingLoadingComplete() {return m_sScheduleInfo.bLoadComplete;}       ///< ������ �ε��� �Ϸ�

	RpClump *GetClump( void ) const;

	RwBool          SetUVAnim(const RwChar* szUVAnimFileName);									///< UVAnim�� �����Ѵ�.
	CNtlPLUVAnim*   GetUVAnim() {return m_pUVAnim;}												///< UVAnim ��ü�� ��ȯ�Ѵ�.

	RwBool          SetAnimation(const RwChar* szAnimFileName);									///< �ִϸ��̼��� �����Ѵ�.
	virtual RwBool	SetTriggerAnimation(RwUInt32 uiAnimKey, RwReal fStartTime = 0.0f, RwBool bLoop = TRUE);				///< Trigger Animation�� ����Ѵ�.
	virtual int		CallBackBaseAnim(void* pEventData);										///< Animation Event�� CallBack �Լ�    
	void            SetAnimUpdate(RwBool bPlay) {m_bAnimPlay = bPlay;}								///< �ִϸ��̼� �÷���/������ �����Ѵ�.
	RwBool			GetPlayAnim() { return m_bAnimPlay; }										///< �ִϸ��̼��� �÷��̰� �Ǵ���
	RwBool			SetPlayAnimTime(RwReal fStartAnimTime);										///< Animation Play ���� �ð� (0.f - 1.f)
	RwBool			SetPlayAnimSpeed(RwReal fAnimSpeed);										///< Animaiton Speed (1.f: Default )
	RwReal			GetBaseCurrentAnimTime();															///< ���� Base Layer Animation�� �ð��� ��� �Լ�
	RwReal			GetAnimPlayTime(RwUInt32 uiAnimKey);										///< Key�� �ش��ϴ� Anim�� Play Time�� ��ȯ�Ѵ�.
	RwReal			GetBaseDurationAnimTime();													///< Animation�� Play Time�� ��ȯ�Ѵ�.
	void			SetBaseCurrentAnimTime(RwReal fCurrTime);								    		///< �ð��� ������ �ִ� �Լ��� �ʿ�

	RwBool			GetEnableShadow();															///< Shadow�� ���������

	// Doodads PSM
	RwBool				GetEnableGenShadowMap();													///< ShadowMap�� ������ �ؾ� �ϴ���
	RwBool				AreThereObjPSMap();
	VOID				DeleteDoodadShadow();
	ENTITY_ATOMIC_VEC*	GetAtomicList();															///< Atomic List Return�� �Ѵ�.
	VOID				SavePSMap(FILE* _pFile);
	VOID				LoadPSMap(FILE* _pFile);
	VOID				SetAtomicPSMap();

	virtual const RwBBox* GetBoundingBox(void) {return &m_bbox;}								///< Bounding Box�� ��ȯ�Ѵ�.

	// Link Effect ����
	VecLinkEffect*      GetVecLinkEffect() {return &(m_LinkEffectInstance.m_vecLinkEffect);}	///< LinkEffect Vector�� ��ȯ�Ѵ�.
	CNtlInstanceEffect* AttachLinkEffect(SEventLinkEffect* pEventLinkEffect);					///< Link Effect�� Attach ��Ų��.
	RwBool              DetachLinkEffect(CNtlInstanceEffect* pLinkEffect);						///< Link Effect�� Detach ��Ų��.

	// World Editor�� ���� �Լ�
	virtual RwBBox  GetTriggerAABBInfo();														///< ���忡������ Ʈ���� ������ ����ϱ� ���� AABB�� ������ ��ȯ�Ѵ�.
	virtual RwBBox  GetTriggerAABBInfo( const RwV3d& vPos, 
		const RwV3d& vRotate, 
		const RwV3d& vScale);	

	// Fade System ����
	RwBool          UpdateFadeSystem();                                                         ///< ������ Culling Distance�� ���� Object�� Fade ��Ų��.
	void            SetFadeEnable(RwBool bEnable);                                              ///< Fade Enable ������ �����Ѵ�

	void    SetTransform(void);

	// Milepost ���� ������Ƽ
	RwUInt32        GetMilepostID() {return m_uiMilepostTextID;}                                ///< Milepost Text ID�� ��ȯ�Ѵ�.
	void            SetMilepostID(RwUInt32 uiMilepostTextID) {m_uiMilepostTextID = uiMilepostTextID;} ///< Milepost Text ID�� �����Ѵ�.

    // Toon ����
    void            CheckToonData();                                                            ///< Toon ������ �������� Ȯ���Ѵ�.
    SToonData*      GetToonData() {return m_pToonData;}

	// lightmap ����
	virtual RwBool		SaveLightmap(FILE* pFile);
	virtual RwBool		LoadLightmap(FILE* pFile);
	static  RwInt32		SkipLightmap(FILE* pFile);

	static  BYTE*		SaveLightmapFromFileMem(FILE* pFile, BYTE* pFileMem);
	static  BYTE*		SkipLightmapToFileMem(BYTE* pFileMem);

	virtual RwBool		LoadSchedulingLightmapProp(FILE* pFile);

	void		ResetUV();
	RwBool		CheckUVsSetUpForLightMapping();
	RwUInt32	GetObjectSerialID()								{ return m_uiObjectSerialID; }
    void		SetObjectSerialID(RwUInt32 uiObjectSerialID) { m_uiObjectSerialID = uiObjectSerialID; }
	void		DeleteLightmapFile();
	void		CheckLightmapFlags();

	// attach light
	virtual void		AttachLightObject();
	virtual RwBool		LoadLightObjectAttachData(FILE* pFile);	
	virtual RwBool		SaveLightObjectAttachData(FILE* pFile);
	static  RwInt32		SkipLightObjectAttachData(FILE* pFile);
		
	static  BYTE*		SaveLightObjectAttachDataFromFileMem(FILE* pFile, BYTE* pFileMem);
	static  BYTE*		SkipLightObjectAttachDataToFileMem(BYTE* pFileMem);

	RwBBox		GetDefaultAABB();

	// object type
	RwUInt32			GetObjectType();
	void				SetObjectType(RwUInt32 uiObjectType);
	CNtlPLObjectType*	GetObjectTypePtr() { return m_pObjectType; }

protected:

	RwBool	SetThreadSafeProperty(const CNtlPLProperty *pData);
	RwBool	CreateScheduling(const SPLEntityCreateParam * pParam);
	RwBool	CreateThreadSafe(void);

	RwBool  CreateAnim();																		///< Anim ���� ������ ��ü�� �����Ѵ�.
	RwBBox  CreateDefaultAABB();																///< Property�� AABB������ ������ �⺻ AABB������ �����Ѵ�	
	RwBool  UpdateFading(RwReal fElapsedTime);                                                  ///< ���̵��Ѵ�.

	// Loop Effect ����
	void    AddLoopEffect(SLoopEffect* pLoopEffect) {m_listLoopEffect.push_back(pLoopEffect);} ///< LoopEffect List�� LoopEffect�� �߰��Ѵ�.
	void    ClearLoopEffect();                                                                 ///< LoopEffect List�� ����ִ� EffectInstance���� �Ҹ��Ų��.
	RwBool  IsExistLoopEffect(const RwChar* szEffectName, const RwChar* szBoneName);           ///< LoopEffect List�ȿ� �̸�-Bone ���� LoopEffect�� �ִ��� Ȯ���Ѵ�.

	// Loop Sound ����
	void    AddLoopSound(SOUND_HANDLE hSound) {m_listLoopSound.push_back(hSound);}             ///< LoopSound List�� SoundHandle�� �߰��Ѵ�.
	void    ClearLoopSound();                                                                  ///< LoopSound List�� ����ִ� LoopSound���� �Ҹ��Ѵ�.
	RwBool  IsExistLoopSound(RwChar* szSoundName);                                             ///< LoopSound List�� ������ SoundHandle�� �ִ��� Ȯ���Ѵ�.
	void    UpdateLoopSoundPos();                                                              ///< LoopSound ��ġ�� ������Ʈ �Ѵ�.

	// Animation Event ����
	virtual void OnEventAnimEnd(SEventAnimEnd* pEventAnimEnd);
	virtual void OnEventVisualSound(SEventSound* pEventSound);									
	virtual void OnEventVisualEffect(SEventVisualEffect* pEventVisualEffect);    
	virtual void OnEventAlphaFade(SEventAlpha* pEventAlpha);
	virtual void OnEventTMQ(SEventAnimCinematic* pEventTMQ);
	virtual void OnEventExplosion(SEventExplosion* pEventExplosion);

	void    SetAtomicWeightAlpha(const RwChar *pAtomicName, RwReal fWeightValue);               ///< Atomic Weight Alpha Value�� �����Ѵ�.

	void	AddSceneUpdate();
	void	RemoveSceneUpdate();

public:
	void			SetLightMapMaterialFlags(RwUInt32 uiFlags);
	void			SetLightMapObjectFlags(RwUInt32 uiFlags);
	RwUInt32		GetLightMapMaterialFlags();
	RwUInt32		GetLightMapObjectFlags();
	void			FreeSchedulingLTProp();
	void			AllocSchedulingLTProp();
	RwBool			IsRpWorldSectorList(RpWorldSector* pRpWorldSector);
	void			UpdateRpSectorOBBCheck();

	// attach dogi gym. emblem texture. careful for Destroy()
	RwBool			SetAtomicEmblemMap(RwTexture* _pEmblemMap);
	RwBool			GetEmblemMarkEnabled();
	void			DestroyEmblemMap();

	// dojo	
	CNtlPLEntity*	GetDojo()							{ return m_pDojoEntity; }
	void			SetDojo(CNtlPLEntity* pDojoEntity)	{ m_pDojoEntity = pDojoEntity; }

public:
	static RpAtomic *RenderCallBack(RpAtomic *pAtomic);

public:
	//static void					SetFarPlane(RwReal fFarDist);

protected:
	//static RwPlane				g_planeFar;

#ifdef dNTL_WORLD_TOOL_MODE
public:
	static void			SaveSwapFile(RwReal x, RwReal y, RwReal z);
	static void			LoadSwapFile(RwReal x, RwReal y, RwReal z);
#endif
	
protected:
	sSCHEDULING_LM_PROP*		m_pSchedulingLMProp;
    SObjectSchedulingInfo       m_sScheduleInfo;        ///< �����층 �ε� ���� ���� 
	RwUInt32					m_uiObjectSerialID;

	CNtlPLObjectType*			m_pObjectType;

	RwBool						m_bActiveUpdate;
	RwBool						m_bLoadMap;

	CNtlPLResource *			m_pClumpResource;
	ENTITY_ATOMIC_VEC	        m_vecAtomicList;         ///< ���� Clump�� �����ϰ� �ִ� Atomic���� ����Ʈ
	FRAME_MAP				    m_mapFrame;				 ///< Bone Info

	RwV3d						m_vModelAngle;
	RwV3d						m_vModelScale;
	RwV3d						m_vWorldPosition;

	CNtlPLObjectProperty*       m_pProperty;            ///< ������Ʈ ������Ƽ ��ü	

	CNtlPLUVAnim*               m_pUVAnim;              ///< UVAnim ���� ��ü                
	RpHAnimHierarchy*           m_pBaseHierarchy;		///< Base Hierarchy
	CNtlPLResource*             m_pAnimResource;        ///< Anim Resource
	RwBool                      m_bAnimPlay;            ///< Anim Play ����
	RwBool						m_bHaveAnim;			///< Anim ���� ����.

	RwReal						m_fAnimSpeed;			///< Anim Speed

	RwRGBA						m_sColor;				///< Color				
	RwRGBA						m_sAddColor;			///< AddColor

	RwSphere					m_BSphere;				///< Position�� ������� ���� BoundSphere
	RwSphere					m_BSphereCur;			///< Position�� ����� BoundingSphere : GetBoundingSphere�� ȣ���ϰ� �Ǹ� ������Ʈ �ȴ�.

	CNtlPLLinkEffect            m_LinkEffectInstance;   ///< LinkEffect Instance���� �����ϴ� ��ü

	RwBBox                      m_bbox;                 ///< Object�� Bounding Box

	// Fade System ����
	EObjectFadeState            m_eFadeState;           ///< ���� Object�� Fade State
	RwReal                      m_fPrevCameraDistance;  ///< ������ ī�޶���� �Ÿ�
	RwReal                      m_fFadeTime;            ///< Fade Time    
	CNtlPLEntityAlphaWeightBlend* m_pFadeBlend;         ///< Fade Blend ������ ���� ���� ��ü

	// Trigger Object�� Animation ����
	CNtlAnimLayer*				m_pAnimLayer;			///< �ִϸ��̼� ���̾�
	CNtlInstanceAnimTable*		m_pInstanceAnimTable;	///< Animation Resource Instance Table
	RwUInt32					m_uiCurAnimKey;			///< ���� ����ǰ� �ִ� AnimKey

	ListSoundHandle				m_listLoopSound;        ///< LoopSound���� HANDLE List
	ListLoopEffect				m_listLoopEffect;       ///< LoopEffect�� list

	// ���� ������Ʈ �׸��� ����
	vector<CNtlWorldShadow*>    m_vecNtlWorldShadow;

	RwUInt32                    m_uiMilepostTextID;      ///< ����ǥ�� ���ɶ� ����� �ؽ�Ʈ ���̺��� ID

    // ������
    SToonData*				    m_pToonData;			///< Toon Ink, Toon Paint, Toon Resource

	// �ε���
	CNtlOBB						m_OBB;					///< �ε���� ���Ǹ�, RpWorldSector�� �˻��ϱ� ���� ���.
	vector<RpWorldSector*>		m_vecRpWorldSector;		///< �ε���� ���Ǹ�, ���ԵǾ� �ִ� RpWorldSectorlist

	// Dojo
	CNtlPLEntity*				m_pDojoEntity;

	// attach light
	struct SLightObjectAttachData
	{
		RwV3d						vPos;
		RwChar						chBoneName[MAX_ATTR_BONE_NAME];
		SPLLightObjectCreateParam*	pPLLightObjectCreateParam;
	};
	std::vector<SLightObjectAttachData*> m_vecAttachLightParam;

public:
	virtual RwBool	LoadFromFile(FILE* pFile, EActiveWorldType eActiveWorldType);
	virtual RwBool	SaveIntoFile(FILE* pFile, EActiveWorldType eActiveWorldType);
	static	RwInt32	SkipToFile(FILE* pFile, EActiveWorldType eActiveWorldType, RwUInt32 uiObjectType);

	static	BYTE*	SaveIntoFileFromFileMem(FILE* pFile, BYTE* pFileMem, EActiveWorldType eActiveWorldType, RwUInt32 uiObjectType);
	static	BYTE*	SaveIntoFileFromFileMemVisibilityDistance(FILE* pFile, BYTE* pFileMem, EActiveWorldType eActiveWorldType, RwUInt32 uiObjectType, RwReal fVD, RwReal fMinVD, RwReal fMaxVD);
	static	BYTE*	SkipToFileMem(BYTE* pFileMem, EActiveWorldType eActiveWorldType, RwUInt32 uiObjectType);
	static	BYTE*	SkipToFileMemGetEnabledTrigger(BYTE* pFileMem, EActiveWorldType eActiveWorldType, RwUInt32 uiObjectType, RwBool* pResult);
	static	BYTE*	SkipToFileMemGetEnabledPEC(BYTE* pFileMem, EActiveWorldType eActiveWorldType, RwUInt32 uiObjectType, RwBool* pResult);
};

//////////////////////////////////////////////////////////////////////////
// dNTL_WORLD_FILE : DEFINE
//////////////////////////////////////////////////////////////////////////
#endif

#endif