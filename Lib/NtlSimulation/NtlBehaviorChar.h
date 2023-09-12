/*****************************************************************************
 *
 * File			: NtlBehaviorChar.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2006. 2. 9	
 * Abstract		: character behavior class
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __NTL_BEHAVIOR_CHAR_H__
#define __NTL_BEHAVIOR_CHAR_H__

#include "NtlBehaviorBase.h"
#include "NtlBehaviorData.h"
#include "NtlAnimEventData.h"

class CNtlSobProxySystemEffect;
class CNtlPLCharacter;
class CNtlSobVehicle;

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

class CNtlBehaviorCharSpawn : public CNtlBehaviorBase
{
	DECLEAR_MEMORY_POOL(CNtlBehaviorCharSpawn, NTL_DEFAULT_MEMORY_POOL)
	DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharSpawn)

private:

	enum ESpawnType
	{
		SPAWN_NORMAL,
		SPAWN_SPECIAL,
		SPAWN_TMQ_IN
	};

	RwUInt8	m_byType;
	RwBool	m_bEnterShow;    
	RwBool	m_bSpawnAnimExist;
	RwReal	m_fTime;    
    RwReal	m_fSpawnDelayTime;

	CNtlSobProxySystemEffect	*m_pVSEAlpha;

	void	SetSpawnType(void);
	
	void	SetNormalSpawnAnim(RwReal fSpawnTime);
	void	SetNormalSpawnVisualEffect(void);

	void	SetSpecialSpawnVisualEffect(void);

	void	EnterNormalSpawn(void);
	void	EnterSpecialSpawn(void);
	void	EnterTMQInSpawn(void);

	void	ExitNormalSpawn(void);
	void	ExitTMQInSpawn(void);

	void	UpdateNormalSpawn(RwReal fElapsed);
	void	UpdateTMQSpawn(RwReal fElapsed);
	
public:

	CNtlBehaviorCharSpawn(); 
	~CNtlBehaviorCharSpawn();

	virtual void		Enter(void);
	virtual void		Exit(void);
	virtual void		Update(RwReal fElapsed);
	virtual RwUInt32	HandleEvents(RWS::CMsg &pMsg);
};


///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

class CNtlBehaviorSmoothHeading : public CNtlBehaviorBase
{
	DECLEAR_MEMORY_POOL(CNtlBehaviorSmoothHeading, 1)
	DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorSmoothHeading)

private:

	RwReal m_fDeltaAngleY;
	RwReal m_fUpdateAngleY;

	bool	m_bSetAngleX;
	RwReal m_fDeltaAngleX;
	RwReal m_fUpdateAngleX;

	void SetAnim(RwReal fDeltaAngleY, RwReal fDeltaAngleX);

public:

	CNtlBehaviorSmoothHeading();
	~CNtlBehaviorSmoothHeading();

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Update(RwReal fElapsed);
	virtual void UpdateData(void);
};

///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// �Ϲ����� ����.

class CNtlBehaviorCharPushFollow;

class CNtlBehaviorCharNormalAttack : public CNtlBehaviorBase
{
	DECLEAR_MEMORY_POOL(CNtlBehaviorCharNormalAttack, NTL_DEFAULT_MEMORY_POOL)
	DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharNormalAttack)

protected:

#define NTL_MAX_HITGROUP	NTL_MAX_NUMBER_OF_SKILL_TARGET
#define NTL_MAX_HITNUM		16
	
	RwV3d			m_vPushDir;
	RwInt32			m_iHitGroupNum;
	RwInt32			m_iHitNum;
	RwUInt8			m_iHitIdx;
	SHitStuff		*m_ppHit[NTL_MAX_HITGROUP][NTL_MAX_HITNUM];
	RwReal			m_fHitTime[NTL_MAX_HITNUM];
	RwReal			m_fAnimTime;					/** attack animation ��ü �ð� */
	RwReal			m_fAnimSpeed;					/** attack animation speed */

	CNtlBehaviorCharPushFollow *m_pPushFollow;


protected:

	void				Init(void);
	void				Delete(void);
		
	void				SetTransform(const SAttackStuff *pAttackStuff);
	void				SetAnim(const SAttackStuff *pAttackStuff);
	void				SetAnimNoAttackStuff(void);
	void				CalcHitStuff(const SAttackStuff *pAttackStuff, RwInt8 byHitGroupIdx);
	RwUInt8				CalcPowerHitNum(void);
	SAttackDamageStuff	CalcDamage(SAttackDamageStuff sTotDamageStuff, RwUInt8 byTotHitNum, RwUInt8 byPowerHitNum, RwBool bPowerHit);

	void				CreatePushFollow(RwBool bOneStepFollow);
	void				DeletePushFollow(void);

	void				EventProcPhysicHit(SHitStuff *pHitStuff, RwUInt8 byHitIdx);
	void				EventProcProjectileHit(SHitStuff *pHitStuff, RwUInt8 byHitIdx);
	void				EventProcHit(RwBool bOneStepFollow);
	void				EventProcSkillAffectingCancel(void);

public:

	CNtlBehaviorCharNormalAttack();
	~CNtlBehaviorCharNormalAttack();

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Update(RwReal fElapsed);
	virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);
	virtual void UpdateData(void);
};





///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// �Ϲ����� ����.

class CNtlBehaviorCharPushFollow : public CNtlBehaviorBase
{
	DECLEAR_MEMORY_POOL(CNtlBehaviorCharPushFollow, NTL_DEFAULT_MEMORY_POOL)
	DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharPushFollow)

protected:

	RwReal m_fPushSpeed;
	RwReal m_fCurrDist;
	RwV3d m_vPushDir;

public:

	CNtlBehaviorCharPushFollow();
	~CNtlBehaviorCharPushFollow();

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Update(RwReal fElapsed);
	virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);
	
public:

	void SetPushSpeed(RwReal fPushSpeed);
	void SetPushDir(const RwV3d *pPushDir);
};

///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// 

class CNtlBehaviorCharPush : public CNtlBehaviorBase
{
	DECLEAR_MEMORY_POOL(CNtlBehaviorCharPush, NTL_DEFAULT_MEMORY_POOL)
	DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharPush)

public:
    CNtlBehaviorCharPush();
    ~CNtlBehaviorCharPush();

    virtual void Enter(void);
    virtual void Update(RwReal fElapsed);
    virtual void Exit(void);
    virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);
    virtual void UpdateData(void);

private:
    void CreateTimeSequence(void);          ///< push sequence node ���� �Լ�.
    void DeleteTimeSequence(void);          ///< push sequence node ���� �Լ�. 
    RwReal GetMaxTime(void) const;          ///< ��ü�� life time.
    RwReal GetMaxDist(void) const;          ///< �������� �ִ� �Ÿ�.
    void   UpdatePosition(RwReal fElapsed);                ///< ��ġ�� ������Ʈ�Ѵ�.

private:
	RwV3d m_vPushDir;		/** push ���� */
	RwReal m_fPrevDist;     /** �ð��� ���� distance�� ����ϹǷ�, ������ dist�� �����Ѵ�. */
	RwReal m_fTime;			/** push ���� time */
	RwReal m_fDistScale;    /** time sequence�� �ð��� �Ÿ��� ����, push �Ÿ��� ������ �ƴϹǷ� */
	RwV3d  m_vDestPos;		/** push�� ���Ͽ� ������ ���� ��ġ */

	CNtlDistTimeSequence *m_pSeq;	/** push sequence node */
};


///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// 

class CNtlBehaviorCharSliding : public CNtlBehaviorBase
{
	DECLEAR_MEMORY_POOL(CNtlBehaviorCharSliding, NTL_DEFAULT_MEMORY_POOL)
	DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharSliding)

private:

	enum 
	{
		SS_SLIDING_LADING,
		SS_SLIDING_STOP
	};
	
	RwUInt32 m_uiSlidingState;	/** sliding state */
	RwV3d m_vPushDir;			/** sliding ���� */
	RwReal m_fPrevDist;		    /** �ð��� ���� distance�� ����ϹǷ�, ������ dist�� �����Ѵ�. */
	RwReal m_fTime;				/** sliding ���� time */
	RwReal m_fDistScale;		/** time sequence�� �ð��� �Ÿ��� ����, sliding �Ÿ��� ������ �ƴϹǷ� */
	RwV3d  m_vDestPos;			/** sliding�� ���Ͽ� ������ ���� ��ġ */

	CNtlDistTimeSequence *m_pSeq;	/** sliding sequence node */

private:

	/**
	* sliding sequence node ���� �Լ�.
	*/
	void CreateTimeSequence(void);

	/**
	* sliding sequence node ���� �Լ�. 
	*/
	void DeleteTimeSequence(void);

	/**
	* ��ü�� life time.
	*/
	RwReal GetMaxTime(void) const;

	/**
	* �������� �ִ� �Ÿ�.
	*/
	RwReal GetMaxDist(void) const;

	/**
	* update sliding landing.
	*/
	void UpdateSlidingLanding(RwReal fElapsed);

	/**
	* update sliding stop.
	*/
	void UpdateSlidingStop(RwReal fElapsed);

	/**
	* sliding ��ǥ ���.
	*/
	void UpdatePosition(RwReal fTime);

	/**
	* sliding ���� �ٲٴ� �Լ�.
	*/
	void ChangeSlidingState(RwUInt32 uiState);

public:

	/**
	* ������
	*/
	CNtlBehaviorCharSliding();

	/**
	* �Ҹ���
	*/
	~CNtlBehaviorCharSliding();

	virtual void Enter(void);
	virtual void Update(RwReal fElapsed);
	virtual void Exit(void);
	virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);

	/**
	* ��ü�� CNtlBeCharData ��ü ������ �����Ͽ� ����ϱ� ������, sliding ��ü update�� ���.
	* ���� sliding behavior�� �������� ���¿���, �ٸ� sliding ����� �޾��� ��. ���� update.
	*/
	virtual void UpdateData(void);

public:

	void SetSlidingDir(const RwV3d *pSlidingDir);
};

///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// 

class CNtlBehaviorCharShock : public CNtlBehaviorBase
{
	DECLEAR_MEMORY_POOL(CNtlBehaviorCharShock, NTL_DEFAULT_MEMORY_POOL)
	DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharShock)

private:

	RwV3d m_vPushDir;		/** shock ���� */
	RwV3d m_vDestPos;		/** shock�� ���Ͽ� ������ ���� ��ġ */
	RwReal m_fTime;			/** shock ���� time */
	RwReal m_fDistScale;    /** time sequence�� �ð��� �Ÿ��� ����, shock �Ÿ��� ������ �ƴϹǷ� */
		
	CNtlDistTimeSequence *m_pSeq;

private:

	/**
	* hit shock sequence node ���� �Լ�.
	*/
	void CreateTimeSequence(void);

	/**
	* hit shock sequence node ���� �Լ�. 
	*/
	void DeleteTimeSequence(void);

	/**
	* hit shock ��ü data reset �Լ�.
	*/
	void ResetTimeSequence(void);

	/**
	* time sequence node update �Լ�.
	* param1 : �ٷ� ������ ���� �ð�.
	* param2 : ������ ���� �ð�.
	*/
	void UpdateTimeSequence(RwReal fOldTime, RwReal fCurrTime);

	/**
	* ��ü�� life time.
	*/
	RwReal GetMaxTime(void) const;

	/**
	* �������� �ִ� �Ÿ�.
	*/
	RwReal GetMaxDist(void) const;

public:

	/**
	* ������.
	*/
	CNtlBehaviorCharShock();

	/**
	* �Ҹ���.
	*/
	~CNtlBehaviorCharShock();

	virtual void Enter(void);
	virtual void Update(RwReal fElapsed);
	virtual void Exit(void);
	virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);

	/**
	* ��ü�� CNtlBeCharData ��ü ������ �����Ͽ� ����ϱ� ������, shock ��ü update�� ���.
	* ���� shock behavior�� �������� ���¿���, �ٸ� shock ����� �޾��� ��. ���� update.
	*/
	virtual void UpdateData(void);
};

///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//
class CNtlBehaviorCharKnockDown : public CNtlBehaviorBase
{
	DECLEAR_MEMORY_POOL(CNtlBehaviorCharKnockDown, NTL_DEFAULT_MEMORY_POOL)
	DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharKnockDown)

public:
	enum 
	{
		KD_FALLUP,
		KD_LANDING,
		KD_FALLDOWN,
		KD_KNOCK,
		KD_KNOCK_EXIT
	};

public:
    CNtlBehaviorCharKnockDown();
    ~CNtlBehaviorCharKnockDown();

    virtual void Enter(void);
    virtual void Update(RwReal fElapsed);
    virtual void Exit(void);
    virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);

    /**
    * ��ü�� CNtlBeCharData ��ü ������ �����Ͽ� ����ϱ� ������, knock down ��ü update�� ���.
    * ���� knock down behavior�� �������� ���¿���, �ٸ� knock down ����� �޾��� ��. ���� update.
    */
    virtual void UpdateData(void);
    void ChangeKnockDownState(RwUInt32 uiState);    ///< knockdown bahavior �� state�� ���̽�Ű�� �Լ�.
    void SetKnockDownDir(const RwV3d *pKnockDownDir);   ///< knock down direction.

private:
	void CreateFallupTimeSequence(void);    ///< knockdown fall up sequence node ���� �Լ�.
	void CreateLandingTimeSequence(void);   ///< knockdown landing sequence node ���� �Լ�.
	void DeleteTimeSequence(void);          ///< knockdown sequence node ���� �Լ�. 
	void UpdateFallUp(RwReal fElapsed);     ///< knockdown fall up update �Լ�.
	void UpdateLanding(RwReal fElapsed);    ///< knockdown landing update �Լ�.
	void UpdateFallDown(RwReal fElapsed);   ///< knockdown fall down update �Լ�.
	void UpdateKnock(RwReal fElapsed);      ///< knockdown�� ������ ���� �� update �Լ�.
	void CalcLanding(RwReal fElapsed);      ///< landing ���� ���.
    RwV3d UpdatePosition(RwReal fElapsed, RwV3d& vPos, RwReal fSpeed);   ///< y���� ������ ��ġ ��� (�浹 ó��)

protected:
    RwUInt32 m_uiKnockDownState;		/** knock down state */
    RwBool m_bStanding;					/** knock down standing */
    RwBool m_bFainting;					/** knock down fainting */

    RwReal m_fTime;						/** known down ���� time */
    RwV3d m_vKnockDownDir;				/** knock down ���� */
    RwV2d m_vPrevDist;					/** �ð��� ���� distance�� ����ϹǷ�, ������ dist�� �����Ѵ�. */
    RwV2d m_vFallDelta;					/** �������� delta dist */
    RwReal m_fDistScale;				/** time sequence�� �ð��� �Ÿ��� ����, push �Ÿ��� ������ �ƴϹǷ� */

    CNtl2DTimeSequence *m_pSeq;				/** knock down fall up sequence node */
    CNtlDistTimeSequence *m_pLandingSeq;	/** knock donw landing sequence node */
};


///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

class CNtlBehaviorCharHurt : public CNtlBehaviorBase
{
	DECLEAR_MEMORY_POOL(CNtlBehaviorCharHurt, NTL_DEFAULT_MEMORY_POOL)
	DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharHurt)

private:

	void SetAnim(SHitStuff *pHitStuff);
	void SetTrans(SHitStuff *pHitStuff);

public:

	CNtlBehaviorCharHurt();
	~CNtlBehaviorCharHurt();

	virtual void Enter(void);
	virtual void Update(RwReal fElapsed);
	virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);
	virtual void UpdateData(void);
};


///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

class CNtlBehaviorCharHurtTossUp : public CNtlBehaviorBase
{
	DECLEAR_MEMORY_POOL(CNtlBehaviorCharHurtTossUp, NTL_DEFAULT_MEMORY_POOL)
	DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharHurtTossUp)

protected:

	enum
	{
		TOSS_UP_UP,
		TOSS_UP_IDLE,
		TOSS_UP_DOWN,
	};

	RwUInt8 m_byTossUpState;
	CNtlDistTimeSequence *m_pSeq;		// time sequence
	RwReal m_fTime;
	RwReal m_fPrevDist;

private:

	/**
	* animation setting
	*/
	void SetAnim(void);

	/**
	* push sequence node ���� �Լ�.
	*/
	void CreateTimeSequence(void);

	/**
	* push sequence node ���� �Լ�. 
	*/
	void DeleteTimeSequence(void);

	/**
	* toss update up
	*/
	void UpdateUp(RwReal fElapsed);

	/**
	* toss update idle
	*/
	void UpdateIdle(RwReal fElapsed);

	/**
	* toss update down
	*/
	void UpdateDown(RwReal fElapsed);

public:

	CNtlBehaviorCharHurtTossUp();
	~CNtlBehaviorCharHurtTossUp();

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Update(RwReal fElapsed);
	virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);
	virtual void UpdateData(void);
};

///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

class CNtlBehaviorCharHurtTossDown : public CNtlBehaviorBase
{
	DECLEAR_MEMORY_POOL(CNtlBehaviorCharHurtTossDown, NTL_DEFAULT_MEMORY_POOL)
	DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharHurtTossDown)

protected:

	enum
	{
		TOSS_DOWN_DOWN,
		TOSS_DOWN_IDLE,
	};

	RwUInt8 m_byTossDownState;
	
private:

	/**
	* animation setting
	*/
	void SetAnim(void);

	/**
	* toss update up
	*/
	void UpdateDown(RwReal fElapsed);

	/**
	* toss update idle
	*/
	void UpdateIdle(RwReal fElapsed);

public:

	CNtlBehaviorCharHurtTossDown();
	~CNtlBehaviorCharHurtTossDown();

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Update(RwReal fElapsed);
	virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);
	virtual void UpdateData(void);
};

///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ���.(target�� ���󰣴�)

class CNtlBehaviorCharHomingUp : public CNtlBehaviorBase
{
	DECLEAR_MEMORY_POOL(CNtlBehaviorCharHomingUp, NTL_DEFAULT_MEMORY_POOL)
	DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharHomingUp)

private:

	RwUInt8 m_bySpeedSearch;
	RwV3d m_vOldTargetPos;

private:

	/**
	* animation setting
	*/
	void SetAnim(void);


public:

	CNtlBehaviorCharHomingUp();
	~CNtlBehaviorCharHomingUp();

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Update(RwReal fElapsed);
	virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);
	virtual void UpdateData(void);
};

///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// ���� �ϰ�.

class CNtlBehaviorCharHomingDown : public CNtlBehaviorBase
{
	DECLEAR_MEMORY_POOL(CNtlBehaviorCharHomingDown, NTL_DEFAULT_MEMORY_POOL)
	DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharHomingDown)

private:

	CNtlDistTimeSequence	*m_pSeq;		// time sequence
	RwReal					m_fTime;
	RwReal					m_fPrevDist;

	RwBool					m_bLandingEnd;
	RwBool					m_bLandingAnimPlay;

	RwBool					m_bHomingDown;

private:

	/**
	* animation setting
	*/
	void SetAnim(void);


	/**
	* push sequence node ���� �Լ�.
	*/
	void CreateTimeSequence(void);

	/**
	* push sequence node ���� �Լ�. 
	*/
	void DeleteTimeSequence(void);

	void UpdateHomingDown(RwReal fElapsed);

	void UpdateIdleDown(RwReal fElapsed);

public:

	CNtlBehaviorCharHomingDown();
	~CNtlBehaviorCharHomingDown();

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Update(RwReal fElapsed);
	virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);
	virtual void UpdateData(void);
};

///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ���(target�� ������ �ʰ�) ������ ���̸� jumping �Ѵ�.

class CNtlBehaviorCharJumpingUp : public CNtlBehaviorBase
{
	DECLEAR_MEMORY_POOL(CNtlBehaviorCharJumpingUp, NTL_DEFAULT_MEMORY_POOL)
	DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharJumpingUp)

private:

	CNtlDistTimeSequence *m_pSeq;		// time sequence
	RwReal m_fTime;
	RwReal m_fPrevDist;

private:

	/**
	* animation setting
	*/
	void SetAnim(void);

	/**
	* push sequence node ���� �Լ�.
	*/
	void CreateTimeSequence(void);

	/**
	* push sequence node ���� �Լ�. 
	*/
	void DeleteTimeSequence(void);


public:

	CNtlBehaviorCharJumpingUp();
	~CNtlBehaviorCharJumpingUp();

	virtual void Enter(void);
	virtual void Exit(void);
	virtual void Update(RwReal fElapsed);
	virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);
	virtual void UpdateData(void);
};
//////////////////////////////////////////////////////////////////////////

/**
 * \ingroup NtlSimulation
 * \brief ����ũ�� ���ſ� ��ų. Ÿ���� �������.
 *
 * \date 2008-10-17
 * \author agebreak
 */
class CNtlBehaviorCharStretchAttack : public CNtlBehaviorBase
{
    DECLEAR_MEMORY_POOL(CNtlBehaviorCharStretchAttack, NTL_DEFAULT_MEMORY_POOL)
    DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharStretchAttack)

public:
    CNtlBehaviorCharStretchAttack();
    ~CNtlBehaviorCharStretchAttack();

    virtual void Enter(void);
    virtual void Exit(void);
    virtual void Update(RwReal fElapsed);
    virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);
    virtual void UpdateData(void);

protected:
    RwReal  GetTargetDistance(CNtlSobActor* pTargetActor);              ///< ��ܿ��� Ÿ�ٰ��� �Ÿ��� ����Ѵ� (Radius�� ��)

protected:
    CNtlPLCharacter*    m_pCharacter;           ///< ������� ��ƼƼ ��ü    
    RwUInt32            m_uiTargetId;           ///< Ÿ�� �ø��� ID
    RwV3d               m_vTargetPos;           ///< ó�� �̺�Ʈ�� �߻��������� Ÿ�� ��ġ
    RwBool              m_bPulling;             ///< ���� �������� ���»������� �÷��� (FALSE ���»���, TRUE ��ܿ��� ����)    
    SEventStretch*      m_pStretchEvent;         ///< �̺�Ʈ ����ü
    RwReal              m_fStretchPullingSpeed;  ///< ���� Ǯ�� ���ǵ�
    RwMatrix            m_matDir;                ///< ��� ���� ��Ʈ����

    RwBool              m_bOrgBoneScale;        ///< ������ �� ������ �÷���
    RwReal              m_fOrgBoneLength[3];    ///< ������ �� ����
    RwReal              m_fOrgBoneWidth[3];     ///< ������ �� �β�
};
//////////////////////////////////////////////////////////////////////////
/**
 * \ingroup NtlSimulation
 * \brief ����� ��ڷ� �����ؼ� �����ϴ� ��ų (������)
 *
 * \date 2008-11-20
 * \author agebreak
 */
class CNtlBehaviorCharActiveWarpBackAttack : public CNtlBehaviorBase
{
    DECLEAR_MEMORY_POOL(CNtlBehaviorCharActiveWarpBackAttack, NTL_DEFAULT_MEMORY_POOL)
    DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharActiveWarpBackAttack)

public:
    CNtlBehaviorCharActiveWarpBackAttack();
    ~CNtlBehaviorCharActiveWarpBackAttack();

    virtual void Enter(void);
    virtual void Exit(void);
    virtual void Update(RwReal fElapsed);
    virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);    

	void	SetFinalLoc(RwV3d& loc);

protected:

    void    OnWarpBack();                       ///< ������ �ڷ� �����Ѵ�.

protected:

	RwV3d		m_vFinalLoc;
};

//////////////////////////////////////////////////////////////////////////

/**
 * \ingroup NtlSimulation
 * \brief ������ �ٰŸ� ���� ���� ��ų (Ÿ���� ��ó�� �̵�)
 *
 * \date 2008-11-21
 * \author agebreak
 */
class CNtlBehaviorCharActiveWarp : public CNtlBehaviorBase
{
    DECLEAR_MEMORY_POOL(CNtlBehaviorCharActiveWarp, NTL_DEFAULT_MEMORY_POOL)
    DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharActiveWarp)

public:
    CNtlBehaviorCharActiveWarp();
    ~CNtlBehaviorCharActiveWarp();
    
    virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);    

	void	SetFinalLoc(RwV3d& loc);

protected:

    void    OnWarpTarget();                 ///< Ÿ���� ������ �����Ѵ�.

protected:

	RwV3d		m_vFinalLoc;
};

//////////////////////////////////////////////////////////////////////////

#define SKILL_THROUGH_SPEED 15.0f;
#define SKILL_THROUGH_PAST_POS 10.0f;

/**
 * \ingroup NtlSimulation
 * \brief ���� ����(�ϼ� ��Ÿ��) ��ų
 *
 * \date 2008-11-21
 * \author agebreak
 */
class CNtlBehaviorCharActiveThroughAttack : public CNtlBehaviorBase
{
    DECLEAR_MEMORY_POOL(CNtlBehaviorCharActiveThroughAttack, NTL_DEFAULT_MEMORY_POOL)
    DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharActiveThroughAttack)

public:

    CNtlBehaviorCharActiveThroughAttack();
    ~CNtlBehaviorCharActiveThroughAttack();

    virtual void Enter(void);
    virtual void Update(RwReal fElapsed);
    virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);    

	void	SetFinalLoc(RwV3d& loc);

protected:

	void    OnThroughAttack();																		 ///< 
    void    CalcHitDamage();                                                                    ///< Show damage to the right target

protected:

	RwV3d		m_vFinalLoc;
};

class CNtlBehaviorCharActivePull : public CNtlBehaviorBase
{
	DECLEAR_MEMORY_POOL(CNtlBehaviorCharActivePull, NTL_DEFAULT_MEMORY_POOL)
		DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharActivePull)

public:

	CNtlBehaviorCharActivePull();
	~CNtlBehaviorCharActivePull();

	virtual void Enter(void);
	virtual void Update(RwReal fElapsed);
	virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);

	void	SetFinalLoc(RwV3d& loc);

protected:

	void    OnPull();	///< 

protected:

	RwV3d		m_vFinalLoc;
};

/**
 * \ingroup NtlSimulation
 * \brief ���� ���� ��ų�� ����Ҷ� ���Ǵ� Ŭ���� (�� ����)
 *
 * \date 2009-01-16
 * \author agebreak
 */
class CNtlBehaviorCharTransform : public CNtlBehaviorBase
{
    DECLEAR_MEMORY_POOL(CNtlBehaviorCharTransform, NTL_DEFAULT_MEMORY_POOL)
    DECLEAR_BEHAVIOR_FACTROY(CNtlBehaviorCharTransform)

public:
    CNtlBehaviorCharTransform();
    ~CNtlBehaviorCharTransform();

    virtual void Enter(void);
    virtual void Update(RwReal fElapsed);
    virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);   

    void    SetAnimation(RwUInt32 uiAction, RwUInt32 uiActionLoop);       ///< �ִϸ��̼��� �����Ѵ�.
protected:

protected:
    RwUInt32    m_uiAnimAction;
    RwUInt32    m_uiAnimLoop;
};


#endif
