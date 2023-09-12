//***********************************************************************************
//	File		:	NtlInstanceEffect.h
//	Desc		:	
//	Begin		:	2005. 7.28
//                  2006. 8.17
//	Copyright	:	�� 2005 by agebreak CO., Ltd
//	Author		:	agebreak
//                  HoDong
//	Update		:	
//***********************************************************************************
#ifndef __NTL_INSTANCE_EFFECT__
#define __NTL_INSTANCE_EFFECT__

#include "rwcore.h"
#include "NtlPLAttach.h"
#include "NtlEffectDefine.h"
#include "NtlResourceEffect.h"
#include "NtlInstanceComponentSystem.h"
#include "NtlPLResourceManager.h"
#include "NtlPLSound.h"

/**
 * \ingroup Effect
 * Effect Entity Class(NtlInstanceComponentSystem���� Container Class �̴�.)
 * 
 */
class CNtlInstanceEffect : public CNtlPLAttach
{
public:
	typedef std::vector<CNtlInstanceComponentSystem*>	svdef_InstanceComponentSystem;
	svdef_InstanceComponentSystem						m_svSystem;

	CNtlResourceEffect* m_pResourceEffect;

	RwMatrix			m_matWorld;						///< Effect World Matrix (m_vModelScale * m_vModelAngle * m_vWorldPosition)
														///< SetMatrix()�� Matrix ���� ���� �Է½� m_vWorldPosition ���� ȥ���ؼ� ������ �ִ�.
														///< Rotation�� Scale�� Matrix�� �Էµ� ���� �浹�� ���� ���� �ִ�.

	RwV3d				m_vModelScale;					///< Model Scale
	RwV3d				m_vModelAngle;					///< Model Angle (Degree - 360 - 360)
	RwV3d				m_vWorldPosition;				///< World Position    

	RwReal				m_fLifeTime;
	RwBool				m_bReady;
	RwBool				m_bShow;
	RwBool				m_bAutoDelete;
    RwBool              m_bApplyScale;

    // Sound ���� �ν��Ͻ�
    CNtlPLSound         m_PLSound;                      ///< Sound ��ü   

protected:
    RwReal						m_fAnimSpeed;			///< Anim Speed
    CNtlPLResource *			m_pVisibleBVClump;		///< Bounding Volume Clump //Tool���� Picking�� �ϱ� ���� �뵵�θ�	
    RwSphere                    m_BoundingSphere;       ///< Bounding Sphere
    RwBool                      m_bIsCulling;           ///< �ٿ�� ���Ǿ ���ؼ� �ø��Ǿ����� ���� �÷���
    RwReal                      m_fNotUpdateTime;       ///< �ø��ǰų� Not Visible�Ǿ ������Ʈ �ȵ� �ð�    
    
    static  RwBool              m_bLowSpec;             ///< ����Ʈ �ο� ���� ���� ���� �÷���
    static  RwReal              m_fLowSpecRatio;        ///< ����Ʈ �ο� ����� ����
    static  RwBool              m_bRenderMeshSystem;    ///< �޽� �ý��� ������ On/Off �÷���
    static  RwBool              m_bRenderDecalSystem;   ///< ��Į �ý��� ������ On/Off �÷���

public:
	CNtlInstanceEffect(void);
	~CNtlInstanceEffect(void);

	void* operator new(size_t size);
	void operator delete(void *pObj);

	virtual RwBool	Create(const SPLEntityCreateParam *pParam);
	virtual void	Destroy();
    virtual void    Finish();                                   ///< ����Ʈ�� �ٷ� �������� �ʰ�, �����۾��� ȣ���Ҷ� ����ϴ� �޼ҵ� 	    
	virtual RwBool	Update(RwReal fElapsedTime);
	virtual RwBool	Render();
	virtual RwBool  RenderToTexture(void);
    virtual RwBool	SetProperty(const CNtlPLProperty *pData);
    virtual void    SetAttachParent(CNtlPLAttach *pPLAttachEntity);

    void    AddComponentSystem(CNtlInstanceComponentSystem* pComponentSystem);

	virtual RwBool IsAutoDelete()	{ return m_bAutoDelete; }						///< �ڵ����� ������ �Ǵ� Effect ���� �ƴ���
	
	void	SetMatrix(RwMatrix& matWorld);											///< Effect�� World Matrix�� �����Ѵ�.
	RwMatrix &GetMatrix(void);														///< Effect�� World Matrix�� ��´�.
	
	void	SetPosition(const RwV3d *pPos);											///< Effect�� World�� ��ġ�� �̵� ��Ų��.
	RwV3d	GetPosition(void);														///< Effect�� World�� ��ġ�� ��´�.
	
	void	SetRotate(RwReal fXAngle, RwReal fYAngle, RwReal fZAngle);				///< Effect�� Model ���� ȸ����(degree)
	const	RwV3d* GetRotate(void) const;											///< Effect�� Model ���� ȸ���� ���

	void	SetScale( RwReal fScale );												///< Effect�� Model ���� Scale��
	RwReal	GetScale(void);															///< Effect�� Model ���� Scale�� ������
    void    SetApplyScale(RwBool bApply);                                           ///< ������ ���� ������ �����Ѵ�.

    inline RwSphere* GetBoundingSphere();                                           ///< ����Ʈ�� �ٿ�� ���Ǿ ��ȯ�Ѵ�. (�ٿ�� ���Ǿ ������ NULL�� ��ȯ)
    void			 RenderBoundingSphere();                                        ///< Renders the shape of the bounding sphere. (Venus only)

    virtual void	SetAlpha(RwUInt8 byValue);                                      ///< Effect�� Alpha���� �����Ѵ�.
    virtual void	SetVisible(RwBool bVisible);                                    ///< Effect�� Visible ������ �����Ѵ�
    virtual RwBool	IsVisible(RwUInt32 uiFlags = 0xFFFFFFFF);                       ///< Effect�� Visible ������ ��ȯ�Ѵ�.

	RwBool			SetPlayAnimSpeed(RwReal fAnimSpeed);									///< Animaiton Speed (1.f: Default )
	void			SetVisibleBoundingVolume(RwBool bVisible);								///< World Editor�� Picking Bounding Volume
    void			SetPostEffect_CenterFixEnable(RwBool bEnable);                          ///< ���Ե� Post Effect�� Center Fix����� �����Ѵ�.
    void			SetCulling(RwBool bCulling) {m_bIsCulling = bCulling;}                  ///< ������ �ø� ������ �����Ѵ�.
    RwBool			IsCulling() {return m_bIsCulling;}                                      ///< �ø� ���� �÷��׸� ��ȯ�Ѵ�.
    RwUInt32        GetMemoryUseSize();                                                     ///< ����Ʈ�� �޸� ��뷮�� ��ȯ�Ѵ�.
    
#ifndef dNTL_WORLD_CULLING_NEW
	virtual RwBool  CullingTest(RwCamera* pCamera);                                         ///< �ø� ������ �˻��Ѵ�.
#endif

    //-- Flag settings for Low Spec
    static void     SetLowSpecEnable(RwBool bEnable) {m_bLowSpec = bEnable;}        ///< Set whether low specification is applied or not.
    static RwBool   GetLowSpecEnable() {return m_bLowSpec;}
    static void     SetLowSpecRatio(RwReal fRatio) {m_fLowSpecRatio = fRatio;}      ///< Apply the low spec ratio.   
    static RwReal   GetLowSpecRatio() {return m_fLowSpecRatio;}
    static void     SetRenderMeshSystem(RwBool bEnable) {m_bRenderMeshSystem = bEnable;}    ///< Mesh System Rendering On / Off
    static RwBool   GetRenderMeshSystem() {return m_bRenderMeshSystem;}
    static void     SetRenderDecalSystem(RwBool bEnable) {m_bRenderDecalSystem = bEnable;}  ///< Decal System Rendering On / Off
    static RwBool   GetRenderDecalSystem() {return m_bRenderDecalSystem;}

protected:
    void	SetTransform();
    void	CreateSystem(CNtlResourceEffect* pResourceEffect, const RwMatrix& matRender);
    void    CalcBoundingSphere();                                                   ///< Calculate the bounding sphere.

#ifdef dNTL_WORLD_TOOL_MODE
public:
	static void			SaveSwapFile(RwReal x, RwReal y, RwReal z);
	static void			LoadSwapFile(RwReal x, RwReal y, RwReal z);
#endif

public:
	virtual RwBool	LoadFromFile(FILE* pFile);
	virtual RwBool	SaveIntoFile(FILE* pFile);
	static	RwInt32 SkipToFile(FILE* pFile);

	static	BYTE*	SaveIntoFileFromFileMem(FILE* pFile, BYTE* pFileMem);
	static	BYTE*	SkipToFileMem(BYTE* pFileMem);

};

RwSphere* CNtlInstanceEffect::GetBoundingSphere() 
{
    if(m_BoundingSphere.radius != 0.0f)
        return &m_BoundingSphere;

    return NULL;
}

#endif
