/*****************************************************************************
 *
 * File			: NtlPLEntityFactory.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 8. 11	
 * Abstract		: Presentation layer entity factory class
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/


#ifndef __NTL_PLENTITY_FACTORY_H__
#define __NTL_PLENTITY_FACTORY_H__

#include <rwcore.h>
#include <rpworld.h>
#include "NtlPLDef.h"
#include "NtlPLEntity.h"

/**
 * \ingroup NtlPresentation
 * entity ���� �� �Ҹ��� ����ϴ� factory class.
 * presentation�� ��� entity�� ���� �� �Ҹ��� factory ����� ����Ѵ�.
 *
 */

class CNtlPLEntityFactory
{
public:

	/**
	*  entity�� �����ϴ� �Լ�.
	*  \param pEntityName ������ entity name.
	*  \retrun ������ �����ϸ� entity pointer, �����ϸ� NULL�� �����Ѵ�.
	*  \see DeleteEntity
	*/
	static CNtlPLEntity* CreateEntity(ENtlPLEntityType eType, const SPLEntityCreateParam* _pParam);

	/**
	*  entity�� �Ҹ��ϴ� �Լ�.
	*  \param pEntity �Ҹ��� entity pointer.
	*  \see CreateEntity
	*/
	static void DeleteEntity(CNtlPLEntity *pEntity);
};


#endif
