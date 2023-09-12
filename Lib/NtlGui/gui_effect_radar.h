
////////////////////////////////////////////////////////////////////////////////
// Name: class gui::CRadarEffect
// Desc: Effect that is displayed by turning clockwise or counterclockwise according to time
//			 
// 2006.06.15 Peessi@hitel.net   
//
// To Be Desired: 
//	1. I did not think about the whole structure because of lack of time.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GUI_RADAR_EFFECT__
#define __GUI_RADAR_EFFECT__

START_GUI

class CRadarEffect
{
public:
	typedef VOID (CRadarEffect::*CalcProc)( FLOAT fGradient, BOOL bFirst );
	enum { NUM_TRIANGLE = 8 };

//! Constructor & Destructor
	CRadarEffect(VOID);
	~CRadarEffect(VOID);

//! Attribute
	BOOL		IsWork(VOID) { return m_bShow; }

//! Opration
	VOID		SetPosition( INT nPosX, INT nPosY );
	VOID		SetSurface( const CSurface& surface );

	// bDirClock : TRUE �ð�������� ȸ��. bFill : TRUE -> ���࿡ ���� ä����.
	BOOL		StartProc( FLOAT fEffectTime, RwBool bDirClock = TRUE, RwBool bFill = FALSE ); 
	void		EndProc();

	VOID		Update( FLOAT fCurrentTime );
	VOID		Render(VOID);

	INT			GetWidth() { return m_nWidth; }
	INT			GetHeight() { return m_nHeight; }

	VOID		SetClippingMode( BOOL bClipping );
	VOID		SetClippingRect( CRectangle& rtRect );

	float		GetEffectTime() { return m_fEffectTime; }
	float		GetUpdateElapsedTime() { return m_fUpdateElapsedTime; }

private:
//! Implementation
	VOID		CalcProc0( FLOAT fGradient, BOOL bFirst );
	VOID		CalcProc1( FLOAT fGradient, BOOL bFirst );
	VOID		CalcProc2( FLOAT fGradient, BOOL bFirst );
	VOID		CalcProc3( FLOAT fGradient, BOOL bFirst );
	VOID		CalcProc4( FLOAT fGradient, BOOL bFirst );
	VOID		CalcProc5( FLOAT fGradient, BOOL bFirst );
	VOID		CalcProc6( FLOAT fGradient, BOOL bFirst );
	VOID		CalcProc7( FLOAT fGradient, BOOL bFirst );
	
	FLOAT		GetRelativeValue( FLOAT fValue, FLOAT fComparison );

	VOID		SetAttribute( RwBool bDirClock, RwBool bFill );

//! Viriables
	TriSnapShot m_triOriginal[NUM_TRIANGLE];
	TriSnapShot	m_triSnapShot[NUM_TRIANGLE];
	CTexture*	m_pTexture;

	CalcProc	m_fpCalcProc[NUM_TRIANGLE];

	FLOAT		m_fUpdateElapsedTime;
	FLOAT		m_fEffectTime;
	INT			m_nState;

	INT			m_nWidth;
	INT			m_nHeight;
	FLOAT		m_fUVWidth;
	FLOAT		m_fUVHeight;

	CRectangle	m_rtClipping;
	RwBool		m_bClipping;

	BOOL		m_bShow;
	BOOL		m_bRotDirClock;		// ȸ������.
	BOOL		m_bClockDirFill;	// �ð���� �������� TRUE : �ؽ��İ� ��������. FALSE : �ؽ��İ� �������.	
};

END_GUI

#endif//__GUI_RADAR_EFFECT__
