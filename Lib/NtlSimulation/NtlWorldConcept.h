/*****************************************************************************
 *
 * File			: NtlWorldConcept.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 12. 04	
 * Abstract		: Simulation world concept class
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/


#ifndef __NTL_WORLDCONCEPT_H__
#define __NTL_WORLDCONCEPT_H__

#include "ceventhandler.h"
#include "NtlWorldConceptDefine.h"
#include "NtlWorldConceptController.h"

class CNtlSob;
class CNtlSobActor;

/**
 * \ingroup NtlSimulation
 * \brief ���ӳ��� ���� �ý��ۿ� ���õ� World Concept�� �����ϴ� Ŭ���� 
 * (�ѹ��� Ȱ��ȭ�Ǵ� World Concept�� 2���̻��� �� ���� �ִ�)
 * \date 2007-06-14
 * \author agebreak
 */
class CNtlWorldConcept : public RWS::CEventHandler
{
public:

	CNtlWorldConcept();
	~CNtlWorldConcept();

	static CNtlWorldConcept* GetInstance(void);

	RwBool						Create(void);
	void						Destroy(void);

	void						Reset(void);

	void						Update(RwReal fElapsed);

	void						AddWorldPlayConcept(EWorldPlayConcept ePlayConcept);		///< Ȱ��ȭ�� WorldConcept ����Ʈ�� ���ο� World Concept�� �߰��Ѵ�.
	void						RemoveWorldPlayConcept(EWorldPlayConcept ePlayConcept);		///< Ȱ��ȭ�� WorldConcept ����Ʈ���� World Concept�� �����Ѵ�.

	void						DeleteGradeWorldPlayConcept(RwUInt32 uiGrade);
		
	RwBool						IsActivePlayConcept(EWorldPlayConcept ePlayConcept);		///< ���� WorldConcept�� Ȱ��ȭ �Ǿ� �ִ����� ��ȯ�Ѵ�.	
	RwBool						IsActivePlayGrade(RwUInt32 uiGrade);						///< ���� Grade�� Ȱ��ȭ �Ǿ��ִ°�.
	CNtlWorldConceptController* GetWorldConceptController(EWorldPlayConcept eWorldConcept);	///< World Concept�� �ش��ϴ� ��Ʈ�ѷ� ��ü�� ��ȯ�Ѵ�.
	CNtlWorldConceptController* FindGradeExtController(RwUInt32 uiGrade);		
	
	void						BeforeLoadingDirect(void);
	void						AfterLoadingDirect(void);

	RwBool						IsBeforeLoadingDirect(void);
	RwBool						IsAfterLoadingDirect(void);
	RwBool						IsGrade(RwUInt32 uiGrade, EWorldPlayConcept ePlayType);

	RwBool						HasTutorialWorldConcept( void );
	void						SetHaveTutorialWorldConcept( RwBool bHave );

	//---------------- Methods for status checking ---------------//
	void						EnableAction(RwBool	bEnable);
	RwBool						IsEnableAction(EAvatarAction eAction, BOOL bUnknown = FALSE);						///< Check whether the current action can be performed.

	//----------------- event handler ------------------------//
	void						HandleEvents(RWS::CMsg &pMsg);


	//----------------- world conpect rule ------------------------//

	RwBool						IsMoveableArea(CNtlSobActor *pActor, const RwV3d *pPos, const RwV3d *pDestPos);
	RwBool						IsVisiblePCInCinematic(VOID);

	RwBool						CanUseSkill(RwUInt32 hSerialID, RwUInt32& uiResultCode);

	RwBool						IsEnemyTargetFromAvatarActor(CNtlSobActor *pActor, SERIAL_HANDLE hTargetSerial);	///< 
	RwBool						IsEnemyTargetFromAvatarActor(CNtlSobActor* pActor, CNtlSob* pSobObj);
	CNtlSobActor*				FindNearEnemyFromAvatarActor(CNtlSobActor *pActor);									///< 

protected:

	typedef std::list<CNtlWorldConceptController*>	ListController;

	static CNtlWorldConcept		*m_pInstance;
	ListController				m_listController;

	RwBool						m_bActionEnable;
    RwBool                      m_bIsNightOn;                           ///< ���� Night�� On���� Off���� �Ǻ��ϴ� �÷���

	RwBool						m_bHasTutorialWorldConcept;
};


/// World Concept Ŭ������ �̱��� ��ü�� ��ȯ�Ѵ�.
static CNtlWorldConcept* GetNtlWorldConcept(void)
{
	return CNtlWorldConcept::GetInstance();
}

#endif