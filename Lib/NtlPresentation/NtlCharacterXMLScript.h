#pragma once
#pragma warning( disable : 4996 )

#include "NtlSharedCommon.h"
#include "NtlXMLDoc.h"
#include "NtlPLCharacterProperty.h"
#include "NtlPLXMLScriptHelper.h"

// 1.1 : Bone Scale�� ������� ���� ��� Bone Scale Data�� ����/�ε����� �ʵ��� ����

#define CHARACTER_XML_SCRIPT_VER        L"2"

/**
 * \ingroup NtlPresentation
 * \brief ĳ���� ��ũ��Ʈ(XML)�� Save/Load �ϴ� Ŭ����
 * \date 2006-05-16
 * \author agebreak
 */
class CNtlCharacterXMLScript : public CNtlXMLDoc
{
public:
    CNtlCharacterXMLScript(void);
    virtual ~CNtlCharacterXMLScript(void);

    RwBool SaveCharacterScript(const char* strFileName, CNtlPLCharacterProperty* pProperty);         ///< ĳ���� ������Ƽ�� XML ��ũ��Ʈ�� �����Ѵ�.
    RwBool LoadCharacterScript(const char* strFileName, CNtlPLCharacterProperty* pProperty);         ///< XML ��ũ��Ʈ�� �ε��Ͽ� ĳ���� ������Ƽ�� �����Ѵ�.

protected:
    RwBool  SaveHeader(CNtlPLCharacterProperty* pProperty);                        ///< Header �κ��� �����Ѵ�.
    RwBool  SaveBoneData(CNtlPLCharacterProperty* pProperty);                      ///< Bone Data �κ��� �����Ѵ�
    RwBool  SaveLinkEffect(CNtlPLCharacterProperty* pProperty);                    ///< Link Effect Data �κ��� �����Ѵ�.
    RwBool  SaveAnimTable(CNtlPLCharacterProperty* pProperty);                     ///< AnimTable �κ��� �����Ѵ�.      

    RwBool  LoadHeader(CNtlPLCharacterProperty* pProperty);                        ///< Header �κ��� �ε��Ѵ�.
    RwBool  LoadBoneData(CNtlPLCharacterProperty* pProperty);                      ///< Bone Data �κ��� �ε��Ѵ�.
    RwBool  LoadLinkEffect(CNtlPLCharacterProperty* pProperty);                    ///< Link Effect Data �κ��� �ε��Ѵ�.
    RwBool  LoadAnimTable(CNtlPLCharacterProperty* pProperty);                     ///< AnimTable  �κ��� �ε��Ѵ�.


    //////////////////////////////////////////////////////////////////////////
    void    SaveHitEvent(IXMLDOMElement* pElemEvent, const SEventAnimHit* pEventHit);  ///< Hit Event�� Save �Ѵ�.    
    void    LoadHitEvent(IXMLDOMNode* pNodeEvent, SEventAnimHit* pEventHit);           ///< Hit Event�� Load �Ѵ�.

    void    SaveTraceEvent(IXMLDOMElement* pElemEvent, const SEventTrace* pEventTrace);  ///< Trace Event�� Save �Ѵ�.    
    void    LoadTraceEvent(IXMLDOMNode* pNodeEvent, SEventTrace* pEventTrace);           ///< Trace Event�� Load �Ѵ�.

    void    SaveSubWeaponEvent(IXMLDOMElement* pElemEvent, const SEventSubWeapon* pEventSubWeapon); ///< SubWeapon Event�� Save�Ѵ�.
    void    LoadSubWeaponEvent(IXMLDOMNode* pNodeEvent, SEventSubWeapon* pEventSubWeapon);          ///< SubWeapon Event�� Load�Ѵ�.

	void	SavePostEffectEvent(IXMLDOMElement* pElemEvent, const SEventPostEffect* pEventPostEffect);	///< Post Effect Event�� Save �Ѵ�.
	void	LoadPostEffectEvent(IXMLDOMNode* pNodeEvent, SEventPostEffect* pPostEffect);				///< Post Effect Event�� Load �Ѵ�.

    void    SaveFootStepEvent(IXMLDOMElement* pElemEvent, const SEventFootStep* pEventFootStep);        ///< ǲ���� �̺�Ʈ�� Save�Ѵ�.
    void    LoadFootStepEvent(IXMLDOMNode* pNodeEvent, SEventFootStep* pFootStep);                      ///< ǲ���� �̺�Ʈ�� Load�Ѵ�.

    void    SaveDirectEvent(IXMLDOMElement* pElemEvent, const SEventDirect* pEventDirect);
    void    LoadDirectEvent(IXMLDOMNode* pNodeEvent, SEventDirect* pEventDirect);

    void    SaveColorChangeEvent(IXMLDOMElement* pElemEvent, const SEventColorChange* pEvent);         
    void    LoadColorChangeEvent(IXMLDOMNode* pNodeEvent, SEventColorChange* pEvent);

    void    SaveStretchEvent(IXMLDOMElement* pElemEvent, const SEventStretch* pEvent);
    void    LoadStretchEvent(IXMLDOMNode* pNodeEvent, SEventStretch* pEvent);
    
    void    SaveTriggerEvent(IXMLDOMElement* pElemEvent, const SEventTrigger* pEvent);
    void    LoadTriggerEvent(IXMLDOMNode* pNodeEvent, SEventTrigger* pEvent);

    void    SaveSkillCancelEvent(IXMLDOMElement* pElemEvent, const SEventSkillCancel* pEvent);
    void    LoadSkillCancelEvent(IXMLDOMNode* pNodeEvent, SEventSkillCancel* pEvent);   

protected:
    IXMLDOMElement*     m_pElemRoot;             ///< Root Element
    CNtlPLXMLScriptHelper m_XMLScriptHelper;     ///< DBO XML Script Helper 
};
