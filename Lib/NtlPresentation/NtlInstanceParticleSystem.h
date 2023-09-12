//***********************************************************************************
//	File		:	NtlInstanceParticleSystem.h
//	Desc		:	
//	Begin		:	2006. 7.28
//	Copyright	:	�� 2006 by NTL CO., Ltd
//	Author		:	agebreak
//	Update		:	
//***********************************************************************************

#pragma once

#include ".\ntlinstancecomponentsystem.h"

#include ".\ntlresourceparticlesystem.h"

#include "NtlInstanceTrailSystem.h"
/**
 * \ingroup NtlPresentation
 * \brief Particle Instance�� �����ϴ� Ŭ����
 * \date 2006-08-28
 * \author agebreak
 */
class CNtlInstanceParticleSystem : public CNtlInstanceComponentSystem
{
public:
	CNtlResourceParticleSystem* m_pResourceParticleSystem;

	RpPrtStdEmitterClass*		m_pEmitterClass;
	RpPrtStdParticleClass*		m_pParticleClass;

	RpPrtStdEmitter*			m_pEmitter;
	RpPrtStdEmitterStandard*	m_pEmitterStandard;    

	RpAtomic*					m_pAtomic;
	RpPrtStdEmitterPTank*		m_pTankProperties;

	RwTexture*					m_pStandardTexture;

	RwInt32						m_nVelocityOffset;
	// hurricane
	RwReal						m_fHurricaneLifeTime;
	RwReal						m_fHurricaneDeltaTime;
    
    // Trail System (Trail Action)
    CNtlInstanceTrailSystem*    m_pTrailSystem;

protected:
    // Matrix Action�� ����Ǿ����� Rotation ����
    RpPrtStdEmitterPrtMatrix*   m_pEmitterPrtMatrix;
    RwV3d                       m_vOrgAt;           ///< ���� ������ At��
    RwV3d                       m_vOrgUp;           ///< ���� ������ Up��    

    // Follow Particle ���� (��ƼŬ ������ü�� ����ٴϴ� ��ƼŬ)
    RwV3d                       m_vPosPrev;         ///< ���� ��ü�� ���� ��ġ
    RwV3d                       m_vPosDelta;        ///< ���� ��ġ�� ���� ����� ��ġ    

public:
	CNtlInstanceParticleSystem(void);
	virtual ~CNtlInstanceParticleSystem(void);

	void* operator new(size_t size);
	void operator delete(void *pObj);

	virtual void	Init();
	virtual void	Reset();

	virtual void	Delete();
	virtual RwBool	Create(CNtlResourceEffect* pResourceEffect, CNtlResourceComponentSystem* pResourceComponentSystem, const RwMatrix& matWorld);
	virtual void	Stop();    

			RpPrtStdEmitter*	SubEmitterCreate(CNtlResourceParticleSystem* pResourceSystem);

	virtual RwBool	Update(RwReal fElapsedTime);
	virtual RwBool	Render();

	virtual void	SetWorldMatrix(const RwMatrix& matWorld);
	virtual void	SetScale(RwReal fScale);					///< ��ƼŬ�� Scale�� �����Ѵ�.
    virtual void    SetAlpha(RwUInt8 byValue);                  ///< ��ƼŬ�� Alpha�� �����Ѵ�.

			void	BuildHurricanePoint(RwV3d& vPosition, RwReal fLifeTime);

protected:
            void    UpdateFollow();                             ///< Follow ��ƼŬ�� ��ġ�� ������Ʈ�Ѵ�.    
            void    UpdateBillboard();                          ///< �����尡 �����Ȱ�� �����带 �����Ѵ�.
            void    UpdateRotate();                             ///< Emitter�� Rotate���� �����Ѵ�.
};
