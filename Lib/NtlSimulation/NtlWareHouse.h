/*****************************************************************************
*
* File			: NtlWareHouse.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 11. 20	
* Abstract		: Simulation Warehouse class
*****************************************************************************
* Desc         : 
*
*****************************************************************************/

#ifndef __NTL_WARE_HOUSE_H__
#define __NTL_WARE_HOUSE_H__

#include "NtlItem.h"
#include "ceventhandler.h"
#include "NtlSLDef.h"

class CNtlSobItem;
struct SNtlEventSobItemAdd;

class CNtlWarehouse : public RWS::CEventHandler
{
public:
	CNtlWarehouse();
	virtual ~CNtlWarehouse();

	void			Destroy(void);

	SERIAL_HANDLE	GetSlotSerailID(RwUInt8 bySlot);		///< �ش� ������ �ڵ��� ��ȯ�Ѵ�
	RwUInt8			FindWarehouseSlot(SERIAL_HANDLE hSerial);///< ���ڷ� ���� �ڵ��� ������ �ִ� ������ ã�´�
	RwUInt32		GetZenny();								///< â����� ���ϸ� ��ȯ�Ѵ�

	RwBool			IsHaveCommonWarehouse();				///< ���� â�� ������ �ִ��� �˾ƺ���	
	RwBool			IsRecieveData_from_Server();			///< ������ ���� â�� �����͸� ��� �޾Ҵ��� ����

	virtual	void	HandleEvents(RWS::CMsg &pMsg);

protected:	
	CNtlSobItem* CreateItem(void *pParentSobItem, sITEM_PROFILE* pSobItemCreate);
	CNtlSobItem* CreateItem(void *pParentSobItem, SNtlEventSobItemAdd *pSobItemAdd);

	void CreateEventHandler(RWS::CMsg &pMsg);
	void AddEventHandler(RWS::CMsg &pMsg);
	void DeleteEventHandler(RWS::CMsg &pMsg);
	void ItemMoveEventHandler(RWS::CMsg &pMsg);
	void ItemStackMoveEventHandler(RWS::CMsg &msg);

protected:
	SERIAL_HANDLE	m_hWareHouseSlot[NTL_MAX_BANKSLOT_COUNT];///< â�� ����
	RwUInt32		m_uiZenny;								///< ����

	RwBool			m_bHaveCommonWarehouse;					///< ����â�� ��������
	RwBool			m_bRecieveData_from_Server;				///< ������ ���� â�� �����͸� ��� �޾Ҵ��� ����
};

#endif