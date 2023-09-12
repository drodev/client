#pragma once

#include "NtlInstanceImVertexSystem.h"

class CNtlPLItem;

///< Grade Effect�� �ٴ� Bone ���� ����
enum EGradeBoneIndex
{
    GRADE_EFFECT_BONE1,     ///< ù��° ���� Bone�� ���δ�. (Į���� �Ϲ� ����)
    GRADE_EFFECT_BONE2,     ///< �ι�° ���� Bone�� ���δ�. (�۷���, Ŭ�ο�.)
};

/**
 * \ingroup NtlPresentation
 * \brief Item�� Upgrade Effect�� ������ Ŭ���� (NOTE: Resource Ŭ���� ���� �ܵ����� ���δ�.)
 * Effect Tool���� ���� ���� �ʴ� Effect
 * \date 2006-12-13
 * \author agebreak
 */
class CNtlInstanceUpgradeEffectSystem : public CNtlInstanceImVertexSystem
{
public:
    CNtlInstanceUpgradeEffectSystem(void);
    virtual ~CNtlInstanceUpgradeEffectSystem(void);

    void* operator new(size_t size);
    void  operator delete(void* pObj);

    virtual RwBool Create(CNtlPLItem* pItem, EGradeBoneIndex eBoneIndex = GRADE_EFFECT_BONE1);
    virtual void   Delete();

    virtual RwBool Update(RwReal fElapsedTime);
    virtual RwBool Render();

    void    SetTexture(RwChar* szTextureName);             ///< Texture�� �����Ѵ�.    
protected:
    virtual void Init();
    virtual void Reset();

    RwBool  UpdateVertices(RwReal fElapsedTime);

private:
    // �� Create �Լ��� ������� �ʴ´�.
    virtual RwBool Create(CNtlResourceEffect* pResourceEffect, CNtlResourceComponentSystem* pResourceComponentSystem, const RwMatrix& matWorld) {return TRUE;}

protected:
    CNtlPLItem*     m_pItem;                        ///< Effect�� ���� Item ��ü�� ������    
    RwReal          m_fEffetWidthRatio;
    RwBool          m_bWidthSizeUp;    
    EGradeBoneIndex      m_eGradeBone;                   ///< ��� ���� �������� ������
};
