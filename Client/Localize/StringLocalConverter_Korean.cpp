#include "precomp_dboclient.h"
#include "StringLocalConverter_Korean.h"

// core
#include "NtlDebug.h"

namespace
{
	#define dUNICODE_HANGULE_SYLLABLES_FIRST			(44032)
};


void CStringLocalConverter_Korean::LocalStringCovert(WCHAR* pwcOutput, const WCHAR* pwcText)
{
	RwInt32 iCount = 0;
	RwInt32 iTextLength = wcslen(pwcText);

	// ���簡 �������� �ּ��� 2���� �̻��̿��� �Ѵ�
	if( iTextLength < 2 )
	{
		memcpy(pwcOutput, pwcText, sizeof(WCHAR) * wcslen(pwcText) );
		return;
	}

	memcpy(pwcOutput, &(pwcText[0]), sizeof(WCHAR));
	++iCount;

	while( iCount < iTextLength )
	{
		if( wcscmp( L"��", &(pwcText[iCount]) ) == 0 )
		{
			int iThirdSound = GetKoreanThirdSound( &(pwcText[iCount - 1]) );

			if( iThirdSound == 0 )	// ��ħ�� ����
				memcpy(pwcOutput + iCount, L"��", sizeof(WCHAR));
			else
				memcpy(pwcOutput + iCount, L"��", sizeof(WCHAR));

			++iCount;
			continue;
		}
		else if( wcscmp( L"��", &(pwcText[iCount]) ) == 0 )
		{
			int iThirdSound = GetKoreanThirdSound( &(pwcText[iCount - 1]) );

			if( iThirdSound == 0 )	// ��ħ�� ����
				memcpy(pwcOutput + iCount, L"��", sizeof(WCHAR));
			else
				memcpy(pwcOutput + iCount, L"��", sizeof(WCHAR));

			++iCount;
			continue;
		}
		else if( wcscmp( L"��", &(pwcText[iCount]) ) == 0 )
		{
			int iThirdSound = GetKoreanThirdSound( &(pwcText[iCount - 1]) );

			if( iThirdSound == 0 )	// ��ħ�� ����
				memcpy(pwcOutput + iCount, L"��", sizeof(WCHAR));
			else
				memcpy(pwcOutput + iCount, L"��", sizeof(WCHAR));

			++iCount;
			continue;
		}
		else if( wcscmp( L"��", &(pwcText[iCount]) ) == 0 )
		{
			int iThirdSound = GetKoreanThirdSound( &(pwcText[iCount - 1]) );

			if( iThirdSound == 0 )	// ��ħ�� ����
				memcpy(pwcOutput + iCount, L"��", sizeof(WCHAR));
			else
				memcpy(pwcOutput + iCount, L"��", sizeof(WCHAR));

			++iCount;
			continue;
		}
		else if( wcscmp( L"��", &(pwcText[iCount]) ) == 0 )
		{
			int iThirdSound = GetKoreanThirdSound( &(pwcText[iCount - 1]) );

			if( iThirdSound == 0 && iThirdSound == 8 )	// ��ħ�� ���ų� '��' �̴�
			{
				memcpy(pwcOutput + iCount, L"��", sizeof(WCHAR));
				++iCount;
			}
			else
			{
				memcpy(pwcOutput + iCount, L"����", sizeof(WCHAR) * 2);
				iCount += 2;
			}

			continue;
		}

		memcpy(pwcOutput + iCount, &(pwcText[iCount]), sizeof(WCHAR));
		++iCount;
	}

	return;
}

RwInt32 CStringLocalConverter_Korean::GetKoreanThirdSound(const WCHAR* pwcText)
{
	if( !pwcText )
		return 0;

	int iIndex_from_HangulFirst = pwcText[0] - dUNICODE_HANGULE_SYLLABLES_FIRST;

	// �����ڵ�� �ѱ� ������ ���� �˻�
	if( iIndex_from_HangulFirst < 0 || iIndex_from_HangulFirst >= 11172 )
		return 0;

	//int iFirstSound	= iIndex_from_HangulFirst / (21*28);				///< �ʼ� ������
	//int iSecondSound	= iIndex_from_HangulFirst % (21*28) / 28;			///< �߼� ������
	int iThirdSound		= iIndex_from_HangulFirst % (21*28) % 28;			///< ���� ������

	return iThirdSound;
}