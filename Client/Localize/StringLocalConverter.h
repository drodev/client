/******************************************************************************
* File			: StringLocalConverter.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2008. 12. 19
* Abstract		: 
*****************************************************************************
* Desc			: ��, ������ ��Ȳ�� ���� �ܾ� Ȥ�� ������ ������ �Ѵ�.
*				  ��) �ѱ����� ��/��, ��/�� ���..
*
*				  �Ϻ���� ���� ����� ����.
*****************************************************************************/

#pragma once

class CStringLocalConverter_LocalBase;

class CStringLocalConverter
{
public:
	#define dSTRING_CONVERTER_BUFFER_SIZE		1024

	static CStringLocalConverter* GetInstance();
	static RwBool	CreateInstance();
	static void		DestroyInstance();

	enum eLocalType
	{
		LOCAL_TYPE_KOREA,

		INVALID_LOCAL_TYPE
	};

	typedef std::map<RwUInt8, CStringLocalConverter_LocalBase*>		MAP_LOCAL_CONVERTER;

public:
	CStringLocalConverter() {}
	virtual ~CStringLocalConverter() {}

	///< �� ��Ȳ�� ���� ����� ��Ʈ���� ��ȯ�Ѵ�
	const WCHAR*	LocalStringCovert(const WCHAR* pwcText);

protected:
	static CStringLocalConverter* m_pInstance;

	WCHAR						m_awcBuffer[dSTRING_CONVERTER_BUFFER_SIZE];
	MAP_LOCAL_CONVERTER			m_mapLocalConverter;
};

static CStringLocalConverter* GetStringConverter()
{
	return CStringLocalConverter::GetInstance();
}