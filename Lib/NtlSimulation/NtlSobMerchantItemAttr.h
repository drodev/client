/*****************************************************************************
*
* File			: NtlSobMerchantItem.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 8. 1
* Abstract		: Simulation Merchant Item object attribute
*****************************************************************************
* Desc         : 
*
*****************************************************************************/


#ifndef __NTL_SOB_MERCHANT_ITEM_ATTR_H__
#define __NTL_SOB_MERCHANT_ITEM_ATTR_H__

#include "NtlSobAttr.h"

class CNtlSobMerchantAttr : public CNtlSobAttr
{
	DECLEAR_MEMORY_POOL(CNtlSobMerchantAttr, NTL_DEFAULT_MEMORY_POOL)

public:

	sMERCHANT_TBLDAT	*m_pMerchantTbl;		/** Merchant Item table data pointer */

public:

	CNtlSobMerchantAttr();
	virtual ~CNtlSobMerchantAttr();

	virtual RwBool Create(void) { SetClassID(SLCLASS_NPC); return TRUE; }

	virtual void Destroy(void) {}

	virtual void HandleEvents(RWS::CMsg &pMsg);

public:

	sMERCHANT_TBLDAT* GetMerchantTbl(void) const;

	const WCHAR*	GetTabName(void) const;		///< ��ǰ���� �з���( ex : �Ǻ�, ���� ....)
};

#endif
