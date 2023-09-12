/*****************************************************************************
 *
 * File			: NtlStage.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 7. 14	
 * Abstract		: Stage.
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/


#ifndef __NTL_STAGE__
#define __NTL_STAGE__

#include "ceventhandler.h"
#include "NtlSysEvent.h"

/**
 * \ingroup Client
 * client ��� ��ü�� ���� ���� ���� ���� �׷��Ͽ� ������ ������ �ִ� base class�̴�.
 * MMORPG������ Login Stage, Lobby Stage, Character Create Stage, Character Select Stage, Game Stage��� ������ �� �ִ�.
 */

class CNtlStage 
{
private:

	std::string m_strName;
	
public:

	CNtlStage(const char *pStageName);
	virtual ~CNtlStage();

	// stage ��ü�� ������ ���� ��ٷ� ȣ��ȴ�. �̴� ���� ��ü���� ��ӹ޾� ������ ó���� �Ѵ�.
	virtual bool Create(void);

	// stage ��ü�� �����Ǳ� ���� ȣ��ȴ�. �̴� ���� ��ü���� ��ӹ޾� ������ ó���� �Ѵ�.
	virtual void Destroy(void);

	virtual void PostRender(void);

	// stage name�� ���´�.
	const char* GetName(void);
};


inline const char* CNtlStage::GetName(void)
{
	return m_strName.c_str();
}

#endif