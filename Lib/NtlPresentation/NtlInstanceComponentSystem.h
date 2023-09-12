//***********************************************************************************
//	File		:	NtlInstanceComponentSystem.h
//	Desc		:	
//	Begin		:	2005. 7.28
//	Copyright	:	�� 2005 by agebreak CO., Ltd
//	Author		:	agebreak
//	Update		:	
//***********************************************************************************

#pragma once

#include "rwcore.h"
#include "rpworld.h"

#include "rpprtstd.h"
#include "rpprtadv.h"

#include "NtlResourceEffect.h"

#include "NtlEffectSplinePath.h"

#include "NtlResourceComponentSystem.h"
#include "NtlPLResourceManager.h"

class CNtlPLAttach;

class CNtlInstanceComponentSystem
{
public:
	RwReal							m_fLifeTime;						///< Effect�� ��� �ִ� ������ �ð��� ������ �ִ� �ӽ� ����( += fElapsedTime)

	RwBool							m_bReady;
	RwBool							m_bStart;
	RwBool							m_bUpdate;    
    RwBool                          m_bFinish;                          ///< Finish �۾��� ó���Ҷ� ����ϴ� Flag
    RwBool                          m_bVisible;
    RwBool                          m_bIsApplyFlagGround;               ///< ������ ��ġ�ϴ� �÷��׸� ó���ߴ��� ����    
	RwMatrix						m_matWorld;
	RwMatrix						m_matScale;
	RwMatrix						m_matRotate;
	RwMatrix						m_matRender;
	RwMatrix						m_matAttach;
	CNtlResourceComponentSystem*	m_pResourceComponentSystem;
    CNtlPLAttach*                   m_pAttachParent;
    RwReal                          m_fScale;

	RwBool							m_bAttach;

	// Path 
	CNtlEffectSplinePath*			m_pSplinePath;
	RwMatrix						m_matPathWorld;
	RwMatrix						m_matPathRender;
	RwMatrix						m_matTempRender;

	// Texture
	RwTexture*						m_pStandardTexture;

	RwReal							m_fMultiTextureDeltaTime;
	RwInt32							m_nMultiTextureCount;
	RwTexture**						m_ppMultiTexture;

	RwTexture*						m_pCurrentTexture;
	RwInt32							m_nCurrentTexture;

	// random
	RwInt32							m_nRandomSeed;

	// fade out
	RwReal							m_fFadeOutTime;
	CNtlInstanceComponentSystem*	m_pFadeOutSystem;

    // Finish ����
    RwReal                          m_fFinishTime;                      ///< Finish �ð� üũ�� ���� ����
    RwV3d                           m_v3dFinishSize;                    ///< Finish�� ũ�� ���濡 ���� Size

    RwSphere                        m_BoundingSphere;                   ///< The bounding sphere of the effect system
    RwUInt32                        m_uiMemoryUseSize;                  ///< Memory usage

public:
	CNtlInstanceComponentSystem(void);
	virtual ~CNtlInstanceComponentSystem(void);

	virtual void	Init();
	RwTexture*	CreateTexture(std::string& strTexture);
	RwBool		CreateMultiTextures(RpPrtAdvEmtPrtMultiTextures* pEmitterMultiTextures);

	RwBool	UpdateMultiTexture(RwReal fElapsedTime);

	void	RebuildColor(RwRGBA& destCol, RwInt32 seed, RwReal fDeltaTime, RpPrtStdEmitterPrtColor* pEmitterPrtCol);
	void	RebuildSize(RwV3d& destSize, RwInt32 seed, RwReal fDeltaTime, SNtlPrtStdEmitterPrtSize* pEmitterPtrSize);
	void	RebuildRotate(RwV3d& destRotate, RwInt32 seed, RwReal fDeltaTime, SNtlPrtStdEmitterPrtRotate* pEmitterPtrRotate);
	RwTexture* RebuildMultiTexture(RwInt32 nCurrentIndex, RwInt32 seed, RwReal fElapsedTime, RpPrtAdvEmtPrtMultiTextures* pEmitterMultiTexture);

	void	RebuildMultiColor(RwRGBA& destCol, RwInt32 seed, RwReal fDeltaTime, RpPrtStdEmitterPrtColor* pEmitterPrtCol, RpPrtAdvPrtMultiColorEmitter* pEmitterPrtMultiCol);
	void	RebuildMultiSize(RwV3d& destSize, RwInt32 seed, RwReal fDeltaTime, SNtlPrtStdEmitterPrtSize* pEmitterPtrSize, SNtlAdvMultiSizeEmitter* pEmitterPrtMultiSize);
	void	RebuildMultiRotate(RwV3d& destRotate, RwInt32 seed, RwReal fDeltaTime, SNtlPrtStdEmitterPrtRotate* pEmitterPtrRotate, SNtlAdvMultiRotateEmitter* pEmitterPrtMultiRotate);
	RwInt32 GetSystemType()					{ return m_pResourceComponentSystem->GetSystemType(); }


    /// ���� �Լ���
	virtual void	Reset() = 0;

	virtual void	Delete();
	virtual RwBool	Create(CNtlResourceEffect* pResourceEffect, CNtlResourceComponentSystem* pResourceComponentSystem, const RwMatrix& matWorld);

    virtual RwBool  Finish();                                                       ///< ����Ʈ�� ���� �۾��� ó���Ѵ�.
	virtual void	Stop() { m_bUpdate = FALSE; }									///< Update�� �ߴ��� �Ѵ�.

	virtual RwBool	Update(RwReal fElapsedTime);
	virtual RwBool	Render() = 0;

	virtual void	SetWorldMatrix(const RwMatrix& matWorld);
	virtual void	SetAttachMatrix(const RwMatrix& matAttach);
    virtual void    SetAlpha(RwUInt8 byValue) {}                                 ///< ����Ʈ�� Alpha���� �����Ѵ�.
	virtual void	SetScale(RwReal fScale) {m_fScale = fScale;}				 ///< ����Ʈ�� Scale�� �����Ѵ�. 
    virtual RwReal  GetScale() {return m_fScale;}
    virtual void    SetVisible(RwBool bVisible) {m_bVisible = bVisible;}
    virtual RwSphere* GetBoundingSphere();                                       ///< ����Ʈ�� �ٿ�� ���Ǿ ��ȯ�Ѵ�.
    virtual RwUInt32 GetMemoryUseSize() {return m_uiMemoryUseSize;}              ///< �޸� ��뷮�� ��ȯ�Ѵ�.

protected:
    virtual RwBool  UpdateFinish(RwReal fElapsedTime);                          ///< Finish ó���� �Ѵ�.
    virtual RwUInt8 UpdateFinishAlpha(RwUInt8 uiOriginAlpha, RwReal fElapsedTime, RwReal fFinishTime);  ///< Finish���� ���İ��� ����Ѵ�
    virtual RwV3d   UpdateFinishSize(RwV3d v3dOriginSize, RwReal fElapsedTime, RwReal fFinishTime);     ///< Finish���� ������� ����Ѵ�.
};

//------------------------------------------------------------------
//	FuncName	: SetWorldMatrix
//	Desc		: 
//	Parameter	: 
//	Return		: 
//------------------------------------------------------------------
inline void CNtlInstanceComponentSystem::SetAttachMatrix(const RwMatrix& matAttach)
{
	m_bAttach = TRUE;
	m_matAttach = matAttach;
	SetWorldMatrix(m_matWorld);
}

//------------------------------------------------------------------
//	FuncName	: SetWorldMatrix
//	Desc		: 
//	Parameter	: 
//	Return		: 
//------------------------------------------------------------------
inline void CNtlInstanceComponentSystem::SetWorldMatrix(const RwMatrix& matWorld)
{
	m_matWorld = matWorld;

	if (m_bAttach)
	{
		RwMatrix matTemp;
		RwMatrixMultiply(&matTemp, &m_matWorld, &m_matAttach);
		RwMatrixMultiply(&m_matRender, &m_pResourceComponentSystem->m_matWorld, &matTemp);        
	}
	else
	{
		RwMatrixMultiply(&m_matRender, &m_pResourceComponentSystem->m_matWorld, &m_matWorld);
	}

    // Ground Attach
    if(m_pResourceComponentSystem->m_sGroundFlag.bGround && m_bIsApplyFlagGround)
    {
        m_bIsApplyFlagGround = FALSE;
    }

    // Scale ����
    RwV3d vPosition = *RwMatrixGetPos(&m_matRender);
    RwMatrixGetPos(&m_matRender)->x = 0.0f;
    RwMatrixGetPos(&m_matRender)->y = 0.0f;
    RwMatrixGetPos(&m_matRender)->z = 0.0f;

    RwMatrix matOldRender = m_matRender;
    RwMatrixMultiply(&m_matRender, &m_matScale, &matOldRender);
    RwMatrixTranslate(&m_matRender, &vPosition, rwCOMBINEPOSTCONCAT);
    RwMatrixUpdate(&m_matRender);
}
