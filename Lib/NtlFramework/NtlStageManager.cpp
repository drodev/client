#include "precomp_ntlframework.h"
#include "NtlStageManager.h"
#include "NtlStage.h"
#include "NtlDebug.h"
#include "NtlProfiler.h"

/**
*
*  Default constructor for CNtlStageManager
*
*/
CNtlStageManager::CNtlStageManager()
{
}

/**
*
*  Destructor for CNtlStageManager
*
*/
CNtlStageManager::~CNtlStageManager()
{
}


/**
*
*  \param pStageName�� stage name�̴�.
*
*  \return stage name�� �ش��ϴ� stage�� pointer�� �����Ѵ�. ������ NULL.
*/
CNtlStage* CNtlStageManager::FindActiveStage(const char *pStageName)
{
	NTL_FUNCTION("CNtlStageManager::FindActiveStage" );

	CNtlStage *pStage = NULL;
	std::list<CNtlStage*>::iterator it;

	for(it = m_listStage.begin(); it != m_listStage.end(); it++)
	{
		const char *pName = (*it)->GetName();
		if(pName == NULL || strcmp(pName, pStageName) != 0)
			continue;

		pStage = (*it);
		m_listStage.erase(it);

		break;
	}

	NTL_RETURN(pStage);
}

RwBool CNtlStageManager::ExistStage(const char *pStageName)
{
	NTL_FUNCTION("CNtlStageManager::ExistStage" );

	CNtlStage *pStage = NULL;
	std::list<CNtlStage*>::iterator it;

	for(it = m_listStage.begin(); it != m_listStage.end(); it++)
	{
		const char *pName = (*it)->GetName();
		if(pName == NULL || strcmp(pName, pStageName) != 0)
			continue;

		NTL_RETURN(TRUE);
	}

	NTL_RETURN(FALSE);
}

CNtlStage* CNtlStageManager::GetActiveStage(void)
{
	std::list<CNtlStage*>::iterator it = m_listStage.begin();
	if(it == m_listStage.end())
		return NULL;

	return (*it);
}


/**
*  stage�� destroy ��Ų��.
*  \param pStage�� destroy��ų stage pointer�̴�.
*/
void CNtlStageManager::DeleteStage(CNtlStage *pStage)
{
	NTL_FUNCTION("CNtlStageManager::DeleteStage" );

	if(pStage)
	{
		pStage->Destroy();
		NTL_DELETE(pStage);
	}

	NTL_RETURNVOID();
}

/**
*  �� �Լ��� stage manager�� instance�� ������ ���� ��ٷ� ȣ���Ѵ�.
*  �� �Լ��� ����� stage manager�� ó���� event�� ����Ѵ�.
*  event���� stage create �� stage delete event�� �����Ѵ�.
*/

bool CNtlStageManager::Create(void)
{
	NTL_FUNCTION("CNtlStageManager::Create" );

	RegisterMsg (g_EventCreateStage, "g_EventCreateStageStr", "SNtlEventStageData");
	RegisterMsg (g_EventDeleteStage, "g_EventDeleteStageStr", "SNtlEventStageData");

	LinkMsg(g_EventCreateStage, 0);
	LinkMsg(g_EventDeleteStage, 0);

	NTL_RETURN(true);
}

/**
*  �� �Լ��� stage manager ��ü�� �����ϱ� ���� ȣ���Ѵ�.
*  ���⿡�� ��ϵ� event�� ��� �����Ѵ�.
*  �����ϰ� �ִ� active stage�� ��� �����Ѵ�.
*/

void CNtlStageManager::Destroy(void)
{
	NTL_FUNCTION("CNtlStageManager::Destroy" );

	UnLinkMsg(g_EventCreateStage);
	UnLinkMsg(g_EventDeleteStage);

	UnRegisterMsg ( g_EventCreateStage );
	UnRegisterMsg ( g_EventDeleteStage );

	std::list<CNtlStage*>::reverse_iterator it;

	for(it = m_listStage.rbegin(); it != m_listStage.rend(); it++)
	{
		DeleteStage(*it);
	}

	m_listStage.clear();

	NTL_RETURNVOID();
}


void CNtlStageManager::PostRender(void)
{
	NTL_SPROFILE("CNtlStageManager::PostRender")

	std::list<CNtlStage*>::reverse_iterator it;

	for(it = m_listStage.rbegin(); it != m_listStage.rend(); it++)
	{
		(*it)->PostRender();
	}

	NTL_EPROFILE()
}


/**
*  Event Handler �Լ�.
*  \param pMsg�� event message�̸�, message�ȿ� event id�� data ������ ���ԵǾ� �ִ�.
*/

void CNtlStageManager::HandleEvents(RWS::CMsg &pMsg)
{
	NTL_FUNCTION("CNtlStageManager::HandleEvents");

	if(pMsg.Id == g_EventCreateStage)
	{
		SNtlEventStageData *pEventData = static_cast<SNtlEventStageData*>(pMsg.pData);
		CNtlStage *pNewStage = CreateStage(pEventData->chStageName); 
		if(pNewStage->Create()) 
			m_listStage.push_back(pNewStage); 
	}

	else if(pMsg.Id == g_EventDeleteStage)
	{
		SNtlEventStageData *pEventData = static_cast<SNtlEventStageData*>(pMsg.pData);
		DeleteStage(FindActiveStage(pEventData->chStageName)); 
	}

	NTL_RETURNVOID();
}