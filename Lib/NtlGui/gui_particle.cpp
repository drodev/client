#include "gui_precomp.h"
#include "gui_particle.h"

START_GUI

/**
* \brief Construct
*/
CParticle::CParticle( RwV2d& v2dPos, RwV2d& v2dDir, float fLifeTime, float fVel, float fRotate, float fScale, unsigned char uRed, unsigned char uGreen, unsigned char uBlue, unsigned char uAlpha, CSurface surface )
{
	// Position
	m_v2dPos = v2dPos;
	
	// Velocity
	RwV2dScale( &m_v2dDir, &v2dDir, fVel );

	// Lite Time ( sec )
	m_fLifeTime = fLifeTime;

	// Rotate Angle ( Radian (?) )
	m_fRotate = fRotate;

	m_fScale = fScale;

	// ��ƼŬ�� �ؽ��ķ� ����� �����̽����� ���̿� ���̸� �̸� ����صд�.
	m_nWidth = (int)(surface.m_SnapShot.rtRect.GetWidth() * fScale);
	m_nHeight = (int)(surface.m_SnapShot.rtRect.GetHeight() * fScale);

	// �����̽� ���� ( �ؽ��Ĵ� �����͸� ����ȴ�. )
	m_surParticle = surface;

	m_fAge = 0.f;
	
	// Texture Position
	m_surParticle.m_SnapShot.rtRect.left = (int)m_v2dPos.x - ( m_nWidth / 2 );
	m_surParticle.m_SnapShot.rtRect.top = (int)m_v2dPos.y - ( m_nHeight / 2 );
	m_surParticle.m_SnapShot.rtRect.right = m_surParticle.m_SnapShot.rtRect.left + m_nWidth;
	m_surParticle.m_SnapShot.rtRect.bottom = m_surParticle.m_SnapShot.rtRect.top + m_nHeight;
	m_surParticle.m_SnapShot.uRed = uRed;
	m_surParticle.m_SnapShot.uGreen = uGreen;
	m_surParticle.m_SnapShot.uBlue = uBlue;
	m_surParticle.m_SnapShot.uAlpha = uAlpha;

	// ������ ���� �����Ѵ�.
	m_OriginSnapShot = m_surParticle.m_SnapShot;

	m_bDie = FALSE;
}

CParticle::~CParticle()
{

}

void CParticle::Update( float fElapsed )
{
	m_fAge += fElapsed;
	if( m_fAge > m_fLifeTime )
		m_bDie = TRUE;

	//// 1. �ӵ� ���
	RwV2d v2dVelDelta;
	RwV2dScale( &v2dVelDelta, &m_v2dDir, fElapsed );

	// 2. ��ġ + �ӵ�
	RwV2dAdd( &m_v2dPos, &m_v2dPos, &v2dVelDelta );

	// 3. Texture Position update
	m_surParticle.m_SnapShot.rtRect.left = (int)m_v2dPos.x - ( m_nWidth / 2 );
	m_surParticle.m_SnapShot.rtRect.top = (int)m_v2dPos.y - ( m_nHeight / 2 );
	m_surParticle.m_SnapShot.rtRect.right = m_surParticle.m_SnapShot.rtRect.left + m_nWidth;
	m_surParticle.m_SnapShot.rtRect.bottom = m_surParticle.m_SnapShot.rtRect.top + m_nHeight;
	m_surParticle.m_fAngle += ( (m_fRotate * 360.f) * fElapsed );
	m_surParticle.m_fAngle = fmod( m_surParticle.m_fAngle, 360.f );
}

END_GUI