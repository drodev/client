#include "precomp_ntlsimulation.h"
#include "NtlFSMCharController.h"

//shared
#include "NtlMovement.h"
#include "NtlResultCode.h"
#include "NtlSkill.h"

//core
#include "NtlDebug.h"
#include "NtlMath.h"

// presentation
#include "NtlPLPicking.h"

// table
#include "SkillTable.h"

// simulation
#include "NtlFSMDef.h"
#include "NtlFSMLayer.h"
#include "NtlFSMStateBase.h"
#include "NtlSLEvent.h"
#include "NtlSLEventFunc.h"
#include "NtlFSMCharActAgent.h"
#include "NtlFSMEventQueuingHelper.h"
#include "NtlPacketGenerator.h"
#include "NtlSLGlobal.h"
#include "NtlSLPacketGenerator.h"
#include "NtlBehaviorData.h"
#include "NtlSobActor.h"
#include "NtlSobPet.h"
#include "NtlSobPetAttr.h"
#include "NtlSobIcon.h"
#include "NtlSobSkillIcon.h"
#include "NtlSobSkillAttr.h"
#include "NtlSobManager.h"
#include "NtlSobPlayer.h"
#include "NtlSobPlayerAttr.h"
#include "NtlSkillContainer.h"
#include "NtlSLLogic.h"
#include "NtlSLApi.h"
#include "NtlClock.h"
#include "NtlFSMUtil.h"

#define NTL_SUMMON_PET_FOLLOW_DIST				4.0f
#define NTL_SUMMON_PET_RESET_POSITION_DIST		55.0f

#define NTL_SUMMON_PET_WANDER_TIME				20.0f

CNtlFSMAutoFollowCmdAI::CNtlFSMAutoFollowCmdAI(CNtlSobActor *pActor)
{
	m_fThinkTime		= 0.0f;
	m_eState			= EAFS_MOVE;
	m_bFinish			= FALSE;
	m_pActor			= pActor;
	m_pAliveTarActor	= NULL;
}

CNtlFSMAutoFollowCmdAI::~CNtlFSMAutoFollowCmdAI()
{
}

void CNtlFSMAutoFollowCmdAI::Update(RwReal fElapsed)
{
	m_fThinkTime += fElapsed;

	if(m_fThinkTime >= 0.3f)
	{
		if(!IsAliveTarget())
		{
			m_bFinish = TRUE;
			return;
		}

		if(m_eState == EAFS_IDLE)
		{
			UpdateIdle(fElapsed);
		}
		else
		{
			UpdateMove(fElapsed);
		}

		m_fThinkTime = 0.0f;
	}
}

RwBool CNtlFSMAutoFollowCmdAI::IsFinish(void)
{
	return m_bFinish;
}


RwBool CNtlFSMAutoFollowCmdAI::IsAliveTarget(void)
{
	CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(m_pActor->GetBehaviorData()); 
	SCtrlStuff *pCtrlStuff = pBeData->GetCtrlStuff(); 

	m_pAliveTarActor = reinterpret_cast<CNtlSobActor*>( GetNtlSobManager()->GetSobObject(pCtrlStuff->hTargetSerialId) );
	if(m_pAliveTarActor == NULL)
		return FALSE;

	return TRUE;
}

RwBool CNtlFSMAutoFollowCmdAI::IsRoundInTarget(void)
{
	CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(m_pActor->GetBehaviorData()); 
	SCtrlStuff *pCtrlStuff = pBeData->GetCtrlStuff(); 

	RwV3d vPos		= m_pActor->GetPosition();
	RwV3d vTarPos	= m_pAliveTarActor->GetPosition();

	RwV3d vSub;

	RwV3dSubMacro(&vSub, &vTarPos, &vPos);

	RwReal fLen = RwV3dLength(&vSub);

	if(fLen > pCtrlStuff->fFollowRange *1.5f)
		return FALSE;

	return TRUE;
}

void CNtlFSMAutoFollowCmdAI::UpdateIdle(RwReal fElapsed)
{
	if(IsRoundInTarget())
		return;

	CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(m_pActor->GetBehaviorData()); 
	SCtrlStuff *pCtrlStuff = pBeData->GetCtrlStuff(); 

	RwV3d vPos = m_pActor->GetPosition();
	CNtlSLEventGenerator::SobFollowMove(m_pActor->GetSerialID(), pCtrlStuff->hTargetSerialId, NTL_MOVE_FLAG_RUN, vPos, pCtrlStuff->fFollowRange, DBO_MOVE_FOLLOW_FRIENDLY, 0);

	m_eState = EAFS_MOVE;
}

void CNtlFSMAutoFollowCmdAI::UpdateMove(RwReal fElapsed)
{
	if(FSMUtil_IsIdle(m_pActor->GetCurrentState()))
	{
		m_eState = EAFS_IDLE;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CNtlSummonPetAI::CNtlSummonPetAI()
{
	m_eState		= ESPS_IDLE;
	m_pController	= NULL;

	m_fStateTimer		= 0.0f;
	m_fThinkingTimer	= 0.0f;
	m_fPathTimer		= 0.0f;

	for(int i=0; i<NTL_MAX_NPC_HAVE_SKILL; ++i)
		m_fSkillTimer[i] = 0.0f;

	m_bCompulsoryAttack		= FALSE;
	m_hBattleSerialId		= INVALID_SERIAL_ID;
}

CNtlSummonPetAI::~CNtlSummonPetAI()
{
}

void CNtlSummonPetAI::Create(CNtlFSMController *pController)
{
	m_pController = pController;
}

void CNtlSummonPetAI::Destroy(void)
{
}

void CNtlSummonPetAI::UpdateIdle(RwReal fElapsed)
{
	if(IsThinking())
	{
		if(!GetActor()->CanMove())
		{
			ResetThinkingTimer();
			return;
		}

		RwReal fDist;
		if(!IsRoundInOwner(fDist))
		{
			if(fDist >= NTL_SUMMON_PET_RESET_POSITION_DIST)
				JumpPosition();
			else
			{
				CNtlSobActor *pActor = GetActor();
				CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(pActor->GetBehaviorData()); 
				SMoveStuff *pMoveStuff = pBeData->GetMoveStuff();
				if(pMoveStuff->byMoveResult & NTL_MOVE_RESULT_COLLISION)
					ChangeState(ESPS_COLLISION_AVOID);
				else
					ChangeState(ESPS_TARGET_FOLLOW);
			}
		}
		else
		{
			ChangeState(ESPS_POSITION_SET);
		}
	}
}

void CNtlSummonPetAI::UpdatePositionSet(RwReal fElapsed)
{
	if(IsThinking())
	{
		if(!GetActor()->CanMove())
		{
			ChangeState(ESPS_IDLE);
			return;
		}
		
		if(m_fStateTimer >= NTL_SUMMON_PET_WANDER_TIME)
		{
			Wander();
			ResetStateTimer();
		}
		else
		{
			ChangeState(ESPS_OBSERVATION);
		}
	}
}

void CNtlSummonPetAI::UpdateObservation(RwReal fElapsed)
{
	if(IsThinking())
	{
		if(!GetActor()->CanMove())
		{
			ChangeState(ESPS_IDLE);
			return;
		}

		if(IsOwnerFighting())
		{
			// owner �� target �ϰ� �ִ� ��ü�� �����̳�?
			m_hBattleSerialId = SearchFightingTarget();
			if(m_hBattleSerialId != INVALID_SERIAL_ID)
			{
				// target�� �����ϰ�... ������ �Ѵ�.
				ChangeState(ESPS_BATTLE);
			}
			else
			{
				ChangeState(ESPS_IDLE);
			}
		}
		else
		{
			SERIAL_HANDLE hFinialHurtSerialId = GetActor()->GetFinialHurtSerialId();
			if( hFinialHurtSerialId != INVALID_SERIAL_ID)
			{
				CNtlSobActor *pTarActor = reinterpret_cast<CNtlSobActor*>( GetNtlSobManager()->GetSobObject(hFinialHurtSerialId) );
				if(pTarActor == NULL)
					ChangeState(ESPS_IDLE);
				else
				{
					if(pTarActor->IsDie())
						ChangeState(ESPS_IDLE);
					else
					{
						m_hBattleSerialId = hFinialHurtSerialId;
						ChangeState(ESPS_BATTLE);
					}
				}
			}
			else
			{
				ChangeState(ESPS_IDLE);
			}
		}
	}
}

void CNtlSummonPetAI::UpdateCollisionAvoid(RwReal fElapsed)
{
	if(IsThinking())
	{
		if(FSMUtil_IsIdle(GetActor()->GetCurrentState()))
		{
			ChangeState(ESPS_IDLE);
		}

		ResetThinkingTimer();
	}
}

void CNtlSummonPetAI::UpdateTargetFollow(RwReal fElapsed)
{
	/*
	if(IsThinking())
	{
		if(GetActor()->CanMove())
		{
			RwReal fDist;
			RwUInt32 uiStateId = GetActorStateId();
			if(IsRoundInOwner(fDist))
			{
				if(uiStateId == NTL_FSMSID_IDLE)
				{
					ChangeState(ESPS_POSITION_SET);
				}
			}
			else
			{
				if(fDist >= NTL_SUMMON_PET_RESET_POSITION_DIST)
				{
					ClearOwnerTrace();
					JumpPosition();
					CNtlSLEventGenerator::SobStateTransition(GetActor()->GetSerialID(), NTL_FSMSID_IDLE);
					ChangeState(ESPS_IDLE);
				}
				else
					EventGeneratorFollowState();
			}
		}
		else
		{
			ChangeState(ESPS_IDLE);
		}

		ResetThinkingTimer();
	}
	*/

	if(IsThinking())
	{
		if(FSMUtil_IsIdle(GetActor()->GetCurrentState()))
		{
			ChangeState(ESPS_IDLE);
		}

		ResetThinkingTimer();
	}
}

void CNtlSummonPetAI::UpdateBattle(RwReal fElapsed)
{
	CNtlSobActor *pActor = GetActor();

	if(m_fThinkingTimer >= 0.1f)
	{
		if( pActor->CanMove() )
		{
			/*if(!IsOwnerFighting())
			{*/
				if(!IsKeepBattle())
				{
					ResetThinkingTimer();
					ChangeState(ESPS_IDLE);
					return;
				}
			/*}*/

			// owner�� position�� ���� �ִ°�? ���� �ִٸ� BATTLE_POSITION_SET ���¸� �༭
			// ������ �� �� �ִ� ������ ���̵� �ϰ� �Ѵ�.
			if(BattleWander())
				ChangeState(ESPS_BATTLE_POSITION_SET);
		}

		// ���� ���� ��ų�� ��밡���� �����̸� ��ų�� ����ϴ� AI �Ǵ��� �Ѵ�.
		if(Logic_CanSkillUse(GetActor()))
			SkillAction();

		ResetThinkingTimer();
	}
}

void CNtlSummonPetAI::UpdateBattlePositionSet(RwReal fElapsed)
{
	// Battle Position Set���� ���� ���߰� �ִ�.
	if(m_fThinkingTimer >= 0.1f)
	{
		RwUInt32 uiStateId = GetActorStateId();
		if(uiStateId == NTL_FSMSID_IDLE)
			ChangeState(ESPS_IDLE);
		else if(uiStateId == NTL_FSMSID_FIGHTING_POSE || 
			uiStateId == NTL_FSMSID_FIGHTING_SHRINK ||
			uiStateId == NTL_FSMSID_FIGHTING )
			ChangeState(ESPS_BATTLE);

		ResetThinkingTimer();
	}
}

void CNtlSummonPetAI::UpdateDie(RwReal fElapsed)
{
}

void CNtlSummonPetAI::Update(RwReal fElapsed)
{
	if(m_eState == ESPS_IDLE)
		UpdateIdle(fElapsed);
	else if(m_eState == ESPS_POSITION_SET)
		UpdatePositionSet(fElapsed);
	else if(m_eState == ESPS_OBSERVATION)
		UpdateObservation(fElapsed);
	else if(m_eState == ESPS_COLLISION_AVOID)
		UpdateCollisionAvoid(fElapsed);
	else if(m_eState == ESPS_TARGET_FOLLOW)
		UpdateTargetFollow(fElapsed);
	else if(m_eState == ESPS_BATTLE)
	{
		UpdateBattle(fElapsed);
		
	}
	else if(m_eState == ESPS_BATTLE_POSITION_SET)
		UpdateBattlePositionSet(fElapsed);
	else if(m_eState == ESPS_DIE)
		UpdateDie(fElapsed);

	m_fStateTimer		+= fElapsed;
	m_fThinkingTimer	+= fElapsed;
	m_fPathTimer		+= fElapsed;

	for(int i=0; i<NTL_MAX_NPC_HAVE_SKILL; ++i)
		m_fSkillTimer[i] += fElapsed;

	
	// Skill Timer�� ������Ų��.
	

//	CalcOwnerTrace();
}

void CNtlSummonPetAI::EnterState(CNtlSummonPetAI::ESummonPetState eState)
{
	if(m_eState == ESPS_IDLE)
	{
		m_hBattleSerialId = INVALID_SERIAL_ID;
	}
	else if(m_eState == ESPS_POSITION_SET)
	{
	}
	else if(m_eState == ESPS_OBSERVATION)
	{
	}
	else if(m_eState == ESPS_COLLISION_AVOID)
	{
		EventGeneratorCollisionAvoid();
	}
	else if(m_eState == ESPS_TARGET_FOLLOW)
	{
		EventGeneratorFollowState();
	}
	else if(m_eState == ESPS_BATTLE)
	{
		// BAttle�� ���� �ʱ�ȭ�Ѵ�.
		for(int i=0; i<NTL_MAX_NPC_HAVE_SKILL; ++i)
			m_fSkillTimer[i] = 0.0f;
		
		EventGeneratorAttackFollowState();
	}
	else if(m_eState == ESPS_BATTLE_POSITION_SET)
	{
	}
	else if(m_eState == ESPS_DIE)
	{
	}
}

void CNtlSummonPetAI::ExitState(ESummonPetState eState)
{
	if(m_eState == ESPS_IDLE)
	{
	}
	else if(m_eState == ESPS_POSITION_SET)
	{
	}
	else if(m_eState == ESPS_OBSERVATION)
	{
	}
	else if(m_eState == ESPS_TARGET_FOLLOW)
	{
		ResetStateTimer();
	}
	else if(m_eState == ESPS_BATTLE)
	{
		ResetStateTimer();
	}
	else if(m_eState == ESPS_BATTLE_POSITION_SET)
	{
		CNtlSobActor *pActor = GetActor();
		CNtlSob *pSobTar = GetNtlSobManager()->GetSobObject(m_hBattleSerialId);
		if(pSobTar)
		{
			RwV3d vPos		= pActor->GetPosition();
			RwV3d vTarPos	= pSobTar->GetPosition();
			RwV3d vTarDir;
			RwV3dSubMacro(&vTarDir, &vTarPos, &vPos);
			vTarDir.y = 0.0f;
			pActor->SetDirection(&vTarDir);
		}
	}
	else if(m_eState == ESPS_DIE)
	{
		ResetStateTimer();
	}
}

void CNtlSummonPetAI::ChangeState(ESummonPetState eState, RwBool bEqualStateChange /*= FALSE*/)
{
	if(!bEqualStateChange)
	{
		if(m_eState == eState)
		{
			ResetThinkingTimer();
			return;
		}
	}

	ExitState(m_eState);
	m_eState = eState;
	EnterState(m_eState);

	ResetThinkingTimer();
}

CNtlSobActor* CNtlSummonPetAI::GetActor(void)
{
	return m_pController->GetActor();
}

void CNtlSummonPetAI::ResetStateTimer(void)
{
	m_fStateTimer = 0.0f;
}

void CNtlSummonPetAI::ResetThinkingTimer(void)
{
	m_fThinkingTimer = 0.0f;
}

void CNtlSummonPetAI::ResetPathTimer(void)
{
	m_fPathTimer = 0.0f;
}

void CNtlSummonPetAI::ResetSkillTimer(RwInt32 iSlotIdx)
{
	NTL_ASSERT( iSlotIdx >= 0 && iSlotIdx < NTL_MAX_NPC_HAVE_SKILL , "CNtlSummonPetAI::ResetSkillTimer ---- index over" );

	m_fSkillTimer[ iSlotIdx ] = 0.0f;
}

RwBool CNtlSummonPetAI::IsThinking(void)
{
	// �����ϴ� Ÿ���� �ʹ� ª�Ƽ� ������ ���� ���Ѵ�.
	if(m_fThinkingTimer > 0.2f)
		return TRUE;

	return FALSE;
}

CNtlFSMStateBase* CNtlSummonPetAI::GetActorState(void)
{
	CNtlSobActor *pActor = GetActor();
	return pActor->GetCurrentState();
}


RwUInt32 CNtlSummonPetAI::GetActorStateId(void)
{
	CNtlSobActor *pActor = GetActor();
	return Logic_GetActorStateId(pActor);
}

CNtlFSMStateBase* CNtlSummonPetAI::GetOwnerActorState(void)
{
	CNtlSobActor *pActor = GetActor();
	CNtlSobActor *pOwnerActor = reinterpret_cast<CNtlSobActor*>( GetNtlSobManager()->GetSobObject(pActor->GetOwnerID()) );
	if(pOwnerActor == NULL)
		return NULL;

	return pOwnerActor->GetCurrentState();
}

RwUInt32 CNtlSummonPetAI::GetOwnerActorStateId(void)
{
	CNtlSobActor *pActor = GetActor();
	CNtlSobActor *pOwnerActor = reinterpret_cast<CNtlSobActor*>( GetNtlSobManager()->GetSobObject(pActor->GetOwnerID()) );
	if(pOwnerActor == NULL)
		return NTL_FSMSID_INVALID;

	return Logic_GetActorStateId(pOwnerActor);
}

SERIAL_HANDLE CNtlSummonPetAI::GetOwnerTargetSerial(void)
{
	CNtlSobActor *pActor = GetActor();
	CNtlSobActor *pOwnerActor = reinterpret_cast<CNtlSobActor*>( GetNtlSobManager()->GetSobObject(pActor->GetOwnerID()) );
	if(pOwnerActor == NULL)
		return INVALID_SERIAL_ID;

	return Logic_GetActorTargetSerialId(pOwnerActor);
}

RwBool CNtlSummonPetAI::IsRoundInOwner(RwReal& fDist)
{
	CNtlSobActor *pActor = GetActor();
	CNtlSobActor *pOwnerActor = reinterpret_cast<CNtlSobActor*>( GetNtlSobManager()->GetSobObject(pActor->GetOwnerID()) );
	if(pOwnerActor == NULL)
	{
		fDist = 0.0f;
		return TRUE;
	}

	RwV3d vActorPos = pActor->GetPosition();
	RwV3d vOwnerPos = pOwnerActor->GetPosition();

    // Ÿ���� �����ϴ� ������ ��쿡�� y����
    SWorldHeightStuff hStuff;
    if(Logic_IsSwimmingActor(pOwnerActor, &pOwnerActor->GetPosition(), hStuff))
    {
        vActorPos.y = vOwnerPos.y = 0.0f;
    }

    fDist = CNtlMath::GetLength(vOwnerPos, vActorPos);

	RwReal fActorRadius = Logic_GetRadius(pActor);
	RwReal fOwnerRadius = Logic_GetRadius(pOwnerActor);

	if(fDist < NTL_SUMMON_PET_FOLLOW_DIST+fActorRadius+fOwnerRadius)
		return TRUE;

	return FALSE;
}

RwReal CNtlSummonPetAI::GetDistanceOwner(void)
{
	CNtlSobActor *pActor = GetActor();
	CNtlSobActor *pOwnerActor = reinterpret_cast<CNtlSobActor*>( GetNtlSobManager()->GetSobObject(pActor->GetOwnerID()) );
	if(pOwnerActor == NULL)
		return 0.0f;

	RwV3d vActorPos = pActor->GetPosition();
	RwV3d vOwnerPos = pOwnerActor->GetPosition();

	RwV3d vDelta;
	RwV3dSubMacro(&vDelta, &vOwnerPos, &vActorPos);
	RwReal fDist = RwV3dLength(&vDelta);

	RwReal fActorRadius = Logic_GetRadius(pActor);
	RwReal fOwnerRadius = Logic_GetRadius(pOwnerActor);

	return fDist-fActorRadius-fOwnerRadius;
}

RwBool CNtlSummonPetAI::IsOwnerFighting(void)
{
	CNtlSobActor *pActor = GetActor();
	CNtlSobActor *pOwnerActor = reinterpret_cast<CNtlSobActor*>( GetNtlSobManager()->GetSobObject(pActor->GetOwnerID()) );
	if(pOwnerActor == NULL)
		return FALSE;

	return Logic_IsActorBattleMode(pOwnerActor);
}



void CNtlSummonPetAI::Wander(void)
{
	CNtlSobActor *pActor = GetActor();
	CNtlSobActor *pOwnerActor = reinterpret_cast<CNtlSobActor*>( GetNtlSobManager()->GetSobObject(pActor->GetOwnerID()) );
	if(pOwnerActor == NULL)
		return;

	RwV3d vOwnerPos = pOwnerActor->GetPosition();
	RwReal fRadius = Logic_GetRadius(pOwnerActor);
	RwReal fRandValueX = NtlRandomNumber(0.2f, 0.5f);
	RwReal fRandValueZ = NtlRandomNumber(0.2f, 0.5f);

	if(rand()%2)
		vOwnerPos.x += fRadius+NTL_SUMMON_PET_FOLLOW_DIST*fRandValueX;
	else
		vOwnerPos.x -= fRadius+NTL_SUMMON_PET_FOLLOW_DIST*fRandValueX;

	if(rand()%2)
		vOwnerPos.z += fRadius+NTL_SUMMON_PET_FOLLOW_DIST*fRandValueZ;
	else
		vOwnerPos.z -= fRadius+NTL_SUMMON_PET_FOLLOW_DIST*fRandValueZ;

	RwV3d vPos = pActor->GetPosition();

	CNtlSLEventGenerator::SobDestMove(pActor->GetSerialID(), NTL_MOVEFORM_GROUND, vPos, vOwnerPos, 0);
	API_GetSLPacketGenerator()->SendMouseMove(pActor->GetPosition(), vOwnerPos, pActor->GetServerSyncAvatarType());  
}


RwBool CNtlSummonPetAI::BattleWander(void)
{
	RwUInt32 uiStateId = GetActorStateId();
	if(uiStateId != NTL_FSMSID_FIGHTING_POSE)
		return FALSE;

	CNtlSobActor *pActor = GetActor();
	CNtlSobActor *pOwnerActor = reinterpret_cast<CNtlSobActor*>( GetNtlSobManager()->GetSobObject(pActor->GetOwnerID()) );
	if(pOwnerActor == NULL)
		return FALSE;

	CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>( pActor->GetBehaviorData() );
	SCtrlStuff *pCtrlStuff = pBeData->GetCtrlStuff();

	CNtlSob *pSobTar = GetNtlSobManager()->GetSobObject(pCtrlStuff->hTargetSerialId);
	if(pSobTar == NULL)
		return FALSE;

	RwV3d vPos		= pActor->GetPosition();
	RwV3d vOwnerPos = pOwnerActor->GetPosition();
	RwV3d vTarPos	= pSobTar->GetPosition();

	RwV3d vDestPos  = vPos;

	RwV3d vOwnerDir, vTarDir;
	RwV3dSubMacro(&vOwnerDir, &vOwnerPos, &vPos);
	RwV3dSubMacro(&vTarDir, &vTarPos, &vPos);

	vOwnerDir.y = 0.0f;
	vTarDir.y = 0.0f;

	RwReal fOwnerDist = RwV3dLength(&vOwnerDir);
	
	RwV3dNormalize(&vOwnerDir, &vOwnerDir);
	RwV3dNormalize(&vTarDir, &vTarDir);

	RwReal fAttackRange = Logic_GetAttackRange(pActor, pSobTar->GetSerialID());

	RwReal fActorRadius = Logic_GetRadius(pActor);
	RwReal fOwnerRadius = Logic_GetRadius(pOwnerActor);
	RwReal fSumRadius	= fActorRadius + fOwnerRadius;

	if(fOwnerDist < 0.5f || fOwnerDist < fSumRadius*0.8f)
	{
		RwMatrix mat;
		CNtlMath::MathRwMatrixAssign(&mat, &CNtlPLGlobal::m_vZeroV3, &vTarDir);
		RwReal fRandWeight = NtlRandomNumber(0.1f, 0.5f);
		RwReal fRandDist = NtlRandomNumber(fAttackRange, fAttackRange*1.5f);

		if(rand()%2)
		{
			vDestPos.x += vTarDir.x*fRandDist*fRandWeight + mat.right.x*fRandDist*(1.0f-fRandWeight);
			vDestPos.z += vTarDir.z*fRandDist*fRandWeight + mat.right.z*fRandDist*(1.0f-fRandWeight);
		}
		else
		{
			vDestPos.x += vTarDir.x*fRandDist*fRandWeight - mat.right.x*fRandDist*(1.0f-fRandWeight);
			vDestPos.z += vTarDir.z*fRandDist*fRandWeight - mat.right.z*fRandDist*(1.0f-fRandWeight);
		}

		CNtlSLEventGenerator::SobDestMove(pActor->GetSerialID(), NTL_MOVEFORM_GROUND, vPos, vDestPos, 0);
		API_GetSLPacketGenerator()->SendMouseMove(pActor->GetPosition(), vPos, pActor->GetServerSyncAvatarType());  

		return TRUE;
	}

	return FALSE;
}

/**
* \brief ��ų�� ������� ������ �Ǵ��Ͽ� ��ų�� ����Ѵ�.
* \return ��ų ����, ���� ����
*/
RwBool CNtlSummonPetAI::SkillAction(void)
{
	// ���� �������� ��ų�� ������ �ִ�.
	/*CNtlSobPet *pSobPet = reinterpret_cast<CNtlSobPet*>( GetActor() );*/
	
	// ��ų ���� ��� ���θ� �Ǵ��Ͽ� ��ų�� ����Ϸ��� ���� ���� ���� ���������
	// �� �߿��� �ϳ��� �������� ����Ѵ�. ( �켱 ���� ���� �� ����. )
	for(int i=0; i< NTL_MAX_NPC_HAVE_SKILL; ++i)
	{
		if( IsThinkingUseSkill( i ) )
		{
			// ��� ���� �Ǵ�
			m_vecUseSlotIdx.push_back( i );
		}
	}

	// �ϳ��� ���� ���ߴٴ� �Ǵ�
	if( m_vecUseSlotIdx.empty() )
		return FALSE;

	// �ƴ϶�� ������ �ߴٴ� ���̹Ƿ� �������� �������ش�.
	RwInt32 iSize = (RwInt32)m_vecUseSlotIdx.size();
	RwInt32 iUseSlotIdx = m_vecUseSlotIdx[rand()%iSize];

	// ���õ� ��ų���� �����ش�.
	m_vecUseSlotIdx.clear();

	return SkillAction( iUseSlotIdx );
}

/**
Use \ brief Skill.
* \ param iSlotIdx (RwInt32) Skill's Slot Index
* \ return success, failure
*/
RwBool CNtlSummonPetAI::SkillAction(RwInt32 iSlotIdx)
{
	// Use of skills
	CNtlSobPet* pSobPet = reinterpret_cast<CNtlSobPet*>( GetActor() );
	CNtlPetSkillContainer *pSkillContainer = pSobPet->GetSkillContainer();

	CNtlSobSkill* pSobSkill = reinterpret_cast<CNtlSobSkill*>( pSkillContainer->GetSkill( iSlotIdx ) );
	if( !pSobSkill )
		return FALSE;

	CNtlSobSkillIcon* pSobSkillIcon = reinterpret_cast<CNtlSobSkillIcon*>( pSobSkill->GetIcon() );

	if( !pSobSkillIcon->IsUsePossible() )
		return FALSE;

	CNtlSobSkillAttr* pSobSkillAttr = reinterpret_cast<CNtlSobSkillAttr*>( pSobSkill->GetSobAttr() ); 
	sSKILL_TBLDAT *pTable = pSobSkillAttr->GetSkillTbl();

	// Put the appropriate target according to the type to be applied.
	SERIAL_HANDLE hTarget;
	if( pTable->byApply_Target == DBO_SKILL_APPLY_TARGET_SELF )
	{
		hTarget = pSobPet->GetSerialID();
	}
	else if( pTable->byApply_Target == DBO_SKILL_APPLY_TARGET_ENEMY )
	{
		hTarget = m_hBattleSerialId;
	}
	else if( pTable->byApply_Target == DBO_SKILL_APPLY_TARGET_ALLIANCE )
	{
		hTarget = pSobPet->GetOwnerID();
	}
	else if(pTable->byApply_Target == DBO_SKILL_APPLY_TARGET_PARTY)	// Party
	{
		hTarget = pSobPet->GetSerialID();
	}
	else
	{
		DBO_WARNING_MESSAGE("Unknown apply target type: " << pTable->byApply_Target);
	}

	return pSobSkillIcon->Use( hTarget, INVALID_BYTE );
}


/**
* \brief SkillContainer�� iSlotIdx��° ��ġ�� ��ų�� AI�� �Ǵ� ������ �Ǵ��� Ȯ���Ѵ�.
* \param iSlotIdx	(RwInt32) ��ų ����
* \return TRUE: ����Ѵ�. FALSE: ������� �ʴ´�.
*/
RwBool CNtlSummonPetAI::IsThinkingUseSkill(RwInt32 iSlotIdx)
{
    if(iSlotIdx >= NTL_MAX_NPC_HAVE_SKILL)
        return FALSE;

	CNtlSobPet *pSobPet = reinterpret_cast<CNtlSobPet*>( GetActor() );
	CNtlPetSkillContainer *pSkillContainer = pSobPet->GetSkillContainer();
	
	// ��ų �����̳ʿ� ��ų�� ���ٸ� ����Ѵٰ� �Ǵ��� ���� �� ����.
	if( pSkillContainer->GetSkillCount() < iSlotIdx )
		return FALSE;

	// Skill �� AI Basis Time �� Ȯ���Ͽ� ���� �Ǵ��� Ÿ���� �ƴ϶�� ��ų�� ������� �ʴ´�.
	if( m_fSkillTimer[iSlotIdx] < pSkillContainer->GetSkillUseTime( iSlotIdx ) )
		return FALSE;

	// Ÿ�� �ʱ�ȭ
	ResetSkillTimer( iSlotIdx );

	// Basis Ȯ��
	RwUInt8 byUseBasis = pSkillContainer->GetSkillUseBasis( iSlotIdx );
	
	// enum eSKILLPRIORITY ( NtlSkill.h )
	switch( byUseBasis )
	{
	case SKILLPRIORITY_CALL:
	case SKILLPRIORITY_START:
	case SKILLPRIORITY_FAINTING:	// CALL, START, FAINTING ������
		return FALSE;
		
	case SKILLPRIORITY_LP:			// �ڱ� �ڽ��� LP �� ���ǰ� ��ġ�Ѵٸ� ������ ���
		{
			RwUInt16 wUseLp = pSkillContainer->GetSkillUseLp( iSlotIdx );

			CNtlSobPetAttr* pAttr = reinterpret_cast<CNtlSobPetAttr*>( pSobPet->GetSobAttr() );
			
			// ���� ���� LP ����
			RwReal fLpRate = ( (RwReal)pAttr->GetLp() / (RwReal)pAttr->GetMaxLp()) * 100.0f;

			// ���� ���� LP���� ��� ������ ���� �ʴ´ٸ� ������� �ʴ´�.
			if( (RwReal)wUseLp < fLpRate )
			{
				return FALSE;
			}
		}
		break;

	case SKILLPRIORITY_GIVE:		// ������ LP ��ġ�� ������ �����Ѵٸ� ������ ���
		{
			RwUInt16 wUseLp = pSkillContainer->GetSkillUseLp( iSlotIdx );

			CNtlSobPlayer* pSobPlayer = reinterpret_cast<CNtlSobPlayer*>(GetNtlSobManager()->GetSobObject(pSobPet->GetOwnerID()));
			CNtlSobPlayerAttr* pSobPlayerAttr = reinterpret_cast<CNtlSobPlayerAttr*>(pSobPlayer->GetSobAttr());

			// ���� ������ LP ����
			RwReal fLpRate = ( (RwReal)pSobPlayerAttr->GetLp() / (RwReal)pSobPlayerAttr->GetMaxLp() ) * 100.0f;

			if( (RwReal)wUseLp < fLpRate )
			{
				return FALSE;
			}
		}
		break;

	case SKILLPRIORITY_TIME:
		{
			RwUInt16 wUseTime = pSkillContainer->GetSkillUseLp( iSlotIdx );

			RwInt32 iRate = rand()%100;

			// Ȯ�� �ߵ�
			if( iRate > wUseTime)
			{
				return FALSE;
			}
		}
	
		break;
	default:						// Table Data�� �̻�
		return FALSE;
	}

	// ��ų�� AI ������ ���������� ��ų�� ����� �� �ִ� �������� �ƴ��� Ȯ���Ѵ�.
	CNtlSobSkill* pSobSkill = pSkillContainer->GetSkill( iSlotIdx );
	CNtlSobSkillAttr* pSobSkillAttr = reinterpret_cast<CNtlSobSkillAttr*>(pSobSkill->GetSobAttr());
	sSKILL_TBLDAT* pSkillTbl = pSobSkillAttr->GetSkillTbl();

	// ��� ������ EP�� �ȵ�
	if( Logic_GetEp( pSobPet ) < pSkillTbl->wRequire_EP )
		return FALSE;

	CNtlSobSkillIcon* pSobSkillIcon = reinterpret_cast<CNtlSobSkillIcon*>(pSobSkill->GetIcon());
	
	// ��Ÿ�� ��
	if( pSobSkillIcon->GetIconState() != CNtlSobSkillIcon::ICON_STATE_USEABLE )
		return FALSE;

	return TRUE;
}

void CNtlSummonPetAI::JumpPosition(void)
{
	CNtlSobActor *pActor = GetActor();
	CNtlSobActor *pOwnerActor = reinterpret_cast<CNtlSobActor*>( GetNtlSobManager()->GetSobObject(pActor->GetOwnerID()) );
	if(pOwnerActor == NULL)
		return;

	RwV3d vActorPos = pActor->GetPosition();
	RwV3d vOwnerPos = pOwnerActor->GetPosition();

	vActorPos = vOwnerPos;

	RwV3d vOwnerDir = pOwnerActor->GetDirection();
	RwV3dScale(&vOwnerDir, &vOwnerDir, -1.0f);

	RwReal fRadius = Logic_GetRadius(pOwnerActor);

	vActorPos.x += vOwnerDir.x * NtlRandomNumber(fRadius+2.0f, fRadius+4.0f);
	vActorPos.y = vOwnerPos.y;
	vActorPos.z += vOwnerDir.z * NtlRandomNumber(fRadius+2.0f, fRadius+4.0f);

	SWorldHeightStuff sHStuff;
	Logic_GetWorldHeight(pActor, &vActorPos, sHStuff);
	vActorPos.y = sHStuff.fFinialHeight;

	pActor->SetPosition(&vActorPos);

//	ClearOwnerTrace();
}

SERIAL_HANDLE CNtlSummonPetAI::SearchFightingTarget(void)
{
	// 1. owner�� ���� �ֱٿ� ������ target�� ã�´�.
	// 2. owner�� target�� ã�´�.
	// 3. ������ �������� �ʴ´�. 

	CNtlSobActor *pActor = GetActor();
	CNtlSobActor *pOwnerActor = reinterpret_cast<CNtlSobActor*>( GetNtlSobManager()->GetSobObject(pActor->GetOwnerID()) );
	if(pOwnerActor == NULL)
		return INVALID_SERIAL_ID;

	SERIAL_HANDLE hTargetSerialId	= Logic_GetActorTargetSerialId(pOwnerActor);
	SERIAL_HANDLE hHurtSerialId		= pOwnerActor->GetFinialHurtSerialId();

	if(hHurtSerialId != INVALID_SERIAL_ID)
	{
		CNtlSobActor *pAttackActor = reinterpret_cast<CNtlSobActor*>( GetNtlSobManager()->GetSobObject(hHurtSerialId) );
		if(pAttackActor)
		{
			if(Logic_IsEnemyTagetFromPetActor(pActor, hHurtSerialId))
				return hHurtSerialId;
		}
	}

	if(hTargetSerialId != INVALID_SERIAL_ID)
	{
		if(Logic_IsEnemyTagetFromPetActor(pActor, hTargetSerialId))
			return hTargetSerialId;
	}

	return INVALID_SERIAL_ID;
}

RwBool CNtlSummonPetAI::IsKeepBattle(void)
{
	RwReal fDist = GetDistanceOwner();
	if(fDist >= NTL_SUMMON_PET_RESET_POSITION_DIST*0.9f)
	{
		m_bCompulsoryAttack = FALSE;
		return FALSE;
	}

	if(m_bCompulsoryAttack)
	{
		CNtlSobActor *pTarActor = reinterpret_cast<CNtlSobActor*>( GetNtlSobManager()->GetSobObject(m_hBattleSerialId) );
		if(pTarActor == NULL)
		{
			m_bCompulsoryAttack = FALSE;
			return FALSE;
		}

		if(pTarActor->IsDie())
		{
			m_bCompulsoryAttack = FALSE;
			return FALSE;
		}
		
		return TRUE;
	}

	CNtlFSMCharActAgent *pCharActAgent = reinterpret_cast<CNtlFSMCharActAgent*>( m_pController->GetAgent() );
	if(!pCharActAgent->IsFightingMode())
		return FALSE;

	RwUInt32 uiStateId = GetActorStateId();
	if(uiStateId == NTL_FSMSID_IDLE)
		return FALSE;

	return TRUE;
}

RwBool CNtlSummonPetAI::IsPathCollision(RwV3d vStart, RwV3d vDir, RwReal fLen)
{
	RwLine line;
	line.start		= vStart;
	line.start.y	+= 0.5f;

	line.end.x		= vStart.x + vDir.x * fLen;
	line.end.y		= vStart.y + 0.5f;
	line.end.z		= vStart.z + vDir.z * fLen;
	
	SWorldPickInfo sPickInfo;

	sPickInfo.pPLEntity = NULL;
	sPickInfo.pAtomic = NULL;
	sPickInfo.fMinDist = RwRealMAXVAL;

	return Collision_WorldIntersectionObject(line, &sPickInfo);
}

RwV3d CNtlSummonPetAI::GetPathFinding(void)
{
#define PET_AI_PATHFIND_DIST	7.0f

	CNtlSobActor *pActor = GetActor();
	RwV3d vDir = pActor->GetDirection();

	RwMatrix mat;
	CNtlMath::MathRwMatrixAssign(&mat, &CNtlPLGlobal::m_vZeroV3, &vDir);

	RwV3dScale(&vDir, &vDir, -1.0f);

	RwV3d vPos = pActor->GetPosition();

	RwV3d vStart1, vStart2;
	RwV3dAssignMacro(&vStart1, &vPos);
	RwV3dAssignMacro(&vStart2, &vPos);
	
	vStart1.x += vDir.x * 0.5f;
	vStart1.z += vDir.z * 0.5f;

	vStart2.x += vDir.x * 1.5f;
	vStart2.z += vDir.z * 1.5f;

	RwV3d vLineDir, vSearchDestPos1, vSearchDestPos2;

	if(rand() % 2)
	{
		RwV3dAssignMacro(&vLineDir, &mat.right);

		vSearchDestPos1.x = vStart1.x + mat.right.x * PET_AI_PATHFIND_DIST;
		vSearchDestPos1.y = vStart1.y;
		vSearchDestPos1.z = vStart1.z + mat.right.z * PET_AI_PATHFIND_DIST;

		vSearchDestPos2.x = vStart1.x - mat.right.x * PET_AI_PATHFIND_DIST;
		vSearchDestPos2.y = vStart1.y;
		vSearchDestPos2.z = vStart1.z - mat.right.z * PET_AI_PATHFIND_DIST;
	}
	else
	{
		RwV3dScale(&vLineDir, &mat.right, -1.0f);

		vSearchDestPos1.x = vStart1.x - mat.right.x * PET_AI_PATHFIND_DIST;
		vSearchDestPos1.y = vStart1.y;
		vSearchDestPos1.z = vStart1.z - mat.right.z * PET_AI_PATHFIND_DIST;

		vSearchDestPos2.x = vStart1.x + mat.right.x * PET_AI_PATHFIND_DIST;
		vSearchDestPos2.y = vStart1.y;
		vSearchDestPos2.z = vStart1.z + mat.right.z * PET_AI_PATHFIND_DIST;
	}

	RwBool bCollision1 = IsPathCollision(vStart1, vLineDir, PET_AI_PATHFIND_DIST);
	RwBool bCollision2 = IsPathCollision(vStart2, vLineDir, PET_AI_PATHFIND_DIST);

	if(!bCollision1 && !bCollision2)
		return vSearchDestPos1;

	return vSearchDestPos2;
}

void CNtlSummonPetAI::EventGeneratorCollisionAvoid(void)
{
	CNtlSobActor *pActor = GetActor();
	CNtlBeCharData *pBeData = reinterpret_cast<CNtlBeCharData*>(pActor->GetBehaviorData()); 
	SMoveStuff *pMoveStuff = pBeData->GetMoveStuff();
	pMoveStuff->byMoveResult = 0;

	RwV3d vPos = pActor->GetPosition();
	RwV3d vDestPos = GetPathFinding();

	CNtlSLEventGenerator::SobDestMove(pActor->GetSerialID(), NTL_MOVEFORM_GROUND, vPos, vDestPos, 0);
	API_GetSLPacketGenerator()->SendMouseMove(vPos, vDestPos, pActor->GetServerSyncAvatarType());  
}

void CNtlSummonPetAI::EventGeneratorFollowState(void)
{
	CNtlSobActor *pActor = GetActor();
	RwReal fFollowRange = Logic_GetAttackRange(pActor, m_hBattleSerialId);

	RwV3d vPos = pActor->GetPosition();
	CNtlSLEventGenerator::SobFollowMove(GetActor()->GetSerialID(), pActor->GetOwnerID(), NTL_MOVE_FLAG_RUN, vPos, fFollowRange, DBO_MOVE_FOLLOW_FRIENDLY, 0);
}


void CNtlSummonPetAI::EventGeneratorAttackFollowState(void)
{
	CNtlSobActor *pActor = GetActor();
	RwReal fFollowRange = Logic_GetAttackRange(pActor, m_hBattleSerialId);

	CNtlFSMPlayerController *pPlayerController = reinterpret_cast<CNtlFSMPlayerController*>( m_pController );
	CNtlFSMSyncMsgAttackBegin *pSyncMsgAttackBegin = pPlayerController->GetFSMSyncMsgAttackBegin();
	pSyncMsgAttackBegin->SetTargetSerialId(m_hBattleSerialId);

	// Battle Mode
	m_bCompulsoryAttack = TRUE;

	RwV3d vPos = pActor->GetPosition();
	CNtlSLEventGenerator::SobFollowMove(GetActor()->GetSerialID(), m_hBattleSerialId, NTL_MOVE_FLAG_RUN, vPos, fFollowRange, DBO_MOVE_FOLLOW_AUTO_ATTACK, 0);
}


void CNtlSummonPetAI::UserCommandAttack(SERIAL_HANDLE hTargetSerialId)
{
	if(m_hBattleSerialId == hTargetSerialId)
		return;

	m_hBattleSerialId   = hTargetSerialId;

	ChangeState(ESPS_BATTLE, TRUE);
}

