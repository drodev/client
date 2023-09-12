#pragma once

#include "ceventhandler.h"
#include "NtlSLDef.h"
#include "NtlWorldConceptDefine.h"
/**
 * \ingroup NtlSimulation
 * \brief �� World Concept���� ���� Ŭ����
 * \date 2007-06-14
 * \author agebreak
 */

class CNtlSobActor;

class CNtlWorldConceptController
{
public:

	CNtlWorldConceptController(void);
	virtual ~CNtlWorldConceptController(void);

	virtual void		Update(RwReal fElapsedTime);				///< �� ������ �´� ������� Updateó�� �Լ�
	virtual RwBool		IsEnableAction(EAvatarAction eAction);		///< Avatar�� Action�� ���� ó�� ���������� �� ������ ���� �Ǻ��Ѵ�.
	virtual void		ChangeState(RwInt32 iState);				///< State ���¸� �����Ѵ�.	
	virtual RwInt32		GetState() {return m_iWorldState;}			///< ���� State ���¸� ��ȯ�Ѵ�.
	
	virtual void		BeforeLoadingDirect(void)	{}
	virtual void		AfterLoadingDirect(void)	{}

	virtual RwBool		IsBeforeLoadingDirect(void)	{ return TRUE; }
	virtual RwBool		IsAfterLoadingDirect(void)	{ return TRUE; }

	virtual RwBool		IsMoveableArea(CNtlSobActor *pActor, const RwV3d *pPos, const RwV3d *pDestPos)	{ return TRUE; }
	virtual RwBool		IsVisiblePCInCinematic(VOID) { return FALSE; }

	virtual RwBool		CanUseSkill(RwUInt32 hSerialID, RwUInt32& uiResultCode) { return TRUE; }			

	void				SetConceptType(EWorldPlayConcept eType);
	EWorldPlayConcept	GetConceptType(void);

	void				Pause(RwBool bPause);
	RwBool				IsPause(void)				{ return m_bPause; }

	virtual void		HandleEvents(RWS::CMsg &pMsg) { return; }


protected:

	RwReal				m_fStateTime;									///< �� State������ ����� �ð�
	RwInt32				m_iWorldState;									///< ������ State ����		
	EWorldPlayConcept	m_eType;
	RwBool				m_bPause;
};
