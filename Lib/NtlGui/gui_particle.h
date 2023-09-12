/*****************************************************************************
* File			: gui_particle.h
* Author		: HaeSung, Cho
* Copyright		: (��)NTL
* Date			: 2008. 9. 18
* Abstract		: 
*****************************************************************************
* Desc          : 
* DBO�� ��ƼŬ
* gui_particle.h .cpp
* gui_particlebox.h .cpp
* gui_particlebox_generic.h .cpp
* gui_particleparser.h .cpp
* gui_particlepage.h .cpp
*****************************************************************************/

#ifndef _GUI_PARTICLE_H_
#define	_GUI_PARTICLE_H_

START_GUI

/**
* \ingroup gui
* Objects representing particles
*/
class CParticle
{
public:
	CParticle( RwV2d& v2dPos, RwV2d& v2dDir, float fLifeTime, float fVel,
		float fRotate, float fScale,
		unsigned char uRed, unsigned char uGreen, unsigned char uBlue,
		unsigned char uAlpha,
		CSurface surface );

	virtual ~CParticle();

	void	Update( float fElapsed );
	BOOL	IsDie()						{ return m_bDie; }

	float		m_fLifeTime;		///< ����(��)
	float		m_fAge;

	RwV2d		m_v2dPos;			///< ��ġ
	RwV2d		m_v2dDir;			///< �ӵ�
	
	CSurface		m_surParticle;	///< �����̽�
	PlaneSnapShot	m_OriginSnapShot;

	int			m_nWidth;			///< �����̽� ũ��
	int			m_nHeight;

	float		m_fRotate;			///< Rotate �� ��ġ

	float		m_fScale;			///< Scale��

protected:	
	BOOL		m_bDie;				///< �׾���?
};

///< Type
typedef std::list<CParticle>					PARTICLELIST;
typedef	std::list<CParticle>::iterator			PARTICLELISTIT;

END_GUI

#endif//_GUI_PARTICLE_H_