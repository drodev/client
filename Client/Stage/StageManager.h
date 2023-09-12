/*****************************************************************************
 *
 * File			: NtlStageManager.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 7. 15	
 * Abstract		: DBO Stage Manager.
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __STAGE_MANAGER__
#define __STAGE_MANAGER__

#include "NtlStageManager.h"


/**
 * \ingroup Client
 * DBO���� ���Ǵ� Stage Manager ��ü�̸�, CNtlStageManager class�� ��ӹ޴´�.
 * ���⿡�� ���� ���� stage�� �����ϴ� �κ��� �����Ѵ�.
 * 
 */
class CStageManager : public CNtlStageManager
{
private:

	static CStageManager *m_pInstance;

protected:

	/**
	* 
    *  \return stage name�� �ش��ϴ� stage�� �����Ͽ� �����Ѵ�. 
	*/
	virtual CNtlStage* CreateStage(const char *pStageName);
	
public:

	CStageManager();
	virtual ~CStageManager();

	static CStageManager* GetInstance(void);

	virtual bool Create(void);
	virtual void Destroy(void);
};

#endif

