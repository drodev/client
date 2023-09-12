// Precompile
#include "precomp_ntlsimulation.h"
#include "NtlStorageGroup.h"

// Storage
#include "NtlStorageMTContainer.h"
#include "NtlStorageTextSerializer.h"
#include "NtlStorageBinarySerializer.h"

//
#include "NtlTokenizer.h"

#include "NtlDebug.h"

CNtlStorageGroup::CNtlStorageGroup()
{

}

CNtlStorageGroup::~CNtlStorageGroup()
{

}

bool CNtlStorageGroup::Create()
{
	return true;
}

void CNtlStorageGroup::Destroy()
{
	for each( std::pair< eNTL_STORAGE_TYPE, CNtlStorageUnit* > pair in m_mapStorageUnit )
	{
		if( pair.second )
		{
			pair.second->Destroy();

			NTL_DELETE( pair.second );
		}
	}

	m_mapStorageUnit.clear();
}

/**
* \brief NtlStorageGroup�� �������� Base load �Լ�
* Ư���� �ε��� �ؾ� �ϴ� Group�� ���� ���� �� Class�� ��ӹ޴�
* �ڽ� Ŭ�������� �������̵��ؼ� ����� �Ѵ�.
* \param pS		(CNtlStorageSerializer*) Load�� ���� Serializer buffer
* \return ��������
*/
bool CNtlStorageGroup::Load(CNtlStorageSerializer* pS)
{
	if( eNTL_STORAGE_SERIALIZER_TEXT == pS->GetStorageSerializerType() )
	{
		CNtlTokenizer lexer( pS->GetData() );
		if( !lexer.IsSuccess() )
			return false;

		// Text Parser

		// [ī�װ�]
		// [KEY] = [VALUE];
		
		eNTL_STORAGE_TYPE eCurrentType = eNTL_STORAGE_INVALID;
		
		enum eTextState
		{
			eTEXT_KEY = 0,
			eTEXT_EQUAL,
			eTEXT_VALUE,
			eTEXT_SEMICOLON
		};

		eTextState eState = eTEXT_KEY;
		std::string strKey, strValue;
		for(;;)
		{
			std::string& token = lexer.PeekNextToken();

			// ���� ��ū�� ī�װ����� Ȯ���ϰ� ī�װ��̸� ���� ���� Ű -> = -> �� -> ; ���� �����͸� Ȯ���Ѵ�.
			for( int i=0; i < eNTL_STORAGE_NUMS; ++i )
			{
				if( token.compare( g_acNtlStorageTypeString[i] ) == 0 )
				{
					eState = eTEXT_KEY;
					eCurrentType = (eNTL_STORAGE_TYPE)i;
					token = lexer.PeekNextToken();
					break;
				}
			}

			if( token.empty() )
				break;

			switch( eState )
			{
			case eTEXT_KEY:
				{
					if( token == "=" ||
						token == ";" )
					{
						return false;
					}
					else
					{
						strKey = token;
						eState = eTEXT_EQUAL;
					}
				}
				break;
			case eTEXT_EQUAL:
				{
					if( token != "=" )
					{
						return false;
					}
					else
					{
						eState = eTEXT_VALUE;
					}
				}
				break;
			case eTEXT_VALUE:
				{
					if( token == "=" ||
						token == ";" )
					{
						return false;
					}
					else
					{
						strValue = token;
						eState = eTEXT_SEMICOLON;
					}
				}
				break;
			case eTEXT_SEMICOLON:
				{
					if( token != ";" )
					{
						return false;
					}
					else
					{
						// eTEXT_SEMICOLON �� Ȯ�εǸ� �����ϰ� �ִ� Key�� Value�� ������ Current Type�� �´�
						// Unit�� �־��ش�. ���� eCurrentType�� ������ Group�� ���Ե��� ���� Unit�̶��
						// ������ �߻��ϰ� return �Ѵ�. �׷��� �Ǹ� ������� ������ Key Value�� �����ϰ� �̿���
						// �׸���� �� Default�� ���� �ְ� �ȴ�.
						UNITMAP::iterator it = m_mapStorageUnit.find( eCurrentType );
						if( it == m_mapStorageUnit.end() )
							return false;

						// ���� ���� KEY���� MappingTable�� �������� �ʴ� ���, ������ ����������������. �׷��� �Ǹ� �߸���
						// KEY���� �׸� ������ ���� �ʰ� �������� ���������� ó���Ѵ�.
						unsigned int uiKey = 0;
						if( !GetNtlStorageMTContainer()->GetKeyFromString( strKey, uiKey ) )
						{
							eState = eTEXT_KEY;
							continue;
						}
						else
						{
							(*it).second->SetData( uiKey, strValue );
						}

						eState = eTEXT_KEY;
					}
				}
				break;
			default:
				break;
			}
		}

		return true;
	}
	else if( eNTL_STORAGE_SERIALIZER_BINARY == pS->GetStorageSerializerType() )
	{
		// Binary�� ������ �˸��� Ű�� �����;���.
		/*CNtlStorageBinarySerializer* pBianrySerializer = (CNtlStorageBinarySerializer*)pS;*/

		unsigned int uiKey;
		eNTL_STORAGE_TYPE eCurrentType = eNTL_STORAGE_INVALID;

		int nCount = 0;
		RwBool bLoaded = FALSE;
		while(!bLoaded)
		{
			// ���ѷ��� ����
			if( ++nCount > 1000000 )
				break;

			if( pS->IsEmpty() )
				break;

			(*pS) >> uiKey;
			switch( uiKey )
			{
				// Case By Case
			case dSTORAGE_CATEGORY:
				{
					// ī�װ��� �˸��� ������ �����.
					std::string strCategory;
					(*pS) >> strCategory;

					// ��� ī�װ����� Ȯ��
					eNTL_STORAGE_TYPE eType = eNTL_STORAGE_INVALID;;
					for( int i=0; i < (int)eNTL_STORAGE_NUMS; ++i )
					{
						if( strCategory.compare( g_acNtlStorageTypeString[i] ) == 0 )
						{
							eType = (eNTL_STORAGE_TYPE)i;

							break;
						}
					}

					if( eType == eNTL_STORAGE_INVALID )
					{
						// ���ǵǾ� �ִ� ī�װ��� ã�� �������� ����Ÿ�� �߸��� ���̴�.
						return false;
					}

					// If it does not, overwrite it if you are making it.
					UNITMAP::iterator it = m_mapStorageUnit.find( eType );
					if( it == m_mapStorageUnit.end() )
					{
						CNtlStorageUnit* pUnit = NTL_NEW CNtlStorageUnit();
						if( !pUnit->Create( eType ) )
						{
							return false;
						}
					}

					eCurrentType = eType;					
				}
				break;
			case dSTORAGE_EOF:
				{
					// ���������� �ε��� �Ϸ�
					bLoaded = TRUE;
				}
				break;
			default:
				{
					// ī�װ��� �ƴ� ���� ��� �� uiKey�� ���� ����Ÿ�̴�.
					// ���� Ŀ��Ʈ Ÿ���� �����ͼ�
					UNITMAP::iterator it = m_mapStorageUnit.find( eCurrentType );
					if( it == m_mapStorageUnit.end() )
					{
						return false;
					}

					std::string strData;
					(*pS) >> strData;
					(*it).second->SetData( uiKey, strData );
				}
				break;

			}
		}

		// ByNarySerializer�� �ٽ� Data�� �־��� �ʿ䰡 ����.
		/*for each( std::pair< eNTL_STORAGE_TYPE, CNtlStorageUnit* > pair in m_mapStorageUnit )
		{
			if( pair.second )
			{
				(*pBianrySerializer) << (unsigned int)dSTORAGE_CATEGORY;
				(*pBianrySerializer) << (std::string) g_acNtlStorageTypeString[pair.second->GetType()];

				for each( std::pair< unsigned int, std::string > pairValue in pair.second->m_mapStorageData )
				{
					(*pBianrySerializer) << (std::string)GetNtlStorageMTContainer()->GetString( pairValue.first );
					(*pBianrySerializer) << (std::string)pairValue.second;
				}			
			}
		}
		*/

		return true;
	}

	return false;
}

/**
* \brief NtlStorageGroup�� �������� Base save �Լ�
* Ư���� ������ �ؾ� �ϴ� Group�� ���� ���� �� Class�� ��ӹ޴�
* �ڽ� Ŭ�������� �������̵��ؼ� ����� �Ѵ�.
* \param pS		(CNtlStorageSerializer*) save�� ���� Serializer buffer
* \return ��������
*/
bool CNtlStorageGroup::Save(CNtlStorageSerializer* pS)
{
	// Storage
	if( eNTL_STORAGE_SERIALIZER_TEXT == pS->GetStorageSerializerType() )
	{
		//CNtlStorageTextSerializer pSerializer = (CNtlStorageTextSerializer)s;

		CNtlStorageTextSerializer* pTextSerializer = (CNtlStorageTextSerializer*)pS;

		for each( std::pair< eNTL_STORAGE_TYPE, CNtlStorageUnit* > pair in m_mapStorageUnit )
		{
			(*pTextSerializer) << g_acNtlStorageTypeString[pair.second->GetType()];
			(*pTextSerializer) << "\n";

			if( pair.second )
			{
				for each( std::pair< unsigned int, std::string > pairValue in pair.second->m_mapStorageData )
				{
					(*pTextSerializer) << (std::string)GetNtlStorageMTContainer()->GetString( pairValue.first );
					(*pTextSerializer) << " = ";
					(*pTextSerializer) << (std::string)pairValue.second;	// Data ( std::string )
					(*pTextSerializer) << ";\n";
				}			
			}

			(*pTextSerializer) << "\0";
		}

		return true;
	}
	else if( eNTL_STORAGE_SERIALIZER_BINARY == pS->GetStorageSerializerType() )
	{
		CNtlStorageBinarySerializer* pBianrySerializer = (CNtlStorageBinarySerializer*)pS;

		for each( std::pair< eNTL_STORAGE_TYPE, CNtlStorageUnit* > pair in m_mapStorageUnit )
		{
			if( pair.second )
			{
				(*pBianrySerializer) << (unsigned int)dSTORAGE_CATEGORY;
				(*pBianrySerializer) << (std::string) g_acNtlStorageTypeString[pair.second->GetType()];

				for each( std::pair< unsigned int, std::string > pairValue in pair.second->m_mapStorageData )
				{
					(*pBianrySerializer) << (unsigned int)pairValue.first;
					(*pBianrySerializer) << (std::string)pairValue.second;
				}			
			}
		}

		(*pBianrySerializer) << (unsigned int)dSTORAGE_EOF;

		return true;
	}

	return false;
}

bool CNtlStorageGroup::Reset()
{
	for each( std::pair<eNTL_STORAGE_TYPE, CNtlStorageUnit*> pair in m_mapStorageUnit )
		if( pair.second->Reset() )
			return true;

	return false;
}

bool CNtlStorageGroup::SetData(unsigned int uiKey, int nData)
{
	std::ostringstream outstream;
	outstream << nData;
	std::string strData = outstream.str();

	for each( std::pair<eNTL_STORAGE_TYPE, CNtlStorageUnit*> pair in m_mapStorageUnit )
		if( pair.second->SetData( uiKey, strData ) )
			return true;

	return false;
}

bool CNtlStorageGroup::SetData(unsigned int uiKey, float fData)
{
	std::ostringstream outstream;
	outstream << fData;
	std::string strData = outstream.str();

	for each( std::pair<eNTL_STORAGE_TYPE, CNtlStorageUnit*> pair in m_mapStorageUnit )
		if( pair.second->SetData( uiKey, strData ) )
			return true;

	return false;
}

bool CNtlStorageGroup::SetData(unsigned int uiKey, std::string strData)
{
	for each( std::pair<eNTL_STORAGE_TYPE, CNtlStorageUnit*> pair in m_mapStorageUnit )
		if( pair.second->SetData( uiKey, strData ) )
			return true;

	return false;
}

bool CNtlStorageGroup::SetData(unsigned int uiKey, bool bData)
{
	std::string strData;
	if( bData )
		strData = dSTORAGE_TRUE;
	else
		strData = dSTORAGE_FALSE;

	for each( std::pair<eNTL_STORAGE_TYPE, CNtlStorageUnit*> pair in m_mapStorageUnit )
		if( pair.second->SetData( uiKey, strData ) )
			return true;

	return false;
}

bool CNtlStorageGroup::SetData( unsigned int uiKey, const char* acData )
{
	std::string strData( acData );
	
	for each( std::pair<eNTL_STORAGE_TYPE, CNtlStorageUnit*> pair in m_mapStorageUnit )
		if( pair.second->SetData( uiKey, strData ) )
			return true;

	return false;
}

bool CNtlStorageGroup::GetIntData(unsigned int uiKey, int& nData)
{
	std::string strOut;

	for each( std::pair<eNTL_STORAGE_TYPE, CNtlStorageUnit*> pair in m_mapStorageUnit )
		if( pair.second->GetData( uiKey, strOut ) )
		{
			nData = atoi(strOut.c_str());
			return true;
		}
	

	return false;
}

bool CNtlStorageGroup::GetStringData(unsigned int uiKey, std::string& strData)
{
	std::string strOut;

	for each( std::pair<eNTL_STORAGE_TYPE, CNtlStorageUnit*> pair in m_mapStorageUnit )
		if( pair.second->GetData( uiKey, strOut ) )
		{
			strData = strOut.c_str();
			return true;
		}

	return false;
}


bool CNtlStorageGroup::GetBoolData(unsigned int uiKey, bool& bData)
{
	std::string strOut;

	for each(std::pair<eNTL_STORAGE_TYPE, CNtlStorageUnit*> pair in m_mapStorageUnit)
	{
		if (pair.second->GetData(uiKey, strOut))
		{
			if (strOut.compare(dSTORAGE_TRUE) == 0)
				bData = true;
			else
				bData = false;

			return true;
		}
	}

	return false;
}

bool CNtlStorageGroup::GetFloatData(unsigned int uiKey, float& fData)
{
	std::string strOut;

	for each( std::pair<eNTL_STORAGE_TYPE, CNtlStorageUnit*> pair in m_mapStorageUnit )
		if( pair.second->GetData( uiKey, strOut ) )
		{
			fData = (float)atof( strOut.c_str() );
			return true;
		}

	return false;
}


void CNtlStorageGroup::UnitCheck()
{
	for each( std::pair< eNTL_STORAGE_TYPE, CNtlStorageUnit* > pair in m_mapStorageUnit )
		pair.second->UnitCheck();
}

void CNtlStorageGroup::SetStorageGroupType( eNTL_STORAGE_GROUP_TYPE eType )
{
	m_eGroupType = eType;
}

eNTL_STORAGE_GROUP_TYPE CNtlStorageGroup::GetStorageGroupType()
{
	return m_eGroupType;
}

int CNtlStorageGroup::GetIntData( unsigned int uiKey )
{
	std::string strOut;

	for each( std::pair<eNTL_STORAGE_TYPE, CNtlStorageUnit*> pair in m_mapStorageUnit )
		if( pair.second->GetData( uiKey, strOut ) )
		{
			return atoi(strOut.c_str());
		}

	return 0;
}

bool CNtlStorageGroup::GetBoolData( unsigned int uiKey )
{
	std::string strOut;

	for each( std::pair<eNTL_STORAGE_TYPE, CNtlStorageUnit*> pair in m_mapStorageUnit )
		if( pair.second->GetData( uiKey, strOut ) )
		{
			if( strOut.compare( dSTORAGE_TRUE ) == 0 )
				return true;
			else
				return false;
		}

	return false;
}

float CNtlStorageGroup::GetFloatData( unsigned int uiKey )
{
	std::string strOut;

	for each( std::pair<eNTL_STORAGE_TYPE, CNtlStorageUnit*> pair in m_mapStorageUnit )
		if( pair.second->GetData( uiKey, strOut ) )
		{
			return (float)atof( strOut.c_str() );
		}

	return 0.0f;
}

std::string CNtlStorageGroup::GetStringData( unsigned int uiKey )
{
	std::string strOut;

	for each( std::pair<eNTL_STORAGE_TYPE, CNtlStorageUnit*> pair in m_mapStorageUnit )
		if( pair.second->GetData( uiKey, strOut ) )
		{
			return strOut;
		}

	return strOut;
}

bool CNtlStorageGroup::IsHave( eNTL_STORAGE_TYPE eType )
{
	UNITMAP::iterator it = m_mapStorageUnit.find( eType );
	if( it == m_mapStorageUnit.end() )
	{
		return false;
	}

	return true;
}

CNtlStorageUnit* CNtlStorageGroup::GetStorageUnit( eNTL_STORAGE_TYPE eType )
{
	UNITMAP::iterator it = m_mapStorageUnit.find( eType );
	if( it == m_mapStorageUnit.end() )
	{
		return NULL;
	}

	return (*it).second;
}

bool CNtlStorageGroup::SetUnitApplyFunc( NtlStorageUnitApplyFunc func )
{
	for each( std::pair<eNTL_STORAGE_TYPE, CNtlStorageUnit*> pair in m_mapStorageUnit )
		pair.second->SetApplyFunc( func );

	return true;
}