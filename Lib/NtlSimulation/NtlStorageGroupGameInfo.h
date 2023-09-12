/*****************************************************************************
* File			: NtlStorageGroupGameInfo.h
* Author		: HaeSung, Cho
* Copyright		: (��)NTL
* Date			: 2009. 2. 5	
* Abstract		: GameInfo �� ���� Unit��
*****************************************************************************
* Desc         : 
*
*****************************************************************************/

#ifndef __NTL_STORAGE_GROUP_GAMEINFO_H__
#define __NTL_STORAGE_GROUP_GAMEINFO_H__

#pragma once

#include "NtlStorageGroup.h"

class CNtlStorageGroupGameInfo : public CNtlStorageGroup
{
public:
	CNtlStorageGroupGameInfo(void);
	virtual ~CNtlStorageGroupGameInfo(void);

	virtual bool Create();
};

#endif//__NTL_STORAGE_GROUP_GAMEINFO_H__