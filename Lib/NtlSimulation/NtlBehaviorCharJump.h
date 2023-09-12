#pragma once

#include "NtlBehaviorCharMove.h"

/**
 * \ingroup NtlSimulation
 * \brief ĳ������ ���� ���¿����� ���� Ŭ����
 *
 * \date 2009-04-17
 * \author agebreak
 */
class CNtlBehaviorCharJump : public CNtlBehaviorCharMove
{
    DECLEAR_MEMORY_POOL(CNtlBehaviorCharJump, NTL_DEFAULT_MEMORY_POOL)
    DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharJump)

public:

    CNtlBehaviorCharJump();
    ~CNtlBehaviorCharJump();

    virtual void Enter(void);
    virtual void Exit(void);
    virtual void Update(RwReal fElapsed);    
    virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);

private:
    SWorldHeightStuff	m_sHStuff;				/** world height stuff */

    RwReal              m_fSyncSendTime;
    RwUInt8				m_byJumpState;	        /** jump state */
    RwReal				m_fJumpTime;		    /** jump time */
    RwReal				m_fJumpUpSpeed;	        /** ���� jump �ϴ�  speed */
    RwUInt8				m_byCollMoveImpossCnt;  /** collision move impossible count */
    RwBool				m_bRandingVisualEffect;	/** landing visual effect�� ǥ�� �Ͽ��°�? */
    RwBool				m_bStandRandingEnd;
    RwBool              m_bCreateBubbleEffect;  /** ��ǰ ����Ʈ�� ǥ���Ͽ��°�? */
    RwBool              m_bNoneDirJump;         ///< ���ڸ� ���� ����
    CNtlInstanceEffect* m_pWaterBubbleEffect;   /** �������� �������� ������ ��ǰ ����Ʈ */

    void UpdatePositionMove(SMoveStuff *pMoveStuff, SJumpStuff *pJumpStuff, OUT RwV3d& vPos, RwBool bIncHeight, RwReal fElapsed, RwReal fSpeedScale = 1.0f);

    void UpdateJumpStart(SMoveStuff *pMoveStuff, SJumpStuff *pJumpStuff, RwReal fElapsed);
    void UpdateJumpLoop(SMoveStuff *pMoveStuff, SJumpStuff *pJumpStuff, RwReal fElapsed);
    void UpdateJumpStandLanding(SMoveStuff *pMoveStuff, SJumpStuff *pJumpStuff, RwReal fElapsed);
    void UpdateJumpMoveLanding(SMoveStuff *pMoveStuff, SJumpStuff *pJumpStuff, RwReal fElapsed);
    void UpdateJumpWaterLanding(SMoveStuff *pMoveStuff, SJumpStuff *pJumpStuff, RwReal fElapsed);
    void UpdateSendSyncCheck(RwReal fElapsedTime);
    RwBool UpdateMoveSync(RwV3d vPos, RwReal fElapsedTime);       ///< Udpate function to calculate the current MoveSync value

    void ChangeJumpState(RwUInt8 byJumpState);
};
