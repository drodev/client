/*****************************************************************************
*
* File			: NtlSLTBCrowdController.h
* Author		: agebreak
* Copyright		: (��)NTL
* Date			: 2008. 7. 14	
*****************************************************************************
* Desc          : õ������ ����ȸ�� ���� �̺�Ʈ ��Ʈ�ѷ�
*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// util
#include "NtlSerializer.h"

class CNtlSLCENode;

/**
 * \ingroup NtlSimulation
 * \brief ������ �����ϴ� ��Ʈ�ѷ� Ŭ����. Ÿ�Ժ��� �����Ǿ� ���ȴ�.
 *
 * \date 2008-07-21
 * \author agebreak
 */

typedef std::list<CNtlSLCENode*>				LIST_CENODE;
typedef std::list<CNtlSLCENode*>::iterator		ITER_CENODE;

class CNtlSLTBCrowdController
{
public:
    CNtlSLTBCrowdController(void);
    ~CNtlSLTBCrowdController(void);

    void        Create();
    void        Destroy();
    RwBool      Update(RwReal fElapsedTime);    
    RwBool      Load(CNtlSerializer& s);
    RwBool      Save(CNtlSerializer& s);

	LIST_CENODE&	GetNodeList() { return m_listNode; }

    void        AddNode(CNtlSLCENode* pCENode);
    void        RemoveNode(CNtlSLCENode* pCENode);
    CNtlSLCENode* GetNode(const RwChar* szName);

    void        SetPosition(RwV3d& vPos);
	RwV3d		 GetPosition();

    void        SetName(const std::string& strKeyName) {m_strKeyName = strKeyName;}
    std::string GetName() {return m_strKeyName;}

    void        SetLoop(RwBool bLoop) {m_bLoop = bLoop;}
    RwBool      IsLoop() {return m_bLoop;}

    void        SetLifeTime(RwReal fLifeTime) {m_fLifeTime = fLifeTime;}
    RwReal      GetLifeTime() {return m_fLifeTime;}

	void		HandleEvents(RWS::CMsg &pMsg);

protected:    

protected:        
    std::string                 m_strKeyName;               ///< ��Ʈ�ѷ��� Ű����
    RwBool                      m_bLoop;                    ///< ���� ����Ʈ�� ��� ����� ������ ���� �÷���
    RwReal                      m_fLifeTime;                ///< ��� �ð�
	RwV3d							m_v3Pos;					///< Entry ��ǥ


    LIST_CENODE					    m_listNode;                 ///< ���� ����� ����Ʈ
    RwReal                      m_fInstanceTime;            ///< ������ �ð�
};
