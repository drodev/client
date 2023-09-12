#pragma once

#include "NtlResourceImVertexSystem.h"

/**
 * \ingroup NtlPresentation
 * \brief ����(�β��� ���� ��) ����Ʈ�� ����� ���� ���ҽ� Ŭ����
 * \date 2006-09-21
 * \author agebreak
 */
class CNtlResourceLineSystem : public CNtlResourceImVertexSystem
{
public:
    CNtlResourceLineSystem(const RwChar* strName);
    virtual ~CNtlResourceLineSystem(void);

    virtual void Destroy();

    virtual RwBool Load(FILE* pFile);   ///< ���Ϸκ��� �����͸� �ε��Ѵ�.

public:   
    SNtlLineEmitterStandard         m_EmitterStandard;          ///< Line System�� �⺻ �Ӽ�����    
    
    SNtlPrtStdEmitterPrtSphere      m_EmitterSphere;            ///< Sphere Emitter
    SNtlPrtStdEmitterPrtRotate		m_EmitterPrtRotate;         ///< Rotate Emitter
    SNtlAdvMultiRotateEmitter		m_EmitterPrtMultiRotate;    ///< Multi Rotate

};
