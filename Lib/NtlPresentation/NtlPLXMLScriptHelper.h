#pragma once

#include "NtlXMLDoc.h"
#include "NtlSharedCommon.h"
#include "NtlAnimEventData.h"
#include "NtlTypeAnimData.h"

/**
* \ingroup NtlPresentation
* \brief Model Tool�� ���Ǵ� XML Script�� Event���� ���� ����ȴ�.
*        �̷��� ����� �̺�Ʈ�� �����ϱ� ���� ����� �ڵ带 ��Ƴ��� ���� Helper Ŭ���� 
* \date 2007-10-25
* \author agebreak
*/
class CNtlPLXMLScriptHelper : public CNtlXMLDoc
{
public:
    CNtlPLXMLScriptHelper(void);
    ~CNtlPLXMLScriptHelper(void);

    // ����Ǵ� �̺�Ʈ ����/�ε� ���� �Լ���
    RwBool  SaveTMQEvent(IXMLDOMElement* pElemEvent, const SEventAnimCinematic* pEventTMQ);               ///< TMQ Event�� Save �Ѵ�.
    RwBool  LoadTMQEvent(IXMLDOMNode* pNodeEvent, SEventAnimCinematic* pEventTMQ);

    RwBool  SaveAlphaEvent(IXMLDOMElement* pElemEvent, const SEventAlpha* pEventAlpha);         ///< Alpha Event�� Save �Ѵ�.
    RwBool  LoadAlphaEvent(IXMLDOMNode* pNodeEvent, SEventAlpha* pEventAlpha);                  ///< Alpha Event�� Load �Ѵ�.

    RwBool  SaveExplosionEvent(IXMLDOMElement* pElemEvent, const SEventExplosion* pEventExplosion); ///< ���� �̺�Ʈ�� Save�Ѵ�.
    RwBool  LoadExplosionEvent(IXMLDOMNode* pNodeEvent, SEventExplosion* pEventExplosion);          ///< ���� �̺�Ʈ�� Load�Ѵ�.

    RwBool  SaveSoundEvent(IXMLDOMElement* pElemEvent, const SEventSound* pEventSound);         ///< Sound Event�� �����Ѵ�.
    RwBool  LoadSoundEvent(IXMLDOMNode* pNodeEvent, SEventSound* pEventSound);                  ///< Sound Event�� �ε��Ѵ�.

    RwBool  SaveEffectEvent(IXMLDOMElement* pElemEvent, const SEventVisualEffect* pEventEffect);    ///< ���־� ����Ʈ �̺�Ʈ�� �����Ѵ�.
    RwBool  LoadEffectEvent(IXMLDOMNode* pNodeEvent, SEventVisualEffect* pEventEffect);             ///< ���־� ����Ʈ �̺�Ʈ�� �ε��Ѵ�.

    RwBool  SaveAnimData(IXMLDOMElement* pElemAnimData, const STypeAnimData* pAnimData);        ///< �ִϸ��̼� �����͸� �����Ѵ�.    
    RwBool  LoadAnimData(IXMLDOMNode* pNodeAnimData, STypeAnimData* pAnimData);                 ///< �ִϸ��̼� �����͸� �ε��Ѵ�.

    // ���� ���� �Լ���
    static void SaveAttribute(IXMLDOMElement* pElem, WCHAR* szKey, RwInt32 nInt);                ///< Int���� Attribute�� �����Ѵ�.
    static void SaveAttribute(IXMLDOMElement* pElem, WCHAR* szKey, RwUInt32 nInt);               ///< Int���� Attribute�� �����Ѵ�.
    static void SaveAttribute(IXMLDOMElement* pElem, WCHAR* szKey, RwReal fFloat);               ///< float���� Attribute�� �����Ѵ�.
    static void SaveAttribute(IXMLDOMElement* pElem, WCHAR* szKey, const char* szChar);          ///< char���� Attribute�� �����Ѵ�.
    static void SaveAttribute(IXMLDOMElement* pElem, WCHAR* szKey, const RwV3d& v3d);            ///< RwV3d���� Attribute�� �����Ѵ�.
    static void SaveAttribute(IXMLDOMElement* pElem, WCHAR* szKey, const RwV2d& v2d);            ///< RwV2d���� Attribute�� �����Ѵ�.
    static void SaveAttribute(IXMLDOMElement* pElem, WCHAR* szKey, const RwRGBA& rgba);

protected:    
    static WCHAR   wBuf[128];
    static char    szBuf[128];    
};
