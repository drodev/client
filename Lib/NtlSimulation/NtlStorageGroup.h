/*****************************************************************************
* File			: NtlStorageGroup.h
* Author		: HaeSung, Cho
* Copyright	: (��)NTL
* Date			: 2009. 2. 5	
* Abstract		: Ntl Storage Group base
*****************************************************************************
* Desc          : Unit���� Group���� ������ StorageGroup�� Base class
* ���� NtlStorageGroup�� ��� �޴� Ŭ������ Ư���� �۵��� Load/Save �� ����Ϸ���
* �Ѵٸ� Load�� Save�� ¦�� ���缭 �ۼ������ �Ѵ�.
*
* [Category]
* Key = Value;
*
* ������ �����͸� ����Ϸ��� �Ѵٸ� Base�� Load/Save �Լ��� �״�� ����ص� �������.
*****************************************************************************/

#if !defined(_CNTLSTORAGEGROUP_H)
#define _CNTLSTORAGEGROUP_H

#include "NtlStorageDefine.h"
#include "NtlStorageUnit.h"
#include "NtlStorageSerializer.h"

#include <map>
#include <sstream>

class CNtlStorageGroup
{
public:
	CNtlStorageGroup();
	virtual ~CNtlStorageGroup();

	virtual bool Create();
	virtual void Destroy();

	virtual bool Load(CNtlStorageSerializer* pS);
	virtual bool Save(CNtlStorageSerializer* pS);
	virtual bool Reset();
	
	// Set
	bool SetData(unsigned int uiKey, int nData);
	bool SetData(unsigned int uiKey, float fData);
	bool SetData(unsigned int uiKey, std::string strData);
	bool SetData(unsigned int uiKey, const char* acData);
	bool SetData(unsigned int uiKey, bool bData);

	// Get
	bool GetIntData(unsigned int uiKey, int& nData);
	bool GetStringData(unsigned int uiKey, std::string& strData);
	bool GetBoolData(unsigned int uiKey, bool& bData);
	bool GetFloatData(unsigned int uiKey, float& fData);

	int			GetIntData(unsigned int uiKey);
	std::string GetStringData(unsigned int uiKey);
	bool		GetBoolData(unsigned int uiKey);
	float		GetFloatData(unsigned int uiKey);

	void		UnitCheck();

	void					SetStorageGroupType(eNTL_STORAGE_GROUP_TYPE eType);
	eNTL_STORAGE_GROUP_TYPE	GetStorageGroupType();

	bool					IsHave( eNTL_STORAGE_TYPE eType );
	CNtlStorageUnit*		GetStorageUnit( eNTL_STORAGE_TYPE eType );

	bool					SetUnitApplyFunc( NtlStorageUnitApplyFunc func );

protected:
	eNTL_STORAGE_GROUP_TYPE						m_eGroupType;

	typedef std::map<eNTL_STORAGE_TYPE, CNtlStorageUnit*>		UNITMAP;
	UNITMAP	m_mapStorageUnit;
};

#endif  //_CNTLSTORAGEGROUP_H
