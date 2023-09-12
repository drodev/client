/*****************************************************************************
 *
 * File			: NtlFSMBase.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2006. 2. 9	
 * Abstract		: Finite state machine class
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __NTL_FSMBASE_H__
#define __NTL_FSMBASE_H__

#include "NtlSLDef.h"

class CNtlFSMStateBase;
class CNtlSobActor;

/**
 * \ingroup NtlSimulation
 * DBO���� FSM�� ������Ű�� class�̴�.
 * state�� container ��ɰ� transition ����� �Ѵ�.
 * 
 */
class CNtlFSMBase
{
protected:

    typedef std::map<RwUInt32, CNtlFSMStateBase*> MapState;     ///< Key : State ID, Val : State Pointer
	MapState m_mapState;									    ///< State Container

	CNtlFSMStateBase* Find(RwUInt32 uiStateId);
public:

	virtual ~CNtlFSMBase() {}	
	virtual RwBool Create(void);    ///< �� Ŭ������ ������ �� �ٷ� ȣ���ϴ� �Լ�	
	virtual void Destroy(void);     ///< �� Ŭ������ �Ҹ�Ǳ� ���� ȣ��Ǵ� �Լ�

	RwBool            Register(CNtlFSMStateBase *pState);                                                   ///< State Container�� State�� Add�Ѵ�.	
	CNtlFSMStateBase* CreateState(CNtlSobActor *pActor, RwUInt32 uiNewStateId);                             ///< ������ State�� �����ϴ� �Լ� 	
	virtual CNtlFSMStateBase* Transition(CNtlSobActor *pActor, CNtlFSMStateBase *pOldState, RwUInt32 uiNewStateId); ///< State�� ��ȯ�Ѵ�
};

#endif