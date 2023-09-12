#pragma once

#include "NtlPLAttach.h"
#include "NtlAnimEventData.h"

typedef std::vector<CNtlInstanceEffect*> VecLinkEffect;
/**
 * \ingroup NtlPresentation
 * \brief Link Effect Ŭ���� (Model�� ��� �پ��ִ� ����Ʈ) 
 * \date 2006-07-14
 * \author agebreak
 */
class CNtlPLLinkEffect
{
public:
    CNtlPLLinkEffect(void);
    virtual ~CNtlPLLinkEffect(void);
    
    CNtlInstanceEffect* AttachLinkEffect(CNtlPLAttach* pAttach, SEventLinkEffect* pEventLinkEffect);    
    RwBool DetachLinkEffect(CNtlPLAttach* pAttach, CNtlInstanceEffect* pLinkEffect);
    CNtlInstanceEffect* GetLinkEffectFromName(RwChar* szName);          ///< �̸����� LinkEffect Instance�� �˻��Ͽ� ��ȯ�Ѵ�. (���������� ���)
    void SetVisible(BOOL bVisible);         ///< ��� LinkEffect�� Visible�� �����Ѵ�. 

public:
    VecLinkEffect m_vecLinkEffect;          ///< Link Effect Instance���� ����

};
