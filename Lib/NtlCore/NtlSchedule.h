#pragma once

class CScheduler;
class CScheduleElement;

enum ESCHEDULE_STEP
{
	ESCHEDULE_STEP_NONE,
	ESCHEDULE_STEP_BEGIN,
	ESCHEDULE_STEP_SCHEDULING,
	ESCHEDULE_STEP_END,
};

class CScheduler
{
public:
	typedef std::list<CScheduleElement*>	LIST_ELE;
	typedef LIST_ELE::iterator				LIST_ELE_IT;

protected:
	LIST_ELE			m_listScheduleElement;
	RwReal				m_fElapsedTime;

public:
	CScheduler();
	virtual ~CScheduler();

	virtual RwBool				Scheduling(RwReal fElapsedTime);
	virtual RwBool				SchedulingProcess();
	virtual void				RemovePresentSchedule();

	virtual void				AddSchedule(CScheduleElement* pNewScheduleElement);
	virtual void				RemoveSchedule(RwInt32 iPrimaryKey);
	virtual void				ClearSchedule();

	virtual CScheduleElement*	GetFirstScedule();
};

class CScheduleElement
{
protected:
	RwInt32			m_iPrimaryKey;
	RwReal			m_fUsedTime;
	ESCHEDULE_STEP	m_eScheduleStep;


public:
	CScheduleElement(RwInt32 iPrimaryKey, RwReal fUsedTime);
	virtual ~CScheduleElement();

	virtual RwInt32			GetPrimaryKey()		{ return m_iPrimaryKey; }
	virtual RwReal			GetUsedTime()		{ return m_fUsedTime; }
	virtual ESCHEDULE_STEP	GetScheduleStep()	{ return m_eScheduleStep; }

	// �����층 �غ�.
	// RETURN : TRUE(�غ񼺰�)
	//			FALSE(�غ����) - Scheduler�� List���� ���� �ȴ�.
	virtual RwBool	Begin() = 0;

	// �����층�� ����.
	// RETURN : TRUE(������ �ٽ� �ѹ� ȣ���� �䱸�Ҷ�)
	//          FALSE(�����층 �� ���� ���� ��쳪 �����층�� ���� ���)
	virtual RwBool	Scheduling() = 0;

	// �����층�� ����.
	// RETURN : �����층�� ������ ���� ȣ��ȴ�. RETURN�� �ǹ̴� ����.
	//          ȣ��� �� Scheduler�� List���� ���� �ȴ�.  
	virtual RwBool	End() = 0;

	friend class CScheduler;
};