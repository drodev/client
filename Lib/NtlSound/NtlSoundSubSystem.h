/*****************************************************************************
* File			: NtlSoundManaager.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2009. 1. 16	
* Abstract		: 
*****************************************************************************
* Desc			: ���� ���� �ý��� �����̳�
*****************************************************************************/

#pragma once

class CNtlSoundEventHandler;


class CNtlSoundSubSystem
{
public:
	CNtlSoundSubSystem();
	virtual ~CNtlSoundSubSystem();

	RwBool	Create();
	void	Destroy();

protected:
	CNtlSoundEventHandler*	m_pSoundEventHandler;
};