#pragma once

#include "NtlBehaviorCharMove.h"

/**
 * \ingroup NtlSimulation
 * \brief �̵��� �����Ŀ� ���� ��ġ�� �°� ��ġ ������ ó���ϴ� �ൿ Ŭ����
 *
 * \date 2009-04-15
 * \author agebreak
 */
class CNtlBehaviorCharGroundAdjustMove : public CNtlBehaviorBase
{
    DECLEAR_MEMORY_POOL(CNtlBehaviorCharGroundAdjustMove, NTL_DEFAULT_MEMORY_POOL)
    DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharGroundAdjustMove)

public:

    CNtlBehaviorCharGroundAdjustMove();
    ~CNtlBehaviorCharGroundAdjustMove();

    virtual void Enter(void);
    virtual void Exit(void);
    virtual void Update(RwReal fElapsed);
    virtual void UpdateData(void);
    virtual void SetAnim();

protected:    
    RwBool  IsNotAdjustMove();                  ///< Adjust Move�� ���� �ʴ� �������� üũ�Ѵ�.

protected:
    SMoveStuff			m_MoveStuff;
    SWorldHeightStuff	m_sHStuff;				/** world height stuff */
    RwBool				m_bSlidingAdjust;
    RwV3d				m_vAdjustDir;
};
