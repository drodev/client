#include "precomp_ntlpresentation.h"
#include "NtlPLResourceScheduling.h"

// core
#include "NtlDebug.h"
#include "NtlCoreUtil.h"

// framework
#include "NtlTimer.h"

// presentation
#include "NtlPLDef.h"
#include "NtlPLEntity.h"
#include "NtlPLResourceManager.h"

// Performance Check ( Develop )
//#define USE_RESOURCE_SCHEDULING_PERFORMANCE_CHECK

#define MAX_LOAD_CHARACTER_SCHEDULING_TIME			4.0f
#define MAX_LOAD_OBJECT_SCHEDULING_TIME				3.0f

#define MAX_DELETE_SCHEDULING_TIME					0.1f

// �� �ð��� �ѱ�� rest time �� ��Ƣ�� �Ѵ�.
#define MAX_LOAD_CHARACTER_OVER_WEIGHT				0.07f
#define MAX_LOAD_OBJECT_OVER_WEIGHT					0.05f

#define DEFAULT_LOAD_OBJECT_REST_TIME					0.1f
#define DEFAULT_LOAD_CHARACTER_REST_TIME				0.3f

RwBool	g_bLoadSeamless				= FALSE;
RwReal	g_fLoadObjectTime			= 0.02f;
RwReal	g_fLoadObjectSeamlessTime	= 0.01f;
RwReal	g_fLoadCharacterSeamlessTime = 0.001f;

/**
* \brief Construction
*/
CNtlResourceScheduleUnit::CNtlResourceScheduleUnit()
{
	m_byEntityType			= 0;

	m_fLoadCurrTime			= 0.0f;
	m_fLoadSchedulingTime	= g_fLoadObjectTime;
}

/**
* \brief Destruction
*/
CNtlResourceScheduleUnit::~CNtlResourceScheduleUnit()
{
	// Delete Schedule�� �ִ� clump �� �����Ѵ�.
	CNtlPLResource *pResource;
	ListScheduling::iterator itDelete;
	for(itDelete = m_listClumpDeleteSchedule.begin(); itDelete != m_listClumpDeleteSchedule.end(); itDelete++)
	{
		pResource = (*itDelete);
		GetNtlResourceManager()->UnLoad(pResource);
	}
	m_listClumpDeleteSchedule.clear();

	// Load Schedule�� �ִ� clump ����Ʈ�� �����Ѵ�.
	MapScheduling::iterator it;
	for(it = m_mapClumpLoadSchedule.begin(); it != m_mapClumpLoadSchedule.end(); it++)
	{
		CNtlResourceScheduleManager::FreeListFree((void*)(*it).second);
	}
	m_mapClumpLoadSchedule.clear();
}

/**
* \brief Obejct ���� Clump���� �����층 �ε� ( ���� ���������� ���� ���߿� �ε��Ѵ�. )
* \param fElapsed	(RwReal) ���� ������Ʈ���� ��� �ð�
*/
void CNtlResourceScheduleUnit::UpdateObjectLoadScheduling(RwReal fElapsed)
{
	RwReal fSum = 0.0f;
	DWORD dwTime;
	
	SResourceScheduleNode *pNode;
	CNtlPLResource *pResource;
	CNtlPLEntity *pPLEntity;
	
	MapScheduling::iterator it;

#ifdef USE_RESOURCE_SCHEDULING_PERFORMANCE_CHECK
	DWORD dwCount = 0;
#endif
	
	// The map is rotated for a certain period of time and is loaded unconditionally. (Improving the loading speed of the data that was read.)
	for(it = m_mapClumpLoadSchedule.begin(); it != m_mapClumpLoadSchedule.end(); )
	{
		dwTime = GetTickCount();

		pNode = (*it).second;
		pPLEntity = (*it).first;
		if(pPLEntity)
			pPLEntity->CallPreSchedulingResource();

		pResource = GetNtlResourceManager()->LoadClump(pNode->chFileName, pNode->chResourcePath);

		if(pPLEntity)
		{	
			pPLEntity->CallSchedulingResource(pResource);
			pPLEntity->CallSchedulingResourceOnly();
		}

		it = m_mapClumpLoadSchedule.erase(it);
		CNtlResourceScheduleManager::FreeListFree((void*)pNode);

#ifdef USE_RESOURCE_SCHEDULING_PERFORMANCE_CHECK
		dwCount++;
#endif

		fSum += (RwReal)(GetTickCount() - dwTime)/1000.0f;
		if(fSum > g_fLoadObjectTime)
			break;
	}

#ifdef USE_RESOURCE_SCHEDULING_PERFORMANCE_CHECK
	RwReal fRealTime = fSum;
#endif
	
	if( fSum > MAX_LOAD_OBJECT_OVER_WEIGHT )
	{
		fSum *= 5.0f;
		if( fSum > MAX_LOAD_OBJECT_SCHEDULING_TIME )
			fSum = MAX_LOAD_OBJECT_SCHEDULING_TIME;
	}

	m_fLoadSchedulingTime = DEFAULT_LOAD_OBJECT_REST_TIME + fSum;

#ifdef USE_RESOURCE_SCHEDULING_PERFORMANCE_CHECK
	NtlLogFilePrintArgs( "[OBJECT] : %d loading for one tick, time is %3.3f sec and after rest time %3.3f sec", dwCount, fRealTime, m_fLoadSchedulingTime);
#endif
}

/**
* \brief Object ���� clump���� Seamless �ε� ( ���� ���� �ɸ��� ������ �ε� )
* \param fElapsed	(RwReal) ���� ������Ʈ���� ����� �ð�
*/
void CNtlResourceScheduleUnit::UpdateObjectLoadSeamlessScheduling(RwReal fElapsed)
{
	RwReal fSum = 0.0f;
	DWORD dwTime;
	
	SResourceScheduleNode *pNode;
	CNtlPLResource *pResource;
	CNtlPLEntity *pPLEntity;
	
	MapScheduling::iterator it;

#ifdef USE_RESOURCE_SCHEDULING_PERFORMANCE_CHECK
	DWORD dwCount = 0;
#endif
	
	for(it = m_mapClumpLoadSchedule.begin(); it != m_mapClumpLoadSchedule.end(); )
	{
		dwTime = GetTickCount();

		pNode = (*it).second;
		pPLEntity = (*it).first;
		if(pPLEntity)
			pPLEntity->CallPreSchedulingResource();

		pResource = GetNtlResourceManager()->LoadClump(pNode->chFileName, pNode->chResourcePath);

		if(pPLEntity)
		{	
			pPLEntity->CallSchedulingResource(pResource);
			pPLEntity->CallSchedulingResourceOnly();
		}

		it = m_mapClumpLoadSchedule.erase(it);
		CNtlResourceScheduleManager::FreeListFree((void*)pNode);

#ifdef USE_RESOURCE_SCHEDULING_PERFORMANCE_CHECK
		dwCount++;
#endif

		// �ʴ� 20 frm
		fSum += (RwReal)(GetTickCount() - dwTime)/1000.0f;
		if(fSum > g_fLoadObjectSeamlessTime)
			break;
	}

#ifdef USE_RESOURCE_SCHEDULING_PERFORMANCE_CHECK
	RwReal fRealtime = fSum;
#endif

	if( fSum > MAX_LOAD_OBJECT_OVER_WEIGHT )
	{
		fSum *= 5.0f;
		if( fSum > MAX_LOAD_OBJECT_SCHEDULING_TIME )
			fSum = MAX_LOAD_OBJECT_SCHEDULING_TIME;
	}

	m_fLoadSchedulingTime = DEFAULT_LOAD_OBJECT_REST_TIME + fSum;

#ifdef USE_RESOURCE_SCHEDULING_PERFORMANCE_CHECK
	NtlLogFilePrintArgs( "[OBJECTSEAMLESS] : %d loading for one tick, time is %3.3f sec and after rest time %3.3f sec", dwCount, fRealtime, m_fLoadSchedulingTime);
#endif
}

/**
* \brief �����층 ������Ʈ�� �ε��Ѵ�.
* \param fElapsed	(RwReal) ���� ������Ʈ���� ����� �ð�
*/
void CNtlResourceScheduleUnit::UpdateLoadScheduling(RwReal fElapsed)
{
	m_fLoadCurrTime += fElapsed;
	if(m_fLoadCurrTime <= m_fLoadSchedulingTime)
		return;

	m_fLoadCurrTime -= m_fLoadSchedulingTime;

	if(m_mapClumpLoadSchedule.empty())
		return;

	// ������Ʈ �� ������Ʈ �Ѵ�.
	UpdateObjectLoadScheduling(fElapsed);
}

/**
* \brief �ɸ��� ������� �����췯�� ������Ʈ �Ѵ�.
*/
void CNtlResourceScheduleUnit::UpdateLoadSeamlessScheduling(RwReal fElapsed)
{
	if(m_mapClumpLoadSchedule.empty())
		return;
	
	UpdateObjectLoadSeamlessScheduling(fElapsed);
}

/**
* \brief ������ ����� �����층�Ѵ�.
*/
void CNtlResourceScheduleUnit::UpdateDeleteScheduling(RwReal fElapsed)
{
	if(m_listClumpDeleteSchedule.empty())
		return;

	RwReal fSumTime = 0.0f;
	DWORD dwTime;
	RwReal fFps		= ( 1.0f / CNtlTimer::GetFps() ) * 0.1f;
	if(fFps > 0.1f)
		fFps = 0.1f;

	CNtlPLResource *pResource;
	ListScheduling::iterator it = m_listClumpDeleteSchedule.begin();

	dwTime = GetTickCount();
	
	while(1)
	{

		pResource = (*it);
		GetNtlResourceManager()->UnLoad(pResource);

		it = m_listClumpDeleteSchedule.erase(it);

		if(m_listClumpDeleteSchedule.empty())
		{
			break;
		}

		fSumTime = (GetTickCount() - dwTime)/1000.0f;

		if(fSumTime > fFps)
		{
			break;
		}
	}
}

/**
* \brief Unit�� �����층 �ε��� Entity�� Type�� ����
* \param byEntityType	(RwUInt8) ��ƼƼ�� Ÿ��
*/
void CNtlResourceScheduleUnit::SetEntityType(RwUInt8 byEntityType)
{
	m_byEntityType = byEntityType;
}

/**
* \brief
*/
void CNtlResourceScheduleUnit::Update(RwReal fElapsed)
{
	if(g_bLoadSeamless)
		UpdateLoadSeamlessScheduling(fElapsed);
	else
		UpdateLoadScheduling(fElapsed);

	UpdateDeleteScheduling(fElapsed);
}

void CNtlResourceScheduleUnit::AddSchedulingNode(CNtlPLEntity *pPLEntity, SResourceScheduleNode *pNode)
{
	m_mapClumpLoadSchedule[pPLEntity] = pNode;
}

void CNtlResourceScheduleUnit::UnLoadScheduling(CNtlPLEntity *pPLEntity, CNtlPLResource *pResource)
{
	if(pResource == NULL)
	{
		MapScheduling::iterator it = m_mapClumpLoadSchedule.find(pPLEntity);
		if(it != m_mapClumpLoadSchedule.end())
		{
			CNtlResourceScheduleManager::FreeListFree((void*)(*it).second);
			m_mapClumpLoadSchedule.erase(it);
		}
	}
	else
	{
		m_listClumpDeleteSchedule.push_back(pResource);
	}
}

RwBool CNtlResourceScheduleUnit::IsEmptyLoadScheduling(void)
{
	if(m_mapClumpLoadSchedule.empty())
		return TRUE;

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* \brief Construction
*/
CNtlResourceScheduleCharUnit::CNtlResourceScheduleCharUnit() 
{
}

/**
* \brief Destruction
*/
CNtlResourceScheduleCharUnit::~CNtlResourceScheduleCharUnit() 
{
	ListCharScheduling::iterator it;
	for(it = m_listCharClumpLoadSchedule.begin(); it != m_listCharClumpLoadSchedule.end(); it++)
	{
		CNtlResourceScheduleManager::FreeListFree((void*)(*it).pNode);
	}
	m_listCharClumpLoadSchedule.clear();
}

/**
* \brief Update
* \param fElapsed	(RwReal) ���� �����ӿ����� ������Ʈ Time
*/
void CNtlResourceScheduleCharUnit::Update( RwReal fElapsed ) 
{
	//UpdateCharacterLoadScheduling( fElapsed );
	UpdateCharacterLoadSeamlessScheduling( fElapsed );

	CNtlResourceScheduleUnit::UpdateDeleteScheduling( fElapsed );
}

/**
* \brief �����층 �ε��� Node�� ����Ѵ�.
* \param pPLEntity	(CNtlPLEntity*) Entity�� �ּ�
* \param pNode		(SResourceScheduleNode*) ResourceNode
*/
void CNtlResourceScheduleCharUnit::AddSchedulingNode(CNtlPLEntity *pPLEntity, SResourceScheduleNode *pNode ) 
{
	// ����Ʈ�� ��ϵ� ����ü
	SResourceScheduleCharUnit sCharUnit;
	sCharUnit.pPLEntity = pPLEntity;
	sCharUnit.pNode = pNode;

	// ����Ʈ�� �߰��Ѵ�.
	m_listCharClumpLoadSchedule.push_back( sCharUnit );
}

/**
* \brief �����층 �ε����� Node�� �����Ѵ�.
* \param pPLEntity	(CNtlPLEntity*) ������ Entity�� ������
* \param pResource	(CNtlPLResource*) ������ ���ҽ��� ������
*/
void CNtlResourceScheduleCharUnit::UnLoadScheduling( CNtlPLEntity *pPLEntity, CNtlPLResource *pResource ) 
{
	// pResource�� NULL�� ���´ٸ� ����Ʈ���� �����ؾ� �Ѵ�.
	// multimap���� �ڷᱸ���� �ٲ����
	if(pResource == NULL)
	{
		ListCharScheduling::iterator it = m_listCharClumpLoadSchedule.begin();
		while(it != m_listCharClumpLoadSchedule.end())
		{
			// ����Ʈ���� �˻��Ͽ� ����
			if( (*it).pPLEntity == pPLEntity )
			{
				CNtlResourceScheduleManager::FreeListFree((void*)(*it).pNode);
				m_listCharClumpLoadSchedule.erase(it);
				return;
			}
			else
			{
				it++;
			}
		}
	}
	else
	{
		// ������ ����Ʈ�� ����Ѵ�.
		m_listClumpDeleteSchedule.push_back(pResource);
	}
}

/**
* \brief �����층 �ε� �� ����Ʈ�� ����ִ°�?
* \returns ����ִ��� ����
*/
RwBool CNtlResourceScheduleCharUnit::IsEmptyLoadScheduling( void ) 
{
	if( m_listCharClumpLoadSchedule.empty() )
		return TRUE;

	return FALSE;
}

/**
* \brief ĳ������ �����층�� ��� �ִ� clump�� �ε��Ѵ�.
* \param fElapsed	(RwReal) ����ð�
*/
void CNtlResourceScheduleCharUnit::UpdateCharacterLoadScheduling(RwReal fElapsed)
{
	m_fLoadCurrTime += fElapsed;

	// ������ �ɷȴ� �ð���ŭ ������ �ʾҴٸ� �����Ѵ�.
	if(m_fLoadCurrTime <= m_fLoadSchedulingTime)
		return;

	m_fLoadCurrTime = 0.0f;

	// ���ٸ� ����
	if( IsEmptyLoadScheduling() )
		return;

	SResourceScheduleNode *pNode = NULL;
	CNtlPLResource *pResource = NULL;
	CNtlPLEntity *pPLEntity = NULL;

	ListCharScheduling::iterator it = m_listCharClumpLoadSchedule.begin(); 
		
	DWORD dwTime = GetTickCount();

	pPLEntity = (*it).pPLEntity;
	pNode = (*it).pNode;

	// Entity���� Resource�� �ε��ϱ� ���� �˷��ش�.
	if(pPLEntity)
		pPLEntity->CallPreSchedulingResource();

	// ���ҽ��� ������ �ͼ�
	pResource = GetNtlResourceManager()->LoadClump(pNode->chFileName, pNode->chResourcePath);

	// ���ҽ��� �ε�
	if(pPLEntity)
	{	
		pPLEntity->CallSchedulingResource(pResource);
		pPLEntity->CallSchedulingResourceOnly();
	}

	m_listCharClumpLoadSchedule.erase(it);
	// ���ҽ��� �ε����Ŀ��� �ݺ��ڸ� �����ش�.
	CNtlResourceScheduleManager::FreeListFree((void*)pNode);

	dwTime = GetTickCount() - dwTime;

	m_fLoadSchedulingTime = g_fCharScheduleTime;

}

/**
* \brief Cash �� �������� �ε� �ӵ��� ����Ű�� ���� ������Ʈ �Լ�
* \param fElapsed	(RwReal) ���� ������Ʈ���� ����� �ð�
*/
void CNtlResourceScheduleCharUnit::UpdateCharacterLoadSeamlessScheduling( RwReal fElapsed ) 
{
	m_fLoadCurrTime += fElapsed;

	// ������ �ɷȴ� �ð���ŭ ������ �ʾҴٸ� �����Ѵ�.
	if(m_fLoadCurrTime <= m_fLoadSchedulingTime)
		return;

	m_fLoadCurrTime = 0.0f;

	// ���ٸ� ����
	if( IsEmptyLoadScheduling() )
		return;

	DWORD dwTime = 0;
	RwReal fSum = 0.0f;

	SResourceScheduleNode *pNode = NULL;
	CNtlPLResource *pResource = NULL;
	CNtlPLEntity *pPLEntity = NULL;

	ListCharScheduling::iterator it;

#ifdef USE_RESOURCE_SCHEDULING_PERFORMANCE_CHECK
	DWORD dwCount = 0;
#endif

	for( it = m_listCharClumpLoadSchedule.begin(); it != m_listCharClumpLoadSchedule.end(); )
	{
		dwTime = GetTickCount();

		pPLEntity = (*it).pPLEntity;
		pNode = (*it).pNode;

		// Entity���� Resource�� �ε��ϱ� ���� �˷��ش�.
		if(pPLEntity)
			pPLEntity->CallPreSchedulingResource();

		// ���ҽ��� ������ �ͼ�
		pResource = GetNtlResourceManager()->LoadClump(pNode->chFileName, pNode->chResourcePath);

		// ���ҽ��� �ε�
		if(pPLEntity)
		{	
			pPLEntity->CallSchedulingResource(pResource);
			pPLEntity->CallSchedulingResourceOnly();
		}

		it = m_listCharClumpLoadSchedule.erase(it);
		CNtlResourceScheduleManager::FreeListFree((void*)pNode);

		dwTime = GetTickCount() - dwTime;

#ifdef USE_RESOURCE_SCHEDULING_PERFORMANCE_CHECK
		dwCount++;
#endif

		fSum += ((RwReal)dwTime/1000.0f);
		if( fSum > g_fLoadCharacterSeamlessTime )
			break;
	}

#ifdef USE_RESOURCE_SCHEDULING_PERFORMANCE_CHECK
	RwReal fRealTime = fSum;
#endif

	if( fSum > MAX_LOAD_CHARACTER_OVER_WEIGHT )
	{
		fSum *= 5.0f;
		if( fSum > MAX_LOAD_CHARACTER_SCHEDULING_TIME )
			fSum = MAX_LOAD_CHARACTER_SCHEDULING_TIME;
	}

	m_fLoadSchedulingTime = g_fCharScheduleTime + fSum;

#ifdef USE_RESOURCE_SCHEDULING_PERFORMANCE_CHECK
	NtlLogFilePrintArgs( "[CHARACTER] : %d loading for one tick, time is %3.3f sec and after rest time %3.3f sec", dwCount, fRealTime, m_fLoadSchedulingTime);
#endif
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

RwFreeList* CNtlResourceScheduleManager::m_pScheduleNodeFreeList = NULL;		/* scheduling node memory pool **/


RwBool CNtlResourceScheduleManager::AllocFreeList(void)
{
	NTL_FUNCTION("CNtlReourceScheduleManager::AllocFreeList");

	RwUInt32 iBlockSize = 500;
	m_pScheduleNodeFreeList = RwFreeListCreate(sizeof(SResourceScheduleNode), iBlockSize, 16, rwMEMHINTDUR_GLOBAL);
    RWS_ASSERT(m_pScheduleNodeFreeList, "CNtlReourceScheduleManager::AllocFreeList");

	NTL_RETURN(TRUE);
}

void CNtlResourceScheduleManager::DeAllocFreeList(void)
{
	NTL_FUNCTION("CNtlReourceScheduleManager::DeAllocFreeList");

	if (m_pScheduleNodeFreeList)
    {
        RwFreeListDestroy(m_pScheduleNodeFreeList);
        m_pScheduleNodeFreeList = 0;
    }

	NTL_RETURNVOID();
}

void CNtlResourceScheduleManager::FreeListFree(void *pData)
{
	RwFreeListFree(m_pScheduleNodeFreeList, pData);
}

CNtlResourceScheduleManager::~CNtlResourceScheduleManager()
{
	CNtlResourceScheduleUnit *pUnit;
	MapScheduleUnit::iterator it;

	for(it = m_mapUnit.begin(); it != m_mapUnit.end(); it++)
	{
		pUnit = (*it).second;
		NTL_DELETE(pUnit);
	}

	m_mapUnit.clear();
}

void CNtlResourceScheduleManager::Update(RwReal fElapsed)
{
	// Kell
	static RwBool bCz = FALSE;
	if (bCz)
	{
		return;
	}

	MapScheduleUnit::iterator it;
	for(it = m_mapUnit.begin(); it != m_mapUnit.end(); it++)
	{
		(*it).second->Update(fElapsed);
	}
}

CNtlResourceScheduleUnit* CNtlResourceScheduleManager::FindUnit(RwUInt8 byEntityType)
{
	MapScheduleUnit::iterator it = m_mapUnit.find(byEntityType);
	if(it == m_mapUnit.end())
		return NULL;

	return (*it).second;
}

void CNtlResourceScheduleManager::AddSchedulingClump(const char *pStrName, const char * pResourcePath, CNtlPLEntity *pEntity)
{
	SResourceScheduleNode *pNode = (SResourceScheduleNode*)RwFreeListAlloc(m_pScheduleNodeFreeList, rwMEMHINTDUR_GLOBAL);
	pNode->uiResType = rwID_CLUMP;
	strcpy_s(pNode->chResourcePath, pResourcePath);
	strcpy_s(pNode->chFileName, pStrName);

	RwUInt8 byEntityType = (RwUInt8)pEntity->GetClassType();

	// Ȯ�� by Kell
	// ĳ���Ϳ� �������� �ٸ� ����� �����층 �ε��� ����Ѵ�.
	CNtlResourceScheduleUnit *pUnit = FindUnit(byEntityType);
	if(pUnit == NULL)
	{
		if( byEntityType == PLENTITY_CHARACTER || byEntityType == PLENTITY_ITEM )
		{
			pUnit = NTL_NEW CNtlResourceScheduleCharUnit;
		}
		else
		{
			pUnit = NTL_NEW CNtlResourceScheduleUnit;
		}

		pUnit->SetEntityType(byEntityType);
		m_mapUnit[byEntityType] = pUnit;
	}

	pUnit->AddSchedulingNode(pEntity, pNode);
}

void CNtlResourceScheduleManager::UnLoadScheduling(CNtlPLEntity *pPLEntity, CNtlPLResource *pResource)
{
	if(pPLEntity == NULL)
		return;

	CNtlResourceScheduleUnit *pUnit = FindUnit((RwUInt8)pPLEntity->GetClassType());

	if(pUnit == NULL)
		return;

	pUnit->UnLoadScheduling(pPLEntity, pResource);
}

RwBool CNtlResourceScheduleManager::IsEmptyLoadScheduling(RwUInt8 byEntityType)
{
	CNtlResourceScheduleUnit *pUnit = FindUnit(byEntityType);
	if(pUnit == NULL)
		return TRUE;

	return pUnit->IsEmptyLoadScheduling();
}

RwBool GetLoadObjectSeamlessScheduling(void)
{
	return g_bLoadSeamless;
}

void SetLoadObjectSeamlessScheduling(RwBool bEnable)
{
	g_bLoadSeamless = bEnable;
}

void SetLoadObjectSchedulingOneTickTime(RwReal fTime)
{
	g_fLoadObjectTime = fTime;
}

void SetLoadObjectSeamlessSchedulingOneTickTime(RwReal fTime)
{
	g_fLoadObjectSeamlessTime = fTime;
}