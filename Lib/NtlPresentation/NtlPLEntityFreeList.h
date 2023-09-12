/*****************************************************************************
 *
 * File			: NtlPLEntityFreeList.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 8. 11	
 * Abstract		: Presentation layer entity free list
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __NTL_PLENTITY_FREELIST_H__
#define __NTL_PLENTITY_FREELIST_H__

#include <rwcore.h>
#include <rpworld.h>
#include "NtlPLDef.h"

/**
 * \ingroup NtlPresentation
 * memory ����ȭ�� �����ϱ� ���� entity memory pool class.
 * renderware�� free list�� ����Ѵ�.
 *
 */

class CNtlPLEntityFreeList
{
private:

	static RwFreeList *m_pObjFreeList;			/* object memory pool **/
	static RwFreeList *m_pCharFreeList;			/* character memory pool **/
	// by agebreak
	static RwFreeList *m_pEffectFreeList;		/* effect memory pool **/
	// woody1019
	static RwFreeList *m_pWorldFreeList;
	static RwFreeList *m_pSoundFreeList;
	static RwFreeList *m_pSoundBGMFreeList;
	// jhssugi
	static RwFreeList *m_pDummyWorldFreeList;	/** dummy world free list */
	// by hodong
	static RwFreeList *m_pItemFreeList;
    static RwFreeList *m_pPlayerNameFreeList;
	static RwFreeList *m_pDamageBoxFreeList;
	static RwFreeList *m_pDecalFreeList;
	static RwFreeList *m_pSunFreeList;			// Sun free list by agebreak
	static RwFreeList *m_pPlanetFreeList;		// Sun free list ������ Planet freelist �߰�
public:

	/**
	*  entity free list ��ü�� initialize��Ű�� �Լ�.
	*  \see Destroy
	*/
	static RwBool AllocFreeList(void);

	/**
	*  entity free list ��ü�� terminate��Ű�� �Լ�.
	*  \see Destroy
	*/
	static void DeAllocFreeList(void);

	/**
	*  free list memory�� �Ҵ��Ѵ�.
	*  \param eType entity type
	*  \return �����ϸ� ��û�� free list memory , �����ϸ� NULL
	*  \see Free
	*/
	static void* Alloc(const ENtlPLEntityType eType);

	/**
	*  free list memory�� �����Ѵ�.
	*  \param eType entity type
	*  \param pObj ������ free list memory.
	*  \see Alloc
	*/
	static void Free(const ENtlPLEntityType eType, void *pObj);
};

#endif
