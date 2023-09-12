/*****************************************************************************
* File			: gui_particleemitter.h
* Author		: HaeSung, Cho
* Copyright		: (��)NTL
* Date			: 2008. 9. 19
* Abstract		: 
*****************************************************************************
* Desc          : DBO ��ƼŬ�� ������
*****************************************************************************/

#ifndef _GUI_PARTICLE_EMITTER_H_
#define _GUI_PARTICLE_EMITTER_H_

#include "gui_particle.h"

START_GUI

class CSurfaceManager;

enum e2DParticleEmitterType
{
	eEMITTER_POINT = 0,
	eEMITTER_BOX,

	eEMITTER_NUMS,
	eEMITTER_INVALID = 0xFF
};

/**
* \brief Particle�� ������ �ϴ� Ŭ����
*/
class CParticleEmitter
{
public:
	CParticleEmitter( PARTICLELIST* pParList, CSurfaceManager* pSurfaceManager );
	virtual ~CParticleEmitter();

	virtual void Update(float fElapsed);

	virtual void SetPosition( int nPosX, int nPosY );
	virtual void SetLifeTime( float fLifeMin, float fLifeMax );
	virtual void SetVelocity( float fVelMin, float fVelMax );
	virtual void SetEmissivity( float fEmissivity );
	virtual void SetDirection( RwV2d& v2dDir, float fAngle );
	virtual void SetRotate( float fRotateMin, float fRotateMax );
	virtual void SetScale( float fScaleMin, float fScaleMax );
	
	virtual void SetColorRed( unsigned char uRedMin, unsigned char uRedMax );
	virtual void SetColorGreen( unsigned char uGreenMin, unsigned char uGreenMax );
	virtual void SetColorBlue( unsigned char uBlueMin, unsigned char uBlueMax );
	virtual void SetAlpha( unsigned char uAlphaMin, unsigned char uAlphaMax );
	
	virtual void SetSurface( std::string strSurPage, std::string strSurface );
	virtual void SetSurface( const char* surpage, const char* surface );

	int				m_nID;			// Emitter���� �����Ҽ� �ִ� ID

	int				m_nPosX;		// ��ġ
	int				m_nPosY;

	float			m_fLifeMin;		// ���� �ּ� ~ �ִ�
	float			m_fLifeMax;

	float			m_fVelMin;		// �ӵ� �ּ� ~ �ִ�
	float			m_fVelMax;

	float			m_fEmissivity;

	RwV2d			m_v2dDir;			// ���� ����
	float			m_fAngle;			// ��簢

	float			m_fRotateAngleMin;	// Rotate per sec
	float			m_fRotateAngleMax;

	float			m_fScaleMin;
	float			m_fScaleMax;

	unsigned char	m_uRedMin;
	unsigned char	m_uRedMax;

	unsigned char	m_uGreenMin;
	unsigned char	m_uGreenMax;

	unsigned char	m_uBlueMin;
	unsigned char	m_uBlueMax;

	unsigned char	m_uAlphaMin;
	unsigned char	m_uAlphaMax;

	std::string		m_strSurPage;
	std::string		m_strSurface;

protected:
	virtual void AddParticle( int nEmitNums ) = 0;

protected:
	// Emitter�� �Ӽ�
	PARTICLELIST*		m_pParticleList;
	CSurfaceManager*	m_pSurfaceManager;

	

protected:
	// Emitter�� ���� ����
	BOOL			m_bPlay;
	float			m_fEmissivityRate;
};

class CPointEmitter : public CParticleEmitter
{
public:
	CPointEmitter(PARTICLELIST* pParList, CSurfaceManager* pSurfaceManager);
	virtual ~CPointEmitter();

protected:
	virtual void AddParticle( int nEmitNums );
};

class CBoxEmitter : public CParticleEmitter
{
public:
	CBoxEmitter(PARTICLELIST* pParList, CSurfaceManager* pSurfaceManager);
	virtual ~CBoxEmitter();

	virtual void SetWidthHeight( int nWidth, int nHeight );

	int			m_nWidth;
	int			m_nHeight;

protected:
	virtual void AddParticle( int nEmitNums );

};

END_GUI

#endif//_GUI_PARTICLE_EMITTER_H_