#pragma once

#include "NtlInstanceTraceSystem.h"

/**
 * \ingroup NtlPresentation
 * \brief Particle�� Mesh System�� ���� �κ��� ǥ���ϱ� ���� ����Ʈ Ŭ����. TraceSystem���� ��ӹ޾Ƽ� �����.
 * \date 2006-12-29
 * \author agebreak
 */
class CNtlInstanceTrailSystem : public CNtlInstanceTraceSystem
{
public:
    CNtlInstanceTrailSystem(void);
    virtual ~CNtlInstanceTrailSystem(void);

    // new/delete override
    void* operator new(size_t size);
    void  operator delete(void* pObj);

    // Create/Delete override
    virtual RwBool  Create(CNtlInstanceComponentSystem* pComponentSystem, SNtlPrtStdEmitterTrail* pEmitterTrail);
    virtual void    Delete();

protected:
    virtual void Init();
    virtual void Reset();

    virtual void   CreateEdge();                                        ///< ���ο� Edge�� �߰��Ѵ�.
    void           SetEdgePoint();                                      ///< Edge ��ġ�� �����Ѵ�.

protected:
    SNtlPrtStdEmitterTrail*         m_pEmitterTrail;                    ///< Trail ���� ������ ������ �ִ� ������Ƽ ��ü
    CNtlInstanceComponentSystem*    m_pAttachComponent;                 ///< Trail�� ������ InstanceComponentSystem ��ü
    
    RwV3d                           m_vPrevTrailPoint;                  ///< ���� �����ӿ� ����� Trail Point;
};
