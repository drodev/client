#pragma once

#pragma warning( disable : 4996 )

#include "NtlSharedCommon.h"
#include "NtlXMLDoc.h"
#include "NtlPLItemProperty.h"
#include "NtlPLXMLScriptHelper.h"

#define ITEM_XML_SCRIPT_VER       L"2.0"

/**
 * \ingroup NtlPresentation
 * \brief ������ ��ũ��Ʈ(XML)�� Save/Load �ϴ� Ŭ����
 * \date 2006-06-26
 * \author agebreak
 */
class CNtlPLItemXMLScript : public CNtlXMLDoc
{
public:
    CNtlPLItemXMLScript(void);
    virtual ~CNtlPLItemXMLScript(void);

    RwBool SaveItemScript(const char* strFileName, CNtlPLItemProperty* pProperty);      ///< ��ũ��Ʈ ������ �����Ѵ�.
    RwBool LoadItemScript(const char* strFileName, CNtlPLItemProperty* pProperty);      ///< ��ũ��Ʈ ������ �ε��Ѵ�.

protected:
    RwBool SaveHeader(CNtlPLItemProperty* pProperty);             ///< ��� �κ��� �����Ѵ�.
    RwBool SaveBody(CNtlPLItemProperty* pProperty);               ///< Body �κ��� �����Ѵ�.        

    RwBool LoadHeader(CNtlPLItemProperty* pProperty);             ///< ��� �κ��� �ε��Ѵ�.
    RwBool LoadBody(CNtlPLItemProperty* pProperty);               ///< Body �κ��� �����Ѵ�


    RwBool SaveLinkEffect(CNtlPLItemProperty* pProperty);    ///< Link Effect Data �κ��� �����Ѵ�.
    RwBool LoadLinkEffect(CNtlPLItemProperty* pProperty);    ///< Link Effect Data �κ��� �ε��Ѵ�.

    void   SaveTraceEvent(const SEventTrace* pEventTrace);  ///< Trace Event�� Save �Ѵ�.    
    void   LoadTraceEvent(SEventTrace* pEventTrace);           ///< Trace Event�� Load �Ѵ�.

    RwBool SaveAnimTable(CNtlPLItemProperty* pProperty);          ///< Item�� AnimTable�� �����Ѵ�.
    RwBool LoadAnimTable(CNtlPLItemProperty* pProperty);          ///< Item�� AnimTable�� �ε��Ѵ�.  

    RwBool SaveUpgradeEffect(CNtlPLItemProperty* pProperty);      ///< Item�� UpgradeEffect Proeprty�� �����Ѵ�.
    RwBool LoadUpgradeEffect(CNtlPLItemProperty* pProperty);      ///< Item�� UpgradeEffect Property�� �ε��Ѵ�.

protected:
    IXMLDOMElement*     m_pElemRoot;                ///< Root Element
    RwReal              m_fScriptVer;               ///< ���� �ε��ϰ� �ִ� ��ũ��Ʈ�� ����
    CNtlPLXMLScriptHelper m_XMLScriptHelper;        ///< DBO XML Script Helper
};
