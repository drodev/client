#pragma once

#include "NtlWorldConceptController.h"

/**
 * \ingroup NtlSimulation
 * \brief NPC �� ��ȭ�� �� �̿�
 * \date 2007-07-18
 * \author avooo
 */

class CNtlWorldConceptNPCCOMMU : public CNtlWorldConceptController
{
public:
	CNtlWorldConceptNPCCOMMU(void);
	~CNtlWorldConceptNPCCOMMU(void);

	virtual RwBool	IsEnableAction(EAvatarAction eAction);
	virtual void	ChangeState(RwInt32 iState);
};
