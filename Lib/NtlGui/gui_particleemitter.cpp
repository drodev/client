#include "gui_precomp.h"
#include "GuiUtil.h"
#include "gui_particleemitter.h"
#include "gui_surfacemanager.h"

START_GUI

///////////////////////////////////////////////////////////////////////////////////////////////////
// Base Class : CParticleEmitter
///////////////////////////////////////////////////////////////////////////////////////////////////

/**
* \brief Construction
*/
CParticleEmitter::CParticleEmitter( PARTICLELIST* pParList, CSurfaceManager* pSurfaceManager )
{
	m_nID = 0;

	m_nPosX = 0;
	m_nPosY = 0;

	m_fLifeMin = 0.f;
	m_fLifeMax = 0.f;

	m_fVelMin = 0.f;
	m_fVelMax = 0.f;

	m_fEmissivity = 0.f;

	m_strSurPage = "";
	m_strSurface = "";

	m_fRotateAngleMin = 0.f;
	m_fRotateAngleMax = 0.f;

	m_fScaleMin	= 0.f;
	m_fScaleMax = 0.f;

	m_uRedMin = 0;
	m_uRedMax = 0;

	m_uGreenMin = 0;
	m_uGreenMax = 0;

	m_uBlueMin = 0;
	m_uBlueMax = 0;

	m_uAlphaMin = 0;
	m_uAlphaMax = 0;

	m_pParticleList = pParList;
	m_pSurfaceManager = pSurfaceManager;

	m_fEmissivityRate = 0.f;
}
/**
* \brief Destruction
*/
CParticleEmitter::~CParticleEmitter()
{
}

/**
* \brief Emitter�� ������Ʈ �Ѵ�. ( ��ƼŬ�� �����ϰų� Emitter�� �ൿ�� �����Ѵ�. )
* \param fElapsed		(float) ���� �����ӿ����� ����ð�
* \return Emitter�� ��ƼŬ�� �ϳ� �߰��Ͽ��� �� TRUE, �ƹ� �ൿ�� ���� �ʾ��� �� FALSE
*/
void CParticleEmitter::Update( float fElapsed )
{
	// ����� ���
	// m_fEmissivity per sec
	m_fEmissivityRate += m_fEmissivity * fElapsed;

	// ������� 1 �̻��̶��. �ּ� ���� 1�� �̻� ��ƼŬ ����
	if( m_fEmissivityRate >= 1.0f )
	{
		// �Ҽ��� ���� ������ ������ ��ƼŬ�� ������ ���Ѵ�.
		int nEmitNums = (int)m_fEmissivityRate;

		// �� ������ �ٽ� ������� ���ҽ����༭ 1 ���Ϸ� �����.
		m_fEmissivityRate -= (float)nEmitNums;
		
		// ��� ������ŭ ��ƼŬ�� �߰��Ѵ�.
		AddParticle( nEmitNums );
	}
}

void CParticleEmitter::SetPosition( int nPosX, int nPosY )
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
}

void CParticleEmitter::SetLifeTime( float fLifeMin, float fLifeMax )
{
	m_fLifeMin = fLifeMin;
	m_fLifeMax = fLifeMax;
}

void CParticleEmitter::SetVelocity( float fVelMin, float fVelMax )
{
	m_fVelMin = fVelMin;
	m_fVelMax = fVelMax;
}

void CParticleEmitter::SetEmissivity( float fEmissivity )
{
	m_fEmissivity = fEmissivity;
}

void CParticleEmitter::SetDirection( RwV2d& v2dDir, float fAngle )
{
	m_v2dDir = v2dDir;
	m_fAngle = fAngle;
}

void CParticleEmitter::SetRotate( float fRotateMin, float fRotateMax )
{
	m_fRotateAngleMin = fRotateMin;
	m_fRotateAngleMax = fRotateMax;
}

void CParticleEmitter::SetScale( float fScaleMin, float fScaleMax )
{
	m_fScaleMin = fScaleMin;
	m_fScaleMax = fScaleMax;
}

void CParticleEmitter::SetColorRed( unsigned char uRedMin, unsigned char uRedMax )
{
	m_uRedMin = uRedMin;
	m_uRedMax = uRedMax;
}

void CParticleEmitter::SetColorGreen( unsigned char uGreenMin, unsigned char uGreenMax )
{
	m_uGreenMin = uGreenMin;
	m_uGreenMax = uGreenMax;
}

void CParticleEmitter::SetColorBlue( unsigned char uBlueMin, unsigned char uBlueMax )
{
	m_uBlueMin = uBlueMin;
	m_uBlueMax = uBlueMax;
}

void CParticleEmitter::SetAlpha( unsigned char uAlphaMin, unsigned char uAlphaMax )
{
	m_uAlphaMin = uAlphaMin;
	m_uAlphaMax = uAlphaMax;
}

void CParticleEmitter::SetSurface( std::string strSurPage, std::string strSurface )
{
	m_strSurPage = strSurPage;
	m_strSurface = strSurface;
}

void CParticleEmitter::SetSurface( const char* surpage, const char* surface )
{
	m_strSurPage = surpage;
	m_strSurface = surface;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Class : CPointEmitter
///////////////////////////////////////////////////////////////////////////////////////////////////

CPointEmitter::CPointEmitter(PARTICLELIST* pParList, CSurfaceManager* pSurfaceManager)
: CParticleEmitter( pParList, pSurfaceManager )
{
}

CPointEmitter::~CPointEmitter()
{

}

void CPointEmitter::AddParticle( int nEmitNums )
{
	for( int i = 0; i < nEmitNums; ++i )
	{
		RwV2d v2dPos;
		v2dPos.x = (float)m_nPosX;
		v2dPos.y = (float)m_nPosY;

		float fLife		= RandomNumber( m_fLifeMin, m_fLifeMax );
		float fVel		= RandomNumber( m_fVelMin, m_fVelMax );

		// ������ ���� ���͸� �������� ��簢���� �������� �ϳ��� ���͸� �ִ´�.
		RwV2d v2dDir;
		float fRadiationAngle = RandomNumber( -(m_fAngle/2.0f), (m_fAngle/2.0f) );

		float fDeg2Rad = GUI_DEG2RAD( fRadiationAngle );

		v2dDir.x = ( RwCos(fDeg2Rad)*m_v2dDir.x ) + ( RwSin(fDeg2Rad)*m_v2dDir.y );
		v2dDir.y = ( -(RwSin(fDeg2Rad)*m_v2dDir.x) ) + ( RwCos(fDeg2Rad)*m_v2dDir.y );

		// ȸ���� Ȯ�� �Ӽ�
		float fRotateAngle = RandomNumber( m_fRotateAngleMin, m_fRotateAngleMax );
		float fScale = RandomNumber( m_fScaleMin, m_fScaleMax );

		// ���� �ɼ�
		unsigned char uRed = RandomNumber( m_uRedMin, m_uRedMax );
		unsigned char uGreen = RandomNumber( m_uGreenMin, m_uGreenMax );
		unsigned char uBlue = RandomNumber( m_uBlueMin, m_uBlueMax );
		unsigned char uAlpha = RandomNumber( m_uAlphaMin, m_uAlphaMax );

		m_pParticleList->push_back( CParticle( v2dPos, v2dDir, fLife, fVel,
			fRotateAngle, fScale, uRed, uGreen, uBlue, uAlpha,
			m_pSurfaceManager->GetSurface( m_strSurPage.c_str(), m_strSurface.c_str() ) ) );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Class : CBoxEmitter
///////////////////////////////////////////////////////////////////////////////////////////////////

CBoxEmitter::CBoxEmitter( PARTICLELIST* pParList, CSurfaceManager* pSurfaceManager )
: CParticleEmitter( pParList, pSurfaceManager )
{
	m_nWidth = 0;
	m_nHeight = 0;
}

CBoxEmitter::~CBoxEmitter()
{

}

void CBoxEmitter::SetWidthHeight( int nWidth, int nHeight )
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
}

void CBoxEmitter::AddParticle( int nEmitNums )
{
	for( int i = 0; i < nEmitNums; ++i )
	{
		RwV2d v2dPos;
		v2dPos.x = (float)RandomNumber(m_nPosX, m_nPosX+m_nWidth);
		v2dPos.y = (float)RandomNumber(m_nPosY, m_nPosY+m_nHeight);

		float fLife		= RandomNumber( m_fLifeMin, m_fLifeMax );
		float fVel		= RandomNumber( m_fVelMin, m_fVelMax );

		// ������ ���� ���͸� �������� ��簢���� �������� �ϳ��� ���͸� �ִ´�.
		RwV2d v2dDir;
		float fRadiationAngle = RandomNumber( -(m_fAngle/2.0f), (m_fAngle/2.0f) );

		float fDeg2Rad = GUI_DEG2RAD( fRadiationAngle );

		v2dDir.x = ( RwCos(fDeg2Rad)*m_v2dDir.x ) + ( RwSin(fDeg2Rad)*m_v2dDir.y );
		v2dDir.y = ( -(RwSin(fDeg2Rad)*m_v2dDir.x) ) + ( RwCos(fDeg2Rad)*m_v2dDir.y );

		// ȸ���� Ȯ�� �Ӽ�
		float fRotateAngle = RandomNumber( m_fRotateAngleMin, m_fRotateAngleMax );
		float fScale = RandomNumber( m_fScaleMin, m_fScaleMax );

		// ���� �ɼ�
		unsigned char uRed = RandomNumber( m_uRedMin, m_uRedMax );
		unsigned char uGreen = RandomNumber( m_uGreenMin, m_uGreenMax );
		unsigned char uBlue = RandomNumber( m_uBlueMin, m_uBlueMax );
		unsigned char uAlpha = RandomNumber( m_uAlphaMin, m_uAlphaMax );

		m_pParticleList->push_back( CParticle( v2dPos, v2dDir, fLife, fVel,
			fRotateAngle, fScale, uRed, uGreen, uBlue, uAlpha,
		m_pSurfaceManager->GetSurface( m_strSurPage.c_str(), m_strSurface.c_str() ) ) );
	}
}


END_GUI