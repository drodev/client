#include "gui_particle.h"
#include "gui_particleEmitter.h"
#include "gui_surface.h"

//#ifndef __GUI_PARTICLE_EMITTER_GENERIC_H__
//#define __GUI_PARTICLE_EMITTER_GENERIC_H__

//START_GUI
//
//class CParticleEmitter_Generic
//{
//public:
//	// Construction & Destruction
//	CParticleEmitter_Generic( CParticleEmitter* pSelf );
//	~CParticleEmitter_Generic(VOID);
//
//	// Operation:
//	VOID Start(VOID);
//	VOID End(VOID);
//
//	VOID Update( FLOAT fElapsed );
//
//private:
//	// Implementation:
//	inline VOID CreateParticle(VOID);
//		
//	// CallBack:
//	VOID OnSetOptions(const CComponentOptions& options);
//	VOID OnPaint(VOID);
//	VOID OnMove(INT nX,INT nY);
//	
//	CSlot m_SlotSetOption;
//	CSlot m_SlotPaint;
//	CSlot m_SlotMove;
//	
//public:
//	//! Variable
//	BOOL		m_bStart;
//	
//	FLOAT		m_fElapsedTime;
//
//	std::vector<CSurface> m_vecSurface;
//	std::list<CParticle*> m_listParticle;
//	std::vector<stControlData> m_vecControl;
//
//	DWORD		m_dwEmitMaxCount;		// �ѹ��� ��ŸƮ�� ����� ��ƼŬ�� ���� : 0xffffffff�̸� ����.
//	DWORD		m_dwEmitCurCount;
//
//	FLOAT		m_fEmitRate1;			// ��ƼŬ ���� �ӵ� : �ΰ������� ������. �Ѵ� 0�̸� �ʱ� �ѹ��� ����.
//	FLOAT		m_fEmitRate2;
//
//	FLOAT		m_fLifeTime1;			// ��ƼŬ ���� �ð� : �ΰ������� ������
//	FLOAT		m_fLifeTime2;
//	
//	CRectangle	m_rtEmitterPos;			// ��ƼŬ �ʱ� ��ġ : �簢�� ���� ������.
//	
//	CRectangle	m_rtSize1;				// ��ƼŬ�� �ʱ� ũ�� : �ΰ������� ������
//	CRectangle	m_rtSize2;	
//
//	BYTE		m_ucRed1;				// ��ƼŬ�� �ʱ� ���� : �ΰ������� ������
//	BYTE		m_ucGreen1;
//	BYTE		m_ucBlue1;
//	BYTE		m_ucAlpha1;
//	BYTE		m_ucRed2;
//	BYTE		m_ucGreen2;
//	BYTE		m_ucBlue2;
//	BYTE		m_ucAlpha2;
//
//	FLOAT		m_fZRot1;				// ��ƼŬ�� �ʱ� ȸ���� : �ΰ������� ������
//	FLOAT		m_fZRot2;
//
//	BYTE		m_ucSurfaceIndex1;		// ��ƼŬ�� �ʱ� ���ǽ��� : �ΰ������� ������
//	BYTE		m_ucSurfaceIndex2;
//	
//	CParticleEmitter* m_pParticleEmitter;
//};  
//
//END_GUI
//
//#endif
