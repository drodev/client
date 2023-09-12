#pragma once

#include "NtlInstanceImVertexSystem.h"
#include "NtlResourceLineSystem.h"

/// LineSystem�� ����� �����ϴ� ������ ���� ����ü
struct SLineSystemVertex
{
    RwV3d vStrartPoint;     ///< �������� ��ġ                 
    RwV3d vUpdatePoint;     ///< ������Ʈ �Ǵ� ������ ��ġ
    RwV3d vDir;             ///< ���ư��� ����
    RwIm3DVertex imVertices[6]; ///< Line�� �����ϴ� 6���� ���ؽ��� ������
    RwReal fLifeTime;       ///< ������ Life Time
    RwV2d vLineSize;        ///< ������ Size (Size Action ������ �ʿ��ϴ�)
};

typedef std::list<SLineSystemVertex*> ListLineSystemVertex;

/**
 * \ingroup NtlPresentation
 * \brief ���� ����Ʈ �ν��Ͻ� Ŭ����
 * \date 2006-09-21
 * \author agebreak
 */
class CNtlInstanceLineSystem : public CNtlInstanceImVertexSystem
{
public:
    CNtlInstanceLineSystem(void);
    virtual ~CNtlInstanceLineSystem(void);

    void* operator new(size_t size);
    void  operator delete(void* pObj);

    virtual RwBool Create(CNtlResourceEffect* pResourceEffect, CNtlResourceComponentSystem* pResourceComponentSystem, const RwMatrix& matWorld);
    virtual void   Delete();

    virtual RwBool Update(RwReal fElapsedTime);
    virtual RwBool Render();    

    RwInt32 GetPolyCount() {return (int)m_listLineSystemVertex.size();} ///< ������ ������ ������ ��ȯ�Ѵ�.

protected:
    virtual void Init();
    virtual void Reset();    
    virtual void UpdateColor(RwReal fDeltaTime);
    virtual void UpdateSize(RwReal fDeltaTime);

    void UpdateVertices(RwReal fElapsedTime);
    void BuildEmitterStandard();
    void CreateLine();                                              ///< ���ο� ������ �����Ѵ�.
    void CreatePlane(SLineSystemVertex* pLineSystemVertex, const RwV3d& vStartAxis, const RwV3d& vEndAxis); ///< ������ ������ ����� �����Ͽ� ������ �����.
    void UpdateZBillBoard(SLineSystemVertex* pLineSystemVertex);    ///< z�� ������� ���� �����Ѵ�.    
    void UpdateNoneZBillBoard(SLineSystemVertex* pLineSystemVertex);///< Z�� �����尡 ������� ���� ���� �����Ѵ�.
    void UpdateShake(SLineSystemVertex* pLineSystemVertex);         ///< Shake�� �����Ѵ�.    
    void UpdateRotate(RwReal fDeltaTime);                           ///< Rotate�� �����Ѵ�.
    
protected:
    CNtlResourceLineSystem*     m_pResourceLineSystem;          ///< ���� ������ ������ �ִ� ���� ���ҽ� Ŭ����
    ListLineSystemVertex        m_listLineSystemVertex;         ///< LineSystem�� �����ϴ� ����� ����Ʈ
    SLineSystemVertex*          m_poolLineSystemVertex;         ///< LineSystem Vertex Memory Pool�� ������
    RwInt32                     m_nPoolIndex;                   ///< Memory Pool�� �ε���
    RwReal                      m_fCreateGapTime;               ///< ���� �ֱ⸦ ���ϱ����� ����
    RwInt32                     m_nRoateSeed;                   ///< Rotate Bias�� ���� Seed��               
};
