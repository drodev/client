#pragma once

#include "NtlResourceImVertexSystem.h"

/**
 * \ingroup NtlPresentation
 * \brief ����(Trace) ����Ʈ�� ����� ���� ���ҽ� Ŭ����
 * \date 2006-09-14
 * \author agebreak
 */
class CNtlResourceTraceSystem : public CNtlResourceImVertexSystem
{
public:
    CNtlResourceTraceSystem(const RwChar* strName);
    virtual ~CNtlResourceTraceSystem(void);

    virtual void Destroy();

    virtual RwBool Load(FILE* pFile);           ///< ���Ϸ� ���� �����͸� �ε��Ѵ�.

public:
    // ������Ƽ �Ӽ���
    RwInt32 m_nMaxFrameCount;                   ///< ������ �׸� �ִ� ������ ����. ��Ȯ���� ���� ����. ���ؽ��� �̰��� 2��� �����ȴ�. (���Ʒ� ¦). 1�����ӿ� �ϳ��� ���Ʒ�¦ ������ �׷�����.

protected:

protected:

};
