#pragma once

#include "NtlWorldConceptController.h"

/**
 * \ingroup NtlSimulation
 * \brief ���λ��� �̿� �Ҷ��� ���� Ŭ���� (����� �ƹ��͵� �������� �ʴ´�)
 * \date 2007-07-11
 * \author Cz
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CNtlWorldConceptPrivateShop : �Ǹ���
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CNtlWorldConceptPrivateShop : public CNtlWorldConceptController
{
	RwUInt32 m_uiPrivateShopState; // ePRIVATESHOP_STATE
public:
	CNtlWorldConceptPrivateShop(void);
	~CNtlWorldConceptPrivateShop(void);

	virtual RwBool		IsEnableAction(EAvatarAction eAction);
	
	virtual RwUInt32	GetPrivateShopState();
	virtual void		SetPrivateShopState(RwUInt32 uiPrivateShopState);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CNtlWorldConceptPrivateShopVisitor : ������
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CNtlWorldConceptPrivateShopVisitor : public CNtlWorldConceptController
{
public:
	CNtlWorldConceptPrivateShopVisitor(void);
	~CNtlWorldConceptPrivateShopVisitor(void);

	virtual void	ChangeState(RwInt32 iState);				
	virtual RwBool	IsEnableAction(EAvatarAction eAction);
};
