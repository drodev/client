/******************************************************************************
* File			: StringLocalConverter_Korean.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2008. 12. 19
* Abstract		: 
*****************************************************************************
* Desc			: �ѱ���� �� ���� ������ ���� ������ �Ǵ� ���簡 5���� �ִ�
*
*				  �� ) ��/��, ��/��, ��/��, ��/��, 
*					   ������ ���ų� �� ������ '��'�̸� ��/����
*****************************************************************************/

#ifndef __GUI_STRING_LOCAL_CONVERTER_KOREAN_H__
#define __GUI_STRING_LOCAL_CONVERTER_KOREAN_H__

#include "StringLocalConverter_LocalBase.h"


START_GUI

class CStringLocalConverter_Korean : public CStringLocalConverter_LocalBase
{
public:
	virtual void	LocalStringCovert(WCHAR* pwcOutput, const WCHAR* pwcText);

protected:
	///< �����ڵ� �ѱ� ������ ���� �������� ��ȯ�Ѵ�
	RwInt32			GetKoreanThirdSound(const WCHAR* pwcText);
};

END_GUI

#endif // __GUI_STRING_LOCAL_CONVERTER_KOREAN_H__