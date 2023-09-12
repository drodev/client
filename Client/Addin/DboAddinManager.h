#pragma once
#include "ceventhandler.h"

/// Addin ���̺귯������ �����ϴ� Ŭ����
/// ����� ��ũ������ ���� Devil�� �����Ѵ�.
class CDBOAddinManager : public RWS::CEventHandler
{
public:
    CDBOAddinManager();
    ~CDBOAddinManager();

    static void Init();
    static void ShutDown();

protected:
    virtual void			HandleEvents(RWS::CMsg &pMsg); 

    void    OnEventScreenShot(RWS::CMsg& pMsg);                 ///< ��ũ���� �����Ŀ� ���� ���� ó��

protected:
    static CDBOAddinManager* m_pInstance;

};