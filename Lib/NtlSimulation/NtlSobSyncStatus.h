/*****************************************************************************
 *
 * File			: NtlSobSyncStatus.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 11. 16	
 * Abstract		: Simulation Status object
 *****************************************************************************
 * Desc         : �������� �����ִ� damage�� hp/mp/cp ä��� packet�� ����ȭ ó���� ����Ѵ�.
 *				  �������� ���� damage�� �����־, ���� animation ����ȭ�� ���Ͽ�, ���߿� ó���� �� �ִ�.
                  �̷� ��쿡 current hp�� �״�� actor�� �����Ѵٸ�, avatar gui hp bar�� �龦���� �̻���
				  ���δ�. �̷� ��쿡 animation ����ȭ damage �� hp/mp/cp ó���� �ϱ� ���Ͽ� �������.
 *****************************************************************************/

#ifndef __NTL_SOB_SYNC_STATUS_H__
#define __NTL_SOB_SYNC_STATUS_H__

#include "NtlSob.h"

class CNtlSobActor;

class CNtlSobSyncStatus : public CNtlSob
{
protected:

	RwBool m_bActive;
	RwBool m_bFinish;
	
	/**
	* ������
	*/
	CNtlSobSyncStatus();
	
public:

	/**
	* �Ҹ���
	*/
	virtual ~CNtlSobSyncStatus();

	virtual RwBool Create(void);

	virtual void Destroy(void);

	virtual RwBool IsFinish(void);

	virtual void Update(RwReal fElapsed);

	
public:

	void Active(void);

	virtual void EventGenerator(void) {}
};

inline void CNtlSobSyncStatus::Active(void)
{
	m_bActive = TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

class CNtlSobAttackSyncStatus : public CNtlSobSyncStatus
{
	DECLEAR_MEMORY_POOL(CNtlSobAttackSyncStatus, NTL_DEFAULT_MEMORY_POOL)

private:

	RwReal m_fActiveTime;
	RwReal m_fCurrTime;

public:

	CNtlSobAttackSyncStatus();
	virtual ~CNtlSobAttackSyncStatus();

	virtual void Destroy(void);

	virtual RwBool IsFinish(void);

	virtual void Update(RwReal fElapsed);

	void ActiveTime(RwReal fTime);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


class CNtlSobDieSyncStatus : public CNtlSobSyncStatus
{
	DECLEAR_MEMORY_POOL(CNtlSobDieSyncStatus, NTL_DEFAULT_MEMORY_POOL)

protected:

	RwReal m_fTime;

public:

	CNtlSobDieSyncStatus();
	virtual ~CNtlSobDieSyncStatus();

	virtual void Destroy(void);
	virtual void EventGenerator(void);
    virtual void Update(RwReal fElapsed);
};


#endif
