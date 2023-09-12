/*****************************************************************************
*
* File			: NtlFSMUtil.h
* Author		: HyungSuk, Jang
* Copyright	: (��)NTL
* Date			: 2006. 11. 28	
* Abstract		: fsm utility
*****************************************************************************
* Desc         : 
*
*****************************************************************************/

#ifndef __NTL_FSM_UTIL_H__
#define __NTL_FSM_UTIL_H__

class CNtlFSMStateBase;
class CNtlSobActor;

// �̵��� ������ �����ΰ�?
RwBool FSMUtil_CanMoveState(CNtlFSMStateBase *pStateBase);

// ������ ������ �����ΰ�?
RwBool FSMUtil_CanAttackState(CNtlFSMStateBase *pStateBase);

// ������ ���� �� �ִ� �����ΰ�?
RwBool FSMUtil_CanHurtState(CNtlFSMStateBase *pStateBase);

// skill�� ��� ������ �����ΰ�?
RwBool FSMUtil_CanSkillUse(CNtlFSMStateBase *pStateBase);

// idle �����ΰ�?
RwBool FSMUtil_IsIdle(CNtlFSMStateBase *pStateBase);	

// �̵� �����ΰ�?
RwBool FSMUtil_IsMove(CNtlFSMStateBase *pStateBase);		

// ���� ���� �����ΰ�?
RwBool FSMUtil_IsPrivateShopping(CNtlFSMStateBase *pStateBase);

// charging �����ΰ�?
RwBool FSMUtil_IsCharging(CNtlFSMStateBase *pStateBase);

// teleporting �����ΰ�?
RwBool FSMUtil_IsTeleporting(CNtlFSMStateBase *pStateBase);

// ������ ž�� �����ΰ�?
RwBool FSMUtil_IsOnBus(CNtlFSMStateBase* pStateBase);

// Ż �Ϳ� ž�� �����ΰ�?
RwBool FSMUtil_IsOnVehicle(CNtlFSMStateBase* pStateBase);



// 
RwBool FSMUtil_IsStandingAdjustMoveClass(CNtlSobActor *pActor);

RwBool FSMUtil_StandingAdjustMove(CNtlFSMStateBase* pStateBase, CNtlSobActor *pActor);

#endif
