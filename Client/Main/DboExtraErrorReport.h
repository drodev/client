#pragma once

#include "NtlXMLDoc.h"

/**
 * \ingroup Client
 * \brief �߰� ������ ��������Ʈ�� ����ϴ� Ŭ����
 * \date 2007-01-25
 * \author agebreak
 */
class CDboExtraErrorReport : public CNtlXMLDoc
{
public:
    CDboExtraErrorReport(void);
    virtual ~CDboExtraErrorReport(void);

    RwBool Open();                                          ///< ������ �����Ѵ�.
    RwBool Save(const char* szFileName);                    ///< ������ ����ϰ� �����Ѵ�.

    void WriteInfo(RwChar* szNodeName, RwChar* szInfo);     ///< ���Ͽ� ������ ����Ѵ�.
    void WriteInfo(RwChar* szNodeName, WCHAR* szInfo);      ///< ���Ͽ� ������ ����Ѵ�.
    static void SetDXDiagLog();                             ///< Dxdiag �α׸� ����Ѵ�.

protected:
    RwBool SetIndent();                                             ///< XML�� ��Ÿ�� ��Ʈ�� �����Ѵ�. (indent.xls)

protected:
    IXMLDOMElement*     m_pRootElem;                ///< Root Element
};
