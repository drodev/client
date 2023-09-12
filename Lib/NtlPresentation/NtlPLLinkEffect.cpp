#include "precomp_ntlpresentation.h"
#include "NtlPLSceneManager.h"
#include "NtlDebug.h"
#include "NtlPLLinkEffect.h"

CNtlPLLinkEffect::CNtlPLLinkEffect(void)
{
}

CNtlPLLinkEffect::~CNtlPLLinkEffect(void)
{
    for(size_t i = 0; i < m_vecLinkEffect.size(); ++i)
    {
        if(m_vecLinkEffect[i])
        {
            m_vecLinkEffect[i]->SetVisible(FALSE);
            GetSceneManager()->DeleteEntity(m_vecLinkEffect[i]);        
            m_vecLinkEffect[i] = NULL;
        }        
    }

    m_vecLinkEffect.clear();
}

/**
 * LinkEffect�� �����Ͽ� �����Ѵ�.
 * \param pAttach ������ �θ� ��ü
 * \param pEventLinkEffect ����Ʈ�� ������ ������Ƽ ��ü
 * \param vLinkEffect Instance Effect�� ������ vector
 * return ������ Effect ��ü, ���нÿ� NULL�� ��ȯ
 */
CNtlInstanceEffect* CNtlPLLinkEffect::AttachLinkEffect(CNtlPLAttach* pAttach, SEventLinkEffect* pEventLinkEffect)
{
    if(!pAttach || !pEventLinkEffect)
        return NULL;

    // Add an effect to the screen
    CNtlInstanceEffect* pEffect = NULL;
    if(pEffect == NULL)
    {
	//	DBO_WARNING_MESSAGE("pEventLinkEffect->chEffectName: " << pEventLinkEffect->chEffectName);
        pEffect = (CNtlInstanceEffect*)GetSceneManager()->CreateEntity(PLENTITY_EFFECT, pEventLinkEffect->chEffectName);
		if (!pEffect)
		{
			return NULL;
		}

        // Auto Delete ����Ʈ�� ����Ҽ� ����.
        if(pEffect->IsAutoDelete())
        {
            pEffect->SetVisible(FALSE);
            GetSceneManager()->DeleteEntity(pEffect);
            return NULL;
        }
    }

    // Attach �Ѵ�.
    RwBool bSuccess = FALSE;
    if(pEventLinkEffect->bAttachBone)
    {
        SPLAttachAttr attr;
        attr.vOffsetPos = pEventLinkEffect->vOffsetPos;        
         bSuccess = pAttach->AttachBone(pEffect, pEventLinkEffect->chBoneName, &attr);
    }
    else
    {
		bSuccess = pAttach->AttachWorldPosAndRotate(pEffect, pEventLinkEffect->vOffsetPos);
    }

    if(!bSuccess)       // Attach�� ���������� ���� �ʾ����� (���� ���ٴ���..)
    {
        GetSceneManager()->DeleteEntity(pEffect);
        return NULL;
    }

    // �θ��� Visible �Ӽ��� ������.
    pEffect->SetVisible(pAttach->IsVisible());

    m_vecLinkEffect.push_back(pEffect);    

    return pEffect;
}

/**
* LinkEffect�� �����Ѵ�.
* \param pAttach LinkEffect�� ������ �θ� ��ü
* \param pEventLinkEffect ������ LinkEffect
* \param vLinkEffect Instance Effect�� ������ vector
* return ���� ����
*/
RwBool CNtlPLLinkEffect::DetachLinkEffect(CNtlPLAttach* pAttach, CNtlInstanceEffect* pLinkEffect)
{
    if(!pAttach || !pLinkEffect)
        return FALSE;

    pAttach->Detach(pLinkEffect);
    pLinkEffect->SetVisible(FALSE);
    GetSceneManager()->DeleteEntity(pLinkEffect);    

    // Intance���� Vector���� �����Ѵ�.    
    VecLinkEffect::iterator it = m_vecLinkEffect.begin();
    for(; it != m_vecLinkEffect.end(); ++it)
    {
        CNtlInstanceEffect* pLinkEfffectInstance = *it;
        if(pLinkEffect == pLinkEfffectInstance)
        {
            m_vecLinkEffect.erase(it);
            break;
        }
    }
    
    return TRUE;
}


/**
 * Effect �ν���Ʈ ����Ʈ�߿��� �̸��� �ش��ϴ� �ν��Ͻ� ����Ʈ�� ��ȯ�Ѵ�.
 * \param szName ã�� ����Ʈ�� �̸�
 * return ã�� �ν��Ͻ� ����Ʈ ��ü. ã�����ϸ� NULL�� ��ȯ�Ѵ�.
 */
CNtlInstanceEffect* CNtlPLLinkEffect::GetLinkEffectFromName(RwChar* szName)
{
    if(!szName)
        return NULL;

    for(size_t i = 0; i < m_vecLinkEffect.size(); ++i)
    {
        if(m_vecLinkEffect[i])
        {
            if(strcmp(m_vecLinkEffect[i]->GetName(), szName) == 0)
                return m_vecLinkEffect[i];
        }        
    }

    return NULL;
}

void CNtlPLLinkEffect::SetVisible(BOOL bVisible)
{
    for(size_t i = 0; i < m_vecLinkEffect.size(); ++i)
    {
        if(m_vecLinkEffect[i])
        {
            m_vecLinkEffect[i]->SetVisible(bVisible);
        }
    }
}