/*****************************************************************************
* File			: NtlStorageGroupCharacter.h
* Author		: HaeSung, Cho
* Copyright		: (��)NTL
* Date			: 2009. 8. 16	
* Abstract		: ĳ���� ���� ���� �� �ִ� �ɼǵ�
*****************************************************************************
* Desc         : 
*
*****************************************************************************/

#ifndef __NTL_STORAGE_GROUP_CHARACTER_H__
#define __NTL_STORAGE_GROUP_CHARACTER_H__

#pragma once

#include "NtlStorageGroup.h"

class CNtlStorageGroupCharacter : public CNtlStorageGroup
{
public:
	CNtlStorageGroupCharacter(void);
	virtual ~CNtlStorageGroupCharacter(void);

	virtual bool Create();
};

#endif//__NTL_STORAGE_GROUP_CHARACTER_H__