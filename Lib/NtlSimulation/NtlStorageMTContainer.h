/*****************************************************************************
* File			: NtlStorageMTContainer.h
* Author		: HaeSung, Cho
* Copyright		: (��)NTL
* Date			: 2009. 2. 5	
* Abstract		: NtlStorage�� Key�� ���� �������� �����ϴ� ���� ���̺�
*****************************************************************************
* Desc			: 
*
* ���� MappingTable�� �����ϱ� ���ؼ��� NtlStorageDefine.h �� �ִ� Define���� �����ϰ�
* ���� Ŭ������ �ִ� �������̺� �����͸� ä���ش�. Table �迭�� ���� ������ �� �� ������ ����/������ �����
* ���� �ʴ´�. ���� ����ؾ��� KEY�� �ִٸ� ���ǵ� KEY�� �״�� ���ΰ� �׳� ������� �ʴ´�.
*
* Mapping Table�� static �迭�� �����Ǹ� ����� �߰� ����/������ �ؼ��� �ȵȴ�.
* ( Mapping table is composed of static array, and you should not insert/delete it from the midterm )
*****************************************************************************/

#ifndef __NTL_STORAGE_MT_CONTAINER_H__
#define __NTL_STORAGE_MT_CONTAINER_H__

#include "NtlStorageDefine.h"

#include <map>
#include <string>

#pragma once

class CNtlStorageMTContainer
{
public:
	CNtlStorageMTContainer(void);
	virtual ~CNtlStorageMTContainer(void);

	const SNtlStorageMappingTableData* GetMappingTable( unsigned int uiKey );

	bool					SortTable();
	bool					SetUnitCheckFunc( unsigned int uiKey, NtlStorageUnitCheckFunc funcApply);
	NtlStorageUnitCheckFunc		GetUnitCheckFunc( unsigned int uiKey );

	unsigned int				GetCount();
	eNTL_STORAGE_VARIABLE_TYPE	GetVariableType( unsigned int uiKey );
	eNTL_STORAGE_TYPE			GetStorageType( unsigned int uiKey );
	const char*					GetString( unsigned int uiKey );
	const char*					GetDefaultString( unsigned int uiKey );
	bool						GetDefaultBool( unsigned int uiKey );
	int							GetDefaultInt( unsigned int	uiKey );
	float						GetDefaultFloat( unsigned int uiKey );
	bool						GetKeyFromString( std::string& strKeyName, unsigned int& uiKey );

	static CNtlStorageMTContainer* GetInstance()
	{
		static CNtlStorageMTContainer instance;
		return &instance;
	}

protected:
	static SNtlStorageMappingTableData m_StorageMappingTable[];

	// Type ���� ��Ƽ�ʿ� �����͸� �����ϰ� �ִ´�.
	typedef std::multimap	<unsigned char, SNtlStorageMappingTableData*> SORTMMAP;
	SORTMMAP		m_mmapCategory;

	// KEY ID ������� MAP�� �����ϰ� �ִ´�.
	typedef std::map	<unsigned int, SNtlStorageMappingTableData* > TABLEMAP;
	TABLEMAP		m_mapTable;

	typedef std::map	<std::string, SNtlStorageMappingTableData* > STRINGMAP;
	STRINGMAP		m_mapString;


	bool			m_bSorted;			///< ���̺��� �����ؼ� ������ �ִ��� Ȯ��
	unsigned int	m_uiCount;			///< ���̺� ���� ����
};

static CNtlStorageMTContainer* GetNtlStorageMTContainer()
{
	return CNtlStorageMTContainer::GetInstance();
}

#endif