#pragma once

#include <list>
#include "NtlInstanceImVertexSystem.h"
#include "NtlAnimEventData.h"

#define WEAPON_BONE_NAME_1      "TracePoint1"
#define WEAPON_BONE_NAME_2      "TracePoint2"

// ������ ���Ǵ� vertex ����ü
struct STraceEdge
{
    RwReal          fLifeTime;       ///< Edge�� ���� �ð�
    RwIm3DVertex    vVertices[2];    ///< Edge�� �����ϴ� �ΰ��� Vertex    
};

typedef std::list<STraceEdge*> ListTraceEdge;

/**
 * \ingroup NtlPresentation
 * \brief ����(Trace) ����Ʈ �ν��Ͻ� Ŭ����
 * \date 2006-09-14
 * \author agebreak
 */
class CNtlInstanceTraceSystem : public CNtlInstanceImVertexSystem
{
public:
    CNtlInstanceTraceSystem(void);
    virtual ~CNtlInstanceTraceSystem(void);

    void* operator new(size_t size);
    void  operator delete(void* pObj);

    virtual RwBool Create(SEventTrace* pEventTrace, CNtlPLAttach* pAttach);        ///< TraceEvent ��ü�� ����Ʈ�� �����Ѵ�.
    virtual void   Delete();

    virtual RwBool Update(RwReal fElapsedTime);
    virtual RwBool Render();

protected:
    virtual void Init();
    virtual void Reset();
    
    void    SetEdgePoint(CNtlPLAttach* pAttach);                  ///< Edge�� ���� Vertex�� ��ġ�� �����Ѵ�.
    virtual RwBool  UpdateVertices(RwReal fElapsedTime);          ///< Vertex���� ������ Update�Ѵ�.
    virtual void    CreateEdge();                                         ///< ���ο� Edge�� �߰��Ѵ�.
    void    CreateSplinePath();                                   ///< Spline Path Point���� ���� ���ؽ� ���ۿ� �ִ´�.

    virtual void UpdateUV();                                      ///< UV���� Update�Ѵ�.
    virtual void UpdateColor();                                   ///< Color���� Update�Ѵ�.

private:
    // �� Create �Լ��� ������� �ʴ´�.
    virtual RwBool Create(CNtlResourceEffect* pResourceEffect, CNtlResourceComponentSystem* pResourceComponentSystem, const RwMatrix& matWorld) {return TRUE;}

protected:    
    SEventTrace*    m_pEventTrace;              ///< ���� ������ ������ �ִ� Event ��ü
    CNtlPLAttach*   m_pAttach;                  ///< ������ ���� ĳ���� or Item

    RwV3d           m_vStartPoint;              ///< ������ ���� Point
    RwV3d           m_vEndPoint;                ///< ������ �� Point

    ListTraceEdge   m_listTraceEdge;            ///< ���� ������ �����ϰ� �ִ� Edge���� ����Ʈ
    ListTraceEdge   m_listControlPoint;         ///< ControlPoint���� List
    STraceEdge*     m_poolTraceEdge;            ///< Trace Edge ����ü Pool (Spline���� Control Point�� �ȴ�)
    STraceEdge*     m_poolControlPoint;         ///< ���� �׷��� Spline�� �����ϴ� ����ü Pool
    RwInt32         m_nPoolIndex;               ///< Pool���� ����� Index
    RwInt32         m_nControlPointIndex;       ///< Spline�� Pool Index
    RwReal          m_fEdgeGapTemp;             ///< Edge Gap�� üũ�ϱ� ���� ����    
};

typedef std::list<CNtlInstanceTraceSystem*> ListTraceSystem;
