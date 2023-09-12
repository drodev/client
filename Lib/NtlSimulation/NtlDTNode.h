/*****************************************************************************
 *
 * File			: NtlDTNode.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 11. 02	
 * Abstract		: direct node
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __NTL_DTNODE_H__
#define __NTL_DTNODE_H__

#include "NtlDTProp.h"

class CNtlSob;

enum EDirectLookAtType	
{
	DIRECT_LOOKAT_NOT_USE,

	// camera�� look at�� spline data�� ���� �����ǰ�, ���� transform ��Ű�� �ʴ´�. 
	DIRECT_LOOKAT_SELF,			

	// camera�� look at�� spline data�� ���� �����ǰ�, 
	// ������ ������ �� �ܺο��� �Էµ� �������� spline data�� ��� ������ rotate �Ѵ�.
	DIRECT_LOOKAT_SELF_ALLAXIS,		

	// camera�� look at�� spline data�� ���� �����ǰ�, 
	// ������ ������ �� �ܺο��� �Էµ� �������� spline data�� Y �����θ� rotate �Ѵ�.
	DIRECT_LOOKAT_SELF_YAXIS,				
	
	// camera�� look at�� camera�� ���� position�� look at position �� ���� �׻� ������ �ȴ�.
	// ������ ������ �� �ܺο��� �Էµ� target position���� spline data�� scale �� Y �����θ� rotate �Ѵ�.
	DIRECT_LOOKAT_DYNAMIC,

	// spline position�� ground height check�� �Ͽ�, ���̿� �����Ѵ�.
	DIRECT_GROUND_MOVE,

	// spline position�� ground height check�� ���� �ʴ´�.
	DIRECT_FLY_MOVE,

	DIRECT_LOOKAT_END = DIRECT_FLY_MOVE
};

class CNtlDTNodeBase
{
protected:

	RwBool m_bFinish;

public:
	
	CNtlDTNodeBase();
	virtual ~CNtlDTNodeBase() {}

	virtual void	SetData(const CNtlDTProp *pProp, const CNtlSob *pSobObj) {}
	virtual void	Update(RwReal fElapsed) {}

	RwBool	IsFinish(void) const { return m_bFinish; }
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

class CNtlDTSplineNode : public CNtlDTNodeBase
{
private:

	CNtlDTSpline	*m_pProp;
	CNtlSob			*m_pSobObj;

	RwReal			m_fCurrTime;		/** ������ �帥 �ð� */
	RwReal			m_fPtTime;			/** ���� spline point�� time */
	RwInt32			m_iPtIdx;			/** ���� curve data index */
	RwV3d			m_vPtPos;
	
	EDirectLookAtType	m_eLookAtType;
	
	RwMatrix		m_matTrans;			/** transform matrix */
	RwMatrix		m_matTransRot;		/** transform roate matrix */
	RwMatrix		m_matRot;			/** rotate temp matrix */
	RwV3d			m_vLookAtPos;		/** camera look at position */

private:

	void UniformTypeUpdate(RwReal fElapsed);
	void TimeSequencetypeUpdate(RwReal fElapsed);

	void GroundMoveUniformUpdate(RwReal fElapsed);
	void GroundMoveTimeSequencetypeUpdate(RwReal fElapsed);

	void SetLookAtSelf(RwV3d vStartPos, RwV3d vEndPos, RwV3d vLookAtPos);
	void SetLookAtSelfAllAxis(RwV3d vStartPos, RwV3d vEndPos, RwV3d vLookAtPos);
	void SetLookAtSelfYAxis(RwV3d vStartPos, RwV3d vEndPos, RwV3d vLookAtPos);
	void SetLookAtSelfScaleAllAxis(RwV3d vStartPos, RwV3d vEndPos, RwV3d vLookAtPos);
	void SetLookAtSelfScaleYAxis(RwV3d vStartPos, RwV3d vEndPos, RwV3d vLookAtPos);
	void SetLookAtDynamic(RwV3d vStartPos, RwV3d vEndPos, RwV3d vLookAtPos);

public:

	CNtlDTSplineNode();
	~CNtlDTSplineNode();

	void SetData(const CNtlDTProp *pProp, const CNtlSob *pSobObj, RwV3d vStartPos, RwV3d vEndPos, RwV3d vLookAtPos, EDirectLookAtType eLookAtType);

	void SetData(const CNtlDTProp *pProp, const CNtlSob *pSobObj, RwV3d vStartPos, RwV3d vTransDir);

	void SetDataGroundMove(const CNtlDTProp *pProp, const CNtlSob *pSobObj, RwV3d vStartPos);

	void SetDataFlyMove(const CNtlDTProp *pProp, const CNtlSob *pSobObj, RwV3d vStartPos);
	
	void Update(RwReal fElapsed);
};

#endif