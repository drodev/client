#pragma once

#pragma warning( disable : 4996 )

#include "NtlSharedCommon.h"
#include "NtlXMLDoc.h"
#include "NtlPLObjectProperty.h"
#include "NtlPLXMLScriptHelper.h"

#define OBJECT_XML_SCRIPT_VER       L"1.0"

/**
 * \ingroup NtlPresentation
 * \brief ������Ʈ ��ũ��Ʈ(XML)�� Save/Load �ϴ� Ŭ����
 * \date 2006-06-07
 * \author agebreak
 */
class CNtlPLObjectXMLScript : public CNtlXMLDoc
{
public:
    CNtlPLObjectXMLScript(void);
    virtual ~CNtlPLObjectXMLScript(void);

    RwBool SaveObjectScript(const char* strFileName, CNtlPLObjectProperty* pProperty);      ///< ��ũ��Ʈ ������ �����Ѵ�.
    RwBool LoadObjectScript(const char* strFileName, CNtlPLObjectProperty* pProperty);      ///< ��ũ��Ʈ ������ �ε��Ѵ�.

protected:    
    RwBool SaveHeader(CNtlPLObjectProperty* pProperty);             ///< ��� �κ��� �����Ѵ�.
    RwBool SaveBody(CNtlPLObjectProperty* pProperty);               ///< �ٵ� �κ��� �����Ѵ�.
    RwBool SaveLinkEffect(CNtlPLObjectProperty* pProperty);		    ///< Link Effect Data �κ��� �����Ѵ�.
	RwBool SaveAnimTable(CNtlPLObjectProperty* pProperty);       ///< AnimTable �κ��� �����Ѵ�.      

    RwBool LoadHeader(CNtlPLObjectProperty* pProperty);             ///< ��� �κ��� �ε��Ѵ�.
    RwBool LoadBody(CNtlPLObjectProperty* pProperty);               ///< ��� �κ��� �ε��Ѵ�.
    RwBool LoadLinkEffect(CNtlPLObjectProperty* pProperty);         ///< Link Effect Data �κ��� �ε��Ѵ�.
	RwBool LoadAnimTable(CNtlPLObjectProperty* pProperty);                     ///< AnimTable  �κ��� �ε��Ѵ�.

protected:
    IXMLDOMElement*     m_pElemRoot;                ///< Root Element
    CNtlPLXMLScriptHelper m_XMLScriptHelper;        ///< DBO XML Script Helper
};
